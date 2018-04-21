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

	materialStruct pewter = {
		{0.106, 0.059, 0.114},
		{0.427, 0.471, 0.541},
		{0.333, 0.333, 0.522},
		9.85
	};

	materialStruct *obj;

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

void colorcube(void){
	obj = &pewter;
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, obj->diff);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, obj->spec);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, obj->amb);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, obj->shine);

    //big circle
    glPushMatrix();
        glTranslatef(0.0, -2.0, 0.0);
        glutSolidSphere(2.0, 100, 100);
    glPopMatrix();

    //big square
    glPushMatrix();
        glTranslatef(-1.5, 0.75, 0.0);
        glRotatef(45.0, 0.0, 1.0, 1.0);
        glutSolidCube(2.0);
    glPopMatrix();

    //medium circle
    glPushMatrix();
        glTranslatef(0.0, 2.0, -1.0);
        glutSolidSphere(1.0, 100, 100);
    glPopMatrix();

    //small square
    glPushMatrix();
        glTranslatef(1.75, 2.5, -1.0);
        glRotatef(200.0, 0.0, 1.0, 1.0);
        glutSolidCube(1.5);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(1.5, 3.8, -1.0);
        glutSolidSphere(0.75, 100, 100);
    glPopMatrix();
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