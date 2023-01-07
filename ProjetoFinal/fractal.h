#ifndef fractal
#define fractal

void triangulos3(float points[3][2], int vezes_cada){
    if(vezes_cada == 0){
        glBegin(GL_TRIANGLES);
            glVertex3f(points[0][0],points[0][1],0.0);
            glVertex3f(points[1][0],points[1][1],0.0);
            glVertex3f(points[2][0],points[2][1],0.0);
        glEnd();
    }
    else{
        vezes_cada--;
        float points1[3][2] = {{(points[0][0]+points[2][0])/2.0,(points[0][1]+points[2][1])/2.0},
                               {(points[1][0]+points[2][0])/2.0,(points[1][1]+points[2][1])/2.0},
                               {points[2][0],points[2][1]}};
        float points2[3][2] = {{(points[0][0]+points[1][0])/2.0,(points[0][1]+points[1][1])/2.0},
                               {points[1][0],points[1][1]},
                               {(points[2][0]+points[1][0])/2.0,(points[2][1]+points[1][1])/2.0}};
        float points3[3][2] = {{points[0][0],points[0][1]},
                               {(points[1][0]+points[0][0])/2.0,(points[1][1]+points[0][1])/2.0},
                               {(points[2][0]+points[0][0])/2.0,(points[2][1]+points[0][1])/2.0}};
        triangulos3(points1,vezes_cada);
        triangulos3(points2,vezes_cada);
        triangulos3(points3,vezes_cada);
    }
}

#endif
