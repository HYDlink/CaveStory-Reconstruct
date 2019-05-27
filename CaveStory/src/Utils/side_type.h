#ifndef SIDE_TYPE_H_
#define SIDE_TYPE_H_

namespace sides {
   enum SideType {
      TOP_SIDE = 0b0001,
      BOTTOM_SIDE = 0b0010,
      LEFT_SIDE = 0b0100,
      RIGHT_SIDE = 0b1000,
   };

   inline SideType opposite_side(SideType side) {
      if (side == TOP_SIDE)
         return BOTTOM_SIDE;
      if (side == BOTTOM_SIDE)
         return TOP_SIDE;
      if (side == LEFT_SIDE)
         return RIGHT_SIDE;
      return LEFT_SIDE;
   }

   inline bool vertical(SideType side) {
      return side == TOP_SIDE || side == BOTTOM_SIDE;
   }

   inline bool horizontal(SideType side) {
      return !vertical(side);
   }

#if 0
   inline SideType from_facing(HorizontalFacing h_facing, VerticalFacing v_facing) {
      if (v_facing == UP)
         return TOP_SIDE;
      if (v_facing == DOWN)
         return BOTTOM_SIDE;
      if (h_facing == LEFT)
         return LEFT_SIDE;
      return RIGHT_SIDE;
   }
#endif
   inline bool is_max(SideType side) {
      return side == RIGHT_SIDE || side == BOTTOM_SIDE;
   }
   inline bool is_min(SideType side) {
      return !is_max(side);
   }
}

#endif // SIDE_TYPE_H_
