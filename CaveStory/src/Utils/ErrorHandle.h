#pragma once
#include <iostream>
#include <string>


struct SDL_Texture;
struct SDL_Surface;

SDL_Surface* loadImg(std::string filename);
std::ostream& printSDLError(std::ostream& out, std::string addon);