#include <GL/glut.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "List.h"
#include "objfp.h"

#define DISPLAY_WIDTH 800
#define DISPLAY_HEIGHT 800

List* VList;
List* FList;

double ang_x = 0.0, ang_y = 0.0, ang_z = 0.0; 

void display(void){
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glPushMatrix();
	glRotatef(ang_x,1.0,0.0,0.0);
    glRotatef(ang_y,0.0,1.0,0.0);
    glRotatef(ang_z,0.0,0.0,1.0);
    glScalef(0.5,0.5,0.5);
	/* começa desenhar */
		glLineWidth((GLfloat) 10.0);
		glBegin(GL_QUADS);
			Node* fc_vtx = listGetittem(FList, 0);
			GLfloat color_arr[2];
			for(int i=1;i<FList->size/4;i++){
				color_arr[0] = 0.5*(i/(FList->size/16.0)), color_arr[1] = 0.25*(i/(FList->size/2.0));
				for(int j=0;j<4;j++){
					glColor3f(color_arr[0], color_arr[1], (GLfloat) j/2);
					glVertex3f((GLfloat) (*((float**)fc_vtx->points))[0], (GLfloat) (*((float**)fc_vtx->points))[1], (GLfloat) (*((float**)fc_vtx->points))[2]);
					fc_vtx = fc_vtx->prox;

				}
			}
		glEnd();
	/* termina */
	glPopMatrix();
	glutSwapBuffers();
}



void keyboard (unsigned char key, int x, int y){
	switch(key){
		case 'x':
			ang_x += 5.0;
			break;
		case 'X':
			ang_x -= 5.0;
			break;
		case 'y':
			ang_y += 5.0;
			break;
		case 'Y':
			ang_y -= 5.0;
			break;
		case 'z':
			ang_z += 5.0;
			break;
		case 'Z':
			ang_z -= 5.0;
			break;
		default: break;
	}
}

void reshape(int w, int h){
	if (w >= h)
		glViewport(0, 0, (GLsizei)h, (GLsizei)h);
	else
		glViewport(0, 0, (GLsizei)w, (GLsizei)w);
    
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluOrtho2D(0.0,1.0,0.0,1.0) ;
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Timer(int extra){
   glutPostRedisplay();
   glutTimerFunc(30,Timer,0);
}


int main(int argc, char** argv){
	listInit(&VList);
	listInit(&FList);
	FILE* OBJfp = (FILE*) malloc(sizeof(FILE));
	read_args(argv, argc, &OBJfp);
	parseOBJ(OBJfp, VList, FList);

	glutInit(&argc, argv);
	glutTimerFunc(0,Timer,0);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(DISPLAY_WIDTH,DISPLAY_HEIGHT);
	glutCreateWindow("head test");
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
	//for(int i=0;i<LIST_SIZE;i++){
	//	Node* nod = listGetittem(List, i);
	//	printf("vertex: %f %f %f\n", (*(nod->points))[0], (*(nod->points))[1], (*(nod->points))[2]);
	//}
}