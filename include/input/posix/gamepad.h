/*
 * Copyright 2023 The Nodepp Project Authors. All Rights Reserved.
 *
 * Licensed under the MIT (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://github.com/NodeppOficial/nodepp/blob/main/LICENSE
 */

/*────────────────────────────────────────────────────────────────────────────*/

#ifndef NODEPP_POSIX_GAMEPAD
#define NODEPP_POSIX_GAMEPAD

/*────────────────────────────────────────────────────────────────────────────*/

namespace nodepp { class gamepad_t : public generator_t {
protected:

    struct NODE {
        Display* dpy = nullptr;
        array_t<int>   button;
        int deviceID = 0;
    };  ptr_t<NODE> obj;

public:

    event_t<uint>           onButtonRelease;
    event_t<uint>           onButtonPress;
    event_t<uint,uint,uint> onMotionMove;

    /*─······································································─*/

    int next() noexcept {
    coBegin

        do{ uint   idx  = DefaultScreen( obj->dpy );
            Window win  = XRootWindow  ( obj->dpy, idx );

            uchar mask[(XI_LASTEVENT + 7)/8] = {0};
            XISetMask(mask, XI_ButtonRelease);
            XISetMask(mask, XI_ButtonPress);
            XISetMask(mask, XI_Motion);

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

                if( event->evtype == XI_Motion ) { 
                    onMotionMove.emit( event->event_x, event->event_y, event->detail ); 
                }

                elif( event->evtype == XI_ButtonRelease ) { 
                      auto bt = event->detail; 
                 for( ulong x=obj->button.size(); x--; ){
                  if( obj->button[x] == bt ) 
                    { obj->button.erase(x); }
                    } onButtonRelease.emit( bt ); 
                }

                elif( event->evtype == XI_ButtonPress ) {
                      auto bt = event->detail; 
                 for( ulong x=obj->button.size(); x--; ){
                  if( obj->button[x] == bt ){ coGoto(1); }
                    } obj->button.push( bt ); 
                      onButtonPress.emit( bt );
                }
        
                XFreeEventData( obj->dpy, &ev.xcookie );
            }
        
          coNext; 
        } coGoto(1);

    coFinish
    }

    /*─······································································─*/

	void move( int x, int y, int button ) const noexcept { 
        Window win = XRootWindow(obj->dpy,DefaultScreen( obj->dpy ));
        XIDeviceEvent event; memset( &event, 0, sizeof(event) );
        XEvent xevent; memset( &xevent, 0, sizeof(xevent) );

        event.deviceid      = obj->deviceID;
        event.type          = GenericEvent;
        event.time          = CurrentTime;
        event.evtype        = XI_Motion;
        event.detail        = button;
        event.event         = win;
        event.root          = win;
        event.event_x       = x;
        event.event_y       = y;

        xevent.xcookie.type = GenericEvent;
        xevent.type         = GenericEvent;
        xevent.xcookie.data = &event;

        XSendEvent( obj->dpy, win, 1, 0xfff, &xevent );
        XFlush(obj->dpy);
	}

	void release( int button ) const noexcept { 
        Window win = XRootWindow(obj->dpy,DefaultScreen( obj->dpy ));
        XIDeviceEvent event; memset( &event, 0, sizeof(event) );
        XEvent xevent; memset( &xevent, 0, sizeof(xevent) );

        event.evtype        = XI_ButtonPress;
        event.deviceid      = obj->deviceID;
        event.type          = GenericEvent;
        event.time          = CurrentTime;
        event.detail        = button;
        event.event         = win;
        event.root          = win;

        xevent.xcookie.type = GenericEvent;
        xevent.type         = GenericEvent;
        xevent.xcookie.data = &event;

        XSendEvent( obj->dpy, win, 1, 0xfff, &xevent );
        XFlush( obj->dpy );
	}

	void press( int button ) const noexcept { 
        Window win = XRootWindow(obj->dpy,DefaultScreen( obj->dpy ));
        XIDeviceEvent event; memset( &event, 0, sizeof(event) );
        XEvent xevent; memset( &xevent, 0, sizeof(xevent) );

        event.evtype        = XI_ButtonRelease;
        event.deviceid      = obj->deviceID;
        event.type          = GenericEvent;
        event.time          = CurrentTime;
        event.detail        = button;
        event.event         = win;
        event.root          = win;

        xevent.xcookie.type = GenericEvent;
        xevent.type         = GenericEvent;
        xevent.xcookie.data = &event;

        XSendEvent( obj->dpy, win, 1, 0xfff, &xevent );
        XFlush( obj->dpy );
	}

    /*─······································································─*/

    bool is_button_released( uint btn ) const noexcept {
        if( obj->button.empty() ) return 1; 
        else { for( auto x : obj->button ){
           if( x == btn ) return 0;
        }}                return 1;
    }

    bool is_button_pressed( uint btn ) const noexcept {
        if( obj->button.empty() ) return 0; 
        else { for( auto x : obj->button ){
           if( x == btn ) return 1;
        }}                return 0;
    }

    /*─······································································─*/

    gamepad_t ( int deviceID=0 ) : obj( new NODE() ) {
        obj->dpy = XOpenDisplay( nullptr ); if ( !obj->dpy ) { 
            throw except_t("Unable to open X display"); 
        return; } obj->deviceID = deviceID; next();
    }

   ~gamepad_t () noexcept {
        if( obj.count() > 1 ){ return; }
        if( obj->dpy != nullptr ){ XCloseDisplay(obj->dpy); }
    }

};}

/*────────────────────────────────────────────────────────────────────────────*/

#endif

/*────────────────────────────────────────────────────────────────────────────*/