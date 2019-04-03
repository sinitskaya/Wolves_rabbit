#pragma once
#include <iostream>
#include <queue>
#include <string>
using namespace std;
#define MIN_VALUE 0
#define MAX_VALUE 300

class Position
{
public:
	int x;
	int y;
	bool operator == ( const Position& p2) const
	{
		return ( (p2.x == this->x)  &&  (p2.y == this->y) );
	}
	Position operator - (const Position p2)
	{
		Position pos;
		pos.x = this->x - p2.x;
		pos.y = this->y - p2.y;
		return pos;
	}

	Position operator + (const Position p2)
	{
		Position pos;
		pos.x = this->x + p2.x;
		pos.y = this->y + p2.y;
		return pos;
	}
};

class Game_Wolves_rabbit
{
public:
	enum MonsterType{
		MT_No_Winner = 0,
		MT_Rabbit = 1,
		MT_Wolf = 2
	};
private:   
	// 0 - заяц; 1, 2, 3, 4 - волки
	const int MonsterCount = 5;
	MonsterType gameMode;  //тип игрока (волк, заяц); кем играет пользователь	

	Position rabbit;			   //точка зайца
	Position wolfs[4];		   //позиция волка
	Position possibleMoves[4]; //возможные ходы
	string mapView[8][8];         //шахматная доска
	int map[8][8];  			//расстояние от зайца до края доски
	queue <Position> searchWay;
	int recursivLevel;
	
	int selectedMonster;   //выбранная шашка

	MonsterType winner;    //победитель
public:
		Game_Wolves_rabbit();
		void prepareMap();
		void printMap();
		//раставить игроков (фишки) на шахматной доске
		void initialize();
		//установить кем играет пользователь
		void setPlayMode(MonsterType gameMode) {this->gameMode = gameMode;};
		MonsterType getGameMode() {return this->gameMode;}
		MonsterType getWinner() {return this->winner;}

		//получить позицию зайца
		Position getRabbitPosition() { return rabbit;}

		//получить позицию волка
		Position getWolfPosition(int wolfIndex) 
		{
			if (wolfIndex < 4 && wolfIndex >= 0) // 0 1 2 3
			{ 
				return wolfs[wolfIndex];
			}
			else
			{
				cout << "ошибка 1"<< endl;
				//return ;
			}
		}

		//позиция фишек по номеру фишки; получить позицию монстра
		Position getMonsterPosition(int monsterIndex)
		{
			if (monsterIndex == 0)
				return getRabbitPosition();
			else
				return getWolfPosition(monsterIndex - 1);
		}

		//получить тип монстра
		MonsterType getMonsterType (int monsterIndex)
		{
			if (monsterIndex == 0)
				return MT_Rabbit;
			else
				return MT_Wolf;
		}

		//получить индекс монстра, кот нах в указаной клетке, либо -1; номер фишки
		int getMonsterIndexOnPosition(Position position);

		//получить индекс выбранного монстра
		int getSelectedMonsterIndex() {return selectedMonster;}

		//установить индекс выбранного монстра
		void setSelectedMonsterIndex (int monsterIndex) { this->selectedMonster = monsterIndex; }

		//true если любой (указанный) монстр может пойти на указанную клетку
		bool canMoveToPosition(int monsterIndex, Position position);

		//проверка границ; позиция не выходит за пределы доски
		bool cheakRange(int x, int y) {return (x>=0 && y>=0 && x<=7 && y<=7);}
		bool cheakRange(Position position) {return cheakRange( position.x, position.y );}
		//игра закончилась
		bool isGameOver();/*если да тоreturn winner*/

		//старт/перезапуск игры
		void reset();

		//**************для пользователя*******************

		//перемещает помеченного пользоваелем монстра на указанную позицию (клетку поля)
		bool moveSelectedMonsterToPosition(Position position);		
	private:
		//проверка на свободность и существование ячейки
		bool canMove(const Position);

		//временное передвижение монстра на карте; перестановка фишки
		void temporaryMonsterMovement(int monsterIndex, Position position);

		//эвристическая оценка вероятности победы. Чем больше, тем вероятнее, что победят волки.
		int getHeuristicEvaluation();

		//минимакс с отсечением
		int runMinMax(MonsterType monster, int recursivLevel, int alpha, int beta);

		int MaxValue(int elem1, int elem2)
		{
			if (elem1 > elem2)
				return elem1;
			return elem2;
		}

		int MinValue(int elem1, int elem2)
		{
			if (elem1 > elem2)
				return elem2;
			return elem1;
		}
};