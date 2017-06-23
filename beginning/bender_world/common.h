#ifndef COMMON_H
#define COMMON_H

enum class eBenderMapObj
{
    UNKNOWN
   ,BENDER                  // '@'
   ,EMPTY                   // ' '
   ,WALL                    // '#'
   ,OBSTACLE                // 'X'
   ,FINISH                  // '$'
   ,SOUTH                   // 'S'
   ,EAST                    // 'E'
   ,NORTH                   // 'N'
   ,WEST                    // 'W'
   ,BEER                    // 'B'
   ,INVERT                  // 'I'
   ,TELEPORT                // 'T'
};

enum class eWorldDirection
{
  SOUTH
 ,EAST
 ,NORTH
 ,WEST
};


#endif // COMMON_H
