# Tetris

Tetris made in C++ using SFML and boost. Project isn't working as it is now. I need to change a few things in my free time and it should be fine. Planning on developing it further.

## Plans for the future

- Finally implement true multiplayer mode
- Add song choice menu
- Add global ranking
- Add new gamemodes (?)
- ... I'll figure out the rest

## How to run it

Since it is made using SFML and boost you need to install those libraries first. It works on windows, haven't tested it on linux yet.

### Installing SFML

- Download SFML from [here](https://www.sfml-dev.org/download.php)
- Unzip it
- Configure your project dependencies like [this](https://www.sfml-dev.org/tutorials/2.6/start-vc.php)

### Installing boost

- Download boost from [here](https://www.boost.org/users/download/)
- Unzip it
- Add directory containing boost to compiler include path:  
Project Properties -> Configuration Properties -> C/C++ -> General -> Additional Include Directories  
Add your C://.../boost_1_xx_x directory here

### Building boost

This project uses boost libraries that must be built separately, don't wory - it's easy.  
- Open powershell and change your working directory to boost directory ``$ cd C://.../boost_1_xx_x``
- Run bootstrap ``$ ./bootstrap``
- Build boost libraries ``$ ./b2``, it could take a while
- Add directory containing generated libs to linker library path:  
Project Properties -> Configuration Properties -> Linker -> General -> Additional Library Directories  
Add your C://../boost_1_xx_x/stage/lib directory here

Now, boost should be working properly, but if it isn't check [this](https://levelup.gitconnected.com/the-definite-guide-on-compiling-and-linking-boost-c-libraries-for-visual-studio-projects-c79464d7282d) or [that](https://www.boost.org/doc/libs/1_84_0/more/getting_started/windows.html) out.

## Game engine

Game engine template was created by Sonar Systems, modified and further developed by me.
