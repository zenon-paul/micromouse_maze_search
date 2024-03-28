#include"dijikstr.h"
#include"grid.h"

Dijikstr::Dijikstr(Grid* u, int sx, int sy, int gx, int gy):path(WID* HIG, -1), dist(WID* HIG, INF),start_index(0),goal_index(0){
	user = u;
	from_coordinate_to_index(sx,sy,&start_index);
	from_coordinate_to_index(gx,gy,&goal_index);

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
}

Dijikstr::Dijikstr(Grid* u,int s_index,int g_index) :path(WID* HIG, -1), dist(WID* HIG, INF), start_index(0), goal_index(0) {
	user = u;
	start_index = s_index;
	goal_index = g_index;

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
}

void Dijikstr::from_index_to_coordinate(int i, int* x, int* y) {
	*x = i % WID;
	*y = (i - *x) / WID;
}
void Dijikstr::from_index_to_index(int index_from, int dx, int dy, int* index_to) {
	int x = 0;
	int y = 0;
	from_index_to_coordinate(index_from, &x, &y);
	x += dx;
	y += dy;
	from_coordinate_to_index(x, y, index_to);
}
void Dijikstr::from_coordinate_to_index(int x, int y, int* i) {
	*i = WID * y + x;
}

int Dijikstr::shortcut_judge(int index) {
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

int Dijikstr::evalu(int index) {
	if ((unsigned int)index>=dist.size()) {
		return -1;
	}
	return dist[index] + 1;
}

int Dijikstr::evalu(int x,int y) {
	if ((0>x)||(x>=WID)) {
		return- 1;
	}
	if ((0>y)||(y>=HIG)) {
		return -1;
	}
	int index = 0;
	from_coordinate_to_index(x,y,&index);
	return dist[index] + 1;
}

void Dijikstr::dijikstr() {
	//printf("d\n");
	int parent_index = start_index;
	int parent_cost = 0;
	dist[parent_index] = 0;
	d2_prqueue property(BUFF_SIZE);
	property.put(parent_cost,parent_index);
	while (property.get(&parent_cost,&parent_index)) {
		//printf("[[[[[%d\n",parent_index);
		if (parent_cost > dist[parent_index]) {
			continue;
		}
		for (int i = 0; i < 4;i++) {
			//printf("(%d)\n",i);
			int child_index = 0;
			from_index_to_index(parent_index, direction[i][0], direction[i][1], &child_index);
			int child_cost = evalu(parent_index);
			if (user->get_wall_status(parent_index,i) == WALL_SEEN) {
				//printf("%d seen\n",i);
				continue;
			}
			if (dist[child_index]<=child_cost) {
				//printf("already %d (%d %d)\n",child_index,dist[child_index],child_cost);
				continue;
			}
			property.put(child_cost,child_index);
			dist[child_index] = child_cost;
			path[child_index] = parent_cost;
			//printf("ind:%dcost:%d\n",child_index,child_cost);
		}
	}
	/*for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 16; j++) {
			int x = 0;
			from_coordinate_to_index(j, i, &x);
			printf("%3d ", dist[x]);
		}
		printf("\n");
	}*/
}

int Dijikstr::get_cost(int index) {
	if ((unsigned int)index >= dist.size()) {
		return -1;
	}
	return dist[index];
}

int Dijikstr::get_cost(int x,int y) {
	if ((0 > x) || (x >= WID)) {
		return-1;
	}
	if ((0 > y) || (y >= HIG)) {
		return -1;
	}
	int index = 0;
	from_coordinate_to_index(x, y, &index);
	return dist[index];
}

void Dijikstr::step_back(int index1, int index2) {

}
vector<int> Dijikstr::step_back2(int index1, int index2) {
	vector<int>ans(0);
	return ans;
}
vector<int> Dijikstr::get_a_start_path() {
	vector<int>ans(0);
	return ans;
}