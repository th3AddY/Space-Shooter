#include "MatterCallback.h"

using namespace Shooter;

void MatterCallback::operator()(Node* node, NodeVisitor* nv)
{
	try
	{
		Matter* matter = dynamic_cast<Matter*>(node);
		matter->update();
	} catch(int) {}

	traverse(node, nv);
}