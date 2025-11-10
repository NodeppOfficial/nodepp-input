# NodePP Input Emulation: Simulate Keyboard, Mouse, Gamepad, and Touch

This project provides a powerful and cross-platform solution for programmatically emulating various user inputs (keyboard, mouse, gamepad, and touch) on Windows, Linux, FreeBSD, and macOS, all within the NodePP asynchronous and event-driven C++ framework. Automate tasks, create interactive installations, or build testing tools by programmatically controlling user input.

## Key Features

- **Cross-Platform Support:** Works seamlessly on Windows, Linux, FreeBSD, and macOS.
- **Keyboard Emulation:** Simulate key presses, releases, and typing.
- **Mouse Emulation:** Control mouse movement, clicks (left, right, middle, etc.), and scrolling.
- **Gamepad Emulation:** Simulate button presses, analog stick movements, and trigger actions for game controllers.
- **Touch Input Emulation:** Simulate touch events (down, up, move) for touch-enabled devices.
- **Asynchronous Operations:** Input events are triggered non-blockingly, fitting perfectly within NodePP's event-driven architecture.
- **NodePP Integration:** Leverages the performance and concurrency of NodePP's C++ foundation for responsive input simulation.

## Dependencies
```bash
- 🐧libxtst-dev: sudo apt install libxtst-dev
- 🐧libx11-dev : sudo apt install libx11-dev
- 🐧libxi-dev  : sudo apt install libxi-dev
```

## Build & Run
```bash
- 🪟: g++ -o main main.cpp -I ./include         -lws2_32 ; ./main
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
