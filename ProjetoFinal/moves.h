#include "human.h"
#ifndef MOVES_HEADER
#define MOVES_HEADER

void rotV1D(float* ref[], List** parts, float* angx, float* angy, float* angz);
void rotV2D(float* ref[], List** parts, float* angx, float* angy, float* angz);
void rotV3D(float* ref[], List** parts, float* angx, float* angy, float* angz);
void rotT(float* ref[], List** parts, float* angx, float* angy, float* angz, void (*h_vd)(), void (*h_ve)(), void (*h_t)());
void hndlVD(); void hndlVE(); void hndlPE(); void hndlPD(); void hndlT(); void hndlH(); void hndlGlobal();
void draw(List* obj);
/* ang_(0)V1D, ang_(1)V2D, ang_(2)V1E, ang_(3)V2E, ang_(4)V3D, ang_(5)V3E, ang_(6)P1D, ang_(7)P2D, ang_(8)P1E, ang_(9)P2E, ang_(10)P3D, ang_(11)P3E, ang_(12)C,
ang_(13)T, ang_(14)Global */
float ang_x[] = {0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0, 0.0, 0.0}; 
float ang_y[] = {0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0, 0.0, 0.0};
float ang_z[] = {0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0, 0.0, 0.0};
float h_shift = 0.0;

double delta_ang = 1.0;
float walk_ang_x[6]; /* angulo final de cada junta (E: [0,1,2], D: [3,4,5]) */
float walk_start_ang_x[6]; /* angulo inicial de cada junta (E: [0,1,2], D: [3,4,5]) */
float walk_shift; /* posicao final de deslocamento */
int to_walk = 0; /* modo Walking */
int walk_state = 0; /* */
int walk_turn = 0; /* 0: perna (esquerda forwardMotion, direita backwardMotion), 1: perna (direita forwardMotion, esquerda backwardMotion) */
int firstLeg_idx[3]; /* ang_y_IDX(V1, V2, V3) da perna walk_turn */ 
int auxLeg_idx[3]; /* ang_y_IDX(V1, V2, V3) da perna !walk_turn */

void rotV1D(float* ref[], List** parts, float* angx, float* angy, float* angz){
	glPushMatrix();
		glTranslatef(ref[0][0],ref[0][1],ref[0][2]);
		glRotatef(angx[0], 1.0, 0.0, 0.0);
		glRotatef(angy[0], 0.0, 1.0, 0.0);
		glRotatef(angz[0], 0.0, 0.0, 1.0);
		glTranslatef(-ref[0][0],-ref[0][1],-ref[0][2]); // V1D
		draw(parts[0]); // BD
		rotV2D(ref, parts, angx, angy, angz);
	glPopMatrix();
}

void rotV2D(float* ref[], List** parts, float* angx, float* angy, float* angz){
	glPushMatrix();
		glTranslatef(ref[1][0],ref[1][1],ref[1][2]);
		glRotatef(angx[1], 1.0, 0.0, 0.0);
		glRotatef(angy[1], 0.0, 1.0, 0.0);
		glRotatef(angz[1], 0.0, 0.0, 1.0);
		glTranslatef(-ref[1][0],-ref[1][1],-ref[1][2]); // V2D
		draw(parts[1]); // ABD
		rotV3D(ref, parts, angx, angy, angz);
	glPopMatrix();
}

void rotV3D(float* ref[], List** parts, float* angx, float* angy, float* angz){
	glPushMatrix();
		glTranslatef(ref[2][0],ref[2][1],ref[2][2]);
		glRotatef(angx[2], 1.0, 0.0, 0.0);
		glRotatef(angy[2], 0.0, 1.0, 0.0);
		glRotatef(angz[2], 0.0, 0.0, 1.0);
		glTranslatef(-ref[2][0],-ref[2][1],-ref[2][2]); // V3D
		draw(parts[2]); // MD
	glPopMatrix();
}

void rotP1D(float* ref[], List** parts, float* angx, float* angy, float* angz){
	glPushMatrix();
		glTranslatef(ref[0][0],ref[0][1],ref[0][2]);
		glRotatef(angx[0], 1.0, 0.0, 0.0);
		glRotatef(angy[0], 0.0, 1.0, 0.0);
		glRotatef(angz[0], 0.0, 0.0, 1.0);
		glTranslatef(-ref[0][0],-ref[0][1],-ref[0][2]); // V1D
		draw(parts[1]);
		draw(parts[0]); // BD
		parts[1] = parts[2]; parts[2] = parts[3]; parts[3] = NULL;
		rotV2D(ref, parts, angx, angy, angz);
	glPopMatrix();
}
void rotT(float* ref[], List** parts, float* angx, float* angy, float* angz, void (*h_vd)(), void (*h_ve)(), void (*h_t)()){
	glPushMatrix();
		glTranslatef(ref[0][0],ref[0][1],ref[0][2]);
		glRotatef(angx[0], 1.0, 0.0, 0.0);
		glRotatef(angy[0], 0.0, 1.0, 0.0);
		glRotatef(angz[0], 0.0, 0.0, 1.0);		
		glTranslatef(-ref[0][0],-ref[0][1],-ref[0][2]);
		draw(parts[0]);
		(void)(*h_vd)();
		(void)(*h_ve)();
		(void)(*h_t)();
	glPopMatrix();
}
void rotH(float* ref[], List** parts, float* angx, float* angy, float* angz){
	glPushMatrix();
		glTranslatef(ref[0][0],ref[0][1],ref[0][2]);
		glRotatef(angx[0], 1.0, 0.0, 0.0);
		glRotatef(angy[0], 0.0, 1.0, 0.0);
		glRotatef(angz[0], 0.0, 0.0, 1.0);		
		glTranslatef(-ref[0][0],-ref[0][1],-ref[0][2]);
		draw(parts[0]);
	glPopMatrix();
}

void hndlVD(){
	float* ref[] = {ref_joints[1], ref_joints[3], ref_joints[5]};
	List* parts[] = {(human.parts)[2], (human.parts)[1], (human.parts)[5]};
	float angx[] = {ang_x[0], ang_x[1], ang_x[4]}; float angy[] = {ang_y[0], ang_y[1], ang_y[4]}; float angz[] = {ang_z[0], ang_z[1], ang_z[4]};
	rotV1D(ref, parts, angx, angy, angz);
}

void hndlVE(){
	float* ref[] = {ref_joints[0], ref_joints[2], ref_joints[4]};
	List* parts[] = {(human.parts)[3], (human.parts)[0], (human.parts)[6]};
	float angx[] = {ang_x[2], ang_x[3], ang_x[5]}; float angy[] = {ang_y[2], ang_y[3], ang_y[5]}; float angz[] = {ang_z[2], ang_z[3], ang_z[5]};
	rotV1D(ref, parts, angx, angy, angz);
}

void hndlPD(){
	float* ref[] = {ref_joints[7], ref_joints[9], ref_joints[11]};
	List* parts[] = {(human.parts)[13], (human.parts)[10], (human.parts)[11], (human.parts)[17]};
	float angx[] = {ang_x[6], ang_x[7], ang_x[10]}; float angy[] = {ang_y[6], ang_y[7], ang_y[10]}; float angz[] = {ang_z[6], ang_z[7], ang_z[10]};
	rotP1D(ref, parts, angx, angy, angz);
}

void hndlPE(){
	float* ref[] = {ref_joints[6], ref_joints[8], ref_joints[10]};
	List* parts[] = {(human.parts)[14], (human.parts)[9], (human.parts)[12], (human.parts)[16]};
	float angx[] = {ang_x[8], ang_x[9], ang_x[11]}; float angy[] = {ang_y[8], ang_y[9], ang_y[11]}; float angz[] = {ang_z[8], ang_z[9], ang_z[11]};
	rotP1D(ref, parts, angx, angy, angz);
}

void hndlT(){
	float* ref[] = {ref_joints[13]};
	List* parts[] = {(human.parts)[15]};
	float angx[] = {ang_x[13]}; float angy[] = {ang_y[13]}; float angz[] = {ang_z[13]};
	rotT(ref, parts, angx, angy, angz, hndlVD, hndlVE, hndlH);
}

void hndlH(){
	float* ref[] = {ref_joints[12]};
	List* parts[] = {(human.parts)[4]};
	float angx[] = {ang_x[12]}; float angy[] = {ang_y[12]}; float angz[] = {ang_z[12]};
	rotH(ref, parts, angx, angy, angz);
}
void hndlGlobal(){
	float* ref[] = {ref_joints[13]};
	float angx[] = {ang_x[14]}; float angy[] = {ang_y[14]}; float angz[] = {ang_z[14]};
	glPushMatrix();
		glTranslatef(ref[0][0],ref[0][1],ref[0][2]);
		glRotatef(angx[0], 1.0, 0.0, 0.0);
		glRotatef(angy[0], 0.0, 1.0, 0.0);
		glRotatef(angz[0], 0.0, 0.0, 1.0);		
		glTranslatef(-ref[0][0],-ref[0][1],-ref[0][2]);
		hndlT();
		hndlPD();
		hndlPE();
	glPopMatrix();
}
 // x: P1+, X: P1-, w: P2+, W: P2-, d: P3+, D: P3-
void choseLegs(){
	int sign_esq, sign_dir;
	if(walk_turn==1) {
		sign_dir=-1; sign_esq=1;
		firstLeg_idx[0] = 6; firstLeg_idx[1] = 7; firstLeg_idx[2] = 10;
		auxLeg_idx[0] = 8; auxLeg_idx[1] = 9; auxLeg_idx[2] = 11;
		
		walk_ang_x[0] = ang_x[6] + sign_esq*50.0; walk_ang_x[1] = ang_x[7] - 50.0; walk_ang_x[2] = ang_x[10] - 25.0;
		walk_ang_x[3] = ang_x[8] + sign_dir*50.0; walk_ang_x[4] = ang_x[9] - 50.0; walk_ang_x[5] = ang_x[11] - 25.0;
		walk_start_ang_x[0] = ang_x[6]; walk_start_ang_x[1] = ang_x[7]; walk_start_ang_x[2] = ang_x[10];
		walk_start_ang_x[3] = ang_x[8]; walk_start_ang_x[4] = ang_x[9]; walk_start_ang_x[5] = ang_x[11];
	}
	else{
		sign_esq=1; sign_dir=-1;
		firstLeg_idx[0] = 8; firstLeg_idx[1] = 9; firstLeg_idx[2] = 11;
		auxLeg_idx[0] = 6; auxLeg_idx[1] = 7; auxLeg_idx[2] = 10;
		
		walk_ang_x[0] = ang_x[8] + sign_esq*50.0; walk_ang_x[1] = ang_x[9] - 50.0; walk_ang_x[2] = ang_x[11] - 25.0;
		walk_ang_x[3] = ang_x[6] + sign_dir*50.0; walk_ang_x[4] = ang_x[7] - 50.0; walk_ang_x[5] = ang_x[10] - 25.0;
		walk_start_ang_x[0] = ang_x[8]; walk_start_ang_x[1] = ang_x[9]; walk_start_ang_x[2] = ang_x[11];
		walk_start_ang_x[3] = ang_x[6]; walk_start_ang_x[4] = ang_x[7]; walk_start_ang_x[5] = ang_x[10];		
	}
	//printf("walkturn %d\n", walk_turn);
	//printf("LEFTLEG: P1: %f->%f, P2: %f->%f\n", walk_start_ang_x[0], walk_ang_x[0], walk_start_ang_x[1], walk_ang_x[1]);
	//printf("RIGHTLEG: P1: %f->%f, P2: %f->%f\n", walk_start_ang_x[3], walk_ang_x[3], walk_start_ang_x[4], walk_ang_x[4]);
}
void backwardMotion(){
	int reach[6] = {0};
	if(ang_x[firstLeg_idx[0]]>walk_start_ang_x[0]){
		ang_x[firstLeg_idx[0]] -= delta_ang;
	} else {reach[0]=1;}
	if(ang_x[firstLeg_idx[1]]<walk_start_ang_x[1]){
		ang_x[firstLeg_idx[1]] += delta_ang;
	} else {reach[1]=1;}
	if(ang_x[firstLeg_idx[2]]<walk_start_ang_x[2]){
		ang_x[firstLeg_idx[2]] += delta_ang;
	} else {reach[2]=1;}
	/* -- */
	if(ang_x[auxLeg_idx[0]]<walk_start_ang_x[3]){
		ang_x[auxLeg_idx[0]] += delta_ang;
	} else {reach[3]=1;}
	if(ang_x[auxLeg_idx[1]]<walk_start_ang_x[4]){
		ang_x[auxLeg_idx[1]] += delta_ang;
	} else {reach[4]=1;}
	if(ang_x[auxLeg_idx[2]]<walk_start_ang_x[5]){
		ang_x[auxLeg_idx[2]] += delta_ang;
	} else {reach[5]=1;}
	//printf("LEFTLEG: P1: %f, P2: %f\n", ang_x[firstLeg_idx[0]], ang_x[firstLeg_idx[1]]);
	//printf("RIGHTLEG: P1: %f, P2: %f\n",ang_x[auxLeg_idx[0]], ang_x[auxLeg_idx[1]]);
	if (reach[0] && reach[1] && reach[3] && reach[4]){/*printf("reach backward\n");*/walk_state = 0; to_walk = 0; walk_turn = !walk_turn;}

}
void forwardMotion(){
	int reach[6] = {0};

	if(ang_x[firstLeg_idx[0]]<walk_ang_x[0]){
		ang_x[firstLeg_idx[0]] += delta_ang;
	} else {reach[0]=1;}
	if(ang_x[firstLeg_idx[1]]>walk_ang_x[1]){
		ang_x[firstLeg_idx[1]] -= delta_ang;
	} else {reach[1]=1;}
	if(ang_x[firstLeg_idx[2]]>walk_ang_x[2]){
		ang_x[firstLeg_idx[2]] -= delta_ang;
	} else {reach[2]=1;}
	/* -- */
	if(ang_x[auxLeg_idx[0]]>walk_ang_x[3]){
		ang_x[auxLeg_idx[0]] -= delta_ang;
	} else {reach[3]=1;}
	if(ang_x[auxLeg_idx[1]]>walk_ang_x[4]){
		ang_x[auxLeg_idx[1]] -= delta_ang;
	} else {reach[4]=1;}
	if(ang_x[auxLeg_idx[2]]>walk_ang_x[5]){
		ang_x[auxLeg_idx[2]] -= delta_ang;
	} else {reach[5]=1;}
	//printf("LEFTLEG: P1: %f, P2: %f\n", ang_x[firstLeg_idx[0]], ang_x[firstLeg_idx[1]]);
	//printf("RIGHTLEG: P1: %f, P2: %f\n",ang_x[auxLeg_idx[0]], ang_x[auxLeg_idx[1]]);
	if (reach[0] && reach[1] && reach[3] && reach[4]){walk_state = 1;/*printf("reach forward\n");*/}
}
/*
	FIRSTLEG->FORWARD(P1+,P2-), BACKWARD(P1-, P2+)
	AUXLEG->FORWARD(P1-,P2-), BACKWARD(P1+, P2+)

*/
void Walking(){
	if(to_walk){
		if (walk_state==0){forwardMotion();}
		else{backwardMotion();}
	}
}
void draw(List* obj){
	glBegin(GL_TRIANGLES);
		Node* fc_vtx = listGetittem(obj, 0);
		for(int i=1;i<obj->size/3;i++){
			for(int j=0;j<3;j++){
				glColor3f(0.5*sin(i), 0.33*j, 0.5*cos(i));
				glVertex3f((GLfloat) (*((float**)fc_vtx->points))[0], (GLfloat) (*((float**)fc_vtx->points))[1], (GLfloat) (*((float**)fc_vtx->points))[2]);
				fc_vtx = fc_vtx->prox;
			}
		}
	glEnd();
}
#endif