#include <cstdio>
#include <GL/freeglut.h>

int SCR_WIDTH = 800;
int SCR_HEIGHT = 600;

int mouseX, mouseY;

void render() {
    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
}

static void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    render();
    glutSwapBuffers();
}

static void reshape(int w, int h) {
    SCR_WIDTH = w;
    SCR_HEIGHT = h;
    printf("reshape\n");
}

static void drag(int x, int y) {
    printf("drag\n");
    printf("pos:(%d %d)\n", x, y);
    glutPostRedisplay();
}

static void click(int button, int state, int x, int y) {
    printf("click:%d\n", button);
    printf("pos:(%d %d)\n", x, y);
    glutPostRedisplay();
}

static void wheel(int wheel, int dir, int x, int y) {
    printf("wheel:%d\n", wheel);
    printf("pos:(%d %d)\n", x, y);
    glutPostRedisplay();
}

static void keyboardDown(unsigned char key, int x, int y) {
    printf("key down: %d\n", key);
    printf("pos:(%d %d)\n", x, y);
    glutPostRedisplay();
}

static void keyboardUp(unsigned char key, int x, int y) {
    printf("key up: %d\n", key);
    printf("pos:(%d %d)\n", x, y);
    glutPostRedisplay();
}

static void specialDown(int key, int x, int y) {
    printf("special down: %d\n", key);
    printf("pos:(%d %d)\n", x, y);
    glutPostRedisplay();
}

static void specialUp(int key, int x, int y) {
    printf("special up: %d\n", key);
    printf("pos:(%d %d)\n", x, y);
    glutPostRedisplay();
}

static void init(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_MULTISAMPLE);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("My Solar System");
    glClearColor(0.f, 0.f, 0.f, 1.0f);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMotionFunc(drag);
    glutMouseFunc(click);
    glutMouseWheelFunc(wheel);
    glutKeyboardFunc(keyboardDown);
    glutKeyboardUpFunc(keyboardUp);
    glutSpecialFunc(specialDown);
    glutSpecialUpFunc(specialUp);
}

int main(int argc, char *argv[]) {
    init(argc, argv);
    glutMainLoop();
    return 0;
}
