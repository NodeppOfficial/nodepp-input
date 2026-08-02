//https://learn.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes

/*
#define K_LBUTTON  0x01
#define K_RBUTTON  0x02
#define K_CANCEL   0x03
#define K_MBUTTON  0x04
#define K_XBUTTON1 0x05
#define K_XBUTTON2 0x06

#define K_BACK     0x08
#define K_TAB      0x09
#define K_CLEAR    0x0C
#define K_RETURN   0x0D
#define K_SHIFT    0x10
#define K_CONTROL  0x11
#define K_MENU     0x12
#define K_PAUSE    0x13
#define K_CAPITAL  0x14
#define K_ESCAPE   0x1B

#define K_KANA     0x15
#define K_HANGUL   0x15
#define K_JUNGA    0x17
#define K_FINAL    0x18
#define K_HANJA    0x19
#define K_KANJI    0x19

#define K_IME_PRSS 0xE5
#define K_IME_ON   0x16
#define K_IME_OFF  0x1A

#define K_CONVER   0x1C
#define K_NCONVER  0x1D
#define K_ACCEPT   0x1E

#define K_0        0x30
#define K_1        0x31
#define K_2        0x32
#define K_3        0x33
#define K_4        0x34
#define K_5        0x35
#define K_6        0x36
#define K_7        0x37
#define K_8        0x38
#define K_9        0x39

#define K_A        0x41
#define K_B        0x42
#define K_C        0x43
#define K_D        0x44
#define K_E        0x45
#define K_F        0x46
#define K_G        0x47
#define K_H        0x48
#define K_I        0x49
#define K_J        0x4A
#define K_K        0x4B
#define K_L        0x4C
#define K_M        0x4D
#define K_N        0x4E
#define K_O        0x4F
#define K_P        0x50
#define K_Q        0x51
#define K_R        0x52
#define K_S        0x53
#define K_T        0x54
#define K_U        0x55
#define K_V        0x56
#define K_W        0x57
#define K_X        0x58
#define K_Y        0x59
#define K_Z        0x5A

#define K_F1       0x70
#define K_F2       0x71
#define K_F3       0x72
#define K_F4       0x73
#define K_F5       0x74
#define K_F6       0x75
#define K_F7       0x76
#define K_F8       0x77
#define K_F9       0x78
#define K_F10      0x79
#define K_F11      0x7A
#define K_F12      0x7B
#define K_F13      0x7C
#define K_F14      0x7D
#define K_F15      0x7E
#define K_F16      0x7F
#define K_F17      0x80
#define K_F18      0x81
#define K_F19      0x82
#define K_F20      0x83
#define K_F21      0x84
#define K_F22      0x85
#define K_F23      0x86
#define K_F24      0x87

#define K_MODECH   0x1F
#define K_SPACE    0x20
#define K_PRIOR    0x21
#define K_NEXT     0x22
#define K_END      0x23
#define K_HOME     0x24

#define K_LEFT     0x25
#define K_UP       0x26
#define K_RIGHT    0x27
#define K_DOWN     0x28
#define K_SELECT   0x29
#define K_PRINT    0x2A
#define K_EXECUTE  0x2B
#define K_SNAPSHOT 0x2C
#define K_INSERT   0x2D
#define K_DELETE   0x2E
#define K_HELP     0x2F

#define K_MENU     0x5B
#define K_MENU1    0x5C
#define K_MENU2    0x5D

#define K_SLEEP    0x5F
#define K_N0       0x60
#define K_N1       0x61
#define K_N2       0x62
#define K_N3       0x63
#define K_N4       0x64
#define K_N5       0x65
#define K_N6       0x66
#define K_N7       0x67
#define K_N8       0x68
#define K_N9       0x69
#define K_NMUL     0x6A
#define K_NADD     0x6B
#define K_NSEP     0x6C
#define K_NSUB     0x6D
#define K_NDEC     0x6E
#define K_NDIV     0x6F
#define K_NLOCK    0x90

#define K_SCROLL   0x91
#define K_LSHIFT   0xA0
#define K_RSHIFT   0xA1
#define K_LCNTRL   0xA2
#define K_RCNTRL   0xA3
#define K_LALT     0xA4
#define K_RALT     0xA5

#define K_BBACK    0xA6
#define K_BFORW    0xA7
#define K_BRFRS    0xA8
#define K_BSTOP    0xA9
#define K_BSRCH    0xAA
#define K_BFVRT    0xAB
#define K_BHOME    0xAC

#define K_VMUTE    0xAD
#define K_VDOWN    0xAE
#define K_VUP      0xAF

#define K_MNEXT    0xB0
#define K_MPREV    0xB1
#define K_MSTOP    0xB2
#define K_MPLAY    0xB3

#define K_OEM_1    0xBA
#define K_OEM_2    0xBF
#define K_OEM_3    0xC0
#define K_OEM_4    0xDB
#define K_OEM_5    0xDC
#define K_OEM_6    0xDD
#define K_OEM_7    0xDE
#define K_OEM_8    0xDF
#define K_OEM_9    0xFE

#define K_PLUS     0xBB
#define K_MINUS    0xBD
#define K_PERIOD   0xBE
#define K_COMMA    0xBC
#define K_ERASE    0xF9
#define K_EXSEL    0xF8
#define K_CRSEL    0xF7
*/

/*
 * Copyright 2023 The Nodepp Project Authors. All Rights Reserved.
 *
 * Licensed under the MIT (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://github.com/NodeppOficial/nodepp/blob/main/LICENSE
 */

/*────────────────────────────────────────────────────────────────────────────*/

#ifndef NODEPP_WINDOWS_KEYBOARD
#define NODEPP_WINDOWS_KEYBOARD

/*────────────────────────────────────────────────────────────────────────────*/

namespace nodepp { class keyboard_t : public generator_t {
protected:

    struct NODE {
        array_t<uint> key;
        MSG           msg;
    };  ptr_t<NODE> obj;

public:

    event_t<uint> onKeyRelease;
    event_t<uint> onKeyPress;
	
    /*─······································································─*/

    int next() noexcept {
    coBegin

        while( GetMessage( obj->msg, NULL, 0, 0 )==0 ){ coGoto(0); }
		TranslateMessage(obj->msg); DispatchMessage(obj->msg);

        if ( obj->msg.message == WM_KEYDOWN ) { 
             auto bt = obj->msg.wParam;
        for( ulong x=obj->key.size(); x--; ){
         if( obj->key[x] == bt ){ coGoto(0); }
           } obj->key.push( bt ); 
             onKeyPress.emit( bt );
        }

        elif( obj->msg.message == WM_KEYUP ) { 
              auto bt = obj->msg.wParam;
         for( ulong x=obj->key.size(); x--; ){
          if( obj->key[x] == bt ) 
            { obj->key.erase(x); }
            } onKeyRelease.emit( bt ); 
        }

    coGoto(0);
    coFinish
    }
	
    /*─······································································─*/

    bool is_key_released( uint btn ) const noexcept {
        if( obj->key.empty() ) return 1; 
        else { for( auto x : obj->key ){
          if ( x == btn ) return 0;
        }}                return 1;
    }

    bool is_key_pressed( uint btn ) const noexcept {
        if( obj->key.empty() ) return 0; 
        else { for( auto x : obj->key ){
          if ( x == btn ) return 1;
        }}                return 0;
    }
    
    /*─······································································─*/

	void release( int key ) const noexcept { 
		keybd_event( key, 0x45, 0, 0 ); 
	}

	void press( int key ) const noexcept { 
        keybd_event( key, 0x45, 2, 0 );
	}

    /*─······································································─*/

    keyboard_t () noexcept : obj( new NODE() ) { next(); }

};}

/*────────────────────────────────────────────────────────────────────────────*/

#endif

/*────────────────────────────────────────────────────────────────────────────*/