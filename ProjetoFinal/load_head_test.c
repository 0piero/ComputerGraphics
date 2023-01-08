#include <GL/glut.h>
//#include <glu.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <errno.h>
#include "List.h"
#include "objfp.h"
#include "human.h"
#include "moves.h"
#include <unistd.h>

#define DISPLAY_WIDTH 800
#define DISPLAY_HEIGHT 800

float* mov_mode[9] = {ang_x, ang_y, ang_z, ang_x+1, ang_y+1, ang_z+1, ang_x+4, ang_y+4, ang_z+4};
int torax = 0;
/*
float ang_xV1D = 0.0, ang_yV1D = 0.0, ang_zV1D = 0.0;
float ang_xV2D = 0.0, ang_yV2D = 0.0, ang_zV2D = 0.0;
float ang_xV1E = 0.0, ang_yV1E = 0.0, ang_zV1E = 0.0;
float ang_xV2E = 0.0, ang_yV2E = 0.0, ang_zV2E = 0.0;
float ang_xV3D = 0.0, ang_yV3D = 0.0, ang_zV3D = 0.0;
float ang_xV3E = 0.0, ang_yV3E = 0.0, ang_zV3E = 0.0;

float ang_xP1D = 0.0, ang_yP1D = 0.0, ang_zP1D = 0.0;
float ang_xP2D = 0.0, ang_yP2D = 0.0, ang_zP2D = 0.0;
float ang_xP1E = 0.0, ang_yP1E = 0.0, ang_zP1E = 0.0;
float ang_xP2E = 0.0, ang_yP2E = 0.0, ang_zP2E = 0.0;
float ang_xP3D = 0.0, ang_yP3D = 0.0, ang_zP3D = 0.0;
float ang_xP3E = 0.0, ang_yP3E = 0.0, ang_zP3E = 0.0;

float ang_xC = 0.0, ang_yC = 0.0, ang_zC = 0.0;
*/
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

	glPushMatrix();
	//glRotatef(ang_x,1.0,0.0,0.0);
	//glRotatef(ang_y,0.0,1.0,0.0);
	//glRotatef(ang_z,0.0,0.0,1.0);
		glScalef(0.15,0.15,0.15);


	/* começa desenhar */
		glLineWidth((GLfloat) 10.0);
		if (torax==0){
			hndlVD();
			hndlVE();
		}
		else{hndlT();}
		hndlPD();
		hndlPE();
		//glBegin(GL_TRIANGLES);
		//	for(int part=0; part<human.num_parts;part++){
		//		List* fc_lst = (human.parts)[part];
		//		Node* fc_vtx = listGetittem(fc_lst, 0);
		//		for(int i=1;i<fc_lst->size/3;i++){
		//			for(int j=0;j<3;j++){
		//				glColor3f(0.5*sin(i), 0.33*j, 0.5*cos(i));
		//				glVertex3f((GLfloat) (*((float**)fc_vtx->points))[0], (GLfloat) (*((float**)fc_vtx->points))[1], (GLfloat) (*((float**)fc_vtx->points))[2]);
		//				fc_vtx = fc_vtx->prox;
		//			}
		//		}
		//	}
		//glEnd();
	/* termina */
	glPopMatrix();
	glutSwapBuffers();
}



void keyboard(unsigned char key, int x, int y){
	switch(key){
		// V1D
		case 'x':
			*(mov_mode[0]) += 5.0;
			break;
		case 'X':
			*(mov_mode[0]) -= 5.0;
			break;
		case 'y':
			*(mov_mode[1]) += 5.0;
			break;
		case 'Y':
			*(mov_mode[1]) -= 5.0;
			break;
		case 'z':
			*(mov_mode[2]) += 5.0;
			break;
		case 'Z':
			*(mov_mode[2]) -= 5.0;
			break;

		// V2D
		if(torax==0){
			case 'w':
				*(mov_mode[3]) += 5.0;		
				break;		
			case 'W':		
				*(mov_mode[3]) -= 5.0;		
				break;
	
			case 'a':
				*(mov_mode[4]) += 5.0;		
				break;		
			case 'A':		
				*(mov_mode[4]) -= 5.0;		
				break;
	
			case 's':
				*(mov_mode[5]) += 5.0;		
				break;		
			case 'S':		
				*(mov_mode[5]) -= 5.0;		
				break;
	
			// V3D
			case 'd':
				*(mov_mode[6]) += 5.0;		
				break;		
			case 'D':		
				*(mov_mode[6]) -= 5.0;		
				break;
	
			case 'e':
				*(mov_mode[7]) += 5.0;		
				break;		
			case 'E':		
				*(mov_mode[7]) -= 5.0;		
				break;
	
			case 'r':
				*(mov_mode[8]) += 5.0;		
				break;		
			case 'R':		
				*(mov_mode[8]) -= 5.0;		
				break;
		}
		case '0':
			torax = 0;
			mov_mode[0]=ang_x ; mov_mode[1]=ang_y ; mov_mode[2]=ang_z ;
			mov_mode[3]=ang_x+1 ; mov_mode[4]=ang_y+1 ; mov_mode[5]=ang_z+1 ;
			mov_mode[6]=ang_x+4 ; mov_mode[7]=ang_y+4 ; mov_mode[8]=ang_z+4 ; 
			break;
		case '1':
			torax = 0;
			mov_mode[0]=ang_x+2 ; mov_mode[1]=ang_y+2 ; mov_mode[2]=ang_z+2 ;
			mov_mode[3]=ang_x+3 ; mov_mode[4]=ang_y+3 ; mov_mode[5]=ang_z+3 ;		
			mov_mode[6]=ang_x+5 ; mov_mode[7]=ang_y+5 ; mov_mode[8]=ang_z+5 ;
			break;
		case '2':
			torax = 0;
			mov_mode[0]=ang_x+6 ; mov_mode[1]=ang_y+6 ; mov_mode[2]=ang_z+6 ;
			mov_mode[3]=ang_x+7 ; mov_mode[4]=ang_y+7 ; mov_mode[5]=ang_z+7 ;		
			mov_mode[6]=ang_x+10 ; mov_mode[7]=ang_y+10 ; mov_mode[8]=ang_z+10 ;
			break;
		case '3':
			torax=0;
			mov_mode[0]=ang_x+8; mov_mode[1]=ang_y+8; mov_mode[2]=ang_z+8;
			mov_mode[3]=ang_x+9 ; mov_mode[4]=ang_y+9 ; mov_mode[5]=ang_z+9 ;		
			mov_mode[6]=ang_x+11 ; mov_mode[7]=ang_y+11 ; mov_mode[8]=ang_z+11 ;			
			break;

		case '4':
			torax = 1;
			mov_mode[0]=ang_x+13; mov_mode[1]=ang_y+13; mov_mode[2]=ang_z+13;
			//mov_mode[3]=ang_x+9 ; mov_mode[4]=ang_y+9 ; mov_mode[5]=ang_z+9 ;		
			//mov_mode[6]=ang_x+11 ; mov_mode[7]=ang_y+11 ; mov_mode[8]=ang_z+11 ;					
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
	gluOrtho2D(50.0,50.0,50.0,50.0) ;
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Timer(int extra){
   glutPostRedisplay();
   glutTimerFunc(30,Timer,0);
}


int main(int argc, char** argv){
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
	setParts(&human);
	glutInit(&argc, argv);
	glutTimerFunc(0,Timer,0);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(DISPLAY_WIDTH,DISPLAY_HEIGHT);
	glutCreateWindow("Human");
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