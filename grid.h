#pragma once
#define CELLNUM 256
#define FIELDSIZE 16


#define WID (FIELDSIZE)
#define HIG (FIELDSIZE)
#define X_DISPLACEMENT 150
#define Y_DISPLACEMENT 120
//#define EGSIZE 16

#define CELL_CLOSE 3
#define CELL_OPEN 1
#define CELL_NULL 0
#define CELL_PATH 2

//#define WALL_ON 3//本来は必要なし
#define WALL_OFF 0//not seen or seen and walloff
#define WALL_SEEN 1//seen and wallon

//#define BUFF_SIZE 256

#include<vector>
#include<string>
#include<stdint.h>


struct XY {
	int8_t x;
	int8_t y;
	XY() {}
	XY(int8_t x, int8_t y);
	XY(const XY& xy);
	XY& operator=(const XY& xy)&;
	XY operator-()const;
	XY& operator+=(const XY& xy)&;
	XY& operator-=(const XY& xy)&;
	friend bool operator==(const XY& a, const XY& b);
	friend bool operator!=(const XY& a, const XY& b);
	friend XY operator+(const XY& a, const XY& b);
	friend XY operator-(const XY& a, const XY& b);
};

const XY s(0,-1);
const XY n(0,1);
const XY w(-1,0);
const XY e(1,0);

const XY directions[4] = {
		s,
		n,
		w,
		e,
};

enum { S, N, W, E };
class Maze {
public:
	constexpr static uint8_t mask[4] = { 3,12,48,192 };
	constexpr static uint16_t wid = WID;
	constexpr static uint16_t hig = HIG;
	constexpr static uint16_t buffsize = 64;
	Maze();
	Maze(const Maze&);//コピーコンストラクタ
	~Maze();
	Maze& operator=(const Maze&)&;//コピー代入演算子
	void set_outer_wall();
	void ind2xy(uint8_t i, uint8_t* x, uint8_t* y)const;
	uint8_t xy2ind(uint8_t x, uint8_t y)const;

	int8_t get_wall_status_xyd(int8_t x, int8_t y, uint8_t dir)const;
	int8_t get_wall_status_xyd(XY xy, uint8_t dir)const;
	int8_t get_wall_status_id(uint8_t index, uint8_t dir)const;
	int8_t get_cell_status_xy(int8_t x, int8_t y)const;
	int8_t get_cell_status_xy(XY xy)const;
	int8_t get_cell_status_id(uint8_t index)const;
	int8_t set_wall_status_xyd(int8_t x, int8_t y, uint8_t dir, uint8_t val);
	int8_t set_wall_status_xyd(XY xy, uint8_t dir, uint8_t val);
	int8_t set_wall_status_id(uint8_t index, uint8_t dir, uint8_t val);
	int8_t set_cell_status_xy(int8_t x, int8_t y, uint8_t val);
	int8_t set_cell_status_xy(XY xy, uint8_t val);
	int8_t set_cell_status_id(uint8_t index, uint8_t val);
	void set_maze(std::string file_name);
	void disp_cell();
	void disp_hor_wall();
	void disp_ver_wall();
	void disp();
private:
	uint8_t* cell;
	uint8_t* ver_wall;
	uint8_t* hor_wall;
};
