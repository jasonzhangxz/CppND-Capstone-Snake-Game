#include <algorithm>
#include "ScreenObject.h"

// init static variable
int ScreenObject::_idCnt = 0;


ScreenObject::ScreenObject(std::size_t grid_width, std::size_t grid_height)
  :engine(dev()),
  random_w(0, static_cast<int>(grid_width-1)),
  random_h(0, static_cast<int>(grid_height-1))
{
    _type = ObjectType::noObject;
    _id = _idCnt++;
}

ScreenObject::ScreenObject(const ScreenObject &object)
  :engine(dev()),
  random_w(0, 31),
  random_h(0, 31)
{
  pos = object.pos;
  _type = object._type;
  _id = object._id;
}

//ScreenObject::~ScreenObject()
//{
//}

void ScreenObject::setPos(int x, int y)
{
    pos.x = x;
    pos.y = y;
}
