#pragma once

#include <vector>

// #include <boost/algorithm/string.hpp>

#include "Cache.h"

// using namespace boost;
using namespace std;

namespace Shooter
{
	class ShaderCache : public Cache<ShaderCache>
	{
	public:
		Program* loadProgram(const char* shaderSource);

	protected:
		CacheContainer* load(const char* filename);
	};
}