/*
 * Copyright 2023 The Nodepp Project Authors. All Rights Reserved.
 *
 * Licensed under the MIT (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://github.com/NodeppOficial/nodepp/blob/main/LICENSE
 */

/*────────────────────────────────────────────────────────────────────────────*/

#ifndef NODEPP_INPUT
#define NODEPP_INPUT

/*────────────────────────────────────────────────────────────────────────────*/

#if   _KERNEL == NODEPP_KERNEL_WINDOWS

    #include <Xinput.h>
    #include <winuser.h>
    #include <windowsx.h>

    #include "windows/touch.cpp"

#elif _KERNEL == NODEPP_KERNEL_POSIX

    #include <limits.h>
    #include <X11/Xlib.h>
    #include <X11/keysym.h>
    #include <X11/extensions/XInput2.h>

    #include "posix/touch.cpp"

#else
    #error "This OS Does not support touch.h"
#endif

/*────────────────────────────────────────────────────────────────────────────*/

#endif

/*────────────────────────────────────────────────────────────────────────────*/