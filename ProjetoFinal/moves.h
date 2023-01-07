#include "human.h"
#ifndef MOVES_HEADER
#define MOVES_HEADER

void rotV1D(float* ref[], Human* h, float* angx, float* angy, float* angz);
void rotV2D(float* ref[], Human* h, float* angx, float* angy, float* angz);
void draw(List* obj);
void rotV1D(float* ref[], Human* h, float* angx, float* angy, float* angz){
	
	glPushMatrix();
		glTranslatef(ref[1][0],ref[1][1],ref[1][2]); // V1D
		glRotatef(angx[0], 1.0, 0.0, 0.0);
		glRotatef(angy[0], 0.0, 1.0, 0.0);
		glRotatef(angz[0], 0.0, 0.0, 1.0);
		glTranslatef(-ref[1][0],-ref[1][1],-ref[1][2]); // V1D
		draw(h->parts[2]); // BD
		rotV2D(ref, h, angx, angy, angz);
	glPopMatrix();
}

void rotV2D(float* ref[], Human* h, float* angx, float* angy, float* angz){
	glPushMatrix();
		glTranslatef(ref[3][0],ref[3][1],ref[3][2]);
		glRotatef(angx[1], 1.0, 0.0, 0.0);
		glRotatef(angy[1], 0.0, 1.0, 0.0);
		glRotatef(angz[1], 0.0, 0.0, 1.0);
		glTranslatef(-ref[3][0],-ref[3][1],-ref[3][2]); // V2D
		draw(h->parts[1]); // ABD
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