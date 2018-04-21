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

	materialStruct silver = {
		{0.19, 0.19, 0.19},
		{0.51, 0.51, 0.51},
		{0.51, 0.51, 0.51},
		51.2
	};

    materialStruct polished = {
		{0.23, 0.23, 0.23},
		{0.28, 0.28, 0.28},
		{0.77, 0.77, 0.77},
		89.6
	};

    materialStruct white = {
        {1.0, 1.0, 1.0},
        {1.0, 1.0, 1.0},
        {1.0, 1.0, 1.0},
        90.0
    };

	materialStruct bronze = {
        {0.21, 0.13, 0.05},
        {0.71, 0.43, 0.18},
        {0.39, 0.27, 0.17},
        25.6
    };

	materialStruct brass = {
        {0.33, 0.22, 0.03},
        {0.78, 0.57, 0.11},
        {0.99, 0.94, 0.81},
        27.9
    };

    materialStruct pewter = {
		{0.11, 0.06, 0.11},
		{0.43, 0.48, 0.54},
		{0.33, 0.33, 0.52},
		9.85
	};

	materialStruct *silverObj;
    materialStruct *polishedObj;
    materialStruct *whiteObj;
	materialStruct *bronzeObj;
	materialStruct *brassObj;
    materialStruct *test;

void wall(void){
	silverObj = &silver;
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, silverObj->diff);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, silverObj->spec);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, silverObj->amb);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, silverObj->shine);

	//back wall
	glPushMatrix();
		glTranslatef(0.0, 0.0, -5.0);
		glScalef(15.0, 15.0, 0.1);
		glutSolidCube(1.0);
	glPopMatrix();

	//floor
	glPushMatrix();
		glTranslatef(0.0, -7.5, 2.55);
		glScalef(15.0, 0.1, 15.0);
		glutSolidCube(1.0);
	glPopMatrix();
}

void window(void){
	whiteObj = &white;
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, whiteObj->diff);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, whiteObj->spec);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, whiteObj->amb);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, whiteObj->shine);

	//right window
    glPushMatrix();
        glTranslatef(3.5, 2.0, -4.9);
        glScalef(2.5, 2.0, 0.1);
        glutSolidCube(1.0);
    glPopMatrix();

    polishedObj = &polished;
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, polishedObj->diff);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, polishedObj->spec);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, polishedObj->amb);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, polishedObj->shine);

    //left window
    glPushMatrix();
        glTranslatef(0.5, 2.0, -4.9);
        glScalef(2.5, 2.0, 0.1);
        glutSolidCube(1.0);
    glPopMatrix();
}

void stairs(void){
	bronzeObj = &bronze;
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, bronzeObj->diff);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, bronzeObj->spec);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, bronzeObj->amb);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, bronzeObj->shine);

	int i;
	double x = 4.0, y = -6.5, z = 7.0;
	for(i = 0; i < 8; i++){
		glPushMatrix();
			glTranslatef(x, y + (i * 0.5), z - i);
			glScalef(4.0, 0.1, 1.0);
			glutSolidCube(1.0);
		glPopMatrix();
	}

	polishedObj = &polished;
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, polishedObj->diff);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, polishedObj->spec);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, polishedObj->amb);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, polishedObj->shine);

	glPushMatrix();
		glTranslatef(2.0, -4.8, 3.75);
		//changing y spins like a top
		//changing x spins towards me
		//changing z spins like a pin
		glRotatef(295.0, 1.0, 0.0, 0.0);
		glScalef(0.1, 9.5, 1.0);
		glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(6.0, -4.8, 3.75);
		glRotatef(295.0, 1.0, 0.0, 0.0);
		glScalef(0.1, 9.5, 1.0);
		glutSolidCube(1.0);
	glPopMatrix();
}

void bed(void){
	brassObj = &brass;
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, brassObj->diff);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, brassObj->spec);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, brassObj->amb);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, brassObj->shine);

	glPushMatrix();
		glTranslatef(0.0, -2.0, -4.0);
		glScalef(5.5, 0.5, 2.0);
		glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0.0, -7.2, -4.0);
		glScalef(5.5, 0.5, 2.0);
		glutSolidCube(1.0);
	glPopMatrix();

	whiteObj = &white;
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, whiteObj->diff);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, whiteObj->spec);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, whiteObj->amb);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, whiteObj->shine);

	glPushMatrix();
		glTranslatef(0.0, -1.6, -4.0);
		glScalef(5.0, 0.25, 1.5);
		glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0.0, -6.8, -4.0);
		glScalef(5.0, 0.25, 1.5);
		glutSolidCube(1.0);
	glPopMatrix();

	polishedObj = &polished;
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, polishedObj->diff);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, polishedObj->spec);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, polishedObj->amb);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, polishedObj->shine);

	GLUquadricObj *cyl;
    cyl = gluNewQuadric();
    gluQuadricDrawStyle(cyl, GLU_FILL);

	glPushMatrix();
		glTranslatef(-2.0, -6.4, -4.75);
		gluCylinder(cyl, 0.3, 0.3, 1.5, 10.0, 10.0);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-2.0, -6.4, -3.25);
		glScalef(0.2, 0.2, 0.2);
		glutSolidSphere(1.5, 100, 100);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-2.0, -6.4, -4.75);
		glScalef(0.2, 0.2, 0.2);
		glutSolidSphere(1.5, 100, 100);
	glPopMatrix();
}

void upperFloor(void){
	bronzeObj = &bronze;
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, bronzeObj->diff);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, bronzeObj->spec);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, bronzeObj->amb);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, bronzeObj->shine);

	glPushMatrix();
		glTranslatef(0.0, -2.4, -2.4);
		glScalef(15.0, 0.1, 5.25);
		glutSolidCube(1.0);
	glPopMatrix();

	bed();
}

void desk(void){
	whiteObj = &white;
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, whiteObj->diff);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, whiteObj->spec);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, whiteObj->amb);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, whiteObj->shine);

	glPushMatrix();
		glTranslatef(-6.0, -6.0, 5.0);
		glScalef(1.5, 0.5, 5.0);
		glutSolidCube(1.0);
	glPopMatrix();

	polishedObj = &polished;
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, polishedObj->diff);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, polishedObj->spec);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, polishedObj->amb);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, polishedObj->shine);

	glPushMatrix();
		glTranslatef(-6.5, -6.8, 3.0);
		glScalef(-0.3, 1.25, 0.3);
		glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-5.5, -6.8, 3.0);
		glScalef(-0.3, 1.25, 0.3);
		glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-6.5, -6.8, 7.0);
		glScalef(-0.3, 1.25, 0.3);
		glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-5.5, -6.8, 7.0);
		glScalef(-0.3, 1.25, 0.3);
		glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-6.0, -7.2, 3.0);
		glRotatef(90.0, 0.0, 0.0, 1.0);
		glScalef(-0.3, 0.75, 0.3);
		glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-6.0, -7.2, 7.0);
		glRotatef(90.0, 0.0, 0.0, 1.0);
		glScalef(-0.3, 0.75, 0.3);
		glutSolidCube(1.0);
	glPopMatrix();
}

void lowerWalls(void){
	polishedObj = &polished;
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, polishedObj->diff);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, polishedObj->spec);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, polishedObj->amb);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, polishedObj->shine);

	glPushMatrix();
		glTranslatef(5.0, -5.0, -0.75);
		glScalef(5.0, 5.0, 0.1);
		glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(2.3, -5.0, -2.75);
		glScalef(0.1, 5.0, 4.6);
		glutSolidCube(1.0);
	glPopMatrix();
}

void display(void){
	//display callback, clear frame buffer and z buffer, rotate cube and draw, swap buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glRotatef(theta[0], 1.0, 0.0, 0.0);
	glRotatef(theta[1], 0.0, 1.0, 0.0);
	glRotatef(theta[2], 0.0, 0.0, 1.0);
	
	wall();
    window();
	stairs();
	upperFloor();
	desk();
	lowerWalls();

	glFlush();
	glutSwapBuffers();
}

void mykey(unsigned char key, int x, int y){
	switch(key){
		case 'x':
		case 'a':
			theta[0] = theta[0] + 10;
			glutPostRedisplay();
			break;
		case 'y':
		case 'b':
			theta[1] = theta[1] + 10;
			glutPostRedisplay();
			break;
		case 'z':
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

	if(w <= h) glOrtho(-15.0, 15.0, -15.0 * (GLfloat) h / (GLfloat) w, 15.0 * (GLfloat) h / (GLfloat) w, -15.0, 15.0);
	else glOrtho(-15.0 * (GLfloat) h / (GLfloat) w, 15.0 * (GLfloat) h / (GLfloat) w, -15.0, 15.0, -15.0, 15.0);

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
	glutInitWindowSize(700, 700);
	glutCreateWindow(" ");
	glutReshapeFunc(myReshape);
	glutDisplayFunc(display);
	glutKeyboardFunc(mykey);
	init();
	glutMainLoop();
}
