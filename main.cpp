#include "game.h"

void func (Game_Wolves_rabbit game, Position position)
{
	if(game.getGameMode() == Game_Wolves_rabbit::MT_Wolf)
	{
		int monsterIndex = -1;
		cout << " ��� ���: i x y " << endl;
		cin >>  monsterIndex >> position.x >> position.y;

		while(monsterIndex < 0 || monsterIndex > 4 || position.x < 0 || position.x > 7 || position.y < 0 || position.y > 7)
		{
			if (monsterIndex < 0 || monsterIndex > 4)
			{
				cout << "�������� i, ������� ��� ���:" << endl;
				cout << " ��� ���: i x y " << endl;	
				cin >>  monsterIndex >> position.x >> position.y;
			}
			if (position.x < 0 || position.x > 7 || position.y < 0 || position.y > 7)
			{
				cout << "�������� x ��� y, ������� ��� ���:" << endl;
				cout << " ��� ���: i x y " << endl;	
				cin >>  monsterIndex >> position.x >> position.y;
			}
		}
	} //���� ���� �� ����� ����� � �������
	else
	{
		cout << " ��� ���: x y " << endl;
		cin >> position.x >> position.y;

		while (!game.moveSelectedMonsterToPosition(position) || position.x < 0 || position.x > 7 || position.y < 0 || position.y > 7)
		{
			int monsterIndex;
			cout << "�������� x ��� y, ������� ��� ���:" << endl;
			cout << " ��� ���: i x y " << endl;	
			cin >>  monsterIndex >> position.x >> position.y;
		}
	}
	game.setSelectedMonsterIndex;

	//����� ������ ������ �����
	game.setSelectedMonsterIndex(-1);
}
void Play(Game_Wolves_rabbit game, int cinMonster)
{
	//******************������� ������***************
	cout << "�������� ������" << endl;
	cout << "���� - 0; ���� - 1." << endl;
	cin >> cinMonster;
	//��� ������ ������������
	while (cinMonster != 0 || cinMonster != 1)
	{
		cout << "�������, ��������� �����" << endl;
		cout << "���� - 0; ���� - 1." << endl;
		cin >> cinMonster;
	}
	//**********************************************
	//************��������� *************************
	// ������ ������
	if ( cinMonster == 0 )
		game.setPlayMode(Game_Wolves_rabbit:: MT_Rabbit);
	else // ������ ������
		game.setPlayMode(Game_Wolves_rabbit:: MT_Wolf);
	//****************************************************

	game.reset();
}
/*
	bool nowinner = true;

	if (game.getGameMode() == Game_Wolves_rabbit:: MT_Rabbit)
	{
		while ( game.getWinner == Game_Wolves_rabbit:: MT_No_Winner)
		{
			func();// ��� ������������
			// ����� ����
			game.printMap();
			//��� ����������
			//runmaxmin(�����);
			game.printMap();
		}
	}
	else // ������������ ����
	{
		while ( game.getWinner == Game_Wolves_rabbit:: MT_No_Winner)
		{
			// ���� �����, ��� ����������
			//runmaxmin(�����);
			game.printMap();
	
			func(game, position);// ��� ������������
			game.printMap();
			//��� ����������
		}		
	}
	
	
		if (game.getWinner == Game_Wolves_rabbit:: MT_Rabbit)
			cout << "���������� Rabbit" << endl;
		else 
			cout << " ���������� Wolf" << endl;
		cout << "��������� ���� - 0; ������ ��� - 1" << endl;
		cin >> flagPlayGame;
}
*/
int main()
{
	Game_Wolves_rabbit game;
	game.printMap;

	
	//main
	int cinMonster;
	Position position;
	int flagPlayGame = 1;


	while ( flagPlayGame == 1)
	{
		//����� ������, ��������� �������, ����� ����
		Play(game, cinMonster);


	}
		

	//W_r w;
	system ("pause");
	return 0;
}