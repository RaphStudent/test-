#ifndef Assignment2_H
#define Assignment2_H

#include "MMath.h"
#include "Scene.h"

#include <SDL.h>

#define NUM_BODIES 3

using namespace MATH;
class Assignment2 : public Scene {
private:
	SDL_Window *window;
	Matrix4 projectionMatrix;
	class Body* body[NUM_BODIES];
	float elapsedTime;
	long frameCount;
	bool stopper;
	SDL_Event event_;
public:
	Assignment2(SDL_Window* sdlWindow);
	~Assignment2();
	bool OnCreate();
	void OnDestroy();
	void Update(const float time);
	void Render();
	void HandleEvents(const SDL_Event&event);
};

#endif
