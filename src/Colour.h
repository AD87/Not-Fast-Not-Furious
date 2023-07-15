#pragma once

class Colour{
public:
	Colour();
	Colour(float _r, float _g, float _b, float _a = 1.0f);

	void set(float _r, float _g, float _b, float _a = 1.0f);
	float* toArray();

	float r;
	float g;
	float b;
	float a;
};