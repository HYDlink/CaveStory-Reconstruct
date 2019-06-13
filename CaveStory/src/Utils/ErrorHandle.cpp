#include "ErrorHandle.h"
#include <SDL_error.h>
#include <SDL_render.h>
#include <SDL_surface.h>

SDL_Surface* loadImg(std::string filename) {
	SDL_Surface* loadSurface = SDL_LoadBMP(filename.c_str());
	if (loadSurface == NULL) {
		printSDLError(std::cerr, "Unable to load image " + filename);
		return NULL;
	}
	return loadSurface;
}

std::ostream& printSDLError(std::ostream& out, std::string addon) {
	return out << addon << ". SDL_Error: "
		<< SDL_GetError() << std::endl;
}
