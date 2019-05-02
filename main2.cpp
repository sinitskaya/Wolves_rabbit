#include "game.h"

void printWinner(Game_Wolves_rabbit & game)
{
	if(game.isGameOver())
	{
		Game_Wolves_rabbit :: MonsterType m = game.getWinner();
		if (m == Game_Wolves_rabbit :: MT_Rabbit)
			cout << "������� ����" << endl;
		else
			cout << "������� ����" << endl;
	}
}

void morePlay (Game_Wolves_rabbit & game, int & flagPrintMap, int & CountWinnerRabbit, int & CountWinnerWolves)
{
	for(int i =  1; i <= 8; i++) //
	{
		for(int j = 1; j <= 8; j++)
		{                       //���� ����
			game.playWithThemselves(i, j, flagPrintMap);
			cout << i << " " << j  << " ";
			printWinner(game); //������ ���� ���� ����������, ����� ������ �� ������
	        //PlayAgain(flagPlayGame);
			if (game.getWinner() == Game_Wolves_rabbit:: MT_Wolf)
			{
				CountWinnerWolves++;
			}
			else 
			{
				CountWinnerRabbit++;
			}
		}
	}
}

void Begin(int & flagPrintMap, int & flagRecursLevel)
{
	int flag = 0;
	cout << "����� ��� - 1, ���� ���� - 2" << endl;
	cin >> flag;

	while(! (flag == 1 || flag == 2))
	{
		cout << "������, ������� ��� ���" <<endl;
		cout << "����� ��� - 1, ���� ���� - 2" << endl;
		cin >> flag;
	}

	if(flag == 1){
		flagRecursLevel = 1; }
	else {
		flagPrintMap = 1; }
}

int main()
{
	setlocale(LC_ALL, "Russian");
	Game_Wolves_rabbit game;

	int flagPrintMap = 0, flagRecursLevel = 0;
	Begin(flagPrintMap, flagRecursLevel); //������� ����� ������

	if (flagRecursLevel == 1)// ���� � ������� ��������� �������� ����� � �����
	{
		int CountWinnerWolves = 0;
		int CountWinnerRabbit = 0;

		morePlay(game, flagPrintMap, CountWinnerRabbit, CountWinnerWolves);
		cout << "�������� ����� =" << CountWinnerWolves << endl;
		cout << "�������� ����� =" << CountWinnerRabbit << endl;
	}
	else // ���� ���� � ��������������� ������ �����
	{
		int i = recursivLevelRabbit;
		int j = recursivLevelWolves;
		game.playWithThemselves(i, j, flagPrintMap);
		cout << i << " " << j  << " ";
		printWinner(game); //������ ���� ���� ����������, ����� ������ �� ������
	}

	system ("pause");
	return 0;
}