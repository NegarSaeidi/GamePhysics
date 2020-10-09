#include "Detenator.h"
#include "glm/gtx/string_cast.hpp"
#include "PlayScene.h"
#include "TextureManager.h"
#include "Util.h"
#include "Renderer.h"
#include <cmath>
#include "Game.h"


Detenator::Detenator()
{
	TextureManager::Instance()->load("../Assets/textures/Detenator.png","detenator");
	auto size = TextureManager::Instance()->getTextureSize("detenator");
	setWidth(size.x);
	setHeight(size.y);

	getTransform()->position = glm::vec2(148.0f, 494.0f);
	getRigidBody()->velocity = glm::vec2(0.0f,0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	getRigidBody()->isColliding = false;

	setType(DETENATOR);
	
	m_currentHeading = 0.0f; // current facing angle

	m_turnRate = 5.0f; // 5 degrees per frame
}

Detenator::~Detenator()
= default;
void Detenator::reset()
{
	getTransform()->position = glm::vec2(148.0f, 494.0f);
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	getRigidBody()->isColliding = false;
	keepTurning = true;
}
void Detenator::draw()
{
	TextureManager::Instance()->draw("detenator", getTransform()->position.x, getTransform()->position.y, m_currentHeading, 255, true);
}

void Detenator::update()
{	
	if (keepTurning) {
		move();
		turn();
	}
	else
	{
		getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	}
}

void Detenator::clean() { }

void Detenator::turn()
{
	m_currentHeading -= m_turnRate;
}

void Detenator::move()
{
	float deltaTime = 1.0f / 30.0f;
	glm::vec2 gravity = glm::vec2(0.0f, 9.8f);

	getRigidBody()->velocity = getRigidBody()->initialVel;
	getRigidBody()->acceleration += gravity;
	getRigidBody()->velocity += (getRigidBody()->acceleration) * deltaTime ;
	
	if (getRigidBody()->initialVel.y<0 && getRigidBody()->velocity.y==0.0)
	{
		getRigidBody()->initialVel.y = -1 * getRigidBody()->initialVel.y;
	}
	getTransform()->position += (getRigidBody()->velocity * deltaTime) ;
	

	std::cout <<"Vel:  "<< getRigidBody()->velocity.x << "    " << getRigidBody()->velocity.y << std::endl;
	std::cout << "Pos:  " << getTransform()->position.x << "    " << getTransform()->position.y << std::endl;
}

glm::vec2 Detenator::getCurrentDirection() const
{
	return m_currentDirection;
}

void Detenator::setCurrentDirection(glm::vec2 newDirection)
{
	m_currentDirection = newDirection;
}

void Detenator::m_checkBounds()
{
	if (getTransform()->position.x + 32 > Config::SCREEN_WIDTH)
	{
		if (getTransform()->position.y >= 545 - 35)
		{
			getTransform()->position = glm::vec2(Config::SCREEN_WIDTH - 32, 545-35);
			keepTurning = false;
		}
		else
			getTransform()->position = glm::vec2(Config::SCREEN_WIDTH - 32, getTransform()->position.y);
	}
	if (getTransform()->position.x < 0)
	{
		getTransform()->position = glm::vec2(0.0f, getTransform()->position.y);
	}

	if (getTransform()->position.y + 35 > 545)
	{
		getTransform()->position = glm::vec2(getTransform()->position.x, 545 - 35);
		keepTurning = false;
	}

	if (getTransform()->position.y < 15)
	{
		getTransform()->position = glm::vec2(getTransform()->position.x, 15.0f);
	}
}