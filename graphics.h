#pragma once
double getTime();
void DrawLine(double x1, double y1, double x2, double y2);
enum viewtype { top_view, perspective_view, rat_view };
extern viewtype current_view;
extern unsigned int texName[];



