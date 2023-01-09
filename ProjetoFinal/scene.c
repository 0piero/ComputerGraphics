//#include <windows.h>
#include <GL/glut.h>
#include "Scene.h"
#include <stdio.h>
double angx = -20.0, angy = -30.0, angz = 0.0, deltaAng = 5.0;
//double angx = 0.0, angy = 0.0, angz = 0.0, deltaAng = 5.0;
int x_janela = 600, y_janela = 600;

GLfloat LuzAmbiente[4] = {0.5, 0.5, 0.5, 1.0};
GLfloat LuzDifusa [4] = {0.7, 0.7, 0.7, 1.0};
GLfloat LuzEspecular [4] = {1.0, 1.0, 1.0, 1.0};
GLfloat PosicaoLuz0 [4] = {+x_max/2.0, y_max, 0.0, 1.0};
GLfloat PosicaoLuz1 [4] = {-x_max/2.0, y_max, 0.0, 1.0};
GLfloat objeto_ambiente[4] = {0.5,0.0,0.0,1.0};
GLfloat objeto_difusa[4] = {1.0,0.0,0.0,1.0};
GLfloat objeto_especular[4] = {0.0,0.0,0.0,1.0};
GLint especMaterial = 30;

void implement_Light(){
    glLightfv(GL_LIGHT0, GL_AMBIENT, LuzAmbiente);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, LuzDifusa );
    glLightfv(GL_LIGHT0, GL_SPECULAR, LuzEspecular );
    glLightfv(GL_LIGHT0, GL_POSITION, PosicaoLuz0 );
    glLightfv(GL_LIGHT1, GL_AMBIENT, LuzAmbiente);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, LuzDifusa );
    glLightfv(GL_LIGHT1, GL_SPECULAR, LuzEspecular );
    glLightfv(GL_LIGHT1, GL_POSITION, PosicaoLuz1 );
    glMaterialfv (GL_FRONT_AND_BACK, GL_AMBIENT, objeto_ambiente);
    glMaterialfv (GL_FRONT_AND_BACK, GL_DIFFUSE, objeto_difusa);
    glMaterialfv (GL_FRONT, GL_SPECULAR, objeto_especular);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_DEPTH_TEST);
    glMateriali(GL_FRONT,GL_SHININESS,especMaterial);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,LuzAmbiente);

    glPushMatrix();
    glTranslatef(0.0,y_max,0.0);
    glColor3f(0.0,1.0,0.0);
    //glutSolidCube(0.1);
    glPopMatrix();
}

double eye_x = 0.0, eye_y = 0.0, eye_z = 0.0;
double center_x = 0.0, center_y = 0.0, center_z = z_max;
double up_x = 0.0, up_y = 1.0, up_z = 0.0;
double win = 1.0;
void draw(){
    glClearColor(1,1,1,1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glColor3f(0.0, 0.0 ,0.0);
    implement_Light();

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluLookAt(eye_x, eye_y, eye_z, center_x, center_y, center_z,up_x, up_y, up_z);
    glOrtho(-win,win,-win,win,-win,win);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
        glScalef(1.2,1.2,1.2);
        glRotatef(angx,1,0,0);
        glRotatef(angy,0,1,0);
        glRotatef(angz,0,0,1);
        draw_Scene(angx, angy, angz);
    glPopMatrix();
    printf("ang x = %f, angy = %f e angz = %f\n", angx, angy, angz);
    glFlush();
}

void keyboard(unsigned char key, int x, int y){
    switch(key){
        case 27:
            exit(1);
        case 'x':
            if(angx > 0 ){
                angx -= deltaAng;
            }
            break;
        case 'X':
            if(angx < 360){
                angx += deltaAng;
            }
            break;
        case 'y':
            if(angy > 0){
                angy -= deltaAng;
            }
            break;
        case 'Y':
            if(angy < 360){
                angy += deltaAng;
            }
            break;
        case 'z':
            if(angz > 0){
                angz -= deltaAng;
            }
            break;
        case 'Z':
            if(angz < 360){
                angz += deltaAng;
            }
            break;
        case '+':
            win = win * 0.95;
            break;
        case '-':
            win = win * 1.05;
            break;
        default:
            break;
    }
    glutPostRedisplay();
}

void reshape(int w, int h){
    if (w >= h)
    glViewport(0, 0, (GLsizei)h, (GLsizei)h) ;
    else
    glViewport(0, 0, (GLsizei)w, (GLsizei)w) ;
    glMatrixMode(GL_PROJECTION) ;
    glLoadIdentity() ;
    glMatrixMode(GL_MODELVIEW) ;
    glLoadIdentity();
}

void menu_movements(int option){
    printf("%d\n",option);
    switch (option){
        case 0:
            angx += deltaAng;
            break;
        case 1:
            angy += deltaAng;
            break;
        case 2:
            angz += deltaAng;
            break;
        case 5:
            win = win * 0.95;
            break;
        case 6:
            win = win * 1.05;
            break;
        case 27:
            exit(1);
            break;
        default:
            break;
    }
    glutPostRedisplay();
}

int main(int argc, char *argv[] ){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE| GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(50,100);
    glutInitWindowSize(x_janela,y_janela);
    glutCreateWindow("Projeto Final - Computação Gráfica");

    init(0);
    CarregaTextura("wood.bmp",0);

    //init(1);
    //CarregaTextura("tunnelTexture.bmp",1);

    glutDisplayFunc(draw);

    int menu = glutCreateMenu(menu_movements);
    glutAddMenuEntry("Rotação em X",0);
    glutAddMenuEntry("Rotação em Y",1);
    glutAddMenuEntry("Rotação em Z",2);
    glutAddMenuEntry("Zoom in",5);
    glutAddMenuEntry("Zoom out",6);
    glutAddMenuEntry("Sair",27);
    glutAttachMenu(GLUT_RIGHT_BUTTON);


    glutKeyboardFunc(keyboard);
    glutReshapeFunc(reshape);
    glutMainLoop (); // Mostra tudo e espera
    return 0;
}
