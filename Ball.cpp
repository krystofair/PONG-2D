
using namespace std;

#include "Ball.h"
#include "globals.h"

Ball::Ball()
{
	circleShape.setRadius(10);
	circleShape.setFillColor(sf::Color::White);
}

Ball::~Ball()
{

}

void Ball::Move(float x, float y)
{
	circleShape.move(x, y);
}

void Ball::Draw(sf::RenderWindow* win)
{
	win->draw(circleShape);
}

void Ball::SetPosition(float x, float y)
{
	circleShape.setPosition(x, y);
}

sf::Vector2f Ball::GetSize()
{
	return sf::Vector2f(circleShape.getLocalBounds().width, circleShape.getLocalBounds().height);
}

sf::Vector2f Ball::GetVelocity()
{
	return velocity;
}

sf::Vector2f Ball::GetPosition()
{
	return circleShape.getPosition();
}

float Ball::GetSpeed()
{
	return speed;
}

float Ball::GetRotation()
{
	return rotation;
}
void Ball::SetSpeed(float x)
{
	if (x > 1000) x = 1000;
	speed = x;
}
void Ball::SetRotation(float x)
{
	if (x > 100) x = 100;
	if (x < -100) x = -100;
	rotation = x;
}


bool Ball::DetectCollision(Rakieta* r)
{
	float pktRy = (r->getPozY() + r->getDlugosc())/2;
	float pktBy = (GetPosition().y + GetSize().y)/2;
	float pktRx = (r->getPozX() + r->getSzerokosc())/2;
	float pktBx = (GetPosition().x + GetSize().x)/2;

	float dX = pktBx - pktRx;
	dX = (dX<0) ? -dX : dX;
	float dY = pktBy - pktRy;
	dY = (dY<0) ? -dY : dY;
	if(dY >= (r->getDlugosc()/2 + GetSize().y/2) || dX >(r->getSzerokosc()/2 + GetSize().x/2))
		return false;
	else
		return true;
}

bool Ball::DetectCollision()
{
	if(GetPosition().y + GetSize().y/2 <= 0) return true;
	else return false;
	if(GetPosition().y + GetSize().y/2 >= plansza.getHeight()) return true;
	else return false;
}
