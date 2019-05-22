#ifndef GRAPHICS_H_
#define GRAPHICS_H_

//存储所有图像操作，其他sprite，animation类只存放数据

#include <SDL.h>
#include <iostream>
#include <map>
#include "units.h"

const units::Pixel screenWidth = 640;
const units::Pixel screenHeight = 480;

class Graphics
{
public:
	Graphics();
	~Graphics();
	SDL_Renderer* getRenderer() const { return renderer_; }
	SDL_Texture* loadFromFile(const std::string& path, bool black_is_transparent = false);
	void render(SDL_Texture* texture, SDL_Rect* srcRect, SDL_Rect* dstRect, 
		const SDL_RendererFlip flip = SDL_FLIP_NONE);
	void blitSurface(SDL_Surface* surface, SDL_Rect* srcRect, SDL_Rect* dstRect);
	void clear();
	void update();
	void draw();
	void present();
private:
	SDL_Window* window_;
	SDL_Renderer* renderer_;

	SDL_Surface* screenSurface_;

	std::map<std::string, SDL_Texture*> sprite_sheets_;
	//存储精灵图的位置，这样Sprite重复建立的时候首先读取这个，确认是否已经加载了
	//如果加载了，那Sprite存的是这个的指针，和需要渲染的位置
	std::map<std::string, SDL_Surface*> sprite_surfaces_;//存储精灵图Surface的位置
};


#endif // !GRAPHICS_H_