#include "SpaceCraftBuilder.h"

using namespace Shooter;

SpaceCraft* SpaceCraftBuilder::build(const char* filename, double* simTimeDiff)
{
	try
	{
		SpaceCraft* spaceCraft = static_cast<SpaceCraft*>(fromFile(filename));
		spaceCraft->setSimTimePointer(simTimeDiff);

		return spaceCraft;
	}
	catch (int)
	{
		return 0;
	}
}

CacheContainer* SpaceCraftBuilder::load(const char* filename)
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

Referenced* SpaceCraftBuilder::getReferenced(CacheContainer* container)
{
	try
	{
		SpaceCraftContainer* scontainer = static_cast<SpaceCraftContainer*>(container);

		SpaceCraft* spaceCraft = new SpaceCraft(scontainer->params);
		spaceCraft->addChild(static_cast<Node*>(scontainer->referenced.get()));

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

	if (getLower(XMLString::transcode(doc->getDocumentElement()->getNodeName())) != "spacecraft")
		return 0;

	DOMElement* modelElement = static_cast<DOMElement*>(doc->getElementsByTagName(XMLString::transcode("model"))->item(0));
	if (modelElement != 0)
	{
		DOMNamedNodeMap* categoryAttributes = modelElement->getAttributes();

		for (unsigned int k=0; k<categoryAttributes->getLength(); k++)
			if (getLower(XMLString::transcode(categoryAttributes->item(k)->getNodeName())) == "file")
			{
				container->referenced = ModelCache::get().loadModel(XMLString::transcode(categoryAttributes->item(k)->getNodeValue()));
				// container->modelFilename = XMLString::transcode(categoryAttributes->item(k)->getNodeValue());
				break;
			}
	}

	DOMElement* parametersElement = static_cast<DOMElement*>(doc->getElementsByTagName(XMLString::transcode("parameters"))->item(0));
	if (parametersElement != 0)
	{
		DOMNode* defaultspeed = parametersElement->getElementsByTagName(XMLString::transcode("defaultspeed"))->item(0);
		if (defaultspeed != 0)
			container->params.defaultSpeed = XMLGetScalar(defaultspeed);

		DOMNode* minspeed = parametersElement->getElementsByTagName(XMLString::transcode("minspeed"))->item(0);
		if (minspeed != 0)
			container->params.minSpeed = XMLGetScalar(minspeed);

		DOMNode* maxspeed = parametersElement->getElementsByTagName(XMLString::transcode("maxspeed"))->item(0);
		if (maxspeed != 0)
			container->params.maxSpeed = XMLGetScalar(maxspeed);

		DOMNode* forwardacceleration = parametersElement->getElementsByTagName(XMLString::transcode("forwardacceleration"))->item(0);
		if (forwardacceleration != 0)
			container->params.forwardAcceleration = XMLGetScalar(forwardacceleration);

		DOMNode* backwardacceleration = parametersElement->getElementsByTagName(XMLString::transcode("backwardacceleration"))->item(0);
		if (backwardacceleration != 0)
			container->params.backwardAcceleration = XMLGetScalar(backwardacceleration);

		DOMNode* defaultspeedacceleration = parametersElement->getElementsByTagName(XMLString::transcode("defaultspeedacceleration"))->item(0);
		if (defaultspeedacceleration != 0)
			container->params.defaultSpeedAcceleration = XMLGetScalar(defaultspeedacceleration);

		DOMNode* maxlateraldeflection = parametersElement->getElementsByTagName(XMLString::transcode("maxlateraldeflection"))->item(0);
		if (maxlateraldeflection != 0)
			container->params.maxLateralDeflection = XMLGetScalar(maxlateraldeflection);

		DOMNode* maxattitudedeflection = parametersElement->getElementsByTagName(XMLString::transcode("maxattitudedeflection"))->item(0);
		if (maxattitudedeflection != 0)
			container->params.maxAttitudeDeflection = XMLGetScalar(maxattitudedeflection);

		DOMNode* attitudereduction = parametersElement->getElementsByTagName(XMLString::transcode("attitudereduction"))->item(0);
		if (attitudereduction != 0)
			container->params.attitudeReduction = XMLGetScalar(attitudereduction);

		DOMNode* followerattitude = parametersElement->getElementsByTagName(XMLString::transcode("followerattitude"))->item(0);
		if (followerattitude != 0)
			container->params.followerAttitude = XMLGetQuat(followerattitude);

		DOMNode* followerposition = parametersElement->getElementsByTagName(XMLString::transcode("followerposition"))->item(0);
		if (followerposition != 0)
			container->params.followerPosition = XMLGetVec3(followerposition);

		DOMNode* followerconvergence = parametersElement->getElementsByTagName(XMLString::transcode("followerconvergence"))->item(0);
		if (followerconvergence != 0)
			container->params.followerConvergence = XMLGetScalar(followerconvergence);
	}

	return container;
}