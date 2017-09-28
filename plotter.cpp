#include <string.h>
#include <GL/glut.h>

//float ang = 0.0f;

void initRendering() {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glShadeModel(GL_SMOOTH);
}

void handleKeypress(unsigned char key, int x, int y) {
	switch (key) {
		case 27:
			exit(0);
	}
}

void handleResize(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (double) w / (double) h, 1.0, 200.0);
}

void drawScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(0.0f, 0.0f, -7.0f);

	glBegin(GL_LINES);
		glVertex3f(-5.0f, 0.0f, 0.0f);
		glVertex3f(5.0f, 0.0f, 0.0f);
	glEnd();

	glBegin(GL_LINES);
		glVertex3f(0.0f, -2.75f, 0.0f);
		glVertex3f(0.0f, 2.75f, 0.0f);
	glEnd();

	glutSwapBuffers();
}

void update(int value) {
	/*
	ang += 1;
	if (ang > 360.0f) {
		ang = 0.0f;
	}
	*/
	glutPostRedisplay();
	glutTimerFunc(50, update, 0);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(200, 200);
	initRendering();
	glutCreateWindow("Graph Plotter");
	glutFullScreen();
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(handleKeypress);
	glutReshapeFunc(handleResize);
	//glutTimerFunc(50, update, 0);
	glutMainLoop();
	return 0;
}