//---------------------------------------
// Mae Larrea
// 4/17/19
//---------------------------------------
#include <iostream>
#include <fstream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#ifdef MAC
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include "libim/im_color.h"
using namespace std;

// Global variables 
#define ROTATE 1
#define TRANSLATE 2
int xangle = 0;
int yangle = 0;
int zangle = -90;
int xpos = 0;
int ypos = 0;
int zpos = 0;
int mode = ROTATE;

int xdim, ydim;
char *brick = "textures/brick.jpg";
char *rock = "textures/rock.jpg";
char *wood = "textures/wood.jpg";
char *fire = "textures/fire.jpg";
char *grass = "textures/grass.jpg";

unsigned char *brick_texture;
unsigned char *rock_texture;
unsigned char *wood_texture;
unsigned char *fire_texture;
unsigned char *grass_texture;

int xMax;
int yMax;
int xStart;
int yStart;
char maze[100][100];

void mazeRead()
{
	ifstream in_file;
	in_file.open("maze.txt");
	if(in_file.fail())
	{
		cout << "File did not open" << endl;
		return;
	}
	else
	{
		in_file >> xMax >> yMax;
		in_file >> xStart >> yStart;
		cout << xMax << endl << yMax << endl << xStart <<endl << yStart << endl;
		for(int i = 0; i < xMax; i++)
			for(int j = 0; j < yMax; j++)
				in_file >> maze[i][j];
	}
}

// Initialize texture image
void init_texture(char *name, unsigned char *&texture, int &xdim, int &ydim)
{
   // Read jpg image
   im_color image;
   image.ReadJpg(name);
   printf("Reading image %s\n", name);
   xdim = 1; while (xdim < image.R.Xdim) xdim*=2; xdim /=2;
   ydim = 1; while (ydim < image.R.Ydim) ydim*=2; ydim /=2;
   image.Interpolate(xdim, ydim);
   printf("Interpolating to %d by %d\n", xdim, ydim);

   // Copy image into texture array
   texture = (unsigned char *)malloc((unsigned int)(xdim*ydim*3));
   int index = 0;
   for (int y = 0; y < ydim; y++)
      for (int x = 0; x < xdim; x++)
      {
         texture[index++] = (unsigned char)(image.R.Data2D[y][x]);
         texture[index++] = (unsigned char)(image.G.Data2D[y][x]);
         texture[index++] = (unsigned char)(image.B.Data2D[y][x]);
      }
}

// Function to draw 3D block
void block(float xmin, float ymin, float zmin,
           float xmax, float ymax, float zmax)
{
   // Define 8 vertices
   float ax = xmin, ay = ymin, az = zmax;
   float bx = xmax, by = ymin, bz = zmax;
   float cx = xmax, cy = ymax, cz = zmax;
   float dx = xmin, dy = ymax, dz = zmax;

   float ex = xmin, ey = ymin, ez = zmin;
   float fx = xmax, fy = ymin, fz = zmin;
   float gx = xmax, gy = ymax, gz = zmin;
   float hx = xmin, hy = ymax, hz = zmin;

   // Draw 6 faces
   glBegin(GL_POLYGON);  // Max texture coord 1.0
   glTexCoord2f(0.0, 0.0);
   glVertex3f(ax, ay, az);
   glTexCoord2f(1.0, 0.0);
   glVertex3f(bx, by, bz);
   glTexCoord2f(1.0, 1.0);
   glVertex3f(cx, cy, cz);
   glTexCoord2f(0.0, 1.0);
   glVertex3f(dx, dy, dz);
   glEnd();

   glBegin(GL_POLYGON);  // Max texture coord 1.0
   glTexCoord2f(0.0, 0.0);
   glVertex3f(ex, ey, ez);
   glTexCoord2f(1.0, 0.0);
   glVertex3f(ax, ay, az);
   glTexCoord2f(1.0, 1.0);
   glVertex3f(dx, dy, dz);
   glTexCoord2f(0.0, 1.0);
   glVertex3f(hx, hy, hz);
   glEnd();

   glBegin(GL_POLYGON);  // Max texture coord 1.0
   glTexCoord2f(0.0, 0.0);
   glVertex3f(fx, fy, fz);
   glTexCoord2f(1.0, 0.0);
   glVertex3f(ex, ey, ez);
   glTexCoord2f(1.0, 1.0);
   glVertex3f(hx, hy, hz);
   glTexCoord2f(0.0, 1.0);
   glVertex3f(gx, gy, gz);
   glEnd();

   glBegin(GL_POLYGON);  // Max texture coord 1.0
   glTexCoord2f(0.0, 0.0);
   glVertex3f(bx, by, bz);
   glTexCoord2f(1.0, 0.0);
   glVertex3f(fx, fy, fz);
   glTexCoord2f(1.0, 1.0);
   glVertex3f(gx, gy, gz);
   glTexCoord2f(0.0, 1.0);
   glVertex3f(cx, cy, cz);
   glEnd();

   glBegin(GL_POLYGON);  // Max texture coord 3.0
   glTexCoord2f(0.0, 0.0);
   glVertex3f(ax, ay, az);
   glTexCoord2f(2.0, 0.0);
   glVertex3f(ex, ey, ez);
   glTexCoord2f(2.0, 2.0);
   glVertex3f(fx, fy, fz);
   glTexCoord2f(0.0, 2.0);
   glVertex3f(bx, by, bz);
   glEnd();

   glBegin(GL_POLYGON);  // Max texture coord 3.0
   glTexCoord2f(0.0, 0.0);
   glVertex3f(gx, gy, gz);
   glTexCoord2f(3.0, 0.0);
   glVertex3f(cx, cy, cz);
   glTexCoord2f(3.0, 3.0);
   glVertex3f(dx, dy, dz);
   glTexCoord2f(0.0, 3.0);
   glVertex3f(hx, hy, hz);
   glEnd();
}

// Display callback for OpenGL
void display()
{
   // Incrementally rotate objects
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glTranslatef(xStart / 500.0, yStart / 500.0, zpos / 500.0);
   glRotatef(xangle, 1.0, 0.0, 0.0);
   glRotatef(yangle, 0.0, 1.0, 0.0);
   glRotatef(zangle, 0.0, 0.0, 1.0);
   int k = -9;

   // Draw objects
	for(int i = 0; i < xMax; i++)
	{
		for(int j = 0; j < yMax; j++)
		{
			if(maze[i][j] == 'r')   
			{
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, xdim, ydim, 0, GL_RGB, GL_UNSIGNED_BYTE, rock_texture);
				block(i+k, j+k, k, i+1+k, j+1+k, 3+k);
			}
			else if(maze[i][j] == 'b')   
			{
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, xdim, ydim, 0, GL_RGB, GL_UNSIGNED_BYTE, brick_texture);
				block(i+k, j+k, k, i+1+k, j+1+k, 3+k);
			}
			else if(maze[i][j] == 'w')   
			{
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, xdim, ydim, 0, GL_RGB, GL_UNSIGNED_BYTE, wood_texture);
				block(i+k, j+k, k, i+1+k, j+1+k, 3+k);
			}
			else if(maze[i][j] == '*')
			{
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, xdim, ydim, 0, GL_RGB, GL_UNSIGNED_BYTE, grass_texture);
				block(i+k, j+k, k, i+1+k, j+1+k, k);
			}
		}
	}

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, xdim, ydim, 0, GL_RGB, GL_UNSIGNED_BYTE, fire_texture);
	block(xStart+k, yStart+k, zpos+k, 1+xStart +k, yStart+1+k, zpos+1+k);
    glFlush();
}

void init()
{
   // Init view
	mazeRead();
	float rad = sqrt(xMax*xMax + yMax*yMax)/2;

   glClearColor(0.0, 0.0, 0.0, 1.0);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(-rad, rad, -rad, rad, -rad, rad);
   glEnable(GL_DEPTH_TEST);

   // Init texture
   unsigned char *texture;
   init_texture(brick, brick_texture, xdim, ydim);
	init_texture(rock, rock_texture, xdim, ydim);
	init_texture(wood, wood_texture, xdim, ydim);
	init_texture(grass, grass_texture, xdim, ydim);
	init_texture(fire, fire_texture, xdim, ydim);
   glEnable(GL_TEXTURE_2D);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, xdim, ydim, 0, GL_RGB, GL_UNSIGNED_BYTE, texture);
   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}

// Keyboard callback for OpenGL
void keyboard(unsigned char key, int x, int y)
{
   // Determine if we are in ROTATE or TRANSLATE mode
   if ((key == 's') || (key == 'S'))
   {
      printf("Type x y z to decrease or X Y Z to increase the rotating of the board.\n");
      mode = ROTATE;
   }
   else if ((key == 't') || (key == 'T'))
   {
      printf("Type 'f' or 'F' - to move player forward\n");
      printf("Type 'b' or 'B' - to move player backward\n");
      printf("Type 'l' or 'L' - to move player to the left\n");
  	  printf("Type 'r' or 'R' - to move player to the right\n");
      mode = TRANSLATE;
   }

   // Handle ROTATE
   if (mode == ROTATE)
   {
      if (key == 'x')
	 xangle -= 1;
      else if (key == 'y')
	 yangle -= 1;
      else if (key == 'z')
	 zangle -= 1;
      else if (key == 'X')
	 xangle += 1;
      else if (key == 'Y')
	 yangle += 1;
      else if (key == 'Z')
	 zangle += 1;
      glutPostRedisplay();
   }

   // Handle TRANSLATE


   if (mode == TRANSLATE)
   {
      if (key == 'b' || key == 'B')
		{
			if(maze[xStart-1][yStart] == '*')
	 			xStart -= 1;
		}
      else if (key == 'f' || key == 'F')
		{
			if(maze[xStart+1][yStart] == '*')
	 			xStart += 1;
		}
	 else if (key == 'l' || key == 'L')
	 	{
			if(maze[xStart][yStart-1] == '*')
	 			yStart -= 1;
		}
      else if (key == 'r' || key == 'R')
		{
			if(maze[xStart][1+yStart] == '*')
	 			 yStart += 1;
		}
      glutPostRedisplay();
   }

}

// Main program
int main(int argc, char *argv[])
{
   // Create OpenGL window
   glutInit(&argc, argv);
   glutInitWindowSize(500, 500);
   glutInitWindowPosition(250, 250);
   glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH);
   glutCreateWindow("My Maze");
   glutDisplayFunc(display);
   glutKeyboardFunc(keyboard);
    init();
    printf("Keyboard commands:\n");
    printf("   't' or 'T' - go to move player\n");
    printf("   's' or 'S' - go to spin board\n");

   glutMainLoop();
   return 0;
}
