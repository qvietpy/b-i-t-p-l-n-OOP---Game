#include "character.h"

character::character()
{
	frame = 0;
	x_pos = 0;
	y_pos = 0;
	x_val = 0;
	y_val = 0;
	frame_width = 0;
	frame_height = 0;
	input_type.left = 0;
	input_type.right = 0;
	input_type.jump = 0;
	input_type.down = 0;
	input_type.up = 0;
	status = -1;
	on_world = false;
	map_X = 0;
	map_Y = 0;
}
character::~character()
{

}

bool character::loadImg(std::string path, SDL_Renderer* screen)
{
	bool ret = baseObject::LoadImage(path, screen);
	if (ret == true)
	{
		frame_width = rect.w / 8;
		frame_height = rect.h;
	}
	return ret;
}

void character::set_clip()
{
	if (frame_width > 0 && frame_height > 0)
	{
		for (int i = 0; i < 8; ++i)
		{
			frame_clip[i].x = i * frame_width;
			frame_clip[i].y = 0;
			frame_clip[i].w = frame_width;
			frame_clip[i].h = frame_height;
		}
	}
}
void character::show(SDL_Renderer* des)
{
	if (status == WalkLeft)
		loadImg("image/knight_left.png", des);
	else if (status == WalkRight)
		loadImg("image/knight_right.png", des);
	else if (status == WalkDown)
		loadImg("image/knight_right.png", des);
	else if (status == WalkUp)
		loadImg("image/knight_right.png", des);
	//if (status == WalkLeft)
	//	loadImg("image/player_left.png", des);
	//else if (status == WalkRight)
	//	loadImg("image/player_right.png", des);
	//else if (status == WalkDown)
	//	loadImg("image/jum_right.png", des);
	//else if (status == WalkUp)
	//	loadImg("image/jum_left.png", des);
	if (input_type.left == 1 || input_type.right == 1 || input_type.up == 1 || input_type.down == 1)
	{
		frame++;
	}
	else
	{
		frame = 0;
	}
	if (frame >= 8)
	{
		frame = 0;
	}
	rect.x = x_pos - map_X;
	rect.y = y_pos - map_Y;
	SDL_Rect* current_clip = &frame_clip[frame];//lay frame hien tai;
	SDL_Rect renderQuad = { rect.x, rect.y, frame_width, frame_height };//tao vi tri kich thuoc
	SDL_RenderCopy(des, p_object, current_clip, &renderQuad);//hien thi len man hinh;
}
void character::inputAction(SDL_Event events, SDL_Renderer* screen)
{
	if (events.type == SDL_KEYDOWN)
	{
		switch (events.key.keysym.sym)
		{
		case SDLK_RIGHT:
		{
			status = WalkRight;
			input_type.right = 1;
			input_type.left = 0;
			break;
		}
		case SDLK_LEFT:
		{
			status = WalkLeft;
			input_type.left = 1;
			input_type.right = 0;
			break;
		}
		case SDLK_UP:
		{
			status = WalkUp;
			input_type.up = 1;
			input_type.down = 0;
			break;
		}
		case SDLK_DOWN:
		{
			status = WalkDown;
			input_type.down = 1;
			input_type.up = 0;
			break;
		}
		//default:
		//	break;
		}
	}
	else if (events.type == SDL_KEYUP)
	{
		switch (events.key.keysym.sym)
		{
		case SDLK_RIGHT:
		{
			//status = WalkRight;
			input_type.right = 0;
			break;
		}
		case SDLK_LEFT:
		{
			//status = WalkLeft;
			input_type.left = 0;
			break;
		}
		case SDLK_DOWN:
		{
			//status = WalkLeft;
			input_type.down = 0;
			break;
		}
		case SDLK_UP:
		{
			//status = WalkLeft;
			input_type.up = 0;
			break;
		}
		//default:
		//	break;
		}
	}
}

void character::do_player(Map& map_data)
{
	x_val = 0;
	y_val += 0.8;
	if (y_val >= Max_Fall_Speed)
		y_val = Max_Fall_Speed;

	if (input_type.left == 1)
		x_val -= Player_Speed;
	if (input_type.right == 1)
		x_val += Player_Speed;
	if (input_type.down == 1)
		y_val += Player_Speed;
	if (input_type.up == 1)
		y_val -= Player_Speed;
	check_map(map_data);
	entity_map(map_data);
}

void character::entity_map(Map& map_data)
{
	map_data.start_X = x_pos - (SCREEN_WIDTH / 2);
	if (map_data.start_X < 0)//lui het map thi ko keo map theo nx
	{
		map_data.start_X = 0;
	}
	else if (map_data.start_X + SCREEN_WIDTH >= map_data.max_X)//tien het map thi ko keo map theo nx
	{
		map_data.start_X = map_data.max_X - SCREEN_WIDTH;
	}
	map_data.start_Y = y_pos - (SCREEN_HEIGHT / 2);
	if (map_data.start_Y < 0)
	{
		map_data.start_Y = 0;
	}
	else if (map_data.start_Y + SCREEN_HEIGHT >= map_data.max_Y)
	{
		map_data.start_Y = map_data.max_Y - SCREEN_HEIGHT;
	}
}

void character::check_map(Map& map_data)
{
	int x1 = 0, x2 = 0;
	int y1 = 0, y2 = 0;
	//check ngang
	int height_min = frame_height < TILE_SIZE ? frame_height : TILE_SIZE;
	x1 = (x_pos + x_val) / TILE_SIZE;//x1 o o^ thu may;
	x2 = (x_pos + x_val + frame_width - 1) / TILE_SIZE;

	y1 = (y_pos) / TILE_SIZE;
	y2 = (y_pos + height_min - 1) / TILE_SIZE;

	// check va cham;
	if (x1 >= 0 && x2 <= Max_Map_X && y1 >= 0 && y2 <= Max_Map_Y)
	{
		if (x_val > 0 )//nhan vat dag di chuyen sang phai
		{
			if (map_data.tile[y1][x2] != Blank_Tile || map_data.tile[y2][x2] != Blank_Tile)
			{
				x_pos = x2 * TILE_SIZE;//cham thi gan x_pos tai vi tri do ko cho tang nx;
				x_pos -= frame_width + 1;
				x_val = 0;
			}
		}
		if (x_val < 0)
		{
			if (map_data.tile[y1][x1] != Blank_Tile || map_data.tile[y2][x1] != Blank_Tile)
			{
				x_pos = (x1 + 1) * TILE_SIZE;
				x_val = 0;
			}
		}
	}

	// check doc
	int witdh_min = frame_width < TILE_SIZE ? frame_width : TILE_SIZE;
	x1 = x_pos / TILE_SIZE;
	x2 = (x_pos + witdh_min) / TILE_SIZE;
	y1 = (y_pos + y_val) / TILE_SIZE;
	y2 = (y_pos + y_val + frame_height - 1) / TILE_SIZE;
	if (x1 >= 0 && x2 <= Max_Map_X && y1 >= 0 && y2 <= Max_Map_Y)
	{
		if (y_val > 0)
		{
			if (map_data.tile[y2][x1] != Blank_Tile || map_data.tile[y2][x2] != Blank_Tile)
			{
				y_pos = y2 * TILE_SIZE;
				y_pos -= frame_height + 1;
				y_val = 0;
				on_world = true;
			}
		}
		if (y_val < 0)
		{
			if (map_data.tile[y1][x1] != Blank_Tile || map_data.tile[y1][x2] != Blank_Tile)
			{
				y_pos = (y1 + 1) * TILE_SIZE;
				y_val = 0;
			}
		}
	}

	x_pos += x_val;
	y_pos += y_val;
	if (x_pos < 0)//lui het ban do thi ko dc lui nx
		x_pos = 0;
	else if (x_pos + frame_width > map_data.max_X)
		x_pos = map_data.max_X - frame_width - 1;
	if (y_pos < 0)
		y_pos = 0;
	else if (y_pos + frame_height > map_data.max_Y)
		y_pos = map_data.max_Y - frame_height - 1;
}