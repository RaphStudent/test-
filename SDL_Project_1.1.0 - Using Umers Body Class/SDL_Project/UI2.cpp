#include "UI2.h"
#include "Body.h"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>


UI2::UI2(SDL_Window* sdlwindow_)
{
	timewidth = 510; // max width of the time bar 
	window = sdlwindow_; // the window 
	for (int i = 0; i < NUM_BODIES; i++) // nulls all bodies in body;
	{
		body[i] = nullptr;
	}
}


UI2::~UI2(){}

void UI2::Render() {
	SDL_Surface * screenSurface = SDL_GetWindowSurface(window); // window surface
	SDL_FillRect(screenSurface, nullptr, SDL_MapRGB(screenSurface->format, 25, 25, 25));// makes the backround grey
	SDL_Rect imageRectangle = { 0,0,1024,720 };// image rectangle 
	imageRectangle.h = body[0]->getImage()->h; // gets the height 
	imageRectangle.w = body[0]->getImage()->w;// and the width of the image a puts it to the image rectange

	SDL_BlitSurface(body[0]->getImage(), nullptr, screenSurface, &imageRectangle); // draws most of the ui 
	SDL_Rect time = { 256 , 665 ,timewidth ,30 }; // time in game;
	SDL_FillRect(screenSurface, &time, SDL_MapRGB(screenSurface->format, 25, 25, 118)); 
	SDL_UpdateWindowSurface(window); // updates window
}
void UI2::Update(const float time) { // updates events 
	timeRefresh();// refrehes time if 0 
	timewidth--; // reduces time by 1 each call in game manager
}
void UI2::HandleEvents(const SDL_Event &event_) { // would allow the UI to handle events if events we used in this UI specfically 

}
void UI2::timeRefresh() { // if the timer bar empties this refeshes back to maximum
	if (timewidth <= 0) {
		printf("out of time"); // debug;
		timewidth = maxTime;
	}
}
bool UI2::OnCreate() {
	int w, h;
	SDL_GetWindowSize(window, &w, &h);
	IMG_Init(IMG_INIT_PNG);
	body[0] = new Body("UI2.png", 0.0f, 0.0f, Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f));
	if (body[0] == nullptr) {
		return false;
	}
	return true;
}
