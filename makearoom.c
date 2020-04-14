#include <GL/gl.h>
#include <GL/glext.h>
#include "glut.h"
//For printing debugging
#include <stdio.h>
GLfloat height_of_globe = 0; 
GLfloat x_shift = 0;
GLfloat z_shift = 0;
GLint furniture = 1;
GLfloat objects[10][20];
GLint i = 0; 
GLint number_of_objects = 0; 

GLfloat x_from = 0.0;
GLfloat y_from = 0.9;
GLfloat z_from = 2.0;

//For moving light 
GLfloat dx = 1.0;
GLfloat dy = 1.0;
GLfloat dz = 1.0;

GLfloat theta = 0.0;

/*
typedef stuct material {
	GLfloat ambient[4];
    GLfloat diffuse[4];	
	GLfloat specular[4];
	GLfloat shininess;
} material;

material brass = {
	{0.33,0.22,0.03,1.0},
	{0.78,0.57,0.11,1.0},
	{0.99,0.91,0.81,1.0},
	27.8
};


void materials (material *m){
	glMaterialfv (GL_FRONT_AND_BACK, GL_AMBIENT, m->ambient);
	glMaterialfv (GL_FRONT_AND_BACK, GL_DIFFUSE, m->diffuse);
	glMaterialfv (GL_FRONT_AND_BACK, GL_SPECULAR, m->specular);
	glMaterialfv (GL_FRONT_AND_BACK, GL_SHININESS, m->shininess);
}
*/

void matress(GLfloat x, GLfloat y, GLfloat z){
   glPushMatrix();
   //Up one to give some height to the bed
   glTranslatef(x,y,z);
   //Now give some width to the bed 
   glScalef(0.35,0.2,0.25);
   glutSolidCube(1.0);
   glPopMatrix();
   return;
}

void table_top(GLfloat x, GLfloat y, GLfloat z){
   glPushMatrix();
   //Up one to give some height to the bed,
   glTranslatef(x,y,z);
   //So we have a square top but slim enough.
   glScalef(0.35,0.05,0.05);
   glutSolidCube(1.0);
   glPopMatrix();
   return;
}

void table_leg(GLfloat x, GLfloat y, GLfloat z){
   glPushMatrix();
   //Up one to give some height to the bed
   glTranslatef(x,y,z);
   //So width height and length of legs 
   glScalef(0.05,0.2,0.005);
   glutSolidCube(1.0);
   glPopMatrix();
   return;
}

void pillow(GLfloat x, GLfloat y, GLfloat z){
   glPushMatrix();
   //Up one to give some height to the bed.
   glTranslatef(x,y,z);
   //So we want this bad boy to be a tiny rectangle basically.
   glScalef(0.35,0.1,0.005);
   glutSolidCube(1.0);
   glPopMatrix();
   return;
}

void leg(GLfloat x, GLfloat y, GLfloat z){
   glPushMatrix();
   //Up one to give some height to the bed
   glTranslatef(x,y,z);
   //So width height and length of legs 
   glScalef(0.05,0.1,0.05);
   glutSolidCube(1.0);
   glPopMatrix();
   return;
}

void make_bed(GLfloat x, GLfloat y, GLfloat z){
	glPushMatrix();
	glTranslatef(x,y,z);
	matress(0.0,0.2,0.0);
	pillow(0.0,0.3,-.1);
	leg(-0.1,0.05,0.1);
	leg(-0.1,0.05,-0.1);
	leg(0.1,0.05,-0.1);
	leg(0.1,0.05,0.1);
	glPopMatrix();

	return;
}

void make_bedside_locker(GLfloat x, GLfloat y, GLfloat z){
	glPushMatrix();
	glTranslatef(x,y,z);
	table_top(0.0,0.2,0.0);
	table_leg(-0.1,0.05,0.025);
	table_leg(-0.1,0.05,-0.025);
	table_leg(0.1,0.05,-0.025);
	table_leg(0.1,0.05,0.025);
	glPopMatrix();

	return;
}

void draw_teapot(GLfloat x, GLfloat y, GLfloat z){
    glPushMatrix();
	glTranslatef(x,y,z);
	glutSolidTeapot(0.1); 
	glPopMatrix();
	return;
}

void MyReshape(GLsizei w, GLsizei h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
//	glOrtho(-1.0,1.0,-1.0,1.0,-1.0,1.0);
	glFrustum(-1.0,1.0,-1.0,1.0,0.5,20-.0);
	glViewport(0,0,w,h);
	return;
}



void mySpecialFunction(GLint key, GLint x , GLint y)
{
	if (key == GLUT_KEY_RIGHT){
	    x_shift += 0.1;
	}
	else if (key == GLUT_KEY_LEFT){
	    x_shift -= 0.1; 
	}
	else if (key == GLUT_KEY_UP){
	    z_shift -= 0.1;
	}
    else if (key == GLUT_KEY_DOWN){
	    z_shift += 0.1;
	}
	//For terminal debugging and seeing where everything is.
	//Won't work unless we add the following: 
	glutPostRedisplay();
	glFlush();
	return;

}


void mymenu(int value)
{
//So if you select ("clear" == 1 ) The screen gets cleared(PRETTY EASY INIT ?!?!?)
	if(value == 1) exit(0);
	//Table 
	if(value == 2) 
	{
	furniture = 0;
	}
	//Bed 
	if(value == 3)
	{
	furniture = 1;
	}
	if(value == 4)
	{
	furniture = 2;
	}
	//NB ! 
	glutPostRedisplay();
    return;


}

void save_object(GLint button, GLint state, GLint x, GLint y)
{
    if(state == GLUT_DOWN && button == GLUT_LEFT_BUTTON && furniture == 2)
	{
        printf("We have written to this function for some reason \n");
	    objects[number_of_objects][0] = furniture;
		objects[number_of_objects][1] = x_shift;
		objects[number_of_objects][2] = height_of_globe;
		objects[number_of_objects][3] = z_shift;
		number_of_objects ++;
	}
	else if(state == GLUT_DOWN && button == GLUT_LEFT_BUTTON)
	{ //Set the array of K to: Item of furn and x , y , z
		objects[number_of_objects][0] = furniture;
		objects[number_of_objects][1] = x_shift;
		objects[number_of_objects][2] = 0.0;
		objects[number_of_objects][3] = z_shift;
		number_of_objects ++;
	}
	//Now for scroll wheel 3 is up, 4 is down.
	glutPostRedisplay();
	glFlush();
	return;
}


void display(void)
{
    glClearColor(0.0,0.0,1.0,1.0);
	//Depth buffer decides if geometry rendered is closer than geometry previously rendered. 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//Any time a frag is rendered, it's depth is compared to corresponding value in depth buffer. 
	glEnable(GL_DEPTH_TEST);
	//Lighting settings 
	glEnable(GL_LIGHTING);
	//Enable color with our lighting. 
    glEnable(GL_LIGHT0);
	//specify whether front or back facing polygons are candidates for culling.
	//For lighting position: 
	/*
	GLfloat pos[4] = {0.0,0.0,7.0,0.0};
	glLightfv(GL_LIGHT0, GL_POSITION, pos);
	*/
	//specify which matrix is the current matrix &  modelview below applies matrix operations to the modelview matrix stack. Relationship of viewer to object
	glMatrixMode(GL_MODELVIEW);
	//Replace current matrix with identity matrix. Get's rid of any previous values that are in that matrix
	glLoadIdentity();
	//TODO Below x is up, so z is depth and y is therefore side to side. 
	//Define a viewing transformation([FROM] eyeX, eyeY, eyeZ,[TO] centerX, centerY, centerZ, upX, upY, upZ) ->  Specifies the direction of the up vector. [Y AXIS HERE]
	gluLookAt(x_from,y_from,z_from,0.0,0.0,0.0,0.0,1.0,0.0);
    //Red green blue opicy
	//Clear screen
	//Anytime you create an object start with gl begin and end with gl end. 
	//Vertexes is a corner, 2f(2 dimensions)
    //Those are world coordinates to. 
	//x increases up the way.(So ovo this is flat on the xplane hence the 0's)
	//Store current matrix, and make alterations only to this.

	//************FLOOR***************************

	glPushMatrix();
	glBegin(GL_POLYGON);
	    glNormal3f(0.0,1.0,0.0);
		glVertex3f(-2.0,0.0,0.5);
		glVertex3f(2.0,0.0,0.5);
		glVertex3f(2.0,0.0,-1.5);
		glVertex3f(-2.0,0.0,-1.5);
	glEnd();
	glPopMatrix();

	//************Right wall***************************

	glPushMatrix();
	glBegin(GL_POLYGON);
	    glNormal3f(0.0,1.0,0.0);
		glVertex3f(2.0,0.0,0.5);
		glVertex3f(2.0,0.0,-1.5);
		glVertex3f(2.0,1.5,-1.5);
		glVertex3f(2.0,1.5,0.5);
	glEnd();
	glPopMatrix();

	//************Left wall***************************
	
	glPushMatrix();
	glBegin(GL_POLYGON);
	    glNormal3f(0.0,1.0,0.0);
		glVertex3f(-2.0,0.0,0.5);
		glVertex3f(-2.0,0.0,-1.5);
		glVertex3f(-2.0,1.5,-1.5);
		glVertex3f(-2.0,1.5,0.5);
	glEnd();
	glPopMatrix();

	
	//************Back wall***************************

	glPushMatrix();
	glBegin(GL_POLYGON);
	    glNormal3f(0.0,1.0,0.0);
		glVertex3f(2.0,0.0,-1.5);
		glVertex3f(2.0,1.5,-1.5);
		glVertex3f(-2.0,1.5,-1.5);
		glVertex3f(-2.0,0.0,-1.5);
	glEnd();
	glPopMatrix();

	
	
	//*****************************************************

	glColor3f(1.0,0.0,1.0);

	for (i = 0 ; i < number_of_objects; i++){
		if(objects[i][0] == 1)
		{
		make_bed(objects[i][1], 0.0 , objects[i][3]);
		}
		else if(objects[i][0] == 0)
		{
		make_bedside_locker(objects[i][1], 0.0 ,objects[i][3]);
		}
		else if(objects[i][0] == 2)
		{
		draw_teapot(objects[i][1],objects[i][2] ,objects[i][3]);
		}
	}
	//printf("Furniture here is %d \n", furniture);

	if (furniture == 1)
	{
	glTranslatef(x_shift,0.0,z_shift);
	make_bed(0.0,0.0,0.0);
	}
	if (furniture == 0)
	{
    glTranslatef(x_shift,0.0,z_shift);
    make_bedside_locker(0.0,0.0,0.0);
	}
	if (furniture == 2)
	{
	
    glTranslatef(x_shift,height_of_globe,z_shift);
    draw_teapot(0.0,0.0,0.0);
	}
	GLfloat pos[4] = {0.0,0.0,7.0,0.0};
	//Draw lights after moving object to stop all going into the dark
	glPushMatrix();
	glLoadIdentity();
	glRotatef(theta, dx, dy, dz);
	glRotatef(theta, dx, dy, dz);
	glLightfv(GL_LIGHT0, GL_POSITION, pos);
    glPopMatrix();


	//Test without this
	//glutSwapBuffers();
	//Set it all up 
	glFlush();
	return;
}


void Plandisplay(void)
{
    glClearColor(0.0,0.0,1.0,1.0);
	//Depth buffer decides if geometry rendered is closer than geometry previously rendered. 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//Any time a frag is rendered, it's depth is compared to corresponding value in depth buffer. 
	glEnable(GL_DEPTH_TEST);
	//Lighting settings 
	glEnable(GL_LIGHTING);
	//Enable color with our lighting. 
    glEnable(GL_LIGHT0);
	//specify whether front or back facing polygons are candidates for culling.
	//For lighting position: 
	/*
	GLfloat pos[4] = {0.0,0.0,7.0,0.0};
	glLightfv(GL_LIGHT0, GL_POSITION, pos);
	*/
	//specify which matrix is the current matrix &  modelview below applies matrix operations to the modelview matrix stack. Relationship of viewer to object
	glMatrixMode(GL_MODELVIEW);
	//Replace current matrix with identity matrix. Get's rid of any previous values that are in that matrix
	glLoadIdentity();
	//TODO Below x is up, so z is depth and y is therefore side to side. 
	//Define a viewing transformation([FROM] eyeX, eyeY, eyeZ,[TO] centerX, centerY, centerZ, upX, upY, upZ) ->  Specifies the direction of the up vector. [Y AXIS HERE]
	//TODO Change has to be made to the Look At vector as well if we change to the plan view (UP VECOTR)
	gluLookAt(0.0,1.0,0.0,0.0,0.0,0.0,0.0,0.0,-1.0);
    //Red green blue opicy
	//Clear screen
	//Anytime you create an object start with gl begin and end with gl end. 
	//Vertexes is a corner, 2f(2 dimensions)
    //Those are world coordinates to. 
	//x increases up the way.(So ovo this is flat on the xplane hence the 0's)
	//Store current matrix, and make alterations only to this.

	//************FLOOR***************************

	glPushMatrix();
	glBegin(GL_POLYGON);
	    glNormal3f(0.0,1.0,0.0);
		glVertex3f(-2.0,0.0,0.5);
		glVertex3f(2.0,0.0,0.5);
		glVertex3f(2.0,0.0,-1.5);
		glVertex3f(-2.0,0.0,-1.5);
	glEnd();
	glPopMatrix();

	//************Right wall***************************

	glPushMatrix();
	glBegin(GL_POLYGON);
	    glNormal3f(0.0,1.0,0.0);
		glVertex3f(2.0,0.0,0.5);
		glVertex3f(2.0,0.0,-1.5);
		glVertex3f(2.0,1.5,-1.5);
		glVertex3f(2.0,1.5,0.5);
	glEnd();
	glPopMatrix();

	//************Left wall***************************
	
	glPushMatrix();
	glBegin(GL_POLYGON);
	    glNormal3f(0.0,1.0,0.0);
		glVertex3f(-2.0,0.0,0.5);
		glVertex3f(-2.0,0.0,-1.5);
		glVertex3f(-2.0,1.5,-1.5);
		glVertex3f(-2.0,1.5,0.5);
	glEnd();
	glPopMatrix();

	
	//************Back wall***************************

	glPushMatrix();
	glBegin(GL_POLYGON);
	    glNormal3f(0.0,1.0,0.0);
		glVertex3f(2.0,0.0,-1.5);
		glVertex3f(2.0,1.5,-1.5);
		glVertex3f(-2.0,1.5,-1.5);
		glVertex3f(-2.0,0.0,-1.5);
	glEnd();
	glPopMatrix();

	
	
	//*****************************************************

	glColor3f(1.0,0.0,1.0);

	for (i = 0 ; i < number_of_objects; i++){
		if(objects[i][0] == 1)
		{
		make_bed(objects[i][1], 0.0 , objects[i][3]);
		}
		else if(objects[i][0] == 0)
		{
		make_bedside_locker(objects[i][1], 0.0 ,objects[i][3]);
		}
		else if(objects[i][0] == 2)
		{
		draw_teapot(objects[i][1],objects[i][2] ,objects[i][3]);
		}
	}
	//printf("In plan dispaly");

	if (furniture == 1)
	{
	glTranslatef(x_shift,0.0,z_shift);
	make_bed(0.0,0.0,0.0);
	}
	if (furniture == 0)
	{
    glTranslatef(x_shift,0.0,z_shift);
    make_bedside_locker(0.0,0.0,0.0);
	}
	if (furniture == 2)
	{
	
    glTranslatef(x_shift,height_of_globe,z_shift);
    draw_teapot(0.0,0.0,0.0);
	}
	GLfloat pos[4] = {0.0,1.0,0.0,0.0};
	//Draw lights after moving object to stop all going into the dark
	glPushMatrix();
	glLoadIdentity();
	glLightfv(GL_LIGHT0, GL_POSITION, pos);
    glPopMatrix();


	//Test without this
	//glutSwapBuffers();
	//Set it all up 
	glFlush();
	return;
}

void Plan_MyReshape(GLsizei w, GLsizei h){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0,1.0,-1.0,1.0,-1.0,1.0);
	//glFrustum(-1.0,1.0,-1.0,1.0,0.5,20-.0);
	glViewport(0,0,w,h);
	return;
}

void idle(){
    //printf("Theta here %d", theta);
	theta += 0.02;
	if (theta > 360.0)
	theta -= 360.0;
	glutPostRedisplay();
	glFlush();
	return;
}

void keyboardFunction(unsigned char key, GLint x, GLint y)
{
	if (key == 'u')
	{
	height_of_globe += 0.1;
	}
	else if (key == 'd')
	{
	height_of_globe -= 0.1;
	}
	else if (key == 'w')
	{
	y_from += 0.1;
	}
	else if (key == 's')
	{
	y_from -= 0.1;
	}
    else if (key == 'e')
	{
	x_from += 0.1;
	}
	else if (key == 'r')
	{
	x_from -= 0.1;
	}
	else if (key == 'p')
	{
	z_from += 0.1;
	}
	else if (key == 'l')
	{
	z_from -= 0.1;
	}
	glutPostRedisplay();
	glFlush();
	return;
}

int main(int argc, char **argv)
{
    GLint id;
	glutInit(&argc, argv);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(500,200);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("Right click to select the furniture, arrow keys to place it, left key to save it");
	glutDisplayFunc(display);
	glutReshapeFunc(MyReshape);
	glutSpecialFunc(mySpecialFunction);
	glutKeyboardFunc(keyboardFunction);
	//View the floor from a better angle 
	id = glutCreateMenu(mymenu);
    glutAddMenuEntry("Exit",1);
	glutAddMenuEntry("Table",2);
	glutAddMenuEntry("Bed",3);
	glutAddMenuEntry("Teapot",4);
	glutMouseFunc(save_object);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutCreateWindow("Our supposed window number two");
	glutDisplayFunc(Plandisplay);
	glutReshapeFunc(Plan_MyReshape);


	glEnable(GL_DEPTH_TEST);
	glutIdleFunc(idle);

	glutMainLoop();
}