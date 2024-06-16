/*#include"grid.h"
#include"dfs.h"

Dfs::Dfs(Grid* u) :property(BUFF_SIZE), path(WID* HIG, -1){
	user = u;
	start_index = 0;
	goal_index = 0;

	int d[4][2] = {///////////direction
		{0,-1},
		{0,1},
		{-1,0},
		{1,0}
	};
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 2; j++) {
			direction[i][j] = d[i][j];
		}
	}
	parent_index = 0;
}

void Dfs::from_index_to_coordinate(int i, int* x, int* y) {
	*x = i % WID;
	*y = (i - *x) / WID;
}
void Dfs::from_index_to_index(int index_from, int dx, int dy, int* index_to) {
	int x = 0;
	int y = 0;
	from_index_to_coordinate(index_from, &x, &y);
	x += dx;
	y += dy;
	from_coordinate_to_index(x, y, index_to);
}
void Dfs::from_coordinate_to_index(int x, int y, int* i) {
	*i = WID * y + x;
}

int Dfs::shortcut_judge(int index) {
	if (index == goal_index) {
		return 1;
	}
	int count = 0;
	for (int i = 0; i < 4; i++) {
		if (user->get_wall_status(index, i) == WALL_SEEN) {
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

void Dfs::set_dfs(int sx, int sy, int gx, int gy) {
	from_coordinate_to_index(sx, sy, &start_index);
	from_coordinate_to_index(gx, gy, &goal_index);
	parent_index = start_index;
	property.push(parent_index);
	for (int i = 0; i < WID; i++) {
		user->set_wall_status(i, 0, 0, WALL_SEEN);
		user->set_wall_status(i, HIG - 1, 1, WALL_SEEN);
	}
	for (int i = 0; i < HIG; i++) {
		user->set_wall_status(0, i, 2, WALL_SEEN);
		user->set_wall_status(WID - 1, i, 3, WALL_SEEN);
	}
}

void Dfs::dfs() {
	printf("\n@\n");
	if (property.get(&parent_index) == 0) {
		printf("fail\n");
		return;
	}
	if (user->get_cell_status(parent_index) == CELL_CLOSE) {
		return;
	}
	user->prev_index = user->current_index;
	user->current_index = parent_index;
	user->set_cell_status(parent_index, CELL_CLOSE);
	if (parent_index == goal_index) {
		printf("g\n");
		//return;
	}

	for (int i = 0; i < 4; i++) {
		if (user->get_wall_status(parent_index, i) == WALL_OFF) {
			int child_index = 0;
			from_index_to_index(parent_index, direction[i][0], direction[i][1], &child_index);
			if (user->get_cell_status(child_index) == CELL_CLOSE) {
				continue;
			}
			printf("(%d)\n", i);
			property.push(child_index);
			user->set_cell_status(child_index, CELL_OPEN);
			path[child_index] = parent_index;
		}
		else {
			user->set_wall_status(parent_index,i,WALL_SEEN);
		}
	}
	printf("{{{{%d", property.get_len());
}

void Dfs::step_back(int index1, int index2) {

}
vector<int> Dfs::step_back2(int index1, int index2) {
	std::vector<int> path1(0);//行先
	std::vector<int> path2(0);//スタート側
	std::vector<int> step_back_path(0);
	int curre_index1 = index1;
	int curre_index2 = index2;
	while ((curre_index1 != start_index) && (curre_index1 != -1)) {
		path1.push_back(curre_index1);
		curre_index1 = path[curre_index1];
	}
	path1.push_back(start_index);
	while ((curre_index2 != start_index) && (curre_index2 != -1)) {
		path2.push_back(curre_index2);
		curre_index2 = path[curre_index2];
	}
	path2.push_back(start_index);

	int i = 0;
	while (path1[path1.size() - 1 - i] == path2[path2.size() - 1 - i]) {
		i++;
		if ((path1.size() == i) || (path2.size() == i)) {
			break;
		}
	}
	for (int j = 0; j <= path1.size() - i; j++) {
		step_back_path.push_back(path1[j]);
	}
	for (int k = 0; k < path2.size() - i; k++) {
		step_back_path.push_back(path2[path2.size() - 1 - i - k]);
	}
	return step_back_path;
}
vector<int> Dfs::get_adati_path() {//この方法だとうまくいかない
	std::vector<int> cell_list(0);
	int current = goal_index;
	user->set_cell_status(goal_index, CELL_PATH);
	while ((current != start_index) && (current != -1)) {
		printf("curre:%d\n", current);
		current = path[current];
		user->set_cell_status(current, CELL_PATH);
		cell_list.push_back(current);
	}
	cell_list.push_back(start_index);
	return cell_list;
}*/