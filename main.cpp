#include <windows.h>
#define PI 3.14159265358979323846
#include<math.h>
#include <GL/gl.h>
#include <GL/glut.h>

void ground()
{
    glColor3ub(153, 153, 102);
    glBegin(GL_QUADS);
    glVertex2d(1140, 450);
    glVertex2d(1140, 420);
    glVertex2d(960, 360);
    glVertex2d(960, 390);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2d(1080, 240);
    glVertex2d(1080, 210);
    glVertex2d(960, 150);
    glVertex2d(960, 180);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2d(1080, 150);
    glVertex2d(1080, 120);
    glVertex2d(990, 0);
    glVertex2d(960, 0);
    glEnd();

    glColor3ub(34, 139, 34);
    glBegin(GL_POLYGON);
    glVertex2d(0, 480);
    glVertex2d(960, 480);
    glVertex2d(1140, 450);
    glVertex2d(960,390);
    glVertex2d(1080,360);
    glVertex2d(1080,240);
    glVertex2d(960,180);
    glVertex2d(1080,150);
    glVertex2d(960,0);
    glVertex2d(0,0);
    glVertex2d(0, 480);
    glEnd();
}

void sky()
{
    glBegin(GL_QUADS);
    glColor3ub(51, 204, 255);//1st color
    glVertex2d(0, 840);
    glVertex2d(1920, 840);
    glColor3ub( 0, 102, 204);//2nd color
    glVertex2d(1920, 1080);
    glVertex2d(0, 1080);
    glEnd();
}

void river()
{
    glBegin(GL_QUADS);
    glColor3ub(0, 76, 153);
    glVertex2d(0, 840);
    glColor3ub(0, 128, 255);
    glVertex2d(1920, 840);
    glColor3ub(102, 178, 255);
    glVertex2d(1920, 0);
    glVertex2d(0, 0);
    glEnd();
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    river();
    ground();
    sky();

    glFlush();
}

void init(void)
{
    glClearColor( 1.0, 1.0, 1.0, 1.0);
    glOrtho(0, 1920, 0, 1080, -1, 1);
}
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1920, 1080);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Village Scenario");
    init();
    glutDisplayFunc(display);

    glutMainLoop();
    return 0;
}
