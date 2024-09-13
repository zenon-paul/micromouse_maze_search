#include"stepmap.h"
#include"grid.h"
#include<queue>
#include<stack>

std::stack<XY> route;

StepMap::StepMap()
	:stepmap(std::vector<std::vector<uint16_t>>(field_size, std::vector<uint16_t>(field_size, max))){}

uint16_t StepMap::get_step(XY xy) {
	if (xy.x < 0 || xy.y < 0) {
		return max;
	}
	if (xy.x >= field_size || xy.y >= field_size) {
		return max;
	}
	return this->stepmap[xy.y][xy.x];
}

uint16_t StepMap::get_step(int8_t x, int8_t y) {
	if (x < 0 || y < 0) {
		return max;
	}
	if (x >= field_size || y >= field_size) {
		return max;
	}
	return this->stepmap[y][x];
}

void StepMap::set_step(XY xy,uint16_t val) {
	if (xy.x < 0 || xy.y < 0) {
		return;
	}
	if (xy.x >= field_size || xy.y >= field_size) {
		return;
	}
	this->stepmap[xy.y][xy.x] = val;
}

void StepMap::set_step(int8_t x, int8_t y, uint16_t val) {
	if (x < 0 || y < 0) {
		return;
	}
	if (x >= field_size || y >= field_size) {
		return;
	}
	this->stepmap[y][x] = val;
}

void calculate_stepmap(StepMap& cost_table,const Maze& maze,const XY& start_xy, const XY& goal_xy){//これが足立法の1ステップ
	
	auto comp = [](const CellCost& b, const CellCost& a)->bool {
		return a.cost < b.cost;//昇順で並べ替え
	};
	std::priority_queue < CellCost, std::vector<CellCost>, std::function<bool(const CellCost&, const CellCost&) >> pri_queue(comp);
	//----------------------------------
	cost_table.set_step(start_xy,0);
	CellCost s{ start_xy, 0 };
	pri_queue.push(s);
	while (!pri_queue.empty()) {
		CellCost parent = pri_queue.top();
		pri_queue.pop();
		if (parent.cost > cost_table.get_step(parent.xy)) {
			continue;
		}
		if (parent.xy == goal_xy) {
			printf("goal!\n");
			break;//ゴール判定
		}
		for (int i = 0; i < 4;i++) {
			if (maze.get_wall_status_xyd(parent.xy, i) == WALL_SEEN) {
				continue;
			}
			XY ch_xy = parent.xy + directions[i];
			int ch_cost = parent.cost + 1;
			if (ch_cost < cost_table.get_step(ch_xy)) {
				CellCost child{ch_xy,ch_cost};
				pri_queue.push(child);
				cost_table.set_step(ch_xy,ch_cost);
			}
		}
	}
	for (int i = 0; i < FIELDSIZE; i++) {
		for (int j = 0; j < FIELDSIZE; j++) {
			if (cost_table.get_step(j,i) == StepMap::max) {
				printf(" INF  ");
			}
			else {
				printf("%5d ", cost_table.get_step(j,i));
			}
		}
		printf("\n");
	}
	printf("\n");
}


std::vector<std::vector<int>> calculate_stepmap(const Maze& maze,XY start_xy,XY goal_xy){//これが足立法の1ステップ

	std::vector<std::vector<int>> cost_table(FIELDSIZE,std::vector<int>(FIELDSIZE,StepMap::max));////
	std::vector<std::vector<XY>> path(FIELDSIZE, std::vector<XY>(FIELDSIZE));
	auto comp = [](const CellCost& b, const CellCost& a)->bool {
		return a.cost < b.cost;//昇順で並べ替え
	};
	std::priority_queue < CellCost, std::vector<CellCost>, std::function<bool(const CellCost&, const CellCost&) >> pri_queue(comp);
	//-----------------------------
	cost_table[start_xy.y][start_xy.x] = 0;
	path[start_xy.y][start_xy.x] = start_xy;
	CellCost s{ start_xy, 0 };
	pri_queue.push(s);
	while (!pri_queue.empty()) {
		CellCost parent = pri_queue.top();
		pri_queue.pop();
		int8_t pa_x = parent.xy.x;
		int8_t pa_y = parent.xy.y;
		if (parent.cost > cost_table[pa_y][pa_x]) {
			continue;
		}
		if(parent.xy == goal_xy) {
			printf("goal!\n");
			break;//ゴール判定
		}
		for (int i = 0; i < 4;i++) {
			if (maze.get_wall_status_xyd(pa_x,pa_y,i)==WALL_SEEN) {
				continue;
			}
			XY ch_xy = parent.xy + directions[i];
			//XY ch_xy{ pa_x + direction[i][0],pa_y + direction[i][1] };
			int ch_cost = parent.cost + 1;
			if (ch_cost < cost_table[ch_xy.y][ch_xy.x]) {
				CellCost child{ch_xy,ch_cost};
				pri_queue.push(child);
				cost_table[ch_xy.y][ch_xy.x] = ch_cost;
				path[ch_xy.y][ch_xy.x] = parent.xy;
			}
		}
	}
	for (int i = 0; i < FIELDSIZE; i++) {
		for (int j = 0; j < FIELDSIZE; j++) {
			if (cost_table[i][j] == StepMap::max) {
				printf(" INF  ");
			}
			else {
				printf("%5d ", cost_table[i][j]);
			}
		}
		printf("\n");
	}
	printf("\n");
	return cost_table;
}
