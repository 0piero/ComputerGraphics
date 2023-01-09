#ifndef texture
#define texture
#include <stdio.h>
typedef struct BMPImagem
{
    int   width;
    int   height;
    char *data;
}BMP;

GLuint texture_id[2];

void getBitmapImageData( char *fileName, BMP *Image ){
    FILE *image = NULL;
    unsigned short numPlanes;
    unsigned short numBPR;
	int a;

    if((image = fopen(fileName, "rb")) == NULL){
		printf("ERROR: getBitmapImageData - %s not found.\n",fileName);
    }
    // Seek forward to width and height info
    fseek(image,18,SEEK_CUR);

    if((a = fread(&Image->width,4,1,image)) != 1){
		printf("ERROR: getBitmapImageData - Couldn't read width from %s.\n",fileName);
    }

    if((a = fread(&Image->height,4,1,image)) != 1){
		printf("ERROR: getBitmapImageData - Couldn't read height from %s.\n",fileName);
    }

    if((fread(&numPlanes,2,1,image)) != 1){
		printf("ERROR: getBitmapImageData - Couldn't read plane count from %s.\n",fileName);
    }

    if(numPlanes != 1){
		printf("ERROR: getBitmapImageData - Plane count from %s.\n",fileName);
    }

    if((a = fread(&numBPR,2,1,image)) != 1){
		printf("ERROR: getBitmapImageData - Couldn't read BPP from %s.\n",fileName);
    }

    if(numBPR != 24){
		printf("ERROR: getBitmapImageData - BPP from %s.\n ",fileName);
    }
    // Seek forward to image data
    fseek(image,24,SEEK_CUR);
	// Calculate the image's total size in bytes. Note how we multiply the
	// result of (width * height) by 3. This is becuase a 24 bit color BMP
	// file will give you 3 bytes per pixel.
    int nTotalImagesize = (Image->width*Image->height)*3;

    Image->data = (char*) malloc(nTotalImagesize);

    if((a = fread(Image->data,nTotalImagesize,1,image)) != 1)
		printf("ERROR: getBitmapImageData - Couldn't read image data from %s.\n",fileName);
	// Finally, rearrange BGR to RGB
	char charTemp;
    for(a = 0; a < nTotalImagesize;a += 3){
		charTemp = Image->data[a];
		Image->data[a] = Image->data[a+2];
		Image->data[a+2] = charTemp;
    }
}


/*Função para Carregar uma imagem .BMP */
void chargeTextura(char* Filename, int current_texture){

    BMP c_texture;

    glBindTexture(GL_TEXTURE_2D,texture_id[current_texture]);

    getBitmapImageData( Filename, &c_texture);

    // Define os parâmetros da textura
    glBindTexture(GL_TEXTURE_2D,texture_id[current_texture]);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    // Give the image to OpenGL
    // Define uma textura bidimensional
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, c_texture.width, c_texture.height, 0, GL_RGB, GL_UNSIGNED_BYTE, c_texture.data);
    glEnable(GL_TEXTURE_2D);
}


/* **********************************************************************
  void init(void)
		Inicializa os par‚metros globais de OpenGL
 ********************************************************************** */
void init_texture(int textures) {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);			/* Black Background */
	glEnable(GL_DEPTH_TEST);
         glGenTextures(1,&texture_id[textures]);

}
#endif
