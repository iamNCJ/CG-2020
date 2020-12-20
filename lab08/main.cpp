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
    glColor3f(0.0, 0.0, 1.0);
    GLfloat sun_mat_ambient[]   = {0.0f, 0.0f, 0.0f, 1.0f};  //定义材质的环境光颜色，为0
    GLfloat sun_mat_diffuse[]   = {0.0f, 0.0f, 0.0f, 1.0f};  //定义材质的漫反射光颜色，为0
    GLfloat sun_mat_specular[] = {0.0f, 0.0f, 0.0f, 1.0f};   //定义材质的镜面反射光颜色，为0
    GLfloat sun_mat_emission[] = {0.8f, 0.0f, 0.0f, 1.0f};   //定义材质的辐射广颜色，为偏红色
    GLfloat sun_mat_shininess   = 0.0f;
    glMaterialfv(GL_FRONT, GL_AMBIENT,    sun_mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,    sun_mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,   sun_mat_specular);
    glMaterialfv(GL_FRONT, GL_EMISSION,   sun_mat_emission);
    glMaterialf (GL_FRONT, GL_SHININESS, sun_mat_shininess);
    glutSolidSphere(0.2, 50, 50);

    glPushMatrix();
    {
        glRotatef(angle1, 0, 1, 0);
        glTranslated(0.6, 0, 0);
        // Planet 1
        glColor3f(1.0, 1.0, 1.0);
        GLfloat earth_mat_ambient[]   = {0.0f, 0.0f, 1.0f, 1.0f};  //定义材质的环境光颜色，骗蓝色
        GLfloat earth_mat_diffuse[]   = {0.0f, 0.0f, 0.5f, 1.0f};  //定义材质的漫反射光颜色，偏蓝色
        GLfloat earth_mat_specular[] = {1.0f, 0.0f, 0.0f, 1.0f};   //定义材质的镜面反射光颜色，红色
        GLfloat earth_mat_emission[] = {0.0f, 0.0f, 0.0f, 1.0f};   //定义材质的辐射光颜色，为0
        GLfloat earth_mat_shininess   = 30.0f;
        glMaterialfv(GL_FRONT, GL_AMBIENT,    earth_mat_ambient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE,    earth_mat_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR,   earth_mat_specular);
        glMaterialfv(GL_FRONT, GL_EMISSION,   earth_mat_emission);
        glMaterialf (GL_FRONT, GL_SHININESS, earth_mat_shininess);
        glutSolidSphere(0.1, 50, 50);
        glPushMatrix();
        {
            glRotatef(angle2, 0, 1, 0.5);
            glTranslated(0.2, 0, 0);
            glColor3f(1.0, 0.0, 0.0);
            // Satellite
            glutSolidSphere(0.05, 50, 50);
        }
        glPopMatrix();
    }
    glPopMatrix();
    {
        glPushMatrix();
        glRotatef(angle3, 0, 0.5, 0.5);
        glTranslated(0.4, 0, 0);
        // Planet 2
        glColor3f(0.0, 1.0, 0.0);
        glutSolidSphere(0.1, 50, 50);
    }
    glPopMatrix();
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

static void init()
{
//    glShadeModel ( GL_SMOOTH );
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.f, 0.f, 0.f, 1.0f);
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_AUTO_NORMAL);
    glEnable(GL_NORMALIZE);

    GLfloat mat_diffuse[] = {0.2, 0.4, 0.8, 1.0};
    GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat mat_shininess[] = {80.0};
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    GLfloat sun_light_position[] = {0.0f, 0.0f, 0.0f, 1.0f}; //光源的位置在世界坐标系圆心，齐次坐标形式
    GLfloat sun_light_ambient[]   = {0.0f, 0.0f, 0.0f, 1.0f}; //RGBA模式的环境光，为0
    GLfloat sun_light_diffuse[]   = {1.0f, 1.0f, 1.0f, 1.0f}; //RGBA模式的漫反射光，全白光
    GLfloat sun_light_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};  //RGBA模式下的镜面光 ，全白光
    glLightfv(GL_LIGHT0, GL_POSITION, sun_light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT,   sun_light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,   sun_light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, sun_light_specular);

//    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
//    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
//    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
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
