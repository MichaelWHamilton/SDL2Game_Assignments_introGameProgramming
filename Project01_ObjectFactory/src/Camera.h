#pragma once
#include "SDL2/SDL.h"

class Camera {
public: 
	Camera(float x, float y, float scale, float rotation);
	
	void setCenter(float x, float y);
	void setScale(float s);
	void setRotation(float r);

	float getCenterX() const;
	float getCenterY() const;
	float getScale() const;
	float getRotation() const;

	SDL_Point transformPoint(float x, float y) const;
	SDL_Rect transformRect(const SDL_Rect& rect) const;
private:
	float m_centerX, m_centerY, m_scale, m_rotation;
};