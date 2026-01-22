#include "frame.h"
#include "renderer.h"

void fillRect(int32_t x, int32_t y, uint32_t size_x, uint32_t size_y, uint32_t col) {
	int32_t max_x;
	int32_t max_y;

	if (x < 0) {
		if ((int32_t)size_x < -x) return;
		size_x += x;
		x = 0;
	}

	if (y < 0) {
		if ((int32_t)size_y < -y) return;
		size_y += y;
		y = 0;
	}

	max_x = MIN(x + size_x, FRAME_WIDTH);
	max_y = MIN(y + size_y, FRAME_HEIGHT);

	for (; y < max_y; y += 1) {
		for (int32_t px = x; px < max_x; px += 1) {
			frame_buffer[y][px] = col;
		}
	}
}

void putPoint(vec2i p, uint32_t col) {
	fillRect(p.x - 4, p.y - 4, 8, 8, col);
}

void drawLinef(vec2f p, vec2f p1, uint32_t col) {
	float dx = p.x - p1.x;
	float dy = p.y - p1.y;

	int32_t steps = MAX(ABS(dx), ABS(dy));

	float x_inc = dx/steps;
	float y_inc = dy/steps;

	p.x = p1.x;
	p.y = p1.y;

	for (int32_t i = 0; i < steps; i += 1, p.x += x_inc, p.y += y_inc) {
		if (p.x < 0 || p.y < 0 || FRAME_WIDTH < p.x || FRAME_HEIGHT < p.y) continue;

		frame_buffer[(uint32_t)p.y][(uint32_t)p.x] = col;
	}
}
