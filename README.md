cong
----
Another Pong clone, written in C++ and using SFML. For now, I'll code on/for Linux.

Motivation
----------
This is my first C++ project. The goal is to get a good grasp of the language's basics.
I also want to wrap my head around the basic concepts and patterns of game programming.
In order to focus on the language instead of OS specific APIs, I decided to use SFML.

Dependencies
------------
- [SFML](http://www.sfml-dev.org/)

Building
--------
I use these commands, put into a `build.sh` file, to build:
```
g++ -c *.cpp -std=c++11
g++ -o cong *.o -lsfml-graphics -lsfml-window -lsfml-system
rm ./*.o
```

Planned features
----------------
- Create a simple, but solid game loop that makes for a fixed game speed across machines
- Come up with and use custom physics as an additional challenge
- Main menu, maybe with an additional Settings menu
- 1 and 2 player mode (and therefore a simple AI)
- Possibility to pause the game

Problems and Learnings
----------------------
- Referencing files (textures): I have no idea how it works on Mac; easy on Linux
- Passing pointers/references around: You really need to pay attention to the scope!
