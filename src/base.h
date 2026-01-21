#pragma once

#include <stdbool.h>
#include <stdint.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

#define ABS(a) ((a) < 0 ? -(a) : (a))

#define U8(N) ((uint8_t)(0xFF&(N)))

#define RGB(R, G, B) (0xFF000000|U8(B)<<16|U8(G)<<8|U8(R))
#define RGBA(R, G, B, A) (U8(A)<<24|U8(B)<<16|U8(G)<<8|U8(R))

typedef struct {
	int32_t x;
	int32_t y;
} vec2i;

typedef struct {
	uint32_t x;
	uint32_t y;
} vec2u;

typedef struct {
	float x;
	float y;
} vec2f;

typedef struct {
	float x;
	float y;
	float z;
} vec3f;

