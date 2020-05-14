#ifndef SCREENOBJECT_H
#define SCREENOBJECT_H

#include <iostream>
#include <random>
#include <vector>
#include <memory>
#include <thread>
#include <mutex>
#include "snake.h"
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
    ~ScreenObject();

    // getter and setter
    int getID() { return _id; }
    // void setPosition(double x, double y);
    // void getPosition(double &x, double &y);
    ObjectType getType() { return _type; }

    // typical behaviour methods
    virtual void simulate(){};

protected:
    ObjectType _type;                 // identifies the class type
    int _id;                          // every screen object has its own unique id
    // Snake snake;                      // snake object
    std::vector<std::thread> threads; // holds all threads that have been launched within this object
    static std::mutex _mtx;           // mutex shared by all screen objects for protecting cout
    //TODO: clean up the comments here
    std::random_device dev;
    std::mt19937 engine;
    std::uniform_int_distribution<int> random_w;
    std::uniform_int_distribution<int> random_h;

private:
    static int _idCnt; // global variable for counting object ids
};


#endif
