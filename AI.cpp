


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
AiTreeNode::AiTreeNode(int a_before, int b_before, int rotation_before, bool who)
{
	up = nullptr;
	middle = nullptr;
	down = nullptr;
	this->a_before = a_before;
	this->b_before = b_before;
	this->rotation_before = rotation_before;
	this->who = who;


}
/*Oblicza docelowe miejsce pilki
ustawia zmienne BallTargetPosition*/
void AiTreeNode::CalculateBallTargetPosition()
{
	//kod z silnika
}

/*Sprawdza czy uda siê odbiæ pi³kê
ustawia zmienne can, MyDistance, MyTargetPosition*/
void AiTreeNode::CanIBounceBall()
{
	//szybkoœæ rakietki+dlugoœæ

}

void AiTreeNode::CreateNextLevel()
{
	up = new AiTreeNode(a_after, b_after, rotation_after, !(this->who));
	middle = new AiTreeNode(a_after, b_after, rotation_after, !(this->who));
	down = new AiTreeNode(a_after, b_after, rotation_after, !(this->who));

}

AiTreeNode* create_root()
{
	bool who;
	if (1)//pilka leci do AI
	{
		who =  AiBounce;
	}
	else
	{
		who = UserBounce;
	}
	AiTreeNode* root;
	//root = new AiTreeNode(a_before, b_before, rotation_before, who);//pobierz zmienne z silnika
	root = new AiTreeNode(1, 1, 0, who);
	return root;
}

void AiTreeNode::DeleteNode(AiTreeNode* i)
{
	if (up != nullptr)
		DeleteNode(up);
	delete up;
	if (middle != nullptr)
		DeleteNode(middle);
	delete middle;
	if (down != nullptr)
		DeleteNode(down);
	delete down;
	
}

AiTreeNode::~AiTreeNode()//destruktor drzewa
{
	if (up != nullptr)
		DeleteNode(up);
	delete up;
	if (middle != nullptr)
		DeleteNode(middle);
	delete middle;
	if (down != nullptr)
		DeleteNode(down);
	delete down;
}




