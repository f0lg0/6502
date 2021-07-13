# 6502 Emulator

A minimal, single-stepped and beginner friendly 6502 emulator written in C using ncurses for graphics.

![thumbnail](./images/thumbnail.png)

## DISCLAIMER

This main goal of this project is to understand how CPUs works by directly emulating one and to debug it by single stepping instructions. The code is meant to be readable and understandable, a lot of things could be done better, especially the graphics.

The emulator only shows you what's going on under the hood of a 6502 CPU, without displaying stuff graphically (you will only see hex digits). The example program simply caluclates `10*3` and it's not optimized.

## Code style

The paradigm I've chosen is `modular programming`, especially because this is C. System components aren't defined in a OOP way.

Everything is very verbose with a lot of comments.

## Run

You must have `ncurses` installed on your machine. This project was developed in a Linux environment.

```
make
```

```
./bin/emulator.out
```

Or you can run the _shortcut_ script

```
bash run.sh
```

## TODO

Do you want to contribute? Here are some things that are still a WIP.

-   [ ] check for errors on cpu_fetch() calls
-   [ ] add remaining comments to `instructions.c`
-   [ ] create a better interface

## References

-   [obelisk.me.uk/6502](http://www.obelisk.me.uk/6502/)
