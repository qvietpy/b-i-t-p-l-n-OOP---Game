#pragma once
#ifndef Game_Map_H
#define Game_Map_H
#include "baseFunc.h"
#include "baseObject.h"
#define maxTile 20
class tileMat :public baseObject
{
public:
	tileMat() { ; }
	~tileMat() { ; }
};
class gameMap
{
public:
	gameMap() { ; }
	~gameMap() { ; }
	void loadMap(std::string name);
	void loadTile(SDL_Renderer* screen);
	void drawMap(SDL_Renderer* screen);
	Map getMap() const { return game_Map; };
	void setMap(Map& map_data) { game_Map = map_data; };

private:
	Map game_Map;
	tileMat tile_Mat[maxTile];
};
#endif // !Game_Map_H
