#pragma once
#ifndef __ENEMY__
#define __ENEMY__

#include "Sprite.h"
#include "SDL.h"
#include "SDL_image.h"
class Enemy final : public Sprite
{
public:
	Enemy();
	~Enemy();

	// Life Cycle Functions
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	bool checkCollision;
	void reset();
private:
	int m_pFrame, m_pMaxFrame;
};

#endif /* defined (__ENEMY__) */
