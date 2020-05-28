#ifndef SCREENOBJECT_H
#define SCREENOBJECT_H

#include <iostream>
#include <random>
#include <vector>
#include <memory>
#include <thread>
#include <mutex>
#include "SDL.h"

enum ObjectType
{
    noObject,
    objectFood,
    objectBomb,
    objectReward,
};

class ScreenObject
{
public:
    // constructor / desctructor
    ScreenObject(std::size_t grid_width, std::size_t grid_height);
    ScreenObject(const ScreenObject &object);
//    ~ScreenObject();

    // getter and setter
    int getID() { return _id; }
    ObjectType getType() { return _type; }
    void setPos(int x, int y);

    // typical behaviour methods
    virtual void updatePos(){};
    virtual void run(){};

    SDL_Point pos;

protected:
    ObjectType _type;                 // identifies the class type
    int _id;                          // every screen object has its own unique id

    //The below is the random engine to generate random positions for screen objects
    std::random_device dev;
    std::mt19937_64 engine;
    std::uniform_int_distribution<int> random_w;
    std::uniform_int_distribution<int> random_h;

private:
    static int _idCnt; // global variable for counting object ids
};


#endif
