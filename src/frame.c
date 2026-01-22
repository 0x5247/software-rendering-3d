#include "frame.h"

uint32_t frame_buffer[FRAME_HEIGHT][FRAME_WIDTH];

uint32_t frameSize(void) { return sizeof frame_buffer; }

uint32_t frameWidth(void) { return FRAME_WIDTH; }

uint32_t frameHeight(void) { return FRAME_HEIGHT; }

vec2i screen(vec2f p) {
	return (vec2i){
		.x = ((p.x + 1) / 2) * FRAME_WIDTH,
		.y = (1 - ((p.y + 1) / 2)) * FRAME_HEIGHT,
	};
}

vec2f screenf(vec2f p) {
	return (vec2f){
		.x = ((p.x + 1) / 2) * FRAME_WIDTH,
		.y = (1 - ((p.y + 1) / 2)) * FRAME_HEIGHT,
	};
}

vec2f project(vec3f p) {
	// ref: https://github.com/tsoding/formula/issues/4
	const float focal = 2.5f;

	return (vec2f){
		.x = (p.x / p.z) * focal,
		.y = (p.y / p.z) * focal,
	};
}
