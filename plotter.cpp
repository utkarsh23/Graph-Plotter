#include <string.h>
#include <GL/glut.h>
#include <cmath>
#include <vector>
#include <stdio.h>

using namespace std;

long long counter = 0;
double steps = 0.005;
int functionType, power;
vector<double> coefficients;
GLfloat rescalingFactor = 1.0f / 8.0f; //Manipulate only the second term to change scaling 

void functionInput() {
	printf("Trigonometric Functions:\n");
	printf("Enter 1,2,3,4,5,6 for sine, cosine, tangent, cosecant, secant, cotangent\n");
	printf("Polynomial functions:\n");
	printf("Enter 9\n");
	while (1) {
		printf("Enter your choice: ");
		scanf("%d", &functionType);
		if (((functionType > 0) && (functionType < 7)) || (functionType == 9)) {
			break;
		}
		else {
			printf("Wrong choice!\n");
		}
	}
	if (functionType == 9) {
		printf("Enter degree of the polynomial: ");
		scanf("%d", &power);
		double element;
		for (int s = 0; s <= power; s++) {
			printf("Enter coefficient of term with degree %d: ", s);
			scanf("%lf",  &element);
			coefficients.push_back(element);
		}
	}
}

double polynomialFunc(double v) {
	double toret = 0.0;
	for (int t = 0; t <= power; t++) {
		toret += coefficients[t] * pow(v, t);
	}
	return toret;
}

GLfloat operation(double val) {
	switch (functionType) {
		case 1:
			return (GLfloat) sin(val);
		case 2:
			return (GLfloat) cos(val);
		case 3:
			return (GLfloat) tan(val);
		case 4:
			return (GLfloat) 1.0 / sin(val);
		case 5:
			return (GLfloat) 1.0 / cos(val);
		case 6:
			return (GLfloat) 1.0 / tan(val);
		case 9:
			return (GLfloat) polynomialFunc(val);
		default:
			break;
	}
}

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
	double posPosition = 0.0;
	double negPosition = 0.0;
	double first, second;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(0.0f, 0.0f, -7.0f);

	glBegin(GL_LINES);
	glVertex3f(-5.1f, 0.0f, 0.0f);
	glVertex3f(5.1f, 0.0f, 0.0f);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(0.0f, -2.75f, 0.0f);
	glVertex3f(0.0f, 2.75f, 0.0f);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(0.0f, -2.75f, 0.0f);
	glVertex3f(0.0f, 2.75f, 0.0f);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glVertex3f(-0.1f,-2.65f,0.0f);
	glVertex3f(0.0f,-2.75f,0.0f);
	glVertex3f(0.1f,-2.65f,0.0f);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glVertex3f(-0.1f,2.65f,0.0f);
	glVertex3f(0.0f,2.75f,0.0f);
	glVertex3f(0.1f,2.65f,0.0f);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glVertex3f(-5.0,0.1,0.0f);
	glVertex3f(-5.1f,0.0f,0.0f);
	glVertex3f(-5.0f,-0.1f,0.0f);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glVertex3f(5.0,0.1,0.0f);
	glVertex3f(5.1f,0.0f,0.0f);
	glVertex3f(5.0f,-0.1f,0.0f);
	glEnd();

	glPushMatrix();
	glTranslatef(0.0f, 0.0f, -15.0f * rescalingFactor);

	glBegin(GL_LINES);
	for (long long i = 0; i < counter; i++) {
		posPosition += steps;
		negPosition -= steps;
		glVertex3f((GLfloat) posPosition, operation(posPosition), 0.0f);
		glVertex3f((GLfloat) posPosition + steps, operation(posPosition + steps), 0.0f);
		glVertex3f((GLfloat) negPosition, operation(negPosition), 0.0f);
		glVertex3f((GLfloat) negPosition - steps, operation(negPosition - steps), 0.0f);
	}

	glPopMatrix();
	glEnd();

	glutSwapBuffers();
}

void update(int value) {
	if (counter < pow(10,8))
		counter++;
	glutPostRedisplay();
	glutTimerFunc(1, update, 0);
}

int main(int argc, char** argv) {
	functionInput();
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
	glutTimerFunc(1, update, 0);
	glutMainLoop();
	return 0;
}