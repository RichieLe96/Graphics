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

//      back:           3       2
//                      0       1
//
//      front:          7       6
//                      4       5

//specify light properties below
    GLfloat light0_pos[] = {2.0, 2.0, 2.0, 0.0};
    GLfloat light0_spec[] = {0.0, 0.0, 1.0, 1.0};
    GLfloat light0_amb[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat light0_diff[] = {1.0, 1.0, 1.0, 1.0};

//specify material properties below
    GLfloat mat1_amb[] = {0.33, 0.22, 0.3, 1.0};
    GLfloat mat1_diff[] = {0.78, 0.57, 0.11, 1.0};
    GLfloat mat1_spec[] = {0.99, 0.91, 0.81, 1.0};
    GLfloat mat1_shine = 128.0;

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
    //to be filled in
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat1_diff);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat1_spec);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat1_amb);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, mat1_shine);
    glutSolidSphere(1.5, 100, 100);
}
void display(void){
    //display callback, clear frame buffer and z buffer, rotate cube $
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glRotatef(theta[0], 1.0, 0.0, 0.0);
    glRotatef(theta[1], 0.0, 1.0, 0.0);
    glRotatef(theta[2], 0.0, 0.0, 1.0);

    coordinate();
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
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);

    //specify light properties:
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light0_spec);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light0_diff);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light0_amb);

    //specify material properties:
/*     glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat1_diff);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat1_spec);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat1_amb);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, mat1_shine); */
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