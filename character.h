#pragma once
#ifndef character_h
#define character_h

#include "baseFunc.h"
#include "baseObject.h"

#define G_Speed 0.8
#define Max_Fall_Speed 4
#define Player_Speed 8
class character :public baseObject
{
public:
	character();
	~character();

	enum WalkType
	{
		WalkRight = 0,
		WalkLeft = 1,
	};
	enum jump
	{
		WalkUp = 2,
		WalkDown = 3,
	};
	bool loadImg(std::string path, SDL_Renderer* screen);
	void show(SDL_Renderer* des);
	void inputAction(SDL_Event events, SDL_Renderer* screen);
	void set_clip();
	void do_player(Map& map_data);
	void check_map(Map& map_data);
	void setMap(const int map_x, const int map_y) { map_X = map_x; map_Y = map_y; };
	void entity_map(Map& map_data);
private:
	float x_val, y_val;//x: di chuyen trai phai; y: di chuyen len xuong;

	float x_pos, y_pos;// vi tri hien tai cua nhan vat;

	int frame_width, frame_height;
	SDL_Rect frame_clip[8];
	input input_type;//luu trang thai
	int frame;//no laf frame may
	int status;//luu trang thai, phai hay trai de lay dung anh;
	bool on_world;

	int map_X, map_Y;
};


#endif // !character_h
