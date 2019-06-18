#pragma once
#include <SDL_types.h>

enum MotionType : Uint8 {
	FIRST_MOTION_TYPE,
	STANDING = FIRST_MOTION_TYPE,
	INTERACTING,
	WALKING,
	JUMPING,
	FALLING,
	LAST_MOTION_TYPE
};
enum HorizontalFacing : bool {
	FACING_LEFT,
	FACING_RIGHT
};
enum VerticalFacing : Uint8 {
	FORWARD = 0b000,
	LOOKUP = 0b010,
	LOOKDOWN = 0b100
};
struct FaceType {
	VerticalFacing verticalFacing = FORWARD;
	HorizontalFacing horizontalFacing = FACING_LEFT;
	uint8_t faceType() { return horizontalFacing | verticalFacing; }
};
struct CharState {
	//TODO 更改为scoped enum, 即enum class MotionType, etc.
	MotionType motionType = STANDING;
	VerticalFacing verticalFacing = FORWARD;
	HorizontalFacing horizontalFacing = FACING_LEFT;
	uint8_t faceType() { return horizontalFacing | verticalFacing; }
	// 向FaceType的隐式转换
	operator FaceType() {
		return { verticalFacing, horizontalFacing };
	}
};
//TODO 完善动画状态 修改函数名称
static inline size_t getState(CharState state) {
	return state.motionType | (state.verticalFacing << 3);
}
