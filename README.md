# OsuBot
#### A bot that play Osu! for you.

---

OsuBot is a program that will detect when a Osu! game is running, and will perform a **perfect score**.

Later, when the project will be complete, you will be able to pick up a release version of the program. For now, In order to compile and use this program, you need the clang++ compiler, the CMake and the NMake software. All you need to do is to run the CMake build generator command in the root folder of the project (to any folder you want), and build it with nmake.

```
cmake -B build -G "NMake Makefiles" -DENABLE_TESTS=ON
cd build/
nmake
```

---

### Current Features

- Partial parsing of any Osu! standard map file (only the required infos are parsed).
- Detection of the running Osu! process, and the currently playing map.


### How to use this program ?

All you need to do is:
- Launch the OsuBot.exe program,
- Start a Osu! map,
- Enjoy !
