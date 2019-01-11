#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <Windows.h>

#define HOR 0//�������������� ��������� �������
#define VER 1//������������

using namespace std;

enum ConsoleColor
{
	Black = 0,
	Blue = 1,//������ ��� �� �������������� ������
	Green = 2,
	Cyan = 3,//����������� �������
	Red = 4, //��� ����������� ��������
	Magenta = 5,
	Brown = 6,
	LightGray = 7,
	DarkGray = 8,
	LightBlue = 9,
	LightGreen = 10,
	LightCyan = 11,
	LightRed = 12,
	LightMagenta = 13,
	Yellow = 14,//����������� �������
	White = 15
};

enum Status {
	HITTED = -1,//�������������
	MISS = 0,//������
	HIT = 1,//���������
	KILL = 2//����������
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
	int x;//���������� �� ���������
	int y;//���������� �� �����������
public:
	Point(int x = 0, int y = 0) : x(x), y(y) {};//����������� � ����������� �� ���������
	friend Board;//������������� ������ ��� ������� � Point
	friend Player;
	friend Bot;
};

class Ship : public Point {
private:
	int size;//������ �������(1-4)
	int dir;//��������� �������(������������ ��� ��������������)
public:
	Ship(int size, int dir, int x = 0, int y = 0) : Point(x, y), size(size), dir(dir) {};
	friend Board;//������������� ������ ��� ������� � Ship
	friend Player;
	friend Bot;
};

class Board {
protected:
	ConsoleColor deck[10][10];//�������� ���������� � ����
	int hp;//���������� ��������(����� �� �������� ����� ���� ��������)
public:
	Board(int hp = 20);//����������� � ���������� �� ����������, �������� ����� ��������
	//���������� ������� board_print
	void board_print();//����� �����
	void board_print(Point a);//����� ����� � ���������� �����(��� ������ ���� ��� ��������)
	void board_print(Ship a);//����� ����� � ���������� �������(��� ����������� ��������)
	int set_ship(Ship a);//������� ����������� ������������ ����������� �������
	int check_status(Point a, int dir);//������� ����������� "����" ��� "�����" �������
	int shot(Point a);//������� ������������ ��������� ��������
	int check_win() {//������� ����������� ������ ����, ���� ��� �� �������� ���������� �� 0
		if (this->hp == 0) return 0;//...�� �� ���������� �����������
		else return 1;
	};
	//������ ����������� ������, ���������������� ��� ������������
	virtual void prepare() = 0;//������ ���������� ����� ����������� ��� ���������� � ����
	virtual int play(Board *) = 0;//������ ���������� ����� �������� ��������
	friend Player;//��� ���������� ��������
	friend Bot;
};

class Player: public Board {

public:
	Player(int hp = 20): Board(hp) {};
	void prepare();//����������� � ����(����������� ��������)
	int play(Board *);//��� ��������, ��������� ��������� �� ������ ���������� ���������� � ����������
};

class Bot: public Board {
private:
	Point shoot;//����� ��� ��������
	//����������, ������������ ������������� �������, ��� ��������� � �������������� �������
	int right;
	int left;
	int up;
	int down;
public:
	Bot(int hp = 20) : Board(hp) {//�����������, �������� ��������� ���������
		right = left = up = down = 0;
		shoot.x = -1;
		shoot.y = -1;
	};
	void prepare();//����������� � ����(����������� ��������)
	int play(Board *);//���������� ���� ����, ��������� ��������� �� ������ ���������� ���������� � ������
};

class Game {
private:
	string rules;//������ �������, ����������� �� ����� rules.txt
public:
	Game();
	void menu();//������� ��� ������(�����������, �����) � ����
	void gameplay(int mode);//�������, �������� ���� � ����������� �����, mode - ����������� ����� �������
	void print(int i);//����� ���� ��� ������, i - ���������� ��������� ���� ��� ������ �� �����
};

void SetColor(ConsoleColor text, ConsoleColor background);//������� ��� ��������

void check_ready();//�������� ���������� ������