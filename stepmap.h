#pragma once
#include"parameter.h"
#include"grid.h"
#include<vector>
#include<functional>
#include<stdint.h>
#include<stdint.h>
#include<queue>


struct CellCost {
	XY xy;
	int cost;
};

class StepMap {
public:
	constexpr static uint8_t field_size = FIELDSIZE;
	constexpr static uint16_t max = MAXu16bit - 100;
	StepMap();
	uint16_t get_step(XY xy);
	uint16_t get_step(int8_t x,int8_t y);
	void set_step(XY xy,uint16_t val);
	void set_step(int8_t x, int8_t y,uint16_t val);
private:
	std::vector<std::vector<uint16_t>> stepmap;
};

std::vector<std::vector<int>> calculate_stepmap(const Maze& maze, XY start_xy, XY goal_xy);

void calculate_stepmap(StepMap& cost_table,const Maze& maze,const XY& start_xy,const XY& goal_xy);
