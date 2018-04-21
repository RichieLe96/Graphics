#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include<stdio.h>
#include<stdlib.h>

static GLfloat theta[] = {0.0, 0.0, 0.0};

GLfloat vertices[][3] = {
	{-1.0, -1.0, -1.0},
	{1.0, -1.0, -1.0},
	{1.0, 1.0, -1.0},
	{-1.0, 1.0, -1.0},
	{-1.0, -1.0, 1.0},
	{1.0, -1.0, 1.0},
	{1.0, 1.0, 1.0},
	{-1.0, 1.0, 1.0}
};

//specify light properties below
	GLfloat light0_pos[] = {2.0, 2.0, 2.0, 0.0};
	GLfloat light0_spec[] = {0.0, 0.0, 1.0, 1.0};
	GLfloat light0_amb[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat light0_diff[] = {1.0, 1.0, 1.0, 1.0};

//specify material properties below
	typedef struct materialStruct{
		GLfloat amb[4];
		GLfloat diff[4];
		GLfloat spec[4];
		GLfloat shine;
	} materialStruct;

	//for the shelves and chair
	materialStruct redPlastic = {
		{0.000, 0.000, 0.000},
		{0.500, 0.000, 0.000},
		{0.700, 0.600, 0.600},
		100.0
	};

	materialStruct blackPlastic = {
		{0.000, 0.000, 0.000},
		{0.000, 0.000, 0.000},
		{0.000, 0.000, 0.000},
		0.0
	};

	//for the walls
	materialStruct pewter = {
		{0.106, 0.059, 0.114},
		{0.427, 0.471, 0.541},
		{0.333, 0.333, 0.522},
		9.85
	};

	//wood things
	materialStruct gold = {
		{0.247, 0.199, 0.075},
		{0.752, 0.606, 0.226},
		{0.628, 0.556, 0.366},
		51.2
	};

	materialStruct *shelfChair;
	materialStruct *walls;
	materialStruct *wood;
	materialStruct *knobs;

void coordinate(void){
	//this function draws x, y, z coordinates
	glColor3f(1.0, 1.0, 1.0);

	//x coordinate
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'Z');
	glRasterPos3f(1.8, 0.0, 0.0);

	glBegin(GL_LINES);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(2.0, 0.0, 0.0);
	glEnd();

	//y coordinate
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'X');
	glRasterPos3f(0.0, 1.8, 0.0);

	glBegin(GL_LINES);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, 2.0, 0.0);
	glEnd();

	//z coordinate
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'Y');
	glRasterPos3f(0.0, 0.0, 1.8);

	glBegin(GL_LINES);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, 0.0, 2.0);
	glEnd();
}

void polygon(int a, int b, int c, int d){
	//draws a polygon with the list of vertices
	glBegin(GL_POLYGON);
		glVertex3fv(vertices[a]);
		glVertex3fv(vertices[b]);
		glVertex3fv(vertices[c]);
		glVertex3fv(vertices[d]);
	glEnd();
}

void wall(void){
	walls = &pewter;
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, walls->diff);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, walls->spec);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, walls->amb);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, walls->shine);

	//back wall
	glPushMatrix();
		glTranslatef(0.0, 0.0, -5.0);
		glScalef(10.0, 10.0, 0.1);
		glutSolidCube(1.0);
	glPopMatrix();

	//left wall
	glPushMatrix();
		glTranslatef(-5.0, 0.0, 0.0);
		glScalef(0.1, 10.0, 10.0);
		glutSolidCube(1.0);
	glPopMatrix();
 
	//right wall
	glPushMatrix();
		glTranslatef(5.0, 0.0, 0.0);
		glScalef(0.1, 10.0, 10.0);
		glutSolidCube(1.0);
	glPopMatrix();

	//roof
	glPushMatrix();
		glTranslatef(0.0, 5.0, 0.0);
		glScalef(10.0, 0.1, 10.0);
		glutSolidCube(1.0);
	glPopMatrix();

	//floor
	glPushMatrix();
		glTranslatef(0.0, -5.0, 0.0);
		glScalef(10.0, 0.1, 10.0);
		glutSolidCube(1.0);
	glPopMatrix();
}

void shelf(void){
	shelfChair = &redPlastic;
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, shelfChair->diff);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, shelfChair->spec);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, shelfChair->amb);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shelfChair->shine);

	glPushMatrix();
		glTranslatef(-4.5, 1.0, 2.0);
		glScalef(1.0, 1.0, 0.1);
		glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-4.5, 1.0, -2.0);
		glScalef(1.0, 1.0, 0.1);
		glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-4.5, 1.0, 0.0);
		glScalef(1.0, 0.1, 4.0);
		glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(1.0, 2.0, -4.5);
		glScalef(4.0, 0.1, 1.0);
		glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(3.0, 2.0, -4.5);
		glScalef(0.1, 1.0, 1.0);
		glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-1.0, 2.0, -4.5);
		glScalef(0.1, 1.0, 1.0);
		glutSolidCube(1.0);
	glPopMatrix();

	wood = &gold;
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, wood->diff);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, wood->spec);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, wood->amb);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, wood->shine);

	glPushMatrix();
		glTranslatef(-4.5, 1.25, 0.0);
		glRotatef(-90.0, 0.0, 1.0, 0.0);
		glScalef(0.5, 0.5, 0.5);
		glutSolidTeapot(1.0);
	glPopMatrix();
}

void chair(void){
	wood = &gold;
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, wood->diff);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, wood->spec);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, wood->amb);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, wood->shine);

	glTranslatef(1.0, -3.5, -1.0);

	glPushMatrix();
		glTranslatef(0.0, 0.0, 0.0);
		glScalef(1.5, 0.1, 1.5);
		glutSolidCube(1.0);
    glPopMatrix();

	shelfChair = &redPlastic;
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, shelfChair->diff);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, shelfChair->spec);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, shelfChair->amb);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shelfChair->shine);

    //front right chair leg
    glPushMatrix();
		glTranslatef(0.75, -0.75, 0.75);
		glScalef(0.25, 1.5, 0.25);
		glutSolidCube(1.0);
    glPopMatrix();

	//front left chair leg
    glPushMatrix();
		glTranslatef(-0.75, -0.75, 0.75);
		glScalef(0.25, 1.5, 0.25);
		glutSolidCube(1.0);
    glPopMatrix();

	//back right chair leg
    glPushMatrix();
		glTranslatef(0.75, -0.75, -0.75);
		glScalef(0.25, 1.5, 0.25);
		glutSolidCube(1.0);
    glPopMatrix();

    //chair leg
    glPushMatrix();
		glTranslatef(-0.75, -0.75, -0.75);
		glScalef(0.25, 1.5, 0.25);
		glutSolidCube(1.0);
    glPopMatrix();

	//chair back
    glPushMatrix();
		glTranslatef(0.0, 0.75, 0.75); 
		glScalef(1.75, 1.75, 0.1);
		glutSolidCube(1.0);
    glPopMatrix();
}

void table(void){
	wood = &gold;
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, wood->diff);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, wood->spec);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, wood->amb);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, wood->shine);

	glPushMatrix();
		glTranslatef(0.0, 0.75, -2.0);
		glScalef(5.0, 0.1, 2.0);
		glutSolidCube(1.0);
	glPopMatrix();

	shelfChair = &redPlastic;
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, shelfChair->diff);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, shelfChair->spec);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, shelfChair->amb);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shelfChair->shine);

	glPushMatrix();
		glTranslatef(2.25, -0.35, -1.25);
		glScalef(0.25, 2.25, 0.25);
		glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-2.25, -0.35, -1.25);
		glScalef(0.25, 2.25, 0.25);
		glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(2.25, -0.35, -2.75);
		glScalef(0.25, 2.25, 0.25);
		glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-2.25, -0.35, -2.75);
		glScalef(0.25, 2.25, 0.25);
		glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(1.5, 1.25, -1.5);
		glRotatef(135.0, 0.0, 1.0, 0.0);
		glScalef(0.5, 0.5, 0.5);
		glutSolidTeapot(1.0);
	glPopMatrix();
}

void closet(void){
	knobs = &blackPlastic;
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, knobs->diff);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, knobs->spec);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, knobs->amb);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, knobs->shine);

	//thing in the back of the closet to make it look black
	glPushMatrix();
		glTranslatef(-4.0, 0.5, -3.75);
		glScalef(2.0, 4.0, 0.1);
		glutSolidCube(1.0);
	glPopMatrix();

	//right knob
	glPushMatrix();
		glTranslatef(-3.75, 0.5, -3.0);
		glScalef(0.1, 0.1, 0.1);
		glutSolidSphere(1.0, 100, 100);
	glPopMatrix();

	//left knob
	glPushMatrix();
		glTranslatef(-4.5, 0.5, -2.5);
		glScalef(0.1, 0.1, 0.1);
		glutSolidSphere(1.0, 100, 100);
	glPopMatrix();

	wood = &gold;
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, wood->diff);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, wood->spec);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, wood->amb);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, wood->shine);

	//left wall
	glPushMatrix();
		glTranslatef(-5.0, 0.5, -3.5);
		glScalef(0.1, 4.0, 1.0);
		glutSolidCube(1.0);
	glPopMatrix();

	//right wall
	glPushMatrix();
		glTranslatef(-3.0, 0.5, -3.5);
		glScalef(0.1, 4.0, 1.0);
		glutSolidCube(1.0);
	glPopMatrix();

	//start of shelves
	glPushMatrix();
		glTranslatef(-4.0, 2.5, -3.5);
		glScalef(2.0, 0.1, 1.0);
		glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-4.0, 2.0, -3.5);
		glScalef(2.0, 0.1, 1.0);
		glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-4.0, 1.0, -3.5);
		glScalef(2.0, 0.1, 1.0);
		glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-4.0, 0.0, -3.5);
		glScalef(2.0, 0.1, 1.0);
		glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-4.0, -1.0, -3.5);
		glScalef(2.0, 0.1, 1.0);
		glutSolidCube(1.0);
	glPopMatrix();
	//end of shelves

	//right door
	glPushMatrix();
		glTranslatef(-3.5, 0.5, -3.0);
		glScalef(1.0, 4.0, 0.1);
		glutSolidCube(1.0);
	glPopMatrix();

	//left door
	glPushMatrix();
		glTranslatef(-4.65, 0.5, -2.75);
		glRotatef(-45.0, 0.0, 1.0, 0.0);
		glScalef(1.0, 4.0, 0.1);
		glutSolidCube(1.0);
	glPopMatrix();
}

void colorcube(void){
	wall();
	shelf();
	chair();
	table();
	closet();
}

void display(void){
	//display callback, clear frame buffer and z buffer, rotate cube and draw, swap buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glRotatef(theta[0], 1.0, 0.0, 0.0);
	glRotatef(theta[1], 0.0, 1.0, 0.0);
	glRotatef(theta[2], 0.0, 0.0, 1.0);

	//coordinate();
	colorcube();

	glFlush();
	glutSwapBuffers();
}

void mykey(unsigned char key, int x, int y){
	switch(key){
		case 'x':
			theta[0] = theta[0] + 10;
			glutPostRedisplay();
			break;
		case 'y':
			theta[1] = theta[1] + 10;
			glutPostRedisplay();
			break;
		case 'z':
			theta[2] = theta[2] + 10;
			glutPostRedisplay();
			break;
		case 'a':
			theta[0] = theta[0] + 10;
			glutPostRedisplay();
			break;
		case 'b':
			theta[1] = theta[1] + 10;
			glutPostRedisplay();
			break;
		case 'c':
			theta[2] = theta[2] + 10;
			glutPostRedisplay();
			break;
		case 'q':
			exit(0);
			break;
		default:
			break;
	}
}

void myReshape(int w, int h){
	glViewport(0.0, 0.0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if(w <= h)
		glOrtho(-10.0, 10.0, -10.0 * (GLfloat) h / (GLfloat) w, 10.0 * (GLfloat) h / (GLfloat) w, -10.0, 10.0);
	else
		glOrtho(-10.0 * (GLfloat) h / (GLfloat) w, 10.0 * (GLfloat) h / (GLfloat) w, -10.0, 10.0, -10.0, 10.0);

	glMatrixMode(GL_MODELVIEW);
}

void init(){
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);

	//specify light properties:
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light0_spec);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diff);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light0_amb);
}

int main(int argc, char **argv){
	glutInit(&argc, argv);

	//need both double buffering and z buffer
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow(" ");
	glutReshapeFunc(myReshape);
	glutDisplayFunc(display);
	glutKeyboardFunc(mykey);
	init();
	glutMainLoop();
}
