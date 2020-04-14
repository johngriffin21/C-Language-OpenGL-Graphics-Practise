#include <GL/gl.h>
#include <GL/glext.h>
#include "glut.h"
#include <stdio.h>

//The question: 

/*
You are asked to create a 3D sculpture tool using OpenGL.
The user should be able to construct a 3D sculpture by inserting 
objects at different locations in 3D space using the mouse and/or 
keyboard. The user should be able to choose the size and shape of 
the objects (e.g. spheres, cubes, cylinders etc.) using a menu. 
You should be able to rotate the whole sculpture so that you can 
see it from different viewpoints. You should also be able to add 
colour, material properties and lighting.  
*/

GLfloat y_shift = 0; 
GLfloat x_shift = 0;
GLfloat z_shift = 0;
GLfloat size = 1.0;
GLint shape = 0;
GLfloat shapes[10][20];
GLint i = 0; 
GLint number_of_shapes = 0; 
GLint color = 0;
GLfloat x_view = 0.0;
GLfloat y_view = 0.9;
GLfloat z_view = 2.0;
//For rotating the sculpture. (Come to this last)
GLfloat angle = 0.0;

void MyReshape(GLsizei w, GLsizei h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-1.0,1.0,-1.0,1.0,0.5,20-.0);
	glViewport(0,0,w,h);
	return;
}

//For moving objects left and right. 
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
	glutPostRedisplay();
	glFlush();
	return;
}

void keyboardFunction(unsigned char key, GLint x, GLint y)
{
    // For increasing the height of each repsective object before placing. 
	if (key == 'u')
	{
	y_shift += 0.1;
	}
	else if (key == 'd')
	{
	y_shift -= 0.1;
	}
	//View of sculpture
	//So w,s for height, er for side-side , pl for zoom in/zoom out. q for rotate.
	else if (key == 'w')
	{
	y_view += 0.1;
	}
	else if (key == 's')
	{
	y_view -= 0.1;
	}
    else if (key == 'e')
	{
	x_view += 0.1;
	}
	else if (key == 'r')
	{
	x_view -= 0.1;
	}
	else if (key == 'p')
	{
	z_view += 0.1;
	}
	else if (key == 'l')
	{
	z_view -= 0.1;
	}
	else if (key == 'b')
	{
	size += 0.1;
	}
	else if (key == 'n')
	{
	size -= 0.1;
	}
	else if(key == 'q')
	{
	   angle += 0.9;
       if (angle > 360.0){
       angle -= 360.0;
	   }
	}
	glutPostRedisplay();
	glFlush();
	return;
}

void light_connection(GLfloat x, GLfloat y, GLfloat z){
    glPushMatrix();
	glTranslatef(x,y,z);
	glScalef(0.2,0.00,1.2);
	glutSolidCube(1.0);
    glPopMatrix();
	return;
}

void light_pole(GLfloat x, GLfloat y, GLfloat z){
    glPushMatrix();
	glTranslatef(x,y,z);
	glScalef(0.2,4.5,0.05);
	glutSolidCube(1.0);
	glPopMatrix();
	return;

}

void top_of_light(GLfloat x, GLfloat y, GLfloat z){
    glPushMatrix();
	glTranslatef(x,y,z);
	glutSolidSphere(0.2, 3, 3);
    glPopMatrix();
    return;

}

void lamp (GLfloat x, GLfloat y, GLfloat z)
{
    glPushMatrix();
	glTranslatef(x,y,z);
	light_pole(0.0,1.8,-2.0);	
	light_connection(0.0,3.8,-1.5);
	top_of_light(0.0,3.8,-1.0);
	//Light Source
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glTranslatef(0.0,3.8,0.0);
	GLfloat pos[4] = {x,y,z,1.0};
	glLightfv(GL_LIGHT0,GL_POSITION,pos);
    glShadeModel (GL_SMOOTH);
	glPopMatrix();
	return;
}

void draw_sphere(GLfloat x, GLfloat y, GLfloat z){
    glPushMatrix();
	glTranslatef(x,y,z);
	glutSolidSphere(size, 20, 20); 
	glPopMatrix();
	return;
}

void draw_cube(GLfloat x, GLfloat y, GLfloat z){
    glPushMatrix();
	glTranslatef(x,y,z);
	glutSolidCube(size); 
	glPopMatrix();
	return;
}

void draw_cone(GLfloat x, GLfloat y, GLfloat z){
    glPushMatrix();
	glTranslatef(x,y,z);
	glutSolidCone(size, 0.5, 20 , 20); 
	glPopMatrix();
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
	//So here we define our viewing point. 
 	//Define a viewing ([FROM] eyeX, eyeY, eyeZ,[TO] centerX, centerY, centerZ, upX, upY, upZ) ->  Specifies the direction of the up vector. [Y AXIS HERE]
	gluLookAt(x_view,y_view,z_view,0.0,0.0,0.0,0.0,1.0,0.0);
	//x increases up the way.(So ovo this is flat on the xplane hence the 0's)
	//*************Chosing color of our sculptrure************************************

	//Black sculpture
	if (color == 2){
	GLfloat  ambient[4] ={ 0.02f, 0.02f, 0.02f, 1.0f };
    GLfloat  diffuse[4] ={ 0.01f, 0.01f, 0.01f, 1.0f};
    GLfloat specular[4] ={0.4f, 0.4f, 0.4f, 1.0f };
    GLfloat shininess = 10.0f;

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
	}

	//Brass sculpture
	if (color == 1){
	GLfloat  ambient1[4] = {0.33 , 0.22 , 0.03 , 1.0 };
	GLfloat  diffuse1[4] = {0.78 , 0.57 , 0.11 , 1.0 };
	GLfloat specular1[4] = {0.99 , 0.91 , 0.81 , 1.0 };
	GLfloat shininess1 = 27.0; //32.0;
	
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient1);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse1);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular1);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess1);
	}




	
	//************Sculpture Creation Space****************************************

	glPushMatrix();
	glBegin(GL_POLYGON);
	    glNormal3f(0.0,1.0,0.0);
		glVertex3f(-2.0,0.0,0.5);
		glVertex3f(2.0,0.0,0.5);
		glVertex3f(2.0,0.0,-3.5);
		glVertex3f(-2.0,0.0,-3.5);
	glEnd();
	glPopMatrix();
    
	//For drawing after object is selcted. 
	for (i = 0 ; i < number_of_shapes; i++){
		if(shapes[i][0] == 0)
		{
		draw_sphere(shapes[i][1], shapes[i][2] , shapes[i][3]);
		}
		else if(shapes[i][0] == 1)
		{
		draw_cone(shapes[i][1], shapes[i][2] , shapes[i][3]);
		}
		else if(shapes[i][0] == 2)
		{
		draw_cube(shapes[i][1], shapes[i][2] , shapes[i][3]);
		}
		else if(shapes[i][0] == 4)
		{
		lamp(shapes[i][1], shapes[i][2] , shapes[i][3]);
		}
	}
	//printf("Furniture here is %d \n", furniture);

	if (shape ==0)
	{
	glTranslatef(x_shift,y_shift,z_shift);
	glRotatef(angle,0.0,0.0,1.0);
	draw_sphere(0.0,0.0,0.0);
	}
	
	if (shape == 2)
	{
	glTranslatef(x_shift,y_shift,z_shift);
	//So one here is roating around the x axis by 1.0. 
	glRotatef(angle,1.0,0.0,0.0);
    draw_cube(0.0,0.0,0.0);
	}
	if (shape == 1)
	{
	glTranslatef(x_shift,y_shift,z_shift);
	glRotatef(angle,0.0,0.0,1.0);
    draw_cone(0.0,0.0,0.0);
	}
	if (shape == 4)
	{
	glTranslatef(x_shift,y_shift,z_shift);
	glRotatef(angle,0.0,0.0,1.0);
    lamp(0.0,0.0,0.0);
	}
	GLfloat pos[4] = {0.0,0.0,7.0,0.0};
	//Draw lights after moving object to stop all going into the dark
	glPushMatrix();
	glLoadIdentity();
	glLightfv(GL_LIGHT0, GL_POSITION, pos);
    glPopMatrix();
	glutSwapBuffers();
	glFlush();
	return;
}
//Menu for our objects. 
void mymenu(int value)
{
//So if you select ("clear" == 1 ) The screen gets cleared
	if(value == 1) exit(0);
	//Sphere 
	if(value == 2) 
	{
	shape = 0;
	}
	//Cylinder 
	if(value == 3)
	{
	shape = 1;
	}
	//Cube 
	if(value == 4)
	{
	shape = 2;
	}
	//Car :)
	if(value == 5)
	{
	shape = 3;
	}
    //Light 
	if(value == 6)
	{
	shape = 4;
	}
	if(value == 7)
	{
	color = 1;
	}
	if(value == 8)
	{
	color = 2;
	}
	if(value == 9)
	{
	color = 0;
	}

	//Now redisplay when selected. 
	glutPostRedisplay();
    return;
}

void save_object(GLint button, GLint state, GLint x, GLint y)
{
    //Save object and add it tro our sculpture. 
    if(state == GLUT_DOWN && button == GLUT_LEFT_BUTTON)
	{
	    shapes[number_of_shapes][0] = shape;
		shapes[number_of_shapes][1] = x_shift;
		shapes[number_of_shapes][2] = y_shift;
		shapes[number_of_shapes][3] = z_shift;
		shapes[number_of_shapes][4] = angle;
		number_of_shapes ++;
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
	glutCreateWindow("Sculpture creator");
	glutDisplayFunc(display);
	glutReshapeFunc(MyReshape);
	glutSpecialFunc(mySpecialFunction);
	glutKeyboardFunc(keyboardFunction);
	//View the floor from a better angle 
	id = glutCreateMenu(mymenu);
    glutAddMenuEntry("Exit",1);
	glutAddMenuEntry("Sphere",2);
	glutAddMenuEntry("Cylider",3);
	glutAddMenuEntry("Cube",4);
	glutAddMenuEntry("Car",5);
	glutAddMenuEntry("Light",6);
	glutAddMenuEntry("Brass",7);
	glutAddMenuEntry("Black Rubber",8);
	glutAddMenuEntry("No color",9);
	glutMouseFunc(save_object);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
}