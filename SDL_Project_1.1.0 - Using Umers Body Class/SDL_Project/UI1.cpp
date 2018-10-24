#include "UI1.h"
#include "Body.h"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

UI1::UI1(SDL_Window * sdlwindow_){
	window = sdlwindow_;
	for (int i = 0; i < NUM_BODIES; i++) // loads the bodies if there was need for more elements they can be created here 
	{
		body[i] = nullptr;
	}
	// player health bars
	healthWidth = 400;
	player2HTop = 400;
	player2HBottem = 400;
	healthHeight = 40;
	// colors 
	r = 0;
	g = 225;
	b = 0;
	r2 = 0;
	g2 = 225;
	b2 = 0;
}


UI1::~UI1()
{
}

bool UI1::OnCreate() {
	int w, h;
	SDL_GetWindowSize(window, &w, &h);
	IMG_Init(IMG_INIT_PNG);
	body[0] = new Body("UI1.png", 0.0f, 0.0f, Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f));
	if (body[0] == nullptr) {
		return false;
	}
	return true;
}

void UI1::Update(const float time) {
	updateHealthColor(); // Updates colors
	//if (healthWidth > 0) {
	//	healthWidth -= 4;
	//	player2HTop += 4;
	//	player2HBottem -= 4;
	//}
	//else if (healthWidth <= 0) {
	//	healthWidth = maxHealth;
	//	player2HBottem = maxHealth;
	//	player2HTop = maxHealth;
	//}
}

void UI1::Render(SDL_Surface * surface) { // renders image to screen
		SDL_FillRect(surface, nullptr, SDL_MapRGB(surface->format, 0xff, 0xff, 0xff));// makes screen white
		SDL_Rect imageRectangle = { 0,0,1024,720 }; // new rectange for the image
		for (int i = 0; i < NUM_BODIES; i++) { // this would allow mulitpe UI bojects to be used however with the way it's set up now there will be some tinkering done to allow muliple images to be rendered
			imageRectangle.h = body[i]->getImage()->h; // creates the height and 
			imageRectangle.w = body[i]->getImage()->w; // width based on the images size
			SDL_BlitSurface(body[i]->getImage(), nullptr, surface, &imageRectangle); // puts image on screen 
		}
		Uint32 player1Color = SDL_MapRGB(surface->format, r, g, b); // player 1 color
		Uint32 player2Color = SDL_MapRGB(surface->format, r2, g2, b2); // player 2 color

		SDL_Rect healthBar1 = { 20 , 40 , healthWidth , healthHeight}; // player one health bar
		SDL_FillRect(surface, &healthBar1, player1Color);

		SDL_Rect healthBar2 = { player2HTop +184 , 40 , player2HBottem , healthHeight }; // player two health bar 
		SDL_FillRect(surface, &healthBar2, player2Color);

		SDL_UpdateWindowSurface(window); // updates window
}

void UI1::updateHealthColor() { // this changed the color of the rectangles based on their orginal size 
	if (healthWidth <= maxHealth / 4) {
		r = 225;
		g = 0;
	}
	else if (healthWidth <= maxHealth / 2) {
		r = 225;
		g = 165;
	}
	else {
		r = 0;
		g = 225;
	}
	if (player2HBottem <= maxHealth / 4) {
		r2 = 225;
		g2 = 0;
	}
	else if (player2HBottem <= maxHealth / 2) {
		r2 = 225;
		g2 = 165;
	}
	else {
		r2 = 0;
		g2 = 225;
	}
}
void UI1::HandleEvents(const SDL_Event &event_) { // events handler
	switch (event_.type) {
	case(SDL_KEYDOWN):
		if (event_.key.keysym.sym == SDLK_h) { // if H is inputed the health bars will decrease 
			
			if (healthWidth > 0) {
				//printf("hit");
				healthWidth -=4;
				player2HTop += 4;
				player2HBottem -= 4;
			}
			else if (healthWidth <= 0) { // if less than 0 reset to orginal max
				healthWidth = maxHealth;
				player2HBottem = maxHealth;
				player2HTop = maxHealth;
			}
		}
	}
}