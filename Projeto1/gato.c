#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <GL/glut.h>
//#include <unistd.h>

#define DISPLAY_WIDTH 600.f
#define DISPLAY_HEIGHT 600.f
#define CIRCLE_LIM 0.001
#define PI 3.14159265358979323846
#define BIAS_INCREMENT 0.005
#define SCALE_FACTOR 0.1
#define CICLE_INCREMENT 0.05


typedef struct Node Node;
struct Node{
   Node* prox;
   float** points;
   int fig2d;
   float color[3];
   float thick;
};

Node* crtNode(float** points, int figtype, float color[3], float thick);
Node* listInit();
void listInsert(Node** hdy, Node* nod, int pos);
Node* listGetittem(Node* hdy, int pos);
void listClear(Node** hdy);
int listLen(Node* hdy);
void listR(Node** hdy, int pos);
Node* listPop(Node** hdy);

float m_x = 0.0, m_y = 0.0;
int busy = 0; int state=2; float fixed_angle; float fixed_points[4];
float mass_center[2] = {0.4375/10.07, -0.146/10.07}; float ball_center[2]; float right_click[2];
float head_ref[2] = {0.4375/10.07-0.5, -0.146/10.07};
float alignment; float bias = BIAS_INCREMENT; float cicle = CICLE_INCREMENT; float sxy = SCALE_FACTOR;
float color_ar[3] = {0.3, 0.3, 1.0};
float thickness = 1.0;
float line_bounds[2][2] = {{0.0,0.0},{0.0,0.5}};
int toggle_esp = 0, toggle_kol = 0;
int trace_line = 0, trace_circ = 0, trace_ret = 0;
int click_counter=0;

Node* Liszt = NULL;
Node* Balls = NULL;

//void ponto();
//void line();
//void circ();
void drawCat();
void curve1();
void curve2();
void curve3();
void curve4();
void curve5();
void curve6();
void curve7();
void curve8();
void curve9();
void curve10();
void curve11();
void curve12();
void curve13();
void curve14();
void curve15();
void curve16();
void curve17();
void curve18();
void curve19();
void curve20();
void curve21();
void curve22();
void curve23();
void ball();
void curve24();
void curve25();
void curve26();
void curve27();
void curve28();
void curve29();
void curve30();
void curve31();
void curve32();
void curve33();
void curve34();
void curve35();
void curve36();
void curve37();
void cleanScr();

void Timer(int extra);
void rotCat(void);
void transCat(void);
void scaleCat(void);
void catAnim(void);
void setAngleAlignment(float angle);
void catchBall(void);
double getAlignment(void);

float** XYrotMtx(float theta);
float** transMtx(float* ref);
float** scaleMtx(float amount[2]);
float** windowMtx(float* u, float* x, float* v, float* y);
void multMtx(float** mtx1, float** mtx2, float** prod, int sizes[3]);
void scaleCurve(float** points, float amount[2], float pivot[2], float** prod);
void transCurve(float** points, float pivot[2], float** prod);
void rotCurve(float** points, float theta, float pivot[2], float** prod);
void redrawStrip(Node* obj, long long int intensity);
void redrawAll();

Node* crtNode(float** points, int figtype, float color[3], float thick){
   Node* hdy = (Node*) malloc(sizeof(Node));
   hdy->points = points;
   hdy->fig2d = figtype;
   (hdy->color)[0] = color[0]; (hdy->color)[1] = color[1]; (hdy->color)[2] = color[2];
   hdy->thick = thick ;
   return hdy;
}

Node* listInit(){
   Node* hdy = NULL;
   return hdy;
}

int listLen(Node* hdy){int len=0;while(hdy!=NULL){len++;hdy=hdy->prox;};return len;}

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

Node* listPop(Node** hdy){
   if(*hdy==NULL){
      return NULL;
   }
   Node* ptr;
   ptr = *hdy;
   while((ptr = ptr->prox) != NULL){
      hdy = &((*hdy)->prox);}; Node* nod = (Node*) malloc(sizeof(Node)); nod = *hdy; (*hdy) = NULL; \
   return nod;
}

void listR(Node** hdy, int pos){
   if(pos==0 && (*hdy)!=NULL){
      Node* ptr = (*hdy);
      *hdy = (*hdy)->prox;
      free(ptr);
   }
   else{
      Node* ptr = *hdy;
      int i=0;
      while(i<(pos-1)){
         ptr = ptr->prox;
         i++;
      }
      Node* prox = ptr->prox->prox;
      free(ptr->prox);
      ptr->prox = prox;
   }
}

void listClear(Node** hdy){
   if(*hdy != NULL){
      Node* ptr, *ptr2;
      ptr = ptr2 = (*hdy)->prox;
      *hdy = NULL;
      while((ptr = ptr2) != NULL){
         ptr2 = ptr2->prox;
         free(ptr);
      }
   }
}

void MouseInt (int botao, int estado, int x, int y) {
   switch(botao){
      case GLUT_LEFT_BUTTON:
         if(estado == GLUT_DOWN){}
         break;
      case GLUT_RIGHT_BUTTON:
         if(estado==GLUT_DOWN){
            m_x = (float) (x/((float) glutGet(GLUT_WINDOW_WIDTH)))*2 - 1;
            m_y = (float) -((y/((float) glutGet(GLUT_WINDOW_HEIGHT)))*2 - 1);
            right_click[0] = m_x; right_click[1] = m_y;
            ball();
            //glutIdleFunc(catchBall);
         }
         break;
      default: break; 
   }
}

void catchBall(void){
   //glClearColor(0.0, 0.0, 0.0, 0.0);
   //glClear(GL_COLOR_BUFFER_BIT);
   //redrawAll();
   int i;
   //usleep(50000);
   if((i = listLen(Balls))!=0){
      Node* obj = listGetittem(Balls, i-1);
      ball_center[0] = (obj->points)[0][0]; ball_center[1] = (obj->points)[0][1];
      if((fabs((double)(mass_center[0] - ball_center[0])) <= 0.000001+BIAS_INCREMENT) && (fabs((double)(mass_center[1] - ball_center[1])) <= 0.000001+BIAS_INCREMENT)){
         bias = BIAS_INCREMENT; cicle = CICLE_INCREMENT;
         int j;
         for((j=listLen(Liszt)); j>0; j--){
            int fig = (listGetittem(Liszt, j-1))->fig2d; 
            if (fig==666){
               listR(&Liszt, j-1); 
               break;
            }
         } 
         busy = 0; state = 2;
         Node* nod =  listPop(&Balls);
         free(nod->points); free(nod);
         int ball_pos;
         if(((ball_pos = listLen(Balls)-1)>=0) && ((nod = listGetittem(Balls, ball_pos))!=NULL)){
            ball_center[0] = (nod->points)[0][0]; ball_center[1] = (nod->points)[0][1];
         }
      }

      if((fabs((double)getAlignment())<=0.0001 + CICLE_INCREMENT)&&busy==0){state=2;busy=1;}
      else if(busy==1 && state==0 && ((fabs((double)getAlignment())>0.0001))){state=2;}
      if(state==2){
         state=!busy;
         fixed_angle = (float) getAlignment();
         setAngleAlignment((float)fixed_angle);
         if ((fixed_angle<0.0 && cicle>0) || (fixed_angle>0.0 && cicle<0)){cicle = cicle*(-1.0);}
         fixed_points[0] = head_ref[0]; fixed_points[1] = head_ref[1]; fixed_points[2] = mass_center[0]; fixed_points[3] = mass_center[1];
      }
      //double ang = getAlignment();
      if(busy ==1){
         catAnim();
         bias+=BIAS_INCREMENT;
      }
      else if (busy == 0){
         //setAngleAlignment((float)ang);
         catAnim();
         //cicle+=CICLE_INCREMENT;
      }
   }
   glutDisplayFunc(redrawAll);
   glutPostRedisplay();
}
void drawCat(){curve1();curve2();curve3();curve4();curve5();curve6();curve7();curve8();curve9();curve10();curve11();curve12();curve13();curve14();curve15();curve16();curve17();curve18();curve19();curve20();curve21();curve22();curve23();curve24();curve25();curve26();curve27();curve28();curve29();curve31();curve32();curve33();curve34();curve35();curve36();curve37();}

void Keyboard (unsigned char key, int x, int y) {
   switch(key) {
      case '+':

         if(sxy<0){sxy = sxy*-1.0;}
         scaleCat();
         break;
      case '-':
         if(sxy>0){sxy = sxy*-1.0;}
         scaleCat();
         break;
      default: break; 
   }
}

void cleanScr(){
   glClearColor(0.0, 0.0, 0.0, 0.0);
   glClear(GL_COLOR_BUFFER_BIT);
   glutSwapBuffers();
}
/*
void ponto(){
   float color[3] = {color_ar[0], color_ar[1], color_ar[2]};
   float** points = (float**) malloc(3*sizeof(float*)); points[0] = (float*) malloc(2*sizeof(float)); points[1] = (float*) malloc(2*sizeof(float));
   points[0][0] = mass_center[0]; points[0][1] = mass_center[1];
   points[1][0] = head_ref[0]; points[1][1] = head_ref[1];
   points[2] = NULL;
   int figtype = 1000;
   listInsert(&Liszt, crtNode(points, figtype, color, thickness), 0);
}
*/

float** windowMtx(float* u, float* x, float* v, float* y)/* T((u_min, u_max,),(v_min, v_max))->((x_min, x_max), (y_min, y_max))*/{
   float** mtx = (float**) malloc(sizeof(float*));
   for(int i=0;i<3;i++)
      mtx[i] = (float*) calloc(3, sizeof(float));
   mtx[0][0] = (x[1]-x[0])/(u[1]-u[0]); mtx[0][2] = (x[0]*u[1]-x[1]*u[0])/(u[1]-u[0]); mtx[1][1] = (y[1]-y[0])/(v[1]-v[0]); mtx[1][2] = (y[0]*v[1]-y[1]*v[0])/(v[1]-v[0]); \
   mtx[2][2] = 1.0;
   return mtx;  
}

float** XYrotMtx(float theta){
   float** mtx = (float**) malloc(sizeof(float*));
   for(int i=0;i<3;i++)
      mtx[i] = (float*) calloc(3, sizeof(float));
   mtx[0][0] = cos(theta); mtx[0][1] = -1.0*sin(theta); mtx[1][0] = sin(theta); mtx[1][1] = cos(theta); mtx[2][2] = 1.0;
   return mtx;  
}

float** transMtx(float* ref){
   float** mtx = (float**) malloc(sizeof(float*));
   for(int i=0;i<3;i++)
      mtx[i] = (float*) calloc(3, sizeof(float));
   mtx[0][0] = 1.0; mtx[1][1] = 1.0; mtx[0][2] = ref[0]; mtx[1][2] = ref[1]; mtx[2][2] = 1.0;
   return mtx;  
}

float** scaleMtx(float amount[2]){
   float** mtx = (float**) malloc(sizeof(float*));
   for(int i=0;i<3;i++)
      mtx[i] = (float*) calloc(3, sizeof(float));
   mtx[0][0] = amount[0]; mtx[1][1] = amount[1]; mtx[2][2] = 1.0;
   return mtx;  
}

void rotCurve(float** points, float theta, float pivot[2], float** prod){ 
   float** tr = transMtx(pivot); pivot[0] = pivot[0]*-1.0; pivot[1] = pivot[1]*-1.0;
   float** tri = transMtx(pivot); float** rt = XYrotMtx(theta);
   float** m1 = (float**) malloc(3*sizeof(float*)); for(int i=0; i<3;i++){m1[i] = (float*) malloc(sizeof(float));}
   float** m2 = (float**) malloc(3*sizeof(float*)); for(int i=0; i<3;i++){m2[i] = (float*) malloc(sizeof(float));}
   int sizes[3] = {3,3,1};
   multMtx(tri, points, m1, sizes); multMtx(rt, m1, m2, sizes); multMtx(tr, m2, prod, sizes);
   for(int i=0;i<3;i++){free(m1[i]); free(m2[i]); free(rt[i]); free(tr[i]); free(tri[i]);} free(m1); free(m2); free(rt); free(tr); free(tri);
}

void scaleCurve(float** points, float amount[2], float pivot[2], float** prod){
   float** tr = transMtx(pivot); pivot[0] = pivot[0]*-1.0; pivot[1] = pivot[1]*-1.0;
   float** tri = transMtx(pivot); float** rt = scaleMtx(amount);
   float** m1 = (float**) malloc(3*sizeof(float*)); for(int i=0; i<3;i++){m1[i] = (float*) malloc(sizeof(float));}
   float** m2 = (float**) malloc(3*sizeof(float*)); for(int i=0; i<3;i++){m2[i] = (float*) malloc(sizeof(float));}
   int sizes[3] = {3,3,1};
   multMtx(tri, points, m1, sizes); multMtx(rt, m1, m2, sizes); multMtx(tr, m2, prod, sizes);
   for(int i=0;i<3;i++){free(m1[i]); free(m2[i]); free(rt[i]); free(tr[i]); free(tri[i]);} free(m1); free(m2); free(rt); free(tr); free(tri);
}

void transCurve(float** points, float pivot[2], float** prod){
   float** tr = transMtx(pivot);
   int sizes[3] = {3,3,1};
   multMtx(tr, points, prod, sizes);
   for(int i=0;i<3;i++){free(tr[i]);} free(tr);
}

void multMtx(float** mtx1, float** mtx2, float** prod, int sizes[3])/* prod <- mtx1(ixj) X mtx2(j*k) \ sizes = {i, j, k}*/{
   float entry;
   int i, j, k;
   for(i=0; i<sizes[0]; i++){
      entry=0.0;
      for(k=0; k<sizes[2]; k++){
         for(j=0; j<sizes[1]; j++)
            entry += mtx1[i][j]*mtx2[j][k];
         prod[i][k]=entry;
      }
   }
}

double getAlignment(void){
   double cat_x = ((double)head_ref[0]-(double)mass_center[0]);
   double cat_y = ((double)head_ref[1]-(double)mass_center[1]);
   double ball_x = ((double)ball_center[0]-(double)mass_center[0]);
   double ball_y = ((double)ball_center[1]-(double)mass_center[1]);
   double sign =1.0;
   if(cat_x*ball_y - cat_y*ball_x < 0){
      sign = -1.0;
   }
   double denom = (sqrt(pow((double)(cat_x), (double)2.0)+pow((double)(cat_y), (double)2.0))*sqrt(pow((double)(ball_x), (double)2.0)+pow((double)(ball_y), (double)2.0)));
   double numer = (((double)(cat_x))*((double) ball_x))+(((double)(cat_y))*((double)ball_y));
   if(fabs((double)(numer-denom)) <= 0.0001){return 0.0;}
   double cos_vl = (double) ((numer)/(denom));
   return sign*acos(cos_vl);
}

void setAngleAlignment(float angle){
   alignment = angle;
}

void curve1(){
   //glClearColor(0.0, 0.0, 0.0, 0.0);
   //glClear(GL_COLOR_BUFFER_BIT);

   long long int intensity = (long long int) floor((double)((3.0700-1.9560)/CIRCLE_LIM));
   float** points = (float**) malloc((intensity+1)*sizeof(float*));
   float** vec = (float**) malloc(3*sizeof(float*)); for(int j=0; j<3; j++){vec[j] = (float*) malloc(sizeof(float));};
   float** ar = (float**) malloc(3*sizeof(float*)); for(int j=0; j<3; j++){ar[j] = (float*) malloc(sizeof(float));};
   float u[2] = {1.9560, 3.0700}; float xw[2] = {1.9560/10.0700, 3.0700/10.0700}; float v[2] = {2.4, 3.229472}; float yw[2] = {2.4/10.07, 3.229472/10.07};
   int sizes[3] = {3, 3, 1};
   for(int i=0;i<intensity;i++){
      points[i] = (float*) malloc(2*sizeof(float));
      float x = (float) 1.9560+(i+1)*CIRCLE_LIM;
      float y = (float) 2*(x-2.6)*(x-2.6)+2.4;
      ar[0][0] = x; ar[1][0] = y; ar[2][0] = 1.0;
      multMtx(windowMtx(u, xw, v, yw), ar, vec, sizes);
      points[i][0] = vec[0][0]; points[i][1] = vec[1][0];
   }
   points[intensity] = NULL;
   float color[3] = {color_ar[0], color_ar[1], color_ar[2]};
   //points[0][0] = line_bounds[0][0]; points[0][1] = line_bounds[0][1]; points[1][0] = line_bounds[1][0]; points[1][1] = line_bounds[1][1];
   int figtype = 1;
   listInsert(&Liszt, crtNode(points, figtype, color, thickness), 0);
   //glutSwapBuffers();
}

void curve2(){
   //glClearColor(0.0, 0.0, 0.0, 0.0);
   //glClear(GL_COLOR_BUFFER_BIT);

   long long int intensity = (long long int) floor((double)((1.6200-0.4550)/CIRCLE_LIM));
   float** points = (float**) malloc((intensity+1)*sizeof(float*));
   float** vec = (float**) malloc(3*sizeof(float*)); for(int j=0; j<3; j++){vec[j] = (float*) malloc(sizeof(float));};
   float** ar = (float**) malloc(3*sizeof(float*)); for(int j=0; j<3; j++){ar[j] = (float*) malloc(sizeof(float));};
   float u[2] = {0.4550, 1.6200}; float xw[2] = {0.4550/10.0700, 1.6200/10.0700}; float v[2] = {2.6, 3.3434525}; float yw[2] = {2.6/10.07, 3.3434525/10.07};
   int sizes[3] = {3, 3, 1};
   for(int i=0;i<intensity;i++){
      points[i] = (float*) malloc(2*sizeof(float));
      float x = (float) 0.4550+(i+1)*CIRCLE_LIM;
      float y = (float) 2.1*(x-1.05)*(x-1.05)+2.6;
      ar[0][0] = x; ar[1][0] = y; ar[2][0] = 1.0;
      multMtx(windowMtx(u, xw, v, yw), ar, vec, sizes);
      points[i][0] = vec[0][0]; points[i][1] = vec[1][0];
   }
   points[intensity] = NULL;
   float color[3] = {color_ar[0], color_ar[1], color_ar[2]};
   //points[0][0] = line_bounds[0][0]; points[0][1] = line_bounds[0][1]; points[1][0] = line_bounds[1][0]; points[1][1] = line_bounds[1][1];
   int figtype = 2;
   listInsert(&Liszt, crtNode(points, figtype, color, thickness), 0);
   //glutSwapBuffers();
}

void curve3(){
   long long int intensity = (long long int) floor((double)((5.89-4.965)/CIRCLE_LIM));
   float** points = (float**) malloc((intensity+1)*sizeof(float*));
   float** vec = (float**) malloc(3*sizeof(float*)); for(int j=0; j<3; j++){vec[j] = (float*) malloc(sizeof(float));};
   float** ar = (float**) malloc(3*sizeof(float*)); for(int j=0; j<3; j++){ar[j] = (float*) malloc(sizeof(float));};
   float u[2] = {4.965, 5.89}; float xw[2] = {4.965/10.0700, 5.89/10.0700}; float v[2] = {0.547131875, 1.23036}; float yw[2] = {0.547131875/10.07, 1.23036/10.07};
   int sizes[3] = {3, 3, 1};
   for(int i=0;i<intensity;i++){
      points[i] = (float*) malloc(2*sizeof(float));
      float x = (float) 4.965+(i+1)*CIRCLE_LIM;
      float y = (float) 0.4750*(x-4.65)*(x-4.65)+0.5;
      ar[0][0] = x; ar[1][0] = y; ar[2][0] = 1.0;
      multMtx(windowMtx(u, xw, v, yw), ar, vec, sizes);
      points[i][0] = vec[0][0]; points[i][1] = vec[1][0];
   }
   points[intensity] = NULL;
   float color[3] = {color_ar[0], color_ar[1], color_ar[2]};
   //points[0][0] = line_bounds[0][0]; points[0][1] = line_bounds[0][1]; points[1][0] = line_bounds[1][0]; points[1][1] = line_bounds[1][1];
   int figtype = 3;
   listInsert(&Liszt, crtNode(points, figtype, color, thickness), 0);
}

void curve4(){
   long long int intensity = (long long int) floor((double)((6.945-5.07)/CIRCLE_LIM));
   float** points = (float**) malloc((intensity+1)*sizeof(float*));
   float** vec = (float**) malloc(3*sizeof(float*)); for(int j=0; j<3; j++){vec[j] = (float*) malloc(sizeof(float));};
   float** ar = (float**) malloc(3*sizeof(float*)); for(int j=0; j<3; j++){ar[j] = (float*) malloc(sizeof(float));};
   float u[2] = {5.07, 6.945}; float xw[2] = {5.07/10.0700, 6.945/10.0700}; float v[2] = {-0.589875, 1.2}; float yw[2] = {-0.589875/10.07, 1.2/10.07};
   int sizes[3] = {3, 3, 1};
   for(int i=0;i<intensity;i++){
      points[i] = (float*) malloc(2*sizeof(float));
      float x = (float) 5.07+(i+1)*CIRCLE_LIM;
      float y = (float) 0.45*(x-4.92)*(x-4.92)-0.6;
      ar[0][0] = x; ar[1][0] = y; ar[2][0] = 1.0;
      multMtx(windowMtx(u, xw, v, yw), ar, vec, sizes);
      points[i][0] = vec[0][0]; points[i][1] = vec[1][0];
   }
   points[intensity] = NULL;
   float color[3] = {color_ar[0], color_ar[1], color_ar[2]};
   //points[0][0] = line_bounds[0][0]; points[0][1] = line_bounds[0][1]; points[1][0] = line_bounds[1][0]; points[1][1] = line_bounds[1][1];
   int figtype = 4;
   listInsert(&Liszt, crtNode(points, figtype, color, thickness), 0);
}
void curve5(){
   long long int intensity = (long long int) floor((double)((6.9253-5.879)/CIRCLE_LIM));
   float** points = (float**) malloc((intensity+1)*sizeof(float*));
   float** vec = (float**) malloc(3*sizeof(float*)); for(int j=0; j<3; j++){vec[j] = (float*) malloc(sizeof(float));};
   float** ar = (float**) malloc(3*sizeof(float*)); for(int j=0; j<3; j++){ar[j] = (float*) malloc(sizeof(float));};
   float u[2] = {5.879, 6.9253}; float xw[2] = {5.879/10.0700, 6.9253/10.0700}; float v[2] = {1.2, 6.509}; float yw[2] = {1.2/10.07, 6.509/10.07};
   int sizes[3] = {3, 3, 1};
   for(int i=0;i<intensity;i++){
      points[i] = (float*) malloc(2*sizeof(float));
      float x = (float) 5.879+(i+1)*CIRCLE_LIM;
      float y = (float) 0.01*(1.0*((double)sqrt(-18911.0*((double)x)*((double)x) + 241400.0*((double)x) - 764800.0) + 33.0*((double)x) - 100.0));
      ar[0][0] = x; ar[1][0] = y; ar[2][0] = 1.0;
      multMtx(windowMtx(u, xw, v, yw), ar, vec, sizes);
      points[i][0] = vec[0][0]; points[i][1] = vec[1][0];
   }
   points[intensity] = NULL;
   float color[3] = {color_ar[0], color_ar[1], color_ar[2]};
   //points[0][0] = line_bounds[0][0]; points[0][1] = line_bounds[0][1]; points[1][0] = line_bounds[1][0]; points[1][1] = line_bounds[1][1];
   int figtype = 5;
   listInsert(&Liszt, crtNode(points, figtype, color, thickness), 0);
}

void curve6(){
   long long int intensity = (long long int) floor((double)((5.07-3.4)/CIRCLE_LIM));
   float** points = (float**) malloc((intensity+1)*sizeof(float*));
   float** vec = (float**) malloc(3*sizeof(float*)); for(int j=0; j<3; j++){vec[j] = (float*) malloc(sizeof(float));};
   float** ar = (float**) malloc(3*sizeof(float*)); for(int j=0; j<3; j++){ar[j] = (float*) malloc(sizeof(float));};
   float u[2] = {3.4, 5.07}; float xw[2] = {3.4/10.0700, 5.07/10.0700}; float v[2] = {-3.85, -0.6025}; float yw[2] = {-3.850000/10.0700, -0.6025/10.0700};
   int sizes[3] = {3, 3, 1};
   for(int i=0;i<intensity;i++){
      points[i] = (float*) malloc(2*sizeof(float));
      float x = (float) 3.4+(i+1)*CIRCLE_LIM;
      float y = (float) -sqrt(26.0 - ((double)x)*x) - 0.05;
      ar[0][0] = x; ar[1][0] = y; ar[2][0] = 1.0;
      multMtx(windowMtx(u, xw, v, yw), ar, vec, sizes);
      points[i][0] = vec[0][0]; points[i][1] = vec[1][0];
   }
   points[intensity] = NULL;
   float color[3] = {color_ar[0], color_ar[1], color_ar[2]};
   //points[0][0] = line_bounds[0][0]; points[0][1] = line_bounds[0][1]; points[1][0] = line_bounds[1][0]; points[1][1] = line_bounds[1][1];
   int figtype = 6;
   listInsert(&Liszt, crtNode(points, figtype, color, thickness), 0);
}
void curve7(){
   long long int intensity = (long long int) floor((double)((-4.25+5.59)/CIRCLE_LIM));
   float** points = (float**) malloc((intensity+1)*sizeof(float*));
   float** vec = (float**) malloc(3*sizeof(float*)); for(int j=0; j<3; j++){vec[j] = (float*) malloc(sizeof(float));};
   float** ar = (float**) malloc(3*sizeof(float*)); for(int j=0; j<3; j++){ar[j] = (float*) malloc(sizeof(float));};
   float u[2] = {-5.59, -4.25}; float xw[2] = {-5.59/10.0700, -4.25/10.0700}; float v[2] = {-3.940093456, -1.8}; float yw[2] = {-3.940093456/10.07,-1.8/10.07};
   int sizes[3] = {3, 3, 1};
   for(int i=0;i<intensity;i++){
      points[i] = (float*) malloc(2*sizeof(float));
      float x = (float) -5.59+(i+1)*CIRCLE_LIM;
      float y = (float) -sqrt((double)4.58-(((double)x+3.61)*((double)x+3.61)))-1.8;
      ar[0][0] = x; ar[1][0] = y; ar[2][0] = 1.0;
      multMtx(windowMtx(u, xw, v, yw), ar, vec, sizes);
      points[i][0] = vec[0][0]; points[i][1] = vec[1][0];
   }
   points[intensity] = NULL;
   float color[3] = {color_ar[0], color_ar[1], color_ar[2]};
   //points[0][0] = line_bounds[0][0]; points[0][1] = line_bounds[0][1]; points[1][0] = line_bounds[1][0]; points[1][1] = line_bounds[1][1];
   int figtype = 7;
   listInsert(&Liszt, crtNode(points, figtype, color, thickness), 0);
}

void curve8(){
   long long int intensity = (long long int) floor((double)((-3.64411+4.25589)/CIRCLE_LIM));
   float** points = (float**) malloc((intensity+1)*sizeof(float*));
   float** vec = (float**) malloc(3*sizeof(float*)); for(int j=0; j<3; j++){vec[j] = (float*) malloc(sizeof(float));};
   float** ar = (float**) malloc(3*sizeof(float*)); for(int j=0; j<3; j++){ar[j] = (float*) malloc(sizeof(float));};
   float u[2] = {-4.25589, -3.64411}; float xw[2] = {-4.25589/10.0700, -3.64411/10.0700}; float v[2] = {-4.29161, -3.85}; float yw[2] = {-4.29161/10.0700, -3.85/10.0700};
   int sizes[3] = {3, 3, 1};
   for(int i=0;i<intensity;i++){
      points[i] = (float*) malloc(2*sizeof(float));
      float x = (float) -4.25589+(i+1)*CIRCLE_LIM;
      float y = (float) 0.025*(-148.0 - sqrt((double) 14.0)*sqrt(-6201.0 - 3160.0*((double)x) - 400.0*x*((double) x)));
      ar[0][0] = x; ar[1][0] = y; ar[2][0] = 1.0;
      multMtx(windowMtx(u, xw, v, yw), ar, vec, sizes);
      points[i][0] = vec[0][0]; points[i][1] = vec[1][0];
   }
   points[intensity] = NULL;
   float color[3] = {color_ar[0], color_ar[1], color_ar[2]};
   //points[0][0] = line_bounds[0][0]; points[0][1] = line_bounds[0][1]; points[1][0] = line_bounds[1][0]; points[1][1] = line_bounds[1][1];
   int figtype = 8;
   listInsert(&Liszt, crtNode(points, figtype, color, thickness), 0);
}

void curve9(){
   long long int intensity = (long long int) floor((double)((-2.2+3.64)/CIRCLE_LIM));
   float** points = (float**) malloc((intensity+1)*sizeof(float*));
   float** vec = (float**) malloc(3*sizeof(float*)); for(int j=0; j<3; j++){vec[j] = (float*) malloc(sizeof(float));};
   float** ar = (float**) malloc(3*sizeof(float*)); for(int j=0; j<3; j++){ar[j] = (float*) malloc(sizeof(float));};
   float u[2] = {-3.64, -2.2}; float xw[2] = {-3.64/10.0700, -2.2/10.0700}; float v[2] = {-3.85, -3.85+0.00001}; float yw[2] = {-3.85/10.0700, (-3.85+0.00001)/10.0700};
   int sizes[3] = {3, 3, 1};
   for(int i=0;i<intensity;i++){
      points[i] = (float*) malloc(2*sizeof(float));
      float x = (float) -3.64+(i+1)*CIRCLE_LIM;
      float y = (float) -3.85;
      ar[0][0] = x; ar[1][0] = y; ar[2][0] = 1.0;
      multMtx(windowMtx(u, xw, v, yw), ar, vec, sizes);
      points[i][0] = vec[0][0]; points[i][1] = vec[1][0];
   }
   points[intensity] = NULL;
   float color[3] = {color_ar[0], color_ar[1], color_ar[2]};
   //points[0][0] = line_bounds[0][0]; points[0][1] = line_bounds[0][1]; points[1][0] = line_bounds[1][0]; points[1][1] = line_bounds[1][1];
   int figtype = 9;
   listInsert(&Liszt, crtNode(points, figtype, color, thickness), 0);
}
void curve10(){
   long long int intensity = (long long int) floor((double)((-1.57211+2.18389)/CIRCLE_LIM));
   float** points = (float**) malloc((intensity+1)*sizeof(float*));
   float** vec = (float**) malloc(3*sizeof(float*)); for(int j=0; j<3; j++){vec[j] = (float*) malloc(sizeof(float));};
   float** ar = (float**) malloc(3*sizeof(float*)); for(int j=0; j<3; j++){ar[j] = (float*) malloc(sizeof(float));};
   float u[2] = {-2.18389, -1.57211}; float xw[2] = {-2.18389/10.0700, -1.57211/10.0700}; float v[2] = {-4.29161, 3.85}; float yw[2] = {-4.29161/10.0700, 3.85/10.0700};
   int sizes[3] = {3, 3, 1};
   for(int i=0;i<intensity;i++){
      points[i] = (float*) malloc(2*sizeof(float));
      float x = (float) -2.18389+(i+1)*CIRCLE_LIM;
      float y = (float) -3.7 - 0.002*sqrt(3.5)*sqrt(-856721.0 - 939000.0*((double)x) - 250000.0*((double)x)*x);
      ar[0][0] = x; ar[1][0] = y; ar[2][0] = 1.0;
      multMtx(windowMtx(u, xw, v, yw), ar, vec, sizes);
      points[i][0] = vec[0][0]; points[i][1] = vec[1][0];
   }
   points[intensity] = NULL;
   float color[3] = {color_ar[0], color_ar[1], color_ar[2]};
   //points[0][0] = line_bounds[0][0]; points[0][1] = line_bounds[0][1]; points[1][0] = line_bounds[1][0]; points[1][1] = line_bounds[1][1];
   int figtype = 10;
   listInsert(&Liszt, crtNode(points, figtype, color, thickness), 0);
}
void curve11(){
   long long int intensity = (long long int) floor((double)((0.85+1.56)/CIRCLE_LIM));
   float** points = (float**) malloc((intensity+1)*sizeof(float*));
   float** vec = (float**) malloc(3*sizeof(float*)); for(int j=0; j<3; j++){vec[j] = (float*) malloc(sizeof(float));};
   float** ar = (float**) malloc(3*sizeof(float*)); for(int j=0; j<3; j++){ar[j] = (float*) malloc(sizeof(float));};
   float u[2] = {-1.56, 0.85}; float xw[2] = {-1.56/10.0700, 0.85/10.0700}; float v[2] = {-3.85, -3.85+0.00001}; float yw[2] = {-3.85/10.0700, (-3.85+0.00001)/10.0700};
   int sizes[3] = {3, 3, 1};
   for(int i=0;i<intensity;i++){
      points[i] = (float*) malloc(2*sizeof(float));
      float x = (float) -1.56+(i+1)*CIRCLE_LIM;
      float y = (float) -3.85;
      ar[0][0] = x; ar[1][0] = y; ar[2][0] = 1.0;
      multMtx(windowMtx(u, xw, v, yw), ar, vec, sizes);
      points[i][0] = vec[0][0]; points[i][1] = vec[1][0];
   }
   points[intensity] = NULL;
   float color[3] = {color_ar[0], color_ar[1], color_ar[2]};
   //points[0][0] = line_bounds[0][0]; points[0][1] = line_bounds[0][1]; points[1][0] = line_bounds[1][0]; points[1][1] = line_bounds[1][1];
   int figtype = 11;
   listInsert(&Liszt, crtNode(points, figtype, color, thickness), 0);
}
void curve12(){
   long long int intensity = (long long int) floor((double)((1.4559-0.844106)/CIRCLE_LIM));
   float** points = (float**) malloc((intensity+1)*sizeof(float*));
   float** vec = (float**) malloc(3*sizeof(float*)); for(int j=0; j<3; j++){vec[j] = (float*) malloc(sizeof(float));};
   float** ar = (float**) malloc(3*sizeof(float*)); for(int j=0; j<3; j++){ar[j] = (float*) malloc(sizeof(float));};
   float u[2] = {0.844106, 1.4559}; float xw[2] = {0.844106/10.0700, 1.45589/10.0700}; float v[2] = {-4.29161, -3.85}; float yw[2] = {-4.29161/10.0700, -3.85/10.0700};
   int sizes[3] = {3, 3, 1};
   for(int i=0;i<intensity;i++){
      points[i] = (float*) malloc(2*sizeof(float));
      float x = (float) 0.844106+(i+1)*CIRCLE_LIM;
      float y = (float) 0.025*(-148.0 - sqrt(14.0)*sqrt(-489.0 + 920.0*((double) x) - 400.0*((double) x)*x));
      ar[0][0] = x; ar[1][0] = y; ar[2][0] = 1.0;
      multMtx(windowMtx(u, xw, v, yw), ar, vec, sizes);
      points[i][0] = vec[0][0]; points[i][1] = vec[1][0];
   }
   points[intensity] = NULL;
   float color[3] = {color_ar[0], color_ar[1], color_ar[2]};
   //points[0][0] = line_bounds[0][0]; points[0][1] = line_bounds[0][1]; points[1][0] = line_bounds[1][0]; points[1][1] = line_bounds[1][1];
   int figtype = 12;
   listInsert(&Liszt, crtNode(points, figtype, color, thickness), 0);
}
void curve13(){
   long long int intensity = (long long int) floor((double)((2.8-1.45)/CIRCLE_LIM));
   float** points = (float**) malloc((intensity+1)*sizeof(float*));
   float** vec = (float**) malloc(3*sizeof(float*)); for(int j=0; j<3; j++){vec[j] = (float*) malloc(sizeof(float));};
   float** ar = (float**) malloc(3*sizeof(float*)); for(int j=0; j<3; j++){ar[j] = (float*) malloc(sizeof(float));};
   float u[2] = {1.45, 2.8}; float xw[2] = {1.45/10.0700, 2.8/10.0700}; float v[2] = {-3.85, -3.85+0.00001}; float yw[2] = {-3.85/10.0700, (-3.85+0.00001)/10.0700};
   int sizes[3] = {3, 3, 1};
   for(int i=0;i<intensity;i++){
      points[i] = (float*) malloc(2*sizeof(float));
      float x = (float) 1.45+(i+1)*CIRCLE_LIM;
      float y = (float) -3.85;
      ar[0][0] = x; ar[1][0] = y; ar[2][0] = 1.0;
      multMtx(windowMtx(u, xw, v, yw), ar, vec, sizes);
      points[i][0] = vec[0][0]; points[i][1] = vec[1][0];
   }
   points[intensity] = NULL;
   float color[3] = {color_ar[0], color_ar[1], color_ar[2]};
   //points[0][0] = line_bounds[0][0]; points[0][1] = line_bounds[0][1]; points[1][0] = line_bounds[1][0]; points[1][1] = line_bounds[1][1];
   int figtype = 13;
   listInsert(&Liszt, crtNode(points, figtype, color, thickness), 0);
}
void curve14(){
   long long int intensity = (long long int) floor((double)((3.40589-2.79411)/CIRCLE_LIM));
   float** points = (float**) malloc((intensity+1)*sizeof(float*));
   float** vec = (float**) malloc(3*sizeof(float*)); for(int j=0; j<3; j++){vec[j] = (float*) malloc(sizeof(float));};
   float** ar = (float**) malloc(3*sizeof(float*)); for(int j=0; j<3; j++){ar[j] = (float*) malloc(sizeof(float));};
   float u[2] = {2.79411, 3.40589}; float xw[2] = {2.79411/10.0700, 3.40589/10.0700}; float v[2] = {-4.29161, -3.85}; float yw[2] = {-4.29161/10.0700, -3.85/10.0700};
   int sizes[3] = {3, 3, 1};
   for(int i=0;i<intensity;i++){
      points[i] = (float*) malloc(2*sizeof(float));
      float x = (float) 2.79411+(i+1)*CIRCLE_LIM;
      float y = (float) 0.05*(-sqrt(14.0)*sqrt(-100.0*((double)x)*x + 620.0*x - 951.0) - 74.0);
      ar[0][0] = x; ar[1][0] = y; ar[2][0] = 1.0;
      multMtx(windowMtx(u, xw, v, yw), ar, vec, sizes);
      points[i][0] = vec[0][0]; points[i][1] = vec[1][0];
   }
   points[intensity] = NULL;
   float color[3] = {color_ar[0], color_ar[1], color_ar[2]};
   //points[0][0] = line_bounds[0][0]; points[0][1] = line_bounds[0][1]; points[1][0] = line_bounds[1][0]; points[1][1] = line_bounds[1][1];
   int figtype = 14;
   listInsert(&Liszt, crtNode(points, figtype, color, thickness), 0);
}
void curve15(){
   long long int intensity = (long long int) floor((double)((4.97+0.75)/CIRCLE_LIM));
   float** points = (float**) malloc((intensity+1)*sizeof(float*));
   float** vec = (float**) malloc(3*sizeof(float*)); for(int j=0; j<3; j++){vec[j] = (float*) malloc(sizeof(float));};
   float** ar = (float**) malloc(3*sizeof(float*)); for(int j=0; j<3; j++){ar[j] = (float*) malloc(sizeof(float));};
   float u[2] = {-0.75, 4.97}; float xw[2] = {-0.75/10.0700, 4.97/10.0700}; float v[2] = {0.2, 0.2+sqrt(10.0)}; float yw[2] = {0.2/10.0700, (0.2+sqrt(10.0))/10.0700};
   int sizes[3] = {3, 3, 1};
   for(int i=0;i<intensity;i++){
      points[i] = (float*) malloc(2*sizeof(float));
      float x = (float) -0.75+(i+1)*CIRCLE_LIM;
      float y = (float) 0.08333332*sqrt(5.0)*sqrt(-16.0*((double)x)*x + 24.0*((double)x) + 279.0) + 0.2;
      ar[0][0] = x; ar[1][0] = y; ar[2][0] = 1.0;
      multMtx(windowMtx(u, xw, v, yw), ar, vec, sizes);
      points[i][0] = vec[0][0]; points[i][1] = vec[1][0];
   }
   points[intensity] = NULL;
   float color[3] = {color_ar[0], color_ar[1], color_ar[2]};
   //points[0][0] = line_bounds[0][0]; points[0][1] = line_bounds[0][1]; points[1][0] = line_bounds[1][0]; points[1][1] = line_bounds[1][1];
   int figtype = 15;
   listInsert(&Liszt, crtNode(points, figtype, color, thickness), 0);
}
void curve16(){
   long long int intensity = (long long int) floor((double)((-0.75+2.2)/CIRCLE_LIM));
   float** points = (float**) malloc((intensity+1)*sizeof(float*));
   float** vec = (float**) malloc(3*sizeof(float*)); for(int j=0; j<3; j++){vec[j] = (float*) malloc(sizeof(float));};
   float** ar = (float**) malloc(3*sizeof(float*)); for(int j=0; j<3; j++){ar[j] = (float*) malloc(sizeof(float));};
   float u[2] = {-2.2, -0.75}; float xw[2] = {-2.2/10.0700, -0.75/10.0700}; float v[2] = {3.1565, 4.0}; float yw[2] = {3.1565/10.0700, 4.0/10.0700};
   int sizes[3] = {3, 3, 1};
   for(int i=0;i<intensity;i++){
      points[i] = (float*) malloc(2*sizeof(float));
      float x = (float) -2.2+(i+1)*CIRCLE_LIM;
      float y = (float) -1.5*((double)x + 1.5)*(x + 1.5) + 4.0;
      ar[0][0] = x; ar[1][0] = y; ar[2][0] = 1.0;
      multMtx(windowMtx(u, xw, v, yw), ar, vec, sizes);
      points[i][0] = vec[0][0]; points[i][1] = vec[1][0];
   }
   points[intensity] = NULL;
   float color[3] = {color_ar[0], color_ar[1], color_ar[2]};
   //points[0][0] = line_bounds[0][0]; points[0][1] = line_bounds[0][1]; points[1][0] = line_bounds[1][0]; points[1][1] = line_bounds[1][1];
   int figtype = 16;
   listInsert(&Liszt, crtNode(points, figtype, color, thickness), 0);
}
void curve17(){
   long long int intensity = (long long int) floor((double)((-3.7+6.003)/CIRCLE_LIM));
   float** points = (float**) malloc((intensity+1)*sizeof(float*));
   float** vec = (float**) malloc(3*sizeof(float*)); for(int j=0; j<3; j++){vec[j] = (float*) malloc(sizeof(float));};
   float** ar = (float**) malloc(3*sizeof(float*)); for(int j=0; j<3; j++){ar[j] = (float*) malloc(sizeof(float));};
   float u[2] = {-6.003, -3.7}; float xw[2] = {-6.003/10.0700, -3.7/10.0700}; float v[2] = {0.1648, 4.0}; float yw[2] = {0.1648/10.0700, 4.0/10.0700};
   int sizes[3] = {3, 3, 1};
   for(int i=0;i<intensity;i++){
      points[i] = (float*) malloc(2*sizeof(float));
      float x = (float) -6.003+(i+1)*CIRCLE_LIM;
      float y = (float) -1.5*((double)x + 4.4)*((double)x + 4.4) + 4.0;
      ar[0][0] = x; ar[1][0] = y; ar[2][0] = 1.0;
      multMtx(windowMtx(u, xw, v, yw), ar, vec, sizes);
      points[i][0] = vec[0][0]; points[i][1] = vec[1][0];
   }
   points[intensity] = NULL;
   float color[3] = {color_ar[0], color_ar[1], color_ar[2]};
   //points[0][0] = line_bounds[0][0]; points[0][1] = line_bounds[0][1]; points[1][0] = line_bounds[1][0]; points[1][1] = line_bounds[1][1];
   int figtype = 17;
   listInsert(&Liszt, crtNode(points, figtype, color, thickness), 0);
}
void curve18(){
   long long int intensity = (long long int) floor((double)((+3.68-2.22)/CIRCLE_LIM));
   float** points = (float**) malloc((intensity+1)*sizeof(float*));
   float** vec = (float**) malloc(3*sizeof(float*)); for(int j=0; j<3; j++){vec[j] = (float*) malloc(sizeof(float));};
   float** ar = (float**) malloc(3*sizeof(float*)); for(int j=0; j<3; j++){ar[j] = (float*) malloc(sizeof(float));};
   float u[2] = {-3.68, -2.22}; float xw[2] = {-3.68/10.0700, -2.22/10.0700}; float v[2] = {3.22, 3.22+0.00001}; float yw[2] = {3.22/10.0700, (3.22+0.00001)/10.0700};
   int sizes[3] = {3, 3, 1};
   for(int i=0;i<intensity;i++){
      points[i] = (float*) malloc(2*sizeof(float));
      float x = (float) -3.68+(i+1)*CIRCLE_LIM;
      float y = (float) 3.22;
      ar[0][0] = x; ar[1][0] = y; ar[2][0] = 1.0;
      multMtx(windowMtx(u, xw, v, yw), ar, vec, sizes);
      points[i][0] = vec[0][0]; points[i][1] = vec[1][0];
   }
   points[intensity] = NULL;
   float color[3] = {color_ar[0], color_ar[1], color_ar[2]};
   //points[0][0] = line_bounds[0][0]; points[0][1] = line_bounds[0][1]; points[1][0] = line_bounds[1][0]; points[1][1] = line_bounds[1][1];
   int figtype = 18;
   listInsert(&Liszt, crtNode(points, figtype, color, thickness), 0);
} 
void curve19(){
   long long int intensity = (long long int) floor((double)((-5.61+6.06)/CIRCLE_LIM));
   float** points = (float**) malloc((intensity+1)*sizeof(float*));
   float** vec = (float**) malloc(3*sizeof(float*)); for(int j=0; j<3; j++){vec[j] = (float*) malloc(sizeof(float));};
   float** ar = (float**) malloc(3*sizeof(float*)); for(int j=0; j<3; j++){ar[j] = (float*) malloc(sizeof(float));};
   float u[2] = {-6.06, -5.61}; float xw[2] = {-6.06/10.0700, -5.61/10.0700}; float v[2] = {-2.6, -0.5575}; float yw[2] = {-2.6/10.0700, -0.5575/10.0700};
   int sizes[3] = {3, 3, 1};
   for(int i=0;i<intensity;i++){
      points[i] = (float*) malloc(2*sizeof(float));
      float x = (float) -6.06+(i+1)*CIRCLE_LIM; float k;
      //if (((-6.05<x) && (x<-6.00775)) || ((-6.00775<=x) && (x<-5.609))){k = -1.0;} else{k = 1.0;};
      float y = (float) -0.5 + -1.0*sqrt(60.5 + 10.0*((double)x));
      ar[0][0] = x; ar[1][0] = y; ar[2][0] = 1.0;
      multMtx(windowMtx(u, xw, v, yw), ar, vec, sizes);
      points[i][0] = vec[0][0]; points[i][1] = vec[1][0];
   }
   points[intensity] = NULL;
   float color[3] = {color_ar[0], color_ar[1], color_ar[2]};
   //points[0][0] = line_bounds[0][0]; points[0][1] = line_bounds[0][1]; points[1][0] = line_bounds[1][0]; points[1][1] = line_bounds[1][1];
   int figtype = 19;
   listInsert(&Liszt, crtNode(points, figtype, color, thickness), 0);
}
void curve20(){
   long long int intensity = (long long int) floor((double)((-6.009+6.05)/CIRCLE_LIM));
   float** points = (float**) malloc((intensity+1)*sizeof(float*));
   float** vec = (float**) malloc(3*sizeof(float*)); for(int j=0; j<3; j++){vec[j] = (float*) malloc(sizeof(float));};
   float** ar = (float**) malloc(3*sizeof(float*)); for(int j=0; j<3; j++){ar[j] = (float*) malloc(sizeof(float));};
   float u[2] = {-6.05-0.001, -6.009}; float xw[2] = {(-6.05-0.001)/10.0700, -6.009/10.0700}; float v[2] = {-0.5-0.01, 0.15}; float yw[2] = {(-0.5-0.01)/10.0700, 0.15/10.0700};
   int sizes[3] = {3, 3, 1};
   for(int i=0;i<intensity;i++){
      points[i] = (float*) malloc(2*sizeof(float));
      float x = (float) -6.05-0.001+(i+1)*CIRCLE_LIM; float k;
      //if (((-6.05<x) && (x<-6.00775)) || ((-6.00775<=x) && (x<-5.609))){k = -1.0;} else{k = 1.0;};
      float y = (float) -0.5 + 1.0*sqrt(60.5 + 10.0*((double)x));
      ar[0][0] = x; ar[1][0] = y; ar[2][0] = 1.0;
      multMtx(windowMtx(u, xw, v, yw), ar, vec, sizes);
      points[i][0] = vec[0][0]; points[i][1] = vec[1][0];
   }
   points[intensity] = NULL;
   float color[3] = {color_ar[0], color_ar[1], color_ar[2]};
   //points[0][0] = line_bounds[0][0]; points[0][1] = line_bounds[0][1]; points[1][0] = line_bounds[1][0]; points[1][1] = line_bounds[1][1];
   int figtype = 20;
   listInsert(&Liszt, crtNode(points, figtype, color, thickness), 0);
}
void curve21(){
   long long int intensity = (long long int) floor((double)((2.0*PI*sqrt(0.08))/CIRCLE_LIM));
   float** points = (float**) malloc((intensity+1)*sizeof(float*));
   float** vec = (float**) malloc(3*sizeof(float*)); for(int j=0; j<3; j++){vec[j] = (float*) malloc(sizeof(float));};
   float** ar = (float**) malloc(3*sizeof(float*)); for(int j=0; j<3; j++){ar[j] = (float*) malloc(sizeof(float));};
   float x_m = -1.0*sqrt(0.08)-1.7;
   float u[2] = {x_m, 1.0*sqrt(0.08)-1.7}; float xw[2] = {(-1.0*sqrt(0.08)-1.7)/10.0700, (1.0*sqrt(0.08)-1.7)/10.0700}; \
   float v[2] = {-1.0*sqrt(0.08)+1.9, 1.0*sqrt(0.08)+1.9}; float yw[2] = {(-1.0*sqrt(0.08)+1.9)/10.0700, (1.0*sqrt(0.08)+1.9)/10.0700};
   int sizes[3] = {3, 3, 1}; double radius = sqrt(0.08);
   for(int i=0;i<intensity;i++){
      points[i] = (float*) malloc(2*sizeof(float));
      long double i_intensity = ((long double) i)/((long double) intensity);
      float x = radius * cos(2.0*PI*i_intensity)-1.7;
      float y = radius * sin(2.0*PI*i_intensity)+1.9;
      ar[0][0] = x; ar[1][0] = y; ar[2][0] = 1.0;
      multMtx(windowMtx(u, xw, v, yw), ar, vec, sizes);
      points[i][0] = vec[0][0]; points[i][1] = vec[1][0];
   }
   points[intensity] = NULL;
   float color[3] = {color_ar[0], color_ar[1], color_ar[2]};
   //points[0][0] = line_bounds[0][0]; points[0][1] = line_bounds[0][1]; points[1][0] = line_bounds[1][0]; points[1][1] = line_bounds[1][1];
   int figtype = 21;
   listInsert(&Liszt, crtNode(points, figtype, color, thickness), 0);
}
void curve22(){
   long long int intensity = (long long int) floor((double)((2.0*PI*sqrt(0.08))/CIRCLE_LIM));
   float** points = (float**) malloc((intensity+1)*sizeof(float*));
   float** vec = (float**) malloc(3*sizeof(float*)); for(int j=0; j<3; j++){vec[j] = (float*) malloc(sizeof(float));};
   float** ar = (float**) malloc(3*sizeof(float*)); for(int j=0; j<3; j++){ar[j] = (float*) malloc(sizeof(float));};
   float x_m = -1.0*sqrt(0.08)-4.2;
   float u[2] = {x_m, 1.0*sqrt(0.08)-4.2}; float xw[2] = {(-1.0*sqrt(0.08)-4.2)/10.0700, (1.0*sqrt(0.08)-4.2)/10.0700}; \
   float v[2] = {-1.0*sqrt(0.08)+1.9, 1.0*sqrt(0.08)+1.9}; float yw[2] = {(-1.0*sqrt(0.08)+1.9)/10.0700, (1.0*sqrt(0.08)+1.9)/10.0700};
   int sizes[3] = {3, 3, 1}; double radius = sqrt(0.08);
   for(int i=0;i<intensity;i++){
      points[i] = (float*) malloc(2*sizeof(float));
      long double i_intensity = ((long double) i)/((long double) intensity);
      float x = radius * cos(2.0*PI*i_intensity)-4.2;
      float y = radius * sin(2.0*PI*i_intensity)+1.9;
      ar[0][0] = x; ar[1][0] = y; ar[2][0] = 1.0;
      multMtx(windowMtx(u, xw, v, yw), ar, vec, sizes);
      points[i][0] = vec[0][0]; points[i][1] = vec[1][0];
   }
   points[intensity] = NULL;
   float color[3] = {color_ar[0], color_ar[1], color_ar[2]};
   //points[0][0] = line_bounds[0][0]; points[0][1] = line_bounds[0][1]; points[1][0] = line_bounds[1][0]; points[1][1] = line_bounds[1][1];
   int figtype = 22;
   listInsert(&Liszt, crtNode(points, figtype, color, thickness), 0);
}
void curve23(){
   long long int intensity = (long long int) floor((double)((+3.0-2.65)/CIRCLE_LIM));
   float** points = (float**) malloc((intensity+1)*sizeof(float*));
   float** vec = (float**) malloc(3*sizeof(float*)); for(int j=0; j<3; j++){vec[j] = (float*) malloc(sizeof(float));};
   float** ar = (float**) malloc(3*sizeof(float*)); for(int j=0; j<3; j++){ar[j] = (float*) malloc(sizeof(float));};
   float u[2] = {-3.0, -2.65}; float xw[2] = {-3.0/10.0700, -2.65/10.0700}; float v[2] = {1.6, 1.8525}; float yw[2] = {1.6/10.0700, 1.8525/10.0700};
   int sizes[3] = {3, 3, 1};
   for(int i=0;i<intensity;i++){
      points[i] = (float*) malloc(2*sizeof(float));
      float x = (float) -3.0+(i+1)*CIRCLE_LIM;
      float y = (float) 7.0*(x+2.81)*(((double)x)+2.81)+1.6;
      ar[0][0] = x; ar[1][0] = y; ar[2][0] = 1.0;
      multMtx(windowMtx(u, xw, v, yw), ar, vec, sizes);
      points[i][0] = vec[0][0]; points[i][1] = vec[1][0];
   }
   points[intensity] = NULL;
   float color[3] = {color_ar[0], color_ar[1], color_ar[2]};
   //points[0][0] = line_bounds[0][0]; points[0][1] = line_bounds[0][1]; points[1][0] = line_bounds[1][0]; points[1][1] = line_bounds[1][1];
   int figtype = 23;
   listInsert(&Liszt, crtNode(points, figtype, color, thickness), 0);
}
void curve24(){
   long long int intensity = (long long int) floor((double)((+3.35-3.0)/CIRCLE_LIM));
   float** points = (float**) malloc((intensity+1)*sizeof(float*));
   float** vec = (float**) malloc(3*sizeof(float*)); for(int j=0; j<3; j++){vec[j] = (float*) malloc(sizeof(float));};
   float** ar = (float**) malloc(3*sizeof(float*)); for(int j=0; j<3; j++){ar[j] = (float*) malloc(sizeof(float));};
   float u[2] = {-3.35, -3.0}; float xw[2] = {-3.35/10.0700, -3.0/10.0700}; float v[2] = {1.6, 1.8792}; float yw[2] = {1.6/10.0700, 1.8792/10.0700};
   int sizes[3] = {3, 3, 1};
   for(int i=0;i<intensity;i++){
      points[i] = (float*) malloc(2*sizeof(float));
      float x = (float) -3.35+(i+1)*CIRCLE_LIM;
      float y = (float) 7.0*(x+3.2)*(((double)x)+3.2)+1.6;
      ar[0][0] = x; ar[1][0] = y; ar[2][0] = 1.0;
      multMtx(windowMtx(u, xw, v, yw), ar, vec, sizes);
      points[i][0] = vec[0][0]; points[i][1] = vec[1][0];
   }
   points[intensity] = NULL;
   float color[3] = {color_ar[0], color_ar[1], color_ar[2]};
   //points[0][0] = line_bounds[0][0]; points[0][1] = line_bounds[0][1]; points[1][0] = line_bounds[1][0]; points[1][1] = line_bounds[1][1];
   int figtype = 24;
   listInsert(&Liszt, crtNode(points, figtype, color, thickness), 0);
}
void curve25(){
   long long int intensity = (long long int) floor((double)((2.1-1.85)/CIRCLE_LIM));
   float** points = (float**) malloc((intensity+1)*sizeof(float*));
   float** vec = (float**) malloc(3*sizeof(float*)); for(int j=0; j<3; j++){vec[j] = (float*) malloc(sizeof(float));};
   float** ar = (float**) malloc(3*sizeof(float*)); for(int j=0; j<3; j++){ar[j] = (float*) malloc(sizeof(float));};
   float u[2] = {-3.0, -3+0.0001}; float xw[2] = {-3.0/10.0700, (-3.0+0.0001)/10.0700}; float v[2] = {1.85, 2.1}; float yw[2] = {1.85/10.0700, 2.1/10.0700};
   int sizes[3] = {3, 3, 1};
   for(int i=0;i<intensity;i++){
      points[i] = (float*) malloc(2*sizeof(float));
      float x = (float) -3.0;
      float y = (float) 1.85+(i+1)*CIRCLE_LIM;
      ar[0][0] = x; ar[1][0] = y; ar[2][0] = 1.0;
      multMtx(windowMtx(u, xw, v, yw), ar, vec, sizes);
      points[i][0] = vec[0][0]; points[i][1] = vec[1][0];
   }
   points[intensity] = NULL;
   float color[3] = {color_ar[0], color_ar[1], color_ar[2]};
   //points[0][0] = line_bounds[0][0]; points[0][1] = line_bounds[0][1]; points[1][0] = line_bounds[1][0]; points[1][1] = line_bounds[1][1];
   int figtype = 25;
   listInsert(&Liszt, crtNode(points, figtype, color, thickness), 0);
}
void curve26(){
   long long int intensity = (long long int) floor((double)((-5.62+6.85)/CIRCLE_LIM));
   float** points = (float**) malloc((intensity+1)*sizeof(float*));
   float** vec = (float**) malloc(3*sizeof(float*)); for(int j=0; j<3; j++){vec[j] = (float*) malloc(sizeof(float));};
   float** ar = (float**) malloc(3*sizeof(float*)); for(int j=0; j<3; j++){ar[j] = (float*) malloc(sizeof(float));};
   float u[2] = {-6.85, -5.62}; float xw[2] = {-6.85/10.0700, -5.62/10.0700}; float v[2] = {1.6974, 1.7885}; float yw[2] = {1.6974/10.0700, 1.7885/10.0700};
   int sizes[3] = {3, 3, 1};
   for(int i=0;i<intensity;i++){
      points[i] = (float*) malloc(2*sizeof(float));
      float x = (float) -6.85+(i+1)*CIRCLE_LIM;
      float y = (float) 1.05 - 0.3*x - 0.03*x*x;
      ar[0][0] = x; ar[1][0] = y; ar[2][0] = 1.0;
      multMtx(windowMtx(u, xw, v, yw), ar, vec, sizes);
      points[i][0] = vec[0][0]; points[i][1] = vec[1][0];
   }
   points[intensity] = NULL;
   float color[3] = {color_ar[0], color_ar[1], color_ar[2]};
   //points[0][0] = line_bounds[0][0]; points[0][1] = line_bounds[0][1]; points[1][0] = line_bounds[1][0]; points[1][1] = line_bounds[1][1];
   int figtype = 26;
   listInsert(&Liszt, crtNode(points, figtype, color, thickness), 0);
}
void curve27(){
   long long int intensity = (long long int) floor((double)((+6.8-5.5)/CIRCLE_LIM));
   float** points = (float**) malloc((intensity+1)*sizeof(float*));
   float** vec = (float**) malloc(3*sizeof(float*)); for(int j=0; j<3; j++){vec[j] = (float*) malloc(sizeof(float));};
   float** ar = (float**) malloc(3*sizeof(float*)); for(int j=0; j<3; j++){ar[j] = (float*) malloc(sizeof(float));};
   float u[2] = {-6.8, -5.5}; float xw[2] = {-6.8/10.0700, -5.5/10.0700}; float v[2] = {2.236, 2.4}; float yw[2] = {2.236/10.0700, 2.4/10.0700};
   int sizes[3] = {3, 3, 1};
   for(int i=0;i<intensity;i++){
      points[i] = (float*) malloc(2*sizeof(float));
      float x = (float) -6.8+(i+1)*CIRCLE_LIM;
      float y = (float) -0.17*(((double)x) + 6.5)*(x + 6.5) + 2.4;
      ar[0][0] = x; ar[1][0] = y; ar[2][0] = 1.0;
      multMtx(windowMtx(u, xw, v, yw), ar, vec, sizes);
      points[i][0] = vec[0][0]; points[i][1] = vec[1][0];
   }
   points[intensity] = NULL;
   float color[3] = {color_ar[0], color_ar[1], color_ar[2]};
   //points[0][0] = line_bounds[0][0]; points[0][1] = line_bounds[0][1]; points[1][0] = line_bounds[1][0]; points[1][1] = line_bounds[1][1];
   int figtype = 27;
   listInsert(&Liszt, crtNode(points, figtype, color, thickness), 0);
}
void curve28(){
   long long int intensity = (long long int) floor((double)((+0.7+0.6)/CIRCLE_LIM));
   float** points = (float**) malloc((intensity+1)*sizeof(float*));
   float** vec = (float**) malloc(3*sizeof(float*)); for(int j=0; j<3; j++){vec[j] = (float*) malloc(sizeof(float));};
   float** ar = (float**) malloc(3*sizeof(float*)); for(int j=0; j<3; j++){ar[j] = (float*) malloc(sizeof(float));};
   float u[2] = {-0.7, 0.6}; float xw[2] = {-0.7/10.0700, 0.6/10.0700}; float v[2] = {2.2313, 2.4951}; float yw[2] = {2.2313/10.0700, 2.4951/10.0700};
   int sizes[3] = {3, 3, 1};
   for(int i=0;i<intensity;i++){
      points[i] = (float*) malloc(2*sizeof(float));
      float x = (float) -0.7+(i+1)*CIRCLE_LIM;
      float y = (float) -0.12*(((double)x) - 0.8)*(((double)x) - 0.8) + 2.5;
      ar[0][0] = x; ar[1][0] = y; ar[2][0] = 1.0;
      multMtx(windowMtx(u, xw, v, yw), ar, vec, sizes);
      points[i][0] = vec[0][0]; points[i][1] = vec[1][0];
   }
   points[intensity] = NULL;
   float color[3] = {color_ar[0], color_ar[1], color_ar[2]};
   //points[0][0] = line_bounds[0][0]; points[0][1] = line_bounds[0][1]; points[1][0] = line_bounds[1][0]; points[1][1] = line_bounds[1][1];
   int figtype = 28;
   listInsert(&Liszt, crtNode(points, figtype, color, thickness), 0);
}
void curve29(){
   long long int intensity = (long long int) floor((double)((+0.7+0.6)/CIRCLE_LIM));
   float** points = (float**) malloc((intensity+1)*sizeof(float*));
   float** vec = (float**) malloc(3*sizeof(float*)); for(int j=0; j<3; j++){vec[j] = (float*) malloc(sizeof(float));};
   float** ar = (float**) malloc(3*sizeof(float*)); for(int j=0; j<3; j++){ar[j] = (float*) malloc(sizeof(float));};
   float u[2] = {-0.6, 0.7}; float xw[2] = {-0.6/10.0700, 0.7/10.0700}; float v[2] = {1.7523, 1.85}; float yw[2] = {1.7523/10.0700, 1.85/10.0700};
   int sizes[3] = {3, 3, 1};
   for(int i=0;i<intensity;i++){
      points[i] = (float*) malloc(2*sizeof(float));
      float x = (float) -0.6+(i+1)*CIRCLE_LIM;
      float y = (float) -0.2*x*x + 1.85;
      ar[0][0] = x; ar[1][0] = y; ar[2][0] = 1.0;
      multMtx(windowMtx(u, xw, v, yw), ar, vec, sizes);
      points[i][0] = vec[0][0]; points[i][1] = vec[1][0];
   }
   points[intensity] = NULL;
   float color[3] = {color_ar[0], color_ar[1], color_ar[2]};
   //points[0][0] = line_bounds[0][0]; points[0][1] = line_bounds[0][1]; points[1][0] = line_bounds[1][0]; points[1][1] = line_bounds[1][1];
   int figtype = 29;
   listInsert(&Liszt, crtNode(points, figtype, color, thickness), 0);
}
void curve30(){
   long long int intensity = (long long int) floor((double)((+3.72-3.32)/CIRCLE_LIM));
   float** points = (float**) malloc((intensity+1)*sizeof(float*));
   float** vec = (float**) malloc(3*sizeof(float*)); for(int j=0; j<3; j++){vec[j] = (float*) malloc(sizeof(float));};
   float** ar = (float**) malloc(3*sizeof(float*)); for(int j=0; j<3; j++){ar[j] = (float*) malloc(sizeof(float));};
   float u[2] = {-3.72, -3.32}; float xw[2] = {-3.72/10.0700, -3.32/10.0700}; float v[2] = {2.71270165, 3.1}; float yw[2] = {2.71270165/10.0700, 3.1/10.0700};
   int sizes[3] = {3, 3, 1};
   for(int i=0;i<intensity;i++){
      points[i] = (float*) malloc(2*sizeof(float));
      float x = (float) -3.72+(i+1)*CIRCLE_LIM;
      float y = (float) 0.02*(155.0 - sqrt(15.0)*sqrt(-7719.0 - 4400.0*((double)x) - 625.0*((double)x)*x));
      ar[0][0] = x; ar[1][0] = y; ar[2][0] = 1.0;
      multMtx(windowMtx(u, xw, v, yw), ar, vec, sizes);
      points[i][0] = vec[0][0]; points[i][1] = vec[1][0];
   }
   points[intensity] = NULL;
   float color[3] = {color_ar[0], color_ar[1], color_ar[2]};
   //points[0][0] = line_bounds[0][0]; points[0][1] = line_bounds[0][1]; points[1][0] = line_bounds[1][0]; points[1][1] = line_bounds[1][1];
   int figtype = 30;
   listInsert(&Liszt, crtNode(points, figtype, color, thickness), 0);
}
void curve31(){
   long long int intensity = (long long int) floor((double)((6.74-5.9)/CIRCLE_LIM));
   float** points = (float**) malloc((intensity+1)*sizeof(float*));
   float** vec = (float**) malloc(3*sizeof(float*)); for(int j=0; j<3; j++){vec[j] = (float*) malloc(sizeof(float));};
   float** ar = (float**) malloc(3*sizeof(float*)); for(int j=0; j<3; j++){ar[j] = (float*) malloc(sizeof(float));};
   float u[2] = {5.9, 6.74}; float xw[2] = {5.9/10.0700, 6.74/10.0700}; float v[2] = {0.8971, 1.2858}; float yw[2] = {0.8971/10.0700, 1.2858/10.0700};
   int sizes[3] = {3, 3, 1};
   for(int i=0;i<intensity;i++){
      points[i] = (float*) malloc(2*sizeof(float));
      float x = (float) 5.9+(i+1)*CIRCLE_LIM;
      float y = (float) -0.46*x+4.0;
      ar[0][0] = x; ar[1][0] = y; ar[2][0] = 1.0;
      multMtx(windowMtx(u, xw, v, yw), ar, vec, sizes);
      points[i][0] = vec[0][0]; points[i][1] = vec[1][0];
   }
   points[intensity] = NULL;
   float color[3] = {color_ar[0], color_ar[1], color_ar[2]};
   //points[0][0] = line_bounds[0][0]; points[0][1] = line_bounds[0][1]; points[1][0] = line_bounds[1][0]; points[1][1] = line_bounds[1][1];
   int figtype = 31;
   listInsert(&Liszt, crtNode(points, figtype, color, thickness), 0);
}
void curve32(){
   long long int intensity = (long long int) floor((double)((5.4-5.175)/CIRCLE_LIM));
   float** points = (float**) malloc((intensity+1)*sizeof(float*));
   float** vec = (float**) malloc(3*sizeof(float*)); for(int j=0; j<3; j++){vec[j] = (float*) malloc(sizeof(float));};
   float** ar = (float**) malloc(3*sizeof(float*)); for(int j=0; j<3; j++){ar[j] = (float*) malloc(sizeof(float));};
   float u[2] = {5.175, 5.4}; float xw[2] = {5.175/10.0700, 5.4/10.0700}; float v[2] = {-0.5, 0.6304}; float yw[2] = {-0.5/10.0700, 0.6304/10.0700};
   int sizes[3] = {3, 3, 1};
   for(int i=0;i<intensity;i++){
      points[i] = (float*) malloc(2*sizeof(float));
      float x = (float) 5.175+(i+1)*CIRCLE_LIM;
      float y = (float) -5.0*x+26.5;
      ar[0][0] = x; ar[1][0] = y; ar[2][0] = 1.0;
      multMtx(windowMtx(u, xw, v, yw), ar, vec, sizes);
      points[i][0] = vec[0][0]; points[i][1] = vec[1][0];
   }
   points[intensity] = NULL;
   float color[3] = {color_ar[0], color_ar[1], color_ar[2]};
   //points[0][0] = line_bounds[0][0]; points[0][1] = line_bounds[0][1]; points[1][0] = line_bounds[1][0]; points[1][1] = line_bounds[1][1];
   int figtype = 32;
   listInsert(&Liszt, crtNode(points, figtype, color, thickness), 0);
}
void curve33(){
   long long int intensity = (long long int) floor((double)((5.95-5.35)/CIRCLE_LIM));
   float** points = (float**) malloc((intensity+1)*sizeof(float*));
   float** vec = (float**) malloc(3*sizeof(float*)); for(int j=0; j<3; j++){vec[j] = (float*) malloc(sizeof(float));};
   float** ar = (float**) malloc(3*sizeof(float*)); for(int j=0; j<3; j++){ar[j] = (float*) malloc(sizeof(float));};
   float u[2] = {5.35, 5.95}; float xw[2] = {5.35/10.0700, 5.95/10.0700}; float v[2] = {-0.1255, 0.7275}; float yw[2] = {-0.1255/10.0700, 0.7275/10.0700};
   int sizes[3] = {3, 3, 1};
   for(int i=0;i<intensity;i++){
      points[i] = (float*) malloc(2*sizeof(float));
      float x = (float) 5.35+(i+1)*CIRCLE_LIM;
      float y = (float) -1.4*x+8.2;

      ar[0][0] = x; ar[1][0] = y; ar[2][0] = 1.0;
      multMtx(windowMtx(u, xw, v, yw), ar, vec, sizes);
      points[i][0] = vec[0][0]; points[i][1] = vec[1][0];
   }
   points[intensity] = NULL;
   float color[3] = {color_ar[0], color_ar[1], color_ar[2]};
   //points[0][0] = line_bounds[0][0]; points[0][1] = line_bounds[0][1]; points[1][0] = line_bounds[1][0]; points[1][1] = line_bounds[1][1];
   int figtype = 33;
   listInsert(&Liszt, crtNode(points, figtype, color, thickness), 0);
}

void curve34(){
   long long int intensity = (long long int) floor((double)((-5.06251+5.07)/CIRCLE_LIM));
   float** points = (float**) malloc((intensity+1)*sizeof(float*));
   float** vec = (float**) malloc(3*sizeof(float*)); for(int j=0; j<3; j++){vec[j] = (float*) malloc(sizeof(float));};
   float** ar = (float**) malloc(3*sizeof(float*)); for(int j=0; j<3; j++){ar[j] = (float*) malloc(sizeof(float));};
   float u[2] = {5.06251, 5.07}; float xw[2] = {5.06251/10.0700, 5.07/10.0700}; float v[2] = {-0.6, -0.3256}; float yw[2] = {-0.6/10.0700, -0.3256/10.0700};
   int sizes[3] = {3, 3, 1};
   for(int i=0;i<intensity;i++){
      points[i] = (float*) malloc(2*sizeof(float));
      float x = (float) 5.06251+(i+1)*CIRCLE_LIM;
      float y = (float) 0.05*(-42.0 + 7.0*x - sqrt(32404.0 - 8668.0*x + 449.0*x*x));
      ar[0][0] = x; ar[1][0] = y; ar[2][0] = 1.0;
      multMtx(windowMtx(u, xw, v, yw), ar, vec, sizes);
      points[i][0] = vec[0][0]; points[i][1] = vec[1][0];
   }
   points[intensity] = NULL;   
   float color[3] = {color_ar[0], color_ar[1], color_ar[2]};
   //points[0][0] = line_bounds[0][0]; points[0][1] = line_bounds[0][1]; points[1][0] = line_bounds[1][0]; points[1][1] = line_bounds[1][1];
   int figtype = 34;
   listInsert(&Liszt, crtNode(points, figtype, color, thickness), 0);
}
void curve35(){
   long long int intensity = (long long int) floor((double)((-5.0+5.059)/CIRCLE_LIM));
   float** points = (float**) malloc((intensity+1)*sizeof(float*));
   float** vec = (float**) malloc(3*sizeof(float*)); for(int j=0; j<3; j++){vec[j] = (float*) malloc(sizeof(float));};
   float** ar = (float**) malloc(3*sizeof(float*)); for(int j=0; j<3; j++){ar[j] = (float*) malloc(sizeof(float));};
   float u[2] = {5.0, 5.059}; float xw[2] = {5.0/10.0700, 5.059/10.0700}; float v[2] = {0.0, 0.555}; float yw[2] = {0.0/10.0700, 0.555/10.0700};
   int sizes[3] = {3, 3, 1};
   for(int i=0;i<intensity;i++){
      points[i] = (float*) malloc(2*sizeof(float));
      float x = (float) 5.0+(i+1)*CIRCLE_LIM;
      float y = (float) 0.05*(-42.0 + 7.0*x + sqrt(32404.0 - 8668.0*x + 449.0*x*x));
      ar[0][0] = x; ar[1][0] = y; ar[2][0] = 1.0;
      multMtx(windowMtx(u, xw, v, yw), ar, vec, sizes);
      points[i][0] = vec[0][0]; points[i][1] = vec[1][0];
   }

   float color[3] = {color_ar[0], color_ar[1], color_ar[2]};
   //points[0][0] = line_bounds[0][0]; points[0][1] = line_bounds[0][1]; points[1][0] = line_bounds[1][0]; points[1][1] = line_bounds[1][1];
   int figtype = 35;
   points[intensity] = NULL;
   listInsert(&Liszt, crtNode(points, figtype, color, thickness), 0);
}
void curve36(){
   long long int intensity = (long long int) floor((double)((-5.059+5.06969)/CIRCLE_LIM));
   float** points = (float**) malloc((intensity+1)*sizeof(float*));
   float** vec = (float**) malloc(3*sizeof(float*)); for(int j=0; j<3; j++){vec[j] = (float*) malloc(sizeof(float));};
   float** ar = (float**) malloc(3*sizeof(float*)); for(int j=0; j<3; j++){ar[j] = (float*) malloc(sizeof(float));};
   float u[2] = {5.059, 5.06969}; float xw[2] = {5.059/10.0700, 5.06969/10.0700}; float v[2] = {-0.3256, 0.0}; float yw[2] = {-0.3256/10.0700, 0.0/10.0700};
   int sizes[3] = {3, 3, 1};
   for(int i=0;i<intensity;i++){
      points[i] = (float*) malloc(2*sizeof(float));
      float x = (float) 5.059+(i+1)*CIRCLE_LIM;
      float y = (float) 0.05*(-42.0 + 7.0*x + sqrt(32404.0 - 8668.0*x + 449.0*x*x));
      ar[0][0] = x; ar[1][0] = y; ar[2][0] = 1.0;
      multMtx(windowMtx(u, xw, v, yw), ar, vec, sizes);
      points[i][0] = vec[0][0]; points[i][1] = vec[1][0];
   }
   points[intensity] = NULL;

   float color[3] = {color_ar[0], color_ar[1], color_ar[2]};
   //points[0][0] = line_bounds[0][0]; points[0][1] = line_bounds[0][1]; points[1][0] = line_bounds[1][0]; points[1][1] = line_bounds[1][1];
   int figtype = 36;
   listInsert(&Liszt, crtNode(points, figtype, color, thickness), 0);
}
void curve37(){
   long long int intensity = (long long int) floor((double)((-5.67+6.379)/CIRCLE_LIM));
   float** points = (float**) malloc((intensity+1)*sizeof(float*));
   float** vec = (float**) malloc(3*sizeof(float*)); for(int j=0; j<3; j++){vec[j] = (float*) malloc(sizeof(float));};
   float** ar = (float**) malloc(3*sizeof(float*)); for(int j=0; j<3; j++){ar[j] = (float*) malloc(sizeof(float));};
   float u[2] = {5.67, 6.379}; float xw[2] = {5.67/10.0700, 6.379/10.0700}; float v[2] = {0.3579, 0.9956}; float yw[2] = {0.3579/10.0700, 0.9956/10.0700};
   int sizes[3] = {3, 3, 1};
   for(int i=0;i<intensity;i++){
      points[i] = (float*) malloc(2*sizeof(float));
      float x = (float) 5.67+(i+1)*CIRCLE_LIM;
      float y = (float) -0.9*x+6.1;
      ar[0][0] = x; ar[1][0] = y; ar[2][0] = 1.0;
      multMtx(windowMtx(u, xw, v, yw), ar, vec, sizes);
      points[i][0] = vec[0][0]; points[i][1] = vec[1][0];
   }
   points[intensity] = NULL;

   float color[3] = {color_ar[0], color_ar[1], color_ar[2]};
   //points[0][0] = line_bounds[0][0]; points[0][1] = line_bounds[0][1]; points[1][0] = line_bounds[1][0]; points[1][1] = line_bounds[1][1];
   int figtype = 37;
   listInsert(&Liszt, crtNode(points, figtype, color, thickness), 0);
}
void ball(){
   float radius = 0.1;
   long long int intensity = (long long int) floor((double)((2.0*PI*radius)/CIRCLE_LIM));
   float** points = (float**) malloc((intensity+1)*sizeof(float*));
   for(int i=0;i<intensity;i++){
      points[i] = (float*) malloc(2*sizeof(float));
      float par_arg = 2.0*PI*i/intensity;
      float x = (float) radius*cos(10.0*(1.0+radius)*par_arg)*sin(par_arg) + right_click[0];
      float y = (float) radius*sin(10.0*(1.0+radius)*par_arg) + right_click[1];
      points[i][0] = x; points[i][1] = y;
   }
   points[intensity] = NULL;
   float color[3] = {color_ar[0], color_ar[1], color_ar[2]};
   int figtype = 666;
   listInsert(&Liszt, crtNode(points, figtype, color, thickness), 0);
   float** new_center = (float**) malloc(sizeof(float*)); for(int j=0; j<2; j++){new_center[j] = (float*) malloc(sizeof(float));};
   new_center[0][0] = right_click[0]; new_center[0][1] = right_click[1];
   listInsert(&Balls, crtNode(new_center, figtype, color, thickness), 0);
}

void Timer(int extra) {
   glutPostRedisplay();
   glutTimerFunc(30,Timer,0);
}

void rotCat(void){
   int i = 0; Node* obj;
   float** points = (float**) malloc(3*sizeof(float*)); for(int i=0;i<3;i++){points[i] = (float*) malloc(sizeof(float));}
   float** prod = (float**) malloc(3*sizeof(float*)); for(int i=0;i<3;i++){prod[i] = (float*) malloc(sizeof(float));}
   float pivot[2];
   while(i < listLen(Liszt) && (obj = listGetittem(Liszt, i)) != NULL){
      int j=0;
      if((obj->fig2d) != 666){
         while((obj->points)[j]!=NULL){
            points[0][0] = (obj->points)[j][0]; points[1][0] = (obj->points)[j][1]; points[2][0] = 1.0;
            pivot[0] = fixed_points[2]; pivot[1] = fixed_points[3];
            rotCurve(points, cicle, pivot, prod);
            (obj->points)[j][0] = prod[0][0]; (obj->points)[j][1] = prod[1][0];
            j++;
         }
      }
      i++;
   }
   points[0][0] = head_ref[0]; points[1][0] = head_ref[1]; points[2][0] = 1.0;
   pivot[0] = fixed_points[2]; pivot[1] = fixed_points[3];
   rotCurve(points, cicle, pivot, prod);
   head_ref[0] = prod[0][0]; head_ref[1] = prod[1][0];
   for(int i=0;i<3;i++){free(points[i]); free(prod[i]);} free(points); free(prod);
}

void transCat(void){
   int i = 0; Node* obj;
   float** points = (float**) malloc(3*sizeof(float*)); for(int i=0;i<3;i++){points[i] = (float*) malloc(sizeof(float));}
   float** prod = (float**) malloc(3*sizeof(float*)); for(int i=0;i<3;i++){prod[i] = (float*) malloc(sizeof(float));}
   while(i < listLen(Liszt) && ((obj = listGetittem(Liszt, i)) != NULL)){
      int j=0;
      float pivot[2] = {bias*(ball_center[0]-fixed_points[2]), bias*(ball_center[1]-fixed_points[3])};
      if((obj->fig2d) != 666){
         while((obj->points)[j]!=NULL){
            points[0][0] = (obj->points)[j][0]; points[1][0] = (obj->points)[j][1]; points[2][0] = 1.0;
            transCurve(points, pivot, prod);
            (obj->points)[j][0] = prod[0][0]; (obj->points)[j][1] = prod[1][0];
            j++;
         }
      }
      i++;
   }
   for(int i=0;i<3;i++){free(points[i]); free(prod[i]);} free(points); free(prod);
}

void scaleCat(void){
   int i = 0; Node* obj;
   float** points = (float**) malloc(3*sizeof(float*)); for(int i=0;i<3;i++){points[i] = (float*) malloc(sizeof(float));}
   float** prod = (float**) malloc(3*sizeof(float*)); for(int i=0;i<3;i++){prod[i] = (float*) malloc(sizeof(float));}
   float pivot[2];
   float amount[2] = {1.0+sxy, 1.0+sxy};
   while(i < listLen(Liszt) && ((obj = listGetittem(Liszt, i)) != NULL)){
      int j=0;
      if((obj->fig2d) != 666){
         while((obj->points)[j]!=NULL){
            pivot[0] = mass_center[0]; pivot[1] = mass_center[1];
            points[0][0] = (obj->points)[j][0]; points[1][0] = (obj->points)[j][1]; points[2][0] = 1.0;
            scaleCurve(points, amount, pivot, prod);
            (obj->points)[j][0] = prod[0][0]; (obj->points)[j][1] = prod[1][0];
            j++;
         }
      }
      i++;
   }
   points[0][0] = head_ref[0]; points[1][0] = head_ref[1]; points[2][0] = 1.0;
   pivot[0] = mass_center[0]; pivot[1] = mass_center[1];
   scaleCurve(points, amount, pivot, prod);
   head_ref[0] = prod[0][0]; head_ref[1] = prod[1][0];
   for(int i=0;i<3;i++){free(points[i]); free(prod[i]);} free(points); free(prod);
}

void catAnim(void){
   if(busy==1){
      transCat(); 
      head_ref[0] += (bias)*(ball_center[0]-fixed_points[2]);
      head_ref[1] += (bias)*(ball_center[1]-fixed_points[3]);
      mass_center[0] += (bias)*(ball_center[0]-fixed_points[2]); mass_center[1] += (bias)*(ball_center[1]-fixed_points[3]);
   } 
   else if(busy==0){rotCat();}
}

void redrawAll(){
   glClearColor(0.0, 0.0, 0.0, 0.0);
   glClear(GL_COLOR_BUFFER_BIT);
   int i = listLen(Liszt); Node* obj;
   while (i!=-1 && (obj = listGetittem(Liszt, i-1)) != NULL){
      switch((obj->fig2d)){

         long long int intensity;
         case 1000: //point
            glPointSize((GLfloat) obj->thick);
            glBegin(GL_LINES);
               glColor3f((GLfloat) (obj->color)[0], (GLfloat) (obj->color)[1], (GLfloat) (obj->color)[2]);
               glVertex2f((GLfloat) (obj->points)[0][0], (GLfloat) (obj->points)[0][1]);
               //glVertex2f((GLfloat) mass_center[0], (GLfloat) mass_center[1]);
               glVertex2f((GLfloat) (obj->points)[1][0], (GLfloat) (obj->points)[1][1]);
               //glVertex2f((GLfloat) head_ref[0], (GLfloat) head_ref[1]);
            glEnd();
            break;
         case 666:
            intensity = (long long int) floor((double)((2.0*PI*0.1)/CIRCLE_LIM));
            redrawStrip(obj, intensity);   
            break;            
         case 1:
            intensity = (long long int) floor((double)((3.0700-1.9560)/CIRCLE_LIM));
            redrawStrip(obj, intensity);
            break;
         case 2:
            intensity = (long long int) floor((double)((1.6200-0.4550)/CIRCLE_LIM));
            redrawStrip(obj, intensity);
            break;
         case 3:
            intensity = (long long int) floor((double)((5.89-4.965)/CIRCLE_LIM));
            redrawStrip(obj, intensity);
            break;
         case 4:
            intensity = (long long int) floor((double)((6.945-5.07)/CIRCLE_LIM));
            redrawStrip(obj, intensity);
            break;
         case 5:
            intensity = (long long int) floor((double)((6.9253-5.879)/CIRCLE_LIM));
            redrawStrip(obj, intensity);
            break;
         case 6:
            intensity = (long long int) floor((double)((5.070-3.4)/CIRCLE_LIM));
            redrawStrip(obj, intensity);
            break;
         case 7:
            intensity = (long long int) floor((double)((-4.25+5.59)/CIRCLE_LIM));
            redrawStrip(obj, intensity);
            break;
         case 8:
            intensity = (long long int) floor((double)((-3.64411+4.25589)/CIRCLE_LIM));
            redrawStrip(obj, intensity);
            break;
         case 9:
            intensity = (long long int) floor((double)((-2.2+3.64)/CIRCLE_LIM));
            redrawStrip(obj, intensity);
            break;
         case 10:
            intensity = (long long int) floor((double)((-1.57211+2.18389)/CIRCLE_LIM));
            redrawStrip(obj, intensity);
            break;
         case 11:
            intensity = (long long int) floor((double)((0.85+1.56)/CIRCLE_LIM));
            redrawStrip(obj, intensity);
            break;
         case 12:
            intensity = (long long int) floor((double)((1.4559-0.844106)/CIRCLE_LIM));
            redrawStrip(obj, intensity);
            break;
         case 13:
            intensity = (long long int) floor((double)((2.8-1.45)/CIRCLE_LIM));
            redrawStrip(obj, intensity);
            break;
         case 14:
            intensity = (long long int) floor((double)((3.40589-2.79411)/CIRCLE_LIM));
            redrawStrip(obj, intensity);
            break;
         case 15:
            intensity = (long long int) floor((double)((4.97+0.75)/CIRCLE_LIM));
            redrawStrip(obj, intensity);
            break;
         case 16:
            intensity = (long long int) floor((double)((-0.75+2.2)/CIRCLE_LIM));
            redrawStrip(obj, intensity);
            break;
         case 17:
            intensity = (long long int) floor((double)((-3.7+6.003)/CIRCLE_LIM));
            redrawStrip(obj, intensity);
            break;
         case 18:
            intensity = (long long int) floor((double)((+3.68-2.22)/CIRCLE_LIM));
            redrawStrip(obj, intensity);
            break;
         case 19:
            intensity = (long long int) floor((double)((-5.61+6.06)/CIRCLE_LIM));
            redrawStrip(obj, intensity);
            break;
         case 20:
            intensity = (long long int) floor((double)((-6.009+6.05)/CIRCLE_LIM));
            redrawStrip(obj, intensity);
            break;
         case 21:
            intensity = (long long int) floor((double)((2.0*PI*sqrt(0.08))/CIRCLE_LIM));
            redrawStrip(obj, intensity);
            break;
         case 22:
            intensity = (long long int) floor((double)((2.0*PI*sqrt(0.08))/CIRCLE_LIM));
            redrawStrip(obj, intensity);
            break;
         case 23:
            intensity = (long long int) floor((double)((+3.0-2.65)/CIRCLE_LIM));
            redrawStrip(obj, intensity);
            break;
         case 24:
            intensity = (long long int) floor((double)((+3.35-3.0)/CIRCLE_LIM));
            redrawStrip(obj, intensity);
            break;
         case 25:
            intensity = (long long int) floor((double)((2.1-1.85)/CIRCLE_LIM));
            redrawStrip(obj, intensity);
            break;
         case 26:
            intensity = (long long int) floor((double)((-5.62+6.85)/CIRCLE_LIM));
            redrawStrip(obj, intensity);
            break;  
         case 27:
            intensity = (long long int) floor((double)((+6.8-5.5)/CIRCLE_LIM));
            redrawStrip(obj, intensity);
            break;
         case 28:
            intensity = (long long int) floor((double)((+0.7+0.6)/CIRCLE_LIM));
            redrawStrip(obj, intensity);
            break;
         case 29:
            intensity = (long long int) floor((double)((+0.7+0.6)/CIRCLE_LIM));
            redrawStrip(obj, intensity);
            break;
         case 30:
            intensity = (long long int) floor((double)((+3.72-3.32)/CIRCLE_LIM));
            redrawStrip(obj, intensity);
            break;
         case 31:
            intensity = (long long int) floor((double)((6.74-5.9)/CIRCLE_LIM));
            redrawStrip(obj, intensity);
            break;
         case 32:
            intensity = (long long int) floor((double)((5.4-5.175)/CIRCLE_LIM));
            redrawStrip(obj, intensity);
            break;
         case 33:
            intensity = (long long int) floor((double)((5.95-5.35)/CIRCLE_LIM));
            redrawStrip(obj, intensity);
            break;
         case 34:
            intensity = (long long int) floor((double)((-5.06251+5.07)/CIRCLE_LIM));
            redrawStrip(obj, intensity);
            break;
         case 35:
            intensity = (long long int) floor((double)((-5.0+5.059)/CIRCLE_LIM));
            redrawStrip(obj, intensity);
            break;
         case 36:
            intensity = (long long int) floor((double)((-5.059+5.06969)/CIRCLE_LIM));
            redrawStrip(obj, intensity);
            break;
         case 37:
            intensity = (long long int) floor((double)((-5.67+6.379)/CIRCLE_LIM));
            redrawStrip(obj, intensity);
            break;
         default: break;
      }
      i--;
   }
   glutSwapBuffers();
}
void redrawStrip(Node* obj, long long int intensity){
   glLineWidth((GLfloat) obj->thick);
   glBegin(GL_LINE_STRIP);
      glColor3f((GLfloat) (obj->color)[0], (GLfloat) (obj->color)[1], (GLfloat) (obj->color)[2]);
      for(int i=0;i<intensity;i++){
         glVertex2f((GLfloat) (obj->points)[i][0], (GLfloat) (obj->points)[i][1]);
      }
   glEnd();
}

int main(int argc, char** argv){
   glutInit(&argc, argv);
   glutTimerFunc(0,Timer,0);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowPosition(0,0);
   glutInitWindowSize(DISPLAY_WIDTH,DISPLAY_HEIGHT);
   glutCreateWindow("Ex");
   drawCat();
   glClearColor(0.0, 0.0, 0.0, 0);
   glClear(GL_COLOR_BUFFER_BIT);
   glutIdleFunc(catchBall);
   glutKeyboardFunc(Keyboard);
   glutMouseFunc(MouseInt);
   glutMainLoop();
   return 0;
}