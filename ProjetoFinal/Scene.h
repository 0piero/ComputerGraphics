#ifndef Scene
double angle_x, angle_y, angle_z;
#define x_max 0.6
#define y_max 0.3
#define z_max 0.5


GLUquadricObj *quad; // Argumento necessario para funcoes glu

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
        if(!((angle_y > 180) && (angle_y < 360))){//draw left border
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

        glBegin(GL_QUADS);//desenha a porta
        glColor3f(0.7,0.4,0.2);
        glVertex3f(+x_max*0.0-x_max/2.0,+2.0*y_max/3.0,-z_max+0.01);
        glVertex3f(-x_max*1.0+x_max/6.0,+2.0*y_max/3.0,-z_max+0.01);
        glVertex3f(-x_max*1.0+x_max/6.0,-1.0*y_max/1.0,-z_max+0.01);
        glVertex3f(+x_max*0.0-x_max/2.0,-1.0*y_max/1.0,-z_max+0.01);
        glEnd();

        glPushMatrix();
            glTranslatef(-x_max/2.0-0.04,-y_max/4.0,-z_max+0.01);
            glColor3f(1.0,0.0,0.0);
            glutWireSphere(0.01,20,10);
        glPopMatrix();
    }
}

void draw_Objects(){
    draw_Door();
}

draw_Scene(double alpha, double beta, double gama){
    angle_x = alpha;
    angle_y = beta;
    angle_z = gama;

    draw_Borders();
    draw_Objects();
}

#endif
