
#ifndef texture
#define texture
#include <stdio.h>
typedef struct BMPImagem
{
    int   width;
    int   height;
    char *data;
}BMPImage;

GLuint texture_id;

void getBitmapImageData( char *pFileName, BMPImage *pImage ){
    FILE *pFile = NULL;
    unsigned short nNumPlanes;
    unsigned short nNumBPP;
	int i;

    if( (pFile = fopen(pFileName, "rb") ) == NULL )
		printf("ERROR: getBitmapImageData - %s not found.\n", pFileName);

    // Seek forward to width and height info
    fseek( pFile, 18, SEEK_CUR );

    if( (i = fread(&pImage->width, 4, 1, pFile) ) != 1 )
		printf("ERROR: getBitmapImageData - Couldn't read width from %s.\n ", pFileName);

    if( (i = fread(&pImage->height, 4, 1, pFile) ) != 1 )
		printf("ERROR: getBitmapImageData - Couldn't read height from %s.\n ", pFileName);

    if( (fread(&nNumPlanes, 2, 1, pFile) ) != 1 )
		printf("ERROR: getBitmapImageData - Couldn't read plane count from %s.\n", pFileName);

    if( nNumPlanes != 1 )
		printf("ERROR: getBitmapImageData - Plane count from %s.\n ", pFileName);

    if( (i = fread(&nNumBPP, 2, 1, pFile)) != 1 )
		printf( "ERROR: getBitmapImageData - Couldn't read BPP from %s.\n ", pFileName);

    if( nNumBPP != 24 )
		printf("ERROR: getBitmapImageData - BPP from %s.\n ", pFileName);

    // Seek forward to image data
    fseek( pFile, 24, SEEK_CUR );

	// Calculate the image's total size in bytes. Note how we multiply the
	// result of (width * height) by 3. This is becuase a 24 bit color BMP
	// file will give you 3 bytes per pixel.
    int nTotalImagesize = (pImage->width * pImage->height) * 3;

    pImage->data = (char*) malloc( nTotalImagesize );

    if( (i = fread(pImage->data, nTotalImagesize, 1, pFile) ) != 1 )
		printf("ERROR: getBitmapImageData - Couldn't read image data from %s.\n ", pFileName);

    //
	// Finally, rearrange BGR to RGB
	//

	char charTemp;
    for( i = 0; i < nTotalImagesize; i += 3 )
	{
		charTemp = pImage->data[i];
		pImage->data[i] = pImage->data[i+2];
		pImage->data[i+2] = charTemp;
    }
}


/*Fun��o para Carregar uma imagem .BMP */
void CarregaTextura(char* Filename)
{

    BMPImage textura;

    glBindTexture(GL_TEXTURE_2D,texture_id);
    getBitmapImageData( Filename, &textura);

    // Define os par�metros da textura
    glBindTexture ( GL_TEXTURE_2D, texture_id);

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST  );

    // Give the image to OpenGL
    // Define uma textura bidimensional
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textura.width, textura.height, 0, GL_RGB, GL_UNSIGNED_BYTE, textura.data);
    glEnable(GL_TEXTURE_2D);
}


/* **********************************************************************
  void init(void)
		Inicializa os par�metros globais de OpenGL

 ********************************************************************** */
void init(void) {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);			/* Black Background */
	glEnable(GL_DEPTH_TEST);
         glGenTextures(1,&texture_id);

}

/* **********************************************************************
  void reshape( int w, int h )
		trata o redimensionamento da janela OpenGL

 ********************************************************************** */

#endif
