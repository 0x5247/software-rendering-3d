#pragma once

#include "base.h"

void fillRect(int32_t x, int32_t y, uint32_t size_x, uint32_t size_y, uint32_t col);
void putPoint(vec2i p, uint32_t col);
void drawLinef(vec2f p, vec2f p1, uint32_t col);
void drawLine(vec2i p, vec2i p1, uint32_t col);
