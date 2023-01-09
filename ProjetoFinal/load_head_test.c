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
#define PI 3.1415926535897932
float* mov_mode[9] = {ang_x, ang_y, ang_z, ang_x+1, ang_y+1, ang_z+1, ang_x+4, ang_y+4, ang_z+4};
int torax = 0;

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

	GLfloat position[] = {50.0, 50.0, 50.0, 1.0};
	glLightfv(GL_LIGHT0, GL_POSITION, position);
}



void display(){
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);	
	
	GLfloat LA_rgba[] = {1.0,1.0,1.0,1.0};
	GLfloat OA_rgba[] = {0.25,0.25,0.25,1.0};
	GLfloat LD_rgba[] = {1.0,1.0,1.0,1.0};
	GLfloat OD_rgba[] = {0.15,0.15,0.15,1.0};
	GLfloat LE_rgba[] = {-0.0, -0.0, -0.0, 1.0};
	GLfloat OE_rgba[] = {-0.0, -0.0, -0.0, 1.0};
	LightingStuff(LA_rgba, OA_rgba, LD_rgba, OD_rgba, LE_rgba, OE_rgba,32);

	glEnable(GL_DEPTH_TEST);
	glPushMatrix();
		glScalef(0.1,0.1,0.1);
		glLineWidth((GLfloat) 1.0);
		Walking();
		hndlGlobal();

	glPopMatrix();
	glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y){
	if(torax==0){
		switch(key){
			case 'x':
				*(mov_mode[0]) += delta_ang;
				break;
			case 'X':
				*(mov_mode[0]) -= delta_ang;
				break;
			case 'y':
				*(mov_mode[1]) += delta_ang;
				break;
			case 'Y':
				*(mov_mode[1]) -= delta_ang;
				break;
			case 'z':
				*(mov_mode[2]) += delta_ang;
				break;
			case 'Z':
				*(mov_mode[2]) -= delta_ang;
				break;			

			case 'w':
				*(mov_mode[3]) += delta_ang;		
				break;		
			case 'W':		
				*(mov_mode[3]) -= delta_ang;		
				break;
	
			case 'a':
				*(mov_mode[4]) += delta_ang;		
				break;		
			case 'A':		
				*(mov_mode[4]) -= delta_ang;		
				break;
	
			case 's':
				*(mov_mode[5]) += delta_ang;		
				break;		
			case 'S':		
				*(mov_mode[5]) -= delta_ang;		
				break;
	
			case 'd':
				*(mov_mode[6]) += delta_ang;		
				break;		
			case 'D':		
				*(mov_mode[6]) -= delta_ang;		
				break;
	
			case 'e':
				*(mov_mode[7]) += delta_ang;		
				break;		
			case 'E':		
				*(mov_mode[7]) -= delta_ang;		
				break;
	
			case 'r':
				*(mov_mode[8]) += delta_ang;		
				break;		
			case 'R':		
				*(mov_mode[8]) -= delta_ang;		
				break;

			default: break;
		}
	}
	else if(torax==1){
		switch(key){
						case 'c':
				ang_x[13] += delta_ang;
				break;
			case 'C':
				ang_x[13] -= delta_ang;
				break;
			case 'v':
				ang_y[13] += delta_ang;
				break;
			case 'V':
				ang_y[13] -= delta_ang;
				break;
			case 'b':
				ang_z[13] += delta_ang;
				break;
			case 'B':
				ang_z[13] -= delta_ang;
				break;

			default: break;
		}
	}
	switch(key){
		case '0':
			torax = 0;
			mov_mode[0]=ang_x ; mov_mode[1]=ang_y ; mov_mode[2]=ang_z ; // braco
			mov_mode[3]=ang_x+1 ; mov_mode[4]=ang_y+1 ; mov_mode[5]=ang_z+1 ; // ante braco
			mov_mode[6]=ang_x+4 ; mov_mode[7]=ang_y+4 ; mov_mode[8]=ang_z+4 ; // mao
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
			break;
		case '+':
			ang_y[14] = (ang_y[14] + delta_ang);
			if(ang_y[14]>360.0){ang_y[14] = ang_y[14] - 360.0;}
			break;
		case '-':
			ang_y[14] = ang_y[14] - delta_ang;
			if(ang_y[14]<-360.0){ang_y[14] = ang_y[14] + 360.0;}
			break;

		case '.':
			if(to_walk==0){
				printf("Walking key\n");
				float pi_180 = PI/180.0;
				float rad_deg = pi_180 * ang_y[14]; 		
				to_walk=1; choseLegs();
				float sign_x, sign_y;
				if ((0<rad_deg && rad_deg <= PI/2.0) || (-2.0*PI<rad_deg && rad_deg <= -(3.0/2.0)*(PI)))
					{sign_x = -1.0; sign_y = -1.0; }
				else if((PI/2.0<rad_deg && rad_deg<= PI) || (-(3.0/2.0)*(PI)<rad_deg && rad_deg <= -PI))
					{sign_x = -1.0; sign_y = 1.0; rad_deg = PI - rad_deg; }
				else if((PI<rad_deg && rad_deg<= (3.0/2.0)*(PI)) || (-PI<rad_deg && rad_deg<= -(PI/2.0)))
					{sign_x = 1.0; sign_y = 1.0; rad_deg = (3.0/2.0)*(PI) - rad_deg; }
				else if(((3.0/2.0)*(PI)<rad_deg && rad_deg<= 2.0*(PI)) || (-(PI/2.0)<rad_deg && rad_deg<= 0.0))
					{sign_x = 1.0; sign_y = -1.0; rad_deg = 2*PI - rad_deg;}

				h_shift[0] += 0.5*sin(rad_deg)*sign_x; h_shift[2] += 0.5*cos(rad_deg)*sign_y;
			}

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

void menu_movements(int option){
    switch(option){
        case 0:
            torax = 0;
			mov_mode[0]=ang_x ; mov_mode[1]=ang_y ; mov_mode[2]=ang_z ;
			mov_mode[3]=ang_x+1 ; mov_mode[4]=ang_y+1 ; mov_mode[5]=ang_z+1 ;
			mov_mode[6]=ang_x+4 ; mov_mode[7]=ang_y+4 ; mov_mode[8]=ang_z+4 ;
            break;
        case 1:
            torax = 0;
			mov_mode[0]=ang_x+2 ; mov_mode[1]=ang_y+2 ; mov_mode[2]=ang_z+2 ;
			mov_mode[3]=ang_x+3 ; mov_mode[4]=ang_y+3 ; mov_mode[5]=ang_z+3 ;
			mov_mode[6]=ang_x+5 ; mov_mode[7]=ang_y+5 ; mov_mode[8]=ang_z+5 ;
            break;
        case 2:
            torax = 0;
			mov_mode[0]=ang_x+6 ; mov_mode[1]=ang_y+6 ; mov_mode[2]=ang_z+6 ;
			mov_mode[3]=ang_x+7 ; mov_mode[4]=ang_y+7 ; mov_mode[5]=ang_z+7 ;
			mov_mode[6]=ang_x+10 ; mov_mode[7]=ang_y+10 ; mov_mode[8]=ang_z+10 ;
            break;
        case 3:
            torax=0;
			mov_mode[0]=ang_x+8; mov_mode[1]=ang_y+8; mov_mode[2]=ang_z+8;
			mov_mode[3]=ang_x+9 ; mov_mode[4]=ang_y+9 ; mov_mode[5]=ang_z+9 ;
			mov_mode[6]=ang_x+11 ; mov_mode[7]=ang_y+11 ; mov_mode[8]=ang_z+11 ;
            break;
        case 4:
            torax = 1;
            break;
        default:
            break;
    }
    glutPostRedisplay();
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
	//char* str[2] = {"aa", "head.obj"};
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
	
	int menu;

	menu = glutCreateMenu(menu_movements);
    	glutAddMenuEntry("Movimentar braço direito",1);
    	glutAddMenuEntry("Movimentar braço esquerdo",0);
    	glutAddMenuEntry("Movimentar perna direita",3);
    	glutAddMenuEntry("Movimentar perna esquerda",2);
    	glutAddMenuEntry("Movimentar torax",4);
    	glutAttachMenu(GLUT_RIGHT_BUTTON);
	
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
	//for(int i=0;i<LIST_SIZE;i++){
	//	Node* nod = listGetittem(List, i);
	//	printf("vertex: %f %f %f\n", (*(nod->points))[0], (*(nod->points))[1], (*(nod->points))[2]);
	//}
}