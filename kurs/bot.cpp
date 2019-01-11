#include "game.h"
#include <ctime>

void Bot::prepare()
{
	srand(time(NULL));
	int check = 1;
	int x, y, dir;
	for (int i = 0, count = 4; i < 4; i++, count--) {
		for (int j = 0; j < count; j++) {
			while (1) {
				dir = rand() % 2;
				x = rand() % 10;
				y = rand() % 10;
				if (dir == HOR && y + i > 9)
					continue;
				else if (dir == VER && x + i > 9)
					continue;
				Ship s4(i + 1, dir, x, y);
				check = this->set_ship(s4);
				if (check != 1)
					continue;
				else
					break;
			}
		}
	}
}
					

int Bot::play(Board *p2)
{
	srand(time(NULL));
	Point a, b;
	int check = 10;//проверка выстрела


	while (1) {
		system("cls");
		p2->board_print();
		cout << "----------------------------------------------------------------------------\n";
		this->board_print(b);
		cout << "\n\nХод противника:\n   ";
		if (shoot.x == -1 && shoot.y == -1) {
			shoot.x = rand() % 10;
			shoot.y = rand() % 10;
			check = p2->shot(shoot);
		}
		else {
			check = HIT;
			p2->hp++;
		}
		if (check == MISS) {
			shoot.x = -1;
			shoot.y = -1;
			system("cls");
			p2->board_print();
			cout << "----------------------------------------------------------------------------\n";
			this->board_print(b);
			cout << "\n\nХод противника:\n   ";
			cout << "Промах\n\n";
			system("pause");
			return 1;
		}
		else if (check == HITTED) {
			shoot.x = -1;
			shoot.y = -1;
			continue;
		}
		else if (check == HIT) {
			p2->hp--;
			if (this->right == 0) {
				system("cls");
				p2->board_print();
				cout << "----------------------------------------------------------------------------\n";
				this->board_print(b);
				cout << "\n\nХод противника:\n   ";
				cout << "Попадание\n\n";
				system("pause");
			}
			if (this->right == 0) {//проверка направо
				a = shoot;
				if (a.y < 9) {
					a.y++;
					check = p2->shot(a);
				}
				else
					check = HITTED;

				this->right = 1;

				while (check == HIT) {
					p2->hp--;

					system("cls");
					p2->board_print();
					cout << "----------------------------------------------------------------------------\n";
					this->board_print(b);
					cout << "\n\nХод противника:\n   ";
					cout << "Попадание\n\n";
					system("pause");

					if (a.y < 9) {
						a.y++;
						check = p2->shot(a);
					}
					else
						break;
				}
				if (check == MISS) {
					system("cls");
					p2->board_print();
					cout << "----------------------------------------------------------------------------\n";
					this->board_print(b);
					cout << "\n\nХод противника:\n   ";
					cout << "Промах\n\n";
					system("pause");
					return 1;
				}
			}
			else if (this->right != 0 && this->left == 0) {//проверка налево(не запускается если весь корабль был справа)
				a = shoot;
				if (a.y > 0) {
					a.y--;
					check = p2->shot(a);
				}
				else
					check = HITTED;

				this->left = 1;

				if (check == MISS) {
					system("cls");
					p2->board_print();
					cout << "----------------------------------------------------------------------------\n";
					this->board_print(b);
					cout << "\n\nХод противника:\n   ";
					cout << "Промах\n\n";
					system("pause");
					return 1;
				}

				while (check == HIT) {
					p2->hp--;
					system("cls");
					p2->board_print();
					cout << "----------------------------------------------------------------------------\n";
					this->board_print(b);
					cout << "\n\nХод противника:\n   ";
					cout << "Попадание\n\n";
					system("pause");
					if (a.y > 0) {
						a.y--;
						check = p2->shot(a);
					}
					else
						break;
				}
			}
			else if (this->down == 0) {//проверка вниз(не запускается, если корабль стоит горизонтально)
				a = shoot;
				if (a.x < 9) {
					a.x++;
					check = p2->shot(a);
				}
				else
					check = HITTED;

				this->down = 1;

				while (check == HIT) {
					p2->hp--;
					system("cls");
					p2->board_print();
					cout << "----------------------------------------------------------------------------\n";
					this->board_print(b);
					cout << "\n\nХод противника:\n   ";
					cout << "Попадание\n\n";
					system("pause");

					if (a.x < 9) {
						a.x++;
						check = p2->shot(a);
					}
					else
						break;
				}
				if (check == MISS) {
					system("cls");
					p2->board_print();
					cout << "----------------------------------------------------------------------------\n";
					this->board_print(b);
					cout << "\n\nХод противника:\n   ";
					cout << "Промах\n\n";
					system("pause");
					return 1;
				}
			}
			else if (this->down != 0 && this->up == 0) {//проверка вверх(не запускается если весь корабль был снизу)
				a = shoot;
				a.x--;
				check = p2->shot(a);
				this->up = 1;

				while (check == HIT) {
					p2->hp--;
					system("cls");
					p2->board_print();
					cout << "----------------------------------------------------------------------------\n";
					this->board_print(b);
					cout << "\n\nХод противника:\n   ";
					cout << "Попадание\n\n";
					system("pause");

					a.x--;
					check = p2->shot(a);
				}
			}
		}
		if (check == KILL) {
			shoot.x = -1;
			shoot.y = -1;
			this->right = 0;
			this->left = 0;
			this->up = 0;
			this->down = 0;
			p2->hp--;
			system("cls");
			p2->board_print();
			cout << "----------------------------------------------------------------------------\n";
			this->board_print(b);
			cout << "\n\nХод противника:\n   ";
			cout << "Потопил\n\n";
			system("pause");
			if (p2->check_win() == 0) {
				return 0;
			}
		}
	}
}
