#include <GL/glut.h>
//#include <glu.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <errno.h>
#include "List.h"
#include "objfp.h"
#include "Scene.h"
#include "human.h"
#include "moves.h"
#include <unistd.h>
#include "texture.h"

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
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glColor3f(0.0, 0.0 ,0.0);
    implement_Light();

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluLookAt(eye_x, eye_y, eye_z, center_x, center_y, center_z,up_x, up_y, up_z);
    glOrtho(-win,win,-win,win,-win,win);

    glMatrixMode(GL_MODELVIEW);


	glPushMatrix();
		glTranslatef(0.0,-0.165,0.0);

        glRotatef(angx,1,0,0);
        glRotatef(angy,0,1,0);
        glRotatef(angz,0,0,1);
        //draw_Scene(angx, angy, angz);

		draw_Scene(angx,angy, angz);
	glPopMatrix();

	glPushMatrix();
		glScalef(0.05,0.05,0.05);
		glLineWidth((GLfloat) 1.0);
		Walking();
		hndlGlobal();

	glPopMatrix();
	glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y){
	//if(mode_cam_params==1){
		/*switch(key){
			case 'x':
				eye_x += 0.1;
				break;
			case 'X':
				eye_x -= 0.1;
				break;
			case 'y':
				eye_y += 0.1;
				break;
			case 'Y':
				eye_y -= 0.1;
				break;
			case 'z':
				eye_z += 0.1;
				break;
			case 'Z':
				eye_z -= 0.1;
				break;
			case 'w':
				center_x += 0.1;
				break;
			case 'W':
				center_x -= 0.1;
				break;

			case 'a':
				center_y += 0.1;
				break;
			case 'A':
				center_y -= 0.1;
				break;

			case 's':
				center_z += 0.1;
				break;
			case 'S':
				center_z -= 0.1;
				break;
		}*/
	//}
	//else if(mode_rot_cena){
		switch(key){
			case 27:
            exit(1);
        case 'q':
            if(angx > 0 ){
                angx -= deltaAng;
            }
            break;
        case 'Q':
            if(angx < 360){
                angx += deltaAng;
            }
            break;
        case 'w':
            if(angy > 0){
                angy -= deltaAng;
            }
            break;
        case 'W':
            if(angy < 360){
                angy += deltaAng;
            }
            break;
        case 'e':
            if(angz > 0){
                angz -= deltaAng;
            }
            break;
        case 'E':
            if(angz < 360){
                angz += deltaAng;
            }
            break;
		}
	//}
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
		case '/':
//			if (mode_cam_params==0){mode_cam_params = 1;}
	//		else {mode_cam_params = 0;}
		case 'm':
			//if (mode_rot_cena==0){mode_rot_cena = 1;}
			//else {mode_rot_cena = 0;}
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
				//printf("deg>%f cos>%f sin>%f\n", rad_deg, cos(rad_deg), sin(rad_deg));
				//printf("%f %f\n", PI/2.0, -PI/2.0);
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
		case '[':
			to_ex1 = 1;
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
	//gluOrtho2D(500.0,-500.0,500.0,-500.0);
    //glOrtho(-win,win,-win,win,-win,win);
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
	read_args(argv, 2, &OBJfp);
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
    init_texture(0);
    chargeTexture("wood.bmp",0);
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
