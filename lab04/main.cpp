#define GL_SILENCE_DEPRECATION

#include <cstdio>
#include <GL/freeglut.h>

int SCR_WIDTH = 800;
int SCR_HEIGHT = 600;

int mousex, mousey;
int time = 0;


float angle = 60.0;
float x = 0.0f, y = 0.0f, z = 2.0f;
float lx = 0.0f, ly = 0.0f, lz = -1.0f;
float lastlx, lastly, lastlz;

bool isShiftDown, isWDown, isSDown, isADown, isDDown, isSpaceDown;

void render() {
    float angle1 = 1 * time;
    float angle2 = 3 * time;
    float angle3 = 2 * time;
    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
    // Center Star
    glColor3f(0.0, 0.0, 1.0);
    glutWireSphere(0.2, 50, 50);

    glRotatef(angle1, 0, 1, 0);
    {
        glTranslated(0.6, 0, 0);
        {
            // Planet 1
            glColor3f(1.0, 1.0, 1.0);
            glutWireSphere(0.1, 50, 50);
            glRotatef(angle2, 0, 1, 0.5);
            {
                glTranslated(0.2, 0, 0);
                {
                    glColor3f(1.0, 0.0, 0.0);
                    // Satellite
                    glutWireSphere(0.05, 50, 50);
                }
                glTranslated(-0.2, 0, 0);
            }
            glRotatef(-angle2, 0, 1, 0.5);
        }
        glTranslated(-0.6, 0, 0);
    }
    glRotatef(-angle1, 0, 1, 0);
    glRotatef(angle3, 0, 0.5, 0.5);
    {
        glTranslated(0.4, 0, 0);
        {
            // Planet 2
            glColor3f(0.0, 1.0, 0.0);
            glutWireSphere(0.1, 50, 50);
        }
        glTranslated(-0.4, 0, 0);
    }
    glRotatef(-angle3, 0, 0.5, 0.5);

    glutPostRedisplay();
    if (isShiftDown) {
        y -= 0.01;
    }
    if (isSpaceDown) {
        y += 0.01;
    }
    if (isWDown) {
        x = x + lx * 0.01;
        //  y = y + ly * 0.01;
        z = z + lz * 0.01;
    }
    if (isSDown) {
        x = x - lx * 0.01;
        //  y = y - ly * 0.01;
        z = z - lz * 0.01;
    }
    if (isADown) {
        x = x + lz * 0.01;
        z = z - lx * 0.01;
    }
    if (isDDown) {
        x = x - lz * 0.01;
        z = z + lx * 0.01;
    }
    glLoadIdentity();
    gluLookAt(x, y, z, x + lx, y + ly, z + lz, 0.0f, 1.0f, 0.0f);
}

void timerFunc(int nTimerID) {
    ++time;
    glutPostRedisplay();
    glutTimerFunc(100, timerFunc, 0);
}


static void init() {
    glClearColor(0.f, 0.f, 0.f, 1.0f);
}

static void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    render();

    glutSwapBuffers();
}

static void reshape(int w, int h) {
    SCR_WIDTH = w;
    SCR_HEIGHT = h;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    gluPerspective(angle, 1.0f * w / h, 0.1, 1000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(x, y, z, x + lx, y + ly, z + lz, 0.0f, 1.0f, 0.0f);
}

static void drag(int _x, int _y) {
    lx = 0.001 * (_x - mousex) + lastlx;
    ly = -0.001 * (_y - mousey) + lastly;
}

static void click(int button, int state, int _x, int _y) {
    mousex = _x;
    mousey = _y;
    lastlx = lx;
    lastly = ly;
    glutPostRedisplay();
}

static void idle() {
    ++time;
}

static void wheel(int wheel, int dir, int _x, int _y) {
    glutPostRedisplay();
    angle += dir * 1.0;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(angle, 1.0f * SCR_WIDTH / SCR_HEIGHT, 0.1, 1000);
    glMatrixMode(GL_MODELVIEW);
}

static void keyboardDown(unsigned char key, int _x, int _y) {
    switch (key) {
        case 'w':
            isWDown = true;
            break;
        case 's':
            isSDown = true;
            break;
        case 'a':
            isADown = true;
            break;
        case 'd':
            isDDown = true;
            break;
        case ' ':
            isSpaceDown = true;
            break;
        default:
            break;
    }
}

static void keyboardUp(unsigned char key, int x, int y) {
    switch (key) {
        case 'w':
            isWDown = false;
            break;
        case 's':
            isSDown = false;
            break;
        case 'a':
            isADown = false;
            break;
        case 'd':
            isDDown = false;
            break;
        case ' ':
            isSpaceDown = false;
            break;
        default:
            break;
    }
}

static void specialDown(int key, int _x, int _y) {
    if (key == GLUT_KEY_SHIFT_L || key == GLUT_KEY_SHIFT_R) {
        isShiftDown = true;
    }
}

static void specialUp(int key, int x, int y) {
    if (key == GLUT_KEY_SHIFT_L || key == GLUT_KEY_SHIFT_R) {
        isShiftDown = false;
    }
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_MULTISAMPLE);
    glutInitWindowSize(SCR_WIDTH, SCR_HEIGHT);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("My Solar System");
    glEnable(GL_DEPTH_TEST);
    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMotionFunc(drag);
    glutMouseFunc(click);
    glutMouseWheelFunc(wheel);
    glutKeyboardFunc(keyboardDown);
    glutKeyboardUpFunc(keyboardUp);
    glutSpecialFunc(specialDown);
    glutSpecialUpFunc(specialUp);
    glutIdleFunc(idle);

    glutMainLoop();
    return 0;
}
