#pragma once

namespace MapGenerator
{
	enum EShapeType {
		NONE = -1,
		DOWN = 0,  // | Shape
		ACROSS, // -- Shape
		L, // L Shape (Down-Right direction)
		MIRROR_L, // Mirror L Shape (Down-Left direction)
		UPSIDEDOWN_L, // Upside down L  (Left - Down direction)
		UPSIDEDOWN_MIRROR_L // Upside down Mirror L Shape  (Right - Down direction)
		
	};

}