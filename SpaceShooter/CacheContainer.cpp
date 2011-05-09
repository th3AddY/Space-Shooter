#include "CacheContainer.h"

using namespace Shooter;

void CacheContainer::release()
{
	referenced.release();
}