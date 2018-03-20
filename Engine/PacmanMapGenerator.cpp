#include "PacmanMapGenerator.h"


namespace MapGenerator
{
	PacmanMapGenerator::PacmanMapGenerator() :
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
					Shape s(coord.x, coord.y, shapeType);

					// Add 1 to the right coord if the type of shape is INVERT_LEFT_L
					if (shapeType == EShapeType::INVERT_LEFT_L)
					{
						coord.x = coord.x + 1;
						s.SetX(coord.x);
						s.SetY(coord.y);
					}

					// Place shape
					placeShape(&grid, &s, coord, sizeShape - 1);

					if (s.GetSize() == sizeShape)
					{
						// cover shape
						coverShape(&grid, s, coord, sizeShape - 1);

						// Add 1 to number of shapes in grid
						shapesNumber += 1;
						totalShapes -= 1;

						// Find next spawn location in the grid for the shape
						coord =  findNextSpawnLocation(&grid, coord);

						if ((coord.x > -1) && (coord.y > -1))
						{
							GenerateGrid(grid, coord, EShapeType::DOWN, totalShapes);
							GenerateGrid(grid, coord, EShapeType::ACROSS, totalShapes);
							GenerateGrid(grid, coord, EShapeType::RIGHT_L, totalShapes);
							GenerateGrid(grid, coord, EShapeType::LEFT_L, totalShapes);
							GenerateGrid(grid, coord, EShapeType::INVERT_RIGHT_L, totalShapes);
							GenerateGrid(grid, coord, EShapeType::INVERT_LEFT_L, totalShapes);
						}
					}

				}
				else
				{
					// Unable to place shape, try with another shape

					EShapeType initShape = shapeType;
					bool exit = false;
					do
					{
						int tShape = shapeType;

						// Check if the shape is the last one
						if ((tShape + 1) > EShapeType::INVERT_LEFT_L)
						{
							tShape = EShapeType::DOWN;
						}
						else
						{
							tShape += 1;
						}

						shapeType = (EShapeType)tShape;

						if (tShape == initShape)
						{
							exit = true;
						}
						else
						{
							bool auxF = false;
							tryPlaceShape(&grid, coord, shapeType, sizeShape - 1, auxF);

							if (auxF)
							{
								exit = true;
							}

						}
					} while (!exit);

					if (shapeType != initShape)
					{
						GenerateGrid(grid, coord, shapeType, totalShapes);
					}
				}
			}
		}

		if (totalShapes == 0)
		{
			bool isDifferent = true;

			int nDifferentSolutions = 0;

			if (solutionList.size() > 0)
			{
				for (int k = 0; k < solutionList.size(); k++)
				{
					bool checkSolution = true;
					for (int x = 0; x < EGridDefinitions::XCOLS; x++)
					{
						for (int y = 0; y < EGridDefinitions::YROWS; y++)
						{
							if ((grid.matrix[x][y]) != (solutionList[k].matrix[x][y]))
							{
								checkSolution = false;
								break;
							}
						}
						if (!checkSolution)
						{
							break;
						}
					}
				}
			}

			if (isDifferent)
			{
				solutionNumber++;
				solutionList.push_back(grid);
				currentGrid = &grid;
			}
		}

		shapesNumber = 0;
	}

	int PacmanMapGenerator::GetShapesNumber() const
	{
		return shapesNumber;
	}
	int PacmanMapGenerator::GetSolutionNumber() const
	{
		return solutionNumber;
	}

	void PacmanMapGenerator::tryPlaceShape(Matrix2D<EGridDefinitions::XCOLS, EGridDefinitions::YROWS, int> * grid, Coords coord, EShapeType shapeType, int totalSteps, bool & testShape)
	{

		if (totalSteps >= 0)
		{
			if ((grid->matrix[coord.x][coord.y] == ETILETYPE::CLEAN) || (grid->matrix[coord.x][coord.y] == ETILETYPE::SPAWN))
			{
				testShape = true;

				switch (shapeType)
				{
				case EShapeType::DOWN: // | Shape

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
				case EShapeType::ACROSS: // -- Shape

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
				case EShapeType::RIGHT_L:  // L Shape (Down-Right direction)

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
				case EShapeType::LEFT_L:  // Mirror L Shape (Down-Left direction)

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
				case EShapeType::INVERT_RIGHT_L: // L Shape Upside down (Right - Down direction)

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
				case EShapeType::INVERT_LEFT_L: // Mirror L Shape Upside down (Left - Down direction)

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

	void PacmanMapGenerator::placeShape(Matrix2D<EGridDefinitions::XCOLS, EGridDefinitions::YROWS, int> * grid, Shape * shape, Coords coord, int totalSteps)
	{
		if ((grid->matrix[coord.x][coord.y] == ETILETYPE::CLEAN) || (grid->matrix[coord.x][coord.y] == ETILETYPE::SPAWN))
		{
			// Set the tile as a occupied
			grid->matrix[coord.x][coord.y] = ETILETYPE::SHAPE;
			// Increase the shape size
			shape->SetSize(shape->GetSize() + 1);
		}

		// Place shape according to the type of shape
		if (totalSteps > 0)
		{
			switch (shape->GetType())
			{
				case EShapeType::DOWN: // | Shape

					// Check boundaries
					if ((coord.y + 1) < EGridDefinitions::YROWS)
					{
						coord.y = coord.y + 1;
						placeShape(grid, shape, coord, totalSteps - 1);
					}
				break;
				case EShapeType::ACROSS: // -- Shape

					 // Check boundaries
					if ((coord.x + 1) < EGridDefinitions::XCOLS)
					{
						coord.x = coord.x + 1;
						placeShape(grid, shape, coord, totalSteps - 1);
					}				

				break;
				case EShapeType::RIGHT_L:  // L Shape (Down-Right direction)

					// Down
					if (((coord.y + 1) < EGridDefinitions::YROWS) && (totalSteps > 1))
					{
						coord.y = coord.y + 1;
						placeShape(grid, shape, coord, totalSteps - 1);
					}

					// Rigth
					if (((coord.x + 1) < EGridDefinitions::XCOLS) && (totalSteps == 1))
					{
						coord.x = coord.x + 1;
						placeShape(grid, shape, coord, totalSteps - 1);
					}

				break;
				case EShapeType::LEFT_L:  // Mirror L Shape (Down-Left direction)

				// Down
				if (((coord.y + 1) < EGridDefinitions::YROWS) && (totalSteps > 1))
				{
					coord.y = coord.y + 1;
					placeShape(grid, shape, coord, totalSteps - 1);
				}

				// Left
				if (((coord.x - 1) >= 0) && (totalSteps == 1))
				{
					coord.x = coord.x - 1;
					placeShape(grid, shape, coord, totalSteps - 1);
				}

				break;

				case EShapeType::INVERT_RIGHT_L: // L Shape Upside down (Right - Down direction)

					 // Rigth
					if (((coord.x + 1) < EGridDefinitions::XCOLS) && (totalSteps > 1))
					{
						coord.x = coord.x + 1;
						placeShape(grid, shape, coord, totalSteps - 1);
					}

					// Down
					if (((coord.y + 1) < EGridDefinitions::YROWS) && (totalSteps == 1))
					{
						coord.y = coord.y + 1;
						placeShape(grid, shape, coord, totalSteps - 1);
					}

				break;
				case EShapeType::INVERT_LEFT_L: // Mirror L Shape Upside down (Left - Down direction)

				// Left
				if (((coord.x - 1) >= 0) && (totalSteps > 1))
				{
					coord.x = coord.x - 1;
					placeShape(grid, shape, coord, totalSteps - 1);
				}

				// Down
				if (((coord.y + 1) < EGridDefinitions::YROWS) && (totalSteps == 1))
				{
					coord.y = coord.y + 1;
					placeShape(grid, shape, coord, totalSteps - 1);
				}
				break;			
			}
		}
	}

	void PacmanMapGenerator::coverShape(Matrix2D<EGridDefinitions::XCOLS, EGridDefinitions::YROWS, int> * grid, const Shape shape, Coords coord, int totalSteps)
	{
		if (totalSteps >= 0)
		{
			// cover the shape with the firt cover, with 2
			cover(grid, coord, 1, ETILETYPE::OBSTACLE);

			switch (shape.GetType())
			{
				case EShapeType::DOWN:

					// Down
					if ((coord.y + 1) < EGridDefinitions::YROWS)
					{
						coord.y = coord.y + 1;
						coverShape(grid, shape, coord, totalSteps - 1);
					}

				break;

				case EShapeType::ACROSS: // -- Shape
					// Rigth
					if ((coord.x + 1) < EGridDefinitions::XCOLS)
					{
						coord.x = coord.x + 1;
						coverShape(grid, shape, coord, totalSteps - 1);
					}
				break;

				case EShapeType::RIGHT_L:  // L Shape (Down-Right direction)

										   // Down
					if (((coord.y + 1) < EGridDefinitions::YROWS) && (totalSteps > 1))
					{
						coord.y = coord.y + 1;
						coverShape(grid, shape, coord, totalSteps - 1);
					}

					// Rigth
					if (((coord.x + 1) < EGridDefinitions::XCOLS) && (totalSteps == 1))
					{
						coord.x = coord.x + 1;
						coverShape(grid, shape, coord, totalSteps - 1);
					}

					break;
				case EShapeType::LEFT_L:  // Mirror L Shape (Down-Left direction)

										  // Down
					if (((coord.y + 1) < EGridDefinitions::YROWS) && (totalSteps > 1))
					{
						coord.y = coord.y + 1;
						coverShape(grid, shape, coord, totalSteps - 1);
					}

					// Left
					if (((coord.x - 1) >= 0) && (totalSteps == 1))
					{
						coord.x = coord.x - 1;
						coverShape(grid, shape, coord, totalSteps - 1);
					}

					break;

				case EShapeType::INVERT_RIGHT_L: // L Shape Upside down (Right - Down direction)

												 // Rigth
					if (((coord.x + 1) < EGridDefinitions::XCOLS) && (totalSteps > 1))
					{
						coord.x = coord.x + 1;
						coverShape(grid, shape, coord, totalSteps - 1);
					}

					// Down
					if (((coord.y + 1) < EGridDefinitions::YROWS) && (totalSteps == 1))
					{
						coord.y = coord.y + 1;
						coverShape(grid, shape, coord, totalSteps - 1);
					}

					break;
				case EShapeType::INVERT_LEFT_L: // Mirror L Shape Upside down (Left - Down direction)

												// Left
					if (((coord.x - 1) >= 0) && (totalSteps > 1))
					{
						coord.x = coord.x - 1;
						coverShape(grid, shape, coord, totalSteps - 1);
					}

					// Down
					if (((coord.y + 1) < EGridDefinitions::YROWS) && (totalSteps == 1))
					{
						coord.y = coord.y + 1;
						coverShape(grid, shape, coord, totalSteps - 1);
					}
					break;

			default:
				break;
			}
		}
	}

	void PacmanMapGenerator::cover(Matrix2D<EGridDefinitions::XCOLS, EGridDefinitions::YROWS, int> * grid, Coords coord, int totalSteps, ETILETYPE tileType)
	{
		// Left
		if (coord.x - 1 >= 0)
		{
			coord.x = coord.x - 1;
		}

		// Up left
		if ((coord.x - 1 >= 0) && (coord.y - 1 >= 0))
		{
			coord.x = coord.x - 1;
			coord.y = coord.y - 1;
		}

		// Up
		if (coord.y - 1 >= 0)
		{
			coord.y = coord.y - 1;
		}

		// Up right
		if ((coord.x + 1 < EGridDefinitions::XCOLS) && (coord.y - 1 >= 0))
		{
			coord.x = coord.x + 1;
			coord.y = coord.y - 1;
		}

		// Right
		if (coord.x + 1 < EGridDefinitions::XCOLS)
		{
			coord.x = coord.x + 1;
		}

		// Down right
		if ((coord.y + 1 < EGridDefinitions::YROWS) && (coord.x + 1 < EGridDefinitions::XCOLS) )
		{

			coord.x = coord.x + 1;
			coord.y = coord.y + 1;

		}

		// Down
		if (coord.y + 1 < EGridDefinitions::YROWS)
		{
			coord.y = coord.y + 1;			
		}

		// Down left
		if ((coord.y + 1 < EGridDefinitions::YROWS) && (coord.x - 1 >= 0 ))
		{
			coord.x = coord.x - 1;
			coord.y = coord.y + 1;
		}

		if ((grid->matrix[coord.x][coord.y] == ETILETYPE::CLEAN) || (grid->matrix[coord.x][coord.y] == ETILETYPE::SPAWN))
		{
			grid->matrix[coord.x][coord.y] = tileType;
		}

		if (totalSteps > 0)
		{
			cover(grid, coord, 0, ETILETYPE::SPAWN);
		}
	}

	Coords PacmanMapGenerator::findNextSpawnLocation(Matrix2D<EGridDefinitions::XCOLS, EGridDefinitions::YROWS, int> * grid, Coords coord)
	{
		if (grid->matrix[coord.x][coord.y] == ETILETYPE::SPAWN)
		{
			return coord;
		}
		else
		{
			if ((coord.x + 1) < EGridDefinitions::XCOLS)
			{
				coord.x = coord.x + 1;
				return findNextSpawnLocation(grid, coord);
			}
			else
			{
				if ((coord.y + 1) < EGridDefinitions::YROWS)
				{
					coord.x = 0;
					coord.y = coord.y + 1;
					return findNextSpawnLocation(grid, coord);
				}
				else
				{
					Coords c(-1, -1);
					return c;
				}
			}
		}
	}
}