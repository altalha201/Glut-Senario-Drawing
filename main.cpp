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

GLfloat stand_boat_position_x = 0.0;
GLfloat stand_boat_position_y = 0.0;

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

void draw_line(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2)
{
    glBegin(GL_LINES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();
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

void draw_building(GLfloat start_x, GLfloat start_y,int floor_count, int body[3], int border[3])
{
    for (int i = 0; i < floor_count; i++)
    {
        glColor3ub(body[0], body[1], body[2]);
        glRectf(start_x, start_y + (i * 115), start_x + 300, start_y + 100 + (i * 115));
        glColor3ub(border[0], border[1], border[2]);
        glRectf(start_x - 30, start_y + 100 + (i * 115), start_x + 330, start_y + 115 + (i * 115));
        // window left
        glColor3ub(0, 0, 0);
        glRectf(start_x + 60, start_y + 60 + (i * 115), start_x + 90, start_y + 90 + (i * 115));
        // window right
        glRectf(start_x + 210, start_y + 60 + (i * 115), start_x + 240, start_y + 90 + (i * 115));
    }
    // door
    glColor3ub(102, 51, 0);
    glRectf(start_x + 130, start_y, start_x + 170, start_y + 70);
    glColor3ub(0, 0, 0);
    draw_line(start_x + 130, start_y, start_x + 130, start_y + 70);
    draw_line(start_x + 170, start_y, start_x + 170, start_y + 70);
    draw_line(start_x + 150, start_y, start_x + 150, start_y + 50);
    draw_line(start_x + 130, start_y  + 70, start_x + 170, start_y + 70);
    draw_line(start_x + 130, start_y  + 70, start_x + 150, start_y + 50);
    draw_line(start_x + 170, start_y  + 70, start_x + 150, start_y + 50);

    // roof top border
    for (int j = start_x - 30; j <= start_x + 330; j += 10)
    {
        draw_line(j, start_y + (floor_count * 115), j, start_y + 15 + (floor_count * 115));
    }

    draw_line(start_x - 30, start_y + 15 + (floor_count * 115), start_x + 330, start_y + 15 + (floor_count * 115));

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
    if (stand_boat_position_x == 0.0 && stand_boat_position_y == 0.0)
    {
        glBegin(GL_QUADS);
        glVertex2d(990, 392);
        glVertex2d(1140, 302);
        glVertex2d(1140, 298);
        glVertex2d(990, 388);
        glEnd();
    }
    glPushMatrix();
    glTranslatef(stand_boat_position_x, stand_boat_position_y, 0.0);
    draw_boat(1110, 300, base_1, shade_1, sail_1);
    glPopMatrix();
}

void light_source()
{
    if (isNight)
    {
        // moon
        glColor3ub(246, 241, 213);
        draw_solid_circle(120.0, 960.0, 90);
    }
    else
    {
        // sun
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

void buildings()
{
    // left building
    int body_1[3] = {102, 107, 113}, border_1[3] = {230, 238, 241};
    draw_building(90, 300, 3, body_1, border_1);

    // right building
    int body_2[3] = {255, 221, 84}, border_2[3] = {255, 128, 0};
    draw_building(470, 300, 4, body_2, border_2);
}

void road()
{
    glColor3ub(135, 135, 135);
    glBegin(GL_QUADS);
    glVertex2d(210, 300);
    glVertex2d(270, 300);
    glVertex2d(445, 150);
    glVertex2d(445, 90);
    glEnd();
    glBegin(GL_QUADS);
    glVertex2d(590, 300);
    glVertex2d(650, 300);
    glVertex2d(445, 90);
    glVertex2d(445, 150);
    glEnd();
    glRectd(415, 150, 475, 0);

    glColor3ub(239, 172, 31);
    glRectd(443, 90, 447, 0);

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
    road();
    buildings();


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
        case 'r':
            boat_position = 0.0;
            boat_speed = 1.0;
            cloud_position = 0.0;
            cloud_speed = 1.0;
            stand_boat_position_x = 0.0;
            stand_boat_position_y = 0.0;
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

void spe_fun_key(int key, int x, int y)
{
    switch(key)
    {
        case GLUT_KEY_LEFT:
            if (stand_boat_position_x > 0.0)
                stand_boat_position_x -= 3;
            break;
        case GLUT_KEY_RIGHT:
            if (stand_boat_position_x < 400.0)
                stand_boat_position_x +=3;
            break;
        case GLUT_KEY_UP:
            if (stand_boat_position_y < 400.0)
                stand_boat_position_y +=3;
            break;
        case GLUT_KEY_DOWN:
            if (stand_boat_position_y > -400.0)
                stand_boat_position_y -=3;
            break;
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
    glutInitWindowSize(960, 540);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Village Scenario");
    init();
    glutKeyboardFunc(fun_keys);
    glutSpecialFunc(spe_fun_key);
    glutDisplayFunc(display);
    glutTimerFunc(100, cloud_movement, 0);
    glutTimerFunc(100, boat_movement, 0);

    glutMainLoop();
    return 0;
}
