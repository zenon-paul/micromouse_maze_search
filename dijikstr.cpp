#include"dijikstr.h"
#include"grid.h"
#include<queue>
bool operator==(const XY& a, const XY& b) {
	return (a.x == b.x) && (a.y == b.y);
}
StepMap::StepMap(XY s,XY g):start_xy(s),goal_xy(g) {

}
void StepMap::update_stepmap(Grid_t& maze) {
	std::vector<std::vector<int>> cost_table(FIELDSIZE,std::vector<int>(FIELDSIZE,MAXu16bit));
	std::vector<std::vector<XY>> path(FIELDSIZE, std::vector<XY>(FIELDSIZE));
	auto comp = [](const CellCost& b, const CellCost& a)->bool {
		return a.cost < b.cost;//¸‡‚Å•À‚×‘Ö‚¦
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
		int pa_x = parent.xy.x;
		int pa_y = parent.xy.y;
		if (parent.cost > cost_table[pa_y][pa_x]) {
			continue;
		}
		if(parent.xy == goal_xy) {
			printf("goal!\n");
			return;
		}
		for (int i = 0; i < 4;i++) {
			if (maze.get_wall_status_xyd(pa_x,pa_y,i)==WALL_SEEN) {
				continue;
			}
			XY ch_xy{ pa_x + direction[i][0],pa_y + direction[i][1] };
			int ch_cost = parent.cost + 1;
			if (ch_cost < cost_table[ch_xy.y][ch_xy.x]) {
				CellCost child{ch_xy,ch_cost};
				pri_queue.push(child);
				cost_table[ch_xy.y][ch_xy.x] = ch_cost;
				path[ch_xy.y][ch_xy.x] = parent.xy;
			}
		}
		for (int i = 0; i < FIELDSIZE;i++) {
			for (int j = 0; j < FIELDSIZE;j++) {
				if (cost_table[i][j] == MAXu16bit) {
					printf(" INF  ");
				}
				else {
					printf("%5d ", cost_table[i][j]);
				}
			}
			printf("\n");
		}
		printf("\n");
	}


}
/*void Dijikstr_constructor(Dijikstr_* this_,Grid_* u) {
	this_->user = u;
	this_->start_index = 0;
	this_->goal_index = 0;
	for (int i = 0; i < WID * HIG;i++) {
		this_->dist[i] = INF_;
		this_->path[i] = 0;
	}
}
uint8_t Dijikstr_ind2ind(uint8_t frm_i,int8_t dx,int8_t dy) {
	return frm_i + WID * dy + dx;
}
void Dijikstr_dijikstr(Dijikstr_* this_) {
	int p_i = this_->start_index;
	int p_dst = 0;
	this_->dist[p_i] = p_dst;
	//d2_prqueue buff(BUFF_SIZE);
	d2_prqueue_ buff;
	d2_prqueue_constructor(&buff,BUFF_SIZE);
	//buff.put(p_dst,p_i);
	d2_prqueue_put(&buff,p_dst, p_i);
	while (d2_prqueue_get(&buff,&p_dst, &p_i)) {
		if (p_dst > this_->dist[p_i]) {
			continue;
		}
		for (int i = 0; i < 4;i++) {
			if (Grid_get_wall_status_id(this_->user, p_i, i) == WALL_SEEN) {
				continue;
			}
			int ch_i = Dijikstr_ind2ind(p_i,direction[i][0],direction[i][1]);
			int ch_dst = this_->dist[p_i] + 1;
			if (this_->dist[ch_i]<=ch_dst) {
				continue;
			}
			//buff.put(ch_dst,ch_i);
			d2_prqueue_put(&buff,ch_dst, ch_i);
			this_->dist[ch_i] = ch_dst;
			this_->path[ch_i] = p_i;
		}
	}
}


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
}*/
