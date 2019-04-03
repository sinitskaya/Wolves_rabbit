#include "game.h"

Game_Wolves_rabbit:: Game_Wolves_rabbit()
{
	selectedMonster = -100; //пользователь еще не выбрал монстра

	this->possibleMoves[0].x = -1;		this->possibleMoves[0].y = -1;	//влево вверх
	this->possibleMoves[1].x = -1;		this->possibleMoves[1].y =  1;	//вправо вверх
	this->possibleMoves[2].x =  1;		this->possibleMoves[2].y = -1;	//влево вниз
	this->possibleMoves[3].x =  1;		this->possibleMoves[3].y =  1;	//вправо вниз

	initialize(); // расставить фишки на шахматной доске
}

//расстановка фишек на доске; их начальное полочение
void Game_Wolves_rabbit:: initialize()
{
	this->wolfs[0].x = 0;	this->wolfs[0].y = 0;
	this->wolfs[1].x = 0;	this->wolfs[1].y = 2;
	this->wolfs[2].x = 0;	this->wolfs[2].y = 4;
	this->wolfs[3].x = 0;	this->wolfs[3].y = 6;

	this->rabbit.x = 7;		this->rabbit.y = 3; 
}

void Game_Wolves_rabbit:: reset()
{
	initialize(); // расставить фишки на шахматной доске
	if (this->gameMode != MT_Rabbit) // игрок не заяц т е волк
		runMinMax(MT_Rabbit, INT_MIN, INT_MAX);
}

int Game_Wolves_rabbit:: getMonsterIndexOnPosition(Position position) //номер фишки
{
	//если на позиции заяц, то его индекс = 0
	if(this->rabbit == position)
		return 0;
	//индекс волка (одна из фишек волка, которую хотим сдвинуть)
	for(int i = 0; i < 4; i++)
		if(this->wolfs[i] == position)
			return i + 1;
	//на позиции никого
	return -1;
}

//может ли пойти на клетку
bool Game_Wolves_rabbit:: canMoveToPosition (int monsterIndex, Position position)
{
	if(monsterIndex < 0 || monsterIndex > 4)
	{
		cout << "monsterIndex < 0, > 4"<< endl;
		return false; //не может пойти на клетку
	}

	//проверка границ
	if (!cheakRange (position))
		return false;

	//ходим только по черным (четным клеткам)
	if ((position.x + position.y) % 2 != 0 ) // число нечетное, то не может пойти на клетку; ходит только по четным клеткам
		return false;

	//*********ходим по диагонали
	//старая позиция фишки
	Position oldPosition = getMonsterPosition(monsterIndex);

	//расстояние/ разница
	Position diff = oldPosition - position;

	if (abs(diff.x) != 1 || abs(diff.y) != 1)
		return false;
	//******************************

	//не было хода
	if (oldPosition == position)
		return false;

	//проверяем что позиция не занята другой фишкой
	for(int i = 0; i < MonsterCount; i++)
	{
		if(getMonsterPosition(i) == position)
			return false;
	}

	//волк не может ходить вверх
	if(monsterIndex > 0 && oldPosition.y > position.y)
		{return false; }

	return true;
}

bool Game_Wolves_rabbit:: isGameOver() // остались ли ходы
{
	MonsterType winner = MT_No_Winner;

	//есть ли куда ходить волкам; если не куда, то победил заяц
	bool canMove = false;
	for(int i = 0; i < 4; i++)
	{
		for(int j = 2; j < 4; j++) //могут ли волки ходить вниз
		{		  //номер фишки(волки), позиция вока   + клетки по диагонали вниз
			if(canMoveToPosition(i + 1, this->wolfs[i] + this->possibleMoves[j]))
				canMove = true;
		}
	}
	//нет ходов для волков или заяц на вершине
	if (!canMove || this->rabbit.x == 0)
	{ winner = MT_Rabbit; }


	//есть ли куда ходить зайцу
	canMove = false;
	for(int i = 0; i < 4; i++)
	{
		if(canMoveToPosition(0, this->rabbit + this->possibleMoves[i]))
			{ canMove = true; }
	}
	//заяц окружен волками
	if (!canMove)
		{ winner = MT_Wolf;}

	if(winner != MT_No_Winner)//если есть победитель
	{
		return true;
	}

	return false; // игра продолжается
}

bool Game_Wolves_rabbit:: moveSelectedMonsterToPosition(Position position)
{
	if(this->selectedMonster < 0 || this->selectedMonster > 4)
	{
		//cout << "selectedMonster < 0, > 4" << endl;
		return false;
	}

	//хотим переместить выбранного зверя на клетку
	if(canMoveToPosition(this->selectedMonster, position)) //если можем переместить
	{
		if(this->selectedMonster == 0) //если это заяц
			this->rabbit = position; //переместили зайца
		else //если это волк
			this->wolfs[this->selectedMonster - 1] = position; //переместили волка
	}
	else //не переместили
		return false;

	//проверка
	if (isGameOver())
		return true;

	runMinMax(this->gameMode == MT_Rabbit ? MT_Wolf : MT_Rabbit, INT_MIN, INT_MAX);

	isGameOver();
	return true;
}

void Game_Wolves_rabbit:: prepareMap()
{
	for(int i = 0; i < 8; i++)
		for(int j = 0; j < 8; j++)
			map[i][j] = NULL;

	//поставили зайца
	this->map[this->rabbit.x][this->rabbit.y] = 0; // заяц 0

	//поставили волков на доску
	for(int i = 0; i < 4; i++)
		this->map[this->wolfs[i].x][this->wolfs[i].y] = -2;
}

void Game_Wolves_rabbit:: printMap()
{
	for(int i = 0; i < 8; i++)
	{
		for(int j = 0; j < 8; j++)
				mapView[i][j] = '*';
	}

	for(int i = 0; i < 8; i++)
	{
		for(int j = 0; j < 8; j++)
		{
			if(map[i][j] == 0)
			{
				mapView[i][j] = 'R0';
			}
			if(map[i][j] == -2)
			{
				Position position;		position.x = i;		position.y = j;
				int monsterIndex = getMonsterIndexOnPosition(position);
				mapView[i][j] = 'W' + to_string(monsterIndex);
			}
		}
	}

	//печать
	for(int i = 0; i < 8; i++)
	{
		for(int j = 0; j < 8; j++)
			{
				cout << mapView[i][j]; cout << "  ";
			}
		cout << endl;
	}
}

bool Game_Wolves_rabbit:: canMove(Position position)
{
	int x = position.x;
	int y = position.y;

	//проверка границ
	if(!cheakRange(x,y))
		return false;

	//стоит другая фишка(-2, 0) или уже есть значение
	if ( map[position.x][position.y] != NULL )
		return false;
}

int Game_Wolves_rabbit:: getHeuristicEvaluation()
{
	if(this->rabbit.x == 0)
		return 0;

	//очистка очереди
	while ( !this->searchWay.empty() )
		searchWay.pop();

	//
	this->searchWay.push(this->rabbit);
	while (!this->searchWay.empty())
	{
		Position currentPosition = this->searchWay.back();
		this->searchWay.pop();

		for(int i = 0; i < 4; i++)
		{	//проверка на свободность и существование ячейки
			if(canMove( currentPosition + possibleMoves[i] ) )
			{
				Position newPosition = currentPosition + possibleMoves[i];
				this->map[newPosition.x][newPosition.y] = this->map[currentPosition.x][currentPosition.y] + 1;

				this->searchWay.push(newPosition);
			}
		}
	}
	
	int min = MAX_VALUE; 
	for(int i = 0; i < 4; i++)
	{
		if( (this->map[0][i*2] > MIN_VALUE) && (this->map[0][i*2] < min) )
			min = this->map[0][i*2];
	}
	return min - 1;
}


/*
W_r :: W_r()
{
	int * p = new int [64];
	for (int i =0; i<64; i++)
		p[i]=i;
	for(int i = 0; i < 8; i++)
	{
		for(int j = i*8; j<(i+1)*8; j++)
			{
				cout << p[j]; cout << " ";
			}
		cout << endl;
	}
}
*/
