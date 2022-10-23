#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>

#define DISPLAY_WIDTH 800.f
#define DISPLAY_HEIGHT 800.f
#define SQRT7 2.645751311064591
#define SIZE 0.015
#define PI 3.14159265358979323846

int ITER;

int listSize=0;

typedef struct Node Node;
struct Node{
   Node* prox;
   float p[2];
};
Node* crtNode(float p[2]);
void listInsert(Node** hdy, Node* nod, int pos);
Node* listGetittem(Node* hdy, int pos);
int listLen(Node* hdy);
void map_rule(char s, int order, float size, float point[2], float* angle);
void gosper(int order, float size, int rule, float point[2], float* angle);
void Timer(int extra);
void display(void);

Node* List = NULL;
char lindenmayerA[15] = {'A','-','B','-','-','B','+','A','+','+','A','A','+','B','-'};
char lindenmayerB[15] = {'+','A','-','B','B','-','-','B','-','A','+','+','A','+','B'};

int listLen(Node* hdy){int len=0;while(hdy!=NULL){len++;hdy=hdy->prox;};return len;}

Node* crtNode(float p[2]){
   Node* hdy = (Node*) malloc(sizeof(Node));
   hdy->p[0] = p[0]; hdy->p[1] = p[1];
   return hdy;
}
void listInsert(Node** hdy, Node* nod, int pos){
   if (pos == 0){
      Node* aux = (*hdy);
      *hdy = nod;
      nod->prox = aux;
   }
   else{
      int i=0;
      Node* ptr;
      ptr = *hdy;
      while(i<pos-1){
         ptr = ptr->prox;
         i++;
      }
      Node* aux = (Node*) malloc(sizeof(Node));
      aux = ptr->prox;
      ptr->prox = nod;
      nod->prox = aux;
   }
}

Node* listGetittem(Node* hdy, int pos){
   int i=0;
   Node* ptr = hdy;
   while(i<pos){
      ptr = ptr->prox;
      i++;
   }
   return ptr;
}

void gosper(int order, float size, int rule, float point[2], float* angle){
	if (order == 0){
		float x, y; //new_point[2];
		x = size*((float)cos((double)(*angle))) + point[0];
		y = size*((float)sin((double)(*angle))) + point[1];
		point[0] = x; point[1] = y;

		listInsert(&List, crtNode(point), listSize);
		listSize++;
	}
	else if (rule==0){
		for(int i=0;i<15;i++){
			map_rule(lindenmayerA[i], order, size, point, angle);
		}
	}
	else{
		for(int i=0;i<15;i++){
			map_rule(lindenmayerB[i], order, size, point, angle);
		}
	}
}

void map_rule(char s, int order, float size, float point[2], float* angle){
	int rule;
	switch(s){
		case 'A':
			rule = 0;
			break;
		case 'B':
			rule = 1;
			break;
		case '+':
			*angle += PI/3.0;
			return;
		case '-':
			*angle -= PI/3.0;
			return;
	}
	gosper(order-1, size, rule, point, angle);
}
void display(void){
	glClearColor(1.0, 1.0, 1.0, 0);
	glClear(GL_COLOR_BUFFER_BIT);

	glLineWidth(1.5);
	glBegin(GL_LINE_STRIP);
		glColor3f(0.0, 0.0, 0.0);
		Node* ptr = listGetittem(List, 0);
		for(int i=0;i<listLen(List);i++){
			glVertex2f((GLfloat) ptr->p[0], (GLfloat) ptr->p[1]);
			ptr = ptr->prox;
		}
	glEnd();
	glFlush();
}

void Timer(int extra){
   glutPostRedisplay();
   glutTimerFunc(30,Timer,0);
}

int main(int argc, char** argv){
	printf("# Iterações (>=0, <6): ");
	scanf("%d", &ITER);
	float pt[2] = {0.0, 0.0};
	listInsert(&List, crtNode(pt),0); listSize++;
	float* ang = (float*) malloc(sizeof(float)); *ang = 0.0;
	gosper(ITER, SIZE, 0, pt, ang);

	glutInit(&argc, argv);
	glutTimerFunc(0,Timer,0);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(DISPLAY_WIDTH,DISPLAY_HEIGHT);
	glutCreateWindow("Gosper");
	glClearColor(1.0, 1.0, 1.0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	glutIdleFunc(display);
	glutMainLoop();
	return 0;
}