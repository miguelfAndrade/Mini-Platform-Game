#pragma once

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

#define	WINDOW_SIZE_QUADRANT_X (WINDOW_WIDTH / 2)
#define WINDOW_SIZE_QUADRANT_Y (WINDOW_HEIGHT / 2)

enum ShapeType { SQUARE = 8, TRIANGLE = 6, REC_TRIANGLE = 6 };

struct Color {
	float red;
	float green;
	float blue;
	float alpha;
};

struct Point {
	float x;
	float y;
	float z;
};

