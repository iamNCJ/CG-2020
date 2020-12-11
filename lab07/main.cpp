#define GL_SILENCE_DEPRECATION

#ifdef __APPLE__
#include <glut/glut.h>
#elif WIN32
#include <GL/freeglut.h>
#endif

GLfloat ctrlPoints[4][4][3] = {
        {{-1.5, -1.5, 4.0}, {-0.5, -1.5, 2.0},
                {0.5, -1.5, -1.0}, {1.5, -1.5, 2.0}},
        {{-1.5, -0.5, 1.0}, {-0.5, -0.5, 3.0},
                {0.5, -0.5, 0.0}, {1.5, -0.5, -1.0}},
        {{-1.5, 0.5, 4.0}, {-0.5, 0.5, 0.0},
                {0.5, 0.5, 3.0}, {1.5, 0.5, 4.0}},
        {{-1.5, 1.5, -2.0}, {-0.5, 1.5, -2.0},
                {0.5, 1.5, 0.0}, {1.5, 1.5, -1.0}}
};

int SCR_WIDTH = 800;
int SCR_HEIGHT = 600;

int lastMouseX, lastMouseY;
int time = 0;

float angle = 60.0;
float cameraX = 0.0f, cameraY = 0.0f, cameraZ = 2.0f;
float viewDirX = 0.0f, viewDirY = 0.0f, viewDirZ = -1.0f, lastViewDirX, lastViewDirY;

bool isShiftDown, isWDown, isSDown, isADown, isDDown, isSpaceDown;

void modeling() {
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
}

static void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    modeling();
    glLoadIdentity();
    gluLookAt(cameraX, cameraY, cameraZ, cameraX + viewDirX, cameraY + viewDirY, cameraZ + viewDirZ, 0.0f, 1.0f, 0.0f);
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
    gluLookAt(cameraX, cameraY, cameraZ, cameraX + viewDirX, cameraY + viewDirY, cameraZ + viewDirZ, 0.0f, 1.0f, 0.0f);
}

static void drag(int _x, int _y) {
    viewDirX = 0.001 * (_x - lastMouseX) + lastViewDirX;
    viewDirY = -0.001 * (_y - lastMouseY) + lastViewDirY;
}

static void click(int button, int state, int _x, int _y) {
    lastMouseX = _x;
    lastMouseY = _y;
    lastViewDirX = viewDirX;
    lastViewDirY = viewDirY;
    glutPostRedisplay();
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

#ifdef WIN32
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
#endif

static void idle() {
    time = glutGet(GLUT_ELAPSED_TIME) / 10;
    glutPostRedisplay();
    if (isShiftDown) {
        cameraY -= 0.01;
    }
    if (isSpaceDown) {
        cameraY += 0.01;
    }
    if (isWDown) {
        cameraX += viewDirX * 0.01;
        cameraZ += viewDirZ * 0.01;
    }
    if (isSDown) {
        cameraX -= viewDirX * 0.01;
        cameraZ -= viewDirZ * 0.01;
    }
    if (isADown) {
        cameraX += viewDirZ * 0.01;
        cameraZ -= viewDirX * 0.01;
    }
    if (isDDown) {
        cameraX -= viewDirZ * 0.01;
        cameraZ += viewDirX * 0.01;
    }
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_MULTISAMPLE);
    glutInitWindowSize(SCR_WIDTH, SCR_HEIGHT);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("My Solar System");
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.f, 0.f, 0.f, 1.0f);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMotionFunc(drag);
    glutMouseFunc(click);
#ifdef WIN32
    glutMouseWheelFunc(wheel); // mouse wheel function is not supported in macOS
    glutSpecialFunc(specialDown); // Shift key detection is not working in macOS
    glutSpecialUpFunc(specialUp);
#endif
    glutKeyboardFunc(keyboardDown);
    glutKeyboardUpFunc(keyboardUp);
    glutIdleFunc(idle);
    glutMainLoop();
    return 0;
}
