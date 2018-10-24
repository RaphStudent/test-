#include "GameManager.h"
#include "Window.h"
#include "Timer.h"
#include "Assignment1.h"
#include "Assignment2.h"
#include "Assignment3.h"
#include "UI1.h" 
#include "UI2.h"
#include <iostream>
#include <memory>
using namespace std;
GameManager::GameManager() {
	timer = nullptr;
	isRunning = true;
	currentScene = nullptr;
	//currentUI = nullptr;
	state = false;
}

/// In this OnCreate() method, fuction, subroutine, whatever the word, 
bool GameManager::OnCreate() {
	const int SCREEN_WIDTH = 1024;
	const int SCREEN_HEIGHT = 780;
	ptr = new Window(SCREEN_WIDTH, SCREEN_HEIGHT); // creates window pointer 
	if (ptr == nullptr) { // failure checks 
		OnDestroy();
		return false;
	}
	if (ptr->OnCreate() == false) {
		OnDestroy();
		return false;
	}
	timer = new Timer(); // creates timer
	if (timer == nullptr) {  // failure checks 
		OnDestroy();
		return false;
	}
	// scene loader 
	currentScene = new Assignment1(ptr->GetSDL_Window());
	//failure checks 
	if (currentScene == nullptr) {
		OnDestroy();
		return false;
	}
	if (currentScene->OnCreate() == false) {
		OnDestroy();
		return false;
	}
	// UI1 Loader
	firstUI = new UI1(ptr->GetSDL_Window());
	//failure checks 
	if (firstUI == nullptr) {
		OnDestroy();
		return false;
	}
	if (firstUI->OnCreate() == false) {
		OnDestroy();
		return false;
	}
	//loads the the second UI
	secondUI = new UI2(ptr->GetSDL_Window());
	if (secondUI->OnCreate() == false) {
		OnDestroy();
		return false;
	}
	if (secondUI == nullptr) {
		OnDestroy();
		return false;
	}
	return true;
}

/// Here's the whole game
void GameManager::Run() { // the run function
	shared_ptr<UIBase> currentUI(firstUI); // current Scene smart pointer 
	shared_ptr<UIBase> nextUI(secondUI); // second UI to swap with 
	timer->Start(); // Start timer
	while (isRunning) {// check if the game is running 
		
		if (SDL_PollEvent(&event) != 0) {
			switch (event.type) { // switch case for determing the event type

			case (SDL_QUIT): // case for checing if escape is pressed 
				isRunning = false; // running is false 
				break; // breaks switch case 

			case(SDL_KEYDOWN): // case to check press down

				//if (event.key.keysym.sym == SDLK_F4) {
				//	currentScene->OnDestroy();
				//	delete currentScene;
				//	//currentScene = new UI1(ptr -> GetSDL_Window());
				//	currentScene->OnCreate();
				//	printf("hit4");
				//}
				if (event.key.keysym.sym == SDLK_F3) { // event for press of f3 
					currentScene->OnDestroy(); // destroys the last scene 
					delete currentScene;
					currentScene = new Assignment3(ptr->GetSDL_Window());
					currentScene->OnCreate();
					printf("hit3");
				}
				if (event.key.keysym.sym == SDLK_F2) {
					currentScene->OnDestroy();
					delete currentScene;
					currentScene = nullptr;
					currentScene = new Assignment2(ptr->GetSDL_Window());
					currentScene->OnCreate();
					printf("hit2");
				}
				if (event.key.keysym.sym == SDLK_F1) {
					currentScene->OnDestroy();
					delete currentScene;
					currentScene = nullptr;
					currentScene = new Assignment1(ptr->GetSDL_Window());
					currentScene->OnCreate();
					printf("hit");
				}
				if (event.key.keysym.sym == SDLK_ESCAPE) {
					isRunning = false;
				}
				if (event.key.keysym.sym == SDLK_SPACE) {
					currentScene->HandleEvents(event);
				}
				if (event.key.keysym.sym == SDLK_0) { // switch things
					currentUI.swap(nextUI); // swaps the current UI with next UI, if more UI is in the system more swaps will be nessicary
				}
				currentUI->HandleEvents(event);// allows the UImanager to change based on key inputs the UI it's self will determine if it can be used on its own
				break;
				
			default:
				break;
			}
			
		}
		timer->UpdateFrameTicks();
		/*currentScene->Update(timer->GetDeltaTime());
		currentScene->Render();*/
		currentUI->Update(timer->GetDeltaTime()); // updates any events in the ui 
		currentUI->Render(); // renders the UI
		/// Keeep the event loop running at a proper rate
		SDL_Delay(timer->GetSleepTime(60)); ///60 frames per sec	
		}
	}

GameManager::~GameManager() {}

void GameManager::OnDestroy(){
	if (ptr) delete ptr;
	if (timer) delete timer;
	if (currentScene) delete currentScene;
}