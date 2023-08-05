#include <iostream>
#include <string>
#include <ctime>
#include <vector>
#include <conio.h>
#include <fstream>

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

	setup_rand_position_and_parametr(character, enemies, fruit);
}

void menu(Character& character, std::vector<Enemy>& enemies,
	Dir& dir, Fruit& fruit, std::ifstream& load, bool& gameOver)
{
	std::string choose;

	while (choose != "Begin" && choose != "begin" && 
		choose != "Load" && choose != "load")
	{
		std::cout << "Begin - Start the game." << std::endl;
		std::cout << "Load - Load the game." << std::endl;
		std::getline(std::cin, choose);

		if (choose == "Load" || choose == "load")
		{
			load.open("..\\savefile.bin", std::ios::binary);
			if (!load.is_open())
			{
				std::cout << "No data saved. " << std::endl;
				std::cout << "Would you like to start a new game ?(yes or no)" << "\n:";
				std::getline(std::cin, choose);
				if (choose == "No" || choose == "no")
				{
					gameOver = true;
					return;
				}
				else if (choose == "Yes" || choose == "yes")
				{

				}
				else
				{

				}
			}
		}
		else if (choose == "Begin" || choose == "begin")
			setup(character, enemies, dir, fruit, load, gameOver);
		else 
			std::cerr << "Error! You can only choose begin or load. " << std::endl;
	}
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

void logic(Character& character, std::vector<Enemy>& enemies, Dir& dir, bool& gameOver, Fruit& fruit)
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
			" \n\n\n\n\n\t\t\t\t\t\tYou have won! " << std::endl;
		gameOver = true;
	}
}

int main()
{
	srand(time(NULL));
	Character player;
	Fruit fruit;
	std::vector<Enemy> enemies(5);
	Dir dir;
	bool gameOver = false;
	std::ofstream save;
	std::ifstream load;

	menu(player, enemies, dir, fruit, load, gameOver);
	if (!gameOver)
	{
		draw(player, enemies, fruit);
		while (!gameOver)
		{
			input(player, dir);
			logic(player, enemies, dir, gameOver, fruit);
		}
	}
	

	return 0;
}