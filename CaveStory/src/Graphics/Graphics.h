#ifndef GRAPHICS_H_
#define GRAPHICS_H_

//�洢����ͼ�����������sprite��animation��ֻ�������

#include <SDL.h>
#include <iostream>
#include <map>
#include <memory>
#include "../Camera.h"
#include "../Utils/units.h"

const units::Pixel screenWidth = 640;
const units::Pixel screenHeight = 480;

class Camera;
class Graphics
{
public:
	Graphics();
	Graphics(std::shared_ptr<Camera> cam);
	~Graphics();
	SDL_Renderer* getRenderer() const { return renderer_; }
	SDL_Texture* loadFromFile(const std::string& path, bool black_is_transparent = false);
	void setCamera(std::shared_ptr<Camera>);
	void setClearColor(SDL_Color& color);
	void setClearColor(SDL_Color&& color);
	void render(SDL_Texture* texture, const SDL_Rect* srcRect, const SDL_Rect* dstRect,
		bool camIndep = false, const SDL_RendererFlip flip = SDL_FLIP_NONE) const;
	void blitSurface(SDL_Surface* surface, SDL_Rect* srcRect, SDL_Rect* dstRect);
	void clear();
	void update();
	void present();

	Rectangle screenRect() const;
private:
	SDL_Window* window_;
	SDL_Renderer* renderer_;

	SDL_Color clearColor_;
	SDL_Surface* screenSurface_;
	std::shared_ptr<Camera> camera_;
	std::map<std::string, SDL_Texture*> sprite_sheets_;
	//�洢����ͼ��λ�ã�����Sprite�ظ�������ʱ�����ȶ�ȡ�����ȷ���Ƿ��Ѿ�������
	//��������ˣ���Sprite����������ָ�룬����Ҫ��Ⱦ��λ��
	std::map<std::string, SDL_Surface*> sprite_surfaces_;//�洢����ͼSurface��λ��
};


#endif // !GRAPHICS_H_