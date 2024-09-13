#include<GL/glut.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<limits.h>
#include<vector>
#include"grid.h"
#include"make_maze.h"
#include"search.h"
#include"adati.h"
#include"dfs.h"
#include<iostream>
#include"stepmap.h"
#include<queue>
#include<stack>
#include"grid.h"
/*auto* p = new Grid;
Adati TT(p);
Maze test;
typedef void(Grid::* func)();
func c = &Grid::geo_cell;
func w = &Grid::geo_wall;
std::vector<int> step_back_path(0);


//---------------------------------------------------------------------------

void idle() {
	glutPostRedisplay();
}
void Init() {
	glClearColor(0.7, 0.7, 0.7, 1.0);
}
void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	(p->*c)();
	(p->*w)();

	glPointSize(5);
	glBegin(GL_POINTS);
	glColor3d(0,0,0);
	for (int i = 0; i < step_back_path.size();i++) {
		int x = 0;
		int y = 0;
		p->from_index_to_coordinate(step_back_path[i],&x,&y);
		glVertex2i(EGSIZE * x + X_DISPLACEMENT + EGSIZE*0.5, EGSIZE * y + Y_DISPLACEMENT + EGSIZE * 0.5);
	}
	glEnd();
	glFlush();
	glutSwapBuffers();
}
void reshape(int w, int h) {
	glViewport(0.0, 0.0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (double)w, 0.0, (double)h);

}
void mouse(int button, int state, int x, int y) {
	if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN)) {
		//test.init_for_extending_wall();
		//test.extending_wall();
		//p->set_maze(test.bord1);
		p->set_maze("AllJapan_001_1980_classic___16x16.json");
		TT.set_adati(0, 0, 15, 15);
	}
	if ((button == GLUT_RIGHT_BUTTON) && (state == GLUT_DOWN)) {
		TT.adati();
		//TT.get_adati_path();
		//step_back_path = TT.step_back2(p->prev_index,p->current_index);

	}
}*/


class MazeLocation {
public:
	constexpr static uint8_t convert_lcl2glb_table[4][4] = {
		{2,3,1,0},
		{3,2,0,1},
		{1,0,3,2},
		{0,1,2,3}
	}; 
	constexpr static uint8_t convert_glb2lcl_table[4][4] = {
		{3,2,0,1},
		{2,3,1,0},
		{1,0,3,2},
		{0,1,2,3}
	};

	enum class Motion{LEFT,RIGHT,BACK,FORWARD,NONE};
	uint8_t glb_forward_dir;
	XY glb_mylocation;
	MazeLocation();
	uint8_t convert_dir_lcl2lglb(uint8_t lcl) const;
	uint8_t convert_dir_glb2lcl(uint8_t glb) const;
	void go_to_left();
	void go_to_right();
	void back();
	void go_forward();
	void go_to(uint8_t dir);
	Motion detect_next_motion(XY neiborhood) const;
};

MazeLocation::MazeLocation()
:glb_forward_dir(3),
glb_mylocation(0, 0) {}

uint8_t MazeLocation::convert_dir_lcl2lglb(uint8_t lcl) const {//glb_foward_dirの更新 
	return convert_lcl2glb_table[this->glb_forward_dir][lcl];
}

uint8_t MazeLocation::convert_dir_glb2lcl(uint8_t glb) const {
	return convert_glb2lcl_table[this->glb_forward_dir][glb];
}
void MazeLocation::go_to_left() {
	this->glb_forward_dir = this->convert_dir_lcl2lglb(0);
	this->glb_mylocation += directions[this->glb_forward_dir];
}
void MazeLocation::go_to_right() {
	this->glb_forward_dir = this->convert_dir_lcl2lglb(1);
	this->glb_mylocation += directions[this->glb_forward_dir];
}
void MazeLocation::back() {
	this->glb_forward_dir = this->convert_dir_lcl2lglb(2);
	this->glb_mylocation += directions[this->glb_forward_dir];
}
void MazeLocation::go_forward() {
	this->glb_mylocation += directions[this->glb_forward_dir];
}
void MazeLocation::go_to(uint8_t dir) {
	if (dir >= 4) {
		return;
	}
	this->glb_forward_dir = this->convert_dir_lcl2lglb(dir);
	this->glb_mylocation += directions[this->glb_forward_dir];
}

/*帰ってきた座標と現在の座標からgo left rightを決定する*/
MazeLocation::Motion MazeLocation::detect_next_motion(XY neiborhood) const {//引き算で決定
	XY glb_dir_vec = neiborhood - glb_mylocation;//命名則...
	uint8_t lcl_dir = 0;
	for (int i = 0; i < 4; i++) {
		if (directions[i] == glb_dir_vec) {
			lcl_dir = convert_dir_glb2lcl(i);
			break;
		}
	}
	switch (lcl_dir) {
	case 0:
		return Motion::LEFT;
	case 1:
		return Motion::RIGHT;
	case 2:
		return Motion::BACK;
	case 3:
		return Motion::FORWARD;
	default:
		return Motion::NONE;
	}
}

uint8_t AdatiSearch(const Maze& maze, const MazeLocation& maze_location, const XY& goal) {
	StepMap stepmap;
	calculate_stepmap(stepmap, maze, goal, maze_location.glb_mylocation);

	uint8_t next_dir = 2;
	uint16_t next_step = stepmap.get_step(maze_location.glb_mylocation) - 1;

	if ((maze.get_wall_status_xyd(maze_location.glb_mylocation, maze_location.convert_dir_lcl2lglb(1)) != WALL_SEEN)
		&& (next_step == stepmap.get_step(maze_location.glb_mylocation + directions[maze_location.convert_dir_lcl2lglb(1)]))) {
		next_dir = 1;
	}
	if ((maze.get_wall_status_xyd(maze_location.glb_mylocation, maze_location.convert_dir_lcl2lglb(3)) != WALL_SEEN)
		&& (next_step == stepmap.get_step(maze_location.glb_mylocation + directions[maze_location.convert_dir_lcl2lglb(3)]))) {
		next_dir = 3;
	}
	if ((maze.get_wall_status_xyd(maze_location.glb_mylocation, maze_location.convert_dir_lcl2lglb(0)) != WALL_SEEN)
		&& (next_step == stepmap.get_step(maze_location.glb_mylocation + directions[maze_location.convert_dir_lcl2lglb(0)]))) {
		next_dir = 0;
	}

	return next_dir;
}



void update_map(Maze* map, Maze* ans, MazeLocation m) {
	int8_t wall_lcl0 = ans->get_wall_status_xyd(m.glb_mylocation, m.convert_dir_lcl2lglb(0));
	//printf("%d\n", wall_lcl0);
	int8_t wall_lcl1 = ans->get_wall_status_xyd(m.glb_mylocation, m.convert_dir_lcl2lglb(1));
	//printf("%d\n", wall_lcl1);
	int8_t wall_lcl3 = ans->get_wall_status_xyd(m.glb_mylocation, m.convert_dir_lcl2lglb(3));
	//printf("%d\n",wall_lcl3);
	map->set_wall_status_xyd(m.glb_mylocation, m.convert_dir_lcl2lglb(0), wall_lcl0);
	map->set_wall_status_xyd(m.glb_mylocation, m.convert_dir_lcl2lglb(1), wall_lcl1);
	map->set_wall_status_xyd(m.glb_mylocation, m.convert_dir_lcl2lglb(3), wall_lcl3);
}

void test_adati() {
	Maze answer;

	answer.set_maze("AllJapan_001_1980_classic___16x16.json");
	std::cout << "answer\n";
	answer.disp();

	Maze map;
	std::cout << "map\n";
	map.disp();

	XY start{ 0,0 };
	XY goal{ 15,15 };

	MazeLocation car;
	car.glb_mylocation = start;
	
	char c;
	int i = 0;
	while (car.glb_mylocation != goal) {
		map.set_cell_status_xy(car.glb_mylocation,1);/////////
		//wallsencer grid MazeLocation
		update_map(&map,&answer,car);//ここのタイミングで迷路情報の更新を行う
		map.disp();///////
		
		uint8_t next_dir = AdatiSearch(map, car,goal);

		/*StepMap stepmap;
		calculate_stepmap(stepmap,map,goal,car.glb_mylocation);
		

		uint8_t next_dir = 2;
		uint16_t next_step = stepmap.get_step(car.glb_mylocation) - 1;
		printf("i am in (%d,%d,%d)\n",car.glb_mylocation.x,car.glb_mylocation.y,car.glb_forward_dir);
		printf("next %d\n",next_step);
		
		//MazeLocation grid stepmap
		if ((map.get_wall_status_xyd(car.glb_mylocation, car.convert_dir_lcl2lglb(1)) != WALL_SEEN)
			&& (next_step == stepmap.get_step(car.glb_mylocation + directions[car.convert_dir_lcl2lglb(1)]))) {
			next_dir = 1;
		}
		if ((map.get_wall_status_xyd(car.glb_mylocation, car.convert_dir_lcl2lglb(3)) != WALL_SEEN)
			&& (next_step == stepmap.get_step(car.glb_mylocation + directions[car.convert_dir_lcl2lglb(3)]))) {
			next_dir = 3;
		}
		if ((map.get_wall_status_xyd(car.glb_mylocation, car.convert_dir_lcl2lglb(0)) != WALL_SEEN) 
			&& (next_step == stepmap.get_step(car.glb_mylocation + directions[car.convert_dir_lcl2lglb(0)]))) {
			next_dir = 0;
		}*/
		//-------------------------------------------------------
		printf("i will go to %d\n",next_dir);//////////
		car.go_to(next_dir);

		map.set_cell_status_xy(car.glb_mylocation,3);/////
		map.disp();//////
		printf("i am in (%d,%d,%d)\n",car.glb_mylocation.x,car.glb_mylocation.y,car.glb_forward_dir);//////
		printf("====================================================\n");////////
		scanf("%c",&c);///////
	}
	printf("end\n");
}

int main(int argc, char** argv) {
	/*srand((unsigned int)time(NULL));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(640,640);
	glutCreateWindow("test");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutIdleFunc(idle);
	Init();*/
	
	
	//p->suround();
	//p->a_star(&property,dist);
	//init_for_extending_wall();
	//by_extending_wall();
	
	///////glutMainLoop();
	/*Grid_set_cell_status_xy(&ctest, 0, 0, 3);
	Grid_set_cell_status_xy(&ctest,15,15,3);
	Grid_set_cell_status_xy(&ctest, 0, 15, 3);
	Grid_set_cell_status_xy(&ctest, 15, 0, 3);*/
	//int x = Grid_set_wall_status_xyd(&ctest,15,2,3,3);
	//Grid_disp_ver_wall(&ctest);
	/*Maze ctest;
	ctest.set_outer_wall();
	ctest.set_maze("AllJapan_001_1980_classic___16x16.json");
	printf("%d\n", ctest.get_wall_status_xyd(0, 0, 0));
	ctest.disp();
	Maze cptest(ctest);
	Maze cptest2 = ctest;
	cptest.disp();
	cptest2.disp();
	printf("%d %d %d\n",ctest.cell,cptest.cell,cptest2.cell);*/
	/*XY a{0,0};
	XY b{ 1,0 };
	XY c{-1,0};
	for (int i = 0; i < 4;i++) {
		printf("%d\n", ctest.get_wall_status_xyd(a, i));
	}
	for (int i = 0; i < 4; i++) {
		printf("%d\n", ctest.get_wall_status_xyd(b, i));
	}
	for (int i = 0; i < 4; i++) {
		printf("%d\n", ctest.get_wall_status_xyd(c, i));
	}
	/*XY start{1,0};
	XY goal{ 5,6 };

	StepMap map;
	calculate_stepmap(map,ctest, goal, start);
	MazeLocation test;
	test.go_forward();
	test.go_to_right();
	test.go_to_left();
	test.go_to_left();
	test.back();
	test.go_forward();
	printf("%d %d %d\n",test.glb_mylocation.x,test.glb_mylocation.y,test.glb_forward_dir);
	printf("%d\n", test.convert_dir_glb2lcl(0));
	printf("%d\n", test.convert_dir_glb2lcl(1));
	printf("%d\n", test.convert_dir_glb2lcl(2));
	printf("%d\n", test.convert_dir_glb2lcl(3));
	printf("%d\n", test.detect_next_motion(XY(1,2)));
	printf("%d\n", test.detect_next_motion(XY(3, 2)));
	printf("%d\n", test.detect_next_motion(XY(2, 1)));
	printf("%d\n", test.detect_next_motion(XY(2, 3)));*/
	
	test_adati();
	/*MazeLocation ml;
	XY s(1, 1);
	ml.glb_mylocation = s;
	ml.glb_forward_dir = 0;
	XY n(0,1);
	printf("%d\n",ml.detect_next_motion(n));*/

	/*XY a{0,0};
	XY b{ 0,0 };
	XY c{ 1,0 };
	if (a==b) {
		printf("yes\n");
	}
	if (a==c) {
		printf("yes1\n");
	}
	if (a!=b) {
		printf("yes2\n");
	}
	if (a!=c) {
		printf("yes3\n");
	}*/
}
