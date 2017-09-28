#pragma once

#include "Colors.h"
#include "RectI.h"
#include <string>

// Surface is a 2D array of pixels to represent a image
class Surface
{
public:
	Surface(const std::string& filename);

	Surface(int width, int height);
	Surface(const Surface& );
	~Surface();
	Surface& operator=(const Surface&);
	void PutPixel(int x, int y, Color c);
	Color GetPixel(int x, int y) const;
	int GetWidth() const;
	int GetHeight() const;
	RectI GetRect() const;
	

private:

	// Array of colors (pointers)
	Color* pPixels = nullptr;
	int width;
	int height;

};
