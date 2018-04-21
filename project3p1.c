#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include<stdio.h>
#include<stdlib.h>

static GLfloat theta[] = {0.0, 0.0, 0.0};

GLfloat vertices[][3] = {
    {-1.0, -1.0, -1.0}, //0
    {1.0, -1.0, -1.0},  //1
    {1.0, 1.0, -1.0},   //2
    {-1.0, 1.0, -1.0},  //3
    {-1.0, -1.0, 1.0},  //4
    {1.0, -1.0, 1.0},   //5
    {1.0, 1.0, 1.0},    //6
    {-1.0, 1.0, 1.0}    //7
};

//specify light properties below
GLfloat light0_pos[] = {5.0, 4.0, 5.0, 0.0};
GLfloat light0_spec[] = {1.0, 1.0, 1.0, 0.0};
GLfloat light0_amb[] = {1.0, 1.0, 1.0, 0.0};
GLfloat light0_diff[] = {1.0, 1.0, 1.0, 0.0};

//specify material properties below
typedef struct materialStruct{
    GLfloat amb[4];
    GLfloat diff[4];
    GLfloat spec[4];
    GLfloat shine;
} materialStruct;

//for the castle and floor
materialStruct gold = {
    {0.247, 0.199, 0.074},
    {0.751, 0.606, 0.226},
    {0.628, 0.555, 0.366},
    51.2
};

//for the roof jawn
materialStruct bronze = {
    {0.213, 0.128, 0.054},
    {0.714, 0.428, 0.181},
    {0.394, 0.272, 0.167},
    100.0
};

materialStruct *outline;
materialStruct *roof;

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
    outline = &gold;

    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, outline->diff);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, outline->spec);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, outline->amb);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, outline->shine);

    GLUquadricObj *cyl;
    cyl = gluNewQuadric();
    gluQuadricDrawStyle(cyl, GLU_FILL);

    //base
    glPushMatrix();
        glTranslatef(0.0, -2.0, 0.0);
        glScalef(5.0, 0.1, 5.0);
        glutSolidCube(1.0);
    glPopMatrix();

    //right doorway pillar
    glPushMatrix();
        glTranslatef(0.75, -1.0, 1.0);
        glScalef(0.5, 2.0, 0.5);
        glRotatef(90.0, 1.0, 0.0, 0.0);
        gluCylinder(cyl, 0.5, 0.5, 0.5, 10.0, 10.0);
    glPopMatrix();

    //left doorway pillar
    glPushMatrix();
        glTranslatef(-0.75, -1.0, 1.0);
        glScalef(0.5, 2.0, 0.5);
        glRotatef(90.0, 1.0, 0.0, 0.0);
        gluCylinder(cyl, 0.5, 0.5, 0.5, 10.0, 10.0);
    glPopMatrix();

    //left middle doorway pillar
    glPushMatrix();
        glTranslatef(-1.25, -0.65, -0.5);
        glScalef(0.75, 2.65, 0.75);
        glRotatef(90.0, 1.0, 0.0, 0.0);
        gluCylinder(cyl, 0.5, 0.5, 0.5, 10.0, 10.0);
    glPopMatrix();

    //right middle doorway pillar
    glPushMatrix();
        glTranslatef(1.25, -0.65, -0.5);
        glScalef(0.75, 2.65, 0.75);
        glRotatef(90.0, 1.0, 0.0, 0.0);
        gluCylinder(cyl, 0.5, 0.5, 0.5, 10.0, 10.0);
    glPopMatrix();

    //left back doorway pillar
    glPushMatrix();
        glTranslatef(-1.25, -0.5, -2.0);
        glScalef(0.5, 3.0, 0.5);
        glRotatef(90.0, 1.0, 0.0, 0.0);
        gluCylinder(cyl, 0.5, 0.5, 0.5, 10.0, 10.0);
    glPopMatrix();

    //left back doorway pillar
    glPushMatrix();
        glTranslatef(1.25, -0.5, -2.0);
        glScalef(0.5, 3.0, 0.5);
        glRotatef(90.0, 1.0, 0.0, 0.0);
        gluCylinder(cyl, 0.5, 0.5, 0.5, 10.0, 10.0);
    glPopMatrix();

    //left mid wall
    glPushMatrix();
        glTranslatef(-1.25, -1.55, -1.25);
        glScalef(0.1, 1.0, 1.0);
        glutSolidCube(1.0);
    glPopMatrix();

    //right mid wall
    glPushMatrix();
        glTranslatef(1.25, -1.55, -1.25);
        glScalef(0.1, 1.0, 1.0);
        glutSolidCube(1.0);
    glPopMatrix();

    //front left cone
    glPushMatrix();
        glTranslatef(-1.25, -0.75, -0.5);
        glScalef(0.5, 0.5, 0.5);
        glRotatef(-90.0, 1.0, 0.0, 0.0);
        glutSolidCone(1.0, 1.0, 100, 100);
    glPopMatrix();

    //front right cone
    glPushMatrix();
        glTranslatef(1.25, -0.75, -0.5);
        glScalef(0.5, 0.5, 0.5);
        glRotatef(-90.0, 1.0, 0.0, 0.0);
        glutSolidCone(1.0, 1.0, 100, 100);
    glPopMatrix();

    //back left cone
    glPushMatrix();
        glTranslatef(-1.25, -0.5, -2.0);
        glScalef(0.45, 0.45, 0.45);
        glRotatef(-90.0, 1.0, 0.0, 0.0);
        glutSolidCone(1.0, 1.0, 100, 100);
    glPopMatrix();

    //back right cone
    glPushMatrix();
        glTranslatef(1.25, -0.5, -2.0);
        glScalef(0.45, 0.45, 0.45);
        glRotatef(-90.0, 1.0, 0.0, 0.0);
        glutSolidCone(1.0, 1.0, 100, 100);
    glPopMatrix();

    //left angled wall
    glPushMatrix();
        glTranslatef(-1.0, -1.5, 0.4);
        glRotatef(220.0, 0.0, 1.0, 0.0);
        glScalef(0.1, 1.0, 1.8);
        glutSolidCube(1.0);
    glPopMatrix();

    //right angled wall
    glPushMatrix();
        glTranslatef(1.0, -1.5, 0.4);
        glRotatef(140.0, 0.0, 1.0, 0.0);
        glScalef(0.1, 1.0, 1.8);
        glutSolidCube(1.0);
    glPopMatrix();

    roof = &bronze;
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, roof->diff);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, roof->spec);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, roof->amb);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, roof->shine);

    //back wall
    glPushMatrix();
        glTranslatef(0.0, -1.5, -2.0);
        glScalef(2.0, 1.0, 0.1);
        glutSolidCube(1.0);
    glPopMatrix();

    //top thing
    glPushMatrix();
        glTranslatef(0.0, -1.0, 1.0);
        glScalef(2.0, 0.1, 1.0);
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

    //coordinate();
    colorcube();

    glFlush();
    glutSwapBuffers();
}

void mykey(unsigned char key, int x, int y){
    switch(key){
        case 'x':
            theta[0] = theta[0] + 1;
            glutPostRedisplay();
            break;
        case 'y':
            theta[1] = theta[1] + 1;
            glutPostRedisplay();
            break;
        case 'z':
            theta[2] = theta[2] + 1;
            glutPostRedisplay();
            break;
        case 'a':
            theta[0] = theta[0] + 1;
            glutPostRedisplay();
            break;
        case 'b':
            theta[1] = theta[1] + 1;
            glutPostRedisplay();
            break;
        case 'c':
            theta[2] = theta[2] + 1;
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
        glOrtho(-4.0, 4.0, -4.0 * (GLfloat) h / (GLfloat) w, 4.0 * (GLfloat) h / (GLfloat) w, -10.0, 10.0);
    else
        glOrtho(-4.0 * (GLfloat) h / (GLfloat) w, 4.0 * (GLfloat) h / (GLfloat) w, -4.0, 4.0, -10.0, 10.0);

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