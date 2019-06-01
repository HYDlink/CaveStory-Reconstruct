#ifndef RECTANGLE_H_
#define RECTANGLE_H_

//#include "side_type.h"
#include "Utils/units.h"
#include "Utils/sideType.h"
#include <SDL_rect.h>
#include <vector>

struct Rectangle {
	friend Rectangle operator+(const Position2D& pos, const Rectangle& rect);
	Rectangle() : Rectangle(0, 0, 0, 0) {}
	Rectangle(const SDL_Rect& r) : x_(r.x), y_(r.y), width_(r.w), height_(r.h) {}
	Rectangle(const Position2D& position, const Dimensions2D& dimensions) :
		x_(position.x),
		y_(position.y),
		width_(dimensions.x),
		height_(dimensions.y) {
	}
	Rectangle(units::Game x, units::Game y, units::Game width, units::Game height) :
		x_(x),
		y_(y),
		width_(width),
		height_(height) {
	}
	Rectangle(const Rectangle& r) = default;
	Rectangle& operator=(const Rectangle& rect);
	// 向SDL_Rect的隐式转换
	operator SDL_Rect() {
		return SDL_Rect{ units::gameToPixel(x_), units::gameToPixel(y_),
			units::gameToPixel(width_), units::gameToPixel(height_), };
	}

	static void setRectByCenter(Rectangle& rect, const Position2D& center) {
		rect.setLeft(center.x - rect.width() / 2);
		rect.setTop(center.y - rect.height() / 2);
	}
	Position2D pos() const { return Position2D(x_, y_); }
	units::Game center_x() const { return x_ + width_ / 2; }
	units::Game center_y() const { return y_ + height_ / 2; }

	
	units::Game side(sides::SideType side) const {
		if (side == sides::LEFT_SIDE)
			return left();
		if (side == sides::RIGHT_SIDE)
			return right();
		if (side == sides::TOP_SIDE)
			return top();
		return bottom();
	}
	void setLeft(units::Game x) { x_ = x; }
	void setTop(units::Game y) { y_ = y; }
	void setRight(units::Game x) { x_ = x - width_; }
	void setBottom(units::Game y) { y_ = y - height_; }
	void setWidth(units::Game width) { width_ = width; }
	void setHeight(units::Game height) { height_ = height; }

	units::Game left() const { return x_; }
	units::Game right() const { return x_ + width_; }
	units::Game top() const { return y_; }
	units::Game bottom() const { return y_ + height_; }

	units::Game width() const { return width_; }
	units::Game height() const { return height_; }

	bool collidesWith(const Rectangle & other) const {
		return right() >= other.left() &&
			left() <= other.right() &&
			top() <= other.bottom() &&
			bottom() >= other.top();
	}
	bool collidesWith(const std::vector<Rectangle>& others) const {
		bool collided = false;
		for (const auto& other : others) {
			if (collidesWith(other))
				return true;
		}
		return false;
	}
	Uint8 totalIn(const Rectangle& other) const {
		return ((left() >= other.left())? sides::NO_SIDE : sides::LEFT_SIDE) |
			((right() <= other.right()) ? sides::NO_SIDE : sides::RIGHT_SIDE) |
			((top() >= other.top()) ? sides::NO_SIDE : sides::TOP_SIDE) |
			((bottom() <= other.bottom()) ? sides::NO_SIDE : sides::BOTTOM_SIDE);
	}
private:
	units::Game x_, y_, width_, height_;
};

inline Rectangle operator+(const Position2D& pos, const Rectangle& rect) {
	return Rectangle{ pos.x + rect.x_, pos.y + rect.y_, rect.width_, rect.height_ };
}
inline Rectangle& Rectangle::operator=(const Rectangle& rect) = default;
#endif // RECTANGLE_H_
