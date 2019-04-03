# Игра "Волки и заяц"

## Содержание
* [Постановка задачи](#Постановка-задачи)
* [Описание игры](#Описание-игры)
* [Оценочная функция](#Оценоная-функция)

## Постановка задачи
Реализовать Alpha-beta pruning и использовать его в решении прикладной задачи.

## Описание игры
Игра "Волки и заяц"
«Волки и заяц» —  настольная шашечная игра для двух игроков. У одного из них одна черная шашка («заяц»), у другого — четыре белых («волки»). 
Игра идёт на шахматной доске (только по темным клеткам), шашки могут ходить по диагонали на ближайшую незанятую клетку — волки только вперед (вниз), заяц вперёд и назад. В начале игры заяц и волки расставлены по краям доски друг против друга, заяц ходит первым.

Цель зайца — дойти до противоположного края доски, в этом случае он выиграл партию. Волки выигрывают, если им удаётся окружить зайца или прижать его к краю, так что он не может больше ходить.

![1](/img/1.png)

## Оценочная функция
Результат оценочной функции - значение равное расстоянию (количеству ходов) от зайца до ближайшей верхней клетки, либо некоторая большая константа, если дойти зайцу до верхних клеток невозможно.
