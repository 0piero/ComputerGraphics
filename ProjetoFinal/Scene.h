#ifndef Scene
#define Scene

double angle_x, angle_y, angle_z;
#define x_max 0.6
#define y_max 0.3
#define z_max 0.5

double wall_vertices[8][8] = {
                            {+x_max,+y_max,-z_max},//0
                            {+x_max,-y_max,-z_max},//1
                            {+x_max,-y_max,+z_max},//2
                            {+x_max,+y_max,+z_max},//3
                            {-x_max,+y_max,-z_max},//4
                            {-x_max,-y_max,-z_max},//5
                            {-x_max,-y_max,+z_max},//6
                            {-x_max,+y_max,+z_max},//7

};

int wall_faces[5][4] = {
                    {0,1,2,3},//right
                    {4,5,6,7},//left
                    {2,3,7,6},//back
                    {1,2,6,5},//floor
                    {0,1,5,4},//front
};

void draw_Borders(){
    glColor3f(0.0,1.0,1.0);
    int i;
    glBegin(GL_QUADS);
        i = 0;
        if(!((angle_y > 0) && (angle_y < 180))){//draw right border
            glVertex3f(wall_vertices[wall_faces[i][0]][0],wall_vertices[wall_faces[i][0]][1],wall_vertices[wall_faces[i][0]][2]);
            glVertex3f(wall_vertices[wall_faces[i][1]][0],wall_vertices[wall_faces[i][1]][1],wall_vertices[wall_faces[i][1]][2]);
            glVertex3f(wall_vertices[wall_faces[i][2]][0],wall_vertices[wall_faces[i][2]][1],wall_vertices[wall_faces[i][2]][2]);
            glVertex3f(wall_vertices[wall_faces[i][3]][0],wall_vertices[wall_faces[i][3]][1],wall_vertices[wall_faces[i][3]][2]);
        }
        i = 1;
        if(!((angle_y > 180) && (angle_y < 360) || (angle_y < 0))){//draw left border
            glVertex3f(wall_vertices[wall_faces[i][0]][0],wall_vertices[wall_faces[i][0]][1],wall_vertices[wall_faces[i][0]][2]);
            glVertex3f(wall_vertices[wall_faces[i][1]][0],wall_vertices[wall_faces[i][1]][1],wall_vertices[wall_faces[i][1]][2]);
            glVertex3f(wall_vertices[wall_faces[i][2]][0],wall_vertices[wall_faces[i][2]][1],wall_vertices[wall_faces[i][2]][2]);
            glVertex3f(wall_vertices[wall_faces[i][3]][0],wall_vertices[wall_faces[i][3]][1],wall_vertices[wall_faces[i][3]][2]);
        }
        glColor3f(0.0,0.0,1.0);
        i = 2;
        if(!((angle_y > 90) && (angle_y < 270))){//draw back border
            glVertex3f(wall_vertices[wall_faces[i][0]][0],wall_vertices[wall_faces[i][0]][1],wall_vertices[wall_faces[i][0]][2]);
            glVertex3f(wall_vertices[wall_faces[i][1]][0],wall_vertices[wall_faces[i][1]][1],wall_vertices[wall_faces[i][1]][2]);
            glVertex3f(wall_vertices[wall_faces[i][2]][0],wall_vertices[wall_faces[i][2]][1],wall_vertices[wall_faces[i][2]][2]);
            glVertex3f(wall_vertices[wall_faces[i][3]][0],wall_vertices[wall_faces[i][3]][1],wall_vertices[wall_faces[i][3]][2]);
        }
        i = 3;
            glColor3f(1.0,1.0,0.0);//draw floor border
            glVertex3f(wall_vertices[wall_faces[i][0]][0],wall_vertices[wall_faces[i][0]][1],wall_vertices[wall_faces[i][0]][2]);
            glVertex3f(wall_vertices[wall_faces[i][1]][0],wall_vertices[wall_faces[i][1]][1],wall_vertices[wall_faces[i][1]][2]);
            glVertex3f(wall_vertices[wall_faces[i][2]][0],wall_vertices[wall_faces[i][2]][1],wall_vertices[wall_faces[i][2]][2]);
            glVertex3f(wall_vertices[wall_faces[i][3]][0],wall_vertices[wall_faces[i][3]][1],wall_vertices[wall_faces[i][3]][2]);

        i = 4;
        glColor3f(0.0,0.0,1.0);
        if(!((angle_y > 270) || (angle_y < 90))){//draw front border
            glVertex3f(wall_vertices[wall_faces[i][0]][0],wall_vertices[wall_faces[i][0]][1],wall_vertices[wall_faces[i][0]][2]);
            glVertex3f(wall_vertices[wall_faces[i][1]][0],wall_vertices[wall_faces[i][1]][1],wall_vertices[wall_faces[i][1]][2]);
            glVertex3f(wall_vertices[wall_faces[i][2]][0],wall_vertices[wall_faces[i][2]][1],wall_vertices[wall_faces[i][2]][2]);
            glVertex3f(wall_vertices[wall_faces[i][3]][0],wall_vertices[wall_faces[i][3]][1],wall_vertices[wall_faces[i][3]][2]);
        }
    glEnd();
    /*glColor3f(0.0,1.0,0.0);
    glutWireCube(0.4);*/
}

void draw_Door(){
    if(!((angle_y > 270) || (angle_y < 90))){//draw door, in front border

        glBegin(GL_QUADS);//draw the door
        glColor3f(0.7,0.4,0.2);
        glVertex3f(+x_max*0.0-x_max/2.0,+2.0*y_max/3.0,-z_max+0.01);
        glVertex3f(-x_max*1.0+x_max/6.0,+2.0*y_max/3.0,-z_max+0.01);
        glVertex3f(-x_max*1.0+x_max/6.0,-1.0*y_max/1.0,-z_max+0.01);
        glVertex3f(+x_max*0.0-x_max/2.0,-1.0*y_max/1.0,-z_max+0.01);
        glEnd();

        glPushMatrix();//draw_handle_door
            glTranslatef(-x_max/2.0-0.04,-y_max/4.0,-z_max+0.01);
            glColor3f(1.0,0.0,0.0);
            glutSolidSphere(0.01,20,10);
        glPopMatrix();
    }
}

void make_Window(){
    glPushMatrix();//draw the background of the window
                    glScalef(0.0,1.0/3.0,1.0/3.0);
                    glColor3f(0.0,0.0,0.0);
                    glBegin(GL_QUADS);
                        glVertex3f(+x_max,+y_max,+z_max);
                        glVertex3f(+x_max,-y_max,+z_max);
                        glVertex3f(+x_max,-y_max,-z_max);
                        glVertex3f(+x_max,+y_max,-z_max);
                    glEnd();
                glPopMatrix();

                glPushMatrix();//draw the internal divisions
                    glTranslatef(-0.0005,0.0,0.0);
                    glPushMatrix();
                        glRotatef(90.0,1.0,0.0,0.0);
                        glScalef(0.0,1.0/30.0,1.0/5.0);
                        glColor3f(0.7,0.4,0.2);
                        glBegin(GL_QUADS);
                            glVertex3f(+x_max,+y_max,+z_max);
                            glVertex3f(+x_max,-y_max,+z_max);
                            glVertex3f(+x_max,-y_max,-z_max);
                            glVertex3f(+x_max,+y_max,-z_max);
                        glEnd();
                    glPopMatrix();

                    glPushMatrix();
                        glScalef(0.0,1.0/30.0,1.0/3.0);
                        glColor3f(0.7,0.4,0.2);
                        glBegin(GL_QUADS);
                            glVertex3f(+x_max,+y_max,+z_max);
                            glVertex3f(+x_max,-y_max,+z_max);
                            glVertex3f(+x_max,-y_max,-z_max);
                            glVertex3f(+x_max,+y_max,-z_max);
                        glEnd();
                    glPopMatrix();
                glPopMatrix();


                glPushMatrix();//draw the external divisions

                    glTranslatef(-0.0005,0.0,0.0);//draw the left division
                    glPushMatrix();
                        glScalef(1.0,0.7,1.0);
                        glTranslatef(0.0,0.0,y_max/1.8);
                        glRotatef(90,1.0,0.0,0.0);
                        glScalef(0.0,1.0/30.0,1.0/3.0);
                        glColor3f(0.7,0.4,0.2);
                        glBegin(GL_QUADS);
                            glVertex3f(+x_max,+y_max,+z_max);
                            glVertex3f(+x_max,-y_max,+z_max);
                            glVertex3f(+x_max,-y_max,-z_max);
                            glVertex3f(+x_max,+y_max,-z_max);
                        glEnd();
                    glPopMatrix();

                    glTranslatef(-0.0005,0.0,0.0);//draw the right division
                    glPushMatrix();
                        glScalef(1.0,0.7,1.0);
                        glTranslatef(0.0,0.0,-y_max/1.8);
                        glRotatef(90,1.0,0.0,0.0);
                        glScalef(0.0,1.0/30.0,1.0/3.0);
                        glColor3f(0.7,0.4,0.2);
                        glBegin(GL_QUADS);
                            glVertex3f(+x_max,+y_max,+z_max);
                            glVertex3f(+x_max,-y_max,+z_max);
                            glVertex3f(+x_max,-y_max,-z_max);
                            glVertex3f(+x_max,+y_max,-z_max);
                        glEnd();
                    glPopMatrix();

                    glTranslatef(-0.0005,0.0,0.0);//draw the above division
                    glPushMatrix();
                        glTranslatef(0.0,y_max/2.8,0.0);
                        glScalef(0.0,1.0/30.0,1.0/3.0);
                        glColor3f(0.7,0.4,0.2);
                        glBegin(GL_QUADS);
                            glVertex3f(+x_max,+y_max,+z_max);
                            glVertex3f(+x_max,-y_max,+z_max);
                            glVertex3f(+x_max,-y_max,-z_max);
                            glVertex3f(+x_max,+y_max,-z_max);
                        glEnd();
                    glPopMatrix();

                    glTranslatef(-0.0005,0.0,0.0);//draw the below division
                    glPushMatrix();
                        glTranslatef(0.0,-y_max/2.8,0.0);
                        glScalef(0.0,1.0/30.0,1.0/3.0);
                        glColor3f(0.7,0.4,0.2);
                        glBegin(GL_QUADS);
                            glVertex3f(+x_max,+y_max,+z_max);
                            glVertex3f(+x_max,-y_max,+z_max);
                            glVertex3f(+x_max,-y_max,-z_max);
                            glVertex3f(+x_max,+y_max,-z_max);
                        glEnd();
                    glPopMatrix();


                glPopMatrix();
}

void draw_Window(){
        if(!((angle_y > 0) && (angle_y < 180))){//draw window in the right border
            glPushMatrix();
                glTranslatef(+x_max-0.01,0.0,0.0);
                make_Window();
            glPopMatrix();
    }

}

void draw_Stretcher(){
    glPushMatrix();

        glPushMatrix();//draw the stretcher
            glColor3f(0.0,0.0,0.0);
            glTranslatef(0.0,-y_max/2.0,z_max-0.101);
            glScalef(4.0, 0.6, 2.0);
            glutSolidCube(0.1);
        glPopMatrix();

        glPushMatrix();//draw the pillow
            glColor3f(0.8,0.0,0.0);
            glTranslatef(0.16,-0.11,z_max-0.1);
            glScalef(0.8, 0.3, 1.8);
            glutSolidCube(0.1);
        glPopMatrix();

        glTranslatef(0.0,0.001,-0.001);
        glPushMatrix();//draw the first support of the stretcher
            glColor3f(0.0,1.0,0.0);
            glTranslatef(0.17,-0.24,z_max-0.02);
            glScalef(0.5,1.2,0.4);
            glutSolidCube(0.1);
        glPopMatrix();

        glPushMatrix();//draw the second support of the stretcher
            glColor3f(0.0,1.0,0.0);
            glTranslatef(-0.17,-0.24,z_max-0.02);
            glScalef(0.5,1.2,0.4);
            glutSolidCube(0.1);
        glPopMatrix();

        glPushMatrix();//draw the third support of the stretcher
            glColor3f(0.0,1.0,0.0);
            glTranslatef(+0.17,-0.24,z_max-0.18);
            glScalef(0.5,1.2,0.4);
            glutSolidCube(0.1);
        glPopMatrix();

        glPushMatrix();//draw the forth support of the stretcher
            glColor3f(0.0,1.0,0.0);
            glTranslatef(-0.17,-0.24,z_max-0.18);
            glScalef(0.5,1.2,0.4);
            glutSolidCube(0.1);
        glPopMatrix();
    glPopMatrix();
}

void draw_Ball(){
    glColor3f(0.2,0.5,0.6);

    glTranslatef(-x_max+0.2,-y_max+0.101,z_max-0.101);
    glutSolidSphere(0.1,20,10);
}


void draw_Objects(){
    draw_Door();
    draw_Window();
    draw_Stretcher();
    draw_Ball();
}

draw_Scene(double alpha, double beta, double gama){
    angle_x = alpha;
    angle_y = beta;
    angle_z = gama;

    draw_Borders();
    draw_Objects();
}

#endif
