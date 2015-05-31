cong
====
Another Pong clone, written in C++, using SFML. For now, I'll code on/for Linux.

![Screenshot of Cong](http://i.imgur.com/QSUj3cD.png)

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
- Solid game loop that makes for a fixed game speed across machines
- Main menu, maybe with an additional Settings menu
- 1 and 2 player mode (and therefore a simple AI)
- Possibility to pause the game
- Some simple sound effects

Stretch goals (if time/motivation permits)
------------------------------------------
- Round ball and the required custom physics as an additional challenge
- Support for other Input devices (Joystick, Joypad) and analog input
- Possibility to customize inputs (user can choose which buttons/keys move the paddles)
- Possibility to configure video settings (resolution, windowed/full screen, ...)
- Color setting (change element/font color from white to some other colors)

Lincence, Copyright, Credits
----------------------------
Everything is public domain (do whatever you want with it).
All code and contents have been created by me, with the exepction of:
- The sounds, which I got from [OpenGameArt.org](http://opengameart.org/content/3-ping-pong-sounds-8-bit-style)


Problems and Learnings
----------------------
- Referencing files (textures): I have no idea how it works on Mac/OS X; easy on Linux. Well, fuck OS X for now!
- Passing pointers/references around: You really need to pay attention to the scope! (See point 5 for further insight)
- Member vars and member functions can't have the same name; this is in fact one reason why a lot of people would prefix member variables with `m` or `_` or `m_` or ...
- Better make a cheat sheet on what can/must (not) go in the `.hpp` and .`cpp` file, it get's confusing. Especially with (for example) `static`, which should be in the `.hpp`, but not in the `.cpp` (why?).
- Passing pointers around creates the ownership question. Who should `delete`? Remember: `delete` will delete the value at the address the pointer is pointing to; the pointer will still point to the same address, there is just nothing anymore.
- Stack Overflow is full of the advice not to use 'raw' pointers, but 'smart' pointers. But I see so many projects that do fine with 'raw' pointers. So... I don't know.
- Trying to `delete` a pointer that has not been initialized will cause a segmentation fault. Always initialize them to `0` or `nullptr`!
- There are many "weird" types, like size_t, that seem to be used instead of types like int. I should figure out why and what exactly they are.
- Default values for function parameters should appear in the declaration (header file), *not* the definition (cpp file)! (The other way round is possible with a different effect on visibility, but can never have both)
