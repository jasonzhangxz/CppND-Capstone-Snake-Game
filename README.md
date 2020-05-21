# CPPND: Capstone Snake Game Extension

In this Capstone Project, I decided to extend the Snake Game project with some additional features, like adding Reward/Punishment mechanisms to the game. When the snake hits a Reward coin then it get certain grace period with lower speed so that it's easier to navigate through the fields and eat foods; when it hits a bomb icon, it then ends the game. The Reward/Punishment will only show up after score reaches certain value (3 for now) and higher. The bomb will always be showed up closely around the reward just to increase the difficulty to get reward. Both reward and bomb show up on the screen for a random amount of time, but with the bomb always showing on the screen longer than the bomb.

This final project takes the starter repo from [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213), which was inspired by [this](https://codereview.stackexchange.com/questions/212296/snake-game-in-c-with-sdl) excellent StackOverflow post and set of responses.

The original starter snake game looks like below:
<img src="snake_game.gif"/>

## Extensions I did in this project
The food in the video game is extracted out as a class. And as I am putting reward/bomb on the screen too, I think it is good to have a base class called ScreenObject which has the basic methods and data I need for all food, reward and bomb. Then the ScreenFood and ScreenReward are both inherited from ScreenObject. The ScreenFood is very simple only have the updatePos() method, whereas the ScreenReward is a little bit complicated that it has a functions to check the duration of the reward and object, and put it in unseen corner when the time runs out. And same for the ScreenBomb, but to make it a little difficult to get the reward, so the bomb's position is always close around the reward object, so the ScreenBomb inherits from ScreenReward and update its position based on the reward object. The class hierarchy looks like below:

<img src="classHierarchy.png"/>

The other thing I learned in this project is how to use the SDL library to render texture to the screen. As you can see in the video, now that you will see reward and bomb show up on the screen.

## Snake Game Code Structure
The code structure stays about the same, other than the food is now an object of ScreenFood, and two new objects: ScreenReward and ScreenBomb also stored in the Game.

<img src="codeStrtructure.png"/>

## New Sname Game looks like below
After the extension, it looks like something below:
<video src=""/>

## Rubrics covered in this final project
1.The project uses Object Oriented Programming techniques: as I create the class hierarchy of ScreenObject, ScreenReward, ScreenBomb.
2.Class constructors utilize member initialization lists: this can be seen in the above mentioned classes.
3.Classes follow an appropriate inheritance hierarchy.
4.Derived class functions override virtual base class functions.
5.The project makes use of references in function declarations.



## Dependencies for Running Locally
* cmake >= 3.11
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  * Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source.
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./snakeGame`.
