#pragma once

#define PI 3.14159265358979323846264338327

#define RAD2DEG(a) ((a) * (180.0f/PI))
#define DEG2RAD(a) ((a) * (PI/180.0f))

extern float sin(float);
extern float cos(float);

vec3f rotate_xz(vec3f v, float theta);
vec3f rotate_yz(vec3f v, float theta);
vec3f rotate_xy(vec3f v, float theta);
