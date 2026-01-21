#pragma once

#include "base.h"

#define FRAME_WIDTH 500
#define FRAME_HEIGHT 500

extern uint32_t frame_buffer[FRAME_HEIGHT][FRAME_WIDTH];

uint32_t frameSize(void);
uint32_t frameWidth(void);
uint32_t frameHeight(void);

vec2i screen(vec2f p);
vec2f screenf(vec2f p);
vec2f project(vec3f p);
