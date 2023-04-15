# apal-project
## Hashed Array Tree (HAT)
For the lack of a better name we are going to called all the data structures (1 of Sitarski's and 2 of Brodnik's) Hashed Array Tree.
### Naming
1. Sitarski's HAT is has the same name.
2. Brodnik's HAT non-superblock version is named *Brodnik's HAT A* (brodnik-hat-a.cpp/ BrodnikHatA class)
3. Brodnik's HAT superblock version is named *Brodnik's HAT B* (brodnik-hat-b.cpp/ BrodnikHatB class)
### Changes
The implementation of ```get``` function of Brodnik's HAT B is different from ```locate``` function in the original [paper](https://sedgewick.io/wp-content/themes/sedgewick/papers/1999Optimal.pdf). Namely, I cannot implement part of it since there might be something wrong. More information can be found in ```brodnik-hat-b.cpp```.
### Files
For Brodnik's HAT A and B, the version that have background-rebuilding implemented has the file name ended with ```brd``` i.e. ```brodnik-hat-a-brd.cpp```.
