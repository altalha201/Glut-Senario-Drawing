#include <windows.h>
#define PI 3.14159265358979323846
#include<math.h>
#include <GL/gl.h>
#include <GL/glut.h>

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3ub(165, 255, 165);
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