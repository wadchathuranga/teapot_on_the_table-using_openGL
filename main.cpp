#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>


GLfloat T = 0;
GLfloat Cx=0,Cy=0,Cz=3;   // for camera view change


void Spin()
{
    T = T + 0.1;
    if(T>360)
        T = 0;
    glutPostRedisplay();
}


void display()
{
    GLfloat Pos[] = {0,1,0,1};
    GLfloat Col[] = {1,0,0,1};

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glLightfv(GL_LIGHT0,GL_POSITION,Pos);
    glLightfv(GL_LIGHT0,GL_DIFFUSE,Col);

    gluLookAt(Cx,Cy,Cz,0,0,0,0,1,0);

    glRotatef(T,0,1,0);

    // ---------------- table top face ---------
    glPushMatrix();
        glScalef(1,0.05,1);
        glutSolidCube(1);
    glPopMatrix();

    // ---------------- table leg ---------
    glPushMatrix();
        glTranslatef(-0.5, -0.5, -0.5);
        glScalef(0.05,1,0.05);
        glutSolidCube(1);
    glPopMatrix();

    // ---------------- table leg ---------
    glPushMatrix();
        glTranslatef(0.5, -0.5, -0.5);
        glScalef(0.05,1,0.05);
        glutSolidCube(1);
    glPopMatrix();

    // ---------------- table leg ---------
    glPushMatrix();
        glTranslatef(-0.5, -0.5, 0.5);
        glScalef(0.05,1,0.05);
        glutSolidCube(1);
    glPopMatrix();

    // ---------------- table leg ---------
    glPushMatrix();
        glTranslatef(0.5, -0.5, 0.5);
        glScalef(0.05,1,0.05);
        glutSolidCube(1);
    glPopMatrix();


    // ---------------- tea pot ---------
    glPushMatrix();
        glTranslatef(0, 0.18, 0);
        glutSolidTeapot(0.2);
    glPopMatrix();



    glutSwapBuffers();
}

// Keyboard handling
void Key(unsigned char ch, int x, int y)
{
    switch(ch)
    {
        case 'x' : Cx = Cx - 0.5; break;
        case 'X' : Cx = Cx + 0.5; break;

        case 'y' : Cy = Cy - 0.5; break;
        case 'Y' : Cy = Cy + 0.5; break;

        case 'z' : Cz = Cz - 0.5; break;
        case 'Z' : Cz = Cz + 0.5; break;
    }
    glutPostRedisplay();
}


void resize(int width, int height)
{
    const float wh = (float) width / (float) height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-wh, wh, -1.0, 1.0, 2.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


void myInit()
{
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1,1,-1,1,2,10);
    glMatrixMode(GL_MODELVIEW);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}



int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(1080,720);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("Tea Table");

    myInit();
    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(Key);
    glutIdleFunc(Spin);

    glutMainLoop();
    return 0;
}
