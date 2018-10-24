#include "Body.h" 
#include <SDL_image.h>
#include "VMath.h"

Body::Body(char* imageName, float mass_, float rad_, Vec3 pos_, Vec3 vel_, Vec3 accel_) {
	mass = mass_;
	rad = rad_;
	pos.x = pos_.x;
	pos.y = pos_.y;
	pos.z = pos_.z;

	vel.x = vel_.x;
	vel.y = vel_.y;
	vel.z = vel_.z;

	accel.x = accel_.x;
	accel.y = accel_.y;
	accel.z = accel_.z;
	bodyImage = IMG_Load(imageName);
	if (bodyImage == nullptr) {
		/// What should we do?
	}

}

Body::~Body() {} /// There is really nothing to do here - yet!


void Body::Update(const float deltaTime, bool isFloor_, bool isContained_) {
	if (isFloor_) {
		pos.x += (vel.x * deltaTime) + (0.5f * accel.x * (deltaTime * deltaTime));
		pos.x += (vel.y * deltaTime) + (0.5f * (accel.y + -9.8f)* (deltaTime * deltaTime));
		pos.x += (vel.z * deltaTime) + (0.5f * accel.z * (deltaTime * deltaTime));
		pos.y += (vel.y * deltaTime) + (0.5f * accel.y * (deltaTime * deltaTime));
		vel.x += accel.x * deltaTime;
		vel.y += (accel.y + -9.8f)* deltaTime;
		vel.z += accel.z * deltaTime;
		/// Assuming all acceleration comes from an applied force - maybe not in the future - gravity!!
		accel.x = 0.0f;
		accel.y = 0.0f;
		accel.z = 0.0f;
		if (pos.y < 3.5f) { pos.y = 3.5f; }
	}
	else if (isContained_) {
		pos.x += (vel.x * deltaTime) + (0.5f * accel.x * (deltaTime * deltaTime));
		pos.x += (vel.y * deltaTime) + (0.5f * (accel.y)* (deltaTime * deltaTime));
		pos.x += (vel.z * deltaTime) + (0.5f * accel.z * (deltaTime * deltaTime));
		pos.y += (vel.y * deltaTime) + (0.5f * accel.y * (deltaTime * deltaTime));
		vel.x += accel.x * deltaTime;
		vel.y += (accel.y)* deltaTime;
		vel.z += accel.z * deltaTime;
		/// Assuming all acceleration comes from an applied force - maybe not in the future - gravity!!
		accel.x = 0.0f;
		accel.y = 0.0f;
		accel.z = 0.0f;
	}
	else {
		pos.x += (vel.x * deltaTime) + (0.5f * accel.x * (deltaTime * deltaTime));
		pos.x += (vel.y * deltaTime) + (0.5f * (accel.y)* (deltaTime * deltaTime));
		pos.x += (vel.z * deltaTime) + (0.5f * accel.z * (deltaTime * deltaTime));
		pos.y += (vel.y * deltaTime) + (0.5f * accel.y * (deltaTime * deltaTime));
		vel.x += accel.x * deltaTime;
		vel.y += (accel.y)* deltaTime;
		vel.z += accel.z * deltaTime;
		/// Assuming all acceleration comes from an applied force - maybe not in the future - gravity!!
		accel.x = 0.0f;
		accel.y = 0.0f;
		accel.z = 0.0f;
	}

}

void Body::ApplyForce(Vec3 force) {
	accel.x = force.x / mass;
	accel.y = force.y / mass;
	accel.z = force.z / mass;
}

//void Body::ColiderMaths(Body body1_, Body body2_, int E_) {
//	Vec3 normal1 = VMath::normalize(body1_.pos);
//	Vec3 normal2 = VMath::normalize(body2_.pos);
//	Vec3 V1p = VMath::dot(body1_.pos, normal1);
//	Vec3 V2p = VMath::dot(body2_.pos, normal2);
//	V1p = ((body1_.mass - E_*body2_.mass)*V1p) + (1 * E_ * body2_.mass * V2p) / body1_.mass + body2_.mass;
//	V2p = ((body2_.mass - E_*body1_.mass)*V2p) + (1 * E_ * body1_.mass * V1p) / body1_.mass + body2_.mass;
//	return(V1p + V2p);}
Vec3 Body::PlanetForce() {
	//Star1 math stuff
	float positionX = 5 - pos.x;
	float positionY = 8 - pos.y;
	float distance = sqrt((positionX*positionX) + (positionY*positionY));
	float magintude = (1 * mass*100) / (distance * distance);
	
	float normPosX = positionX / sqrt((positionX*positionX) + (positionY*positionY));
	float normPoxY = positionY / sqrt((positionX*positionX) + (positionY*positionY));
	float multiPosX = magintude * normPosX; 
	float multiPosY = magintude * normPoxY;
	//star2 math stuff
	float positionX2 = 20 - pos.x;
	float positionY2 = 8 - pos.y; 
	float distance2 = sqrt((positionX2*positionX2) + (positionY2*positionY2));
	float magintude2 = (1 * mass*150) / 50;

	float normPosX2 = positionX2 / sqrt((positionX2*positionX2) + (positionY2*positionY2));
	float normPosY2 = positionY2 / sqrt((positionX2*positionX2) + (positionY2*positionY2));
	float multiPosX2 = magintude2 * normPosX2;
	float multiPosY2 = magintude2 * normPosY2;

	return(Vec3((multiPosX + multiPosX2), (multiPosY + multiPosY2), 0));
}
Vec3 Body::StarForce() { // star force for ass3
	float positionX = 13.0f - pos.x;
	float positionY = 8.0f - pos.y;
	float distance = sqrt((positionX*positionX) + (positionY*positionY));
	float magintude = (1 * mass * 100) / (distance * distance);
	float normalPosX = positionX / sqrt((positionX * positionX) + (positionY*positionY));
	float normalPosY = positionY / sqrt((positionX * positionX) + (positionY*positionY));
	float mulitPosX = magintude * normalPosX;
	float mulitPosY = magintude * normalPosY;
	return(Vec3(mulitPosX , mulitPosY, 0));
}

SDL_Surface* Body::getImage() {
	return bodyImage;
}