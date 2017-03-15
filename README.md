# Simple-dungeon-generator

Another small algorithm for your roguelike game level generation.

### Sample usage:
```
#include"Dungeon.h"

int main()
{
	Dungeon x(64, 64, 5); // (width, height, offset)
	x.gen(60); // Number of rooms to generate
	x.show();  // print map to stdout

	std::cout << "Enter to end... ";
	std::cin.get();

	return 0;
}
```

### Output:
```
# - wall
. - floor
o - gold placed on floor

################################################################
################################################################
################################################################
################################################################
################################################################
################################################################
###########################......###############################
#############.....#########......###############################
#############.....#########......###############################
#############.....#......##......###############################
#######............o.....##...o..###############################
#######.....#.....#......#####.#################################
#######.....#.....###.######...####################.....########
#########.##########...#####...###########...######.....########
#########...########...#####...###...#...#...######.....########
#########........###...#####...###...#.......######.....########
#########...#....###...######.####.......#...########.##########
#############....###...####...####...#...#...###......##########
#############....###...####...########...#######......##########
###############.###########...#########.########......##########
###############...o.#######...#########.....####......##########
##########...o#.....########.##########.....#######.############
######...#..........######..o.#########.....####....############
######...#....#.....######....#########.....####....############
######...########.########....###########.######....############
######o.......#...########....#####...o.#........o..############
######...#.o......#......###.######.....#......#....#...########
######...#....#...#............####............#......>.########
###############..........#...o.####....o#......######...########
###############...########.....######.#####.####################
###############...#....#####.######...##......####...###########
###################....#.....######...##..o..o####...###########
#############...###....#..o..######...##......####...###########
#############...###.....o.............##......#####.############
#############...###....#.....#....#...####.#######....##########
#############...###....####.##.o..#...###...######....##########
#############...###.#####....#....#######o..#.........##########
######......##.##....####....####.#######........#....##########
######......#...#....####....##.....#####...#....###############
######......#........####.#####.....#####...####################
######..........#....#......###.....#######.####################
######......######.###......###.....#####.....##################
######......####....##......#############.....#.....############
################....#####################o..........############
################....#.....########...####.....#.....############
################o...#.....#......#...####.....##################
################..........#..........######.####################
##################.##.....#......#...###......#...#...##########
#################...#....o.......###.###......#...#...##########
#################...##.####......#....##......#...#...##########
#################...#...###......#....##...........o..##########
#################...#.o.####.#####....##......#...#...##########
#################...#...###...####....#########...#...##########
#####################...###...#######.##########.####.##########
#####################...###...######o..##....#.....#...#########
###########################...######...##....#.....#...#########
####################################...##..........#...#########
####################################...##....#######...#########
################################################################
################################################################
################################################################
################################################################
################################################################
################################################################
```
