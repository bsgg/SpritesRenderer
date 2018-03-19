#pragma once
#include <vector>
#include "Definitions.h"

using namespace std;

namespace MapGenerator
{
	struct Coords
	{
		int x;
		int y;

		Coords()
		{
			x = 0;
			y = 0;
		}
		Coords(int inX, int inY)
		{
			x = inX;
			y = inY;
		}
	};
	template< unsigned W, unsigned H, typename TYPE = int>
	class Matrix2D
	{
		public:

		TYPE matrix[W][H];

		Matrix2D(){}

		Matrix2D(const Matrix2D & other)
		{
			*this = other;
		}

		Matrix2D(const TYPE matrix)
		{
			*this = matrix;
		}

		// Assign operator
		Matrix2D & operator = (const Matrix2D & other)
		{
			const TYPE * src = &(other.matrix[0][0]);
			TYPE * dst = &(this->matrix[0][0]);

			for (unsigned i = 0; i < W*H; i++)
			{
				*dst++ = *src++;
			}

			return (*this);
		}

		Matrix2D & operator = (const TYPE matrix)
		{
			TYPE * dst = &this->matrix[0];

			for (unsigned i = 0; i < W*H; i++)
			{
				*dst++ = matrix;
			}

			return (*this);
		}

		void Initialize(int value)
		{
			for (int x = 0; x<W; x++) 
			{
				for (int y = 0; y<H; y++) 
				{
					matrix[x][y] = value;
				}
			}
		}
	};

	

	/** @brief Puzzle Board is in charge of generate the maps with 2 types of pieces
	*/
	class PacmanMapGenerator
	{


	public:
		enum EGridDefinitions { XCOLS = 6, YROWS = 15};		

		enum ETILETYPE {CLEAN, SHAPE, OBSTACLE, SPAWN };

		/*const unsigned int yRows = 15;
		const unsigned int xCols = 6;*/

		PacmanMapGenerator();

		void GenerateGrid(Matrix2D<EGridDefinitions::XCOLS, EGridDefinitions::YROWS, int> grid, Coords coord, EShapeType shapeType, int totalShapes);

	private:
		// Test if a shape is suitable for a given coord
		bool tryPlaceShape(Matrix2D<EGridDefinitions::XCOLS, EGridDefinitions::YROWS, int> * grid, Coords coord, EShapeType shapeType, int totalSteps, bool & testShape);

	private:

		
		// Number shapes
		const int sizeShape = 3;
		int shapesNumber = 0;
		int solutionNumber = 0;

		vector<Matrix2D<EGridDefinitions::XCOLS, EGridDefinitions::YROWS, int>> solutionList;

		Matrix2D<EGridDefinitions::XCOLS, EGridDefinitions::YROWS, int> * currentGrid;



	};

}