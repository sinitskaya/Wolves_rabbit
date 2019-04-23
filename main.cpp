#include "game.h"

void Choose (Game_Wolves_rabbit & game, Position & position)
{
	int monsterIndex = -1;
	if(game.getGameMode() == Game_Wolves_rabbit::MT_Wolf)
	{
		if(!game.isGameOver())
		{
			cout << " ��� ���: i x y " << endl;
			cin >> monsterIndex >> position.x >> position.y;
			//������ ������ ������ ��� ������ ������
			while (!game.canMoveToPosition(monsterIndex, position))
			{
				cout << "�������, ������� ��� ���:" << endl;
				cout << " ��� ���: i x y " << endl;	
				cin >>  monsterIndex >> position.x >> position.y;
			}
		}
	} //���� ���� �� ����� ����� � �������
	else //����
	{
		monsterIndex = 0;
		game.setSelectedMonsterIndex(monsterIndex);
		if(!game.isGameOver())
		{
			cout << " ��� ���: x y " << endl;
			cin >> position.x >> position.y;
			while ( !game.canMoveToPosition(monsterIndex, position) )//��� ��������� �������
			{
				cout << "�������� x ��� y, ������� ��� ���:" << endl;
				cout << " ��� ���: x y " << endl;	
				cin >> position.x >> position.y;
			}
		}
	}
	
	game.setSelectedMonsterIndex(monsterIndex);
}
void Move(Game_Wolves_rabbit & game, Position & position)
{
	game.moveSelectedMonsterToPosition(position);
	//����� ������ ������ �����
	game.setSelectedMonsterIndex(-1);
}
void printWinner(Game_Wolves_rabbit & game)
{
	if(game.isGameOver())
	{
		game.GetWinner() == game.getGameMode() ? cout << "�� ����������" : cout << "Game over";
		cout << endl;
	}
}
void Play(Game_Wolves_rabbit & game, int & cinMonster)
{
	//******************������� ������***************
	cout << "�������� ������" << endl;
	cout << "���� - 0; ���� - 1." << endl;
	cin >> cinMonster;
	//��� ������ ������������
	while (!(cinMonster == 0 || cinMonster == 1))
	{
		cout << "�������, ��������� �����" << endl;
		cout << "���� - 0; ���� - 1." << endl;
		cin >> cinMonster;
	}
	//**********************************************
	//************��������� *************************
	// ������ ������
	if ( cinMonster == 0 )
		game.setGameMode(Game_Wolves_rabbit:: MT_Rabbit);
	else // ������ ������
	{
		game.setGameMode(Game_Wolves_rabbit:: MT_Wolf);
	}
	//****************************************************

	game.reset();
}

void PlayAgain(int & flagPlayGame)
{
	cout << "������ ����� - 1; ��������� - 0" << endl;
	cin >> flagPlayGame;
	while(!(flagPlayGame == 1 || flagPlayGame == 0))
	{
		cout << "�� �����. ������ ����� - 1; ��������� - 0" << endl;
		cin >> flagPlayGame;
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");
	Game_Wolves_rabbit game;
	//game.printMap();

	
	//main
	int cinMonster = -100;
	Position position; position.x = -100; position.y = -100;
	int flagPlayGame = 1;

	while ( flagPlayGame == 1)
	{
		//����� ������, ��������� �������, ����� ����
		Play(game, cinMonster);
		game.printMap();

		while( !game.isGameOver() )
		{
			Choose(game,  position);//�������� ���� ���� �� �����������
			Move(game, position);
			game.printMap();
		}
		printWinner(game); //������ ���� ���� ����������, ����� ������ �� ������
		PlayAgain(flagPlayGame);
	}

	system ("pause");
	return 0;
}