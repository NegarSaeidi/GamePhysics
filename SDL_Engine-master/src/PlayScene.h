#pragma once
#ifndef __PLAY_SCENE__
#define __PLAY_SCENE__

#include "Scene.h"
#include "Enemy.h"
#include "Player.h"
#include "Button.h"
#include "Label.h"
#include "Detenator.h"
#include "SDL.h"
#include "SDL_image.h"
class PlayScene : public Scene
{
public:
	PlayScene();
	~PlayScene();

	// Scene LifeCycle Functions
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	virtual void handleEvents() override;
	virtual void start() override;

private:
	// IMGUI Function
	void GUI_Function() ;
	std::string m_guiTitle;
	
	glm::vec2 m_mousePosition;

	Enemy* m_pEnemy;
	Player* m_pPlayer;
	bool m_playerFacingRight;
	Detenator* m_pDetenator;
	bool activate,throwBall;
	// UI Items
	Button* m_pBackButton;
	Button* m_pNextButton;
	Label* m_pInstructionsLabel;
	SDL_Texture* m_pBackground;
	SDL_Rect src, dst;

};

#endif /* defined (__PLAY_SCENE__) */