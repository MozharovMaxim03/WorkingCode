#include "utils.hpp"

void (*ptr_empty_func)(void) = &empty_func;

DataManager<Image> images(&LoadImage, &UnloadImage);
DataManager<Texture> textures(&LoadTexture, &UnloadTexture);
DataManager<Sound> sounds(&LoadSound, &UnloadSound);

vector2& vector2::rotateto(float angle) {
	float l = len();
	x = l * cos(angle);
	y = l * sin(angle);
	return *this;
}

vector2& vector2::rotateto(double angle)
{
	float l = len();
	x = l * cos(angle);
	y = l * sin(angle);
	return *this;
}