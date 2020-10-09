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
	death = false;
	PlayScene::start();
	distanceFromEnemy = (m_pEnemy->getTransform()->position.x - m_pPlayer->getTransform()->position.x) / Util::PPM;
	dist = std::to_string(distanceFromEnemy);
	calculations[0] = new Label("Distance: " + dist, "Consolas", 20, { 255,204,0,255 }, glm::vec2(600.0f, 20.0f));
	calculations[0]->setParent(this);
	addChild(calculations[0]);
	
	time = ((2.0 * abs((initialVel)*sin(Util::Deg2Rad * (printableAngle))))) / 9.8;
	timeRemaining = std::to_string(time);
	calculations[1] = new Label("Total Time: " + dist, "Consolas", 20, { 255,204,0,255 }, glm::vec2(600.0f, 40.0f));
	calculations[1]->setParent(this);
	addChild(calculations[1]);

	landingPos = (intialPos)+((initialVel)*cos(Util::Deg2Rad * (printableAngle)) * time);
	land = std::to_string(landingPos);
	calculations[2] = new Label("Landing Position: " + dist, "Consolas", 20, { 255,204,0,255 }, glm::vec2(600.0f, 60.0f));
	calculations[2]->setParent(this);
	addChild(calculations[2]);
	

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
	calculations[0]->setText("Distance (player-enemy): " + dist);
	calculations[1]->setText("Total Time: " + timeRemaining);
	calculations[2]->setText("Landing Position: " + land);

	drawDisplayList();
	//SDL_SetRenderDrawColor(Renderer::Instance()->getRenderer(), 255, 255, 255, 255);
}

void PlayScene::update()
{

	distanceFromEnemy = (m_pEnemy->getTransform()->position.x - m_pPlayer->getTransform()->position.x) / Util::PPM;
	dist = std::to_string(distanceFromEnemy);

	time = ((2.0 *abs((initialVel)*sin(Util::Deg2Rad * (printableAngle) ))))/ 9.8;
	
	timeRemaining = std::to_string(time);
	
	if(throwBall)
	updateDisplayList();
	else
	{
		landingPos = (intialPos ) +( (initialVel ) * cos(Util::Deg2Rad * (printableAngle)) * time) ;
		//landingPos = ((initialVel * initialVel * sin(Util::Deg2Rad * (2*printableAngle)))/9.8)+intialPos;
		land = std::to_string(landingPos);

	}
	m_pDetenator->m_checkBounds();
	if (death == false)
		m_pEnemy->checkCollision = collisionWithEnemy();
	std::cout << "position ------------   " << m_pDetenator->getTransform()->position.x/Util::PPM<<std::endl;

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
	SoundManager::Instance().playMusic("space", -1);
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

bool PlayScene::collisionWithEnemy()
{

	if ((m_pDetenator->getTransform()->position.x + 32 > m_pEnemy->getTransform()->position.x)
		&&
		(m_pDetenator->getTransform()->position.y + 32 > m_pEnemy->getTransform()->position.y))
	{
		death = true;
		SoundManager::Instance().playSound("death", 0);
	}
	return death;

}

void PlayScene::GUI_Function() 
{
	// Always open with a NewFrame
	ImGui::NewFrame();

	ImGui::Begin("Customize the setting", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar);

	if(ImGui::Button("Throw"))
	{
		m_pPlayer->jump = true;
		m_pPlayer->m_pFrame = 0;
		SoundManager::Instance().playSound("throw", 0);
		throwBall = true;
		
	}
	
	
	ImGui::Separator();
	
	static float pos = m_pPlayer->getTransform()->position.x/Util::PPM;
	if (ImGui::SliderFloat("Player Position (m)", &pos, 0.0f,715.0f/Util::PPM) );
	{
		intialPos = pos+(63/Util::PPM);
		DetenatorInitPos = intialPos;
		if (!throwBall) 
		{	
			m_pPlayer->getTransform()->position.x = pos * Util::PPM;
			m_pDetenator->getTransform()->position.x = (pos * Util::PPM )+ 63;

		}
		
	}
	ImGui::Separator();
	//Enemy meter
	static float EnemyPos = m_pEnemy->getTransform()->position.x/Util::PPM;
	if (ImGui::SliderFloat("Enemy Position (m)", &EnemyPos, 0.0f, 710.0f/Util::PPM));
	{
		if (!throwBall)
		{
			m_pEnemy->getTransform()->position.x = EnemyPos* Util::PPM;
		}

	}
	static float angle = 15.9;//Default value from part1
	ImGui::SliderFloat("Angle (Degrees)", &angle, 0.0f, 90.0f);
	printableAngle = angle;
	static float vel = 95.0f;//m/s
	if (ImGui::SliderFloat("Initial Velocity (m/s)", &vel, 10.0f, 200.0f) );
	{
		initialVel = vel;
		if (!throwBall) {
			m_pDetenator->getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
			m_pDetenator->getRigidBody()->velocity.x = vel * cos(Util::Deg2Rad * (printableAngle))* Util::PPM;
			m_pDetenator->getRigidBody()->velocity.y = -vel * sin(Util::Deg2Rad * (printableAngle))* Util::PPM;
		}
	}
	ImGui::Separator();
	if (ImGui::Button("Reset"))
	{
		throwBall = false;
		angle = 0;
		printableAngle = 0;
		pos = 85.0f/Util::PPM;
		EnemyPos = 710.0f / Util::PPM;
		vel = 0.0f;
		m_pDetenator->reset();
		m_pPlayer->reset();
		m_pEnemy->reset();
		death = false;
	}

	ImGui::End();
	ImGui::EndFrame();
	// Don't Remove this
	ImGui::Render();
	ImGuiSDL::Render(ImGui::GetDrawData());
	ImGui::StyleColorsDark();
}
