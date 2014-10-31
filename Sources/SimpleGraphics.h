#pragma once

namespace Kore {
	class Image;
}

void initGraphics();
void startFrame();
void endFrame();
void clear(float red, float green, float blue);
void setPixel(int x, int y, float red, float green, float blue);
Kore::Image* loadImage(const char* filename);
void destroyImage(Kore::Image* image);
void drawImage(Kore::Image* image, int x, int y);
void drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3);
const int width = 1024;
const int height = 768;