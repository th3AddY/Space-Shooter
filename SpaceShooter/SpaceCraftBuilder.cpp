#include "SpaceCraftBuilder.h"

using namespace Shooter;

SpaceCraft* SpaceCraftBuilder::build(char* filename, double* simTimeDiff)
{
	Node* node = fromFile(filename);

	try
	{
		SpaceCraft* spaceCraft = static_cast<SpaceCraft*>(node);
		spaceCraft->setSimTimePointer(simTimeDiff);

		return spaceCraft;
	}
	catch (int)
	{
		return 0;
	}
}

CacheContainer* SpaceCraftBuilder::load(char* filename)
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

		return new SpaceCraftContainer();
	}
	catch(const DOMException& e)
	{
		std::cout << e.getMessage() << std::endl;

		return new SpaceCraftContainer();
	}
	catch(const SAXException& e)
	{
		std::cout << e.getMessage() << std::endl;

		return new SpaceCraftContainer();
	}

	SpaceCraftContainer* container = parseXML(parser->getDocument());

	delete errorHandler;
	delete parser;

	return container;
}

Node* SpaceCraftBuilder::getNode(CacheContainer* container)
{
	try
	{
		SpaceCraftContainer* scontainer = static_cast<SpaceCraftContainer*>(container);

		SpaceCraft* spaceCraft = new SpaceCraft(scontainer->params);
		spaceCraft->addChild(scontainer->node);

		return spaceCraft;
	}
	catch(int)
	{
		return 0;
	}
}

SpaceCraftContainer* SpaceCraftBuilder::parseXML(DOMDocument* doc)
{
	SpaceCraftContainer* container = new SpaceCraftContainer();

	DOMNodeList* root = doc->getChildNodes();

	for (unsigned int i=0; i<root->getLength(); i++)
	{
	
		if (getLower(XMLString::transcode(root->item(i)->getNodeName())) == "spacecraft")
		{
			DOMNodeList* category = root->item(i)->getChildNodes();
			for (unsigned int j=0; j<category->getLength(); j++)
			{
				DOMNode* categoryNode = category->item(j);

				// MODEL
				if (getLower(XMLString::transcode(categoryNode->getNodeName())) == "model")
				{
					DOMNamedNodeMap* categoryAttributes = categoryNode->getAttributes();

					for (unsigned int k=0; k<categoryAttributes->getLength(); k++)
						if (getLower(XMLString::transcode(categoryAttributes->item(k)->getNodeName())) == "file")
						{
							container->modelFilename = XMLString::transcode(categoryAttributes->item(k)->getNodeValue());
							break;
						}
				}

				// PARAMS
				if (getLower(XMLString::transcode(categoryNode->getNodeName())) == "parameters")
				{
					DOMNodeList* categoryChilds = categoryNode->getChildNodes();

					for (unsigned int k=0; k<categoryChilds->getLength(); k++)
					{
						if (getLower(XMLString::transcode(categoryChilds->item(k)->getNodeName())) == "defaultspeed")
							container->params.defaultSpeed = XMLGetScalar(categoryChilds->item(k));

						if (getLower(XMLString::transcode(categoryChilds->item(k)->getNodeName())) == "minspeed")
							container->params.minSpeed = XMLGetScalar(categoryChilds->item(k));

						if (getLower(XMLString::transcode(categoryChilds->item(k)->getNodeName())) == "maxspeed")
							container->params.maxSpeed = XMLGetScalar(categoryChilds->item(k));

						if (getLower(XMLString::transcode(categoryChilds->item(k)->getNodeName())) == "forwardacceleration")
							container->params.forwardAcceleration = XMLGetScalar(categoryChilds->item(k));

						if (getLower(XMLString::transcode(categoryChilds->item(k)->getNodeName())) == "backwardacceleration")
							container->params.backwardAcceleration = XMLGetScalar(categoryChilds->item(k));

						if (getLower(XMLString::transcode(categoryChilds->item(k)->getNodeName())) == "defaultspeedacceleration")
							container->params.defaultSpeedAcceleration = XMLGetScalar(categoryChilds->item(k));

						if (getLower(XMLString::transcode(categoryChilds->item(k)->getNodeName())) == "maxlateraldeflection")
							container->params.maxLateralDeflection = XMLGetScalar(categoryChilds->item(k));

						if (getLower(XMLString::transcode(categoryChilds->item(k)->getNodeName())) == "maxattitudedeflection")
							container->params.maxAttitudeDeflection = XMLGetScalar(categoryChilds->item(k));

						if (getLower(XMLString::transcode(categoryChilds->item(k)->getNodeName())) == "attitudereduction")
							container->params.attitudeReduction = XMLGetScalar(categoryChilds->item(k));

						if (getLower(XMLString::transcode(categoryChilds->item(k)->getNodeName())) == "followerattitude")
							container->params.followerAttitude = XMLGetQuat(categoryChilds->item(k));

						if (getLower(XMLString::transcode(categoryChilds->item(k)->getNodeName())) == "followerposition")
							container->params.followerPosition = XMLGetVec3(categoryChilds->item(k));

						if (getLower(XMLString::transcode(categoryChilds->item(k)->getNodeName())) == "followerconvergence")
							container->params.followerConvergence = XMLGetScalar(categoryChilds->item(k));
					}
				}
			}

			break;
		}
	}

	container->node = ModelCache::get().fromFile(container->modelFilename);

	return container;
}