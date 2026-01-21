#include "base.h"
#include "math.h"
#include "frame.h"
#include "renderer.h"

extern const vec3f vs[937];
extern const uint16_t fs[4364];

const vec3f cube_vs[] = {
	{ .x =  0.3f, .y =  0.3f, .z = 0.3f },
	{ .x = -0.3f, .y =  0.3f, .z = 0.3f },
	{ .x = -0.3f, .y = -0.3f, .z = 0.3f },
	{ .x =  0.3f, .y = -0.3f, .z = 0.3f },

	{ .x =  0.3f, .y =  0.3f, .z = -0.3f },
	{ .x = -0.3f, .y =  0.3f, .z = -0.3f },
	{ .x = -0.3f, .y = -0.3f, .z = -0.3f },
	{ .x =  0.3f, .y = -0.3f, .z = -0.3f },
};

// work around for lack of support for static arrays with different length
// length, faces...,
// length, faces...,
const uint16_t cube_fs[] = {
	4, 0, 1, 2, 3,
	2, 0, 4,
	2, 1, 5,
	2, 2, 6,
	2, 3, 7,
	4, 4, 5, 6, 7,
	0,
};

void drawCube(float dx, float dy, float dz, float angle, uint32_t color) {
	for (uint16_t i = 0; i < sizeof(cube_fs)/sizeof(cube_fs[0]); i += cube_fs[i] + 1) {
		vec3f a;
		vec3f b;

		uint16_t j = i + 1;

		for (; j < i + cube_fs[i]; j += 1) {
			a = cube_vs[cube_fs[j]];
			b = cube_vs[cube_fs[j+1]];

			a = rotate_xz(a, angle);
			b = rotate_xz(b, angle);
			a = rotate_xy(a, angle);
			b = rotate_xy(b, angle);
			a = rotate_yz(a, angle);
			b = rotate_yz(b, angle);

			a.x -= dx;
			b.x -= dx;
			a.y -= dy;
			b.y -= dy;
			a.z += dz;
			b.z += dz;

			drawLinef(screenf(project(a)), screenf(project(b)), color);
		}

		if (cube_fs[i] <= 2) continue;

		a = cube_vs[cube_fs[i+1]];
		b = cube_vs[cube_fs[j]];

		a = rotate_xz(a, angle);
		b = rotate_xz(b, angle);
		a = rotate_xy(a, angle);
		b = rotate_xy(b, angle);
		a = rotate_yz(a, angle);
		b = rotate_yz(b, angle);

		a.x -= dx;
		b.x -= dx;
		a.y -= dy;
		b.y -= dy;
		a.z += dz;
		b.z += dz;

		drawLinef(screenf(project(a)), screenf(project(b)), color);
	}
}

float angle = -DEG2RAD(90);
float dz = 4.0f;

void update(const float dt) {
	angle += 1.5f * PI * dt;

	for (uint32_t idx = 0; idx < FRAME_WIDTH*FRAME_HEIGHT; idx += 1) {
		frame_buffer[0][idx] = RGBA(0, 0, 0, 0);
	}

	drawCube( 1.8f, -1.5f, 6.0f,                angle, RGB(255, 255,   0));
	drawCube( 1.8f,  1.5f, 6.0f, -angle + DEG2RAD(45), RGB(255,   0,   0));
	drawCube(-1.8f, -1.5f, 6.0f,               -angle, RGB(  0,   0, 255));
	drawCube(-1.8f,  1.5f, 6.0f,  angle + DEG2RAD(45), RGB(  0, 255,   0));

	for (uint16_t i = 0; i < sizeof(fs)/sizeof(fs[0]); i += fs[i] + 1) {
		vec3f a;
		vec3f b;

		uint16_t j = i + 1;

		uint32_t color = RGB(63, 127, 255);

		if (i > 2454) {
			color = RGB(190, 190, 190);
		} else if (i > 350) {
			color = RGB(255, 63, 127);
		}

		for (; j < i + fs[i]; j += 1) {
			a = vs[fs[j]];
			b = vs[fs[j+1]];

			a = rotate_xz(a, angle);
			b = rotate_xz(b, angle);

			a.z += dz;
			b.z += dz;

			drawLinef(screenf(project(a)), screenf(project(b)), color);
		}

		if (fs[i] <= 2) continue;

		// joining the first and last vertex indecies
		a = vs[fs[i+1]];
		b = vs[fs[j]];

		a = rotate_xz(a, angle);
		b = rotate_xz(b, angle);

		a.z += dz;
		b.z += dz;

		drawLinef(screenf(project(a)), screenf(project(b)), color);
	}

	frame_buffer[0][0] = 0xFF0000FF;
	frame_buffer[0][1] = 0xFF00FF00;
	frame_buffer[0][2] = 0xFFFF0000;
}

