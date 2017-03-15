#ifndef DUNGEON_CPP
#define DUNGEON_CPP

#include "Dungeon.h"

Dungeon::Dungeon(int width, int height, int offset)
	: _width(width)
	, _height(height)
	, _offset(offset+1)
	, dungeon_map(width, std::vector<Tile>(height))
{
	if (_offset < 1)
		_offset = 1;
	if (_width < 6)
		_width = 6;
	if (_height < 6)
		_height = 6;

}

Dungeon::~Dungeon()
{
}

//print map (if succesfully generated...)
void Dungeon::show()
{
	for (int y = 0; y < _height; ++y)
	{
		for (int x = 0; x < _width; ++x)
		{
			if (getGold(x, y) != 0)
			{
				std::cout << 'o';
				continue;
			}

			if (getExit(x, y))
			{
				std::cout << '>';
				continue;
			}

			if (getWall(x, y))
				std::cout << '#';
			else
				std::cout << '.';

		}
		std::cout << std::endl;
	}
}

void Dungeon::refresh()
{
	dungeon_map.clear();
	_rooms.clear();
	dungeon_map.resize(_width);
	for (int j = 0; j < _height; ++j)
	{
		dungeon_map[j].resize(_height);
	}
	gen(_roomCount);
}

void Dungeon::gen(int totalRooms)
{
	this->_roomCount = totalRooms;

	int roomCounter = 0;
	int goldCounter = 0;

	int goldPlaces = getRand(5,25);

	// make first room
	makeRoom(_width / 2, _height / 2, static_cast<Direction>(getRand(0, 3)));
	//makeDoor(_rooms[0]);
	roomCounter++;

	while (roomCounter < totalRooms)
	{

		//get random room from available list
		Room tmp = _rooms[getRand(0, _rooms.size() - 1)];
		//generate door for room
		makeDoor(tmp);

		// place room
		if (makeRoom(tmp.door_x, tmp.door_y, static_cast<Direction>(getRand(0, 3))))
		{
			//set door
			setWall(tmp.door_x, tmp.door_y, false);
			setRes(tmp.door_x, tmp.door_y, true);

			roomCounter++;
		}

		// last room and gold placement
		if (roomCounter == totalRooms)
		{
			//fill outer map with walls
			for (int y = 0; y < _width; ++y)
				for (int x = 0; x < _height; ++x)
					if (!getResStatus(x, y))
						setWall(x, y, true);

			// place all couples of gold
			placeGold(goldPlaces, min_gold * 2);

			// make exit
			placeExit();
		}

	}
}

void Dungeon::setWall(int x, int y, bool wall)
{
	dungeon_map[y][x].wall = wall;
}

void Dungeon::setRes(int x, int y, bool state)
{
	dungeon_map[y][x].reserved = state;
}

void Dungeon::setGold(int x, int y, int gold)
{
	dungeon_map[y][x].gold = gold;
}

void Dungeon::setExit(int x, int y, bool state)
{
	dungeon_map[y][x].exit = state;
}

bool Dungeon::getWall(int x, int y)
{
	return dungeon_map[y][x].wall;
}

bool Dungeon::getResStatus(int x, int y)
{
	return dungeon_map[y][x].reserved;
}

int Dungeon::getGold(int x, int y)
{
	return dungeon_map[y][x].gold;
}

bool Dungeon::getExit(int x, int y)
{
	return dungeon_map[y][x].exit;
}

int Dungeon::getRand(int min, int max)
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<> dist(0, max - min);
	return dist(mt) + min;
}

bool Dungeon::makeRoom(int x, int y, Direction dir)
{
	static const int minSize = 3;
	static const int maxSize = 6;

	Room room;

	room.height = getRand(minSize, maxSize);
	room.width = getRand(minSize, maxSize);
	room.dir = dir;

	if (dir == North)
	{
		room.x = x - room.width / 2;
		room.y = y - room.height;
	}
	else if (dir == South)
	{
		room.x = x - room.width / 2;
		room.y = y + 1;
	}
	else if (dir == East)
	{
		room.x = x + 1;
		room.y = y - room.height / 2;
	}
	else if (dir == West)
	{
		room.x = x - room.width;
		room.y = y - room.height / 2;
	}

	if (place(room))
		return true;
	else
		return false;
}

bool Dungeon::makeDoor(Room &room)
{
	room.dir = static_cast<Direction>(getRand(0, 3));
	if (room.dir == North)
	{
		room.door_y = room.y - 1;
		room.door_x = getRand(room.x, room.x + room.width - 1);
	}
	else if (room.dir == South)
	{
		room.door_y = room.y + room.height;
		room.door_x = getRand(room.x, room.x + room.width - 1);
	}
	else if (room.dir == East)
	{
		room.door_y = getRand(room.y, room.y + room.height - 1);
		room.door_x = room.x + room.width;
	}
	else if (room.dir == West)
	{
		room.door_y = getRand(room.y, room.y + room.height - 1);
		room.door_x = room.x - 1;
	}

	return true;
}

bool Dungeon::place(Room &obj)
{
	if (obj.x < _offset || obj.y < _offset || obj.x + obj.width > _width - _offset || obj.y + obj.height > _height - _offset)
		return false;

	//find good place for room
	for (int y = obj.y; y < obj.y + obj.height; ++y)
		for (int x = obj.x; x < obj.x + obj.width; ++x)
		{
			// if found wall
			if (getWall(x, y) != false)
				return false;
			// if found room inside
			if (getResStatus(x, y) != false)
				return false;
		}

	for (int y = obj.y - 1; y < obj.y + obj.height + 1; ++y)
		for (int x = obj.x - 1; x < obj.x + obj.width + 1; ++x)
		{
			//set room or corridor walls
			if (x == obj.x - 1 || y == obj.y - 1 || x == obj.x + obj.width || y == obj.y + obj.height)
			{
				setWall(x, y, true);
			}
			else
			{
				setWall(x, y, false);
				setRes(x, y, true);
			}
		}

	//store room
	_rooms.push_back(obj);

	return true;
}

bool Dungeon::placeGold(int goldPlaces, int totalGold)
{
	int placedCounter = 0;
	int leftgold = totalGold;

	while (placedCounter < goldPlaces)
	{
		int averageGold = leftgold / (goldPlaces-placedCounter);
		int goldPerTile = averageGold + getRand(-0.5*averageGold, 0.5*averageGold);

		if (placedCounter == goldPlaces - 1)
			goldPerTile = leftgold;

		//get random room from available list
		Room tmp = _rooms[getRand(0, _rooms.size() - 1)];

		// get random rocation in selected room
		int y = getRand(tmp.y, tmp.y + tmp.height - 1);
		int x = getRand(tmp.x, tmp.x + tmp.width - 1);

		if (getWall(x, y))
			continue;

		if (getGold(x, y) == 0)
		{
			setGold(x, y, goldPerTile);
			/*std::cout << "x: " << x << "y: " << y << " gold: " << goldPerTile << std::endl;*/
			leftgold -= goldPerTile;
			placedCounter++;
		}
		else
			continue;
	}
	return true;
}

bool Dungeon::placeExit()
{
	while (true)
	{
		//get random room from available list
		Room tmp = _rooms[getRand(1, _rooms.size() - 1)];

		// get random rocation in selected room
		int y = getRand(tmp.y, tmp.y + tmp.height - 1);
		int x = getRand(tmp.x, tmp.x + tmp.width - 1);

		if (getWall(x, y))
			continue;

		if (getGold(x, y) != 0)
			continue;

		setExit(x, y, true);
		break;
	}
	return true;
}

#endif
