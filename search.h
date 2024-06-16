#pragma once
/*#include"parameter.h"
#include"grid.h"
#include"container.h"
#include<vector>

using namespace std;
class Search {
private:
	Grid* user;
	std::vector<int> path;
	std::vector<int> dist;
	d2_prqueue property;
	int direction[4][2];
	int start_index;//開始マス
	int goal_index;//ゴールマス

	int parent_index;
	int parent_t_cost;
	

	void from_index_to_coordinate(int i, int* x, int* y);
	void from_index_to_index(int index_from,int dx,int dy,int* to_index);
	void from_coordinate_to_index(int x, int y, int* i);
	int euclid_dist(int x_s, int y_s, int x_g, int y_g);
	int get_h_dist(int i, int g);



	int shortcut_judge(int index);
public:
	Search(Grid* u);
	void set_a_star(int sx, int sy, int gx, int gy);
	void a_star();
	void step_back(int index1,int index2);
	vector<int> step_back2(int index1, int index2);
	vector<int> get_a_start_path();
};*/