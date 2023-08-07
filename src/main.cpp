#include <iostream>
#include <string>
#include <ctime>
#include <vector>
#include <conio.h>
#include <fstream>

const int ROW = 20;
const int COL = 50;
char map[ROW][COL];

enum Dir { STOP = 0,LEFT,RIGHT,UP,DOWN, KEY_ESC = 27};

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

struct Fruit
{
	int plusHP;
	int x, y;
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

void setup_rand_position_and_parametr(Character& character, std::vector<Enemy>& enemies, Fruit& fruit)
{
	for (int i = 0; i < 1; ++i)
	{
		character.x = rand() % (ROW - 2) + 1;
		character.y = rand() % (COL - 2) + 1;
		fruit.x = rand() % (ROW - 2) + 1;
		fruit.y = rand() % (ROW - 2) + 1;
		if (character.x == fruit.x) --i;
	}

	fruit.plusHP = rand() % 30 + 20;

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

		if ((enemies[i].x == character.x) || (enemies[i].x == fruit.x))
		{
			--i;
			continue;
		}

		for (int j = 0; j < i; ++j)
			if ((enemies[i].x == enemies[j].x) || (enemies[i].y == enemies[j].y)) --i;
	}
}

void setup(Character& character, std::vector<Enemy>& enemies, 
	Dir& dir, Fruit& fruit, std::ifstream& load, bool& gameOver)
{
	dir = STOP;
	
	enemies.resize(5);

	std::cout << "\n\n\n\n\t\t\t\t\t\tEnter a character name: ";
	std::cin >> character.name;
	while (!is_correct_name(character.name))
	{
		std::cout << "\t\t\t\t\t\tError! Incorrect intup name. Try again." << std::endl;
		std::cout << "\t\t\t\t\t\tEnter a character name: ";
		std::cin >> character.name;
	}

	std::cout << "\t\t\t\t\t\tEnter the number of HP of the character: ";
	std::cin >> character.HP;
	while (!is_correct_HP_armor_damage(character.HP))
	{
		std::cout << "\t\t\t\t\t\tError! Incorrect intup HP. Try again." << std::endl;
		std::cin >> character.HP;
	}

	std::cout << "\t\t\t\t\t\tEnter the number of armor of the character: ";
	std::cin >> character.armor;
	while (!is_correct_HP_armor_damage(character.armor))
	{
		std::cout << "\t\t\t\t\t\tError! Incorrect intup armor. Try again." << std::endl;
		std::cin >> character.armor;
	}

	std::cout << "\t\t\t\t\t\tEnter the number of damage of the character: ";
	std::cin >> character.damage; 
	while (!is_correct_HP_armor_damage(character.damage))
	{
		std::cout << "\t\t\t\t\t\tError! Incorrect intup damage. Try again." << std::endl;
		std::cin >> character.damage;
	}

	setup_rand_position_and_parametr(character, enemies, fruit);

	std::cout << "\t\t\t\t\t\tCharacter management:" << 
		"\n\t\t\t\t\t\tLeft - A. " << 
		"\n\t\t\t\t\t\tRight - D." <<
		"\n\t\t\t\t\t\tUp - W." <<
		"\n\t\t\t\t\t\tDown - S." << 
		"\n\t\t\t\t\t\tPause - ESC.\n" << std::endl;
	system("pause");
}

void draw(const Character& character, const std::vector<Enemy>& enemies, Fruit& fruit)
{
	system("cls");

	std::cout << "Character HP: " << character.HP << "\nCharacter armor: " <<
		character.armor << "\nCharacter damage: " << character.damage << std::endl;

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
				map[i][j] = 'P';
			else if (fruit.x == i && fruit.y == j)
				map[i][j] = 'F';
			else
				map[i][j] = ' ';
		}
	}

	for (int i = 0; i < enemies.size(); ++i)
		map[enemies[i].x][enemies[i].y] = 'e';

	for (int i = 0; i < ROW; ++i)
	{
		for (int j = 0; j < COL; ++j)
		{
			std::cout << map[i][j];
		}
		std::cout << std::endl;
	}
}

void menu(Character& character, std::vector<Enemy>& enemies, Dir& dir,
	Fruit& fruit, std::ifstream& load, bool& gameOver, std::ofstream& save)
{
	std::string choose;

	system("cls");

	while (choose != "Begin" && choose != "begin" && 
		choose != "Load" && choose != "load" && 
		choose != "Yes" && choose != "yes" &&
		choose != "Exit" && choose != "exit")
	{
		if (enemies.size() > 0)
		{
			std::cout << "\n\n\n\n\t\t\t\t\t\tContinue - Continue the game." << std::endl;
			std::cout << "\t\t\t\t\t\tBegin - Start a new game." << std::endl;
		}
		else 
			std::cout << "\n\n\n\n\t\t\t\t\t\tBegin - Start a new game." << std::endl;
		std::cout << "\t\t\t\t\t\tLoad - Load the game." << std::endl;
		std::cout << "\t\t\t\t\t\tExit - Exit the game." << std::endl << "\t\t\t\t\t\t";
		std::cin >> choose;

		if (enemies.size() > 0 && choose == "Continue" || choose == "continue")
		{
			draw(character, enemies, fruit);
			return;
		}
		else if (choose == "Load" || choose == "load")
		{
			load.open("..\\savefile.bin", std::ios::binary);
			if (!load.is_open())
			{
				while (choose != "Yes" && choose != "yes")
				{
					std::cout << "\t\t\t\t\t\tNo data saved. " << std::endl;
					std::cout << "\t\t\t\t\t\tWould you like to start a new game ?(yes or no)" << "\n\t\t\t\t\t\t:";
					std::cin >> choose;
					if (choose == "No" || choose == "no")
					{
						load.close();
						gameOver = true;
						return;
					}
					else if (choose == "Yes" || choose == "yes")
					{
						setup(character, enemies, dir, fruit, load, gameOver);
						load.close();
					}
					else
						std::cerr << "\t\t\t\t\t\tError! You can only choose yes or no. Try again." << std::endl;
				}
			}
			else
			{

			}
		}
		else if (choose == "Begin" || choose == "begin")
			setup(character, enemies, dir, fruit, load, gameOver);
		else if (choose == "Exit" || choose == "exit")
		{
			load.close();
			gameOver = true;
			return;
		}
		else 
			std::cerr << "\t\t\t\t\t\tError! You can only choose begin or load. Try again." << std::endl;

	}
}

void input(Character& character, Dir& dir)
{
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
		case 27:
			dir = KEY_ESC;
			break;
		}
	}
}

void rand_position_fruit(const Character& character, const std::vector<Enemy>& enemies, Fruit& fruit)
{
	for (int i = 0; i < enemies.size(); ++i)
	{
		fruit.x = rand() % (ROW - 2) + 1;
		fruit.y = rand() % (ROW - 2) + 1;
		if (character.x == fruit.x) --i;
		else if ((enemies[i].x == fruit.x) || (enemies[i].y == fruit.y)) --i;
	}

	fruit.plusHP = rand() % 30 + 20;
}

void logic(Character& character, std::vector<Enemy>& enemies, Dir& dir,
	bool& gameOver, Fruit& fruit, std::ifstream& load, std::ofstream& save)
{
	int x = character.x; 
	int y = character.y;

	switch (dir)
	{
	case LEFT:
		if (character.y != 1)
			--character.y;
		break;
	case RIGHT:
		if (character.y != COL -2)
			++character.y;
		break;
	case UP:
		if (character.x != 1 )
			--character.x;
		break;
	case DOWN:
		if (character.x != ROW - 2)
			++character.x;
		break;
	case KEY_ESC:
		menu(character, enemies, dir, fruit, load, gameOver, save);
		break;
	}
	dir = STOP;

	if (character.x != x || character.y != y)
	{
		int dirEnemy;
		for (int i = 0; i < enemies.size(); ++i)
		{
			dirEnemy = rand() % 5;
			switch (dirEnemy)
			{
			case 0:
				break;
			case 1:
				if (enemies[i].y != 1)
					--enemies[i].y;
				break;
			case 2:
				if (enemies[i].y != COL - 2)
					++enemies[i].y;
				break;
			case 3:
				if (enemies[i].x != 1)
					--enemies[i].x;
				break;
			case 4:
				if (enemies[i].x != ROW - 2)
					++enemies[i].x;
				break;
			}
		}
		draw(character, enemies, fruit);
	}
	
	Enemy enemy(enemies[enemies.size() - 1]);

	for (int i = 0; i < enemies.size(); ++i)
	{
		if (enemies[i].x == character.x && enemies[i].y == character.y)
		{
			enemies[i].armor -= character.damage;
			character.armor -= enemies[i].damage;
			if (enemies[i].armor < 0)
			{
				enemies[i].HP += enemies[i].armor;
				if (enemies[i].HP <= 0)
				{
					std::cout << "You won this fight! Against this opponent: " << enemies[i].name << std::endl;
					enemies[i] = enemy;
					enemies.pop_back();
					rand_position_fruit(character, enemies, fruit);
				}
			}
			if (character.armor < 0)
			{
				character.HP += character.armor;
				character.armor = 0;
				if (character.HP <= 0)
				{
					system("cls");
					std::cout << "\n\n\n\n\t\t\t\t\t\tGame over! " << std::endl;
					gameOver = true;
				}
			}
		}
		if (character.x == fruit.x && character.y == fruit.y)
		{
			character.HP += fruit.plusHP;
			fruit.x = fruit.y = 0 ;
			draw(character, enemies, fruit);
		}
	}

	if (enemies.size() == 0)
	{
		system("cls");
		std::cout << "\n\n\n\n\t\t\t\t\t\tThere are no enemies left. " <<
			"\t\t\t\t\t\tYou have won! " << std::endl;
		gameOver = true;
	}
}

int main()
{
	srand(time(NULL));
	Character player;
	Fruit fruit;
	std::vector<Enemy> enemies;
	Dir dir;
	bool gameOver = false;
	std::ofstream save;
	std::ifstream load;

	menu(player, enemies, dir, fruit, load, gameOver, save);
	if (!gameOver)
	{
		draw(player, enemies, fruit);
		while (!gameOver)
		{
			input(player, dir);
			logic(player, enemies, dir, gameOver, fruit, load, save);
		}
	}
	

	return 0;
}