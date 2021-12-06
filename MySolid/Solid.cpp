
#include <cstdio>
#define _CRT_SECURE_NO_DEPRECATE
using namespace std;

int WinWidth=640;
int WinHeight=640;	

GLfloat  rx=0;			
GLfloat  ry=0;			
GLfloat  tx=0;			
GLfloat	 ty=0;		
GLfloat	 tz=0;		
GLint	 tt=0;			
GLint spin1 = 0;    
GLint spin2 = 0;    
GLint spin11 = 0;
GLint spin12 = 0;
//GLfloat light0_position[] = { 0.0, 0.0, 2.5, 1.0 }; 

int mx,my;				
bool ldown=false;		
bool rdown=false;	
GLuint texture1;

GLuint list=0;

//static GLfloat Mambient[] = { 0.2, 0.2, 0.2, 1.0 };
//static GLfloat Mdiffuse[] = { 1.0, 1.0, 1.0, 1.0 };
//static GLfloat Mspecular[] = { 1.0, 1.0, 1.0, 1.0 };
//static GLint Mshininess[] = { 30 };

GLfloat light0_position[] = { -3.0, 2.5, 0.0, 1.0 };
GLfloat light1_position[] = { 3.0, 2.5, 0.0, 1.0 };
GLfloat light1_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
GLfloat mat_specular[] = { 0.774597f, 0.458561f, 0.200621f, 1.0f };
GLfloat diffuseMaterial[4] = { 0.4f, 0.2368f, 0.1036f, 1.0f };
GLfloat mat_ambient[] = { 0.25f, 0.148f, 0.06475f, 1.0f };
GLfloat mat_shine[] = { 76.8f };
GLfloat light1_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat light1_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLuint LoadTexture(const char* filename)
{

	GLuint texture;

	int width, height;

	unsigned char* data;

	FILE* file;

	file = fopen(filename, "rb");

	if (file == NULL) return 0;
	width = 64;
	height = 64;
	data = (unsigned char*)malloc(width * height * 3);
	//int size = fseek(file,);
	fread(data, width * height * 3, 1, file);
	fclose(file);

	for (int i = 0; i < width * height; ++i)
	{
		int index = i * 3;
		unsigned char B, R;
		B = data[index];
		R = data[index + 2];

		data[index] = R;
		data[index + 2] = B;

	}


	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);


	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);
	free(data);


	return texture;
}

void Init()				
{/*
	texture1 = LoadTexture("MyPhoto.bmp");
	glEnable(GL_TEXTURE_2D);*/
	static GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	static GLfloat diffuse[] = { 1.0, 1.0, 0.8, 1.0 };
	
	//	static GLfloat diffuse[] = {0.0, 0.0, 0.0, 1.0}; 
	static GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
	//	static GLfloat specular[] = {0.0, 0.0, 0.0, 1.0}; 
	// static GLfloat specular[] = {0.0, 0.0, 0.0, 1.0}; 

  /* static GLfloat positn1[] = {10.0, 0.0, 0.0, 1.0}; 
   static GLfloat direct1[] = {-1.0, 0.0, 0.0}; */

	/* static GLfloat positn1[] = {0.0, 10.0, 0.0, 1.0}; 
	 static GLfloat direct1[] = {0.0, -1.0, 0.0}; */

	static GLfloat positn1[] = { 0.0, 0.0, 10.0, 1.0 };
	static GLfloat direct1[] = { 0.0, 0.0, -1.0 };

	static GLfloat mas[] = { 1.0, 1.0, 1.0, 1.0 };

	glLightfv(GL_LIGHT0, GL_POSITION, positn1);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, direct1);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLighti(GL_LIGHT0, GL_SPOT_CUTOFF, 80);
	glLighti(GL_LIGHT0, GL_SPOT_EXPONENT, 0);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, mas);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	//
	//glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);
	//glEnable(GL_LIGHT1);

	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glClearDepth(1.0f);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_LINE_SMOOTH);
	//glClearColor(0.9, 0.9, 0.6, 1);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	
}

void MySolid()
{


	
	/*glColor3f(1.0, 1.0, 1.0);*/
	glColor3f(0.8, 0.5, 0.2);
	glNormal3f(-4, 0, 0);
	glBegin(GL_QUADS);
	/*glTexCoord2f(0.0, 0.0); */glVertex3f(0.0, 0.0, 0.0);
	/*glTexCoord2f(1.0, 0.0);*/glVertex3f(0.0, 0.0, 2.0);
/*	glTexCoord2f(1.0, 1.0);*/glVertex3f(0.0, 2.0, 2.0);
/*	glTexCoord2f(0.0, 1.0);*/glVertex3f(0.0, 2.0, 0.0);
	glEnd();

	//glColor3f(0.8, 0.5, 0.2);

	glBegin(GL_QUADS);
	glNormal3f(0, 0, -2);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 2.0, 0.0);
	glVertex3f(1.0, 2.0, 0.0);
	glVertex3f(1.0, 0.0, 0.0);
	glEnd();

	//glColor3f(0.2, 0.3, 0.28);
	glBegin(GL_QUADS);
	glNormal3f(0, 0, 2);
	glVertex3f(0.0, 0.0, 2.0);
	glVertex3f(1.0, 0.0, 2.0);
	glVertex3f(1.0, 2.0, 2.0);
	glVertex3f(0.0, 2.0, 2.0);
	glEnd();
	/////3

	//glColor3f(1.0, 0.33, 0.98);
	//glBegin(GL_QUADS);
	//glNormal3f(0, -2, 0);
	//glVertex3f(0.0, 0.0, 0.0);
	//glVertex3f(1.0, 0.0, 0.0);
	//glVertex3f(1.0, 0.0, 2.0);
	//glVertex3f(0.0, 0.0, 2.0);
	//glEnd();
	///4
	//glColor3f(0.76, 0.45, 0.38);
	glBegin(GL_QUADS);
	glNormal3f(0, 2, 0);
	glVertex3f(0.0, 2.0, 0.0);
	glVertex3f(0.0, 2.0, 2.0);
	glVertex3f(1.0, 2.0, 2.0);
	glVertex3f(1.0, 2.0, 0.0);
	glEnd();
	//5

	//6
	//glColor3f(0.71, 0.33, 0.58);
	glBegin(GL_QUADS);
	glNormal3f(1.5, 0, 0);
	glVertex3f(1.0, 0.0, 0.0);
	glVertex3f(1.0, 2.0, 0.0);
	glVertex3f(1.0, 2.0, 0.75);
	glVertex3f(1.0, 0.0, 0.75);
	glEnd();

	//7
	//glColor3f(0.71, 0.33, 0.58);
	glBegin(GL_QUADS);
	glNormal3f(1.5, 0, 0);
	glVertex3f(1.0, 0.0, 1.25);
	glVertex3f(1.0, 2.0, 1.25);
	glVertex3f(1.0, 2.0, 2.0);
	glVertex3f(1.0, 0.0, 2.0);

	glEnd();

	//18
	/*glColor3f(0.71, 0.33, 0.58);*/
	glBegin(GL_QUADS);
	glNormal3f(0.75, 0, 0);
	glVertex3f(1.0, 2.0, 1.25);
	glVertex3f(1.0, 0.5, 1.25);
	glVertex3f(1.0, 0.5, 0.75);
	glVertex3f(1.0, 2.0, 0.75);
	glEnd();
	//8
	//glColor3f(0.24, 0.81, 0.68);
	glBegin(GL_QUADS);
	glNormal3f(0, 0, -3);
	glVertex3f(-1.0, -1.0, 0.0);
	glVertex3f(-1.0, 0.0, 0.0);
	glVertex3f(2.0, 0.0, 0.0);
	glVertex3f(2.0, -1.0, 0.0);
	glEnd();
	//9
	//glColor3f(0.59, 0.31, 0.18);
	glBegin(GL_QUADS);
	glNormal3f(0, 2, 0);
	glVertex3f(2.0, 0.0, 0.0);
	glVertex3f(1.0, 0.0, 0.0);
	glVertex3f(1.0, 0.0, 2.0);
	glVertex3f(2.0, 0.0, 2.0);
	glEnd();
	//10
	//glColor3f(0.78, 0.23, 0.98);
	glBegin(GL_QUADS);
	glNormal3f(0, 2, 0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(-1.0, 0.0, 0.0);
	glVertex3f(-1.0, 0.0, 2.0);
	glVertex3f(0.0, 0.0, 2.0);
	glEnd();


	//11
	//glColor3f(0.37, 0.3, 0.28);
	glBegin(GL_QUADS);
	glNormal3f(-2, 0, 0);
	glVertex3f(-1.0, 0.0, 0.0);
	glVertex3f(-1.0, -1.0, 0.0);
	glVertex3f(-1.0, -1.0, 2.0);
	glVertex3f(-1.0, 0.0, 2.0);
	glEnd();

	//12
	//glColor3f(0.11, 0.33, 0.88);
	glBegin(GL_QUADS);
	glNormal3f(0, 0, 3);
	glVertex3f(-1.0, 0.0, 2.0);
	glVertex3f(-1.0, -1.0, 2.0);
	glVertex3f(2.0, -1.0, 2.0);
	glVertex3f(2.0, 0.0, 2.0);
	glEnd();
	////13
	//glColor3f(0.77, 0.53, 0.18);
	glBegin(GL_QUADS);
	glNormal3f(2, 0, 0);
	glVertex3f(2.0, 0.0, 2.0);
	glVertex3f(2.0, -1.0, 2.0);
	glVertex3f(2.0, -1.0, 0.0);
	glVertex3f(2.0, 0.0, 0.0);
	glEnd();

	////14
	//glColor3f(0.42, 0.13, 0.98);
	glBegin(GL_QUADS);
	glNormal3f(0, -6, 0);
	glVertex3f(-1.0, -1.0, 2.0);
	glVertex3f(-1.0, -1.0, 0.0);
	glVertex3f(2.0, -1.0, 0.0);
	glVertex3f(2.0, -1.0, 2.0);
	glEnd();


	////15
	//glColor3f(0.37, 0.13, 0.68);
	glBegin(GL_QUADS);
	glNormal3f(0, 0, -0.25);
	glVertex3f(0.5, 0.0, 1.25);
	glVertex3f(0.5, 0.5, 1.25);
	glVertex3f(1.0, 0.5, 1.25);
	glVertex3f(1.0, 0.0, 1.25);
	glEnd();

	//16
	//glColor3f(1.0, 1.0, 0.28);
	glBegin(GL_QUADS);
	glNormal3f(0, 0, 0.25);
	glVertex3f(0.5, 0.5, 0.75);
	glVertex3f(0.5, 0.0, 0.75);
	glVertex3f(1.0, 0.0, 0.75);
	glVertex3f(1.0, 0.5, 0.75);

	glEnd();

	////17
	//glColor3f(0.75, 0.55, 0.15);
	glBegin(GL_QUADS);
	glNormal3f(0, -0.25, 0);
	glVertex3f(1.0, 0.5, 1.25);
	glVertex3f(0.5, 0.5, 1.25);
	glVertex3f(0.5, 0.5, 0.75);
	glVertex3f(1.0, 0.5, 0.75);
	glEnd();

	//glColor3f(0.8, 0.5, 0.2);
	//glBegin(GL_QUADS);
	//glNormal3f(0, 0, -2);
	//glVertex3f(0.0, 0.0, 0.0);
	//glVertex3f(0.0, 2.0, 0.0);
	//glVertex3f(1.0, 2.0, 0.0);
	//glVertex3f(1.0, 0.0, 0.0);
	//glEnd();


	//glBegin(GL_QUADS);
	//glNormal3f(0, 0, 2);
	//glVertex3f(0.0, 0.0, 2.0);
	//glVertex3f(1.0, 0.0, 2.0);
	//glVertex3f(1.0, 2.0, 2.0);
	//glVertex3f(0.0, 2.0, 2.0);
	//glEnd();
	///////3

	////glColor3f(1.0, 0.33, 0.98);
	////glBegin(GL_QUADS);
	////glNormal3f(0, -2, 0);
	////glVertex3f(0.0, 0.0, 0.0);
	////glVertex3f(1.0, 0.0, 0.0);
	////glVertex3f(1.0, 0.0, 2.0);
	////glVertex3f(0.0, 0.0, 2.0);
	////glEnd();
	/////4

	//glBegin(GL_QUADS);
	//glNormal3f(0, 2, 0);
	//glVertex3f(0.0, 2.0, 0.0);
	//glVertex3f(0.0, 2.0, 2.0);
	//glVertex3f(1.0, 2.0, 2.0);
	//glVertex3f(1.0, 2.0, 0.0);
	//glEnd();
	////5

	//glBegin(GL_QUADS);
	//glNormal3f(-4, 0, 0);
	//glVertex3f(0.0, 0.0, 0.0);
	//glVertex3f(0.0, 0.0, 2.0);
	//glVertex3f(0.0, 2.0, 2.0);
	//glVertex3f(0.0, 2.0, 0.0);
	//glEnd();
	////6

	//glBegin(GL_QUADS);
	//glNormal3f(1.5, 0, 0);
	//glVertex3f(1.0, 0.0, 0.0);
	//glVertex3f(1.0, 2.0, 0.0);
	//glVertex3f(1.0, 2.0, 0.75);
	//glVertex3f(1.0, 0.0, 0.75);
	//glEnd();

	////7

	//glBegin(GL_QUADS);
	//glNormal3f(1.5, 0, 0);
	//glVertex3f(1.0, 0.0, 1.25);
	//glVertex3f(1.0, 2.0, 1.25);
	//glVertex3f(1.0, 2.0, 2.0);
	//glVertex3f(1.0, 0.0, 2.0);

	//glEnd();

	////18
	//
	//glBegin(GL_QUADS);
	//glNormal3f(0.75, 0, 0);
	//glVertex3f(1.0, 2.0, 1.25);
	//glVertex3f(1.0, 0.5, 1.25);
	//glVertex3f(1.0, 0.5, 0.75);
	//glVertex3f(1.0, 2.0, 0.75);
	//glEnd();
	////8

	//glBegin(GL_QUADS);
	//glNormal3f(0, 0, -3);
	//glVertex3f(-1.0, -1.0, 0.0);
	//glVertex3f(-1.0, 0.0, 0.0);
	//glVertex3f(2.0, 0.0, 0.0);
	//glVertex3f(2.0, -1.0, 0.0);
	//glEnd();
	////9

	//glBegin(GL_QUADS);
	//glNormal3f(0, 2, 0);
	//glVertex3f(2.0, 0.0, 0.0);
	//glVertex3f(1.0, 0.0, 0.0);
	//glVertex3f(1.0, 0.0, 2.0);
	//glVertex3f(2.0, 0.0, 2.0);
	//glEnd();
	////10
	//
	//glBegin(GL_QUADS);
	//glNormal3f(0, 2, 0);
	//glVertex3f(0.0, 0.0, 0.0);
	//glVertex3f(-1.0, 0.0, 0.0);
	//glVertex3f(-1.0, 0.0, 2.0);
	//glVertex3f(0.0, 0.0, 2.0);
	//glEnd();


	////11

	//glBegin(GL_QUADS);
	//glNormal3f(-2, 0, 0);
	//glVertex3f(-1.0, 0.0, 0.0);
	//glVertex3f(-1.0, -1.0, 0.0);
	//glVertex3f(-1.0, -1.0, 2.0);
	//glVertex3f(-1.0, 0.0, 2.0);
	//glEnd();

	////12

	//glBegin(GL_QUADS);
	//glNormal3f(0, 0, 3);
	//glVertex3f(-1.0, 0.0, 2.0);
	//glVertex3f(-1.0, -1.0, 2.0);
	//glVertex3f(2.0, -1.0, 2.0);
	//glVertex3f(2.0, 0.0, 2.0);
	//glEnd();
	////13
	//
	//glBegin(GL_QUADS);
	//glNormal3f(2, 0, 0);
	//glVertex3f(2.0, 0.0, 2.0);
	//glVertex3f(2.0, -1.0, 2.0);
	//glVertex3f(2.0, -1.0, 0.0);
	//glVertex3f(2.0, 0.0, 0.0);
	//glEnd();

	////14

	//glBegin(GL_QUADS);
	//glNormal3f(0, -6, 0);
	//glVertex3f(-1.0, -1.0, 2.0);
	//glVertex3f(-1.0, -1.0, 0.0);
	//glVertex3f(2.0, -1.0, 0.0);
	//glVertex3f(2.0, -1.0, 2.0);
	//glEnd();


	////15

	//glBegin(GL_QUADS);
	//glNormal3f(0, 0, -0.25);
	//glVertex3f(0.5, 0.0, 1.25);
	//glVertex3f(0.5, 0.5, 1.25);
	//glVertex3f(1.0, 0.5, 1.25);
	//glVertex3f(1.0, 0.0, 1.25);
	//glEnd();

	////16

	//glBegin(GL_QUADS);
	//glNormal3f(0, 0, 0.25);
	//glVertex3f(0.5, 0.5, 0.75);
	//glVertex3f(0.5, 0.0, 0.75);
	//glVertex3f(1.0, 0.0, 0.75);
	//glVertex3f(1.0, 0.5, 0.75);

	//glEnd();

	////17

	//glBegin(GL_QUADS);
	//glNormal3f(0, -0.25, 0);
	//glVertex3f(1.0, 0.5, 1.25);
	//glVertex3f(0.5, 0.5, 1.25);
	//glVertex3f(0.5, 0.5, 0.75);
	//glVertex3f(1.0, 0.5, 0.75);
	//glEnd();



}
void Display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	/*glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);*/
	/*glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_LINE);*/


	glPushMatrix();
	glTranslatef(tx, ty, tz);		//Зміщення об'єкта
	glRotatef(rx, 1, 0, 0);         //Поворот об'єкта
	glRotatef(ry, 0, 1, 0);

	//Вивід об'єкта на екран

// Колір осі X
	glColor3f(1.0, 0.0, 0.0);
	glLineWidth(2);
	glBegin(GL_LINES);

	glVertex3f(-2.0, 0.0, 0.0);
	glVertex3f(2.0, 0.0, 0.0);
	glEnd();

	// Колір осі Y
	glColor3f(0.0, 0.8, 0.0);
	glBegin(GL_LINES);
	glVertex3f(0.0, -2.0, 0.0);
	glVertex3f(0.0, 2.0, 0.0);
	glEnd();

	// Колір осі Z
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_LINES);
	glVertex3f(0.0, 0.0, -2.0);
	glVertex3f(0.0, 0.0, 2.0);
	glEnd();


	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseMaterial);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	//glMaterialf(GL_FRONT, GL_SHININESS, 76.8f);
	MySolid();

	glPopMatrix();


	glPushMatrix();
	glRotated((GLdouble)spin1, 1.0, 0.0, 1.0);
	glRotated((GLdouble)spin2, 0.0, 1.0, 0.0);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light1_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light1_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light1_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);

	glPushMatrix();
	glTranslated(light0_position[0], light0_position[1], -light0_position[2]);
	glEnable(GL_COLOR_MATERIAL);
	glColor3f(0.0, 1.0, 1.0);
	glutSolidSphere(0.2, 100, 100);
	glPopMatrix();

	glPopMatrix();

	glPushMatrix();

	glRotated((GLdouble)spin11, 1.0, 0.0, 1.0);
	glRotated((GLdouble)spin12, 0.0, 1.0, 0.0);
	glClearColor(0.0, 0.0, 0.0, 0.0);

	glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
	glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);


	glEnable(GL_LIGHT1);
	glPushMatrix();
	glTranslated(light1_position[0], light1_position[1], -light1_position[2]);
	glColor3f(1.0, 0.0, 1.0);
	glutSolidSphere(0.2, 100, 100);
	glPopMatrix();

	glPopMatrix();

	glutSwapBuffers();
}

void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'w':
	{spin11 = (spin11 + 10) % 360;
	glutPostRedisplay(); }
	break;
	case 's':
	{spin11 = (spin11 - 10) % 360;
	glutPostRedisplay(); }
	break;
	case 'a':
	{spin12 = (spin12 - 10) % 360;
	glutPostRedisplay(); }
	break;
	case 'd':
	{spin12 = (spin12 + 10) % 360;
	glutPostRedisplay(); }
	break;
	case VK_ESCAPE:	
		exit(0);
		break;
	}
}

void Reshape(int Width,int Height)	
{
	glViewport(0,0,Width,Height);
	WinWidth=Width;					
	WinHeight=Height;
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-3.0, 3.0, -3.0, 3.0, -10.0, 10.0);

	//	gluPerspective(45,GLdouble(WinWidth)/WinHeight,1,100);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glutPostRedisplay();
}

void KeyboardSpecial(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
	{spin1 = (spin1 + 10) % 360;
	glutPostRedisplay(); }
	break;
	case GLUT_KEY_DOWN:
	{spin1 = (spin1 - 10) % 360;
	glutPostRedisplay(); }
	break;
	case GLUT_KEY_LEFT:
	{spin2 = (spin2 - 10) % 360;
	glutPostRedisplay(); }
	break;
	case GLUT_KEY_RIGHT:
	{spin2 = (spin2 + 10) % 360;
	glutPostRedisplay(); }
	break;
	case GLUT_KEY_F1:	//Якщо нажата клавіша F1
	{
		tt = (tt + 1) % 2;	//Зміна площини зміщення
	}

	}
}

void Mouse(int button, int state, int x, int y)	
{
	if (button==GLUT_LEFT_BUTTON)		
	{
		switch (state)
		{
			case GLUT_DOWN:		
				ldown=true;		 
				mx=x;			     
				my=y;
				break;
			case GLUT_UP:
				ldown=false;
				break;
		}
	}
	if (button==GLUT_RIGHT_BUTTON)	
	{
		switch (state)
		{
			case GLUT_DOWN:    
				rdown=true;         
				mx=x;                
				my=y;
				break;
			case GLUT_UP:
				rdown=false;
				break;
		}
	}
}

void MouseMotion(int x, int y)	
{
	if (ldown)		
	{
		rx+=0.5*(y-my);	
		ry+=0.5*(x-mx);
		mx=x;
		my=y;
		glutPostRedisplay();
	}
	if (rdown)	  
	{
		tx+=0.01*(x-mx);
		if (tt)
			tz+=0.01*(y-my);
		else
			ty+=0.01*(my-y);
		mx=x;
		my=y;
		glutPostRedisplay();    
	}
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(WinWidth, WinHeight);
	glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - WinWidth) / 2, (glutGet(GLUT_SCREEN_HEIGHT) - WinHeight) / 2);
	glutCreateWindow("MySolid");

	Init();

	glutDisplayFunc(Display);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(KeyboardSpecial);
	glutReshapeFunc(Reshape);
	glutMouseFunc(Mouse);
	glutMotionFunc(MouseMotion);

	glutMainLoop();
	glDisable(GL_LIGHT1);
	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHTING);
	return 0;
}
