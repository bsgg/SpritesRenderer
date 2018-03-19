#pragma once

namespace MapGenerator
{
	enum EShapeType {
		NONE = -1,
		DOWN = 0,  // | Shape
		ACROSS, // -- Shape
		RIGHT_L, // L Shape (Down-Right direction)
		LEFT_L, // Mirror L Shape (Down-Left direction)
		INVERT_RIGHT_L, // L Shape Upside down (Right - Down direction)
		INVERT_LEFT_L // Mirror L Shape Upside down (Left - Down direction)
	};

}