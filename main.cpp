#include <GL/gl.h>
#include <GL/glut.h>
#include <windows.h>
#include <math.h>
#include <stdio.h>

#define PI 3.14159265358979323846

bool isNight = false;

GLfloat cloud_position = 0.0;
GLfloat cloud_speed = 1.0;

GLfloat boat_position = 0.0;
GLfloat boat_speed = 3.0;

void cloud_movement(int value)
{
    if (cloud_position > 1450)
        cloud_position = -550;
    cloud_position += cloud_speed;
    glutPostRedisplay();
    glutTimerFunc(100, cloud_movement, 0);
}

void boat_movement(int value)
{
    if (boat_position < -700)
        boat_position = 1600;
    boat_position -= boat_speed;
    glutPostRedisplay();
    glutTimerFunc(100, boat_movement, 0);
}

void draw_solid_circle(GLfloat x, GLfloat y, GLfloat radius)
{
    int i, triangleAmount = 100;
    GLfloat twicePI = 2.0 * PI;

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);

    for(i = 0; i <= triangleAmount; i++)
    {
        glVertex2f(x + (radius * cos(i * twicePI / triangleAmount)),
                   y + (radius * sin(i * twicePI / triangleAmount)));
    }
    glEnd();
}

void draw_boat(int start_x, int start_y, int base[3], int shade[3], int sail[3])
{
    // base
    glColor3ub(base[0], base[1], base[2]);
    glBegin(GL_QUADS);
    glVertex2d(start_x, start_y);
    glVertex2d(start_x + 60, start_y - 30);
    glVertex2d(start_x + 360, start_y - 30);
    glVertex2d(start_x + 420, start_y);
    glEnd();

    // sail stand
    glColor3ub(102, 51, 0);
    glRectd(start_x + 235, start_y, start_x + 245, start_y + 300);

    // Shade
    glColor3ub(shade[0], shade[1], shade[2]);
    glBegin(GL_POLYGON);
    glVertex2d(start_x + 90, start_y);
    glVertex2d(start_x + 120, start_y + 120);
    glVertex2d(start_x + 270, start_y + 120);
    glVertex2d(start_x + 360, start_y + 90);
    glVertex2d(start_x + 390, start_y);
    glVertex2d(start_x + 90, start_y);
    glEnd();

    // sail
    glColor3ub(sail[0], sail[1], sail[2]);
    glBegin(GL_POLYGON);
    glVertex2d(start_x + 150, start_y + 180);
    glVertex2d(start_x + 140, start_y + 190);
    glVertex2d(start_x + 140, start_y + 290);
    glVertex2d(start_x + 150, start_y + 300);
    glVertex2d(start_x + 330, start_y + 240);
    glVertex2d(start_x + 320, start_y + 230);
    glVertex2d(start_x + 320, start_y + 130);
    glVertex2d(start_x + 330, start_y + 120);
    glVertex2d(start_x + 150, start_y + 180);
    glEnd();

}

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
    int c1[3], c2[3];

    if (isNight)
    {
        c1 = {208, 222, 236};
        c2 = {59, 65, 79};
    }
    else
    {
        c1 = {51, 204, 255};
        c2 = {0, 102, 204};
    }

    glBegin(GL_QUADS);
    glColor3ub(c1[0], c1[1], c1[2]);//1st color
    glVertex2d(0, 840);
    glVertex2d(1920, 840);
    glColor3ub(c2[0], c2[1], c2[2]);//2nd color
    glVertex2d(1920, 1080);
    glVertex2d(0, 1080);
    glEnd();
}

void clouds()
{
    glPushMatrix();

    glColor3ub(208, 222, 236);
    glTranslatef(cloud_position, 0.0, 0.0);

    draw_solid_circle(420.0, 960.0, 30);
    draw_solid_circle(480.0, 990.0, 50);
    draw_solid_circle(480.0, 960.0, 50);
    draw_solid_circle(570.0, 990.0, 50);
    draw_solid_circle(550.0, 960.0, 50);
    draw_solid_circle(620.0, 950.0, 40);

    glPopMatrix();
}

void hills()
{
    glColor3ub(155, 118, 83);
    glBegin(GL_POLYGON);
    glVertex2d(0, 840);
    glVertex2d(360, 930);
    glVertex2d(660, 870);
    glVertex2d(720, 840);
    glVertex2d(0, 840);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2d(720, 840);
    glVertex2d(840, 870);
    glVertex2d(930, 900);
    glVertex2d(1080, 930);
    glVertex2d(1140, 900);
    glVertex2d(1350, 870);
    glVertex2d(1410, 840);
    glVertex2d(720, 840);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2d(1410, 840);
    glVertex2d(1770, 960);
    glVertex2d(1860, 900);
    glVertex2d(1920, 870);
    glVertex2d(1920, 840);
    glVertex2d(1410, 840);
    glEnd();
}

void boats()
{
    // Moving boat
    glPushMatrix();
    glTranslatef(boat_position, 0.0, 0.0);
    int base_2[3] = {102, 0, 1}, shade_2[3] = {255, 153, 0}, sail_2[3] = {0, 0, 102};
    draw_boat(300, 650, base_2, shade_2, sail_2);
    glPopMatrix();

    // Non moving Boat
    int base_1[3] = {0, 0, 0}, shade_1[3] = {153, 76, 0}, sail_1[3] = {0, 0, 204};
    glColor3ub(204, 153, 0);
    glRectf(985.0, 300.0, 995.0, 450.0);
    glBegin(GL_QUADS);
    glVertex2d(990, 392);
    glVertex2d(1140, 302);
    glVertex2d(1140, 298);
    glVertex2d(990, 388);
    glEnd();
    draw_boat(1110, 300, base_1, shade_1, sail_1);
}

void light_source()
{
    if (isNight)
    {
        glColor3ub(246, 241, 213);
        draw_solid_circle(120.0, 960.0, 90);
    }
    else
    {
        glColor3ub(253, 184, 19);
        draw_solid_circle(1680.0, 900.0, 150);
    }
}

void river()
{
    int c1[3], c2[3], c3[3];

    if (isNight)
    {
        c1 = {64, 64, 64};
        c2 = {96, 96, 96};
        c3 = {192, 192, 192};
    }
    else
    {
        c1 = {0, 76, 153};
        c2 = {0, 128, 255};
        c3 = {102, 178, 255};
    }
    glBegin(GL_QUADS);
    glColor3ub(c1[0], c1[1], c1[2]);
    glVertex2d(0, 840);
    glColor3ub(c2[0], c2[1], c2[2]);
    glVertex2d(1920, 840);
    glColor3ub(c3[0], c3[1], c3[2]);
    glVertex2d(1920, 0);
    glVertex2d(0, 0);
    glEnd();
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    sky();
    light_source();
    clouds();
    hills();
    river();
    ground();
    boats();


    glFlush();
}

void fun_keys(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 'n':
            isNight = true;
            break;
        case 'd':
            isNight = false;
            break;
        case 's':
            cloud_speed = 0.0;
            boat_speed = 0.0;
            break;
        case 'o':
            cloud_speed = 1.0;
            boat_speed = 3.0;
            break;
        case '+':
            if (cloud_speed <= 10)
                cloud_speed++;
            if (boat_speed <= 15)
                boat_speed *= 2;
            if (boat_speed == 0)
                boat_speed = 3;
            break;
        case '-':
            if (cloud_speed >= 1)
                cloud_speed--;
            if (boat_speed >= 6)
                boat_speed /= 2;
        default:
            break;
    }
    glutPostRedisplay();
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
    glutKeyboardFunc(fun_keys);
    glutDisplayFunc(display);
    glutTimerFunc(100, cloud_movement, 0);
    glutTimerFunc(100, boat_movement, 0);

    glutMainLoop();
    return 0;
}
