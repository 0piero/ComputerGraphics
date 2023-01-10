#include <GL/glut.h>
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

#define DISPLAY_WIDTH 800
#define DISPLAY_HEIGHT 800
#define PI 3.1415926535897932
float* mov_mode[9] = {ang_x, ang_y, ang_z, ang_x+1, ang_y+1, ang_z+1, ang_x+4, ang_y+4, ang_z+4};
int torax = 0;

void LightingStuff(GLfloat* LA_rgba, GLfloat* OA_rgba, GLfloat* LD_rgba, GLfloat* OD_rgba, GLfloat* LE_rgba, GLfloat* OE_rgba, int exp);
float light_x=50.0; float light_y=50.0;float light_z=50.0;
int light_mode = 0;
void display();
void keyboard (unsigned char key, int x, int y);
void reshape(int w, int h);
void Timer(int extra);
// -5.000086 -19.578445 -39.323221 -19.480146 -135.117079 -246.576779 27.000000 -338.000000 -2.000000
double eye_x = -5.000086, eye_y = -19.578445, eye_z =  -39.323221; 
double center_x = -19.480146, center_y = -135.117079, center_z = -246.576779; 
double up_x = 0.0, up_y = 1.0, up_z = 0.0;
float cam_rot_x =27.000000 ;float cam_rot_y=-338.000000; float cam_rot_z=-2.000000;
float cam_trans_x =0.0;float cam_trans_y =0.0;float cam_trans_z =0.0;
double win = 28.900000;

float ang_x_cena, ang_y_cena, ang_z_cena;
int mode_cam_params = 0;
int mode_rot_cena = 0;

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

	GLfloat position[] = {light_x, light_y, light_z, 1.0};
	glLightfv(GL_LIGHT0, GL_POSITION, position);
}



void display(){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-win,win,-win,win,-200,200);
	
	glClearColor(0.0, 0.0, 0.0, 0.0);
	
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	

	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eye_x, eye_y, eye_z, center_x , center_y, center_z,up_x, up_y, up_z);
	glTranslatef( 0 , 0 , cam_trans_z ) ;
	glTranslatef( cam_trans_x , cam_trans_y , 0 ) ;
	glRotatef( cam_rot_x , 1 , 0 , 0 ) ;
	glRotatef( cam_rot_y , 0 , 1 , 0 ) ;
	glRotatef( cam_rot_z , 0 , 0 , 1 ) ;
	


	GLfloat LA_rgba[] = {1.0,1.0,1.0,1.0};
	GLfloat OA_rgba[] = {0.25,0.25,0.25,1.0};
	GLfloat LD_rgba[] = {1.0,1.0,1.0,1.0};
	GLfloat OD_rgba[] = {0.15,0.15,0.15,1.0};
	GLfloat LE_rgba[] = {-0.1, -0.1, -0.1, 1.0};
	GLfloat OE_rgba[] = {-0.1, -0.1, -0.1, 1.0};
	LightingStuff(LA_rgba, OA_rgba, LD_rgba, OD_rgba, LE_rgba, OE_rgba,32);

	agxEx();
	glPushMatrix();
		glTranslatef(0.0,-1.0,-1.0);
		glScalef(50.0,60.0,60.0);
     	exDeltoid();
        //glRotatef(ang_x_cena,1,0,0);
        //glRotatef(ang_y_cena,0,1,0);
        //glRotatef(ang_z_cena,0,0,1);
        //draw_Scene(angx, angy, angz);
  
		draw_Scene(ang_x_cena, ang_y_cena, ang_z_cena);

	glPopMatrix();

	glPushMatrix();
		glTranslatef(0.0,15.0,0.0);
		glScalef(3.5,3.5,3.5);
		glLineWidth((GLfloat) 1.0);
		Walking();
		hndlGlobal();

	glPopMatrix();
 

	glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y){
	if(mode_cam_params==1){
		//printf("%f %f %f %f %f %f %f %f %f %f\n", eye_x, eye_y, eye_z, center_x, center_y, center_z, cam_rot_x, cam_rot_y, cam_rot_z, win);
		switch(key){
			case 'x':
				eye_x += 0.5;
				break;
			case 'X':
				eye_x -= 0.5;
				break;
			case 'y':
				eye_y += 0.5;
				break;
			case 'Y':
				eye_y -= 0.5;
				break;
			case 'z':
				eye_z += 0.5;
				break;
			case 'Z':
				eye_z -= 0.5;
				break;			
			case 'w':
				center_x += 0.5;		
				break;		
			case 'W':		
				center_x -= 0.5;		
				break;
	
			case 'a':
				center_y += 0.5;		
				break;		
			case 'A':		
				center_y -= 0.5;		
				break;
			case 'd':
				win += 0.1;		
				break;		
			case 'D':		
				win -= 0.1;		
				break;	
			case 's':
				center_z += 0.5;		
				break;		
			case 'S':		
				center_z -= 0.5;		
				break;


			case 'e':
				cam_rot_x += 1.0;		
				break;		
			case 'E':		
				cam_rot_x -= 1.0;		
				break;
	
			case 'r':
				cam_rot_y += 1.0;		
				break;		
			case 'R':		
				cam_rot_y -= 1.0;		
				break;
			case 't':
				cam_rot_z += 1.0;		
				break;		
			case 'T':		
				cam_rot_z -= 1.0;		
				break;	

			case 'g':
				cam_trans_x += 1.0;
				break;		
			case 'G':		
				cam_trans_x -= 1.0;
				break;
			case 'h':
				cam_trans_y += 1.0;
				break;		
			case 'H':		
				cam_trans_y -= 1.0;
				break;								
			case 'j':
				cam_trans_z += 1.0;
				break;		
			case 'J':		
				cam_trans_z -= 1.0;
				break;																								
		}
	}
	else if(light_mode==1){
		switch(key){
			case 'x':
				light_x += 0.5;
				break;
			case 'X':
				light_x -= 0.5;
				break;
			case 'y':
				light_y += 0.5;
				break;
			case 'Y':
				light_y -= 0.5;
				break;
			case 'z':
				light_z += 0.5;
				break;
			case 'Z':
				light_z -= 0.5;
				break;
		}			
	}
	else if(to_ex1==1){
		//printf("%f %f %f %f %f %f\n", halter1_shift[0], halter1_shift[1], halter1_shift[2],
		//	h_shift[0], h_shift[2], ang_y[14]);
		//printf("%f %f %f %f %f %f\n", ang_x[0], ang_y[0], ang_z[0], ang_x[2], ang_y[2], ang_z[2]);
		//0.000000 -0.050000 0.175000 1.400000 -4.299998 0.000000
		//0.000000 0.000000 75.000000 0.000000 0.000000 75.000000
		switch(key){
			case 'x':
				halter1_shift[0] += 0.025;
				halter2_shift[0] += 0.025;
				break;
			case 'X':
				halter1_shift[0] -= 0.025;
				halter2_shift[0] -= 0.025;
				break;
			case 'y':
				halter1_shift[1] += 0.025;
				halter2_shift[1] += 0.025;
				break;
			case 'Y':
				halter1_shift[1] -= 0.025;
				halter2_shift[1] -= 0.025;
				break;
			case 'z':
				halter1_shift[2] += 0.025;
				halter2_shift[2] += 0.025;
				break;
			case 'Z':
				halter1_shift[2] -= 0.025;
				halter2_shift[2] -= 0.025;
				break;
			case 'a':
				h_shift[0] += 0.1;
				break;
			case 'A':
				h_shift[0] -= 0.1;
				break;				
			case 'b':
				h_shift[2] += 0.1;
				break;
			case 'B':
				h_shift[2] -= 0.1;
				break;								
							
		}
	}
	else if(torax==0){
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

			case 'i':
				ang_agx[2] += 1.0;
				//printf("a\n");		
				break;		
			case 'I':		
				ang_agx[2] -= 1.0;
				//printf("a\n");		
				break;
	
			case 'o':
				k_perna += 0.1;		
				//printf("b\n");
				break;		
			case 'O':		
				k_perna -= 0.1;		
				break;			
				//printf("b\n");

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
			if (mode_cam_params==0){mode_cam_params = 1;}
			else {mode_cam_params = 0;}
			break;
		//case 'm':
		//	if (mode_rot_cena==0){mode_rot_cena = 1;}
		//	else {mode_rot_cena = 0;}			
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
			break;
		case '[':
			if (to_ex1==0){
				to_ex1 = 1;
				halter1_shift[0] = halter2_shift[0] = 0.000000;
				halter1_shift[1] = halter2_shift[1] = -0.050000;
				halter1_shift[2] = halter2_shift[2] = 0.175000; 
				h_shift[0] = 1.400000; h_shift[2] = -4.299998; ang_y[14] = 0.000000;
				ang_x[0] = 0.0; ang_y[0] = 0.0; ang_z[0] = -75.0;
				ang_x[2] = 0.0; ang_y[2] = 0.0; ang_z[2] = 75.0;
				halter2_angz = -1.0; halter1_angz = 1.0;
				ex1_rot_angs[1] = ang_z[0] + 50.0; ex1_rot_angs[0] = ang_z[2] - 50.0;
			}
			else {to_ex1 = 0;}
			break;
		case ']':
			if (to_agx==0){
				to_agx=1;
				agx_ang_fim = ang_agx[2] + 90.0;
			}
			else{to_agx==0;}
			break;

		case  'l':
			light_mode = 1;

		case 27:
           exit(0);
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
    glOrtho(-win,win,-win,win,-200,200);
	
	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
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
        case 5:
			if (to_ex1==0){
				to_ex1 = 1;
				halter1_shift[0] = halter2_shift[0] = 0.000000;
				halter1_shift[1] = halter2_shift[1] = -0.050000;
				halter1_shift[2] = halter2_shift[2] = 0.175000; 
				h_shift[0] = 1.400000; h_shift[2] = -4.299998; ang_y[14] = 0.000000;
				ang_x[0] = 0.0; ang_y[0] = 0.0; ang_z[0] = -75.0;
				ang_x[2] = 0.0; ang_y[2] = 0.0; ang_z[2] = 75.0;
				halter2_angz = -1.0; halter1_angz = 1.0;
				ex1_rot_angs[1] = ang_z[0] + 50.0; ex1_rot_angs[0] = ang_z[2] - 50.0;
			}
			else {to_ex1 = 0;}
			break;  

		case 6:
			if (to_agx==0){
				to_agx=1;
				agx_ang_fim = ang_agx[2] + 90.0;
			}
			else{to_agx==0;}

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
	init_texture(0);
	chargeTexture("wood.bmp",0);
	glutDisplayFunc(display);
	
	int menu;

	menu = glutCreateMenu(menu_movements);
    	glutAddMenuEntry("Movimentar braco direito",1);
    	glutAddMenuEntry("Movimentar braco esquerdo",0);
    	glutAddMenuEntry("Movimentar perna direita",3);
    	glutAddMenuEntry("Movimentar perna esquerda",2);
    	glutAddMenuEntry("Movimentar torax",4);
    	glutAddMenuEntry("Fortalecimento de Deltoide",5);
    	glutAddMenuEntry("Agachamento",6);
    	glutAttachMenu(GLUT_RIGHT_BUTTON);
	
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
	//for(int i=0;i<LIST_SIZE;i++){
	//	Node* nod = listGetittem(List, i);
	//	printf("vertex: %f %f %f\n", (*(nod->points))[0], (*(nod->points))[1], (*(nod->points))[2]);
	//}
}