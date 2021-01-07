#include "CollisionComponent.h"

CollisionComponent::CollisionComponent(SDL_Rect* area) {
	collisionArea = area;
}

void CollisionComponent::setCollisionArea(SDL_Rect* area) {
	collisionArea = area;
}


bool CollisionComponent::getCollision(SDL_Rect* otherCollisionArea) {
	if (collisionArea->x + collisionArea->w >= otherCollisionArea->x &&
		otherCollisionArea->x + otherCollisionArea->w >= collisionArea->x &&
		collisionArea->y + collisionArea->h >= otherCollisionArea->y &&
		otherCollisionArea->y + otherCollisionArea->h >= collisionArea->y) {
		return true;
	} // AABB collision checking
	return false;
}
