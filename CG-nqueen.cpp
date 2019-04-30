#include <iostream>
#include <GL/gl.h>
#include <GL/glut.h>
using namespace std;
char chessboard[100][100] = {};
int queens;
float W; float H;
int savingposition[100][2] = {};
void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
}
bool checking(int row, int column) {
	for (int i = 0; i< queens; i++) {
		for (int j = 0; j < queens; j++) {
			if ((j + i == column + row || column - row == j - i || i == row || j == column) && chessboard[i][j] == 'Q')
				return false;
		}
	}
	return true;
}
void removeflag(int row)
{
	for (int i = 0; i < queens; i++)
	{
		chessboard[row][i] = '0';

	}
}
void backtracking(void)
{
	for (int row = 0; row < queens; row++)
	{
		for (int column = 0; column <queens; column++) {
			if (checking(row, column) && chessboard[row][column] != '-') {
				chessboard[row][column] = 'Q'; removeflag(row + 1);
				savingposition[row][0] = row;
				savingposition[row][1] = column;
				row++; column = -1;
				if (row == queens) break;
			}
			else if (column == queens - 1 && chessboard[row][column] != 'Q')
			{
				row--;
				column = savingposition[row][1];
				//cout << row << " " << column << endl;
				chessboard[row][column] = '-';
				column = 0;
			}
		}
	}
}
void displaytable(void)
{
	for (int i = 0; i< queens; i++) {
		for (int j = 0; j < queens; j++) {
			if (chessboard[i][j] != 'Q')
				cout << '.';
			else
				cout << chessboard[i][j];
		}
		cout << endl;
	}
}
void displayboard()
{
	glTranslatef(25, H - 25, 0.0);
	glPushMatrix();
	for (int i = 0; i<queens; i++) {
		glPushMatrix();
		for (int j = 0; j < queens; j++) {
			if ((i + j) % 2 == 0) glColor3f(1.0, 1.0, 1.0); else glColor3f(0.0, 0.0, 0.0);
			glPushMatrix(); glScalef(50.0, 50.0, 0.0);
			glutSolidCube(1);
			if (chessboard[i][j] == 'Q') {
				glPushMatrix();
				glColor3f(1, 0, 0);
				glutSolidSphere(0.4, 50, 50); glPopMatrix();
			}
			glPopMatrix();
			glTranslatef(50.0, 0.0, 0.0);
		}
		glPopMatrix();
		glTranslatef(0.0, -50.0, 0.0);
	}
	glPopMatrix();
}
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();
	displayboard();
	glPopMatrix();
	displaytable();
	glutSwapBuffers();
}
void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, W, 0, H);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();//important: last line must be glLoadIdentity() for coloring with openGL
					 //glTranslatef (.0, .0, -5.); //do not translate at all if glLoadIdentity() is used
}
void mouse(int button, int state, int x, int y) //mouse function...
{
	int row, column;
	switch (button) {
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN)
		{
			row = (y / 50);
			column = (x / 50);
			if (checking(row, column))
				chessboard[row][column] = 'Q';
		}
		//cout << "X -->" << x<< "Y-->" << y << endl;
		glutPostRedisplay();
		break;
	case GLUT_RIGHT_BUTTON:
		if (state == GLUT_DOWN)
		{
			row = (y / 50);
			column = (x / 50);
			chessboard[row][column] = ' ';
		}
		//cout << "X -->" << x<< "Y-->" << y << endl;
		//displaytable();
		glutPostRedisplay();

		break;
	}
}

int main(int argc, char **argv)
{
	int input;
	cout << "WELCOME TO N-QUEEN PROGRAM!!!" << endl;
	cout << "1. Show The Solution by Computer!!" << endl;
	cout << "2. Try to solve the puzzle" << endl;
	cout << "3. Exit!!!" << endl;
	cout << "Select the NUMBER from 1-3::";
	cin >> input;
	switch (input)
	{
	case 1:
		cout << "Please enter the number of the queens 1 to 100:" << endl;
		cin >> queens;
		backtracking(); break;
	case 2:
		cout << "What size of N queens do you want to play ?:" << endl;
		cin >> queens;
		cout << "Left Cick on the box to select!!\n Right click to deselect ";
		break;
	case 3:
		cout << "THANK YOU FOR PLAYING"; exit(0);
	default:
		cout << "WRONG INPUT";
		break;
	}
	W = 50 * queens;
	H = 50 * queens;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(W, H);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Chessboard");
	init();
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
}


