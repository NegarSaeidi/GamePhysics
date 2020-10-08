#pragma once
#ifndef __START_SCENE__
#define __START_SCENE__

#include "Scene.h"
#include "Label.h"
#include "Detenator.h"
#include "Button.h"
#include "SDL.h"
#include "SDL_image.h"
class StartScene final : public Scene
{
public:
	StartScene();
	~StartScene();

	// Inherited via Scene
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	virtual void handleEvents() override;
	virtual void start() override;
	
private:
	Label* m_pStartLabel{};
	Label* m_pInstructionsLabel{};

	Detenator* m_pShip{};

	Button* m_pStartButton;

	Label* m_pGroupMembersInfoLabel[3];
	SDL_Texture* m_pBackground;
	SDL_Rect src, dst;
};

#endif /* defined (__START_SCENE__) */