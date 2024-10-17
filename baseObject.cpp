#include "baseObject.h"
void baseObject::setRect(const int& x, const int& y)
{
	rect.x = x;
	rect.y = y;
}
SDL_Rect baseObject::GetRect()
{
	return rect;
}
baseObject::baseObject()
{
	p_object = NULL;
	rect.x = 0;
	rect.y = 0;
	rect.w = 0;
	rect.h = 0;
}
baseObject::~baseObject()
{
	Free();
}
bool baseObject::LoadImage(std::string path, SDL_Renderer* screen)
{
	SDL_Texture* new_Texture = NULL;
	SDL_Surface* load_Surface = IMG_Load(path.c_str());
	if (load_Surface != NULL)
	{
		SDL_SetColorKey(load_Surface, SDL_TRUE, SDL_MapRGB(load_Surface->format, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B));
		new_Texture = SDL_CreateTextureFromSurface(screen, load_Surface);
		//if (new_Texture != NULL)
		//{
		//	rect.x = load_Surface->w;
		//	rect.y = load_Surface->h;
		//}
		if (new_Texture != NULL)
		{
			rect.w = load_Surface->w;  // ?úng
			rect.h = load_Surface->h;  // ?úng
		}

		SDL_FreeSurface(load_Surface);
	}
	p_object = new_Texture;

	return p_object != NULL;
}
void baseObject::Render(SDL_Renderer* des, const SDL_Rect* clip)
{
	SDL_Rect renderquad = { rect.x, rect.y, rect.w, rect.h };
	SDL_RenderCopy(des, p_object, clip, &renderquad);
}
void baseObject::Free()
{
	if (p_object != NULL)
	{
		SDL_DestroyTexture(p_object);
		p_object = NULL;
		rect.w = 0;
		rect.h = 0;
	}
}