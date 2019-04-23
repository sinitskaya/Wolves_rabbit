#include "game.h"

void Choose (Game_Wolves_rabbit & game, Position & position)
{
	int monsterIndex = -1;
	if(game.getGameMode() == Game_Wolves_rabbit::MT_Wolf)
	{
		if(!game.isGameOver())
		{
			cout << " Ваш ход: i x y " << endl;
			cin >> monsterIndex >> position.x >> position.y;
			//играет только зайцем или только волком
			while (!game.canMoveToPosition(monsterIndex, position))
			{
				cout << "неверно, введите еще раз:" << endl;
				cout << " Ваш ход: i x y " << endl;	
				cin >>  monsterIndex >> position.x >> position.y;
			}
		}
	} //если волк то номер фишки и позицию
	else //заяц
	{
		monsterIndex = 0;
		game.setSelectedMonsterIndex(monsterIndex);
		if(!game.isGameOver())
		{
			cout << " Ваш ход: x y " << endl;
			cin >> position.x >> position.y;
			while ( !game.canMoveToPosition(monsterIndex, position) )//уже проверяет границы
			{
				cout << "неверный x или y, введите еще раз:" << endl;
				cout << " Ваш ход: x y " << endl;	
				cin >> position.x >> position.y;
			}
		}
	}
	
	game.setSelectedMonsterIndex(monsterIndex);
}
void Move(Game_Wolves_rabbit & game, Position & position)
{
	game.moveSelectedMonsterToPosition(position);
	//сброс выбора номера фишки
	game.setSelectedMonsterIndex(-1);
}
void printWinner(Game_Wolves_rabbit & game)
{
	if(game.isGameOver())
	{
		game.GetWinner() == game.getGameMode() ? cout << "Вы победитель" : cout << "Game over";
		cout << endl;
	}
}
void Play(Game_Wolves_rabbit & game, int & cinMonster)
{
	//******************МОНСТЕР ИГРОКА***************
	cout << "Выберете игрока" << endl;
	cout << "Заяц - 0; Волк - 1." << endl;
	cin >> cinMonster;
	//кем играет пользователь
	while (!(cinMonster == 0 || cinMonster == 1))
	{
		cout << "Неверно, повторите снова" << endl;
		cout << "Заяц - 0; Волк - 1." << endl;
		cin >> cinMonster;
	}
	//**********************************************
	//************УСТАНОВКА *************************
	// играет зайцем
	if ( cinMonster == 0 )
		game.setGameMode(Game_Wolves_rabbit:: MT_Rabbit);
	else // играет волком
	{
		game.setGameMode(Game_Wolves_rabbit:: MT_Wolf);
	}
	//****************************************************

	game.reset();
}

void PlayAgain(int & flagPlayGame)
{
	cout << "Играть снова - 1; закончить - 0" << endl;
	cin >> flagPlayGame;
	while(!(flagPlayGame == 1 || flagPlayGame == 0))
	{
		cout << "Не верно. Играть снова - 1; закончить - 0" << endl;
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
		//выбор игрока, установка монстра, старт игры
		Play(game, cinMonster);
		game.printMap();

		while( !game.isGameOver() )
		{
			Choose(game,  position);//выбираем если игра не закончилась
			Move(game, position);
			game.printMap();
		}
		printWinner(game); //печать если есть победитель, иначе ничего не делать
		PlayAgain(flagPlayGame);
	}

	system ("pause");
	return 0;
}