


#include "AI.h"
AiTreeNode::AiTreeNode()
{
	up = nullptr;
	middle = nullptr;
	down = nullptr;
	/*a_before = silnik.get_a();
	a_before = silnik.get_b();*/
}

/*Tworzy kolejne elementy dla zadanych wartosci*/
AiTreeNode::AiTreeNode(int a_before, int b_before, int rotation_before)
{
	up = nullptr;
	middle = nullptr;
	down = nullptr;
	this->a_before = a_before;
	this->b_before = b_before;
	this->rotation_before = rotation_before;


}
/*Oblicza docelowe miejsce pilki*/
void AiTreeNode::CalculateBallTargetPosition()
{
	//kod z silnika
}
/*Sprawdza czy uda siê odbiæ pi³kê*/
void AiTreeNode::CanIBounceBall()
{
	//szybkoœæ rakietki+dlugoœæ

}

void AiTreeNode::CreateNextLevel()
{
	up = new AiTreeNode(a_after, b_after, rotation_after);
	middle = new AiTreeNode(a_after, b_after, rotation_after);
	down = new AiTreeNode(a_after, b_after, rotation_after);

}

