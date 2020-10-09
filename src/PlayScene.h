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
	bool collisionWithEnemy();
private:
	// IMGUI Function
	void GUI_Function() ;
	std::string m_guiTitle;
	
	glm::vec2 m_mousePosition;
	std::vector<glm::vec2> points;
	
	float time;
	float landingPos,intialPos,initialVel;
	float angle =0.0,printableAngle=0.0f;
	float distanceFromEnemy,DetenatorInitPos;
	std::string dist;
	std::string timeRemaining;
	std::string land;


	Enemy* m_pEnemy;
	Player* m_pPlayer;
	bool m_playerFacingRight,death;
	Detenator* m_pDetenator;
	bool activate,throwBall;
	// UI Items
	Button* m_pBackButton;
	Button* m_pNextButton;
	Label* m_pInstructionsLabel;
	Label* calculations[3],*detenatorPos;
	
	SDL_Texture* m_pBackground;
	SDL_Rect src, dst;
	SDL_Texture* t_point;
};

#endif /* defined (__PLAY_SCENE__) */