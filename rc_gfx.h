#ifndef RC_GFX_INCLUDED
#define RC_GFX_INCLUDED

#include <SDL2/SDL.h>
#include <irrlicht.h>
#include <iostream>

using namespace irr;

using namespace core;
using namespace video;
using namespace scene;

struct SDLKeyMap
{
    SDLKeyMap() {}
    SDLKeyMap(s32 x11, s32 win32)
        : SDLKey(x11), Win32Key(win32)
    {
    }

    s32 SDLKey;
    s32 Win32Key;

    bool operator<(const SDLKeyMap& o) const
    {
        return SDLKey<o.SDLKey;
    }
};

core::array<SDLKeyMap> KeyMap;

void createKeyMap()
{
	// I don't know if this is the best method  to create
	// the lookuptable, but I'll leave it like that until
	// I find a better version.

	KeyMap.reallocate(105);

	// buttons missing

	KeyMap.push_back(SDLKeyMap(SDLK_BACKSPACE, irr::EKEY_CODE::KEY_BACK));
	KeyMap.push_back(SDLKeyMap(SDLK_TAB, irr::EKEY_CODE::KEY_TAB));
	KeyMap.push_back(SDLKeyMap(SDLK_CLEAR, irr::EKEY_CODE::KEY_CLEAR));
	KeyMap.push_back(SDLKeyMap(SDLK_RETURN, irr::EKEY_CODE::KEY_RETURN));

	// combined modifiers missing

	KeyMap.push_back(SDLKeyMap(SDLK_PAUSE, irr::EKEY_CODE::KEY_PAUSE));
	KeyMap.push_back(SDLKeyMap(SDLK_CAPSLOCK, irr::EKEY_CODE::KEY_CAPITAL));

	// asian letter keys missing

	KeyMap.push_back(SDLKeyMap(SDLK_ESCAPE, irr::EKEY_CODE::KEY_ESCAPE));

	// asian letter keys missing

	KeyMap.push_back(SDLKeyMap(SDLK_SPACE, irr::EKEY_CODE::KEY_SPACE));
	KeyMap.push_back(SDLKeyMap(SDLK_PAGEUP, irr::EKEY_CODE::KEY_PRIOR));
	KeyMap.push_back(SDLKeyMap(SDLK_PAGEDOWN, irr::EKEY_CODE::KEY_NEXT));
	KeyMap.push_back(SDLKeyMap(SDLK_END, irr::EKEY_CODE::KEY_END));
	KeyMap.push_back(SDLKeyMap(SDLK_HOME, irr::EKEY_CODE::KEY_HOME));
	KeyMap.push_back(SDLKeyMap(SDLK_LEFT, irr::EKEY_CODE::KEY_LEFT));
	KeyMap.push_back(SDLKeyMap(SDLK_UP, irr::EKEY_CODE::KEY_UP));
	KeyMap.push_back(SDLKeyMap(SDLK_RIGHT, irr::EKEY_CODE::KEY_RIGHT));
	KeyMap.push_back(SDLKeyMap(SDLK_DOWN, irr::EKEY_CODE::KEY_DOWN));

	// select missing
	KeyMap.push_back(SDLKeyMap(SDLK_PRINTSCREEN, irr::EKEY_CODE::KEY_PRINT));
	// execute missing
	KeyMap.push_back(SDLKeyMap(SDLK_PRINTSCREEN, irr::EKEY_CODE::KEY_SNAPSHOT));

	KeyMap.push_back(SDLKeyMap(SDLK_INSERT, irr::EKEY_CODE::KEY_INSERT));
	KeyMap.push_back(SDLKeyMap(SDLK_DELETE, irr::EKEY_CODE::KEY_DELETE));
	KeyMap.push_back(SDLKeyMap(SDLK_HELP, irr::EKEY_CODE::KEY_HELP));

	KeyMap.push_back(SDLKeyMap(SDLK_0, irr::EKEY_CODE::KEY_KEY_0));
	KeyMap.push_back(SDLKeyMap(SDLK_1, irr::EKEY_CODE::KEY_KEY_1));
	KeyMap.push_back(SDLKeyMap(SDLK_2, irr::EKEY_CODE::KEY_KEY_2));
	KeyMap.push_back(SDLKeyMap(SDLK_3, irr::EKEY_CODE::KEY_KEY_3));
	KeyMap.push_back(SDLKeyMap(SDLK_4, irr::EKEY_CODE::KEY_KEY_4));
	KeyMap.push_back(SDLKeyMap(SDLK_5, irr::EKEY_CODE::KEY_KEY_5));
	KeyMap.push_back(SDLKeyMap(SDLK_6, irr::EKEY_CODE::KEY_KEY_6));
	KeyMap.push_back(SDLKeyMap(SDLK_7, irr::EKEY_CODE::KEY_KEY_7));
	KeyMap.push_back(SDLKeyMap(SDLK_8, irr::EKEY_CODE::KEY_KEY_8));
	KeyMap.push_back(SDLKeyMap(SDLK_9, irr::EKEY_CODE::KEY_KEY_9));

	KeyMap.push_back(SDLKeyMap(SDLK_a, irr::EKEY_CODE::KEY_KEY_A));
	KeyMap.push_back(SDLKeyMap(SDLK_b, irr::EKEY_CODE::KEY_KEY_B));
	KeyMap.push_back(SDLKeyMap(SDLK_c, irr::EKEY_CODE::KEY_KEY_C));
	KeyMap.push_back(SDLKeyMap(SDLK_d, irr::EKEY_CODE::KEY_KEY_D));
	KeyMap.push_back(SDLKeyMap(SDLK_e, irr::EKEY_CODE::KEY_KEY_E));
	KeyMap.push_back(SDLKeyMap(SDLK_f, irr::EKEY_CODE::KEY_KEY_F));
	KeyMap.push_back(SDLKeyMap(SDLK_g, irr::EKEY_CODE::KEY_KEY_G));
	KeyMap.push_back(SDLKeyMap(SDLK_h, irr::EKEY_CODE::KEY_KEY_H));
	KeyMap.push_back(SDLKeyMap(SDLK_i, irr::EKEY_CODE::KEY_KEY_I));
	KeyMap.push_back(SDLKeyMap(SDLK_j, irr::EKEY_CODE::KEY_KEY_J));
	KeyMap.push_back(SDLKeyMap(SDLK_k, irr::EKEY_CODE::KEY_KEY_K));
	KeyMap.push_back(SDLKeyMap(SDLK_l, irr::EKEY_CODE::KEY_KEY_L));
	KeyMap.push_back(SDLKeyMap(SDLK_m, irr::EKEY_CODE::KEY_KEY_M));
	KeyMap.push_back(SDLKeyMap(SDLK_n, irr::EKEY_CODE::KEY_KEY_N));
	KeyMap.push_back(SDLKeyMap(SDLK_o, irr::EKEY_CODE::KEY_KEY_O));
	KeyMap.push_back(SDLKeyMap(SDLK_p, irr::EKEY_CODE::KEY_KEY_P));
	KeyMap.push_back(SDLKeyMap(SDLK_q, irr::EKEY_CODE::KEY_KEY_Q));
	KeyMap.push_back(SDLKeyMap(SDLK_r, irr::EKEY_CODE::KEY_KEY_R));
	KeyMap.push_back(SDLKeyMap(SDLK_s, irr::EKEY_CODE::KEY_KEY_S));
	KeyMap.push_back(SDLKeyMap(SDLK_t, irr::EKEY_CODE::KEY_KEY_T));
	KeyMap.push_back(SDLKeyMap(SDLK_u, irr::EKEY_CODE::KEY_KEY_U));
	KeyMap.push_back(SDLKeyMap(SDLK_v, irr::EKEY_CODE::KEY_KEY_V));
	KeyMap.push_back(SDLKeyMap(SDLK_w, irr::EKEY_CODE::KEY_KEY_W));
	KeyMap.push_back(SDLKeyMap(SDLK_x, irr::EKEY_CODE::KEY_KEY_X));
	KeyMap.push_back(SDLKeyMap(SDLK_y, irr::EKEY_CODE::KEY_KEY_Y));
	KeyMap.push_back(SDLKeyMap(SDLK_z, irr::EKEY_CODE::KEY_KEY_Z));

        // TODO:
	//KeyMap.push_back(SDLKeyMap(SDLK_LSUPER, KEY_LWIN));
        // TODO:
	//KeyMap.push_back(SDLKeyMap(SDLK_RSUPER, KEY_RWIN));
	// apps missing
	KeyMap.push_back(SDLKeyMap(SDLK_POWER, irr::EKEY_CODE::KEY_SLEEP)); //??

	KeyMap.push_back(SDLKeyMap(SDLK_KP_0, irr::EKEY_CODE::KEY_NUMPAD0));
	KeyMap.push_back(SDLKeyMap(SDLK_KP_1, irr::EKEY_CODE::KEY_NUMPAD1));
	KeyMap.push_back(SDLKeyMap(SDLK_KP_2, irr::EKEY_CODE::KEY_NUMPAD2));
	KeyMap.push_back(SDLKeyMap(SDLK_KP_3, irr::EKEY_CODE::KEY_NUMPAD3));
	KeyMap.push_back(SDLKeyMap(SDLK_KP_4, irr::EKEY_CODE::KEY_NUMPAD4));
	KeyMap.push_back(SDLKeyMap(SDLK_KP_5, irr::EKEY_CODE::KEY_NUMPAD5));
	KeyMap.push_back(SDLKeyMap(SDLK_KP_6, irr::EKEY_CODE::KEY_NUMPAD6));
	KeyMap.push_back(SDLKeyMap(SDLK_KP_7, irr::EKEY_CODE::KEY_NUMPAD7));
	KeyMap.push_back(SDLKeyMap(SDLK_KP_8, irr::EKEY_CODE::KEY_NUMPAD8));
	KeyMap.push_back(SDLKeyMap(SDLK_KP_9, irr::EKEY_CODE::KEY_NUMPAD9));
	KeyMap.push_back(SDLKeyMap(SDLK_KP_MULTIPLY, irr::EKEY_CODE::KEY_MULTIPLY));
	KeyMap.push_back(SDLKeyMap(SDLK_KP_PLUS, irr::EKEY_CODE::KEY_ADD));
//	KeyMap.push_back(SDLKeyMap(SDLK_KP_, KEY_SEPARATOR));
	KeyMap.push_back(SDLKeyMap(SDLK_KP_MINUS, irr::EKEY_CODE::KEY_SUBTRACT));
	KeyMap.push_back(SDLKeyMap(SDLK_KP_PERIOD, irr::EKEY_CODE::KEY_DECIMAL));
	KeyMap.push_back(SDLKeyMap(SDLK_KP_DIVIDE, irr::EKEY_CODE::KEY_DIVIDE));

	KeyMap.push_back(SDLKeyMap(SDLK_F1,  irr::EKEY_CODE::KEY_F1));
	KeyMap.push_back(SDLKeyMap(SDLK_F2,  irr::EKEY_CODE::KEY_F2));
	KeyMap.push_back(SDLKeyMap(SDLK_F3,  irr::EKEY_CODE::KEY_F3));
	KeyMap.push_back(SDLKeyMap(SDLK_F4,  irr::EKEY_CODE::KEY_F4));
	KeyMap.push_back(SDLKeyMap(SDLK_F5,  irr::EKEY_CODE::KEY_F5));
	KeyMap.push_back(SDLKeyMap(SDLK_F6,  irr::EKEY_CODE::KEY_F6));
	KeyMap.push_back(SDLKeyMap(SDLK_F7,  irr::EKEY_CODE::KEY_F7));
	KeyMap.push_back(SDLKeyMap(SDLK_F8,  irr::EKEY_CODE::KEY_F8));
	KeyMap.push_back(SDLKeyMap(SDLK_F9,  irr::EKEY_CODE::KEY_F9));
	KeyMap.push_back(SDLKeyMap(SDLK_F10, irr::EKEY_CODE::KEY_F10));
	KeyMap.push_back(SDLKeyMap(SDLK_F11, irr::EKEY_CODE::KEY_F11));
	KeyMap.push_back(SDLKeyMap(SDLK_F12, irr::EKEY_CODE::KEY_F12));
	KeyMap.push_back(SDLKeyMap(SDLK_F13, irr::EKEY_CODE::KEY_F13));
	KeyMap.push_back(SDLKeyMap(SDLK_F14, irr::EKEY_CODE::KEY_F14));
	KeyMap.push_back(SDLKeyMap(SDLK_F15, irr::EKEY_CODE::KEY_F15));
	// no higher F-keys

        // TODO:
	//KeyMap.push_back(SDLKeyMap(SDLK_NUMLOCK, KEY_NUMLOCK));
	KeyMap.push_back(SDLKeyMap(SDLK_SCROLLLOCK, irr::EKEY_CODE::KEY_SCROLL));
	KeyMap.push_back(SDLKeyMap(SDLK_LSHIFT, irr::EKEY_CODE::KEY_LSHIFT));
	KeyMap.push_back(SDLKeyMap(SDLK_RSHIFT, irr::EKEY_CODE::KEY_RSHIFT));
	KeyMap.push_back(SDLKeyMap(SDLK_LCTRL,  irr::EKEY_CODE::KEY_LCONTROL));
	KeyMap.push_back(SDLKeyMap(SDLK_RCTRL,  irr::EKEY_CODE::KEY_RCONTROL));
	KeyMap.push_back(SDLKeyMap(SDLK_LALT,  irr::EKEY_CODE::KEY_LMENU));
	KeyMap.push_back(SDLKeyMap(SDLK_RALT,  irr::EKEY_CODE::KEY_RMENU));

	KeyMap.push_back(SDLKeyMap(SDLK_PLUS,   irr::EKEY_CODE::KEY_PLUS));
	KeyMap.push_back(SDLKeyMap(SDLK_COMMA,  irr::EKEY_CODE::KEY_COMMA));
	KeyMap.push_back(SDLKeyMap(SDLK_MINUS,  irr::EKEY_CODE::KEY_MINUS));
	KeyMap.push_back(SDLKeyMap(SDLK_PERIOD, irr::EKEY_CODE::KEY_PERIOD));

	// some special keys missing

	KeyMap.sort();
}

IrrlichtDevice* device;
irr::video::IVideoDriver * VideoDriver;
SDL_Window* window;


bool rc_windowOpenEx(std::string title, int x, int y, int w, int h, bool stencil_buffer, bool fullscreen, bool vsync)
{
    if(SDL_Init(SDL_INIT_EVENTS | SDL_INIT_TIMER | SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_HAPTIC | SDL_INIT_SENSOR | SDL_INIT_NOPARACHUTE) < 0) //Audio causes init to fail on Fedora40 so I am leaving it out for now
    {
        //os::Printer::log("SDL_Init Error: ", SDL_GetError());
        std::cout << "No DICE" << std::endl;
        return 0;
    }

    uint32_t flags = SDL_WINDOW_OPENGL;
    flags |= (fullscreen ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0);

    window = SDL_CreateWindow(title.c_str(), x, y, w, h, flags);
    SIrrlichtCreationParameters irr_creation_params;
    irr_creation_params.DeviceType = EIDT_SDL;
    irr_creation_params.DriverType = video::EDT_OPENGL;
    irr_creation_params.WindowId = window;
    irr_creation_params.WindowSize = dimension2d<u32>((u32)w, (u32)h);
    irr_creation_params.Bits = 32;
    irr_creation_params.Fullscreen = fullscreen;
    irr_creation_params.Stencilbuffer = stencil_buffer;
    irr_creation_params.Vsync = vsync;
    irr_creation_params.EventReceiver = 0;
    irr_creation_params.WindowPosition = position2d<s32>(x, y);

	device = createDeviceEx(irr_creation_params);


	if (!device)
    {
        std::cout << "A problem occurred" << std::endl;
        return false;
    }

    std::cout << "G2G" << std::endl;
    return true;
}

irr::s32 MouseX, MouseY, MouseXRel, MouseYRel;
irr::u32 MouseButtonStates;

bool rc_update()
{
    if(!device->run())
        return false;

    SEvent irrevent;
	SDL_Event SDL_event;
	bool Close = false;

	while ( !Close && SDL_PollEvent( &SDL_event ) )
	{
		// os::Printer::log("event: ", core::stringc((int)SDL_event.type).c_str(),   ELL_INFORMATION);	// just for debugging

		switch ( SDL_event.type )
		{
		case SDL_MOUSEMOTION:
			irrevent.EventType = irr::EET_MOUSE_INPUT_EVENT;
			irrevent.MouseInput.Event = irr::EMIE_MOUSE_MOVED;
			MouseX = irrevent.MouseInput.X = SDL_event.motion.x;
			MouseY = irrevent.MouseInput.Y = SDL_event.motion.y;
			MouseXRel = SDL_event.motion.xrel;
			MouseYRel = SDL_event.motion.yrel;
			irrevent.MouseInput.ButtonStates = MouseButtonStates;

			device->postEventFromUser(irrevent);
			break;

		case SDL_MOUSEBUTTONDOWN:
		case SDL_MOUSEBUTTONUP:

			irrevent.EventType = irr::EET_MOUSE_INPUT_EVENT;
			irrevent.MouseInput.X = SDL_event.button.x;
			irrevent.MouseInput.Y = SDL_event.button.y;

			irrevent.MouseInput.Event = irr::EMIE_MOUSE_MOVED;

			switch(SDL_event.button.button)
			{
			case SDL_BUTTON_LEFT:
				if (SDL_event.type == SDL_MOUSEBUTTONDOWN)
				{
					irrevent.MouseInput.Event = irr::EMIE_LMOUSE_PRESSED_DOWN;
					MouseButtonStates |= irr::EMBSM_LEFT;
				}
				else
				{
					irrevent.MouseInput.Event = irr::EMIE_LMOUSE_LEFT_UP;
					MouseButtonStates &= !irr::EMBSM_LEFT;
				}
				break;

			case SDL_BUTTON_RIGHT:
				if (SDL_event.type == SDL_MOUSEBUTTONDOWN)
				{
					irrevent.MouseInput.Event = irr::EMIE_RMOUSE_PRESSED_DOWN;
					MouseButtonStates |= irr::EMBSM_RIGHT;
				}
				else
				{
					irrevent.MouseInput.Event = irr::EMIE_RMOUSE_LEFT_UP;
					MouseButtonStates &= !irr::EMBSM_RIGHT;
				}
				break;

			case SDL_BUTTON_MIDDLE:
				if (SDL_event.type == SDL_MOUSEBUTTONDOWN)
				{
					irrevent.MouseInput.Event = irr::EMIE_MMOUSE_PRESSED_DOWN;
					MouseButtonStates |= irr::EMBSM_MIDDLE;
				}
				else
				{
					irrevent.MouseInput.Event = irr::EMIE_MMOUSE_LEFT_UP;
					MouseButtonStates &= !irr::EMBSM_MIDDLE;
				}
				break;

			case SDL_MOUSEWHEEL:
				irrevent.MouseInput.Event = irr::EMIE_MOUSE_WHEEL;
				irrevent.MouseInput.Wheel = SDL_event.wheel.y;
				break;
			}

			irrevent.MouseInput.ButtonStates = MouseButtonStates;

			if (irrevent.MouseInput.Event != irr::EMIE_MOUSE_MOVED)
			{
				device->postEventFromUser(irrevent);

				if ( irrevent.MouseInput.Event >= EMIE_LMOUSE_PRESSED_DOWN && irrevent.MouseInput.Event <= EMIE_MMOUSE_PRESSED_DOWN )
				{
					u32 clicks = device->checkSuccessiveClicks(irrevent.MouseInput.X, irrevent.MouseInput.Y, irrevent.MouseInput.Event);
					if ( clicks == 2 )
					{
						irrevent.MouseInput.Event = (EMOUSE_INPUT_EVENT)(EMIE_LMOUSE_DOUBLE_CLICK + irrevent.MouseInput.Event-EMIE_LMOUSE_PRESSED_DOWN);
						device->postEventFromUser(irrevent);
					}
					else if ( clicks == 3 )
					{
						irrevent.MouseInput.Event = (EMOUSE_INPUT_EVENT)(EMIE_LMOUSE_TRIPLE_CLICK + irrevent.MouseInput.Event-EMIE_LMOUSE_PRESSED_DOWN);
						device->postEventFromUser(irrevent);
					}
				}
			}
			break;

		case SDL_KEYDOWN:
		case SDL_KEYUP:
			{
				SDLKeyMap mp;
				mp.SDLKey = SDL_event.key.keysym.sym;
				s32 idx = KeyMap.binary_search(mp);

				EKEY_CODE key;
				if (idx == -1)
					key = (EKEY_CODE)0;
				else
					key = (EKEY_CODE)KeyMap[idx].Win32Key;

				irrevent.EventType = irr::EET_KEY_INPUT_EVENT;
				irrevent.KeyInput.Char = SDL_event.key.keysym.sym;
				irrevent.KeyInput.Key = key;
				irrevent.KeyInput.PressedDown = (SDL_event.type == SDL_KEYDOWN);
				irrevent.KeyInput.Shift = (SDL_event.key.keysym.mod & KMOD_SHIFT) != 0;
				irrevent.KeyInput.Control = (SDL_event.key.keysym.mod & KMOD_CTRL ) != 0;
				device->postEventFromUser(irrevent);
			}
			break;

		case SDL_QUIT:
			//std::cout << "CLOSE WIN" << std::endl;
			Close = true;
			break;

		case SDL_WINDOWEVENT:
			if (SDL_event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
			{
			// FIXME: Implement more precise window control
				// FIXME: Check if the window is game window
				s32 Width = SDL_event.window.data1;
                s32 Height = SDL_event.window.data2;
                //resizeWindow(Width, Height);
                if (VideoDriver)
                    VideoDriver->OnResize(core::dimension2d<u32>(Width, Height));

			}
			break;

		case SDL_USEREVENT:
			irrevent.EventType = irr::EET_USER_EVENT;
			irrevent.UserEvent.UserData1 = reinterpret_cast<uintptr_t>(SDL_event.user.data1);
			irrevent.UserEvent.UserData2 = reinterpret_cast<uintptr_t>(SDL_event.user.data2);

			device->postEventFromUser(irrevent);
			break;

		default:
			break;
		} // end switch

	} // end while

    return (!Close);
}

#endif // RC_GFX_INCLUDED
