#include <iostream>
#include <string>
#include <ctime>
#include <vector>
#include <conio.h>

const int ROW = 20;
const int COL = 50;
char map[ROW][COL];

enum Dir { STOP = 0,LEFT,RIGHT,UP,DOWN };

struct Character
{
public:
	std::string name = " ";
	int HP = 0;
	int armor = 0;
	int damage = 0;
	int x = 0, y = 0;
};

struct Enemy
{
public:
	std::string name = " ";
	int HP = 0;
	int armor = 0;
	int damage = 0;
	int x = 0, y = 0;
};

bool is_correct_name(const std::string& name)
{
	for (int i = 1; i < name.length(); ++i)
		if ((name[0] < 'A' || name[0] > 'Z') ||
			(name[i] < 'a' || name[i] > 'z')) return false;

	return true;
}

bool is_correct_HP_armor_damage(const int& info)
{
	if (info <= 0) return false;
	return true;
}

void setup_rand_position_and_parametr(Character& character, std::vector<Enemy>& enemies)
{
	character.x = rand() % (ROW - 2) + 1;
	character.y = rand() % (COL - 2) + 1;

	for (int i = 0; i < enemies.size(); ++i)
	{
		enemies[i].name = "Enemy #" + std::to_string(i + 1);
		enemies[i].HP = rand() % 100 + 50;
		enemies[i].armor = rand() % 50;
		enemies[i].damage = rand() % 15 + 15;
	}

	for (int i = 0; i < enemies.size(); ++i)
	{
		enemies[i].x = rand() % (ROW - 2) + 1;
		enemies[i].y = rand() % (COL - 2) + 1;

		if (enemies[i].x == character.x)
		{
			--i;
			continue;
		}
		
		for (int j = 0; j < i; ++j)
			if ((enemies[i].x == enemies[j].x) || (enemies[i].y == enemies[j].y)) --i;
	}
}

void setup(Character& character, std::vector<Enemy>& enemies, Dir& dir)
{
	dir = STOP;

	std::cout << "Enter a character name: ";
	std::getline(std::cin, character.name);
	while (!is_correct_name(character.name))
	{
		std::cout << "Error! Incorrect intup name. Try again." << std::endl;
		std::cout << "Enter a character name: ";
		std::getline(std::cin, character.name);
	}

	std::cout << "Enter the number of HP of the character: ";
	std::cin >> character.HP;
	while (!is_correct_HP_armor_damage(character.HP))
	{
		std::cout << "Error! Incorrect intup HP. Try again." << std::endl;
		std::cin >> character.HP;
	}

	std::cout << "Enter the number of armor of the character: ";
	std::cin >> character.armor;
	while (!is_correct_HP_armor_damage(character.armor))
	{
		std::cout << "Error! Incorrect intup armor. Try again." << std::endl;
		std::cin >> character.armor;
	}

	std::cout << "Enter the number of damage of the character: ";
	std::cin >> character.damage;
	while (!is_correct_HP_armor_damage(character.damage))
	{
		std::cout << "Error! Incorrect intup damage. Try again." << std::endl;
		std::cin >> character.damage;
	}

	setup_rand_position_and_parametr(character, enemies);
}

void draw(const Character& character, const std::vector<Enemy>& enemies)
{
	system("cls");
	for (int i = 0; i < ROW; ++i)
	{
		for (int j = 0; j < COL; ++j)
		{
			if (j == 0 || j == (COL - 1) ||
				i == 0 || i == (ROW - 1))
			{
				map[i][j] = '#';
			}
			else if (character.x == i && character.y == j)
			{
				map[i][j] = 'P';
			}
			else map[i][j] = ' ';
		}
	}

	for (int i = 0; i < enemies.size(); ++i)
		map[enemies[i].x][enemies[i].y] = 'E';

	for (int i = 0; i < ROW; ++i)
	{
		for (int j = 0; j < COL; ++j)
		{
			std::cout << map[i][j];
		}
		std::cout << std::endl;
	}
}

void input(Character& character, Dir& dir, std::vector<Enemy>& enemies)
{
	int dirEnemy;
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a':
			dir = LEFT;
			break;
		case 'A':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'D':
			dir = RIGHT;
			break;
		case 'w':
			dir = UP;
			break;
		case 'W':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'S':
			dir = DOWN;
			break;
		}
		
		for (int i = 0; i < enemies.size(); ++i)
		{
			dirEnemy = rand() % 5;
			switch (dirEnemy)
			{
			case 0:
				break;
			case 1:
				--enemies[i].y;
				break;
			case 2:
				++enemies[i].y;
				break;
			case 3:
				--enemies[i].x;
				break;
			case 4:
				++enemies[i].x;
				break;
			}
		}
	}
}

void logic(Character& character, std::vector<Enemy>& enemies, Dir& dir, bool& gameOver)
{
	switch (dir)
	{
	case LEFT:
		--character.y;
		break;
	case RIGHT:
		++character.y;
		break;
	case UP:
		--character.x;
		break;
	case DOWN:
		++character.x;
		break;
	}
	dir = STOP;
}

int main()
{
	srand(time(NULL));
	Character player;
	std::vector<Enemy> enemies(5);
	Dir dir;
	bool gameOver = false;

	setup(player, enemies, dir);
	while (!gameOver)
	{
		draw(player, enemies);
		input(player, dir, enemies);
		logic(player, enemies, dir, gameOver);
	}
	

	return 0;
}