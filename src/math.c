#include "math.h"

vec3f rotate_xz(vec3f v, float theta) {
	const float c = cos(theta);
	const float s = sin(theta);

	return (vec3f){
		.x = v.x * c - v.z * s,
		.y = v.y,
		.z = v.x * s + v.z * c,
	};
}

vec3f rotate_yz(vec3f v, float theta) {
	const float c = cos(theta);
	const float s = sin(theta);

	return (vec3f){
		.x = v.x,
		.y = v.y * c - v.z * s,
		.z = v.y * s + v.z * c,
	};
}

vec3f rotate_xy(vec3f v, float theta) {
	const float c = cos(theta);
	const float s = sin(theta);

	return (vec3f){
		.x = v.x * c - v.y * s,
		.y = v.x * s + v.y * c,
		.z = v.z,
	};
}
