#include "game.h"

Game_Wolves_rabbit:: Game_Wolves_rabbit()
{
	this->selectedMonster = -100; //пользователь еще не выбрал монстра
	this->winner = MT_No_Winner;
	this->recursivLevel = recursivlevel;
	this->MonsterCount = 5;

	this->possibleMoves[0].x = -1;		this->possibleMoves[0].y = -1;	//влево recur
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

	for(int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			mapView[i][j] = "*";
	for(int i = 0; i < 4; i++)
		mapView[0][this->wolfs[i].y] = "W" + to_string(i + 1);
	for(int i = 0; i < 8; i++)
		mapView[7][3] = "R0";
}

void Game_Wolves_rabbit:: reset()
{
	initialize(); // расставить фишки на шахматной доске
	if (this->gameMode != MT_Rabbit) // игрок не заяц т е волк
	{
		runMinMax(MT_Rabbit, 0, INT_MIN, INT_MAX);
		prepareMap();
		UpdatePrintMap();
	}
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
	if(monsterIndex > 0 && oldPosition.x > position.x)
		{return false; }

	return true;
}

bool Game_Wolves_rabbit:: isGameOver() // остались ли ходы
{
	//MonsterType 
	winner = MT_No_Winner;

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
		//printWinner();
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

	runMinMax(this->gameMode == MT_Rabbit ? MT_Wolf : MT_Rabbit, 0, INT_MIN, INT_MAX);

	UpdatePrintMap();
	isGameOver();
	return true;
}

void Game_Wolves_rabbit:: prepareMap()
{
	for(int i = 0; i < 8; i++)
		for(int j = 0; j < 8; j++)
			map[i][j] = Null;

	//поставили зайца
	this->map[this->rabbit.x][this->rabbit.y] = 0; // заяц 0

	//поставили волков на доску
	for(int i = 0; i < 4; i++)
		this->map[this->wolfs[i].x][this->wolfs[i].y] = -2;
}
void Game_Wolves_rabbit:: UpdatePrintMap()
{
	for(int i = 0; i < 8; i++)
	{
		for(int j = 0; j < 8; j++)
				mapView[i][j] = '*';
	}

	for(int i = 0; i < 4; i++)
		mapView[wolfs[i].x][wolfs[i].y] = "W" + to_string(i + 1);

	mapView[rabbit.x][rabbit.y] = "R0";
}

void Game_Wolves_rabbit:: printMap()
{
	//печать
	int size = 4;
	cout << setw(size + 1) << right << "|";
	for(int i = 0 ; i < 8; i++)
	{
		cout << setw(size) << right << i;
		cout << setw(size) << right << "|";
	}
	cout << endl;
	cout << "---------------------------------------------------------------------";
	cout << endl;
	for(int i = 0; i < 8; i++)
	{
		cout << setw(size) << left << i;
		cout << setw(size) << left << "|";
	
		for(int j = 0; j < 8; j++)
			{
				cout << setw(size) << left << mapView[i][j];
				cout << setw(size) << left << "|";

			}
		cout << endl;
		//cout << "---------------------------------------------------------------------";
		//cout << endl;
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
	if ( map[position.x][position.y] != Null )
		return false;
	return true;
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
		Position currentPosition = this->searchWay.front();
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
	
	int min = MAX_VALUE; //255
	for(int i = 0; i < 4; i++)
	{
		if( (this->map[0][i*2] > MIN_VALUE) && (this->map[0][i*2] < min) )
			min = this->map[0][i*2];
	}
	return min - 1;
}

void Game_Wolves_rabbit:: temporaryMonsterMovement(int monsterIndex, Position position)
{
	int x = position.x;
	int y = position.y;

	//для зайца
	if(monsterIndex == 0)
	{
		this->map[this->rabbit.x][this->rabbit.y] = Null;			// null - пусто; убрали с клетки зайца
		this->map[this->rabbit.x + x][this->rabbit.y + y] = 0; //0 - rabbit
		this->rabbit = this->rabbit + position;					//новая позиция зайца
	}//волки
	else
	{
		this->map[this->wolfs[monsterIndex - 1].x][this->wolfs[monsterIndex - 1].y] = Null;		  // null - пусто
		this->map[this->wolfs[monsterIndex - 1].x + x][this->wolfs[monsterIndex - 1].y + y] = -2; //-2 - wolves
		this->wolfs[monsterIndex - 1] = this->wolfs[monsterIndex - 1] + position;
	}
}

int Game_Wolves_rabbit:: runMinMax(MonsterType monster, int recursivLevel, int alpha, int beta)
{
	if (recursivLevel == 0)
		prepareMap();

	if (recursivLevel >= this->recursivLevel)
	{
		int heuristic = getHeuristicEvaluation();
		prepareMap();
		return heuristic;
	}

	int test = Null;
	int bestMove = Null;
	bool isWolf = (monster == MT_Wolf);
	int MinMax = isWolf ? MIN_VALUE : MAX_VALUE;
	//волк максимизирует, заяц минимизирует расстояние

	//от 0 до 7 возможные ходы волка; от 8 до 11 - зайца
	for(int i = (isWolf ? 0 : 8); i < (isWolf ? 8 : 12); i++)
	{
		int currentMonsterIndex = isWolf ? i / 2 + 1 : 0; // 0 1 ходы для 1волка, 2 3 для 2волка, 4 5 для 3волка, 5 7для 4волка
		//позиция монстра
		Position currentMonsterPos = currentMonsterIndex == 0 ? this->rabbit : this->wolfs[currentMonsterIndex - 1];
		//вариант сходить
		Position currentMove = this->possibleMoves[isWolf ? i % 2 + 2 : i % 4]; //волки ходят только вниз

		if(canMove(currentMonsterPos + currentMove))
		{ 
			// ходим
			temporaryMonsterMovement(currentMonsterIndex, currentMove); 

			//оцениваем насколько ход хорош
			test = runMinMax(isWolf ? MT_Rabbit : MT_Wolf, recursivLevel + 1, alpha, beta);

			Position pos; pos.x = 0; pos.y = 0;
			//восстанавливаем исходное состояние
			temporaryMonsterMovement(currentMonsterIndex, (pos - currentMove) );

			//если лучше из всех что были до этого то запомним его
			if( (test > MinMax && monster == MT_Wolf) || (test <= MinMax && monster == MT_Rabbit) || (bestMove == Null) )
			{
				MinMax = test;
				bestMove = i;
			}

			if(isWolf)
				alpha = MaxValue(alpha, test);
			else
				beta = MinValue(beta, test);

			if (beta <= alpha)
				break; 
		}
	}
	//некуда ходить
	if (bestMove == Null)
	{
		int heuristic = getHeuristicEvaluation();
		prepareMap();
		return heuristic;
	}

	//ходим
	if (recursivLevel == 0 && bestMove != Null)
	{
		if(monster == MT_Wolf)
			this->wolfs[bestMove / 2] = this->wolfs[bestMove / 2] + this->possibleMoves[bestMove % 2 + 2];
		else
			this->rabbit = this->rabbit + this->possibleMoves[bestMove % 4];
	}
	return MinMax;
}