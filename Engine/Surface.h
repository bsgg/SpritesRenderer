#pragma once

#include "Colors.h"
#include "Rect.h"
#include <string>

// Surface is a 2D array of pixels to represent a image
class Surface
{
public:
	Surface(const std::string& filename);

	Surface(int width, int height);
	Surface(const Surface& );
	Surface(Surface &&); // Move constructor
	Surface() = default;
	~Surface();
	Surface& operator=(const Surface&);
	Surface& operator=( Surface&&); // Move assigment operator
	void PutPixel(int x, int y, Color c);
	Color GetPixel(int x, int y) const;
	int GetWidth() const;
	int GetHeight() const;
	RectI GetRect() const;
	

private:

	// Array of colors (pointers)
	Color* pPixels = nullptr;
	int width = 0;
	int height = 0;

};
