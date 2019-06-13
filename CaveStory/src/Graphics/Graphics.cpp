#include "Graphics.h"
#include "../Utils/Locator.h"
#include "../Utils/ErrorHandle.h"

using namespace std;

Graphics::Graphics(): Graphics(nullptr) {}

Graphics::Graphics(shared_ptr<Camera> cam): camera_(cam), clearColor_{0, 0, 0, 0}
{
	window_ = SDL_CreateWindow("CaveStory Reconstruct",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		screenWidth, screenHeight, SDL_WINDOW_SHOWN);
	if (window_ == NULL)
		cerr << "SDL_CreateWindow Failed: " << SDL_GetError() << endl;
	screenSurface_ = SDL_GetWindowSurface(window_);
	renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer_ == NULL)
		cerr << "SDL_CreateRenderer Failed: " << SDL_GetError() << endl;
	SDL_SetRenderDrawColor(renderer_, 255, 255, 255, 255);
	Locator<Graphics>::provide(this);
}


Graphics::~Graphics()
{
	SDL_DestroyWindow(window_);
	SDL_DestroyRenderer(renderer_);
}

//加载一整个贴图，不在这个阶段进行切割等等
SDL_Texture* Graphics::loadFromFile(const std::string& filename, TransparentColor color) {
	if (sprite_sheets_.count(filename) == 0) {
		SDL_Surface* loadSurface = loadImg(filename);

		SetColorKey(color, loadSurface);

		sprite_sheets_[filename] = SDL_CreateTextureFromSurface(renderer_, loadSurface);
		if (sprite_sheets_[filename] == NULL)
			printSDLError(cerr, "Unable to creat texture from " + filename);
		SDL_FreeSurface(loadSurface);
	}
	return sprite_sheets_[filename];
}

SDL_Texture* Graphics::loadMapTexture(const std::string& filename, units::Tile w,
	units::Tile h, units::Pixel size, 
	std::function<void(units::Tile i, units::Tile j, SDL_Rect& srcPos)> setSrcPos) {
	if (mapCache_.first != filename) {

		SDL_Surface* loadSurface = loadImg(filename);
		SDL_Surface* mapSurface =
			SDL_CreateRGBSurface(0,
				w * size, h * size,
				32, 0, 0, 0, 0);
		if (mapSurface == NULL) {
			printSDLError(cerr, "Unable to load image " + filename);
			return NULL;
		}
		SetColorKey(TransparentColor::BLACK, loadSurface);
		SetColorKey(TransparentColor::BLACK, mapSurface);

		//加载地图
		SDL_Rect srcRect{ 0, 0, size, size };
		SDL_Rect dstRect{};
		for (size_t i = 0; i < h; i++) {
			for (size_t j = 0; j < w; j++) {
				//花了好长一段时间我才反映过来，最大的不同只有设置贴图的起始渲染位置
				setSrcPos(i, j, srcRect);
				dstRect.x = j * size;
				dstRect.y = i * size;
				if (SDL_BlitSurface(loadSurface, &srcRect, mapSurface, &dstRect) < 0) {
					printSDLError(cerr, "Unable to Blit Tile To Map " + filename);
					return NULL;
				}
			}
		}

		SDL_Texture* mapTexture =
			SDL_CreateTextureFromSurface(renderer_, mapSurface);
		if (mapTexture == NULL) {
			printSDLError(cerr, "Unable to creat texture from " + filename);
			return NULL;
		}
		SDL_FreeSurface(loadSurface);
		SDL_FreeSurface(mapSurface);

		mapCache_.first = filename;
		mapCache_.second = mapTexture;
	}
	return mapCache_.second;
}

void Graphics::SetColorKey(const TransparentColor& color, SDL_Surface* loadSurface) {
	Uint32 transparentColor = 0;
	switch (color) {
	case TransparentColor::NONE:
		return;
	case TransparentColor::BLACK:
		transparentColor = SDL_MapRGB(loadSurface->format, 0, 0, 0);
		break;
	case TransparentColor::WHITE:
		transparentColor = SDL_MapRGB(loadSurface->format, 255, 255, 255);
		break;
	}
	SDL_SetColorKey(loadSurface, SDL_TRUE, transparentColor);
}

void Graphics::setCamera(shared_ptr<Camera> cam) {
	camera_ = cam;
}

void Graphics::setClearColor(SDL_Color& color) {
	clearColor_ = color;
}

void Graphics::setClearColor(SDL_Color&& color) {
	clearColor_ = color;
}

//TODO 设置旋转等等
/*
*  \param texture   A pointer to the texture to load
*  \param srcrect   A pointer to the source rectangle, or NULL for the entire
*                   texture.
*  \param dstrect   A pointer to the destination rectangle, just need position
*                   or NULL for zero position
#  \param camIndep  相机无关，若想要所渲染的物体不因相机位置而改变，则置为true
*/
void Graphics::render(SDL_Texture* texture, const SDL_Rect* srcRect, const SDL_Rect* dstRect,
	bool camIndep, const SDL_RendererFlip flip) const
{
	//设置渲染目标位置
	SDL_Rect dstTmp = SDL_Rect();
	if(dstRect) dstTmp = *dstRect;
	if (srcRect) {
		dstTmp.w = srcRect->w;
		dstTmp.h = srcRect->h;
	}
	else {
		uint32_t format;
		int access, w, h;
		SDL_QueryTexture(texture, &format, &access, &w, &h);
		dstTmp.w = w;
		dstTmp.h = h;
	}

	//设置相机渲染空间
	if (!camIndep && camera_ != nullptr) {
		dstTmp.x -= camera_->currentPos().x;
		dstTmp.y -= camera_->currentPos().y;
	}

	if (flip == SDL_FLIP_NONE) {
		SDL_assert (SDL_RenderCopy(renderer_, texture, srcRect, &dstTmp) != -1);
	}
	else {
		SDL_assert(SDL_RenderCopyEx(renderer_, texture, srcRect, &dstTmp, NULL, NULL, flip) != -1);
	}
}

void Graphics::blitSurface(SDL_Surface* surface, SDL_Rect* srcRect, SDL_Rect* dstRect) {
	if (srcRect) {
		dstRect->w = srcRect->w;
		dstRect->h = srcRect->h;
	}
	if(SDL_BlitSurface(surface, srcRect, screenSurface_, dstRect) < 0)
		cerr << "SDL_BlitSurface Error: " << SDL_GetError() << endl;
}

void Graphics::clear() {
	SDL_SetRenderDrawColor(renderer_, clearColor_.r, clearColor_.g, clearColor_.b, clearColor_.a);
	SDL_RenderClear(renderer_);
}

void Graphics::update() {
}

void Graphics::present() {
	SDL_RenderPresent(renderer_);
}

Rectangle Graphics::screenRect() const {
	return Rectangle(0, 0, screenWidth, screenHeight);
}
