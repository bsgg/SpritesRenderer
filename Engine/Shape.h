#pragma once

#include "Definitions.h"

namespace MapGenerator
{
	class Shape
	{
	public:

		Shape();
		Shape(unsigned int in_x, unsigned int in_y, EShapeType in_shapeType);

		unsigned int GetX();
		void SetX(unsigned int in_x);

		unsigned int GetY();
		void SetY(unsigned int in_y);

		unsigned int GetSize();
		void SetSize(unsigned int in_size);

		EShapeType GetType();
		void SetType(EShapeType in_type);


	private:
		unsigned int x;
		unsigned int y;
		EShapeType shapeType;
		unsigned int size;
	};
}