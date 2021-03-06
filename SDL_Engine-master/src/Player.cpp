#include "Player.h"
#include "TextureManager.h"
#include "Renderer.h"
Player::Player(): m_pFrame(0), m_pMaxFrame(60)
{
	TextureManager::Instance()->load("../Assets/textures/Player.png", "player");
	TextureManager::Instance()->load("../Assets/textures/Player2.png", "player2");
	
	// Getters
	getTransform()->position = glm::vec2(85.0f, 434.0f);
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);

	setType(PLAYER);

}
void Player::reset()
{
	getTransform()->position = glm::vec2(85.0f, 434.0f);
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
}
Player::~Player()
= default;

void Player::draw()
{
	// Drawing the animation. 
	if (m_pFrame <= m_pMaxFrame/2)
	{
		m_pFrame++;
		TextureManager::Instance()->draw("player", getTransform()->position.x, getTransform()->position.y, 0, 255, false, SDL_FLIP_NONE);
	}
	else if ((m_pFrame > m_pMaxFrame / 2) && (m_pFrame < m_pMaxFrame))
	{
		m_pFrame++;
		TextureManager::Instance()->draw("player2", getTransform()->position.x, getTransform()->position.y, 0, 255, false, SDL_FLIP_NONE);
	}
	else if (m_pFrame == m_pMaxFrame)
	{
		m_pFrame = 0;
		TextureManager::Instance()->draw("player", getTransform()->position.x, getTransform()->position.y, 0, 255, false, SDL_FLIP_NONE);
	}
}

void Player::update() { }

void Player::clean() { }

