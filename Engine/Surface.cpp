#include "Surface.h"
#include "ChiliWin.h"
#include <cassert>
#include <fstream>

Surface::Surface(const std::string& filename)
{

	// Open the file
	std::ifstream file(filename, std::ios::binary);

	assert(file);

	BITMAPFILEHEADER bmFileHeader; // Include in ChiliWin wich include window.h

	// Read the bits from file to the header
	file.read(reinterpret_cast<char*>(&bmFileHeader), sizeof(bmFileHeader) );

	BITMAPINFOHEADER bmInfoHeader;// Include in ChiliWin wich include window.h
	file.read(reinterpret_cast<char*>(&bmInfoHeader), sizeof(bmInfoHeader));

	// Assert to only deal with 24 bits bitmaps files
	// Each 3 byte is RGB
	// Pixel 0 = RGB  Pixel 1 = RGB  Pixel 2 = RGB ...
	// Color range from 0 to 255
	// We only want to deal with 24 bits format (3 byts for each pixel)
	assert(bmInfoHeader.biBitCount == 24 || bmInfoHeader.biBitCount == 32);
	assert(bmInfoHeader.biCompression == BI_RGB); // Only deal with no compression images

	const bool is32B = bmInfoHeader.biBitCount == 32;

	// Load width and height
	width = bmInfoHeader.biWidth;


	// If the biHeight is negative, the read pixels will be in reverse
	int yStart;
	int yEnd;
	int dy; // Direction for the loop
	if (bmInfoHeader.biHeight < 0)
	{
		height = -bmInfoHeader.biHeight;
		yStart = 0;
		yEnd = height;
		dy = 1;

	}else
	{
		height = bmInfoHeader.biHeight;
		yStart = height -1;
		yEnd = -1;
		dy = -1;

	}


	pixels.resize(width * height);
	//pPixels = std::make_unique<Color[]>(width*height);

	// Load the data into the array of pixels
	// Seek the pixels start
	// Every 3 bytes is 1 pixel (1 byte == 8 bits) = 3 Bytes == 24 bits each byte for each channel colour
	file.seekg(bmFileHeader.bfOffBits);

	// Every row of the file is divided into Pixels and Padding (at the end of each row), so in total the row size is multple of 4 Bytes
	// We will need to calculate the padding of each row

	// The row with no padding will be = width * 3
	// Padding is for the case of 24 bit depth only
	const int padding = (4 - (width * 3) % 4) % 4;

	// The bitmapt starts in the bottom left corner so we have to read the y from the bottom.
	// This information is given in bmInfoHeader.biHeight. If the height is negative the 0,0 starts in upper left corner
	for (int y = yStart; y != yEnd ; y += dy)
	{
		for (int x = 0; x < width; x++)
		{
			// Set each pixel from the file
			PutPixel(x, y, Color(file.get(), file.get(), file.get()));
			// If it's 32bits, will seek 1 element from current position
			if (is32B)
			{
				file.seekg(1, std::ios::cur);
			}

		}

		// Only seek for padding if it's not 32B (There will be no padding if it's 32 bits file)
		if (!is32B)
		{
			// Move to the next row including the padding
			file.seekg(padding, std::ios::cur);
		}
		
	}

}


Surface::Surface(int width, int height)
	:
	width(width),
	height(height),
	//pPixels( new Color[width*height])
	pixels(width * height)
{	
}

Surface::Surface(Surface&& donor)
{
	*this = std::move(donor);
}

/*Surface::Surface(const Surface& rhs)
	:
	Surface(rhs.width, rhs.height),

{
	const int nPixels = width * height;
	for (int i = 0; i < nPixels; i++)
	{
		pPixels[i] = rhs.pPixels[i];
	}
}*/


Surface& Surface::operator=(Surface&& rhs)
{
	/*if (&rhs != this)
	{
		width = rhs.width;
		height = rhs.height;

		// Free old buffer
		pPixels = std::make_unique<Color[]>(width * height);

		const int nPixels = width * height;
		for (int i = 0; i < nPixels; i++)
		{
			pPixels[i] = rhs.pPixels[i];
		}

		
	}*/

	return *this;

	width = rhs.width;
	height = rhs.height;
	pixels = std::move(rhs.pixels);
	rhs.width = 0;
	rhs.height = 0;
	return *this;
}


/*void Surface::PutPixel(int x, int y, Color c)
{
	assert(x >= 0);
	assert(x < width);
	assert(y >= 0);
	assert(y < height);

	pixels.data()[y * width + x] = c;
	//pPixels[y * width + x] = c;
}*/

/*Color Surface::GetPixel(int x, int y) const
{
	assert(x >= 0);
	assert(x < width);
	assert(y >= 0);
	assert(y < height);

	return pixels.data()[y * width + x];
	//return pPixels[y * width + x];
}*/

int Surface::GetWidth() const
{
	return width;
}

int Surface::GetHeight() const
{
	return height;
}


RectI Surface::GetRect() const
{
	return { 0, width, 0, height };
}


const Color* Surface::Data() const
{
	return pixels.data();
}
