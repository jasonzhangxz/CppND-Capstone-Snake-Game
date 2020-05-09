# CPPND: Capstone Snake Game Extension

In this Capstone Project, I decided to extend the Snake Game project with some additional features, like adding Reward/Punishment mechanisms to the game. When the snake hits a coin then he can get extra points, when it catches a crown, the snake will slow down for a minute to make it easier to navigate through the field and catch points, and there will be more breadcrumbs adding to the fields. When it hits a Punishment icon, it speeds up for 30 seconds and there will be some bombs adding to the fields, if it hits the bomb then the game ends.

This final project takes the starter repo from [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213), which was inspired by [this](https://codereview.stackexchange.com/questions/212296/snake-game-in-c-with-sdl) excellent StackOverflow post and set of responses.

The original starter snake game looks like below:
<img src="snake_game.gif"/>

After the extension, it looks like something below:


## Rubrics covered in this final project
1.
2.
3.
4.
5.



## Dependencies for Running Locally
* cmake >= 3.7
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
4. Run it: `./SnakeGame`.
