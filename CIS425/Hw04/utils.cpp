#include "utils.h"
#include <cmath>

float degToRad(int angInDeg){
	return PI * angInDeg / 180;
}

void incAng(int& angInDeg){
	angInDeg = (angInDeg + 5) % 360;
}

void decAng(int& angInDeg){
	angInDeg = (angInDeg - 5) % 360;
}

float cosDiffAng(float u[], float v[], int length){
	float answer = 0;
	float norm_u_2 = 0;
	float norm_v_2 = 0;
	for (int i = 0; i < length; i++){
		answer += u[i] * v[i];
		norm_u_2 += u[i] * u[i];
		norm_v_2 += v[i] * v[i];
	}
	answer = answer / sqrt(norm_u_2*norm_v_2);
	return answer;
}