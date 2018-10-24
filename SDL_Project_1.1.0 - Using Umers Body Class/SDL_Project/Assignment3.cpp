#include "Assignment3.h"
#include "Body.h"
#include "Collider.h"
#include <SDL.h>
#include <SDL_image.h>

Assignment3::Assignment3(SDL_Window* sdlWindow_) {
	window = sdlWindow_;
	elapsedTime = 0.0f;
	frameCount = 0.0f;
	isHit = false;
	stopper = false;
	for (int i = 0; i < NUM_BODIES; i++)
	{
		body[i] = nullptr;
	}
}

Assignment3::~Assignment3() {
}

bool Assignment3::OnCreate() {
	int w, h;
	SDL_GetWindowSize(window, &w, &h);

	projectionMatrix = MMath::viewportNDC(w, h) * MMath::orthographic(0.0f, 30.0f, 0.0f, 15.0f, 0.0f, 1.0f);
	IMG_Init(IMG_INIT_PNG);

	body[0] = new Body("umer.png", 150.0f, 1.0f, Vec3(13.0f, 8.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f));
	if (body[0] == nullptr) {
		return false;
	}
	body[1] = new Body("scott2.png", 1.0f, 1.0f, Vec3(13.0f, 16.0f, 0.0f), Vec3(-1.0f, 0.0f, 0.0f), Vec3(-0.0, -0.0f, 0.0f));
	if (body[1] == nullptr) {
		return false;
	}
	body[2] = new Body("scott2.png", 1.0f, 1.0f, Vec3(5.0f, 8.0f, 0.0f), Vec3(0.0f, -1.0f, 0.0f), Vec3(-0.0, -0.0f, 0.0f));
	if (body[2] == nullptr) {
		return false;
	}
	body[3] = new Body("unknown.png", 1.0f, 1.0f, Vec3(13.0f,0.0f, 0.0f), Vec3(1.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f));
	if (body[3] == nullptr) {
		return false;
	}
	body[4] = new Body("unknown.png", 1.0f, 1.0f, Vec3(2.0f, 8.0f, 0.0f), Vec3(0.0f, 1.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f));
	if (body[4] == nullptr) {
		return false;
	}
	return true;
}

void Assignment3::OnDestroy() {
	IMG_Quit();
	for (int i = 0; i < NUM_BODIES; i++) {
		if (body[i]) {
			delete body[i];
			body[i] = nullptr;
		}
	}
}

void Assignment3::Update(const float time) {
	if (stopper) {
		elapsedTime += time;
		frameCount++;
		for (int i = 0; i < NUM_BODIES; ++i) {
			for (int j = i+1; j < NUM_BODIES; ++j) {
				isHit = Collider::CheckCollision(body[i], body[j]);

				if (isHit) {
					Collider::HandleCollision(body[i], body[j], 0.5);
					body[i]->Update(time, false, true);
				}
				else if (!isHit) {
					// (body[i]->pos.y < 1.5f || body[i]->pos.y > 20.0f || body[i]->pos.x < 1.0f || body[i]->pos.x > 20.0f) {VMath::reflect()}
				}
			}
			for (int i = 0; i < NUM_BODIES; i++) {
				if (i == 0) {}
				else {
					Vec3 netForce = body[i]->StarForce();
					body[i]->ApplyForce(netForce);
					if (body) body[i]->Update(time, false, true);
				}
			}
		}
	}
}

void Assignment3::Render() {
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

void Assignment3::HandleEvents(const SDL_Event &event_) {
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