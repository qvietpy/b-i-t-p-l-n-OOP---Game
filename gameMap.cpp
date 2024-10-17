#include <iostream>
#include "gameMap.h"
//gameMap::gameMap()
//{
//
//}
void gameMap::loadMap(std::string name)
{
	FILE* fp = NULL;
	fopen_s(&fp, name.c_str(), "rb");
	if (fp == NULL)
		return;
	game_Map.max_X = 0;
	game_Map.max_Y = 0;
	for (int i = 0; i < Max_Map_Y; i++)
	{
		for (int j = 0; j < Max_Map_X; j++)
		{
			fscanf_s(fp, "%d", &game_Map.tile[i][j]);
			int val = game_Map.tile[i][j];
			if (val > 0)
			{
				if (j > game_Map.max_X)
				{
					game_Map.max_X = j;
				}
				if (j > game_Map.max_Y)
				{
					game_Map.max_Y = i;
				}
			}
		}
	}
	game_Map.max_X = (game_Map.max_X + 1) * TILE_SIZE;
	game_Map.max_Y = (game_Map.max_Y + 1) * TILE_SIZE;

	game_Map.start_X = 0;
	game_Map.start_Y = 0;

	//game_Map.file_name = name;
	fclose(fp);
}

void gameMap::loadTile(SDL_Renderer* screen)
{
	char file_img[30];
	FILE* fp = NULL;

	for (int i = 0; i < maxTile; i++)
	{
		sprintf_s(file_img, "map/%d.png", i);//truy cap vao forder map mo cac hinh anh co duoi .png theo chi so i;
		fopen_s(&fp, file_img, "rb");
		if (fp == NULL)
			continue;
		fclose(fp);
		tile_Mat[i].LoadImage(file_img, screen);
	}
}
void gameMap::drawMap(SDL_Renderer* screen)
{
	int x1 = 0, x2 = 0;//ben trai va phai cua man hinh
	int y1 = 0, y2 = 0;//ben tren va duoi cua man hinh
	int map_x = 0, map_y = 0;

	map_x = game_Map.start_X / TILE_SIZE;
	x1 = (game_Map.start_X % TILE_SIZE) * - 1;/* * -1 de fill dc het khi x nam o nhung vi tri khong nguyen; la x1 se lui ve vi tri
												nguyen trc do*/
	x2 = x1 + SCREEN_WIDTH + (x1 == 0 ? 0 : TILE_SIZE);/* + (x1 == 0 ? 0 : TILE_SIZE) de fill dc het khi x1 nam o nhung vi tri khong nguyen;
														vi x1 lui ve 1 khoang len x2 cung lui ve 1 khoang neu ko + (x1 == 0 ? 0 : TILE_SIZE) */
	
	map_y = game_Map.start_Y / TILE_SIZE;
	y1 = (game_Map.max_Y % TILE_SIZE) * -1;//nhu x1;
	y2 = y1 + SCREEN_HEIGHT + (y1 == 0 ? 0 : TILE_SIZE);//nhu x2;

	for (int i = 0; i < y2; i += TILE_SIZE)
	{
		map_x = game_Map.start_X / TILE_SIZE;
		for (int j = 0; j < x2; j += TILE_SIZE)
		{
			int val = game_Map.tile[map_y][map_x];
			if (val > 0)
			{
				tile_Mat[val].setRect(j, i);//bat dau fill tung o 1;
				tile_Mat[val].Render(screen);
			}
			map_x++;
		}
		map_y++;
	}
}