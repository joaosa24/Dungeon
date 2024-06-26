# Dungeon

## Grade: 18/20 :star:

An [ncurses](https://invisible-island.net/ncurses/) roguelite game, made for
our [LI2](https://www4.di.uminho.pt/~jno/sitedi/uc_J302N6.html) class. 

## Building

### Dependencies

 - GNU Make (build-time)
 - GCC (build-time)
 - Bash (build-time)
 - Doxygen (optional, build-time)
 - ncurses

Note that the only supported platform is **Linux** (others \*NIX systems _may_ work) and the only
supported compiler is GCC (clang _may_ work).

### Building

A release build is achieved with:

``` bash
$ make
```

To remove files generated by a build, run:

``` bash
$ make clean
```
