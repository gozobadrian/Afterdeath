/*
	THIS FILE IS A PART OF GTA V SCRIPT HOOK SDK
				http://dev-c.com			
			(C) Alexander Blade 2015
*/

///Mod by YUNoCake

#include "script.h"
#include <fstream>
#include <string>
#include <ctime>
#include <Windows.h>

bool get_key_pressed(int nVirtKey)
{
	return (GetAsyncKeyState(nVirtKey) & 0x8000) != 0;
}

bool skipDead = false;
bool skipArrest = false;
int key,suicideKey;

void readConfigFile()
{
	std::ifstream file("Afterdeath.ini");
	std::string temp;

	std::getline(file, temp, ' ');
	key = atoi(temp.c_str());
	std::getline(file, temp);
	suicideKey = atoi(temp.c_str());
}

void afterDeath()
{
	    Player player = PLAYER::PLAYER_ID();

        //If player is dying
		if (PLAYER::IS_PLAYER_DEAD(player) && get_key_pressed(key))
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
            if (CAM::IS_SCREEN_FADED_OUT()) CAM::DO_SCREEN_FADE_IN(100);
		}
		else if (PLAYER::IS_PLAYER_DEAD(player) == false)
		{
			skipDead = false;
		}

		//If player is being arrested
		if (PLAYER::IS_PLAYER_BEING_ARRESTED(player,false) && get_key_pressed(key))
		{
			skipArrest = true;
			GAMEPLAY::_0x2C2B3493FBF51C71(false); //GAMEPLAY::_DISABLE_AUTOMATIC_RESPAWN
			SCRIPT::SET_NO_LOADING_SCREEN(false);
			CAM::DO_SCREEN_FADE_OUT(4000);
		}
		else if (PLAYER::IS_PLAYER_BEING_ARRESTED(player,false) && skipArrest == false)
		{
			GAMEPLAY::_0x2C2B3493FBF51C71(true); //GAMEPLAY::_DISABLE_AUTOMATIC_RESPAWN
			SCRIPT::SET_NO_LOADING_SCREEN(true);
			if (CAM::IS_SCREEN_FADED_OUT()) CAM::DO_SCREEN_FADE_IN(100);
		}
		else if (PLAYER::IS_PLAYER_BEING_ARRESTED(player, false) == false)
		{
			skipArrest = false;
		}
}

void suicide()
{
	Player player = PLAYER::PLAYER_ID();
	Ped playerPed = PLAYER::GET_PLAYER_PED(player);
	PED::EXPLODE_PED_HEAD(playerPed, 0x5FC3C11);
}

void main()
{
	readConfigFile();
	while (true)
	{
		afterDeath();
		if (get_key_pressed(suicideKey)) suicide();
		WAIT(0);
	}
}

void ScriptMain()
{
	srand(GetTickCount());
	main();
}
