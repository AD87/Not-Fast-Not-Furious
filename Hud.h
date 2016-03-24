#pragma once

class Hud{
public:
	virtual ~Hud() = 0{}
	virtual void update() = 0;
	virtual void draw() = 0;
protected:
	void begin();
	void end();
};