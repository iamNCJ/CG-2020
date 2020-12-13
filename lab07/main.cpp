#define GL_SILENCE_DEPRECATION

#ifdef __APPLE__
#include <glut/glut.h>
#elif WIN32
#include <GL/freeglut.h>
#endif

GLfloat ctrlPoints[4][4][3] = {
        { { -0.5, 0, -0.15 },
                { -0.325, 0.045, -0.15 },
                { -0.275, 0.5, -0.15 },
                { 0, 0.5, -0.15 } },
        { { -0.5, 0, -0.05 },
                { -0.325, 0.045, -0.05 },
                { -0.275, 0.5, -0.05 },
                { 0, 0.5, -0.05 } },
        { { -0.5, 0, 0.05 },
                { -0.325, 0.045, 0.05 },
                { -0.275, 0.5, 0.05 },
                { 0, 0.5, 0.05 } },
        { { -0.5, 0, 0.15 },
                { -0.325, 0.045, 0.15 },
                { -0.275, 0.5, 0.15 },
                { 0, 0.5, 0.15 } },
};

GLfloat ctrlPoints2[4][4][3] = {
        { { 0.5, 0, -0.15 },
          { 0.325, 0.045, -0.15 },
          { 0.275, 0.5, -0.15 },
          { 0, 0.5, -0.15 } },
        { { 0.5, 0, -0.05 },
          { 0.325, 0.045, -0.05 },
          { 0.275, 0.5, -0.05 },
          { 0, 0.5, -0.05 } },
        { { 0.5, 0, 0.05 },
          { 0.325, 0.045, 0.05 },
          { 0.275, 0.5, 0.05 },
          { 0, 0.5, 0.05 } },
        { { 0.5, 0, 0.15 },
          { 0.325, 0.045, 0.15 },
          { 0.275, 0.5, 0.15 },
          { 0, 0.5, 0.15 } },
};

GLfloat knots[8] = { 0.0, 0.0, 0.0, 0.0,
                     1.0, 1.0, 1.0, 1.0 };

GLUnurbsObj *Nurb;

int SCR_WIDTH = 800;
int SCR_HEIGHT = 600;

int lastMouseX, lastMouseY;
int time = 0;

float angle = 60.0;
float cameraX = 0.0f, cameraY = 0.0f, cameraZ = 2.0f;
float viewDirX = 0.0f, viewDirY = 0.0f, viewDirZ = -1.0f, lastViewDirX, lastViewDirY;

bool isShiftDown, isWDown, isSDown, isADown, isDDown, isSpaceDown;

void modeling() {
    glColor3f(0.0, 1.0, 0.0);
    glutWireSphere(0.1, 50, 50);
    // Bezier
//    glPushMatrix();
    glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 4, &ctrlPoints[0][0][0]);
    glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
    glEvalMesh2(GL_FILL, 0, 20, 0, 20);
    // NURB
    gluBeginSurface(Nurb);
    gluNurbsSurface(Nurb, 8, knots, 8, knots, 4 * 3, 3, &ctrlPoints2[0][0][0], 4, 4, GL_MAP2_VERTEX_3);
    gluEndSurface(Nurb);
//    glPopMatrix();
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

void init()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
//    glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 4, &ctrlPoints[0][0][0]);
    glEnable(GL_MAP2_VERTEX_3);
//    glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    //代码开关4：取消下面两行代码，查看曲面显示效果差异
    //打开自动法矢量开关
    glEnable(GL_AUTO_NORMAL);
    //允许正则化法矢量
    glEnable(GL_NORMALIZE);

    GLfloat ambient[] = { 0.4, 0.6, 0.2, 1.0 };
    GLfloat position[] = { 0.0, 1.0, 3.0, 1.0 };
    GLfloat mat_diffuse[] = { 0.2, 0.4, 0.8, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 80.0 };
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    Nurb = gluNewNurbsRenderer();
    gluNurbsProperty(Nurb, GLU_SAMPLING_TOLERANCE, 5.0);
    gluNurbsProperty(Nurb, GLU_DISPLAY_MODE, GLU_FILL);
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_MULTISAMPLE | GLUT_DEPTH);
    glutInitWindowSize(SCR_WIDTH, SCR_HEIGHT);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("My Dream Car");
    init();
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
