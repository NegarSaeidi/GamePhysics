#include "Enemy.h"
#include "TextureManager.h"
#include "Renderer.h"
Enemy::Enemy() : m_pFrame(0), m_pMaxFrame(60)
{
	TextureManager::Instance()->load("../Assets/textures/Enemy1 (1).png", "enemy");
	TextureManager::Instance()->load("../Assets/textures/Enemy1 (2).png", "enemy2");
	getTransform()->position = glm::vec2(710.0f, 435.0f);

	setType(ENEMY);
}
void Enemy::reset()
{
	getTransform()->position = glm::vec2(710.0f, 435.0f);
}
Enemy::~Enemy()
= default;

void Enemy::draw()
{
	if (m_pFrame <= m_pMaxFrame / 2)
	{
		m_pFrame++;
		TextureManager::Instance()->draw("enemy", getTransform()->position.x, getTransform()->position.y, 0, 255, false, SDL_FLIP_HORIZONTAL);
	}
	else if ((m_pFrame > m_pMaxFrame / 2) && (m_pFrame < m_pMaxFrame))
	{
		m_pFrame++;
		TextureManager::Instance()->draw("enemy2", getTransform()->position.x, getTransform()->position.y, 0, 255, false, SDL_FLIP_HORIZONTAL);
	}

	else if (m_pFrame == m_pMaxFrame)
	{
		m_pFrame = 0;
		TextureManager::Instance()->draw("enemy", getTransform()->position.x, getTransform()->position.y, 0, 255, false, SDL_FLIP_HORIZONTAL);
	}
}

void Enemy::update() { }

void Enemy::clean() { }