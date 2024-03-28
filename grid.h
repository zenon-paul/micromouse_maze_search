#pragma once
#define WID 16
#define HIG 16
#define X_DISPLACEMENT 150
#define Y_DISPLACEMENT 120
#define EGSIZE 16

#include"container.h"
#include<vector>
#include<string>
using namespace std;

enum { S, N, W, E };


class Grid {
private:
public:
	int hight;
	int width;
	char* cell;
	int** ver_wall;
	int** hor_wall;
	int direction[4][2];
	int current_index;//
	int prev_index;//

	unsigned int mask[4];

	Grid(int h, int w);
	~Grid();
	void from_index_to_coordinate(int i, int* x, int* y);
	void from_coordinate_to_index(int x, int y, int* i);


	int get_wall_status(int x, int y, int dir);
	int get_wall_status(int index, int dir);
	int get_cell_status(int x, int y);
	int get_cell_status(int index);
	void set_wall_status(int x, int y, int dir,int val);
	void set_wall_status(int index,int dir,int val);
	void set_cell_status(int x, int y,int val);
	void set_cell_status(int index,int val);


	void clean_wall(Grid* user);
	void clean_cell(Grid* user);
	void geo_cell();
	void geo_wall();

	void set_maze(int** map);
	void set_maze(string file_name);
	//void a_star(d2_prqueue* x,int* dist);
	//int get_a_start_path();
};
