#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <Windows.h>

#define HOR 0//горизонтальное положение корабля
#define VER 1//вертикальное

using namespace std;

enum ConsoleColor
{
	Black = 0,
	Blue = 1,//пустая или не простреллянаяя клетка
	Green = 2,
	Cyan = 3,//окрашивание корабля
	Red = 4, //для окрашивания попадния
	Magenta = 5,
	Brown = 6,
	LightGray = 7,
	DarkGray = 8,
	LightBlue = 9,
	LightGreen = 10,
	LightCyan = 11,
	LightRed = 12,
	LightMagenta = 13,
	Yellow = 14,//окрашивание промаха
	White = 15
};

enum Status {
	HITTED = -1,//прострелянная
	MISS = 0,//промах
	HIT = 1,//попадание
	KILL = 2//потопление
};

enum Keys {
	UP = 72,
	DOWN = 80,
	RIGHT = 77,
	LEFT = 75,
	ENTER = 13,
	SPACE = 32
};

class Board;
class Gamer;
class Player;
class Bot;

class Point {
protected:
	int x;//координата по вертикали
	int y;//координата по горизонтали
public:
	Point(int x = 0, int y = 0) : x(x), y(y) {};//констурктор с параметрами по умолчанию
	friend Board;//дружественные классы для доступа к Point
	friend Player;
	friend Bot;
};

class Ship : public Point {
private:
	int size;//размер корабля(1-4)
	int dir;//положение корабля(вертикальное или горизонтальное)
public:
	Ship(int size, int dir, int x = 0, int y = 0) : Point(x, y), size(size), dir(dir) {};
	friend Board;//дружественные классы для доступа к Ship
	friend Player;
	friend Bot;
};

class Board {
protected:
	ConsoleColor deck[10][10];//содержит информацию о поле
	int hp;//количество здоровья(сумма не подбитых ячеек всех кораблей)
public:
	Board(int hp = 20);//констурктор с параметром по умаолчанию, задающий колво здоровья
	//перегрузка функции board_print
	void board_print();//вывод доски
	void board_print(Point a);//вывод доски с выделением точки(для выбора поля для стрельбы)
	void board_print(Ship a);//вывод доски с выделением корабля(для расстановки кораблей)
	int set_ship(Ship a);//функция проверяющая допустимость расстановки корабля
	int check_status(Point a, int dir);//функция проверяющая "убит" или "ранен" корабль
	int shot(Point a);//функция возвращающая результат стрельбы
	int check_win() {//функция проверяющая статус игры, если чье то здоровье опускается до 0
		if (this->hp == 0) return 0;//...то он считаетсяя проигравшим
		else return 1;
	};
	//чистые виртуальные методы, переопределяемые при наследовании
	virtual void prepare() = 0;//чистый виртульный метод реализуется для подготовки к игре
	virtual int play(Board *) = 0;//чистый виртульный метод задающий геймплей
	friend Player;//для уменьшения здоровья
	friend Bot;
};

class Player: public Board {

public:
	Player(int hp = 20): Board(hp) {};
	void prepare();//подготоовка к игре(расстановка кораблей)
	int play(Board *);//сам геймплей, принимает указатель на объект содержащий информацию о противнике
};

class Bot: public Board {
private:
	Point shoot;//точка для стрельбы
	//переменные, показывающие прострелянные стороны, при попадании в неоднопалубный корабль
	int right;
	int left;
	int up;
	int down;
public:
	Bot(int hp = 20) : Board(hp) {//конструктор, задающий начальные параметры
		right = left = up = down = 0;
		shoot.x = -1;
		shoot.y = -1;
	};
	void prepare();//подготоовка к игре(расстановка кораблей)
	int play(Board *);//реализация игры бота, принимает указатель на объект содержащий информацию о игроке
};

class Game {
private:
	string rules;//Хранит правила, считываемые из файла rules.txt
public:
	Game();
	void menu();//функция для работы(перемещение, выбор) с меню
	void gameplay(int mode);//функция, задающая игру и очередность ходов, mode - опеределяет колво игроков
	void print(int i);//вывод меню или правил, i - определяет состояние меню для вывода на экран
};

void SetColor(ConsoleColor text, ConsoleColor background);//функция для покраски

void check_ready();//проверка готовности игрока