#include "Graphics.h"

using namespace std;

Graphics::Graphics(): Graphics(nullptr) {}

Graphics::Graphics(shared_ptr<Camera> cam): camera_(cam)
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
}


Graphics::~Graphics()
{
	SDL_DestroyWindow(window_);
	SDL_DestroyRenderer(renderer_);
}

SDL_Texture* Graphics::loadFromFile(const std::string& file_path, bool black_is_transparent) {
	if (sprite_sheets_.count(file_path) == 0) {
		SDL_Surface* loadSurface = SDL_LoadBMP(file_path.c_str());
		if (loadSurface == NULL) {
			std::cerr << "Unable to load image "
				<< file_path << ". SDL_Error: "
				<< SDL_GetError() << std::endl;
			return NULL;
		}
		//SDL_SetColorKey(loadSurface, 1, SDL_MapRGB(loadSurface->format, 0, 255, 255));
		//设置加载图片的区域
	//	if (srcPos_ == SDL_Rect() || SDL_SetClipRect(loadSurface, &srcPos_) == SDL_FALSE)
	//		srcPos_ = loadSurface->clip_rect;

		if (black_is_transparent) {
			const Uint32 black_color = SDL_MapRGB(loadSurface->format, 0, 0, 0);
			SDL_SetColorKey(loadSurface, SDL_TRUE, black_color);
		}
		sprite_sheets_[file_path] = SDL_CreateTextureFromSurface(renderer_, loadSurface);
		if (sprite_sheets_[file_path] == NULL)
			std::cerr << "Unable to creat texture from "
			<< file_path << ". SDL_Error: "
			<< SDL_GetError() << std::endl;
		sprite_surfaces_[file_path] = loadSurface;
		//SDL_FreeSurface(loadSurface);
	}
	return sprite_sheets_[file_path];
}

void Graphics::setCamera(shared_ptr<Camera> cam) {
	camera_ = cam;
}

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
	bool hasDstRect = true;
	SDL_Rect dstTmp = SDL_Rect();
	if (!dstRect) {
		hasDstRect = false;
	}
	else dstTmp = *dstRect;
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
	if (!camIndep && camera_ != nullptr) {
		dstTmp.x -= camera_->currentPos().x;
		dstTmp.y -= camera_->currentPos().y;
	}
	if (flip == SDL_FLIP_NONE) {
		SDL_assert (SDL_RenderCopy(renderer_, texture, srcRect, &dstTmp) != -1);
			//cerr << "SDL_RenderCopy failed: " << SDL_GetError() << endl;
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
	//SDL_SetRenderDrawColor(renderer_, 0, 255, 0, 0);
	SDL_RenderClear(renderer_);
}

void Graphics::update() {
}

void Graphics::draw() {
	SDL_Rect srcRect{ 0, 0, 32, 32 };
	SDL_Rect dstRect{ 100, 100, 32, 32 };
	//blitSurface(sprite_surfaces_["res/MyChar.bmp"], &srcRect, &dstRect);
}

void Graphics::present() {
	//SDL_UpdateWindowSurface(window_);
	SDL_RenderPresent(renderer_);
}

Rectangle Graphics::screenRect() const {
	return Rectangle(0, 0, screenWidth, screenHeight);
}
