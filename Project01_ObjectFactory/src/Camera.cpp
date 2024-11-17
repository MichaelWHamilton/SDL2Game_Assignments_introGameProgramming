#include "Camera.h"

Camera::Camera(float x = 0.0f, float y = 0.0f, float scale = 1.0f, float rotation = 0.0f)
	:m_centerX(x), m_centerY(y), m_scale(scale), m_rotation(rotation) {}

void Camera::setCenter(float x, float y) { m_centerX = x; m_centerY = y; }
void Camera::setScale(float s) { m_scale = s; }
void Camera::setRotation(float r) { m_rotation = r; }

float Camera::getCenterX() const { return m_centerX; }
float Camera::getCenterY() const { return m_centerY; }
float Camera::getScale() const { return m_scale; }
float Camera::getRotation() const { return m_rotation; }

SDL_Point Camera::transformPoint(float x, float y) const {
	SDL_Point point;
	point.x = static_cast<int>((x - m_centerX) * m_scale);
	point.y = static_cast<int>((y - m_centerY) * m_scale);
	return point;
}
SDL_Rect Camera::transformRect(const SDL_Rect& rect) const {
	SDL_Rect transformed;
	/*transformed.x = static_cast<int>((rect.x - centerX) * scale);
	transformed.y = static_cast<int>((rect.y - centerY) * scale);
	transformed.w = static_cast<int>(rect.w * scale);
	transformed.h = static_cast<int>(rect.h * scale);*/
	int h = 600;
	int w = 800;
	// Translate the position to keep player at the center of the screen
	transformed.x = static_cast<int>((rect.x - m_centerX) * m_scale + w / 2);
	transformed.y = static_cast<int>((rect.y - m_centerY) * m_scale + h / 2);
	// Scale the width and height
	transformed.w = static_cast<int>(rect.w * m_scale);
	transformed.h = static_cast<int>(rect.h * m_scale);

	return transformed;
}


