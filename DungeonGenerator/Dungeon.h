#ifndef DUNGEON_H
#define DUNGEON_H

#include <random>
#include <iostream>
#include <cmath>
#include <vector>

enum Direction
{
	North,
	South,
	West,
	East,
	DirectionCount
};

struct Room
{
	int x, y;
	int width, height;
	Direction dir;
	int door_x, door_y;
};

struct Tile
{
	bool wall = false;
	bool reserved = false;
	bool exit = false;
	int gold = 0;
};

class Dungeon
{
public:
	Dungeon(int width, int height, int offset);
	~Dungeon();

	void show();
	void gen(int totalRooms);
	void refresh();

private:
	void setWall(int x, int y, bool wall);
	void setRes(int x, int y, bool state);
	void setGold(int x, int y, int gold);
	void setExit(int x, int y, bool state);

	bool getWall(int x, int y);
	bool getResStatus(int x, int y);
	int getGold(int x, int y);
	bool getExit(int x, int y);
	int getRand(int min, int max);

	bool makeDoor(Room &obj);
	bool makeRoom(int x, int y, Direction dir);
	bool place(Room &obj);
	bool placeGold(int goldPlaces, int totalGold);
	bool placeExit();
	
	int _width, _height, _offset, _roomCount;
	std::vector<std::vector<Tile>> dungeon_map;
	std::vector<Room> _rooms;

	uint32_t level = 1;
	uint64_t min_gold = 1000;
};

#endif
