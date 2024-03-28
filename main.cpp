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


auto* p = new Grid(WID,HIG);
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
}

int main(int argc, char** argv) {
	srand((unsigned int)time(NULL));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(640,640);
	glutCreateWindow("test");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutIdleFunc(idle);
	Init();
	
	
	//p->suround();
	//p->a_star(&property,dist);
	//init_for_extending_wall();
	//by_extending_wall();
	
	glutMainLoop();
}
