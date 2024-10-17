#pragma once
#ifndef baseFunc_h
#include <SDL.h>
#include <iostream>
#include <Windows.h>
#include <string>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <Windows.h>
static SDL_Window* g_window = NULL;
static SDL_Renderer* g_screen = NULL;
static SDL_Event g_event;
//screen
const int SCREEN_WIDTH = 840/*1280*/;
const int SCREEN_HEIGHT = /*640*/640;
const int SCREEN_BPP = 32;

const int FPS = 120;
const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;



#define Blank_Tile 0
#define TILE_SIZE 64
#define Max_Map_X 400
#define Max_Map_Y 10
typedef struct input
{
	int left, right, up, down, run, jump;
};

typedef struct Map
{
	int start_X, start_Y;
	int max_X, max_Y;
	int tile[Max_Map_Y][Max_Map_X];
	char* file_name;
};
#endif // !baseFunc_h
