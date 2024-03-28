#pragma once
#include"parameter.h"
#include"grid.h"
#include"container.h"
#include<vector>
#include<functional>

class Dijikstr {
private:
	Grid* user;
	std::vector<int> path;
	std::vector<int> dist;
	int direction[4][2];
	int start_index;//開始マス
	int goal_index;//ゴールマス
	//std::function<int(int, int)>evalu;
	//std::function<int(int, int, int)>evalu;


	void from_index_to_coordinate(int i, int* x, int* y);
	void from_index_to_index(int index_from, int dx, int dy, int* to_index);
	void from_coordinate_to_index(int x, int y, int* i);

	int shortcut_judge(int index);
	int evalu(int index);
	int evalu(int x,int y);
public:
	Dijikstr(Grid* u, int sx, int sy, int gx, int gy);
	Dijikstr(Grid* u,int s_index,int g_index);
	void dijikstr();
	int get_cost(int index);
	int get_cost(int x,int y);
	void step_back(int index1, int index2);
	vector<int> step_back2(int index1, int index2);
	vector<int> get_a_start_path();

};