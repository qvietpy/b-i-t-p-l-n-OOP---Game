#pragma once
#ifndef baseObject_h
#include "baseFunc.h"

class baseObject
{
public:
	baseObject();
	~baseObject();
	void setRect(const int& x, const int& y);
	SDL_Rect GetRect();
	SDL_Texture* GetObject() { return p_object; }

	virtual bool LoadImage(std::string path, SDL_Renderer* screen);// ham ao, ham ke thua co the su dung va khai bao them trong ham;
	void Render(SDL_Renderer* des, const SDL_Rect* clip = NULL);
	void Free();
protected:
	SDL_Texture* p_object;
	SDL_Rect rect;
};
#endif // !baseObject_h
