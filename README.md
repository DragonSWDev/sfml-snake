# SFML Snake
This is a simple Snake clone written in C++ with SFML 2 library.

### Installation

#### 1. Install SFML library and CMake

#### 2. Get source code

    git clone https://github.com/BlackDragonK99/sfml-snake && cd sfml-snake
    
#### 3. Configure and build
**Unix-like (Linux, BSD etc.)**

    mkdir build && cd build
    cmake ..
    make
    
If You have SFML installed in custom location, You can specify include and lib files by adding this to CMakeLists.txt:

    include_directories(/mydir/include)
    link_directories(/mydir/lib)
    
**Windows**
You can use cmake, but better idea is to install Visual Studio, create new project, install SFML, import all SFML Snake sources to the created project and compile it. You can find instructions about using SFML in Visual Studio here:
http://www.sfml-dev.org/tutorials/2.4/start-vc.php
    
#### 4. Copy compiled binary (sfmlsnake) to the desired directory and put directory font with content next to binary
SFML Snake expects font directory to be next to the binary, so don't use make install.

### Instruction
Use mouse to operate in menu. You can tweak some options in Options menu (like random wall generation). You can move Snake by arrows. Use P to pause game and Escape to return to the menu. Wall generation isn't perfect (It can leave empty field surrounded by walls) but it is.
