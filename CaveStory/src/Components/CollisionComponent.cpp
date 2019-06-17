#include "CollisionComponent.h"
#include "PhysicsComponent.h"

bool CollisionComponent::xCollide(units::Game deltaX) {
	CollisionInfo info;
	if (deltaX > 0) {
		info = getCollisionInfo(*map_, rightCollision(deltaX));
		if (info.collided) {
			physics_->xPos_ = info.row * units::TileSize - CollisionX_.right();
			physics_->velocityX_ = 0;
		}
		else {
			physics_->xPos_ += deltaX;
		}
	}
	else {
		info = getCollisionInfo(*map_, leftCollision(deltaX));
		if (info.collided) {
			physics_->xPos_ = (info.row + 1) * units::TileSize - CollisionX_.left();
			physics_->velocityX_ = 0;
		}
		else {
			physics_->xPos_ += deltaX;
		}
	}
	return info.collided;
}

bool CollisionComponent::yCollide(units::Game deltaY) {
	CollisionInfo info;
	if (deltaY > 0) {
		info = getCollisionInfo(*map_, bottomCollision(deltaY));
		if (info.collided) {
			physics_->yPos_ = info.col * units::TileSize - CollisionY_.bottom();
			physics_->velocityY_ = 0;
		}
		else {
			physics_->yPos_ += deltaY;
		}
	}
	else {
		info = getCollisionInfo(*map_, topCollision(deltaY));
		if (info.collided) {
			physics_->yPos_ = (info.col + 1) * units::TileSize - CollisionY_.top();
			physics_->velocityY_ = 0;
		}
		else {
			physics_->yPos_ += deltaY;
		}
	}
	return info.collided;
}

Rectangle CollisionComponent::xCollision() const {
	return Rectangle(physics_->pos() + CollisionX_);
}

Rectangle CollisionComponent::yCollision() const {
	return Rectangle(physics_->pos() + CollisionY_);
}

std::vector<Rectangle> CollisionComponent::collisions() const {
	return std::vector<Rectangle>{xCollision(), yCollision()};
}

Rectangle CollisionComponent::leftCollision(units::Game delta) {
	return Rectangle(
		physics_->xPos_ + CollisionX_.left() + delta,
		physics_->yPos_ + CollisionX_.top(),
		CollisionX_.width() / 2 + delta,
		CollisionX_.height()
	);
}

Rectangle CollisionComponent::rightCollision(units::Game delta) {
	return Rectangle(
		physics_->xPos_ + CollisionX_.width() / 2 + CollisionX_.left() + delta,
		physics_->yPos_ + CollisionX_.top(),
		CollisionX_.width() / 2 + delta,
		CollisionX_.height()
	);
}

Rectangle CollisionComponent::topCollision(units::Game delta) {
	return Rectangle(
		physics_->xPos_ + CollisionY_.left(),
		physics_->yPos_ + CollisionY_.top() + delta,
		CollisionY_.width(),
		CollisionY_.height() / 2 + delta
	);
}

Rectangle CollisionComponent::bottomCollision(units::Game delta) {
	return Rectangle(
		physics_->xPos_ + CollisionY_.left(),
		physics_->yPos_ + CollisionY_.height() / 2 + CollisionY_.top() + delta,
		CollisionY_.width(),
		CollisionY_.height() / 2 + delta
	);
}