/*
 * Copyright 2023 The Nodepp Project Authors. All Rights Reserved.
 *
 * Licensed under the MIT (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://github.com/NodeppOficial/nodepp/blob/main/LICENSE
 */

/*────────────────────────────────────────────────────────────────────────────*/

#ifndef NODEPP_POSIX_TOUCH
#define NODEPP_POSIX_TOUCH

/*────────────────────────────────────────────────────────────────────────────*/

namespace nodepp { class touch_t : public generator_t {
protected:

    struct NODE {
        Display* dpy = nullptr;
        int deviceID = 0;
    };  ptr_t<NODE> obj;

public:

    event_t<uint,uint,uint> onTouchDown;
    event_t<uint,uint,uint> onTouchMove;
    event_t<uint,uint,uint> onTouchUp;

    /*─······································································─*/

    int next() noexcept {
    coBegin

        do{ uint   idx = DefaultScreen( obj->dpy );
            Window win = XRootWindow  ( obj->dpy, idx );

            uchar mask[(XI_LASTEVENT + 7)/8] = {0};
            XISetMask(mask, XI_TouchUpdate);
            XISetMask(mask, XI_TouchBegin);
            XISetMask(mask, XI_TouchEnd);

            XIEventMask evmask;
                        evmask.mask     = mask;
                        evmask.mask_len = sizeof(mask);
                        evmask.deviceid = obj->deviceID;

            XISelectEvents( obj->dpy, obj->deviceID, &evmask, 1 );
        } while(0); coYield(1);

        while( XPending( obj->dpy ) > 0 ){
            XEvent ev; XNextEvent( obj->dpy, &ev );

            if( ev.xcookie.type == GenericEvent ){
                XGetEventData( obj->dpy, &ev.xcookie );
                auto event = type::cast<XIDeviceEvent>( ev.xcookie.data );

                  if( event->evtype == XI_TouchUpdate )
                    { onTouchMove.emit( event->event_x, event->event_y, event->detail ); }

                elif( event->evtype == XI_TouchBegin )
                    { onTouchDown.emit( event->event_x, event->event_y, event->detail ); }

                elif( event->evtype == XI_TouchEnd )
                    { onTouchUp.emit( event->event_x, event->event_y, event->detail ); }

                XFreeEventData( obj->dpy, &ev.xcookie );
            }
        
        coNext; } coGoto(1);

    coFinish
    }

    /*─······································································─*/

    ptr_t<float> get_screen_size() const noexcept{
        Screen* scr = DefaultScreenOfDisplay( obj->dpy ); if( scr==nullptr )
        { return nullptr; } return ptr_t<float>({ scr->width, scr->height });
	};

    /*─······································································─*/

	void move( int x, int y ) const noexcept { 
        Window win = XRootWindow(obj->dpy,DefaultScreen( obj->dpy ));
        XIDeviceEvent event; memset( &event, 0, sizeof(event) );
        XEvent xevent; memset( &xevent, 0, sizeof(xevent) );

        event.evtype    = XI_TouchUpdate;
        event.deviceid  = obj->deviceID;
        event.type      = GenericEvent;
        event.time      = CurrentTime;
        event.event     = win;
        event.root      = win;
        event.event_x   = x;
        event.event_y   = y;

        xevent.xcookie.type      = GenericEvent;
        xevent.type              = GenericEvent;
        xevent.xcookie.data      = &event;

        XSendEvent( obj->dpy, win, 1, 0xfff, &xevent );
        XFlush(obj->dpy);
	}

	void begin( int x, int y ) const noexcept { 
        Window win = XRootWindow(obj->dpy,DefaultScreen( obj->dpy ));
        XIDeviceEvent event; memset( &event, 0, sizeof(event) );
        XEvent xevent; memset( &xevent, 0, sizeof(xevent) );

        event.evtype        = XI_TouchBegin;
        event.deviceid      = obj->deviceID;
        event.type          = GenericEvent;
        event.time          = CurrentTime;
        event.event         = win;
        event.root          = win;
        event.event_x       = x;
        event.event_y       = y;

        xevent.xcookie.type = GenericEvent;
        xevent.type         = GenericEvent;
        xevent.xcookie.data = &event;

        XSendEvent( obj->dpy, win, 1, 0xfff, &xevent );
        XFlush( obj->dpy );
	}

	void end( int x, int y ) const noexcept { 
        Window win = XRootWindow(obj->dpy,DefaultScreen( obj->dpy ));
        XIDeviceEvent event; memset( &event, 0, sizeof(event) );
        XEvent xevent; memset( &xevent, 0, sizeof(xevent) );

        event.deviceid      = obj->deviceID;
        event.type          = GenericEvent;
        event.evtype        = XI_TouchEnd;
        event.time          = CurrentTime;
        event.event         = win;
        event.root          = win;
        event.event_x       = x;
        event.event_y       = y;

        xevent.xcookie.type = GenericEvent;
        xevent.type         = GenericEvent;
        xevent.xcookie.data = &event;

        XSendEvent( obj->dpy, win, 1, 0xfff, &xevent );
        XFlush( obj->dpy );
	}

    /*─······································································─*/

    touch_t ( int deviceID=0 ) : obj( new NODE() ) {
        obj->dpy = XOpenDisplay( nullptr ); if ( !obj->dpy ) { 
            throw except_t("Unable to open X display"); 
        return; } obj->deviceID = deviceID; next();
    }

   ~touch_t () noexcept {
        if( obj.count() > 1 ){ return; }
        if( obj->dpy != nullptr ){ XCloseDisplay(obj->dpy); }
    }

};}

/*────────────────────────────────────────────────────────────────────────────*/

#endif

/*────────────────────────────────────────────────────────────────────────────*/