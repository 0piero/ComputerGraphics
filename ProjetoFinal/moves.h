#include "human.h"
#ifndef MOVES_HEADER
#define MOVES_HEADER

void rotV1D(float* ref[], List** parts, float* angx, float* angy, float* angz);
void rotV2D(float* ref[], List** parts, float* angx, float* angy, float* angz);
void rotV3D(float* ref[], List** parts, float* angx, float* angy, float* angz);
void rotT(float* ref[], List** parts, float* angx, float* angy, float* angz, void (*h_vd)(), void (*h_ve)(), void (*h_t)());
void hndlVD(); void hndlVE(); void hndlPE(); void hndlPD(); void hndlT(); void hndlH(); void hndlGlobal();
void draw(List* obj);
/* ang_()V1D, ang_()V2D, ang_()V1E, ang_()V2E, ang_()V3D, ang_()V3E, ang_()P1D, ang_()P2D, ang_()P1E, ang_()P2E, ang_()P3D, ang_()P3E, ang_()C, ang_()T, ang_()Global */
float ang_x[] = {0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0, 0.0, 0.0}; 
float ang_y[] = {0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0, 0.0, 0.0};
float ang_z[] = {0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0, 0.0, 0.0};
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
/*
void rotGlobal(){
	hndlT();
	hndlPD();
	hndlPE();
	hndlH();
}*/
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