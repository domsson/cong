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
- [SFML](http://www.sfml-dev.org/) (Version 2.0+)

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
- The sounds, which I got from [OpenGameArt.org](http://opengameart.org/content/3-ping-pong-sounds-8-bit-style) (Public Domain)


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
- Circular dependencies are tricky. Forward declarations can help. See http://stackoverflow.com/questions/625799/resolve-circular-dependencies-in-c
- [Virtual / Pure Virtual](http://stackoverflow.com/questions/1306778/c-virtual-pure-virtual-explained) - Important for inheritance and interfaces / abstract classes
- If a class has members that are pointers, you will most likely need a copy constructor and custom assignment operator (for deep instead of shallow copies), otherwise you'll run into ugly problems (Segfault says hello!). See http://stackoverflow.com/questions/29052286/initialize-object-with-pointer-members-in-a-vector-c
- The above leads or is related to move semantics (no idea yet!), the [&&-operator](http://stackoverflow.com/questions/4549151/c-double-address-operator) (related to move semantics) and the Rule of Three / Five (basically the previous point)
- For move semantics, check out http://stackoverflow.com/questions/3106110/what-are-move-semantics
- Copy constructors can have member initializer lists as well!
- Copy constructors in derived classes need to explicitly call their base/parent's copy constructors (in the initializer list), otherwise the base object's will properties not be copied accordingly
- Custom assignment operators can NOT have member initializer lists. Simple reason: As we define what happens when we _assign_ (and not _initialize_) to our object, the members have already been initialized at this point.
- Check out the copy&swap idiom: http://stackoverflow.com/questions/3279543/what-is-the-copy-and-swap-idiom
- Virtual: makes sure the most-derived (overriden) version of a function is called, if any. See http://stackoverflow.com/questions/2391679/why-do-we-need-virtual-methods-in-c
- Pure virtual (virtual ... = 0): See virtual, plus deriving classes _have to_ implement these functions.
- If you have a function in a child class that has the same name but different arguments as a function in the base class, calling the base class' function through an object of the child class will not work. The keyword here is "name hiding": http://stackoverflow.com/questions/16835897/overloading-base-class-method-in-derived-class and http://www.programmerinterview.com/index.php/c-cplusplus/c-name-hiding/
