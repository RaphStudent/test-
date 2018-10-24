#ifndef UI2_H
#define UI2_h
#include "UIBase.h"
#include <SDL.H>

#define NUM_BODIES 1
class UI2: public UIBase
{
private:
	SDL_Window * window; // sdl window 
	SDL_Event * event_; // events for events manager 
	float timewidth; // float for time bar 
	class Body* body[NUM_BODIES]; // body to hold images 
	void timeRefresh(); // to refesh ui timer 
	const float maxTime = 510; // max time for the time ui 
public:
	UI2(SDL_Window* SDLwindow);
	~UI2();
	bool OnCreate();
	void Update(const float time);
	void Render();
	void HandleEvents(const SDL_Event&event);
};

#endif // !UI2_H