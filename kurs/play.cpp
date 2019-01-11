#include "game.h"

void Player::prepare()
{
	Point c;
	int s;
	int check = 1;
	for(int i = 0, count = 4; i < 4; i++, count--) {
		for (int j = 0; j < count; j++) {
			Ship s4(i+1, HOR);
			while (1) {
				system("cls");
				this->board_print(s4);
				cout << "\n��������� " << i + 1 << " �������� �������\n";
				if (check != 1)
					cout << "!!!!!������!!!!\n������������ ����� (��������� ����� ��������� �� ������ ����� ������).\n";
				s = _getch();
				if (s == SPACE) {
					if (s4.dir == HOR) {
						if (s4.x + s4.size > 10)
							s4.x = 0;
						s4.dir = VER;
					}
					else {
						if (s4.y + s4.size > 10)
							s4.y = 0;
						s4.dir = HOR;
					}
					continue;
				}
				if (s == ENTER) {
					check = this->set_ship(s4);
					if (check != 1)
						continue;
					else
						break;
				}
				if (s4.dir == HOR) {
					if (s == DOWN) {
						s4.x++;
						if (s4.x > 9)
							s4.x = 0;
					}
					else if (s == UP) {
						s4.x--;
						if (s4.x < 0)
							s4.x = 9;
					}
					else if (s == LEFT) {
						s4.y--;
						if (s4.y < 0)
							s4.y = 10 - s4.size;
					}
					else if (s == RIGHT) {
						s4.y++;
						if (s4.y + s4.size > 10)
							s4.y = 0;
					}
				}
				else {
					if (s == DOWN) {
						s4.x++;
						if (s4.x + s4.size > 10)
							s4.x = 0;
					}
					else if (s == UP) {
						s4.x--;
						if (s4.x < 0)
							s4.x = 10 - s4.size;
					}
					else if (s == LEFT) {
						s4.y--;
						if (s4.y < 0)
							s4.y = 9;
					}
					else if (s == RIGHT) {
						s4.y++;
						if (s4.y > 9)
							s4.y = 0;
					}
				}
			}
		}
	}
}

int Player::play(Board *p2)
{
	system("cls");
	Point a;
	int s;//���������� ������
	int check = 10;//�������� ��������
	while (1) {
		system("cls");
		this->board_print();
		cout << "----------------------------------------------------------------------------\n";
		p2->board_print(a);
		if (check == HITTED)
			cout << "\n\n�� ���� ��� ��������, ���������� �����\n\n";
		else if (check == HIT)
			cout << "\n\n���������\n\n";
		else if (check == KILL)
			cout << "\n\n�������\n\n";
		s = _getch();
		if (s == DOWN) {
			a.x++;
			if (a.x > 9)
				a.x = 0;
		}
		else if (s == UP) {
			a.x--;
			if (a.x < 0)
				a.x = 9;
		}
		else if (s == RIGHT) {
			a.y++;
			if (a.y > 9)
				a.y = 0;
		}
		else if (s == LEFT) {
			a.y--;
			if (a.y < 0)
				a.y = 9;
		}
		else if (s == ENTER) {
			check = p2->shot(a);
			if (check == MISS) {
				system("cls");
				this->board_print();
				cout << "----------------------------------------------------------------------------\n";
				p2->board_print(a);
				cout << "\n\n������\n\n";
				return 1;
			}
			else if (check == HIT || check == KILL) {
				p2->hp--;
				if (p2->check_win() == 0) {
					cout << "\n!!!!!������!!!!!!";
					return 0;
				}
			}
		}
	}
}