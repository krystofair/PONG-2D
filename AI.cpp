


#include "AI.h"
#include "Silnik.cpp"
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

/*Oblicza zmienne pi³ki po odbiciu od danej rakietki
ustawia a_after, b_after_ rotation_after
*/
void AiTreeNode::CalculateBallParams()
{
	
	int bs = 50;
	int br = 15;
	this->speed_after = this->speed_before + 2 * bs;
	if (this->rotation_before == 0) this->rotation_after = this->rotation_before - (me*br);//pi³ka bez rotacji
	if (this->rotation_before != 0)// pi³ka z rotacja
	{
		if ((me = 1 && this->rotation_before > 0) || (me = -1 && rotation_before < 0))
		{
			this->rotation_after = this->rotation_before + me * br;//zwieksza bezwgledn¹ wartoœæ wspolczynnika rotacji
		}
		else
		{
			this->rotation_after = this->rotation_before - me * br;//zmniejsza bezwgledn¹ wartoœæ wspolczynnika rotacji
		}

	}
	if (this->speed_before > 1000) this->speed_after = 1000;//nie przekraczanie wartosci maksymalnej
	if (this->rotation_after > 100) this->rotation_after = 100;//////
	if (this->rotation_after < -100) this->rotation_after = -100;////
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

	AiTreeNode* root;
	
	//TODO pobierz zmienne o locie z silnika
	root = new AiTreeNode(a_before, b_before, rotation_before, AiBounce);//pobierz zmienne z silnika
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



bool AiTreeNode::get_can()//destruktor drzewa
{
	return this->can;
}

void StartAI()
{
	AiTreeNode* root = create_root();
	root->CalculateBallTargetPosition();
	root->CanIBounceBall();

	if (root->get_can())
	{
		root->CreateNextLevel();
		root->up.CalculateBallParams()



	}

}







