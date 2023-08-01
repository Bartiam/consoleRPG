#include <iostream>
#include <string>
#include <ctime>
#include <vector>

const int ROW = 20;
const int COL = 20;

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

void setup(Character& character, std::vector<Enemy>& enemies)
{
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

	character.x = rand() % (ROW - 1) + 1;
	character.y = rand() % (COL - 1) + 1;

	for (int i = 0; i < enemies.size(); ++i)
	{
		enemies[i].name = "Enemy #" + std::to_string(i + 1);
		enemies[i].HP = rand() % 100 + 50;
		enemies[i].armor = rand() % 50;
		enemies[i].damage = rand() % 15 + 15;
	}

	for (int i = 0; i < enemies.size(); ++i)
	{
		enemies[i].x = rand() % (ROW - 1) + 1;
		enemies[i].y = rand() % (COL - 1) + 1;

		if ((enemies[i].x == character.x) && (enemies[i].y == character.y))
		{
			--i;
			continue;
		}

		for (int j = 0; j < i; ++j)
			if ((enemies[i].x == enemies[j].x) && (enemies[i].y == enemies[j].y)) --i;
	}
}

void insertion_sort_for_enemies(std::vector<Enemy>& enemies)
{
	int tempX, tempY;
	for (int i = 1; i < enemies.size(); ++i)
	{
		int j = i - 1;
		tempX = enemies[i].x;
		tempY = enemies[i].y;
		while (j >= 0 && enemies[j].x > tempX)
		{
			enemies[j + 1].x = enemies[j].x;
			enemies[j + 1].y = enemies[j].y;
			--j;
		}
		enemies[j + 1].x = tempX;
		enemies[j + 1].y = tempY;
	}
}

void draw(const Character& character, const std::vector<Enemy>& enemies)
{
	int itEnemy = 0;
	for (int i = 0; i < ROW; ++i)
	{
		for (int j = 0; j < COL; ++j)
		{
			if (j == 0 || j == (COL - 1) ||
				i == 0 || i == (ROW - 1))
			{
				std::cout << '#';
			}
			else if (character.x == i && character.y == j)
			{
				std::cout << 'P';
			}
			else if (enemies[itEnemy].x == i && enemies[itEnemy].y == j)
			{
				std::cout << 'E';
				if (itEnemy < 4)
				{
					++itEnemy;
				}
			}
			else std::cout << ' ';
		}
		std::cout << std::endl;
	}
}

int main()
{
	srand(time(NULL));
	Character player;
	std::vector<Enemy> enemies(5);
	setup(player, enemies);
	insertion_sort_for_enemies(enemies);
	draw(player, enemies);
	

	return 0;
}