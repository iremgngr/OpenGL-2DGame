// OpenGLDemo_2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <windows.h>
#include <stdlib.h>
#include <iostream>
#include <GL/glut.h>

#include "Ship.h"
#include "Game.h"

Game game;

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    game.render(); 

    glutSwapBuffers();
}

// 60 FPS
void timer(int value) {
    game.onTimer();  

    glutTimerFunc(16, timer, 0);  // 60 FPS ~ 16 ms
}

// Klavye tuþlarý (özel tuþlar: ok tuþlarý)
void specialKeys(int key, int x, int y) {
    game.handleKeyPress(key);
}

// Klavye tuþlarý (normal tuþlar: boþluk vb.)
void keyboard(unsigned char key, int x, int y) {
    if (key == 27) {  // ESC çýkýþ
        exit(0);
    }
    game.handleKeyPress(key);
}

// Fare butonlarý
void mouse(int button, int state, int x, int y) {
    game.handleMouse(button, state);
}

// OpenGL ayarlarý
void initOpenGL() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT);  // 2D görünüm
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("2D Shooting Game");  // BU OLMADAN ÖNCE OpenGL fonksiyonu çaðýrma!
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


    initOpenGL();

    game.init();

    glutDisplayFunc(display);
    glutTimerFunc(0, timer, 0);
    glutSpecialFunc(specialKeys);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);

    glutMainLoop();

    return 0;
}










// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
