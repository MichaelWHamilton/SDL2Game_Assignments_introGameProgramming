#pragma once
#include "SDL2/SDL.h"

class Camera {
public: 
	Camera(float x = 0.0f, float y = 0.0f, float scale = 1.0f, float rotation = 0.0f)
	:centerX(x), centerY(y), scale(scale), rotation(rotation) {}
	
	void setCenter(float x, float y) { centerX = x; centerY = y; }
	void setScale(float s) { scale = s; }
	void setRotation(float r) { rotation = r; }

	float getCenterX() const { return centerX; }
	float getCenterY() const { return centerY; }
	float getScale() const { return scale; }
	float getRotation() const { return rotation; }

	SDL_Point transformPoint(float x, float y) const {
		SDL_Point point;
		point.x = static_cast<int>((x - centerX) * scale);
		point.y = static_cast<int>((y - centerY) * scale);
		return point;
	}
	SDL_Rect transformRect(const SDL_Rect& rect) const {
		SDL_Rect transformed;
		/*transformed.x = static_cast<int>((rect.x - centerX) * scale);
		transformed.y = static_cast<int>((rect.y - centerY) * scale);
		transformed.w = static_cast<int>(rect.w * scale);
		transformed.h = static_cast<int>(rect.h * scale);*/
		int h = 600;
		int w = 800;
		// Translate the position to keep player at the center of the screen
		transformed.x = static_cast<int>((rect.x - centerX) * scale + w / 2);
		transformed.y = static_cast<int>((rect.y - centerY) * scale + h / 2);
		// Scale the width and height
		transformed.w = static_cast<int>(rect.w * scale);
		transformed.h = static_cast<int>(rect.h * scale);

		return transformed;
	}
private:
	float centerX, centerY, scale, rotation;
};