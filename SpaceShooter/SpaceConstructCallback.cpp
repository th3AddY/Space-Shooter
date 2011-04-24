#include "SpaceConstructCallback.h"

using namespace Shooter;

SpaceConstructCallback::SpaceConstructCallback(SpaceConstruct* c)
	: NodeCallback(),
	  m_spaceConstruct(c)
{

}

void SpaceConstructCallback::operator()(Node* node, NodeVisitor* nv)
{
	m_spaceConstruct->preRender();

	SpaceState* newState =
		m_spaceConstruct->getCurrentState()->update();

	traverse(node, nv);

	if (newState != 0)
		m_spaceConstruct->setState(newState);
}
