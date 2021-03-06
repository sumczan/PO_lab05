// PO_05_skonczone.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include "pch.h"
#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

class Item
{
private:
	string Item_name;
	int Item_value;

public:

	void Item_setname(string Item_name)
	{
		this->Item_name = Item_name;
	}

	void Item_setvalue(int Item_value)
	{
		this->Item_value = Item_value;
	}

	string Item_getname()
	{
		return this->Item_name;
	}

	int Item_getvalue()
	{
		return this->Item_value;
	}

};

class Room
{
private:
	int x = 0;
	int y = 0;
	string desc = "smth";
	Room* north = nullptr;
	Room* south = nullptr;
	Room* east = nullptr;
	Room* west = nullptr;
	Item* item = nullptr;

public:

	void Room_setx(int X)
	{
		this->x = X;
	}

	void Room_sety(int Y)
	{
		this->y = Y;
	}

	void Room_setdesc(string T)
	{
		this->desc = T;
	}

	void Room_setnorth(Room* id)
	{
		this->north = id;
	}

	void Room_setsouth(Room* id)
	{
		this->south = id;
	}

	void Room_seteast(Room* id)
	{
		this->east = id;
	}

	void Room_setwest(Room* id)
	{
		this->west = id;
	}

	void Room_setitem(Item* item)
	{
		this->item = item;
	}

	string Room_getdesc()
	{
		return this->desc;
	}

	Room* Room_gonorth()
	{
		return this->north;
	}

	Room* Room_gosouth()
	{
		return this->south;
	}

	Room* Room_goeast()
	{
		return this->east;
	}

	Room* Room_gowest()
	{
		return this->west;
	}

	bool Room_checkitem()
	{
		if (this->item != nullptr)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	Item* Room_getitem()
	{
		return this->item;
	}
};

int random_x()
{
	return (rand() % 3);
}

int random_y()
{
	return (rand() % 6);
}

int main()
{
	srand(time(0));
	Room* map[6][3];
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			map[i][j] = new Room;
		}
	}

	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (j - 1 > -1) map[i][j]->Room_setnorth(map[i][j - 1]);
			if (j + 1 < 3)  map[i][j]->Room_setsouth(map[i][j + 1]);
			if (i + 1 < 6)	map[i][j]->Room_seteast(map[i + 1][j]);
			if (i - 1 > -1) map[i][j]->Room_setwest(map[i - 1][j]);

			map[i][j]->Room_setx(i);
			map[i][j]->Room_sety(j);
		}
	}

	map[1][0]->Room_seteast(nullptr);
	map[2][0]->Room_seteast(nullptr);
	map[4][1]->Room_seteast(nullptr);
	map[1][2]->Room_seteast(nullptr);
	map[2][2]->Room_seteast(nullptr);

	map[2][0]->Room_setwest(nullptr);
	map[3][0]->Room_setwest(nullptr);
	map[5][1]->Room_setwest(nullptr);
	map[2][2]->Room_setwest(nullptr);
	map[3][2]->Room_setwest(nullptr);

	for (int j = 0; j < 3; j++)
	{
		if (j == 1)
		{
			cout << "X";
		}
		for (int i = 0; i < 6; i++)
		{
			if (i == 1 && map[i][j]->Room_gowest() == nullptr)
			{
				cout << "X";
			}

			cout << "#";

			if (i != 5 && map[i][j]->Room_goeast() == nullptr)
			{
				cout << "X";
			}
		}
		cout << endl;
	}

	cout << endl;

	Item* item_1 = new Item;
	item_1->Item_setname("Pistol 10mm");
	item_1->Item_setvalue(121);

	Item* item_2 = new Item;
	item_2->Item_setname("Stimpak");
	item_2->Item_setvalue(50);

	Item* item_3 = new Item;
	item_3->Item_setname("Fatman");
	item_3->Item_setvalue(999);

	map[random_x()][random_y()]->Room_setitem(item_1);
	map[random_x()][random_y()]->Room_setitem(item_2);
	map[random_x()][random_y()]->Room_setitem(item_3);

	Room* whereami = map[0][0];
	char trip[23] = { 'e', 's', 's', 'w', 'e', 'n', 'e', 'e', 's', 'n', 'n', 's', 'e', 'e', 'n', 'e', 'e', 'w', 'w', 's', 's', 'e', 'e' };

	int i = 0;
	int step = 0;

	do {

		if (whereami != nullptr) {
			if (whereami->Room_checkitem())
				cout << whereami->Room_getitem()->Item_getname()
				<< " Steps: " << step << endl;
		}

		switch (trip[i]) {
		case 'n':
			if (whereami->Room_gonorth() != nullptr) {
				whereami = whereami->Room_gonorth();
				step++;
			}
			break;
		case 'e':
			if (whereami->Room_goeast() != nullptr) {
				whereami = whereami->Room_goeast();
				step++;
			}
			break;
		case 's':
			if (whereami->Room_gosouth() != nullptr) {
				whereami = whereami->Room_gosouth();
				step++;
			}
			break;
		case 'w':
			if (whereami->Room_gowest() != nullptr) {
				whereami = whereami->Room_gowest();
				step++;
			}
			break;
		}
		i++;
	} while (i < 22);

	cout << endl;

	for (int j = 0; j < 3; j++)
	{
		if (j == 1)
		{
			cout << "X";
		}
		for (int i = 0; i < 6; i++)
		{
			if (i == 1 && map[i][j]->Room_gowest() == nullptr)
			{
				cout << "X";
			}

			if (map[i][j]->Room_checkitem())
			{
				cout << map[i][j]->Room_getitem()->Item_getname()[0];
			}
			else
			{
				cout << "#";
			}

			if (i != 5 && map[i][j]->Room_goeast() == nullptr)
			{
				cout << "X";
			}
		}
		cout << endl;
	}

	cout << step;

	getchar();
	getchar();
	return 0;
}


