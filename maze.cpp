#include <vector>
#include <cstdlib>
#include <ctime>
#include "graphics.h"
#include "maze.h"
#include "glut.h"

Cell::Cell()
{
	left = top = right = bottom = true;
	visited = false;
}
void Cell::Draw2d(int x, int y)
{
	glColor3d(0, 0, 0);
	if (left)
		DrawLine(x, y, x, y + 1);
	if (top)
		DrawLine(x, y + 1, x + 1, y + 1);
	if (right)
		DrawLine(x + 1, y + 1, x + 1, y);
	if (bottom)
		DrawLine(x + 1, y, x, y);
}


void Cell::Draw3d(int i, int j) {
	if (left) {
		/*unsigned char r = (i * 78456 + j * 11459) % 256;
		unsigned char g = (i * 98572 + j * 24657) % 256;
		unsigned char b = (i * 14978 + j * 33645) % 256;
		glColor3ub(r, g, b);
		*/
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texName[0]);
		glBegin(GL_QUADS);
		glTexCoord2f(0, 3); glVertex3d(i, j, 0);
		glTexCoord2f(3, 3); glVertex3d(i, j + 1, 0);
		glTexCoord2f(3, 0); glVertex3d(i, j + 1, 1);
		glTexCoord2f(0, 0); glVertex3d(i, j, 1);
		glEnd();
	}
	if (bottom) {
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texName[1]);
		glBegin(GL_QUADS);
		glTexCoord2f(0, 1); glVertex3d(i, j, 0);
		glTexCoord2f(1, 1); glVertex3d(i+1, j, 0);
		glTexCoord2f(1, 0); glVertex3d(i+1, j, 1);
		glTexCoord2f(0, 0); glVertex3d(i, j, 1);
		glEnd();
	}

	if (right && i == WIDTH - 1) {
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texName[2]);
		glBegin(GL_QUADS);
		glTexCoord2f(0, 1); glVertex3d(i+1, j, 0);
		glTexCoord2f(1, 1); glVertex3d(i + 1, j+1, 0);
		glTexCoord2f(1, 0); glVertex3d(i + 1, j+1, 1);
		glTexCoord2f(0, 0); glVertex3d(i+1, j, 1);
		glEnd();

	}

	if (top && j == HEIGHT - 1) {
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texName[2]);
		glBegin(GL_QUADS);
		glTexCoord2f(0, 3); glVertex3d(i, j+1, 0);
		glTexCoord2f(3, 3); glVertex3d(i + 1, j + 1, 0);
		glTexCoord2f(3, 0); glVertex3d(i + 1, j + 1, 1);
		glTexCoord2f(0, 0); glVertex3d(i, j+1, 1);
		glEnd();

	}
}


Maze::Maze()
{

}

int Maze::getB() {
	return mb;
}
int Maze::getT() {
	return mt;
}

void Maze::RemoveWalls()
{
	srand(time(NULL));
	RemoveWallsR(0, 0);

	// Remove top and bottom wall

	int r = rand() % WIDTH;
	cells[r][0].bottom = false;
	mb = r;
	int r2 = rand() % WIDTH;
	cells[r2][HEIGHT-1].top = false;
	mt = r2;

}

void Maze::RemoveWallsR(int i, int j)
{
	cells[i][j].visited = true;

	while (true)
	{
		// record legal possibilitites between LEFT, UP, RIGHT, DOWN
		enum MOVES { LEFT, UP, RIGHT, DOWN };
		std::vector<MOVES> moves;

		// check for a legal LEFT move
		if (i - 1 >= 0 && !cells[i - 1][j].visited)
		{
			moves.push_back(LEFT);
		}
		if (i + 1 < WIDTH && !cells[i + 1][j].visited) {
			moves.push_back(RIGHT);
		}
		if (j - 1 >= 0 && !cells[i][j - 1].visited) {
			moves.push_back(DOWN);
		}

		if (j + 1 < HEIGHT && !cells[i][j + 1].visited) {
			moves.push_back(UP);
		}

		if (moves.size() == 0)
		{
			return;
		}

		int r = rand() % moves.size();

		if (moves[r] == LEFT)
		{
			cells[i][j].left = false;
			cells[i - 1][j].right = false;
			RemoveWallsR(i - 1, j);
		}
		// Likewise for other 3 directions
		if (moves[r] == RIGHT) {
			cells[i][j].right = false;
			cells[i + 1][j].left = false;
			RemoveWallsR(i + 1, j);
		}

		if (moves[r] == DOWN) {
			cells[i][j].bottom = false;
			cells[i][j - 1].top = false;
			RemoveWallsR(i, j - 1);
		}

		if (moves[r] == UP) {
			cells[i][j].top = false;
			cells[i][j + 1].bottom = false;
			RemoveWallsR(i, j + 1);
		}

	}

}
void Maze::Draw()
{
	if (current_view == top_view)
	{
		for (int i = 0; i < WIDTH; i++)
			for (int j = 0; j < HEIGHT; j++)
				cells[i][j].Draw2d(i, j);
	}
	else
	{
		for (int i = 0; i < WIDTH; i++)
			for (int j = 0; j < HEIGHT; j++)
				cells[i][j].Draw3d(i, j);
	}
	
}

bool Maze::isSafe(double x, double y, double radius)
{
	int i = (int)x;
	int j = (int)y;

	double xoffset = x - i;
	double yoffset = y - j;

	if (cells[i][j].right && xoffset + radius > 1.0) {

		return false;
	}

	if (cells[i][j].left && xoffset - radius < 0.0) {

		return false;
	}

	if (cells[i][j].top && yoffset + radius > 1.0) {
		return false;
	}

	if (cells[i][j].bottom && yoffset - radius < 0.0) {
		return false;
	}

	//TODO add logic for other three walls


	//Corner logic
	if (xoffset + radius > 1.0 && yoffset + radius > 1.0) {
		return false;

	}

	if (xoffset + radius > 1.0 && yoffset - radius < 0) {
		return false;
	}

	if (xoffset - radius < 0 && yoffset - radius < 0) {
		return false;

	}

	if (xoffset - radius < 0 && yoffset + radius > 1.0) {
		return false;
	}

	return true;
}
