#include "game.h"

void SetColor(ConsoleColor text, ConsoleColor background)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}

void check_ready()
{
	system("cls");
	while (_getch() != ENTER) {
		SetColor(Black, Yellow);
		cout << "\n\n\t\t����� ������ ������, ������� Enter\n\n";
		SetColor(White, Black);
	}
}

Game::Game()
{
	ifstream f("rules.txt");
	getline(f, this->rules, '\0');
	f.close();
}

void Game::menu()
{
	int c = 1;
	this->print(c);
	int s;

	while (1) {
		this->print(c);
		s = _getch();
		if (s == DOWN) {
			c++;
			if (c > 4)
				c = 1;
			this->print(c);
		}
		else if (s == UP) {
			c--;
			if (c < 1)
				c = 4;
			this->print(c);
		}
		else if (s == ENTER) {
			if (c == 1)
				this->gameplay(c);
			else if (c == 2)
				this->gameplay(c);
			else if (c == 3)
				this->print(5);
			else if (c == 4)
				break;
		}
	}
}

void Game::print(int i)
{
	system("cls");
	SetColor(LightCyan, LightBlue);
	cout << "\n\n                  \n";
	cout << "    ������� ���   \n";
	cout << "                  \n\n\n";
	SetColor(White, Black);
	if (i == 1) {
		SetColor(Black, Yellow);
		cout << "       1 �����\n\n";
		SetColor(White, Black);
		cout << "       2 ������\n\n";
		cout << "       �������\n\n";
		cout << "       �����\n\n";
	}
	else if (i == 2) {
		cout << "       1 �����\n\n";
		SetColor(Black, Yellow);
		cout << "       2 ������\n\n";
		SetColor(White, Black);
		cout << "       �������\n\n";
		cout << "       �����\n\n";
	}
	else if (i == 3) {
		cout << "       1 �����\n\n";
		cout << "       2 ������\n\n";
		SetColor(Black, Yellow);
		cout << "       �������\n\n";
		SetColor(White, Black);
		cout << "       �����\n\n";
	}
	else if (i == 4) {
		cout << "       1 �����\n\n";
		cout << "       2 ������\n\n";
		cout << "       �������\n\n";
		SetColor(Black, Yellow);
		cout << "       �����\n\n";
		SetColor(White, Black);
	}
	else if (i == 5) {
		cout << "\t�������: \n" << rules;
		cout << "\n\n\t����������: \n";
		cout << "��������� - ������������ �������\n������ - ����� ����������� �������(��� ������������),\n";
		cout << "Enter - ������� ����� � ������� �������/���������� �������.";
		SetColor(Black, Yellow);
		cout << "\n\n       �����\n\n";
		SetColor(White, Black);
		while (_getch() != ENTER)
			continue;
	}
}

void Game::gameplay(int mode)
{
	Board **player;
	int i, j;
	player = new (Board *[2]);
	player[0] = new Player;
	if (mode == 1)
		player[1] = new Bot;
	else if(mode == 2)
		player[1] = new Player;

	check_ready();

	for (i = 0; i < 2; i++) {
		player[i]->prepare();
		if(mode == 2)
			check_ready();
	}
	i = 0;
	j = 1;
	int win;
	while (1) {
		win = player[i]->play(player[j]);
		system("pause");
		if (win == 0) {
			win = i;
			break;
		}
		if(mode == 2)
			check_ready();

		win = player[j]->play(player[i]);
		if (mode == 2)
			system("pause");
		if (win == 0) {
			win = j;
			break;
		}
		if (mode == 2)
			check_ready();
	}
	system("cls");
	if (mode == 1) {
		if(win == 0)
			cout << "\n\n\n\t\t!!!!����������� �� ��������!!!!!!\n";
		else
			cout << "\n\n\n\t\t� ��������� �� ��������� :-(\n";
	}
	if(mode == 2)
		cout << "\n\n\n\t\t!!!!����������� ������� ����� " << win + 1 << "!!!!!!\n";
	system("pause");
}