#ifndef UIBASE_H
#define UIBASE_H
#include <SDL.h>
// Virtual class which all othe UI inherets from
class UIBase
{
public:
	virtual bool OnCreate() = 0;
	virtual void Update(const float time) = 0;
	virtual void Render() = 0;
	virtual void HandleEvents(const SDL_Event& event) = 0;
};
#endif // !UIBASE_H