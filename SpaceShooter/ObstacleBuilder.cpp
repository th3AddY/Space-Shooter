#include "ObstacleBuilder.h"

using namespace Shooter;

Obstacle* ObstacleBuilder::build(const char* filename, double* simTimeDiff)
{
	try
	{
		Obstacle* obstacle = static_cast<Obstacle*>(fromFile(filename));
		obstacle->setSimTimePointer(simTimeDiff);

		return obstacle;
	}
	catch (int)
	{
		return 0;
	}
}

Referenced* ObstacleBuilder::getReferenced(CacheContainer* container)
{
	try
	{
		Obstacle* obstacle = new Obstacle();
		obstacle->addChild(static_cast<Node*>(container->referenced.get()));

		return obstacle;
	}
	catch(int)
	{
		return 0;
	}
}

CacheContainer* ObstacleBuilder::load(const char* filename)
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

	CacheContainer* container = new CacheContainer();
	container->referenced = parseXML(parser->getDocument());

	delete errorHandler;
	delete parser;

	return container;
}

Node* ObstacleBuilder::parseXML(DOMDocument* doc)
{
	Group* group = new Group();

	if (getLower(XMLString::transcode(doc->getDocumentElement()->getNodeName())) != "obstacle")
		return 0;

	DOMNodeList* modelNodeList = doc->getDocumentElement()->getElementsByTagName(XMLString::transcode("model"));
	for (unsigned int i = 0; i<modelNodeList->getLength(); i++)
	{
		DOMElement* modelElement = static_cast<DOMElement*>(modelNodeList->item(i));
		DOMNamedNodeMap* modelAttributes = modelElement->getAttributes();

		PositionAttitudeTransform* transform = new PositionAttitudeTransform();
		group->addChild(transform);

		for (unsigned int j=0; j<modelAttributes->getLength(); j++)
			if (getLower(XMLString::transcode(modelAttributes->item(j)->getNodeName())) == "file")
			{
				transform->addChild(ModelCache::get().loadModel(XMLString::transcode(modelAttributes->item(j)->getNodeValue())));
				break;
			}

		DOMNode* positionNode = modelElement->getElementsByTagName(XMLString::transcode("position"))->item(0);
		if (positionNode != 0)
			transform->setPosition(XMLGetVec3(positionNode));

		DOMNode* scaleNode = modelElement->getElementsByTagName(XMLString::transcode("scale"))->item(0);
		if (scaleNode != 0)
			transform->setScale(XMLGetVec3(scaleNode));

		DOMNode* attutideNode = modelElement->getElementsByTagName(XMLString::transcode("attitude"))->item(0);
		if (attutideNode != 0)
			transform->setAttitude(XMLGetQuat(attutideNode));
	}

	return group;
}