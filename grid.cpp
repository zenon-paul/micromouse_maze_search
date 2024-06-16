#include<GL/glut.h>
#include<stdio.h>
#include<stdlib.h>
#include<vector>
#include<string>
#include <nlohmann/json_fwd.hpp>
#include <nlohmann/json.hpp>
#include<fstream>
#include"grid.h"
#include"parameter.h"
#include<stdint.h>
using json = nlohmann::json;
using namespace std;
const uint8_t hight = HIG;
const uint8_t width = WID;
const int8_t direction[4][2] = {
	{0,-1},
	{0,1},
	{-1,0},
	{1,0}
};
const uint8_t mask[4] = { 3,12,48,192 };

double cell_color[5][3] = {
	{0.789, 0.781, 0.753},
	{ 0.605, 0.703, 0.699},
	{ 1.0, 0, 0.0 },
	{1,1,0},
	{0.53,0.1,0.653}
};

double wall_color[5][3] = {
	//{0.45,0.93,0.1},
	{0.789, 0.781, 0.753},
	//{ 0.85, 0.89, 0.1 },
	{ 0.02, 0.25, 0.289 },
	{ 0.5,0.5,0.5 },
	//{ 0.02, 0.25, 0.289 },
	{1, 1, 1},
	{0.85,0.23,0.53}
};
//----------------micromouse------------------------------------------------------
Grid_t::Grid_t() 
: cell(new uint8_t[64]()),
ver_wall(new uint8_t[64]()),
hor_wall(new uint8_t[64]()){
	/*for (int i = 0; i < 64;i++) {
		cell[i] = 0;
		ver_wall[i] = 0;
		hor_wall[i] = 0;
	}*/
}
Grid_t::~Grid_t() {
	delete[] cell;
	delete[] ver_wall;
	delete[] hor_wall;
}
void Grid_t::set_outer_wall() {
	for (int i = 0; i < FIELDSIZE;i++) {
		set_wall_status_xyd(0, i, 2, WALL_SEEN);
	}
	for (int i = 0; i < FIELDSIZE;i++) {
		set_wall_status_xyd(i, 0, 0, WALL_SEEN);
	}
}
void Grid_t::ind2xy(uint8_t i,uint8_t* x,uint8_t* y) {
	*x = i & 15;
	*y = i >> 4;
	//*x = i % WID;
	//*y = (i - *x) / WID;
}
uint8_t Grid_t::xy2ind(uint8_t x,uint8_t y) {
	return WID * y + x;
}
int8_t Grid_t::get_wall_status_xyd(uint8_t x,uint8_t y,uint8_t dir) {
	if (WID <= x) {
		return -1;
	}
	if (HIG <= y) {
		return -1;
	}
	if ((0 <= dir) && (dir < 2)) {//hor
		y = y + (dir & 1);
		if (y == 16) {
			return WALL_SEEN;
		}
		uint8_t ind = xy2ind(x,y);
		return (hor_wall[ind >> 2] & mask[ind & 3]) >> (ind & 3) * 2;
	}
	else if ((2 <= dir) && (dir < 4)) {//ver
		x = x + (dir & 1);
		if (x == 16) {
			return WALL_SEEN;
		}
		uint8_t ind = xy2ind(x,y);
		return (ver_wall[ind >> 2] & mask[ind & 3]) >> (ind & 3) * 2;
	}
}
int8_t Grid_t::get_wall_status_id(uint8_t index,uint8_t dir) {
	if (WID * HIG <= index) {
		return -1;
	}
	uint8_t x = 0;
	uint8_t y = 0;
	ind2xy(index,&x,&y);
	return get_wall_status_xyd(x, y, dir);
}
int8_t Grid_t::get_cell_status_xy(uint8_t x,uint8_t y) {
	if (WID <= x) {
		return -1;
	}
	if (HIG <= y) {
		return -1;
	}
	uint8_t index = 0;
	index = xy2ind(x, y);
	return get_cell_status_id(index);
}
int8_t Grid_t::get_cell_status_id(uint8_t index) {
	if (WID * HIG <= index) {
		return -1;
	}
	return (cell[index >> 2] & mask[index & 3]) >> (index & 3) * 2;
}
int8_t Grid_t::set_wall_status_xyd(uint8_t x, uint8_t y, uint8_t dir,uint8_t val) {
	if (WID <= x) {
		return 0;
	}
	if (HIG <= y) {
		return 0;
	}
	if ((0 <= dir) && (dir < 2)) {//hor
		y = y + (dir & 1);
		if (y == 16) {
			return 0;
		}
		uint8_t ind = xy2ind(x,y);
		hor_wall[ind >> 2] &= ~mask[ind & 3];
		hor_wall[ind >> 2] |= (val << (ind & 3) * 2);
		return 1;
	}
	else if ((2 <= dir) && (dir < 4)) {//ver
		x = x + (dir & 1);
		if (x == 16) {
			return 0;
		}
		uint8_t ind = xy2ind(x,y);
		ver_wall[ind >> 2] &= ~mask[ind & 3];
		ver_wall[ind >> 2] |= (val << (ind & 3) * 2);
		return 1;
	}
}
int8_t Grid_t::set_wall_status_id(uint8_t index, uint8_t dir,uint8_t val) {
	if ((index < 0) || (WID * HIG <= index)) {
		return 0;
	}
	uint8_t x = 0;
	uint8_t y = 0;
	ind2xy(index, &x, &y);
	return set_wall_status_xyd(x,y,dir,val);
}
int8_t Grid_t::set_cell_status_xy(uint8_t x, uint8_t y,uint8_t val) {
	if (WID <= x) {
		return 0;
	}
	if (HIG <= y) {
		return 0;
	}
	uint8_t index = 0;
	index = xy2ind(x, y);
	return set_cell_status_id(index,val);
}
int8_t Grid_t::set_cell_status_id(uint8_t index,uint8_t val) {
	if (WID * HIG <= index) {
		return 0;
	}
	cell[index >> 2] &= ~mask[index & 3];
	cell[index >> 2] |= (val << (index & 3) * 2);
	return 1;
}
//--------------------------------------------------------------
void Grid_t::set_maze(string file_name) {
	ifstream ifs(file_name.c_str());
	if (ifs.good()) {
		json user_json;
		ifs >> user_json;

		string maze_name = user_json["name"];
		for (int i = 0; i < 16; i++) {
			for (int j = 0; j < 16; j++) {
				set_wall_status_xyd(j,i,S, WALL_SEEN * user_json["horizontal_walls"][i][j]);
			}
		}

		for (int i = 0; i < 16; i++) {
			for (int j = 0; j < 17; j++) {
				set_wall_status_xyd(j,i,W, WALL_SEEN * user_json["vertical_walls"][i][j]);
			}
		}
	}
	else {
		printf("The file couldnot be found.\n");
	}
}
void Grid_t::disp_cell() {
	for (int i = 0; i < 16;i++) {
		for (int j = 0; j < 16;j++) {
			if (get_cell_status_xy(j,i) == 0) {
				printf("O");
			}
			else {
				printf("@");
			}
		}
		printf("\n");
	}
	printf("\n\n");
}
void Grid_t::disp_hor_wall() {
	for (int i = 0; i < 17;i++) {
		for (int j = 0; j < 16;j++) {
			if (get_wall_status_xyd(j,i,0) == 0) {
				printf(" ");
			}
			else {
				printf("-");
			}
		}
		printf("\n");
	}
	printf("\n\n");
}
void Grid_t::disp_ver_wall() {
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 16; j++) {
			if (get_wall_status_xyd(j, i, 3) == 0) {
				printf(" ");
			}
			else {
				printf("|");
			}
		}
		printf("\n");
	}
	printf("\n\n");
}
void Grid_t::disp() {
	for (int i = 0; i < HIG * 2;i++) {
		for (int j = 0; j < WID * 2;j++) {
			if ((i&1)&&(j&1)) {//Šï” Šï”
				int8_t s = get_cell_status_xy((j-1)/2,(i-1)/2);
				if (s == CELL_NULL) {
					printf("O");
				}
				else if(s == CELL_CLOSE) {
					printf("@");
				}
				else if (s == CELL_OPEN) {
					printf("X");
				}
				else {
					printf("=");
				}
			}
			else if ((j&1)&&((i&1) == 0)) {//Šï”@‹ô”
				int8_t s = get_wall_status_xyd((j-1)/2,i/2,0);
				if (s == WALL_OFF) {
					printf(" ");
				}
				else {
					printf("-");
				}
			}
			else if (((j&1) == 0)&&(i&1)) {//‹ô”@Šï”
				int8_t s = get_wall_status_xyd(j/2,(i-1)/2,2);
				if (s == WALL_OFF) {
					printf(" ");
				}
				else {
					printf("|");
				}
			}
			else {//‹ô”@‹ô”
				printf(" ");
			}
		}
		printf("\n");
	}
	printf("\n\n");
}
//--------------------------------------------------------------------------------

/*
Grid::Grid() {
	int w = 16;
	int h = 16;
	cell = (char*)calloc((WID * HIG / 4), sizeof(char));

	ver_wall = (int**)malloc(sizeof(int*) * h);
	for (int i = 0; i < h; i++) {
		ver_wall[i] = (int*)calloc(w + 1, sizeof(int));
	}

	hor_wall = (int**)malloc(sizeof(int*) * (h + 1));
	for (int i = 0; i < h + 1; i++) {
		hor_wall[i] = (int*)calloc(w, sizeof(int));
	}
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
	unsigned int m[4] = { 3,12,48,192 };
	for (int i = 0; i < 4; i++) {
		mask[i] = m[i];
	}
	current_index = 0;
}
Grid::~Grid() {
	free(cell);

	for (int i = 0; i < hight; i++) {
		free(ver_wall[i]);
	}
	free(ver_wall);

	for (int i = 0; i < hight + 1; i++) {
		free(hor_wall[i]);
	}
	free(hor_wall);
}

void Grid::from_index_to_coordinate(int i, int* x, int* y) {
	*x = i % WID;
	*y = (i - *x) / WID;
}
void Grid::from_coordinate_to_index(int x, int y, int* i) {
	*i = WID * y + x;
}

int Grid::get_wall_status(int x, int y, int dir) {
	if ((x<0)||(WID<=x)) {
		return -1;
	}
	if ((y<0)||(HIG<=y)) {
		return -1;
	}
	if ((0<=dir)&&(dir<2)) {//hor
		return hor_wall[y+(dir%2)][x];
	}
	else if ((2<=dir)&&(dir<4)) {//ver
		return ver_wall[y][x+(dir%2)];
	}
	return -1;
}
int Grid::get_wall_status(int index,int dir) {
	if ((index<0)||(WID*HIG<=index)) {
		return -1;
	}
	if ((dir<0)||(4<=dir)) {
		return -1;
	}
	int x = 0;
	int y = 0;
	from_index_to_coordinate(index,&x,&y);
	return get_wall_status(x,y,dir);
}
int Grid::get_cell_status(int x, int y) {
	if ((x < 0) || (WID < x)) {
		return -1;
	}
	if ((y < 0) || (HIG < y)) {
		return -1;
	}
	int index = 0;
	from_coordinate_to_index(x,y,&index);
	return (cell[(index - index % 4) / 4] & mask[index % 4]) >> (index % 4)*2;
}
int Grid::get_cell_status(int index) {
	if ((index < 0) || (WID * HIG <= index)) {
		return -1;
	}
	return (cell[(index - index % 4) / 4] & mask[index % 4]) >> (index % 4)*2;
}
void Grid::set_wall_status(int x, int y, int dir, int val) {
	if ((0 <= dir) && (dir < 2)) {//hor
		hor_wall[y + (dir % 2)][x] = val;
	}
	else if ((2 <= dir) && (dir < 4)) {//ver
		ver_wall[y][x + (dir % 2)] = val;
	}
}
void Grid::set_wall_status(int index, int dir, int val) {
	if ((index < 0) || (WID * HIG <= index)) {
		return;
	}
	if ((dir < 0) || (4 <= dir)) {
		return;
	}
	int x = 0;
	int y = 0;
	from_index_to_coordinate(index, &x, &y);
	set_wall_status(x, y, dir, val);
}
void Grid::set_cell_status(int x, int y, int val) {
	if ((x < 0) || (WID < x)) {
		return;
	}
	if ((y < 0) || (HIG < y)) {
		return;
	}
	if ((val<0)||(4<=val)) {
		return;
	}
	int index = 0;
	from_coordinate_to_index(x, y, &index);
	cell[(index - index % 4) / 4] &= ~mask[index % 4];
	cell[(index - index % 4) / 4] |= (val << (index % 4)*2);
}
void Grid::set_cell_status(int index,int val) {
	if ((index<0)||(WID*HIG<=index)) {
		return;
	}
	cell[(index - index % 4) / 4] &= ~mask[index % 4];
	cell[(index - index % 4) / 4] |= (val << (index % 4)*2);
}


void Grid::clean_cell(Grid* user) {
	memset(cell, 0, sizeof(char)*WID*HIG/4);
}
void Grid::clean_wall(Grid* user) {
	for (int i = 0; i < hight;i++) {
		memset(user->ver_wall[i], 0, sizeof(int)*(width+1));
	}
	for (int i = 0; i < hight + 1;i++) {
		memset(user->hor_wall,0,sizeof(int)*width);
	}
}
void Grid::geo_wall() {
	//glColor3d(0.363, 0.433, 0.437);
	glBegin(GL_LINES);
	for (int i = 0;i<hight; i++) {
		for (int j = 0; j < width + 1;j++) {
			
			glColor3dv(wall_color[ver_wall[i][j]]);//ver_wall[i][j]%3
			//printf("%d",ver_wall[i][j]);
			glVertex2i(EGSIZE * j + X_DISPLACEMENT, EGSIZE * i + Y_DISPLACEMENT);
			glVertex2i(EGSIZE * j + X_DISPLACEMENT, EGSIZE * i + EGSIZE + Y_DISPLACEMENT);
		}
	}
	
	for (int i = 0; i < hight + 1;i++) {
		for (int j = 0; j < width;j++) {
			glColor3dv(wall_color[hor_wall[i][j]]);//hor_wall[i][j]%3
			glVertex2i(EGSIZE * j + X_DISPLACEMENT, EGSIZE * i + Y_DISPLACEMENT);
			glVertex2i(EGSIZE * j + EGSIZE + X_DISPLACEMENT, EGSIZE * i + Y_DISPLACEMENT);
		}
	}
	glEnd();
	glFlush();
}
void Grid::geo_cell() {
	glBegin(GL_QUADS);
	for (int i = 0; i < hight; i++) {
		for (int j = 0; j < width; j++) {
			int index = 0;
			from_coordinate_to_index(j, i, &index);
			glColor3dv(cell_color[get_cell_status(index)]);//cell[i][j]%3
			if (current_index == index) {
				glColor3d(0.2,0,0.5);
			}
			//printf("%d ", get_cell_status(index));
			glVertex2i(EGSIZE * j + X_DISPLACEMENT, EGSIZE * i + Y_DISPLACEMENT);
			glVertex2i(EGSIZE * j + X_DISPLACEMENT + EGSIZE, EGSIZE * i + Y_DISPLACEMENT);
			glVertex2i(EGSIZE * j + X_DISPLACEMENT + EGSIZE, EGSIZE * i + EGSIZE + Y_DISPLACEMENT);
			glVertex2i(EGSIZE * j + X_DISPLACEMENT, EGSIZE * i + EGSIZE + Y_DISPLACEMENT);
		}
		//printf("\n");
	}

	glEnd();
	glFlush();
}

void Grid::set_maze(int** map) {
	for (int i = 0; i < hight;i++) {
		for (int j = 0; j < width + 1;j++) {
			ver_wall[i][j] = map[2*i+1][j * 2];
		}
	}
	for (int i = 0; i < hight + 1;i++) {
		for (int j = 0; j < width;j++) {
			hor_wall[i][j] = map[i * 2][2*j+1];
		}
	}
}

void Grid::set_maze(string file_name) {
	ifstream ifs(file_name.c_str());
	if (ifs.good()) {
		json user_json;
		ifs >> user_json;

		string maze_name = user_json["name"];
		for (int i = 0; i < 17; i++) {
			for (int j = 0; j < 16; j++) {
				hor_wall[i][j] = WALL_ON*user_json["horizontal_walls"][i][j];
			}
		}

		for (int i = 0; i < 16; i++) {
			for (int j = 0; j < 17; j++) {
				ver_wall[i][j] = WALL_ON*user_json["vertical_walls"][i][j];
			}
		}
	}
	else {
		printf("The file couldnot be found.\n");
	}
}
*/

