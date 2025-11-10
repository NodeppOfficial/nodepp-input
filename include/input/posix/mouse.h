/*
 * Copyright 2023 The Nodepp Project Authors. All Rights Reserved.
 *
 * Licensed under the MIT (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://github.com/NodeppOficial/nodepp/blob/main/LICENSE
 */

/*────────────────────────────────────────────────────────────────────────────*/

#ifndef NODEPP_POSIX_MOUSE
#define NODEPP_POSIX_MOUSE

/*────────────────────────────────────────────────────────────────────────────*/

namespace nodepp { class mouse_t : public generator_t {
protected: 

    struct NODE {
        Display* dpy = nullptr;
        array_t<uint> button;
    };  ptr_t<NODE> obj;

public:

    event_t<uint>      onButtonRelease;
    event_t<uint>      onButtonPress;
    event_t<uint,uint> onMotionMove;

    /*─······································································─*/

    int next() noexcept {
    coBegin

        do{ auto events = ButtonPressMask | ButtonReleaseMask | ButtonMotionMask | PointerMotionMask;
            Window win  = XRootWindow( obj->dpy, DefaultScreen( obj->dpy ) );
            XSelectInput( obj->dpy, win, events );
        } while(0); coYield(1);

        while( XPending( obj->dpy ) > 0 ){
            XEvent ev; XNextEvent( obj->dpy, &ev );

            if( ev.type == MotionNotify ) { 
                auto bt =  ev.xmotion;
                onMotionMove.emit( bt.x, bt.y ); 
            }

            elif( ev.type == ButtonRelease ) { 
                 auto bt =  ev.xbutton.button;
            for( ulong x=obj->button.size(); x--; ){
             if( obj->button[x] == bt ) 
               { obj->button.erase(x); }
               } onButtonRelease.emit( bt ); 
            }

            elif( ev.type == ButtonPress ) { 
                 auto bt =  ev.xbutton.button;
            for( ulong x=obj->button.size(); x--; ){
             if( obj->button[x] == bt ){ coGoto(1); }
               } obj->button.push( bt ); 
                 onButtonPress.emit( bt );
            }
        
        coNext; } coGoto(1);
        
    coFinish
    }

    /*─······································································─*/

    ptr_t<float> get_screen_size() const noexcept{
        Screen* scr = DefaultScreenOfDisplay( obj->dpy ); if( scr == nullptr )
        { return nullptr; } return ptr_t<float>({ scr->width, scr->height });
	};

    ptr_t<int> get_position() const noexcept { 
        Window win = XRootWindow( obj->dpy, DefaultScreen( obj->dpy ) );
        uint mask; int rootX, rootY, winX, winY;

        XQueryPointer( 
            obj->dpy,  win,  &win,  &win, 
            &rootX, &rootY, &winX, &winY, 
            &mask 
        );
        
        return ptr_t<int>({ winX, winY, rootX, rootY });
    }

    /*─······································································─*/

    bool is_button_released( uint btn ) const noexcept {
        if( obj->button.empty() ) return 1; 
        else { for( auto x : obj->button ){
          if ( x == btn ) return 0;
        }}                return 1;
    }

    bool is_button_pressed( uint btn ) const noexcept {
        if( obj->button.empty() ) return 0; 
        else { for( auto x : obj->button ){
          if ( x == btn ) return 1;
        }}                return 0;
    }

    /*─······································································─*/

	void move( float x, float y ) const noexcept {
        Window id = DefaultScreen( obj->dpy );
        auto sx = get_screen_size(); if( sx==nullptr ){ return; }
		auto dx = x / 100.0f * sx[0];
		auto dy = y / 100.0f * sx[0];
        XTestFakeMotionEvent( obj->dpy, id, dx, dy, CurrentTime );
		XFlush( obj->dpy );
	}

	void press( int button ) const noexcept { 
        XTestFakeButtonEvent( obj->dpy, button, True, CurrentTime );
		XFlush( obj->dpy );
	}

	void release( int button ) const noexcept { 
        XTestFakeButtonEvent( obj->dpy, button, False, CurrentTime );
		XFlush( obj->dpy );
	}

    /*─······································································─*/

	void scroll_up  () const noexcept { press( 4 ); release( 4 ); }

	void scroll_down() const noexcept { press( 5 ); release( 5 ); }

    /*─······································································─*/

    mouse_t () : obj( new NODE() ) {
        obj->dpy = XOpenDisplay( nullptr ); if ( !obj->dpy ) { 
            throw except_t("Unable to open X display"); 
        return; } next();
    }

   ~mouse_t () noexcept {
        if( obj.count() > 1 ){ return; }
        if( obj->dpy != nullptr ){ XCloseDisplay(obj->dpy); }
    }

};}

/*────────────────────────────────────────────────────────────────────────────*/

#endif

/*────────────────────────────────────────────────────────────────────────────*/