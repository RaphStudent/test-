#ifndef Assignment3_H
#define Assignment3_H
#define NUM_BODIES 5
#include "MMath.h"
#include "Scene.h"
#include <SDL.h>
#include "Collider.h"
using namespace MATH;
class Assignment3 : public Scene {
private:
	SDL_Window *window;
	Matrix4 projectionMatrix;
	class Body* body[NUM_BODIES];
	float elapsedTime;
	bool isHit;
	long frameCount;
	bool stopper;
	SDL_Event event_;
public:
	Assignment3(SDL_Window* sdlWindow);
	~Assignment3();
	bool OnCreate();
	void OnDestroy();
	void Update(const float time);
	void Render();
	void HandleEvents(const SDL_Event&event);
};
#endif
