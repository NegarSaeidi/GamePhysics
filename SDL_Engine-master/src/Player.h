#pragma once
#ifndef __PLAYER__
#define __PLAYER__

#include "Sprite.h"
#include "SDL.h"
#include "SDL_image.h"
class Player final : public Sprite
{
public:
	Player();
	~Player();

	// Life Cycle Methods
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	void reset();
private:
	int m_pFrame, m_pMaxFrame;
};

#endif /* defined (__PLAYER__) */