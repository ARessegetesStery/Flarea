#include "flrpch.h"

#include "Application/Application.h"

#include "Lua/lua.hpp"
#include "LuaBridge/LuaBridge.h"

int main(int argc, char** argv)
{
	FLR::Log::Init();

	FLR::Application* app = FLR::createApp();
	app->MainLoop();
	delete app;

    return 0;
}
