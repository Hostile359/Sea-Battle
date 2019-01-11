#include "game.h"

Board::Board(int hp)
{
	this->hp = hp;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			this->deck[i][j] = Blue;
		}
	}
}

void Board::board_print()
{
	cout << "Ваша доска \t\tУ вас осталось " << this->hp <<" жизней\n\n";
	for (int i = 0; i < 10; i++)
		cout << "  " << i;
	cout << endl;
	for (int i = 0; i < 10; i++) {
		cout << i;
		for (int j = 0; j < 10; j++) {
			SetColor(LightGray, deck[i][j]);
			cout << "[ ]";
			SetColor(White, Black);
		}
		cout << endl;
	}
}

void Board::board_print(Point a)
{
	cout << "Доска противника \t\tУ противника осталось " << this->hp << " жизней\n\n";
	for (int i = 0; i < 10; i++)
		cout << "  " << i;
	cout << endl;
	for (int i = 0; i < 10; i++) {
		cout << i;
		for (int j = 0; j < 10; j++) {
			if (i == a.x && j == a.y) {
				if (deck[i][j] == Cyan)
					SetColor(Green, Blue);
				else
					SetColor(Green, deck[i][j]);
				cout << "[+]";
				SetColor(White, Black);
			}
			else {
				if(deck[i][j] == Cyan)
					SetColor(Brown, Blue);
				else
					SetColor(Brown, deck[i][j]);
				cout << "[ ]";
				SetColor(White, Black);
			}
		}
		cout << endl;
	}
}

void Board::board_print(Ship a)
{
	system("cls");
	for (int i = 0; i < 10; i++)
		cout << "  " << i;
	cout << endl;
	for (int i = 0; i < 10; i++) {
		cout << i;
		for (int j = 0; j < 10; j++) {
			if (a.dir == VER && i >= a.x && i <= a.x + a.size - 1 && j == a.y
				|| a.dir == HOR && i == a.x && j >= a.y && j <= a.y + a.size - 1) {
				if (deck[i][j] == Cyan) {
					SetColor(Black, Red);
				}
				else {
					SetColor(Brown, Cyan);
				}
				cout << "[ ]";
				SetColor(White, Black);
			}
			else {
				SetColor(Brown, deck[i][j]);
				cout << "[ ]";
				SetColor(White, Black);
			}
		}
		cout << endl;
	}
}

int Board::set_ship(Ship a)
{
	for (int i = 0; i < a.size + 2; i++) {
		if (a.dir == HOR) {
			if (a.y - 1 + i >= 0 && a.y - 1 + i <= 9) {
				if (deck[a.x][a.y - 1 + i] == Cyan)
					return 0;
				else if (a.x - 1 >= 0 && deck[a.x - 1][a.y - 1 + i] == Cyan)
					return 0;
				else if (a.x + 1 <= 9 && deck[a.x + 1][a.y - 1 + i] == Cyan)
					return 0;
			}
		}
		else if (a.dir == VER) {
			if (a.x - 1 + i >= 0 && a.x - 1 + i <= 9) {
				if (deck[a.x - 1 + i][a.y] == Cyan)
					return 0;
				else if (a.y - 1 >= 0 && deck[a.x - 1 + i][a.y - 1] == Cyan)
					return 0;
				else if (a.y + 1 <= 9 && deck[a.x - 1 + i][a.y + 1] == Cyan)
					return 0;

			}
		}
	}

	for (int i = 0; i < a.size; i++) {
		if (a.dir == HOR) {
			deck[a.x][a.y + i] = Cyan;
		}
		else if (a.dir == VER) {
			deck[a.x + i][a.y] = Cyan;
		}
	}
	return 1;
}

int Board::check_status(Point a, int dir)
{
	int i = 0, hp = 0;
	int x, y;
	
		for (int j = 0, x = a.x, y = a.y; j < 4; j++, x--) {
			if (x < 0 || this->deck[x][y] == Yellow || this->deck[x][y] == Blue)
				break;
			if (this->deck[x][y] == Cyan)
				hp++;
		}

		for (int j = 0, x = a.x, y = a.y; j < 4; j++, x++) {
			if (x > 9 || this->deck[x][y] == Yellow || this->deck[x][y] == Blue)
				break;
			if (this->deck[x][y] == Cyan)
				hp++;
		}
	
	
		for (int j = 0, x = a.x, y = a.y; j < 4; j++, y--) {
			if (y < 0 || this->deck[x][y] == Yellow || this->deck[x][y] == Blue)
				break;
			if (this->deck[x][y] == Cyan)
				hp++;
		}

		for (int j = 0, x = a.x, y = a.y; j < 4; j++, y++) {
			if (y > 9 || this->deck[x][y] == Yellow || this->deck[x][y] == Blue)
				break;
			if (this->deck[x][y] == Cyan)
				hp++;
		}
	
	if (hp > 0)
		return HIT;
	else {
			for (int j = 0, x = a.x, y = a.y; j <= 4; j++, x--) {
				if (x < 0)
					break;
				else if (this->deck[x][y] == Blue || this->deck[x][y] == Yellow) {
					this->deck[x][y] = Yellow;
					if (y > 0)
						this->deck[x][y - 1] = Yellow;
					if (y < 9)
						this->deck[x][y + 1] = Yellow;
					break;
				}
				if (y > 0 && this->deck[x][y - 1] != Red && this->deck[x][y - 1] != Cyan)
					this->deck[x][y - 1] = Yellow;
				if (y < 9 && this->deck[x][y + 1] != Red && this->deck[x][y + 1] != Cyan)
					this->deck[x][y + 1] = Yellow;
			}

			for (int j = 0, x = a.x, y = a.y; j <= 4; j++, x++) {
				if (x > 9)
					break;
				else if (this->deck[x][y] == Blue || this->deck[x][y] == Yellow) {
					this->deck[x][y] = Yellow;
					if (y > 0)
						this->deck[x][y - 1] = Yellow;
					if (y < 9)
						this->deck[x][y + 1] = Yellow;
					break;
				}
				if (y > 0 && this->deck[x][y - 1] != Red && this->deck[x][y - 1] != Cyan)
					this->deck[x][y - 1] = Yellow;
				if (y < 9 && this->deck[x][y + 1] != Red && this->deck[x][y + 1] != Cyan)
					this->deck[x][y + 1] = Yellow;
			}
		
			for (int j = 0, x = a.x, y = a.y; j <= 4; j++, y--) {
				if (y < 0)
					break;
				else if (this->deck[x][y] == Blue || this->deck[x][y] == Yellow) {
					this->deck[x][y] = Yellow;
					if (x > 0)
						this->deck[x - 1][y] = Yellow;
					if (x < 9)
						this->deck[x + 1][y] = Yellow;
					break;
				}
				if (x > 0 && this->deck[x - 1][y] != Red && this->deck[x - 1][y] != Cyan)
					this->deck[x - 1][y] = Yellow;
				if (x < 9 && this->deck[x + 1][y] != Red && this->deck[x + 1][y] != Cyan)
					this->deck[x + 1][y] = Yellow;
			}

			for (int j = 0, x = a.x, y = a.y; j <= 4; j++, y++) {
				if (y > 9)
					break;
				else if (this->deck[x][y] == Blue || this->deck[x][y] == Yellow) {
					this->deck[x][y] = Yellow;
					if (x > 0)
						this->deck[x - 1][y] = Yellow;
					if (x < 9)
						this->deck[x + 1][y] = Yellow;
					break;
				}
				if (x > 0 && this->deck[x - 1][y] != Red && this->deck[x - 1][y] != Cyan)
					this->deck[x - 1][y] = Yellow;
				if (x < 9 && this->deck[x + 1][y] != Red && this->deck[x + 1][y] != Cyan)
					this->deck[x + 1][y] = Yellow;
			}
		
		return KILL;
	}
}

int Board::shot(Point a)
{
	if (this->deck[a.x][a.y] == Yellow || this->deck[a.x][a.y] == Red)
		return HITTED;
	else if (this->deck[a.x][a.y] == Blue) {
		this->deck[a.x][a.y] = Yellow;
		return MISS;
	}
	else if (this->deck[a.x][a.y] == Cyan) {
		this->deck[a.x][a.y] = Red;
		return check_status(a, 0);
	}
}