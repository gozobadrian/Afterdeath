/*
	THIS FILE IS A PART OF GTA V SCRIPT HOOK SDK
				http://dev-c.com			
			(C) Alexander Blade 2015
*/

///MOD BY YUNoCake

#include "script.h"

#include <string>
#include <ctime>
#include <Windows.h>

bool get_key_pressed(int nVirtKey)
{
	return (GetAsyncKeyState(nVirtKey) & 0x8000) != 0;
}

DWORD trainerResetTime = 0;

bool mod_switch_pressed()
{
	return (GetTickCount() > trainerResetTime + 1000) && get_key_pressed(VK_NUMLOCK);
}

void reset_mod_switch()
{
	trainerResetTime = GetTickCount();
}

std::string statusText;
DWORD statusTextDrawTicksMax;
bool statusTextGxtEntry;

void update_status_text()
{
	if (GetTickCount() < statusTextDrawTicksMax)
	{
		UI::SET_TEXT_FONT(0);
		UI::SET_TEXT_SCALE(0.55, 0.65);
		UI::SET_TEXT_COLOUR(10, 152, 12, 255);
		UI::SET_TEXT_WRAP(0.0, 1.0);
		UI::SET_TEXT_CENTRE(1);
		UI::SET_TEXT_DROPSHADOW(0, 0, 0, 0, 0);
		UI::SET_TEXT_EDGE(1, 0, 0, 0, 205);
		if (statusTextGxtEntry)
		{
			UI::_SET_TEXT_ENTRY((char *)statusText.c_str());
		} else
		{
			UI::_SET_TEXT_ENTRY("STRING");
			UI::_ADD_TEXT_COMPONENT_STRING((char *)statusText.c_str());
		}
		UI::_DRAW_TEXT(0.1, 0.3);
	}
}

void set_status_text(std::string str, DWORD time = 2500, bool isGxtEntry = false)
{
	statusText = str;
	statusTextDrawTicksMax = GetTickCount() + time;
	statusTextGxtEntry = isGxtEntry;
}

bool modEnabled = true;
bool skipDead = false;

void afterDeath()
{
	    Player player = PLAYER::PLAYER_ID();

		if (get_key_pressed(VK_RETURN))
		{
			skipDead = true;
			GAMEPLAY::_0x2C2B3493FBF51C71(false); //GAMEPLAY::_DISABLE_AUTOMATIC_RESPAWN
			SCRIPT::SET_NO_LOADING_SCREEN(false);
			CAM::DO_SCREEN_FADE_OUT(4000);
		}
		else if (PLAYER::IS_PLAYER_DEAD(player) && skipDead == false)
		{
			GAMEPLAY::_0x2C2B3493FBF51C71(true); //GAMEPLAY::_DISABLE_AUTOMATIC_RESPAWN
			SCRIPT::SET_NO_LOADING_SCREEN(true);
            if (CAM::IS_SCREEN_FADED_OUT()) CAM::DO_SCREEN_FADE_IN(2000);
		}
		else if (PLAYER::IS_PLAYER_DEAD(player) == false)
		{
			skipDead = false;
		}
}

void main()
{
	while (true)
	{
		if (mod_switch_pressed())
		{
			reset_mod_switch();
			DWORD time = GetTickCount() + 1000;

			while (GetTickCount() < time)
			{
				update_status_text();
				WAIT(0);
			}
			reset_mod_switch();
		}
		afterDeath();
		WAIT(0);
	}
}

void ScriptMain()
{
	srand(GetTickCount());
	main();
}
