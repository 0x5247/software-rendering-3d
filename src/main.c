#include "base.h"
#include "math.h"
#include "frame.h"
#include "renderer.h"
#include "model.h"

const vec3f cube_vs[] = {
	{ .x =  1.0f, .y =  1.0f, .z = 1.0f },
	{ .x = -1.0f, .y =  1.0f, .z = 1.0f },
	{ .x = -1.0f, .y = -1.0f, .z = 1.0f },
	{ .x =  1.0f, .y = -1.0f, .z = 1.0f },

	{ .x =  1.0f, .y =  1.0f, .z = -1.0f },
	{ .x = -1.0f, .y =  1.0f, .z = -1.0f },
	{ .x = -1.0f, .y = -1.0f, .z = -1.0f },
	{ .x =  1.0f, .y = -1.0f, .z = -1.0f },
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

			a.x /= 5;
			a.y /= 5;
			a.z /= 5;

			b.x /= 5;
			b.y /= 5;
			b.z /= 5;

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

		a.x /= 5;
		a.y /= 5;
		a.z /= 5;

		b.x /= 5;
		b.y /= 5;
		b.z /= 5;

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

float angle = 0.0f;
float dz = 5.0f;

float o = 0.0f;

void update(const float dt) {
	angle += (0.5f * PI) * dt;

	o += (FS_LEN / 15.0f) * dt;

	for (uint32_t idx = 0; idx < FRAME_WIDTH*FRAME_HEIGHT; idx += 1) {
		frame_buffer[0][idx] = RGBA(0, 0, 0, 0);
	}

	drawCube(1.5f, -1.5f, 6.0f, angle * 2.0f, RGB(0, 255, 0));

	for (uint16_t i = 0, fs_idx = 0, len = MIN(FS_LEN, (uint16_t)o); i < sizeof(fs)/sizeof(fs[0]) && fs_idx < len; i += fs[i] + 1, fs_idx += 1) {
		vec3f a;
		vec3f b;

		uint16_t j = i + 1;

		uint32_t color = RGB(255, 63, 127);

		if (fs_idx == (uint16_t)o - 1) {
			color = RGB(0,255, 0);
		} else if (fs_idx < 76) {
			color = RGB(63, 127, 255);
		} else if (fs_idx > 479) {
			color = RGB(190, 190, 190);
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
		//print_u16(fs_idx, 0); // 869
	}

	frame_buffer[0][0] = 0xFF0000FF;
	frame_buffer[0][1] = 0xFF00FF00;
	frame_buffer[0][2] = 0xFFFF0000;
}


