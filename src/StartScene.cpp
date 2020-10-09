#include "StartScene.h"
#include <algorithm>
#include "Game.h"
#include "glm/gtx/string_cast.hpp"
#include "EventManager.h"
#include "Renderer.h"
StartScene::StartScene()
{
	TextureManager::Instance()->load("../Assets/textures/StartScene.png", "background");
	StartScene::start();
}

StartScene::~StartScene()
= default;

void StartScene::draw()
{
	
	TextureManager::Instance()->draw("background", 0, 0, 0, 255, false, SDL_FLIP_NONE);
	drawDisplayList();
}

void StartScene::update()
{
	updateDisplayList();
}

void StartScene::clean()
{
	removeAllChildren();
}

void StartScene::handleEvents()
{
	EventManager::Instance().update();

	// Keyboard Events
	if(EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->quit();
	}

	if(EventManager::Instance().isKeyDown(SDL_SCANCODE_1))
	{
		TheGame::Instance()->changeSceneState(PLAY_SCENE);
	}
}

void StartScene::start()
{
	SoundManager::Instance().playMusic("start", -1);
	const SDL_Color blue = { 0, 0, 255, 255 };
	/*m_pStartLabel = new Label("MAY THE FORCE BE WITH YOU", "name", 20, { 255,255,255,255 }, glm::vec2(400.0f, 40.0f));
	m_pStartLabel->setParent(this);
	addChild(m_pStartLabel);*/

	/*m_pInstructionsLabel = new Label("Press 1 to Play", "name", 18, { 255,255,255,255 } , glm::vec2(400.0f, 120.0f));
	m_pInstructionsLabel->setParent(this);
	addChild(m_pInstructionsLabel);*/

	m_pGroupMembersInfoLabel[0] = new Label("Negar Saeidi - 101261396 ", "Consolas", 15, { 255,255,255,255 }, glm::vec2(110.0f, 585.0f));
	m_pGroupMembersInfoLabel[0]->setParent(this);
	addChild(m_pGroupMembersInfoLabel[0]);

	m_pGroupMembersInfoLabel[1] = new Label("Negin Saeidi - 101261395 ", "Consolas", 15, { 255,255,255,255 }, glm::vec2(380.0f, 585.0f));
	m_pGroupMembersInfoLabel[1]->setParent(this);
	addChild(m_pGroupMembersInfoLabel[1]);

	m_pGroupMembersInfoLabel[2] = new Label("  Mehrara Sarabi - 101247463 ", "Consolas", 15, { 255,255,255,255 }, glm::vec2(620.0f, 585.0f));
	m_pGroupMembersInfoLabel[2]->setParent(this);
	addChild(m_pGroupMembersInfoLabel[2]);

	/*m_pShip = new Ship();
	m_pShip->getTransform()->position = glm::vec2(400.0f, 300.0f);
	addChild(m_pShip); */


	// Start Button
	m_pStartButton = new Button();
	m_pStartButton->getTransform()->position = glm::vec2(400.0f, 315.0f); 

	m_pStartButton->addEventListener(CLICK, [&]()-> void
	{
			SoundManager::Instance().playSound("click", 0);
		m_pStartButton->setActive(false);
		TheGame::Instance()->changeSceneState(PLAY_SCENE);
	});
	
	m_pStartButton->addEventListener(MOUSE_OVER, [&]()->void
	{
		m_pStartButton->setAlpha(128);
	});

	m_pStartButton->addEventListener(MOUSE_OUT, [&]()->void
	{
		m_pStartButton->setAlpha(255);
	});
	addChild(m_pStartButton);

	
}

