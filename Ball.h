#pragma once
#include <iostream>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#ifndef BALL_H
#define BALL_H
//#include "paddle.h"
#include <stdio.h> 
#include <stdlib.h>  
#include <math.h>

class Ball
{
	int speed, rotation;
public:
	Ball();
	~Ball();
	void GenerateVelocity();
	sf::Vector2f GetVelocity();
	void Move(float x, float y);
	void Draw(sf::RenderWindow* win);
	void SetPosition(int x, int y);
	sf::Vector2f GetPosition();
	sf::Vector2f GetSize();
	void Rest();
	void Bounce(int a, int b);
	//bool DetectCollision(Paddle p);
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
