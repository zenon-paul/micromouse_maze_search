/*#include"search.h"
#include"grid.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<vector>

Search::Search(Grid* u):property(BUFF_SIZE),path(WID*HIG,-1),dist(WID*HIG,INF){
	user = u;
	start_index = 0;
	goal_index = 0;
	
	int d[4][2] = {///////////direction
		{0,-1},
		{0,1},
		{-1,0},
		{1,0}
	};
	for (int i = 0; i < 4;i++) {
		for (int j = 0; j < 2;j++) {
			direction[i][j] = d[i][j];
		}
	}
	parent_index = 0;
	parent_t_cost = 0;
}

int Search::shortcut_judge(int index) {
	if (index == goal_index) {
		return 1;
	}
	int count = 0;
	for (int i = 0; i < 4;i++) {
		if (user->get_wall_status(index,i) == WALL_SEEN) {
			count++;
		}
	}
	if (count == 3) {
		return 0;
	}
	else {
		return 1;
	}
}

void Search::from_index_to_coordinate(int i, int* x, int* y) {
	*x = i % WID;
	*y = (i - *x) / WID;
}
void Search::from_index_to_index(int index_from, int dx, int dy, int* index_to) {
	int x = 0;
	int y = 0;
	from_index_to_coordinate(index_from,&x,&y);
	x += dx;
	y += dy;
	from_coordinate_to_index(x,y,index_to);
}
void Search::from_coordinate_to_index(int x, int y, int* i) {
	*i = WID * y + x;
}
int Search::euclid_dist(int x_s, int y_s, int x_g, int y_g) {
	int restx = x_g - x_s;
	int resty = y_g - y_s;
	return restx * restx + resty * resty;
}
int Search::get_h_dist(int i, int g) {
	int ix, iy, gx, gy;
	from_index_to_coordinate(i, &ix, &iy);
	from_index_to_coordinate(g, &gx, &gy);
	return (gx - ix)*(gx - ix) + (gy - iy) * (gy - iy);
	//return abs(gx - ix) + abs(gy - iy);
	//return 0;
}
void Search::set_a_star(int sx, int sy, int gx, int gy) {
	from_coordinate_to_index(sx, sy, &start_index);
	from_coordinate_to_index(gx, gy, &goal_index);
	parent_index = start_index;
	parent_t_cost = 0;
	property.put(0 + get_h_dist(parent_index, goal_index), start_index);
	for (int i = 0; i < WID;i++) {
		user->set_wall_status(i,0,0,WALL_SEEN);
		user->set_wall_status(i,HIG-1,1,WALL_SEEN);
	}
	for (int i = 0; i < HIG;i++) {
		user->set_wall_status(0,i,2,WALL_SEEN);
		user->set_wall_status(WID-1,i,3,WALL_SEEN);
	}
	//printf("(%d)", property.tail);
}

void Search::step_back(int index1,int index2) {

}

std::vector<int> Search::step_back2(int index1, int index2) {
	std::vector<int> path1(0);//行先
	std::vector<int> path2(0);//スタート側
	std::vector<int> step_back_path(0);
	int curre_index1 = index1;
	int curre_index2 = index2;
	while ((curre_index1 != start_index)&&(curre_index1 != -1)) {
		path1.push_back(curre_index1);
		curre_index1 = path[curre_index1];
	}
	path1.push_back(start_index);
	while ((curre_index2 != start_index)&&(curre_index2 != -1)) {
		path2.push_back(curre_index2);
		curre_index2 = path[curre_index2];
	}
	path2.push_back(start_index);

	int i = 0;
	while (path1[path1.size()-1-i] == path2[path2.size()-1-i]) {
		i++;
		if ((path1.size() == i)||(path2.size() == i)) {
			break;
		}
	}
	for (int j = 0; j <= path1.size() - i;j++) {
		step_back_path.push_back(path1[j]);
	}
	for (int k = 0; k < path2.size() - i;k++) {
		step_back_path.push_back(path2[path2.size()-1-i-k]);
	}
	return step_back_path;
}

void Search::a_star() {
	if (property.get(&parent_t_cost, &parent_index) == 0) {
		return;
	}
	printf("[%d]",parent_index);
	int g_cost_from = parent_t_cost - get_h_dist(parent_index, goal_index);

	if (user->get_cell_status(parent_index) == CELL_CLOSE) {
		return;
	}

	if (parent_t_cost > dist[parent_index]) {
		return;
	}

	user->prev_index = user->current_index;
	user->current_index = parent_index;
	user->set_cell_status(parent_index, CELL_CLOSE);
	dist[parent_index] = parent_t_cost;

	if (parent_index == goal_index) {
		printf("G");
		//int rest = goal_index;
		//goal_index = start_index;
		//start_index = goal_index;
	}

	for (int i = 0; i < 4; i++) {
		int child_index = 0;
		int child_t_cost = 0;
		from_index_to_index(parent_index,direction[i][0],direction[i][1],&child_index);
		child_t_cost = g_cost_from + 1 + get_h_dist(child_index, goal_index);
		if (user->get_wall_status(parent_index, i) == WALL_OFF) {
			if (dist[child_index] > child_t_cost) {
				if (shortcut_judge(child_index) == 0) {//ここでゴールを例外にしないといけない
					user->set_cell_status(child_index, CELL_CLOSE);
				}
				else {
					property.put(child_t_cost, child_index);
					user->set_cell_status(child_index,CELL_OPEN);
					path[child_index] = parent_index;//--------------------
					dist[child_index] = child_t_cost;
				}
			}
		}
		else {
			user->set_wall_status(parent_index,i,WALL_SEEN);
		}
	}
	//printf("(%d)", property.tail);
}

std::vector<int> Search::get_a_start_path() {
	std::vector<int> cell_list(0);
	int current = goal_index;
	user->set_cell_status(goal_index,CELL_PATH);
	while ((current != start_index) && (current != -1)) {
		current = path[current];
		user->set_cell_status(current,CELL_PATH);
		cell_list.push_back(current);
	}
	cell_list.push_back(start_index);
	return cell_list;
}*/

