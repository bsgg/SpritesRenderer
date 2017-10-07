#pragma once

#include "Colors.h"
#include "Graphics.h"

namespace SpriteEffect
{
	class Chroma
	{
	public:
		Chroma(Color c)
			:
			chroma(c)
		{}

		void operator()(Color cSrc, int xDest, int yDest, Graphics& gfx) const
		{
			if (cSrc != chroma)
			{
				gfx.PutPixel(xDest, yDest, cSrc);
			}
		}

	private:
		Color chroma;
	};


	class Substitution
	{
	public:
		Substitution(Color c, Color s)
			:
			chroma(c),
			sub(s)
		{}

		void operator()(Color cSrc, int xDest, int yDest, Graphics& gfx) const
		{
			if (cSrc != chroma)
			{
				gfx.PutPixel(xDest, yDest, sub);
			}
		}

	private:
		Color chroma = Colors::Magenta;
		Color sub;
	};


	class Copy
	{
	public:
		
		void operator()(Color cSrc, int xDest, int yDest, Graphics& gfx) const
		{
			gfx.PutPixel(xDest, yDest, cSrc);
			
		}

	};

	class Ghost
	{
	public:
		Ghost(Color c)
			:
			chroma(c)
		{}

		void operator()(Color cSrc, int xDest, int yDest, Graphics& gfx) const
		{
			if (cSrc != chroma)
			{
				const Color dest = gfx.GetPixel(xDest, yDest);
				const Color blend = {
					unsigned char ((cSrc.GetR() + dest.GetR()) / 2),
					unsigned char ((cSrc.GetG() + dest.GetG()) / 2),
					unsigned char ((cSrc.GetB() + dest.GetB()) / 2),
				};

				gfx.PutPixel(xDest, yDest, blend);
			}
		}

	private:
		Color chroma = Colors::Magenta;

	};
}
