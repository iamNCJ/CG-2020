#define GL_SILENCE_DEPRECATION
#define STB_IMAGE_IMPLEMENTATION

#ifdef __APPLE__

#include <glut/glut.h>

#elif WIN32

#include <GL/glew.h>
#include <GL/freeglut.h>

#endif

#include <cstdio>
#include <cstdlib>
#include "stb_image.h"

int SCR_WIDTH = 800;
int SCR_HEIGHT = 600;

int lastMouseX, lastMouseY;
int localTime = 0;

float angle = 60.0;
float cameraX = 0.0f, cameraY = 0.0f, cameraZ = 2.0f;
float viewDirX = 0.0f, viewDirY = 0.0f, viewDirZ = -1.0f, lastViewDirX, lastViewDirY;

bool isShiftDown, isWDown, isSDown, isADown, isDDown, isSpaceDown;

GLuint textures[4];
GLUquadricObj *pGlUquadric;

static void DrawPlanet(double radius, GLuint texture) {
    gluQuadricTexture(pGlUquadric, GLU_TRUE);
    glPushAttrib(GL_ENABLE_BIT | GL_TEXTURE_BIT);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);

    gluSphere(pGlUquadric, radius, 50, 50);
    glBindTexture(GL_TEXTURE_2D, 0);

    glPopAttrib();
    gluQuadricTexture(pGlUquadric, GLU_FALSE);
}

static void DrawSkyBox() {
    GLfloat fExtent = 15.0f;

    glEnable(GL_TEXTURE_CUBE_MAP);

    glBegin(GL_QUADS);
    // Negative X
    glTexCoord3f(-1.0f, -1.0f, 1.0f);
    glVertex3f(-fExtent, -fExtent, fExtent);
    glTexCoord3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-fExtent, -fExtent, -fExtent);
    glTexCoord3f(-1.0f, 1.0f, -1.0f);
    glVertex3f(-fExtent, fExtent, -fExtent);
    glTexCoord3f(-1.0f, 1.0f, 1.0f);
    glVertex3f(-fExtent, fExtent, fExtent);

    //  Positive X
    glTexCoord3f(1.0f, -1.0f, -1.0f);
    glVertex3f(fExtent, -fExtent, -fExtent);
    glTexCoord3f(1.0f, -1.0f, 1.0f);
    glVertex3f(fExtent, -fExtent, fExtent);
    glTexCoord3f(1.0f, 1.0f, 1.0f);
    glVertex3f(fExtent, fExtent, fExtent);
    glTexCoord3f(1.0f, 1.0f, -1.0f);
    glVertex3f(fExtent, fExtent, -fExtent);

    // Negative Z
    glTexCoord3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-fExtent, -fExtent, -fExtent);
    glTexCoord3f(1.0f, -1.0f, -1.0f);
    glVertex3f(fExtent, -fExtent, -fExtent);
    glTexCoord3f(1.0f, 1.0f, -1.0f);
    glVertex3f(fExtent, fExtent, -fExtent);
    glTexCoord3f(-1.0f, 1.0f, -1.0f);
    glVertex3f(-fExtent, fExtent, -fExtent);

    // Positive Z
    glTexCoord3f(1.0f, -1.0f, 1.0f);
    glVertex3f(fExtent, -fExtent, fExtent);
    glTexCoord3f(-1.0f, -1.0f, 1.0f);
    glVertex3f(-fExtent, -fExtent, fExtent);
    glTexCoord3f(-1.0f, 1.0f, 1.0f);
    glVertex3f(-fExtent, fExtent, fExtent);
    glTexCoord3f(1.0f, 1.0f, 1.0f);
    glVertex3f(fExtent, fExtent, fExtent);

    // Positive Y
    glTexCoord3f(-1.0f, 1.0f, 1.0f);
    glVertex3f(-fExtent, fExtent, fExtent);
    glTexCoord3f(-1.0f, 1.0f, -1.0f);
    glVertex3f(-fExtent, fExtent, -fExtent);
    glTexCoord3f(1.0f, 1.0f, -1.0f);
    glVertex3f(fExtent, fExtent, -fExtent);
    glTexCoord3f(1.0f, 1.0f, 1.0f);
    glVertex3f(fExtent, fExtent, fExtent);

    // Negative Y
    glTexCoord3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-fExtent, -fExtent, -fExtent);
    glTexCoord3f(-1.0f, -1.0f, 1.0f);
    glVertex3f(-fExtent, -fExtent, fExtent);
    glTexCoord3f(1.0f, -1.0f, 1.0f);
    glVertex3f(fExtent, -fExtent, fExtent);
    glTexCoord3f(1.0f, -1.0f, -1.0f);
    glVertex3f(fExtent, -fExtent, -fExtent);
    glEnd();

    glDisable(GL_TEXTURE_CUBE_MAP);
}

static void modeling() {
//#ifdef __APPLE__
    DrawSkyBox();
//#endif
    float angle1 = 1 * localTime;
    float angle2 = 3 * localTime;
    float angle3 = 2 * localTime;
    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
    // Center Star
    // also as light source
    GLfloat LightPosition[] = {0.0f, 0.0f, 0.0f, 1.0f};
    GLfloat LightAmbient[] = {0.0f, 0.0f, 0.0f, 1.0f};
    GLfloat LightDiffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat LightSpecular[] = {1.0f, 1.0f, 1.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, LightPosition);
    glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, LightSpecular);
    // material
    GLfloat MatAmbient0[] = {0.0f, 0.0f, 0.0f, 1.0f};
    GLfloat MatDiffuse0[] = {0.0f, 0.0f, 0.0f, 1.0f};
    GLfloat MatSpecular0[] = {0.0f, 0.0f, 0.0f, 1.0f};
    GLfloat MatEmission0[] = {0.8f, 0.8f, 0.8f, 1.0f};
    GLfloat MatShininess0 = 0.0f;
    glMaterialfv(GL_FRONT, GL_AMBIENT, MatAmbient0);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, MatDiffuse0);
    glMaterialfv(GL_FRONT, GL_SPECULAR, MatSpecular0);
    glMaterialfv(GL_FRONT, GL_EMISSION, MatEmission0);
    glMaterialf(GL_FRONT, GL_SHININESS, MatShininess0);
    DrawPlanet(0.2, textures[0]);

    glPushMatrix();
    {
        glRotatef(angle1, 0, 1, 0);
        glTranslated(0.6, 0, 0);
        // Planet 1
        GLfloat MatAmbient1[] = {1.0f, 1.0f, 1.0f, 1.0f};
        GLfloat MatDiffuse1[] = {0.5f, 0.5f, 0.5f, 1.0f};
        GLfloat MatSpecular1[] = {1.0f, 1.0f, 1.0f, 1.0f};
        GLfloat MatEmission1[] = {0.0f, 0.0f, 0.0f, 1.0f};
        GLfloat MatShininess1 = 30.0f;
        glMaterialfv(GL_FRONT, GL_AMBIENT, MatAmbient1);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, MatDiffuse1);
        glMaterialfv(GL_FRONT, GL_SPECULAR, MatSpecular1);
        glMaterialfv(GL_FRONT, GL_EMISSION, MatEmission1);
        glMaterialf(GL_FRONT, GL_SHININESS, MatShininess1);
        DrawPlanet(0.1, textures[1]);
        glPushMatrix();
        {
            glRotatef(angle2, 0, 1, 0.5);
            glTranslated(0.2, 0, 0);
            // Satellite
            GLfloat MatAmbient2[] = {1.0f, 1.0f, 1.0f, 1.0f};
            GLfloat MatDiffuse2[] = {0.5f, 0.5f, 0.5f, 1.0f};
            GLfloat MatSpecular2[] = {1.0f, 1.0f, 1.0f, 1.0f};
            GLfloat MatEmission2[] = {0.0f, 0.0f, 0.0f, 1.0f};
            GLfloat MatShininess2 = 30.0f;
            glMaterialfv(GL_FRONT, GL_AMBIENT, MatAmbient2);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, MatDiffuse2);
            glMaterialfv(GL_FRONT, GL_SPECULAR, MatSpecular2);
            glMaterialfv(GL_FRONT, GL_EMISSION, MatEmission2);
            glMaterialf(GL_FRONT, GL_SHININESS, MatShininess2);
            DrawPlanet(0.05, textures[2]);
        }
        glPopMatrix();
    }
    glPopMatrix();
    glPushMatrix();
    {
        glRotatef(angle3, 0, 0.5, 0.5);
        glTranslated(0.4, 0, 0);
        // Planet 2
        GLfloat MatAmbient3[] = {1.0f, 1.0f, 1.0f, 1.0f};
        GLfloat MatDiffuse3[] = {0.5f, 0.5f, 0.5f, 1.0f};
        GLfloat MatSpecular3[] = {1.0f, 1.0f, 1.0f, 1.0f};
        GLfloat MatEmission3[] = {0.0f, 0.0f, 0.0f, 1.0f};
        GLfloat MatShininess3 = 30.0f;
        glMaterialfv(GL_FRONT, GL_AMBIENT, MatAmbient3);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, MatDiffuse3);
        glMaterialfv(GL_FRONT, GL_SPECULAR, MatSpecular3);
        glMaterialfv(GL_FRONT, GL_EMISSION, MatEmission3);
        glMaterialf(GL_FRONT, GL_SHININESS, MatShininess3);
        DrawPlanet(0.1, textures[3]);
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
    localTime = glutGet(GLUT_ELAPSED_TIME) / 10;
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

static GLuint loadTexture(char *file) {
    int width, height, nrChannels;
    GLuint ID;

    unsigned char *data = stbi_load(file, &width, &height, &nrChannels, 0);
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
#ifdef __APPLE__
    glGenerateMipmap(GL_TEXTURE_2D); // will cause DEP on Windows
#endif
    stbi_image_free(data);

    return ID;
}

static GLuint loadSkyBox(char *file) {
    int width, height, nrChannels;
    GLuint ID;

    unsigned char *data = stbi_load(file, &width, &height, &nrChannels, 0);
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, ID);
    for (int i = 0; i < 6; i++) {
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    stbi_image_free(data);

    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);
    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);
    glTexGeni(GL_R, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);

    return ID;
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

    pGlUquadric = gluNewQuadric();

    textures[0] = loadTexture((char *) "../assets/sun.jpg");
    textures[1] = loadTexture((char *) "../assets/earth.jpg");
    textures[2] = loadTexture((char *) "../assets/moon.jpg");
    textures[3] = loadTexture((char *) "../assets/venus.jpg");

    loadSkyBox((char *) "../assets/skybox.jpg");
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
