/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"


Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd )
{

	/*for (int y = 0; y < surf.GetHeight(); y++)
	{
		for (int x = 0; x < surf.GetWidth(); x++)
		{
			surf.PutPixel(x, y, Color(
				(x - 25) * (x - 25) + (y - 25) * (y - 25),
				(x - 50) * (x - 50) + (y - 50) * (y - 50),
				(x - 75) * (x - 75) + (y - 75) * (y - 75)
			));
		}
	}*/
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{

	// process key messages while any remain
	while (!wnd.kbd.KeyIsEmpty())
	{
		const auto e = wnd.kbd.ReadKey();
		// only interested in space bar presses
		if (e.IsPress() && e.GetCode() == VK_SPACE)
		{
			link.ActivateEffect();
			hit.Play();
		}
	}

	Vec2 dir = { 0.0f,0.0f };
	if (wnd.kbd.KeyIsPressed(VK_UP))
	{
		dir.y -= 1.0f;
	}
	else if (wnd.kbd.KeyIsPressed(VK_DOWN))
	{
		dir.y += 1.0f;
	}
	else if (wnd.kbd.KeyIsPressed(VK_LEFT))
	{
		dir.x-= 1.0f;
	}
	else if (wnd.kbd.KeyIsPressed(VK_RIGHT))
	{
		dir.x += 1.0f;
	}


	link.SetDirection(dir);
	link.Update(ft.Mark());
}

void Game::ComposeFrame()
{
	//gfx.DrawSprite(200, 200, surf);
	//gfx.DrawSprite(0, 0, surf);

	/*int xPos = wnd.mouse.GetPosX();
	int yPos = wnd.mouse.GetPosY();
	RectI source(32, 64, 48, 96);
	RectI clip(100, 300, 100, 300);

	gfx.DrawSprite(xPos, yPos, source, gfx.GetScreenRect(), surf);*/

	//marleRight.Draw( { wnd.mouse.GetPosX(), wnd.mouse.GetPosY() }, gfx);
	link.Draw(gfx);

	font.DrawText("Hi Bea!\nHow are you?", wnd.mouse.GetPos(), Colors::Cyan, gfx);

}
