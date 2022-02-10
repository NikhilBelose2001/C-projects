#include<iostream>
#include<time.h>
#include<cstdlib>
#include<windows.h>
#include<gl/glut.h>

using namespace std;

int width = 102, height = 102;
int* p = new int[height * width];
int* q = new int[height * width];

void gol()
{
	//Adding game rules
	for (int k = 0; k < (height * width); k++)
	{
		int cnt = 0;
		if (k / width != 0 && k / width != (height - 1) && k % width != 0 && k % width != (width - 1))
		{
			int nbr[] = { p[k - 1], p[k + 1], p[k + width], p[k + width + 1], p[k + width - 1], p[k - width], p[k - width - 1], p[k - width + 1] };
			for (int l = 0; l < 8; l++)
			{
				if (nbr[l] == 1)
					cnt++;
			}
			if (p[k] == 1)
			{
				if (cnt < 2 || cnt > 3)
					q[k] = 0;
				else
					q[k] = 1;
			}
			else
			{
				if (cnt == 3)
					q[k] = 1;
				else
					q[k] = 0;
			}
		}
	}

		for (int i = 0; i < height * width; i++)
		{
			p[i] = q[i];
		}
}

void init()
{
	glClearColor(0, 0, 0, 1);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0, 1000, 1000, 0);
}

void drawSquare(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat x3, GLfloat y3, GLfloat x4, GLfloat y4, int a)
{
	if (a == 1)
		glColor3f(0, 0, 0);
	else
		glColor3f(1, 1, 1);

	glBegin(GL_POLYGON);
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glVertex2f(x3, y3);
	glVertex2f(x4, y4);
	glEnd();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	int i = 0;
	GLfloat x = 0, y = 0;
	float j = 1000.00 / width;
	for (x = 0; x < height; x++)
	{
		for (y = 0; y < width; y++)
		{
			drawSquare(x * j, y * j + j, x * j + j, y * j + j, x * j + j, y * j, x * j, y * j, p[i]);
			i++;
		}
	}

	glutSwapBuffers();
}

void time1(int)
{
	gol();
	glutPostRedisplay();
	glutTimerFunc(1000 / 24, time1, 0);
}

int main(int agrc, char** argv)
{
	int i, position;

	for (i = 0; i < height * width; i++)
	{
		p[i] = 0;
	}

	srand(time(0));
	for (i = 0; i < (height - 2) * (width - 2) / 2.5; i++)
	{
		position = rand() % (height * width);
		if (position / width == 0 || position / width == (height - 1) || position % width == 0 || position % width == (width - 1) || p[position] == 1)
		{
			--i;
		}
		else
		{
			p[position] = 1;
		}
	}

	glutInit(&agrc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowPosition(200, 0);
	glutInitWindowSize(1000, 1000);
	glutCreateWindow("Game of Life");

	init();

	glutDisplayFunc(display);
	glutTimerFunc(1000, time1, 0);

	glutMainLoop();

	return 0;
}