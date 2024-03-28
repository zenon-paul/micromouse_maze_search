#pragma once
#include"parameter.h"
#include"grid.h"
#include"container.h"
#include<vector>

class Adati {
private:
	Grid* user;
	std::vector<int> path;
	std::vector<int> dist;
	d_stack property;
	int direction[4][2];
	int start_index;//開始マス
	int goal_index;//ゴールマス

	int parent_index;

	void from_index_to_coordinate(int i, int* x, int* y);
	void from_index_to_index(int index_from, int dx, int dy, int* to_index);
	void from_coordinate_to_index(int x, int y, int* i);

	int shortcut_judge(int index);

public:
	Adati(Grid* u);
	void set_adati(int sx, int sy, int gx, int gy);
	void adati();
	void step_back(int index1, int index2);
	vector<int> step_back2(int index1, int index2);
	vector<int> get_adati_path();

};