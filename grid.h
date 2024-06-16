#pragma once
#define WID 16
#define HIG 16
#define X_DISPLACEMENT 150
#define Y_DISPLACEMENT 120
#define EGSIZE 16

#define CELLNUM 256
#define FIELDSIZE 16

#define CELL_CLOSE 3
#define CELL_OPEN 1
#define CELL_NULL 0
#define CELL_PATH 2

//#define WALL_ON 3//–{—ˆ‚Í•K—v‚È‚µ
#define WALL_OFF 0//not seen or seen and walloff
#define WALL_SEEN 1//seen and wallon

#define BUFF_SIZE 256

#include<vector>
#include<string>
#include<stdint.h>
using namespace std;
//     0  1  2  3
enum { S, N, W, E };
extern const int8_t direction[4][2];
class Grid_t {
private:
	uint8_t *cell;
	uint8_t *ver_wall;
	uint8_t *hor_wall;
	//uint8_t cell[64];
	//uint8_t ver_wall[64];
	//uint8_t hor_wall[64];
public:
	Grid_t();
	~Grid_t();
	void set_outer_wall();
	void ind2xy(uint8_t i, uint8_t* x, uint8_t* y);
	uint8_t xy2ind(uint8_t x, uint8_t y);
	int8_t get_wall_status_xyd(uint8_t x, uint8_t y, uint8_t dir);
	int8_t get_wall_status_id(uint8_t index, uint8_t dir);
	int8_t get_cell_status_xy(uint8_t x, uint8_t y);
	int8_t get_cell_status_id(uint8_t index);
	int8_t set_wall_status_xyd(uint8_t x, uint8_t y, uint8_t dir, uint8_t val);
	int8_t set_wall_status_id(uint8_t index, uint8_t dir, uint8_t val);
	int8_t set_cell_status_xy(uint8_t x, uint8_t y, uint8_t val);
	int8_t set_cell_status_id(uint8_t index, uint8_t val);
	void set_maze(string file_name);
	void disp_cell();
	void disp_hor_wall();
	void disp_ver_wall();
	void disp();


};







/*
class Grid {
private:
public:
	char* cell;////
	int** ver_wall;
	int** hor_wall;
	int direction[4][2];////////
	int current_index;//////////
	int prev_index;////////////

	unsigned int mask[4];//////////
	;
	Grid();
	~Grid();
	void from_index_to_coordinate(int i, int* x, int* y);//////
	void from_coordinate_to_index(int x, int y, int* i);///////////


	int get_wall_status(int x, int y, int dir);///////
	int get_wall_status(int index, int dir);/////////
	int get_cell_status(int x, int y);/////
	int get_cell_status(int index);///////
	void set_wall_status(int x, int y, int dir,int val);////////
	void set_wall_status(int index,int dir,int val);/////////
	void set_cell_status(int x, int y,int val);//////
	void set_cell_status(int index,int val);///////////


	void clean_wall(Grid* user);
	void clean_cell(Grid* user);
	void geo_cell();
	void geo_wall();

	void set_maze(int** map);
	void set_maze(string file_name);////////////
	//void a_star(d2_prqueue* x,int* dist);
	//int get_a_start_path();
};
*/