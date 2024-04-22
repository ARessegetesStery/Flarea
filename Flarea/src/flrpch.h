#ifndef _FLR_PCH
#define _FLR_PCH

#include <iostream>
#include <fstream>
#include <sstream>

#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cmath>
#include <cassert>
#include <algorithm>
#include <memory>
#include <filesystem>
#include <unordered_map>
#include <unordered_set>

#include <string>
#include <array>
#include <vector>
#include <deque>
#include <set>
#include <list>
#include <iterator>

#include <optional>
#include <variant>
#include <thread>

#include "glm/glm.hpp"

#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"

#include "Lua/lua.hpp"
#include "LuaBridge/LuaBridge.h"

#include "Util/Log.h"

#include "GLFW/glfw3.h"

// included in glfw, but conflicts with name in Renderer
#undef LoadImage

using std::cout, std::cin, std::endl;
using std::vector, std::string, std::deque;
namespace fs = std::filesystem;

#define FLR_DEBUG

//#define FLR_DISABLE_AUDIO

#define FLR_ASSERT_ENABLED

//#define FLR_RENDER_COLLIDER

//#define FLR_PRINT_RENDERQUEUE
//#define FLR_PRINT_INPUT

using LuaBool = bool;
using LuaInt = int64_t;
using LuaFloat = float;
using LuaString = string;

using LuaVar = std::variant<LuaBool, LuaInt, LuaFloat, LuaString>;

// TODO make a forward declaration for all of the classes

#ifdef FLR_ASSERT_ENABLED
#define FLR_CORE_ASSERT(x, ...) \
		if (!(x)) \
		{\
			FLR_CORE_ERROR("Assertion failed: {0}", __VA_ARGS__);\
			__debugbreak();\
		}
#define FLR_ASSERT(x, ...) \
		if (!(x)) \
		{\
			FLR_ERROR("Assertion failed: {0}", __VA_ARGS__); \
			__debugbreak(); \
		}
#else
#define FLR_CORE_ASSERT(x, ...)
#define FLR_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#endif
