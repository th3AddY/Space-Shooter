#include "ModelCache.h"

using namespace Shooter;

CacheContainer* ModelCache::load(char* filename)
{
	XercesDOMParser* parser    = new XercesDOMParser();
	ErrorHandler* errorHandler = new HandlerBase();

	parser->setValidationScheme(XercesDOMParser::Val_Always);
	parser->setErrorHandler(errorHandler);

	try
	{
		parser->parse(filename);
	}
	catch(const XMLException& e)
	{
		std::cout << e.getMessage() << std::endl;

		return new CacheContainer();
	}
	catch(const DOMException& e)
	{
		std::cout << e.getMessage() << std::endl;

		return new CacheContainer();
	}
	catch(const SAXException& e)
	{
		std::cout << e.getMessage() << std::endl;

		return new CacheContainer();
	}

	CacheContainer* container = parseXML(parser->getDocument());

	delete errorHandler;
	delete parser;

	return container;
}

CacheContainer* ModelCache::parseXML(DOMDocument* doc)
{
	CacheContainer* container = new CacheContainer();

	Group* group = new Group();

	DOMNodeList* root = doc->getChildNodes();

	for (unsigned int i=0; i<root->getLength(); i++)
	{
		if (getLower(XMLString::transcode(root->item(i)->getNodeName())) == "model")
		{
			DOMNodeList* category = root->item(i)->getChildNodes();
			for (unsigned int j=0; j<category->getLength(); j++)
			{
				DOMNode* categoryNode = category->item(j);

				// MESH
				if (getLower(XMLString::transcode(categoryNode->getNodeName())) == "mesh")
				{
					DOMNamedNodeMap* categoryAttributes = categoryNode->getAttributes();
					DOMNodeList* categoryChilds = categoryNode->getChildNodes();

					PositionAttitudeTransform* transform = new PositionAttitudeTransform();
					group->addChild(transform);

					for (unsigned int k=0; k<categoryAttributes->getLength(); k++)
						if (getLower(XMLString::transcode(categoryAttributes->item(k)->getNodeName())) == "file")
						{
							transform->addChild(MeshCache::get().fromFile(XMLString::transcode(categoryAttributes->item(k)->getNodeValue())));
							break;
						}

					for (unsigned int k=0; k<categoryChilds->getLength(); k++)
					{
						if (getLower(XMLString::transcode(categoryChilds->item(k)->getNodeName())) == "position")
							transform->setPosition(XMLGetVec3(categoryChilds->item(k)));

						if (getLower(XMLString::transcode(categoryChilds->item(k)->getNodeName())) == "scale")
							transform->setScale(XMLGetVec3(categoryChilds->item(k)));

						if (getLower(XMLString::transcode(categoryChilds->item(k)->getNodeName())) == "attitude")
							transform->setAttitude(XMLGetQuat(categoryChilds->item(k)));
					}
				}
			}

			break;
		}
	}

	container->node = group;

	return container;
}