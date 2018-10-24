#include "Assignment1.h"
#include "Body.h"
#include <SDL.h>
#include <SDL_image.h>

Assignment1::Assignment1(SDL_Window* sdlWindow_) {
	window = sdlWindow_;
	elapsedTime = 0.0f;
	frameCount = 0.0f;
	stopper = true; 
	for (int i = 0; i < NUM_BODIES; i++)
	{
		body[i] = nullptr;
	}
}

Assignment1::~Assignment1(){
}

bool Assignment1::OnCreate() {
	int w, h;
	SDL_GetWindowSize(window,&w,&h);
	
	projectionMatrix = MMath::viewportNDC(w,h) * MMath::orthographic(0.0f, 30.0f, 0.0f, 15.0f, 0.0f, 1.0f) ;
	IMG_Init(IMG_INIT_PNG);

	body[0] = new Body("umer.png", 25.0f, 5.0f, Vec3(0.0f, 6.5f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(10.0f, 0.0f, 0.0f));
	if (body[0] == nullptr) {
			return false;	
	}
	body[1] = new Body("unknown.png", 20.0f, 5.0f, Vec3(0.0f, 3.5f, 0.0f), Vec3(0.0f, 2.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f));
	if (body[1] == nullptr) {
			return false;
		}
	return true;
}

void Assignment1::OnDestroy() {
	IMG_Quit();
	for (int i = 0; i < NUM_BODIES; i++){
		if (body[i]) {
			delete body[i];
			body[i] = nullptr;
		}
	}
}

void Assignment1::Update(const float time) {
		if (stopper) {
			elapsedTime += time;
			frameCount++;
			if (frameCount == 0) {
				body[0]->ApplyForce(Vec3(1000.0f, 0.0f, 0.0f));
			}

			for (int i = 0; i < NUM_BODIES; i++) {

				if (elapsedTime < 5.0f) {
					/// Accelerate for three seconds
					body[i]->ApplyForce(Vec3(400.0f, 0.0f, 0.0f));
				}
				if (elapsedTime > 14.0f) {
					/// Apply the brakes until it stops
					if (body[i]->vel.x > 0.0f) {
						body[i]->ApplyForce(Vec3(-600.0f, 0.0f, 0.0f));
					}
					else {
						body[i]->vel.x = 0.0f;

					}
				}
				if (body) body[i]->Update(time, true,false);
		}

	}
}

void Assignment1::Render() {
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

void Assignment1::HandleEvents(const SDL_Event &event_) {
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