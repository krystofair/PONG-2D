#pragma once

#define AiBounce true;
#define UserBounce false;
#define part_up =1;
#define part_middle = 0;
#define part_down=-1;
class AiTreeNode
{
private:
	AiTreeNode* up;
	AiTreeNode* middle;
	AiTreeNode* down;
	char me;//ktora czescia paletki jestem
	int a_before, b_before, rotation_before, speed_before;//rownanie prostej przed odbiciem
	int a_after, b_after, rotation_after, speed_after;//rownanie prostej po odbiciu
	bool kierunek;//kierunek pilki;
	bool who;
	unsigned BallTargetPosition;//gdzie uderzy pilka
	bool can;//czy jest szansa na odbicie
	unsigned MyDistance;//odleglosc rakaietki od pilki
	unsigned MyTargetPosition;//optymalna moja pozycja do odbicia pilki



	unsigned OponentDistance;//ogleglosc przeciwnika od pilki po odbiciu

public:
	AiTreeNode();//tylko dla roota
	bool get_can();
	AiTreeNode(int a_before, int b_before, int rotation_before, bool who);//dla kolejnych elementow
	~AiTreeNode();
	void CalculateBallTargetPosition();
	void CalculateBallParams();
	void CanIBounceBall();
	void DeleteNode(AiTreeNode*);

	void CreateNextLevel();


};
