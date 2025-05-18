# NODEPP-INPUT
Emulate Keyboard | Mouse | Gamepad | Touch Inputs in Windows, Linux, FreeBSD and Mac, using [Nodepp](https://github.com/NodeppOficial/nodepp).

## Dependencies
```bash
- 🐧libx11-dev : sudo apt install libx11-dev
- 🐧libxi-dev  : sudo apt install libxi-dev
```

## Build & Run
```bash
- 🪟: g++ -o main main.cpp -I ./include -lws2_32 ; ./main
- 🐧: g++ -o main main.cpp -I ./include lX11 -lXtst -lXi ; ./main
```

## Example
```cpp
#include <nodepp/nodepp.h>
#include <nodepp/json.h>
#include <input/mouse.h>

using namespace nodepp;

void onMain(){

    ptr_t<mouse_t> mouse = new mouse_t();

    mouse->onMotionMove([]( uint x, uint y ){
        console::log( json::stringify( object_t({
           { "x", x }, { "y", y }
        }) ));
    });

    mouse->move( 100, 100 );

    process::add([=](){ mouse->next(); return 1; });

}
```
