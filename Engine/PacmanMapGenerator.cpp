#include "PacmanMapGenerator.h"

namespace MapGenerator
{




	PacmanMapGenerator::PacmanMapGenerator():
		currentGrid(new Matrix2D<EGridDefinitions::XCOLS, EGridDefinitions::YROWS, int>())

	{
		//currentGrid = new Matrix2D<Definitions::XCOLS, Definitions::YCOLS, int>();
		currentGrid->Initialize(0);
	}


	void PacmanMapGenerator::GenerateGrid(Matrix2D<EGridDefinitions::XCOLS, EGridDefinitions::YROWS, int> grid, Coords coord, EShapeType shapeType, int totalShapes)
	{
		// No shapes (first time), call GenerateGrid with all 6 posibilites
		if (shapeType == EShapeType::NONE)
		{
			GenerateGrid(grid, coord, EShapeType::DOWN, totalShapes);
			GenerateGrid(grid, coord, EShapeType::ACROSS, totalShapes);
			GenerateGrid(grid, coord, EShapeType::RIGHT_L, totalShapes);
			GenerateGrid(grid, coord, EShapeType::LEFT_L, totalShapes);
			GenerateGrid(grid, coord, EShapeType::INVERT_RIGHT_L, totalShapes);
			GenerateGrid(grid, coord, EShapeType::INVERT_LEFT_L, totalShapes);
		}
		else
		{
			if (totalShapes > 0)
			{
				// test if if possible to locate the figure 
				bool testShape = false;
				tryPlaceShape(&grid, coord, shapeType, sizeShape - 1, testShape);

				// The shapes is correct
				if (testShape)
				{

				}
			}
		}
	}

	bool PacmanMapGenerator::tryPlaceShape(Matrix2D<EGridDefinitions::XCOLS, EGridDefinitions::YROWS, int> * grid, Coords coord, EShapeType shapeType, int totalSteps, bool & testShape)
	{
		
		if (totalSteps >= 0)
		{
			if ((grid->matrix[coord.x][coord.y] == ETILETYPE::CLEAN) || (grid->matrix[coord.x][coord.y] == ETILETYPE::SPAWN))
			{
				testShape = true;

				switch (shapeType)
				{				
				case MapGenerator::PacmanMapGenerator::DOWN: // | Shape

					// Check boundaries
					if ((coord.y + 1) < EGridDefinitions::YROWS)
					{
						coord.y = coord.y + 1;
					}
					else
					{
						// Check if more steps
						if (totalSteps > 0)
						{
							testShape = false;
						}
					}

					// If it's possible to place the shape, and we have more steps left, call the function again
					if (testShape && (totalSteps > 0))
					{
						// call test place shape
						tryPlaceShape(grid, coord, shapeType, totalSteps - 1, testShape);
					}

				break;
				case MapGenerator::PacmanMapGenerator::ACROSS: // -- Shape

															   // Check boundaries
					if ((coord.x + 1) < EGridDefinitions::XCOLS)
					{
						coord.x = coord.x + 1;
					}
					else
					{
						// Check if more steps
						if (totalSteps > 0)
						{
							testShape = false;
						}
					}

					// If it's possible to place the shape, and we have more steps left, call the function again
					if (testShape && (totalSteps > 0))
					{
						// call test place shape
						tryPlaceShape(grid, coord, shapeType, totalSteps - 1, testShape);
					}

				break;
				case MapGenerator::PacmanMapGenerator::RIGHT_L:  // L Shape (Down-Right direction)

					if (totalSteps == 2) // Step down
					{
						if ((coord.y + 1) < EGridDefinitions::YROWS)
						{
							coord.y = coord.y + 1;
						}
						else
						{
							testShape = false;							
						}

					}
					else if (totalSteps == 1) // Step right
					{
						if ((coord.x + 1) < EGridDefinitions::XCOLS)
						{
							coord.x = coord.x + 1;
						}
						else
						{
							testShape = false;
						}
					}

					if (testShape && (totalSteps > 0))
					{
						// call test place shape
						tryPlaceShape(grid, coord, shapeType, totalSteps - 1, testShape);
					}

					break;
					case MapGenerator::PacmanMapGenerator::LEFT_L:  // Mirror L Shape (Down-Left direction)

						if (totalSteps == 2) // Step down
						{
							if ((coord.y + 1) < EGridDefinitions::YROWS)
							{
								coord.y = coord.y + 1;
							}
							else
							{
								testShape = false;
							}

						}
						else if (totalSteps == 1) // Step left
						{
							if ((coord.x - 1) >= 0)
							{
								coord.x = coord.x - 1;
							}
							else
							{
								testShape = false;
							}
						}

						if (testShape && (totalSteps > 0))
						{
							// call test place shape
							tryPlaceShape(grid, coord, shapeType, totalSteps - 1, testShape);
						}


					break;
					case MapGenerator::PacmanMapGenerator::INVERT_RIGHT_L: // L Shape Upside down (Right - Down direction)

						if (totalSteps == 2) // Step right
						{
							if ((coord.x + 1) < EGridDefinitions::XCOLS)
							{
								coord.x = coord.x + 1;
							}
							else
							{
								testShape = false;
							}

						}
						else if (totalSteps == 1) // Step down
						{
							if ((coord.y + 1) < EGridDefinitions::YROWS)
							{
								coord.y = coord.y + 1;
							}
							else
							{
								testShape = false;
							}
						}

						if (testShape && (totalSteps > 0))
						{
							// call test place shape
							tryPlaceShape(grid, coord, shapeType, totalSteps - 1, testShape);
						}

					break;
					case MapGenerator::PacmanMapGenerator::INVERT_LEFT_L: // Mirror L Shape Upside down (Left - Down direction)

						if (totalSteps == 2) // Step left
						{
							if ((coord.x - 1) >= 0)
							{
								coord.x = coord.x - 1;
							}
							else
							{
								testShape = false;
							}

						}
						else if (totalSteps == 1) // Step down
						{
							if ((coord.y + 1) < EGridDefinitions::YROWS)
							{
								coord.y = coord.y + 1;
							}
							else
							{
								testShape = false;
							}
						}

						if (testShape && (totalSteps > 0))
						{
							// call test place shape
							tryPlaceShape(grid, coord, shapeType, totalSteps - 1, testShape);
						}
					break;
					default: // Any other shape
						testShape = false;
					break;
				}
			}
			else // Any other type of tile
			{
				testShape = false;
			}
		}
	}
}