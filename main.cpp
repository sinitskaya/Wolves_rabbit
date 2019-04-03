#include "game.h"

void func (Game_Wolves_rabbit game, Position position)
{
	if(game.getGameMode() == Game_Wolves_rabbit::MT_Wolf)
	{
		int monsterIndex = -1;
		cout << " Ваш ход: i x y " << endl;
		cin >>  monsterIndex >> position.x >> position.y;

		while(monsterIndex < 0 || monsterIndex > 4 || position.x < 0 || position.x > 7 || position.y < 0 || position.y > 7)
		{
			if (monsterIndex < 0 || monsterIndex > 4)
			{
				cout << "неверный i, введите еще раз:" << endl;
				cout << " Ваш ход: i x y " << endl;	
				cin >>  monsterIndex >> position.x >> position.y;
			}
			if (position.x < 0 || position.x > 7 || position.y < 0 || position.y > 7)
			{
				cout << "неверный x или y, введите еще раз:" << endl;
				cout << " Ваш ход: i x y " << endl;	
				cin >>  monsterIndex >> position.x >> position.y;
			}
		}
	} //если волк то номер фишки и позицию
	else
	{
		cout << " Ваш ход: x y " << endl;
		cin >> position.x >> position.y;

		while (!game.moveSelectedMonsterToPosition(position) || position.x < 0 || position.x > 7 || position.y < 0 || position.y > 7)
		{
			int monsterIndex;
			cout << "неверный x или y, введите еще раз:" << endl;
			cout << " Ваш ход: i x y " << endl;	
			cin >>  monsterIndex >> position.x >> position.y;
		}
	}
	game.setSelectedMonsterIndex;

	//сброс выбора номера фишки
	game.setSelectedMonsterIndex(-1);
}
void Play(Game_Wolves_rabbit game, int cinMonster)
{
	//******************МОНСТЕР ИГРОКА***************
	cout << "Выберете игрока" << endl;
	cout << "Заяц - 0; Волк - 1." << endl;
	cin >> cinMonster;
	//кем играет пользователь
	while (cinMonster != 0 || cinMonster != 1)
	{
		cout << "Неверно, повторите снова" << endl;
		cout << "Заяц - 0; Волк - 1." << endl;
		cin >> cinMonster;
	}
	//**********************************************
	//************УСТАНОВКА *************************
	// играет зайцем
	if ( cinMonster == 0 )
		game.setPlayMode(Game_Wolves_rabbit:: MT_Rabbit);
	else // играет волком
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
			func();// ход пользователя
			// вывод поля
			game.printMap();
			//ход компьютера
			//runmaxmin(волка);
			game.printMap();
		}
	}
	else // пользователь волк
	{
		while ( game.getWinner == Game_Wolves_rabbit:: MT_No_Winner)
		{
			// заяц пошел, ход компьютера
			//runmaxmin(зайца);
			game.printMap();
	
			func(game, position);// ход пользователя
			game.printMap();
			//ход компьютера
		}		
	}
	
	
		if (game.getWinner == Game_Wolves_rabbit:: MT_Rabbit)
			cout << "Победитель Rabbit" << endl;
		else 
			cout << " Победитель Wolf" << endl;
		cout << "Закончить игру - 0; Играть еще - 1" << endl;
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
		//выбор игрока, установка монстра, старт игры
		Play(game, cinMonster);


	}
		

	//W_r w;
	system ("pause");
	return 0;
}