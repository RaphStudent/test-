#include "Collider.h"
#include "Body.h" 
#include <math.h>

Collider::Collider()
{
}


Collider::~Collider()
{
}

bool Collider::CheckCollision(Body *body1_,  Body *body2_) {
	float changex = (body2_->pos.x - body1_->pos.x);
	float changey = (body2_->pos.y - body1_->pos.y);
	float changez = (body2_->pos.z - body1_->pos.z);
	float distance = sqrt((changex)*(changex)+(changey)*(changey)+(changez)*(changez));
	if (distance < (body2_->rad + body1_->rad)) {
		printf("hitter");
		return true;
	}
	else { return false;}
}
void Collider::HandleCollision(Body*body1_, Body*body2_, float E_) {
	Vec3 normal = VMath::normalize(body2_->pos - body1_->pos);
	float v1p = VMath::dot(body1_->vel, normal);
	float v2p = VMath::dot(body2_->vel, normal);
	float v1f = (((body1_->mass - (E_ * body2_->mass)) * v1p) + ((1.0f + E_) * body2_->mass * v2p) / (body1_->mass + body2_->mass));
	float v2f = (((body2_->mass - (E_ * body1_->mass)) * v2p) + ((1.0f + E_) * body1_->mass * v1p) / (body1_->mass + body2_->mass));
	body1_->vel = (v1f - v1p) * normal;
	body2_->vel = (v2f - v2p) * normal;
}