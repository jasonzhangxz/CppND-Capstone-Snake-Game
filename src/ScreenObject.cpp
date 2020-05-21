#include <algorithm>
#include "ScreenObject.h"

// init static variable
int ScreenObject::_idCnt = 0;

// std::mutex ScreenObject::_mtx;

void ScreenObject::setPos(int x, int y)
{
    pos.x = x;
    pos.y = y;
}

ScreenObject::ScreenObject(std::size_t grid_width, std::size_t grid_height)
  :engine(dev()),
  random_w(0, static_cast<int>(grid_width-1)),
  random_h(0, static_cast<int>(grid_height-1))
{
    _type = ObjectType::noObject;
    _id = _idCnt++;
}
