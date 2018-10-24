#ifndef UI1_h
#define UI1_h

#include "UIBase.h"
#include <SDL.h>

#define NUM_BODIES 1
class UI1 : public UIBase
{
private:
	SDL_Window * window;// window 
	SDL_Event * event_; // events 
	class Body* body[NUM_BODIES]; // body array of bodies 
	float healthWidth, player2HTop, player2HBottem, healthHeight; // has all the components for the rectanges for the life 
	const float maxHealth = 400; // maxiume size for the life 
	int r, g, b, r2, g2, b2; // colors for the life bars labled for RGB 
	void updateHealthColor(); // updates the health bar color
public:
	UI1(SDL_Window* SDLwindow);
	~UI1();
	bool OnCreate();
	void Update(const float time);
	void Render(SDL_Surface * surface);
	void HandleEvents(const SDL_Event&event);
};


#endif // !UI1_h
