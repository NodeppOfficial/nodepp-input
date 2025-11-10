/*
 * Copyright 2023 The Nodepp Project Authors. All Rights Reserved.
 *
 * Licensed under the MIT (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://github.com/NodeppOficial/nodepp/blob/main/LICENSE
 */

/*────────────────────────────────────────────────────────────────────────────*/

#ifndef NODEPP_WINDOWS_TOUCH
#define NODEPP_WINDOWS_TOUCH

/*────────────────────────────────────────────────────────────────────────────*/

namespace nodepp { class touch_t : public generator_t {
protected:

    struct NODE {
        MSG      msg;
        int deviceID = 0;
    };  ptr_t<NODE> obj;

public:

    event_t<uint,uint,uint> onTouchDown;
    event_t<uint,uint,uint> onTouchMove;
    event_t<uint,uint,uint> onTouchUp;

    /*─······································································─*/

    int next() noexcept {
    coBegin

        while( GetMessage( obj->msg, NULL, 0, 0 )==0 ){ coGoto(0); }
		TranslateMessage(obj->msg); DispatchMessage(obj->msg);

        if( obj->msg.message == WM_TOUCH ){
            UINT numInputs = obj->msg.wParam;
            TOUCHINPUT* pInputs = new TOUCHINPUT[numInputs];

            if (GetTouchInputInfo( (HTOUCHINPUT)obj->msg.lParam, numInputs, &pInputs, sizeof(TOUCHINPUT) )) {
            for( uint x=0; x<pInputs.size(); x++ ) { auto y = pInputs[x];
                if ( y.dwFlags & TOUCHEVENTF_MOVE ){ onTouchMove.emit( y.x, y.y, x ); }
                if ( y.dwFlags & TOUCHEVENTF_DOWN ){ onTouchDown.emit( y.x, y.y, x ); }
                if ( y.dwFlags & TOUCHEVENTF_UP   ){ onTouchUp  .emit( y.x, y.y, x ); }
            }}

            delete[] pInputs;
            CloseTouchInputHandle( (HTOUCHINPUT)lParam );
        }

    coGoto(0);
    coFinish
    }

    /*─······································································─*/

    ptr_t<float> get_screen_size() const noexcept{
        auto size = get_screen_size(); return ptr_t<float>({
            ::GetSystemMetrics( SM_CXSCREEN ), 
            ::GetSystemMetrics( SM_CYSCREEN )
        });
	};

    /*─······································································─*/

	void move( int x, int y ) const noexcept { 
        TOUCHINPUT input; memset( &input, 0, sizeof(input) ); 

        input.dwFlags     = TOUCHEVENTF_MOVE;
        input.hSource     = nullptr;
        input.x           = x;
        input.y           = y;

        SendTouchInput( 1, &input );
	}

	void begin( int x, int y ) const noexcept { 
        TOUCHINPUT input; memset( &input, 0, sizeof(input) ); 

        input.dwFlags     = TOUCHEVENTF_DOWN;
        input.hSource     = nullptr;
        input.x           = x;
        input.y           = y;

        SendTouchInput( 1, &input );
	}

	void end( int x, int y ) const noexcept { 
        TOUCHINPUT input; memset( &input, 0, sizeof(input) ); 

        input.dwFlags     = TOUCHEVENTF_UP;
        input.hSource     = nullptr;
        input.x           = x;
        input.y           = y;

        SendTouchInput( 1, &input );
	}

    /*─······································································─*/

    touch_t () noexcept : obj( new NODE() ) { next(); }

};}

/*────────────────────────────────────────────────────────────────────────────*/

#endif

/*────────────────────────────────────────────────────────────────────────────*/