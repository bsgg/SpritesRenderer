#include "Animation.h"
#include "SpriteEffect.h"

Animation::Animation(int x, int y, int width, int height, int count,
	const Surface& sprite, float holdTime, Color chroma)
	:
	sprite(sprite),
	holdTime(holdTime),
	chroma(chroma)
{
	for (int i = 0; i < count; i++)
	{
		frames.emplace_back(x + i * width, x + (i + 1) * width, y, y + height);
	}
}

void Animation::Draw(const Vei2& pos, Graphics& gfx) const
{
	//gfx.DrawSprite(pos.x, pos.y, frames[iCurFrame], sprite, SpriteEffect::Ghost{ chroma });

	// Negative effect
	gfx.DrawSprite(pos.x, pos.y, frames[iCurFrame], sprite,
		// Capturing this, we can get the chroma from Animation clas.
		[this](Color cSrc, int xDest, int yDest, Graphics& gfx)
		{
			if (cSrc != chroma)
			{
				// Get the complement colour for each channel. If the channel is very low it will get a very high color 
				gfx.PutPixel(xDest, yDest,
					{255u - cSrc.GetR(), 255u - cSrc.GetG(), 255u - cSrc.GetB() }
				);
			}
		}
	);
}

void Animation::Draw(const Vei2& pos, Graphics& gfx, const RectI& clip) const
{
	gfx.DrawSprite(pos.x, pos.y, frames[iCurFrame], clip, sprite, SpriteEffect::Chroma{ chroma });
}

void Animation::DrawColor(const Vei2& pos, Graphics& gfx, Color c) const
{
	gfx.DrawSprite(pos.x, pos.y, frames[iCurFrame], sprite, SpriteEffect::Ghost{ chroma});
}

void Animation::Update(float dt)
{
	curFrameTime += dt;
	while (curFrameTime >= holdTime)
	{
		Advance();
		curFrameTime -= holdTime;
	}
}

void Animation::Advance()
{
	if (++iCurFrame >= frames.size())
	{
		iCurFrame = 0;
	}
}
