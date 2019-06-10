#pragma once

#include <cmath>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "rakieta.h"


#ifndef BALL_H
#define BALL_H

class Ball
{
	int speed, rotation;
public:
	Ball();
	~Ball();
	//void GenerateVelocity();
	sf::Vector2f GetVelocity();
	void Move(float x, float y);
	void Draw(sf::RenderWindow* win);
	void SetPosition(float x, float y);
	sf::Vector2f GetPosition();
	sf::Vector2f GetSize();
	void Rest();
	void Bounce(int a, int b);
	/// Wykrywanie kolizji z banda.
	bool DetectCollision();
	/// WYkrywanie kolizji z rakiet¹.
	bool DetectCollision(Rakieta* r);
	int GetSpeed();
	int GetRotation();
	void SetSpeed(int x);
	void SetRotation(int x);
private:

	sf::CircleShape circleShape;
	sf::Vector2f velocity;
	int maxAxisSpeed;
};

#endif
