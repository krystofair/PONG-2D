
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

sf::Vector2f Ball::GetSize() const
{
	return sf::Vector2f(circleShape.getLocalBounds().width, circleShape.getLocalBounds().height);
}

sf::Vector2f Ball::GetPosition() const
{
	return circleShape.getPosition();
}

float Ball::GetSpeed() const
{
	return speed;
}

float Ball::GetRotation() const
{
	return rotation;
}
void Ball::SetSpeed(float x)
{
	if(x > 1000) x = 1000;
	else if(x<-1000) x = -1000;
	speed = x;
}
void Ball::SetRotation(float x)
{
	if (x > 100) x = 100;
	if (x < -100) x = -100;
	rotation = x;
}


bool Ball::DetectCollision(Rakieta* r) const
{
	bool warunek_wejscia{false}, warunek_wyjscia{false};
	int war_odb{0};
	float dl_r = r->getDlugosc();
	float sz_r = r->getSzerokosc();
	float promien = circleShape.getRadius();
	double rel_pkt_b[] ={
		(GetPosition().x + 2*promien)/2,
		GetPosition().y + promien
	};
	double rel_pkt_r[]={
		(r->getPozX() + sz_r)/2,
		r->getPozY() + dl_r/2
	};
	sz_r = sz_r/2;
	dl_r = dl_r/2;
	auto down_edge_r = rel_pkt_r[1] + dl_r + promien;
	auto up_edge_r = rel_pkt_r[1] - dl_r - promien;

	war_odb = (down_edge_r - rel_pkt_b[1]) * (rel_pkt_b[1] - up_edge_r);
	if(war_odb>0) // it is war_odb.
	{
		if(r->getStrona()) {
			warunek_wejscia = ((rel_pkt_b[0] >= (rel_pkt_r[0] - sz_r - prog_wejscia)));
							   //&& (rel_pkt_b[0] <= (rel_pkt_r[0] - sz_r + prog_wyjscia)));
			warunek_wyjscia = rel_pkt_b[0] <= (rel_pkt_r[0] - sz_r - prog_wyjscia);
		}
		else {
			warunek_wejscia = ((rel_pkt_b[0] <= (rel_pkt_r[0] + sz_r + prog_wejscia)));
							   //&& (rel_pkt_b[0] >= (rel_pkt_r[0] + sz_r - prog_wyjscia)));
			warunek_wyjscia = rel_pkt_b[0] >= (rel_pkt_r[0] + sz_r + prog_wyjscia);
		}
		return warunek_wejscia && !warunek_wyjscia;
	}
	else return false;

	
}

bool Ball::DetectCollision() const
{
	bool warunek_wejscia{false}, warunek_wyjscia{false};
	float up_edge = GetPosition().y;
	float down_edge = GetPosition().y + GetSize().y;
	auto bottom = plansza.getHeight();
	if(down_edge < bottom/2)
	{
		warunek_wejscia = (up_edge <= prog_wejscia);
		warunek_wyjscia = (up_edge > prog_wyjscia);
	}
	else
	{
		warunek_wejscia = (down_edge >= bottom - prog_wejscia);
		warunek_wyjscia = (down_edge < bottom - prog_wyjscia);
	}

	return warunek_wejscia && !warunek_wyjscia;
}
