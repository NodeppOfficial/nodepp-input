/*
 * Copyright 2023 The Nodepp Project Authors. All Rights Reserved.
 *
 * Licensed under the MIT (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://github.com/NodeppOficial/nodepp/blob/main/LICENSE
 */

/*────────────────────────────────────────────────────────────────────────────*/

#ifndef NODEPP_WINDOWS_GAMEPAD
#define NODEPP_WINDOWS_GAMEPAD

/*────────────────────────────────────────────────────────────────────────────*/

namespace nodepp { class gamepad_t : public generator_t {
protected:

    struct NODE {
        XINPUT_STATE dpy, prev;
        array_t<int> button;
        int deviceID = 0;
    };  ptr_t<NODE> obj;

public:

    event_t<uint>           onButtonRelease;
    event_t<uint>           onButtonPress;
    event_t<uint,uint,uint> onMotionMove;

    /*─······································································─*/

    int next() noexcept {
    coBegin

        if( XInputGetState( obj->deviceID, &obj->dpy ) == ERROR_SUCCESS ) {

            uchar x=1; while( x!=0 ){
                if( obj->dpy.Gamepad.wButtons & x ){
                if( is_button_pressed(x) ){ coGoto(0); }
                    for( ulong y=obj->button.size(); y--; ){
                     if( obj->button[y] == x ){ coGoto(0); }
                       } obj->button.push( x ); 
                         onButtonPress.emit( x );
                } else {
                if( is_button_released(x) ){ coGoto(0); }
                    for( ulong y=obj->button.size(); y--; ){
                     if( obj->button[y] == x ) 
                       { obj->button.erase(y); }
                       } onButtonRelease.emit( x ); 
                }        x = x << 1;
            }

            if(
                obj->dpy.Gamepad.sThumbLX != obj->prev.Gamepad.sThumbLX ||
                obj->dpy.Gamepad.sThumbLY != obj->prev.Gamepad.sThumbLY
            ){  onMotionMove( obj->dpy.Gamepad.sThumbLX, obj->dpy.Gamepad.sThumbLY, 1 ); }

            if(
                obj->dpy.Gamepad.sThumbRX != obj->prev.Gamepad.sThumbRX ||
                obj->dpy.Gamepad.sThumbRY != obj->prev.Gamepad.sThumbRY
            ){  onMotionMove( obj->dpy.Gamepad.sThumbRX, obj->dpy.Gamepad.sThumbRY, 2 ); }

            if(
                obj->dpy.Gamepad.bLeftTrigger  != obj->prev.Gamepad.bLeftTrigger ||
                obj->dpy.Gamepad.bRightTrigger != obj->prev.Gamepad.bRightTrigger
            ){  onMotionMove( obj->dpy.Gamepad.bLeftTrigger, obj->dpy.Gamepad.bRightTrigger, 0 ); }
        
            coNext; memcpy( &obj->prev, &obj->dpy, sizeof(XINPUT_STATE) ); 
        }   coGoto(0);
    
    coFinish
    }

    /*─······································································─*/

	void move( int x, int y, int button ) const noexcept { 
        if( XInputGetState( obj->deviceID, &obj->dpy ) == ERROR_SUCCESS ){
        if( button == 0 ){
            obj->dpy.Gamepad.bLeftTrigger  = x % 255;
            obj->dpy.Gamepad.bRightTrigger = y % 255;
        } elif( button == 1 ){
            obj->dpy.Gamepad.sThumbLX = x;
            obj->dpy.Gamepad.sThumbLY = y;
        } elif( button == 2 ){
            obj->dpy.Gamepad.sThumbRX = x;
            obj->dpy.Gamepad.sThumbRY = y;
        }   XInputSetState( obj->deviceID, &obj->dpy );
        }
	}

	void release( int button ) const noexcept { 
        if( XInputGetState( obj->deviceID, &obj->dpy ) == ERROR_SUCCESS ){
            obj->dpy.Gamepad.wButtons &= ~button;
            XInputSetState( obj->deviceID, &obj->dpy );
        }
	}

	void press( int button ) const noexcept { 
        if( XInputGetState( obj->deviceID, &obj->dpy ) == ERROR_SUCCESS ){
            obj->dpy.Gamepad.wButtons |= button;
            XInputSetState( obj->deviceID, &obj->dpy );
        }
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

    gamepad_t ( int deviceID=0 ) : obj( new NODE() ) { obj->deviceID = deviceID; next(); }

};}

/*────────────────────────────────────────────────────────────────────────────*/

#endif

/*────────────────────────────────────────────────────────────────────────────*/