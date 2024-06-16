#pragma once
#include"parameter.h"
#include"grid.h"
#include"container.h"
#include<vector>
#include<functional>
#include<stdint.h>
#include<stdint.h>
#include<queue>

struct XY {
	uint8_t x;
	uint8_t y;
	friend bool operator==(const XY& a,const XY&b);
};
struct CellCost {
	XY xy;
	int cost;
};

class StepMap {
private:
	XY start_xy;
	XY goal_xy;
public:
	StepMap(XY s,XY g);
	void update_stepmap(Grid_t& maze);
};
/*class Dijikstr_t {
private:
	Grid_t* maze;
	uint8_t start_index;
	uint8_t goal_index;
	std::vector<uint16_t> dist;
	std::vector<uint8_t> path;
public:
};


typedef struct dijikstr {
	Grid_* user;
	uint8_t start_index;
	uint8_t goal_index;
	uint16_t dist[WID * HIG];
	uint8_t path[WID * HIG];
}Dijikstr_;

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


	void from_index_to_coordinate(int i, int* x, int* y);/////////////
	void from_index_to_index(int index_from, int dx, int dy, int* to_index);///////////////
	void from_coordinate_to_index(int x, int y, int* i);/////////////////

	int shortcut_judge(int index);/////////////////
	int evalu(int index);///////////////
	int evalu(int x,int y);/////////////
public:
	Dijikstr(Grid* u, int sx, int sy, int gx, int gy);/////////////
	Dijikstr(Grid* u,int s_index,int g_index);/////////////
	void dijikstr();///////////////////
	int get_cost(int index);/////////
	int get_cost(int x,int y);///////////////
	void step_back(int index1, int index2);/////////////
	vector<int> step_back2(int index1, int index2);/////////////
	vector<int> get_a_start_path();////////////

};

void Dijikstr_constructor(Dijikstr_* this_, Grid_* u);
uint8_t Dijikstr_ind2ind(uint8_t frm_i, int8_t dx, int8_t dy);
void Dijikstr_dijikstr(Dijikstr_* this_);*/
