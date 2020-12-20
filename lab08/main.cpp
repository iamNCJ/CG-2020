#define GL_SILENCE_DEPRECATION

#ifdef __APPLE__

#include <glut/glut.h>

#elif WIN32

#include <GL/freeglut.h>

#endif

#include <cstdio>
#include <cstdlib>

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
    GLfloat LightPosition[] = {0.0f, 0.0f, 0.0f, 1.0f};
    GLfloat LightAmbient[] = {0.0f, 0.0f, 0.0f, 1.0f};
    GLfloat LightDiffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat LightSpecular[] = {1.0f, 1.0f, 1.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, LightPosition);
    glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, LightSpecular);
    GLfloat MatAmbient0[] = {0.0f, 0.0f, 0.0f, 1.0f};
    GLfloat MatDiffuse0[] = {0.0f, 0.0f, 0.0f, 1.0f};
    GLfloat MatSpecular0[] = {0.0f, 0.0f, 0.0f, 1.0f};
    GLfloat MatEmission0[] = {0.8f, 0.0f, 0.0f, 1.0f};
    GLfloat MatShininess0 = 0.0f;
    glMaterialfv(GL_FRONT, GL_AMBIENT, MatAmbient0);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, MatDiffuse0);
    glMaterialfv(GL_FRONT, GL_SPECULAR, MatSpecular0);
    glMaterialfv(GL_FRONT, GL_EMISSION, MatEmission0);
    glMaterialf(GL_FRONT, GL_SHININESS, MatShininess0);
    glutSolidSphere(0.2, 50, 50);

    glPushMatrix();
    {
        glRotatef(angle1, 0, 1, 0);
        glTranslated(0.6, 0, 0);
        // Planet 1
        GLfloat MatAmbient1[] = {0.0f, 0.0f, 1.0f, 1.0f};
        GLfloat MatDiffuse1[] = {0.0f, 0.0f, 0.5f, 1.0f};
        GLfloat MatSpecular1[] = {1.0f, 0.0f, 0.0f, 1.0f};
        GLfloat MatEmission1[] = {0.0f, 0.0f, 0.0f, 1.0f};
        GLfloat MatShininess1 = 30.0f;
        glMaterialfv(GL_FRONT, GL_AMBIENT, MatAmbient1);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, MatDiffuse1);
        glMaterialfv(GL_FRONT, GL_SPECULAR, MatSpecular1);
        glMaterialfv(GL_FRONT, GL_EMISSION, MatEmission1);
        glMaterialf(GL_FRONT, GL_SHININESS, MatShininess1);
        glutSolidSphere(0.1, 50, 50);
        glPushMatrix();
        {
            glRotatef(angle2, 0, 1, 0.5);
            glTranslated(0.2, 0, 0);
            // Satellite
            GLfloat MatAmbient2[] = {0.0f, 1.0f, 0.0f, 1.0f};
            GLfloat MatDiffuse2[] = {0.0f, 0.5f, 0.0f, 1.0f};
            GLfloat MatSpecular2[] = {1.0f, 0.0f, 0.0f, 1.0f};
            GLfloat MatEmission2[] = {0.0f, 0.0f, 0.0f, 1.0f};
            GLfloat MatShininess2 = 30.0f;
            glMaterialfv(GL_FRONT, GL_AMBIENT, MatAmbient2);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, MatDiffuse2);
            glMaterialfv(GL_FRONT, GL_SPECULAR, MatSpecular2);
            glMaterialfv(GL_FRONT, GL_EMISSION, MatEmission2);
            glMaterialf(GL_FRONT, GL_SHININESS, MatShininess2);
            glutSolidSphere(0.05, 50, 50);
        }
        glPopMatrix();
    }
    glPopMatrix();
    glPushMatrix();
    {
        glRotatef(angle3, 0, 0.5, 0.5);
        glTranslated(0.4, 0, 0);
        // Planet 2
        GLfloat MatAmbient3[] = {1.0f, 1.0f, 0.0f, 1.0f};
        GLfloat MatDiffuse3[] = {0.5f, 0.5f, 0.0f, 1.0f};
        GLfloat MatSpecular3[] = {1.0f, 0.0f, 0.0f, 1.0f};
        GLfloat MatEmission3[] = {0.0f, 0.0f, 0.0f, 1.0f};
        GLfloat MatShininess3 = 30.0f;
        glMaterialfv(GL_FRONT, GL_AMBIENT, MatAmbient3);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, MatDiffuse3);
        glMaterialfv(GL_FRONT, GL_SPECULAR, MatSpecular3);
        glMaterialfv(GL_FRONT, GL_EMISSION, MatEmission3);
        glMaterialf(GL_FRONT, GL_SHININESS, MatShininess3);
        glutSolidSphere(0.1, 50, 50);
    }
    glPopMatrix();
}

static void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    gluPerspective(80.0f, 1.0f, 1.0f, 20.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(cameraX, cameraY, cameraZ, cameraX + viewDirX, cameraY + viewDirY, cameraZ + viewDirZ, 0.0f, 1.0f, 0.0f);
    modeling();

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

#ifdef WIN32

static void wheel(int wheel, int dir, int _x, int _y) {
    glutPostRedisplay();
    angle += dir * 1.0;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(angle, 1.0f * SCR_WIDTH / SCR_HEIGHT, 0.1, 1000);
    glMatrixMode(GL_MODELVIEW);
}

#endif

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
        case 27:
            exit(0);
        default:
            printf("%d\n", key);
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

static void init() {
    glClearColor(0.f, 0.f, 0.f, 1.0f);
    glDepthFunc(GL_LESS);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_AUTO_NORMAL);
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_MULTISAMPLE | GLUT_DEPTH);
    glutInitWindowSize(SCR_WIDTH, SCR_HEIGHT);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("My Solar System");

    init();

    // GLUT Bindings
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMotionFunc(drag);
    glutMouseFunc(click);
#ifdef WIN32
    glutMouseWheelFunc(wheel);
    glutSpecialFunc(specialDown);
    glutSpecialUpFunc(specialUp);
#endif
    glutKeyboardFunc(keyboardDown);
    glutKeyboardUpFunc(keyboardUp);
    glutIdleFunc(idle);
    glutMainLoop();
    return 0;
}
