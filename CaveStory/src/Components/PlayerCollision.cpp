#include "PlayerCollision.h"

bool PlayerCollision::xCollide(units::Game deltaX) {
	CollisionInfo info;
	if (deltaX > 0) {
		info = getCollisionInfo(*map_, rightCollision(deltaX));
		if (info.collided) {
			physics_->xPos_ = info.row * units::TileSize - CollisionX.right();
			physics_->velocityX_ = 0;
		}
		else {
			physics_->xPos_ += deltaX;
		}
	}
	else {
		info = getCollisionInfo(*map_, leftCollision(deltaX));
		if (info.collided) {
			physics_->xPos_ = (info.row + 1) * units::TileSize - CollisionX.left();
			physics_->velocityX_ = 0;
		}
		else {
			physics_->xPos_ += deltaX;
		}
	}
	return info.collided;
}

bool PlayerCollision::yCollide(units::Game deltaY) {
	CollisionInfo info;
	if (deltaY > 0) {
		info = getCollisionInfo(*map_, bottomCollision(deltaY));
		if (info.collided) {
			physics_->yPos_ = info.col * units::TileSize - CollisionY.bottom();
			physics_->onGround_ = true;
			physics_->velocityY_ = 0;
		}
		else {
			physics_->yPos_ += deltaY;
			physics_->onGround_ = false;
		}
	}
	else {
		info = getCollisionInfo(*map_, topCollision(deltaY));
		if (info.collided) {
			physics_->yPos_ = (info.col + 1) * units::TileSize - CollisionY.top();
			physics_->velocityY_ = 0;
			physics_->jumping_ = false;
		}
		else {
			physics_->yPos_ += deltaY;
		}
	}
	return info.collided;
}

Rectangle PlayerCollision::xCollision() const {
	return Rectangle(physics_->pos() + CollisionX);
}

Rectangle PlayerCollision::yCollision() const {
	return Rectangle(physics_->pos() + CollisionY);
}

std::vector<Rectangle> PlayerCollision::collisions() const {
	return std::vector<Rectangle>{xCollision(), yCollision()};
}

Rectangle PlayerCollision::leftCollision(units::Game delta) {
	return Rectangle(
		physics_->xPos_ + CollisionX.left() + delta,
		physics_->yPos_ + CollisionX.top(),
		CollisionX.width() / 2 + delta,
		CollisionX.height()
	);
}

Rectangle PlayerCollision::rightCollision(units::Game delta) {
	return Rectangle(
		physics_->xPos_ + CollisionX.width() / 2 + CollisionX.left() + delta,
		physics_->yPos_ + CollisionX.top(),
		CollisionX.width() / 2 + delta,
		CollisionX.height()
	);
}

Rectangle PlayerCollision::topCollision(units::Game delta) {
	return Rectangle(
		physics_->xPos_ + CollisionY.left(),
		physics_->yPos_ + CollisionY.top() + delta,
		CollisionY.width(),
		CollisionY.height() / 2 + delta
	);
}

Rectangle PlayerCollision::bottomCollision(units::Game delta) {
	return Rectangle(
		physics_->xPos_ + CollisionY.left(),
		physics_->yPos_ + CollisionY.height() / 2 + CollisionY.top() + delta,
		CollisionY.width(),
		CollisionY.height() / 2 + delta
	);
}