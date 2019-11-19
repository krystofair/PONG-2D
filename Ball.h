#pragma once

#include <cmath>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "rakieta.h"


#ifndef BALL_H
#define BALL_H

class Ball
{
	float speed{2}, rotation{0};
public:
	Ball();
	~Ball();
	void Move(float x, float y);
	void Draw(sf::RenderWindow* win);
	void SetPosition(float x, float y);
	sf::Vector2f GetPosition() const;
	sf::Vector2f GetSize() const;
	/// Wykrywanie kolizji z banda.
	bool DetectCollision() const;
	/// WYkrywanie kolizji z rakiet¹.
	bool DetectCollision(Rakieta* r) const;
	float GetSpeed() const;
	float GetRotation() const;
	void SetSpeed(float x);
	void SetRotation(float x);
private:

	sf::CircleShape circleShape;
	float prog_wejscia = 15;
	float prog_wyjscia = 15;
};

#endif
