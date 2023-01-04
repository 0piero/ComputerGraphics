#include <GL/glut.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <errno.h>
#include "List.h"
#include "objfp.h"
#include <unistd.h>

#define DISPLAY_WIDTH 800
#define DISPLAY_HEIGHT 800
List* FList;
List* ABE_flist;
List* ABD_flist;
List* BD_flist;
List* BE_flist;
List* H_flist;
List* MD_flist;
List* ME_flist;
List* OE_flist;
List* OD_flist;
List* JE_flist;
List* JD_flist;
List* PD_flist;
List* PE_flist;
List* QD_flist;
List* QE_flist;
List* T_flist;
List* CE_flist;
List* CD_flist;

double ang_x = 0.0, ang_y = 0.0, ang_z = 0.0;

void LightingStuff(GLfloat* LA_rgba, GLfloat* OA_rgba, GLfloat* LD_rgba, GLfloat* OD_rgba, GLfloat* LE_rgba, GLfloat* OE_rgba, int exp);
void display();
void keyboard (unsigned char key, int x, int y);
void reshape(int w, int h);
void Timer(int extra);

float max(float num1, float num2);

float max(float num1, float num2){
    return (num1 > num2 ) ? num1 : num2;
}

void LightingStuff(GLfloat* LA_rgba, GLfloat* OA_rgba, GLfloat* LD_rgba, GLfloat* OD_rgba, GLfloat* LE_rgba, GLfloat* OE_rgba, int exp){
	glLightfv(GL_LIGHT0, GL_AMBIENT, LA_rgba);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, LD_rgba);
	glLightfv(GL_LIGHT0, GL_SPECULAR, LE_rgba);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, LA_rgba);

	glMaterialfv (GL_FRONT_AND_BACK, GL_AMBIENT, OA_rgba);
	glMaterialfv (GL_FRONT_AND_BACK, GL_DIFFUSE, OD_rgba);
	glMaterialfv (GL_FRONT_AND_BACK, GL_SPECULAR, OE_rgba);
	glMaterialf (GL_FRONT_AND_BACK, GL_SHININESS, exp);

	glEnable (GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	GLfloat position[] = {0.0, 200.0, 100.0, 1.0};
	glLightfv(GL_LIGHT0, GL_POSITION, position);
}

void display(){
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);	
	
	GLfloat LA_rgba[] = {0.5,0.5,0.5,1.0};
	GLfloat OA_rgba[] = {0.5,0.0,0.0,1.0};
	GLfloat LD_rgba[] = {0.7,0.7,0.7,1.0};
	GLfloat OD_rgba[] = {1.0,0.0,0.0,1.0};
	GLfloat LE_rgba[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat OE_rgba[] = {0.5, 0.5, 0.5, 1.0};
	LightingStuff(LA_rgba, OA_rgba, LD_rgba, OD_rgba, LE_rgba, OE_rgba, 2);

	glEnable(GL_DEPTH_TEST);

	//GLfloat ambient_rgba[4] = {1.0, 0.0, 0.0, 1.0};
	//glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_rgba);
	//glEnable(GL_LIGHT0);

	//glEnable(GL_COLOR_MATERIAL);
	//glEnable(GL_LIGHTING);

	//GLfloat ambient_rgba2[4] = {0.0, 0.0, 1.0, 1.0};
	//glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient_rgba2);

	glPushMatrix();
	glRotatef(ang_x,1.0,0.0,0.0);
	glRotatef(ang_y,0.0,1.0,0.0);
	glRotatef(ang_z,0.0,0.0,1.0);
	glScalef(0.1,0.1,0.1);


	/* começa desenhar */
		glLineWidth((GLfloat) 10.0);
		glBegin(GL_TRIANGLES);
			Node* fc_vtx = listGetittem(FList, 0);
			GLfloat color_arr[2];
			for(int i=1;i<FList->size/3;i++){
				//color_arr[0] = (i*0.5/(FList->size/3.0)), color_arr[1] = 0.85*(i/(FList->size));
				for(int j=0;j<3;j++){
					glColor3f(0.5*sin(i), 0.33*j, 0.5*cos(i));
					glVertex3f((GLfloat) (*((float**)fc_vtx->points))[0], (GLfloat) (*((float**)fc_vtx->points))[1], (GLfloat) (*((float**)fc_vtx->points))[2]);
					fc_vtx = fc_vtx->prox;
					//fc_vtx ++;
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
	listInit(&FList);
	listInit(&ABE_flist);
	listInit(&ABD_flist);
	listInit(&BD_flist);
	listInit(&BE_flist);
	listInit(&H_flist);
	listInit(&MD_flist);
	listInit(&ME_flist);
	listInit(&OE_flist);
	listInit(&OD_flist);
	listInit(&JE_flist);
	listInit(&JD_flist);
	listInit(&PD_flist);
	listInit(&PE_flist);
	listInit(&QD_flist);
	listInit(&QE_flist);
	listInit(&T_flist);
	listInit(&CE_flist);
	listInit(&CD_flist);

	FILE* OBJfp = (FILE*) malloc(sizeof(FILE));
	read_args(argv, argc, &OBJfp);
	parseOBJ(OBJfp,
	ABE_flist,
	ABD_flist,
	BD_flist,
	BE_flist,
	H_flist,
	MD_flist,
	ME_flist,
	OE_flist,
	OD_flist,
	JE_flist,
	JD_flist,
	PD_flist,
	PE_flist,
	QD_flist,
	QE_flist,
	T_flist,
	CE_flist,
	CD_flist);

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