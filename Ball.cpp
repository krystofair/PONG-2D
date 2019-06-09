
using namespace std;

#include "Ball.h"

Ball::Ball()
{
	maxAxisSpeed = 12;
	circleShape.setRadius(10);
	circleShape.setFillColor(sf::Color::White);
	GenerateVelocity();
}

float RandomNumber(float Min, float Max)
{
	return ((float(rand()) / float(RAND_MAX)) * (Max - Min));
}

void Ball::GenerateVelocity()
{
	float x, y;

	//utworzenie poziomej sk³dowej prêdkosci
	x = RandomNumber(1.5, 7) - RandomNumber(1.5, 7);

	//Jeœli pozioma sk³adowa prêdkosci za niska utowrzyæ inn¹
	if (abs(x) < 1)
	{
		GenerateVelocity();
		return;
	}
	//Utworzenie pionowej sk³¹dowej prêdkosci
	y = RandomNumber(1.5, 7) - RandomNumber(1.5, 7);
	velocity = sf::Vector2f(x, y);
	float magnitude = sqrt(pow(velocity.x, 2) + pow(velocity.y, 2));
	velocity.x = velocity.x / magnitude;
	velocity.y = velocity.y / magnitude;
	velocity.x = velocity.x * maxAxisSpeed;
	velocity.y = velocity.y * maxAxisSpeed;
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

void Ball::SetPosition(int x, int y)
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

void Ball::Rest()
{
	GenerateVelocity();
}

void Ball::Bounce(int a, int b)
{
	velocity = sf::Vector2f(velocity.x * a, velocity.y * b);
}

int Ball::GetSpeed()
{
	return speed;
}

int Ball::GetRotation()
{
	return rotation;
}
////////Niby detekcja kolizji//////////
/*

bool Ball::DetectCollision(Rakieta* p)
{
	if (GetPosition().y > p.GetPosition().y + p.GetSize().y
		|| GetPosition().y + GetSize().y < p.GetPosition().y
		|| GetPosition().x > p.GetPosition().x + p.GetSize().x
		|| GetPosition().x + GetSize().x < p.GetPosition().x)
	{
		return false;
	}
	else
	{
		Bounce(-1, 1);
	}

	
	return true;
}

*/