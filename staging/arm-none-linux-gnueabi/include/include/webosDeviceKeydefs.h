// @@@LICENSE
//
//      Copyright (c) 2008-2012 Hewlett-Packard Development Company, L.P.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// LICENSE@@@

enum Key {
	
	Key_Invalid		= -1,
	Key_Null		= 0x00,
	Key_Backspace	= 0x08,
    Key_Tab         = 0x09,
	Key_Return      = 0x0D,
	Key_Escape      = 0x1B,
	Key_Space       = 0x20,
	Key_Exclamation	= 0x21,
	Key_DoubleQuote	= 0x22,
	Key_PoundSign	= 0x23,
	Key_DollarSign	= 0x24,
	Key_EuroSign	= 0x20ac,
	Key_Percent		= 0x25,
	Key_Ampersand	= 0x26,
	Key_SingleQuote = 0x27,
	Key_LeftParen   = 0x28,
	Key_RightParen  = 0x29,
	Key_Asterik     = 0x2A,
	Key_Plus        = 0x2B,
	Key_Comma       = 0x2C,
	Key_Minus       = 0x2D,
	Key_Period      = 0x2E,
	Key_Slash       = 0x2F,
	Key_0           = 0x30,
	Key_1           = 0x31,
	Key_2           = 0x32,
	Key_3           = 0x33,
	Key_4           = 0x34,
	Key_5           = 0x35,
	Key_6           = 0x36,
	Key_7           = 0x37,
	Key_8           = 0x38,
	Key_9           = 0x39,
	Key_Colon       = 0x3A,
	Key_SemiColon   = 0x3B,
	Key_Less        = 0x3C,
	Key_Equal       = 0x3D,
	Key_Greater     = 0x3E,
	Key_Question    = 0x3F,
	Key_At          = 0x40,
	Key_A           = 0x41,
	Key_B           = 0x42,
	Key_C           = 0x43,
	Key_D           = 0x44,
	Key_E           = 0x45,
	Key_F           = 0x46,
	Key_G           = 0x47,
	Key_H           = 0x48,
	Key_I           = 0x49,
	Key_J           = 0x4A,
	Key_K           = 0x4B,
	Key_L           = 0x4C,
	Key_M           = 0x4D,
	Key_N           = 0x4E,
	Key_O           = 0x4F,
	Key_P           = 0x50,
	Key_Q           = 0x51,
	Key_R           = 0x52,
	Key_S           = 0x53,
	Key_T           = 0x54,
	Key_U           = 0x55,
	Key_V           = 0x56,
	Key_W           = 0x57,
	Key_X           = 0x58,
	Key_Y           = 0x59,
	Key_Z           = 0x5A,
	Key_LeftBracket = 0x5B,
	Key_BackSlash   = 0x5C,
	Key_RightBracket = 0x5D,
	Key_Circum      = 0x5E,
	Key_UnderScore  = 0x5F,
	Key_BackQuote   = 0x60,
	Key_a           = 0x61,
	Key_b           = 0x62,
	Key_c           = 0x63,
	Key_d           = 0x64,
	Key_e           = 0x65,
	Key_f           = 0x66,
	Key_g           = 0x67,
	Key_h           = 0x68,
	Key_i           = 0x69,
	Key_j           = 0x6A,
	Key_k           = 0x6B,
	Key_l           = 0x6C,
	Key_m           = 0x6D,
	Key_n           = 0x6E,
	Key_o           = 0x6F,
	Key_p           = 0x70,
	Key_q           = 0x71,
	Key_r           = 0x72,
	Key_s           = 0x73,
	Key_t           = 0x74,
	Key_u           = 0x75,
	Key_v           = 0x76,
	Key_w           = 0x77,
	Key_x           = 0x78,
	Key_y           = 0x79,
	Key_z           = 0x7A,
	Key_LeftBrace   = 0x7B,
	Key_Bar         = 0x7C,
	Key_RightBrace  = 0x7D,
	Key_Tilde       = 0x7E,
	Key_Delete      = 0x7F,

	// Grave
	Key_a_grave		= 0xe0,
	Key_e_grave		= 0xe8, 
	Key_e_acute		= 0xe9, 	
	Key_c_cedilla	= 0xe7,
	
	// Diaeresis
	Key_A_diaeresis	= 0x00c4, //196
	Key_E_diaeresis	= 0x00cb, //203
	Key_O_diaeresis	= 0x00d6, //214
	Key_U_diaeresis	= 0x00dc, //220
	Key_SSet 		= 0x00df, //223
	Key_a_diaeresis	= 0x00e4, //228
	Key_e_diaeresis	= 0x00eb, //235 
	Key_o_diaeresis	= 0x00f6, //246
	Key_u_diaeresis	= 0x00fc, //252

	// Modifier keys
	Key_Shift       = 0x80,
	Key_Alt         = 0x81,
	Key_Ctrl        = 0x82,
	Key_Option      = 0x83,
	
	// Desktop F keys
	Key_F1          = 0x90,
	Key_F2          = 0x91,
	Key_F3          = 0x92,
	Key_F4          = 0x93,
	Key_F5          = 0x94,
	Key_F6          = 0x95,
	Key_F7          = 0x96,
	Key_F8          = 0x97,
	Key_F9          = 0x98,
	Key_F10         = 0x99,
	Key_F11         = 0x9A,
	Key_F12         = 0x9B,

	// UI Features
	// E000 .. F8FF is the unicode private use area

	// Device/Desktop Rocker/Up Keys
	Key_Up          = 0xE0A0,
	Key_Down        = 0xE0A1,
	Key_Left        = 0xE0A2,
	Key_Right       = 0xE0A3,
	Key_Center      = 0xE0A4,

 	// Desktop keys
	Key_Insert      = 0xE0B0,
	Key_Home        = 0xE0B1,
	Key_End         = 0xE0B2,
	Key_PageUp      = 0xE0B3,
	Key_PageDown    = 0xE0B4,

	// Device keys
	Key_HardPhone       = 0xE0C0,
	Key_HardHome        = 0xE0C1,
	Key_HardMail        = 0xE0C2,
	Key_HardCalendar    = 0xE0C3,
	Key_HardOk          = 0xE0C4,
	Key_HardPower       = 0xE0C5,
	Key_SoftLeft        = 0xE0C6,
	Key_SoftRight       = 0xE0C7,
	Key_VolumeUp        = 0xE0C8,
	Key_VolumeDown      = 0xE0C9,
	Key_SideButton      = 0xE0CA,
	Key_Brightness      = 0xE0CB,
	Key_Ringer	    	= 0xE0CD,
	Key_HeadsetButton   = 0xE0CE,

	// Device keys -- media
	Key_MediaPlay		= 0xE0D0,
	Key_MediaPause		= 0xE0D1,
	Key_MediaStop		= 0xE0D2,
	Key_MediaNext		= 0xE0D3,
	Key_MediaPrevious	= 0xE0D4,
	Key_MediaRepeatAll	= 0xE0D5,
	Key_MediaRepeatTrack	= 0xE0D6,
	Key_MediaRepeatNone	= 0xE0D7,
	Key_MediaShuffleOn	= 0xE0D8,
	Key_MediaShuffleOff	= 0xE0D9,
	
	Key_CoreNavi_Home			= Key_Home,
	Key_CoreNavi_QuickLaunch	= 0xE0E1,
	Key_CoreNavi_Previous		= 0xE0E2,
	Key_CoreNavi_Next			= 0xE0E3,
	Key_CoreNavi_Back			= Key_Escape,
	Key_CoreNavi_Menu			= 0xE0E5,
	Key_CoreNavi_Launcher		= Key_End,
	Key_Flick					= 0xE0E6, //Having Flick and Hold here are pretty nasty, as they are only there to pretend all gestures are 'keys'.
	Key_CoreNavi_Meta			= 0xE0E7,
	Key_Hold					= 0xE0E8,
	Key_CoreNavi_Down   		= 0xE0E9,

	// Device "keys" -- sticky
	Key_Slider          = 0xE0F0,
	Key_Optical         = 0xE0F1,
	Key_Headset         = 0xE0F2,
	Key_HeadsetMic      = 0xE0F3
	
};

enum VirtualKey {
	Vk_NULL = 0,
	Vk_LBUTTON =0x01, //  	Left mouse button
	Vk_RBUTTON 	=0x02, // 	Right mouse button
	Vk_CANCEL 	=0x03, // 	Control-break processing
	Vk_MBUTTON 	=0x04, // 	Middle mouse button (three-button mouse)
	Vk_XBUTTON1 	=0x05, // 	Windows 2000/XP/2003/Vista/2008: X1 mouse button
	Vk_XBUTTON2 	=0x06, // 	Windows 2000/XP/2003/Vista/2008: X2 mouse button
	//- 	07 	Undefined
	Vk_BACK 	=0x08, // 	BACKSPACE key
	Vk_TAB 	=0x09, // 	TAB key
	//- 	0A-0B 	Reserved
	Vk_CLEAR 	=0x0C, // 	CLEAR key
	Vk_RETURN 	=0x0D, // 	ENTER key
	//- 	0E-0F 	Undefined
	Vk_SHIFT 	=0x10, // 	SHIFT key
	Vk_CONTROL 	=0x11, // 	CTRL key
	Vk_MENU 	=0x12, // 	ALT key
	Vk_PAUSE 	=0x13, // 	PAUSE key
	Vk_CAPITAL 	=0x14, // 	CAPS LOCK key
	Vk_KANA 	=0x15, // 	Input Method Editor (IME) Kana mode
	Vk_HANGUEL 	=0x15, // 	IME Hanguel mode (maintained for compatibility; use Vk_HANGUL)
	Vk_HANGUL 	=0x15, // 	IME Hangul mode
	//- 	16 	Undefined
	Vk_JUNJA 	=0x17, // 	IME Junja mode
	Vk_FINAL 	=0x18, // 	IME final mode
	Vk_HANJA 	=0x19, // 	IME Hanja mode
	Vk_KANJI 	=0x19, // 	IME Kanji mode
	//- 	1A 	Undefined
	Vk_ESCAPE 	=0x1B, // 	ESC key
	Vk_CONVERT 	=0x1C, // 	IME convert (Reserved for Kanji systems)
	Vk_NONCONVERT 	=0x1D, // 	IME nonconvert (Reserved for Kanji systems)
	Vk_ACCEPT 		=0x1E, // 	IME accept (Reserved for Kanji systems)
	Vk_MODECHANGE 	=0x1F, // 	IME mode change request (Reserved for Kanji systems)
	Vk_SPACE 	=0x20, // 	SPACEBAR
	Vk_PRIOR 	=0x21, // 	PAGE UP key
	Vk_NEXT 	=0x22, // 	PAGE DOWN key
	Vk_END 	=0x23, // 	END key
	Vk_HOME 	=0x24, // 	HOME key
	Vk_LEFT 	=0x25, // 	LEFT ARROW key
	Vk_UP 	=0x26, // 	UP ARROW key
	Vk_RIGHT 	=0x27, // 	RIGHT ARROW key
	Vk_DOWN 	=0x28, // 	DOWN ARROW key
	Vk_SELECT 	=0x29, // 	SELECT key
	Vk_PRINT 	=0x2A, // 	PRINT key
	Vk_EXECUTE 	=0x2B, // 	EXECUTE key
	Vk_SNAPSHOT 	=0x2C, // 	PRINT SCREEN key for Windows 3.0 and later
	Vk_INSERT 	=0x2D, // 	INS key
	Vk_DELETE 	=0x2E, // 	DEL key
	Vk_HELP 	=0x2F, // 	HELP key
	Vk_0 	=0x30, // 	0 key
	Vk_1 	=0x31, // 	1 key
	Vk_2 	=0x32, // 	2 key
	Vk_3 	=0x33, // 	3 key
	Vk_4 	=0x34, // 	4 key
	Vk_5 	=0x35, // 	5 key
	Vk_6 	=0x36, // 	6 key
	Vk_7 	=0x37, // 	7 key
	Vk_8 	=0x38, // 	8 key
	Vk_9 	=0x39, // 	9 key
	//- 	3A-40 	Undefined
	Vk_A 	=0x41, // 	A key
	Vk_B 	=0x42, // 	B key
	Vk_C 	=0x43, // 	C key
	Vk_D 	=0x44, // 	D key
	Vk_E 	=0x45, // 	E key
	Vk_F 	=0x46, // 	F key
	Vk_G 	=0x47, // 	G key
	Vk_H 	=0x48, // 	H key
	Vk_I 	=0x49, // 	I key
	Vk_J 	=0x4A, // 	J key
	Vk_K 	=0x4B, // 	K key
	Vk_L 	=0x4C, // 	L key
	Vk_M 	=0x4D, // 	M key
	Vk_N 	=0x4E, // 	N key
	Vk_O 	=0x4F, // 	O key
	Vk_P 	=0x50, // 	P key
	Vk_Q 	=0x51, // 	Q key
	Vk_R 	=0x52, // 	R key
	Vk_S 	=0x53, // 	S key
	Vk_T 	=0x54, // 	T key
	Vk_U 	=0x55, // 	U key
	Vk_V 	=0x56, // 	V key
	Vk_W 	=0x57, // 	W key
	Vk_X 	=0x58, // 	X key
	Vk_Y 	=0x59, // 	Y key
	Vk_Z 	=0x5A, // 	Z key
	Vk_LWIN 	=0x5B, // 	Left Windows key (Microsoft Natural Keyboard)
	Vk_RWIN 	=0x5C, // 	Right Windows key (Microsoft Natural Keyboard)
	Vk_APPS 	=0x5D, // 	Applications key (Microsoft Natural Keyboard)
	//- 	5E 	Reserved
	Vk_SLEEP 	=0x5F,  //	Computer Sleep key
	Vk_NUMPAD0 	=0x60, // 	Numeric keypad 0 key
	Vk_NUMPAD1 	=0x61, // 	Numeric keypad 1 key
	Vk_NUMPAD2 	=0x62, // 	Numeric keypad 2 key
	Vk_NUMPAD3 	=0x63, // 	Numeric keypad 3 key
	Vk_NUMPAD4 	=0x64, // 	Numeric keypad 4 key
	Vk_NUMPAD5 	=0x65, // 	Numeric keypad 5 key
	Vk_NUMPAD6 	=0x66, // 	Numeric keypad 6 key
	Vk_NUMPAD7 	=0x67, // 	Numeric keypad 7 key
	Vk_NUMPAD8 	=0x68, // 	Numeric keypad 8 key
	Vk_NUMPAD9 	=0x69, // 	Numeric keypad 9 key
	Vk_MULTIPLY 	=0x6A, // 	Multiply key
	Vk_ADD =0x6B, // 	Add key
	Vk_SEPARATOR 	=0x6C , //	Separator key
	Vk_SUBTRACT 	=0x6D, // 	Subtract key
	Vk_DECIMAL 	=0x6E, // 	Decimal key
	Vk_DIVIDE 	=0x6F, // 	Divide key
	Vk_F1 	=0x70, // 	F1 key
	Vk_F2 	=0x71, // 	F2 key
	Vk_F3 	=0x72, // 	F3 key
	Vk_F4 	=0x73, // 	F4 key
	Vk_F5 	=0x74, // 	F5 key
	Vk_F6 	=0x75, // 	F6 key
	Vk_F7 	=0x76, // 	F7 key
	Vk_F8 	=0x77, // 	F8 key
	Vk_F9 	=0x78, // 	F9 key
	Vk_F10 	=0x79, // 	F10 key
	Vk_F11 	=0x7A, // 	F11 key
	Vk_F12 	=0x7B, // 	F12 key
	Vk_F13 	=0x7C, // 	F13 key
	Vk_F14 	=0x7D, // 	F14 key
	Vk_F15 	=0x7E, // 	F15 key
	Vk_F16 	=0x7F, // 	F16 key
	Vk_F17 	=0x80, // 	F17 key
	Vk_F18 	=0x81, // 	F18 key
	Vk_F19 	=0x82, // 	F19 key
	Vk_F20 	=0x83, // 	F20 key
	Vk_F21 	=0x84, // 	F21 key
	Vk_F22 	=0x85, // 	F22 key
	Vk_F23 	=0x86, // 	F23 key
	Vk_F24 	=0x87, // 	F24 key
	//- 	88-8F 	Unassigned
	Vk_NUMLOCK 	=0x90, // 	NUM LOCK key
	Vk_SCROLL 	=0x91, // 	SCROLL LOCK key
	Vk_OEM_NEC_EQUAL 	=0x92, // 	NEC PC-9800 kbd definitions: '=' key on numpad
	Vk_OEM_FJ_JISHO 	=0x92, // 	Fujitsu/OASYS kbd definitions: 'Dictionary' key
	Vk_OEM_FJ_MASSHOU 	=0x93, // 	Fujitsu/OASYS kbd definitions: 'Unregister word' key
	Vk_OEM_FJ_TOUROKU 	=0x94, // 	Fujitsu/OASYS kbd definitions: 'Register word' key
	Vk_OEM_FJ_LOYA 	=0x95, // 	Fujitsu/OASYS kbd definitions: 'Left OYAYUBI' key
	Vk_OEM_FJ_ROYA 	=0x96, // 	Fujitsu/OASYS kbd definitions: 'Right OYAYUBI' key
	//- 	97-9F 	Unassigned
	Vk_LSHIFT 	=0xA0, // 	Left SHIFT key
	Vk_RSHIFT 	=0xA1, // 	Right SHIFT key
	Vk_LCONTROL 	=0xA2, // 	Left CONTROL key
	Vk_RCONTROL 	=0xA3, // 	Right CONTROL key
	Vk_LMENU 	=0xA4, // 	Left MENU key
	Vk_RMENU 	=0xA5, // 	Right MENU key
	Vk_BROWSER_BACK 	=0xA6, // 	Windows 2000/XP/2003/Vista/2008: Browser Back key
	Vk_BROWSER_FORWARD 	=0xA7, // 	Windows 2000/XP/2003/Vista/2008: Browser Forward key
	Vk_BROWSER_REFRESH 	=0xA8, // 	Windows 2000/XP/2003/Vista/2008: Browser Refresh key
	Vk_BROWSER_STOP 	=0xA9, // 	Windows 2000/XP/2003/Vista/2008: Browser Stop key
	Vk_BROWSER_SEARCH 	=0xAA, // 	Windows 2000/XP/2003/Vista/2008: Browser Search key
	Vk_BROWSER_FAVORITES 	=0xAB, // 	Windows 2000/XP/2003/Vista/2008: Browser Favorites key
	Vk_BROWSER_HOME 	=0xAC, // 	Windows 2000/XP/2003/Vista/2008: Browser Start and Home key
	Vk_VOLUME_MUTE 	=0xAD, // 	Windows 2000/XP/2003/Vista/2008: Volume Mute key
	Vk_VOLUME_DOWN 	=0xAE, // 	Windows 2000/XP/2003/Vista/2008: Volume Down key
	Vk_VOLUME_UP 	=0xAF, // 	Windows 2000/XP/2003/Vista/2008: Volume Up key
	Vk_MEDIA_NEXT_TRACK 	=0xB0, // 	Windows 2000/XP/2003/Vista/2008: Next Track key
	Vk_MEDIA_PREV_TRACK 	=0xB1, // 	Windows 2000/XP/2003/Vista/2008: Previous Track key
	Vk_MEDIA_STOP 	=0xB2, // 	Windows 2000/XP/2003/Vista/2008: Stop Media key
	Vk_MEDIA_PLAY_PAUSE 	=0xB3, // 	Windows 2000/XP/2003/Vista/2008: Play/Pause Media key
	Vk_LAUNCH_MAIL 	=0xB4, // 	Windows 2000/XP/2003/Vista/2008: Start Mail key
	Vk_LAUNCH_MEDIA_SELECT 	=0xB5, // 	Windows 2000/XP/2003/Vista/2008: Select Media key
	Vk_LAUNCH_APP1 	=0xB6, // 	Windows 2000/XP/2003/Vista/2008: Start Application 1 key
	Vk_LAUNCH_APP2 	=0xB7, // 	Windows 2000/XP/2003/Vista/2008: Start Application 2 key
	//- 	B8-B9 	Reserved
	Vk_OEM_1 	=0xBA, // 	Windows 2000/XP/2003/Vista/2008: For the US standard keyboard, the ';:' key
	Vk_OEM_PLUS 	=0xBB, // 	Windows 2000/XP/2003/Vista/2008: For any country/region, the '+' key
	Vk_OEM_COMMA 	=0xBC, // 	Windows 2000/XP/2003/Vista/2008: For any country/region, the ',' key
	Vk_OEM_MINUS 	=0xBD, // 	Windows 2000/XP/2003/Vista/2008: For any country/region, the '-' key
	Vk_OEM_PERIOD 	=0xBE, // 	Windows 2000/XP/2003/Vista/2008: For any country/region, the '.' key
	Vk_OEM_2 	=0xBF, // 	Windows 2000/XP/2003/Vista/2008: For the US standard keyboard, the '/?' key
	Vk_OEM_3 	=0xC0, // 	Windows 2000/XP/2003/Vista/2008: For the US standard keyboard, the '`~' key
	//- 	C1-D7 	Reserved
	//- 	D8-DA 	Unassigned
	Vk_OEM_4 	=0xDB, // 	Windows 2000/XP/2003/Vista/2008: For the US standard keyboard, the '[{' key
	Vk_OEM_5 	=0xDC, // 	Windows 2000/XP/2003/Vista/2008: For the US standard keyboard, the '\|' key
	Vk_OEM_6 	=0xDD, // 	Windows 2000/XP/2003/Vista/2008: For the US standard keyboard, the ']}' key
	Vk_OEM_7 	=0xDE, // 	Windows 2000/XP/2003/Vista/2008: For the US standard keyboard, the 'single-quote/double-quote' key
	Vk_OEM_8 	=0xDF, // 	Used for miscellaneous characters; it can vary by keyboard.
	//- 	E0 	Reserved
	//	E1 	OEM specific
	Vk_OEM_102 	=0xE2, // 	Windows 2000/XP/2003/Vista/2008: Either the angle bracket key or the backslash key on the RT 102-key keyboard
	//- 	E3-E4 	OEM specific
	Vk_PROCESSKEY 	=0xE5, // 	Windows 95/98/Me, Windows NT/2000/XP/2003/Vista/2008: IME PROCESS key
	//- 	E6 	OEM specific
	Vk_PACKET 	=0xE7, // 	Windows 2000/XP/2003/Vista/2008: Used to pass Unicode characters as if they were keystrokes. The Vk_PACKET key is the low word of a 32-bit Virtual Key value used for non-keyboard input methods. For more information, see Remark in KEYBDINPUT , SendInput , WM_KEYDOWN , and WM_KEYUP
	//- 	E8 	Unassigned
	Vk_OEM_RESET 	=0xE9, // 	Only used by Nokia.
	Vk_OEM_JUMP 	=0xEA, // 	Only used by Nokia.
	Vk_OEM_PA1 	=0xEB, // 	Only used by Nokia.
	Vk_OEM_PA2 	=0xEC, // 	Only used by Nokia.
	Vk_OEM_PA3 	=0xED, // 	Only used by Nokia.
	Vk_OEM_WSCTRL 	=0xEE, // 	Only used by Nokia.
	Vk_OEM_CUSEL 	=0xEF, // 	Only used by Nokia.
	Vk_OEM_ATTN 	=0xF0, // 	Only used by Nokia.
	Vk_OEM_FINNISH 	=0xF1, // 	Only used by Nokia.
	Vk_OEM_COPY 	=0xF2, // 	Only used by Nokia.
	Vk_OEM_AUTO 	=0xF3, // 	Only used by Nokia.
	Vk_OEM_ENLW 	=0xF4, // 	Only used by Nokia.
	Vk_OEM_BACKTAB 	=0xF5, // 	Only used by Nokia.
	Vk_ATTN 	=0xF6, // 	Attn key
	Vk_CRSEL 	=0xF7, // 	CrSel key
	Vk_EXSEL 	=0xF8, // 	ExSel key
	Vk_EREOF 	=0xF9, // 	Erase EOF key
	Vk_PLAY 	=0xFA, // 	Play key
	Vk_ZOOM 	=0xFB, // 	Zoom key
	Vk_NONAME 	=0xFC, // 	Reserved for future use.
	Vk_PA1 	=0xFD, // 	PA1 key
	Vk_OEM_CLEAR 	=0xFE // 	Clear key	
};

