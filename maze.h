#pragma once

const int WIDTH = 6;
const int HEIGHT = 5;

struct Cell
{
	Cell();
	void Draw2d(int x, int y);
	void Draw3d(int i, int j);
	bool left, top, right, bottom;
	bool visited;
};

class Maze
{
public:
	
	Maze();
	void RemoveWalls();
	void RemoveWallsR(int i, int j);
	void Draw();
	bool isSafe(double x, double y, double radius);

	int getB();
	int getT();

private:
	Cell cells[WIDTH][HEIGHT];
	int mb, mt;
};