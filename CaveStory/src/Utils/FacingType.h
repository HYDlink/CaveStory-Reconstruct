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
	//TODO ����Ϊscoped enum, ��enum class MotionType, etc.
	MotionType motionType = STANDING;
	VerticalFacing verticalFacing = FORWARD;
	HorizontalFacing horizontalFacing = FACING_LEFT;
	uint8_t faceType() { return horizontalFacing | verticalFacing; }
	// ��FaceType����ʽת��
	operator FaceType() {
		return { verticalFacing, horizontalFacing };
	}
};
//TODO ���ƶ���״̬ �޸ĺ�������
static inline size_t getState(CharState state) {
	return state.motionType | (state.verticalFacing << 3);
}
