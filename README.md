Experiental
===========

README
------

Experiental is an Open Source game engine.

[GameDev.ru forum thread (russian)](http://www.gamedev.ru/projects/forum/?id=176799)

##Compiling

###Linux:
To compile this project you need get a working **Code::Blocks IDE** and several libraries at least with these versions:

* libsdl2-2.0.1
* sdl2-net-2.0.0
* sdl2-mixer-2.0.0
* DevIL(OpenIL)-1.7.8
* CEGUI-0.7.7
* (optional) OpenAL-1.15.1


###Windows:
Download and install Code::Blocks IDE with MinGW:
[codeblocks-13.12mingw-setup.exe](http://www.codeblocks.org/downloads/26#windows)

Download SDL2: [http://www.libsdl.org/release/SDL2-devel-2.0.1-mingw.tar.gz](http://www.libsdl.org/release/SDL2-devel-2.0.1-mingw.tar.gz)
<br>Extract with merge folders "bin, "lib" and "include" into CodeBlocks main folder\MinGW.

Download SDL2-Net: [http://www.libsdl.org/projects/SDL_net/release/SDL2_net-devel-2.0.0-mingw.tar.gz](http://www.libsdl.org/projects/SDL_net/release/SDL2_net-devel-2.0.0-mingw.tar.gz)
<br>Extract with merge folders "bin", "lib" and "include" into CodeBlocks main folder\MinGW.

Download SDL2-Mixer: [http://www.libsdl.org/projects/SDL_mixer/release/SDL2_mixer-devel-2.0.0-mingw.tar.gz](http://www.libsdl.org/projects/SDL_mixer/release/SDL2_mixer-devel-2.0.0-mingw.tar.gz)
<br>Extract with merge folders "bin", "lib" and "include" into CodeBlocks main folder\MinGW.

Merge folders "mingw32libs\include" and "mingw32libs\lib" into CodeBlocks main folder\MinGW. Taken from [MinGW libraries for the Spring RTS game engine](https://github.com/spring/mingwlibs)

Open "Experiental.cbp" and select WDebug32 as target. Go to the Project->Build options...->WDebug32->Search directories->Compiler/Linker and change path to where project file is located.