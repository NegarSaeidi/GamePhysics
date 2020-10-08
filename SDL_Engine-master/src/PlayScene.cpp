#include "PlayScene.h"
#include "Game.h"
#include "EventManager.h"
#include "Renderer.h"
// required for IMGUI
#include "imgui.h"
#include "imgui_sdl.h"
#include "Renderer.h"
#include "Util.h"
#include <cmath>
PlayScene::PlayScene()
{
	TextureManager::Instance()->load("../Assets/textures/Background.png","background");
	activate = false;
	throwBall = false;
	PlayScene::start();
}

PlayScene::~PlayScene()
= default;

void PlayScene::draw()
{
	TextureManager::Instance()->draw("background", 0, 0, 0,255, false, SDL_FLIP_NONE);
	//SDL_RenderCopy(Renderer::Instance()->getRenderer(), m_pBackground, &src, &dst);
	if(EventManager::Instance().isIMGUIActive())
	{
		GUI_Function();
	}
	
	drawDisplayList();
	//SDL_SetRenderDrawColor(Renderer::Instance()->getRenderer(), 255, 255, 255, 255);
}

void PlayScene::update()
{
	if((throwBall))
	updateDisplayList();
	m_pDetenator->m_checkBounds();
}

void PlayScene::clean()
{
	removeAllChildren();
}

void PlayScene::handleEvents()
{
	EventManager::Instance().update();

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->quit();
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_1))
	{
		TheGame::Instance()->changeSceneState(START_SCENE);
	}
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_3))
	{
		
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_2))
	{
		TheGame::Instance()->changeSceneState(END_SCENE);
	}
}

void PlayScene::start()
{
	// Set GUI Title
	m_guiTitle = "Play Scene";
	
	
	m_pEnemy = new Enemy();
	addChild(m_pEnemy);
	
	m_pPlayer = new Player();
	addChild(m_pPlayer);
	m_playerFacingRight = true;

	m_pDetenator = new Detenator();
	addChild(m_pDetenator);
}

void PlayScene::GUI_Function() 
{
	// Always open with a NewFrame
	ImGui::NewFrame();

	ImGui::Begin("Customize the setting", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar);

	if(ImGui::Button("Throw"))
	{
		throwBall = true;
	}
	
	ImGui::Separator();
	static bool isGravityEnabled =false;
	if (ImGui::Checkbox("Gravity", &isGravityEnabled))
	{
		std::cout << "Gravity Enabled" << std::endl;
		m_pDetenator->m_isGravityEnabled = isGravityEnabled;
	}
	ImGui::Separator();

	static float pos = m_pPlayer->getTransform()->position.x;
	
	if (ImGui::SliderFloat("Player Position", &pos, 0.0f,800.0f - 85.0f) );
	{
		if (!throwBall) 
		{	
			m_pPlayer->getTransform()->position.x = pos;
			m_pDetenator->getTransform()->position.x = pos + 68;
		}
		
	}
	static float EnemyPos = m_pEnemy->getTransform()->position.x;

	if (ImGui::SliderFloat("Enemy Position", &EnemyPos, 0.0f, 710.0f));
	{
		if (!throwBall)
		{
			m_pEnemy->getTransform()->position.x = EnemyPos;
		}

	}
	static float angle = 0;
	if (ImGui::SliderFloat("Angle", &angle, 0.0f, 90.0f));
	{}
	static float vel = Util::magnitude(m_pDetenator->getRigidBody()->velocity);
	if (ImGui::SliderFloat("Initial Velocity", &vel, 10.0f, 500.0f) );
	{
		if (!throwBall) {
			m_pDetenator->getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
			m_pDetenator->getRigidBody()->initialVel.x = vel * cos(Util::Deg2Rad * (angle));
			m_pDetenator->getRigidBody()->initialVel.y = -vel * sin(Util::Deg2Rad * (angle));
		}
	}
	ImGui::Separator();
	if (ImGui::Button("Reset"))
	{
		throwBall = false;
		angle = 0;
		pos = 85.0f;
		EnemyPos = 710.0f;
		vel = 0.0f;
		isGravityEnabled = false;
		m_pDetenator->reset();
		m_pPlayer->reset();
		m_pEnemy->reset();
	}

	ImGui::End();
	ImGui::EndFrame();
	// Don't Remove this
	ImGui::Render();
	ImGuiSDL::Render(ImGui::GetDrawData());
	ImGui::StyleColorsDark();
}
