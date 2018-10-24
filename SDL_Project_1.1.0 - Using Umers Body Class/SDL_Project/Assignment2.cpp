#include "Assignment2.h"
#include "Body.h"
#include <SDL.h>
#include <SDL_image.h>

Assignment2::Assignment2(SDL_Window* sdlWindow_) {
	window = sdlWindow_;
	elapsedTime = 0.0f;
	frameCount = 0.0f;
	stopper = false;
	for (int i = 0; i < NUM_BODIES; i++)
	{
		body[i] = nullptr;
	}
}

Assignment2::~Assignment2() {
}

bool Assignment2::OnCreate() {
	int w, h;
	SDL_GetWindowSize(window, &w, &h);

	projectionMatrix = MMath::viewportNDC(w, h) * MMath::orthographic(0.0f, 30.0f, 0.0f, 15.0f, 0.0f, 1.0f);
	IMG_Init(IMG_INIT_PNG);

	body[0] = new Body("umer.png", 150.0f, 5.0f, Vec3(20.0f, 8.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f));
	if (body[0] == nullptr) {
		return false;
	}
	body[1] = new Body("scott2.png", 1.0f, 5.0f, Vec3(14.0f, 11.0f, 0.0f), Vec3(6.0f, -4.0f, 0.0f), Vec3(-40.0f, -0.0f, 0.0f));
	if (body[1] == nullptr) {
		return false;
	}
	body[2] = new Body("unknown.png", 100.0f, 5.0f, Vec3(5.0f, 8.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f));
	if (body[2] == nullptr) {
		return false;
	}
	return true;
}

void Assignment2::OnDestroy() {
	IMG_Quit();
	for (int i = 0; i < NUM_BODIES; i++) {
		if (body[i]) {
			delete body[i];
			body[i] = nullptr;
		}
	}
}

void Assignment2::Update(const float time) {
	if (stopper) {
		elapsedTime += time;
		frameCount++;

	
		Vec3 netForce = body[1]->PlanetForce();
		body[1]->ApplyForce(netForce); 
		if (body) body[1]->Update(time, false,false);
	}

}

void Assignment2::Render() {
	if (stopper) {
		SDL_Rect imageRectangle;
		SDL_Surface *screenSurface = SDL_GetWindowSurface(window);
		SDL_FillRect(screenSurface, nullptr, SDL_MapRGB(screenSurface->format, 0xff, 0xff, 0xff));
		for (int i = 0; i < NUM_BODIES; i++) {
			Vec3 screenCoords = projectionMatrix * body[i]->pos;
			imageRectangle.h = body[i]->getImage()->h;
			imageRectangle.w = body[i]->getImage()->w;
			imageRectangle.x = screenCoords.x; /// implicit type conversions BAD - probably causes a compiler warning
			imageRectangle.y = screenCoords.y; /// implicit type conversions BAD - probably causes a compiler warning


			SDL_BlitSurface(body[i]->getImage(), nullptr, screenSurface, &imageRectangle);

		}
		SDL_UpdateWindowSurface(window);
	}
}

void Assignment2::HandleEvents(const SDL_Event &event_) {
	switch (event_.type) {
	case SDL_KEYDOWN:
		if (event_.key.keysym.scancode == SDL_SCANCODE_SPACE) {
			printf("Key press detected\n");
			stopper = true;
		}
		break;

	default:
		//stopper = false;
		break;
	}
}