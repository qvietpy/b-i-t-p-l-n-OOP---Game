#include <iostream>
#include "baseFunc.h"
#include "baseObject.h"
#include "gameMap.h"
#include "character.h"
#include "Timer.h"
baseObject g_backGround;
bool InitData()
{
	bool success = true;
	int ret = SDL_Init(SDL_INIT_VIDEO);
	if (ret < 0)
		return false;
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
	g_window = SDL_CreateWindow("Game Cpp sdl2.0",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		SDL_WINDOW_SHOWN);
	if (g_window == NULL)
	{
		success = false;
	}
	else
	{
		g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
		if (g_window == NULL)
			success = false;
		//if (g_screen == NULL)
		//	success = false;

		else
		{
			SDL_SetRenderDrawColor(g_screen, 255, 255, 255, 255);
			int imgFlags = IMG_INIT_PNG;
			if ((IMG_Init(imgFlags) & imgFlags) != imgFlags)
			{
				success = false;
			}
		}
	}
	return success;
}
bool loadBackGround()
{
	bool ret = g_backGround.LoadImage("image/bg1.png", g_screen);
	if (ret == false)
		return false;
	return true;
}
void close()
{
	g_backGround.Free();
	SDL_DestroyRenderer(g_screen);
	g_screen = NULL;
	SDL_DestroyWindow(g_window);
	g_window = NULL;
	IMG_Quit();
	SDL_Quit();

}
int main(int argc, char* argv[])
{
	Timer FPS_timer;
	if (InitData() == false)
		return -1;
	if (loadBackGround() == false)
		return -1;

	gameMap game_map;
	game_map.loadMap("map/map01.dat");
	game_map.loadTile(g_screen);
	character p_player;
	p_player.loadImg("image/knight_right.png", g_screen);
	//p_player.loadImg("image/player_right.png", g_screen);
	p_player.set_clip();
	bool is_quit = false;
	while (!is_quit)
	{
		FPS_timer.start();
		while (SDL_PollEvent(&g_event) != 0)
		{
			if (g_event.type == SDL_QUIT)
			{
				is_quit = true;
			}
			p_player.inputAction(g_event, g_screen);
		}
		SDL_SetRenderDrawColor(g_screen, 255, 255, 255, 255);
		SDL_RenderClear(g_screen);

		g_backGround.Render(g_screen, NULL);
		//game_map.drawMap(g_screen);
		Map map_data = game_map.getMap();

		p_player.setMap(map_data.start_X, map_data.start_Y);
		p_player.do_player(map_data);
		p_player.show(g_screen);

		game_map.setMap(map_data);
		game_map.drawMap(g_screen);

		SDL_RenderPresent(g_screen);
		int real_time = FPS_timer.get_tick();
		int time_one_frame = 1000 / FPS;//ms
		if (real_time < time_one_frame)
		{
			int delay = time_one_frame - real_time;
			if (delay >= 0)
				SDL_Delay(delay);
		}
	}
	close();
	return 0;
}