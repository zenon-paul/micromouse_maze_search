#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<limits.h>
#include"container.h"
#include"make_maze.h"



Maze::Maze():p_info2((WIDTH / 2)* (HIGHT / 2)){
	int d[4][2] = {
	{-1,0},
	{0,1},
	{1,0},
	{0,-1}
	};
	for (int i = 0; i < 4;i++) {
		for (int j = 0; j < 2;j++) {
			direction_set_1[i][j] = d[i][j];
		}
	}
	srand((unsigned int)time(NULL));
	random_num = rand();
}
Maze::~Maze() {
	for (int i = 0; i < HIGHT;i++) {
		free(bord1[i]);
	}
	free(bord1);
}
void Maze::init_for_extending_wall() {
	bord1 = (int**)malloc(sizeof(int*) * HIGHT);
	for (int i = 0; i < HIGHT; i++) {
		bord1[i] = (int*)calloc(WIDTH, sizeof(int));
	}
	for (int i = 0; i < HIGHT; i++) {
		if ((i == 0) || (i == HIGHT - 1)) {
			for (int j = 0; j < WIDTH; j++) {
				bord1[i][j] = 3;
			}
		}
		else {
			bord1[i][0] = 3;
			bord1[i][WIDTH - 1] = 3;
		}
	}
}
//----------------by_extending_wall--------------------------------------------
void Maze::listup_available_point(int list___num_ps[WIDTH * HIGHT], int list___num_ps_index[WIDTH * HIGHT], int lim) {
	for (int i = 0; i < lim; i++) {
		p_info2.get(&list___num_ps[i], &list___num_ps_index[i]);
	}

}
void Maze::random_select(int list___num_ps_index[WIDTH * HIGHT], int* start, int count) {
	srand((unsigned int)random_num);
	random_num++;
	*start = list___num_ps_index[rand() % count];
}
void Maze::turn_list_to_1(int list___num_ps[WIDTH * HIGHT], int list___num_ps_index[WIDTH * HIGHT], int start, int lim) {
	for (int i = 0; i < lim; i++) {
		if (list___num_ps_index[i] == start) {
			list___num_ps[i] = 1;
		}
	}
}
void Maze:: check_dead_end_even(int s_body[WIDTH * HIGHT], int start, int dire4[4],int leng) {
	int restx, resty, reststart;
	from_index_to_component_even(start, &restx, &resty);
	for (int i = 0; i < 4; i++) {
		from_component_to_index_even(restx + direction_set_1[i][0], resty + direction_set_1[i][1], &reststart);
		for (int j = 0; j <= leng; j++) {
			if (s_body[j] == reststart) {
				dire4[i] = -1;
			}
		}
	}
}
void Maze::from_component_to_index_even(int x, int y, int* index) {
	int x_max = (WIDTH - 3) / 2;
	int y_max = (HIGHT - 3) / 2;
	*index = (y - 1) * x_max + x;
}
void Maze::from_index_to_component_even(int i, int* x, int* y) {
	int x_max = (WIDTH - 3) / 2;
	int y_max = (HIGHT - 3) / 2;
	*x = (i - 1) % x_max + 1;
	*y = (i - 1) / x_max + 1;
}
void Maze::make_maze_easier() {
	for (int i = 0; i < HIGHT;i++) {
		for (int j = 0; j < WIDTH;j++) {
			srand((unsigned int)time(NULL));
			int r = (rand()*7) % 10;
			if ((r==0)||(r==1)) {
				//bord1[i][j] = 0;
			}
		}
	}
}
void Maze::extending_wall() {
	int x_max = (WIDTH - 3) / 2;
	int y_max = (HIGHT - 3) / 2;

	int* list_even_num_ps = 0;
	int* list_even_num_ps_index = 0;

	list_even_num_ps = (int*)malloc(sizeof(int) * WIDTH * HIGHT);
	list_even_num_ps_index = (int*)malloc(sizeof(int) * WIDTH * HIGHT);

	int available_ps_count = x_max * y_max;
	for (int i = 1; i <= available_ps_count; i++) {
		p_info2.put(0, i);
	}
	while (available_ps_count > 0) {//すべての偶数座標が壁になるまで
		d_stack s_info(WIDTH * HIGHT);

		int first_available_ps = available_ps_count;
		int start = 0;
		int x_component = 0;
		int y_component = 0;
		int x_coordinate = 0;
		int y_coordinate = 0;
		int depth = 0;
		int memo[WIDTH * HIGHT] = { 0 };
		int flag = 1;
		listup_available_point(list_even_num_ps, list_even_num_ps_index, first_available_ps);
		random_select(list_even_num_ps_index, &start, first_available_ps);
		while (1) {//一世代が終わるまで
			int dire4[4] = { 0 };
			from_index_to_component_even(start, &x_component, &y_component);
			x_coordinate = x_component * 2;                             //座標
			y_coordinate = y_component * 2;                             //座標
			bord1[y_coordinate][x_coordinate] = WALL;                  //書き込み
			turn_list_to_1(list_even_num_ps, list_even_num_ps_index, start, first_available_ps);                                //seen->1
			s_info.push(start);                                      //push
			available_ps_count--;                                                    //count--
			check_dead_end_even(s_info.body, start, dire4,s_info.get_len());
			int dire = 0;
			while (1) {//次進む点が決まるまで

				if ((dire4[0] == -1) && (dire4[1] == -1) && (dire4[2] == -1) && (dire4[3] == -1)) {
					depth++;
					for (int i = 0; i < depth; i++) {
						s_info.get(&start);
						memo[i] = start;
					}
					s_info.get(&start);
					for (int i = 0; i < depth; i++) {
						s_info.push(memo[depth - i - 1]);
					}
					available_ps_count++;
					break;
				}
				srand((unsigned int)time(NULL)+random_num*13);
				random_num++;
				dire = rand() % 4;
				//printf("[%d]\n",dire);
				if (dire4[dire] == -1) {
					continue;
				}
				else if (bord1[y_coordinate + direction_set_1[dire][1] * 2][x_coordinate + direction_set_1[dire][0] * 2] > 0) {//ボードに中間書き込み後//次のスタートを設定//一世代の終了
					depth = 0;
					bord1[y_coordinate + direction_set_1[dire][1]][x_coordinate + direction_set_1[dire][0]] = WALL;
					from_component_to_index_even(x_component + direction_set_1[dire][0], y_component + direction_set_1[dire][1], &start);
					flag = 0;
					break;
				}
				else {//ボードに中間書き込み後//次のスタートを設定
					depth = 0;
					bord1[y_coordinate + direction_set_1[dire][1]][x_coordinate + direction_set_1[dire][0]] = WALL;
					from_component_to_index_even(x_component + direction_set_1[dire][0], y_component + direction_set_1[dire][1], &start);
					break;
				}
			}
			if (flag == 0) {
				break;
			}
		}
		for (int i = 0; i < first_available_ps; i++) {
			p_info2.put(list_even_num_ps[i], list_even_num_ps_index[i]);
		}
	}
	free(list_even_num_ps);
	free(list_even_num_ps_index);
	make_maze_easier();
}