#pragma once
#ifndef __DETENATOR__
#define __DETENATOR__

#include "DisplayObject.h"
#include "TextureManager.h"
#include "SDL.h"
#include "SDL_image.h"

class Detenator final : public DisplayObject
{
public:
	Detenator();
	~Detenator();

	// Inherited via GameObject
	void draw() override;
	void update() override;
	void clean() override;

	void turn();
	void move();
	void reset();
	// getters
	glm::vec2 getCurrentDirection() const;

	// setters
	void setCurrentDirection(glm::vec2 newDirection);
	void m_checkBounds();
	bool keepTurning = true;
	bool m_isGravityEnabled = false;
private:
	// steering behaviours
	float m_turnRate;
	float m_currentHeading;
	glm::vec2 m_currentDirection;
};


#endif /* defined (__DETENATOR__) */

