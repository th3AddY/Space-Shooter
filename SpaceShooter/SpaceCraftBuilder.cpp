#include "SpaceCraftBuilder.h"

using namespace Shooter;

SpaceCraftBuilder* SpaceCraftBuilder::m_instance = 0;

SpaceCraftBuilder* SpaceCraftBuilder::get()
{
	if (m_instance == 0)
		m_instance = new SpaceCraftBuilder();

	return m_instance;
}

void SpaceCraftBuilder::clear()
{
	for(unsigned int i=0; i<m_spaceCraftCache.size(); i++)
	{
		m_spaceCraftCache[i]->node.release();
		delete m_spaceCraftCache[i];
	}

	m_spaceCraftCache.clear();
	delete m_instance;
	m_instance = 0;
}

SpaceCraft* SpaceCraftBuilder::fromFile(char* filename, double* simTimeDiff)
{
	SpaceCraftData* data = findCache(filename);

	if (data == 0)
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

			return 0;
		}
		catch(const DOMException& e)
		{
			std::cout << e.getMessage() << std::endl;

			return 0;
		}
		catch(const SAXException& e)
		{
			std::cout << e.getMessage() << std::endl;

			return 0;
		}

		data = parseXML(parser->getDocument());

		data->filename = filename;
		buildSpaceCraftNode(data);

		m_spaceCraftCache.push_back(data);

		delete errorHandler;
		delete parser;
	}

	SpaceCraft* spaceCraft = new SpaceCraft(simTimeDiff, data->params);
	spaceCraft->addChild(data->node);

	return spaceCraft;
}

SpaceCraftData* SpaceCraftBuilder::findCache(char* filename)
{
	for (unsigned int i=0; i<m_spaceCraftCache.size(); i++)
		if (getLower(m_spaceCraftCache[i]->filename) == getLower(filename))
			return m_spaceCraftCache[i];

	return 0;
}

SpaceCraftData* SpaceCraftBuilder::parseXML(DOMDocument* doc)
{
	SpaceCraftData* data = new SpaceCraftData();

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
					DOMNodeList* categoryChilds = categoryNode->getChildNodes();

					for (unsigned int k=0; k<categoryAttributes->getLength(); k++)
						if (getLower(XMLString::transcode(categoryAttributes->item(k)->getNodeName())) == "file")
						{
							data->modelFilename = XMLString::transcode(categoryAttributes->item(k)->getNodeValue());
							break;
						}

					for (unsigned int k=0; k<categoryChilds->getLength(); k++)
					{
						if (getLower(XMLString::transcode(categoryChilds->item(k)->getNodeName())) == "position")
							data->position = XMLGetVec3(categoryChilds->item(k));

						if (getLower(XMLString::transcode(categoryChilds->item(k)->getNodeName())) == "scale")
							data->scale = XMLGetVec3(categoryChilds->item(k));

						if (getLower(XMLString::transcode(categoryChilds->item(k)->getNodeName())) == "attitude")
							data->attitude = XMLGetQuat(categoryChilds->item(k));
					}
				}

				// PARAMS
				if (getLower(XMLString::transcode(categoryNode->getNodeName())) == "parameters")
				{
					DOMNodeList* categoryChilds = categoryNode->getChildNodes();

					for (unsigned int k=0; k<categoryChilds->getLength(); k++)
					{
						if (getLower(XMLString::transcode(categoryChilds->item(k)->getNodeName())) == "defaultspeed")
							data->params.defaultSpeed = XMLGetScalar(categoryChilds->item(k));

						if (getLower(XMLString::transcode(categoryChilds->item(k)->getNodeName())) == "minspeed")
							data->params.minSpeed = XMLGetScalar(categoryChilds->item(k));

						if (getLower(XMLString::transcode(categoryChilds->item(k)->getNodeName())) == "maxspeed")
							data->params.maxSpeed = XMLGetScalar(categoryChilds->item(k));

						if (getLower(XMLString::transcode(categoryChilds->item(k)->getNodeName())) == "forwardacceleration")
							data->params.forwardAcceleration = XMLGetScalar(categoryChilds->item(k));

						if (getLower(XMLString::transcode(categoryChilds->item(k)->getNodeName())) == "backwardacceleration")
							data->params.backwardAcceleration = XMLGetScalar(categoryChilds->item(k));

						if (getLower(XMLString::transcode(categoryChilds->item(k)->getNodeName())) == "defaultspeedacceleration")
							data->params.defaultSpeedAcceleration = XMLGetScalar(categoryChilds->item(k));

						if (getLower(XMLString::transcode(categoryChilds->item(k)->getNodeName())) == "maxlateraldeflection")
							data->params.maxLateralDeflection = XMLGetScalar(categoryChilds->item(k));

						if (getLower(XMLString::transcode(categoryChilds->item(k)->getNodeName())) == "maxattitudedeflection")
							data->params.maxAttitudeDeflection = XMLGetScalar(categoryChilds->item(k));

						if (getLower(XMLString::transcode(categoryChilds->item(k)->getNodeName())) == "attitudereduction")
							data->params.attitudeReduction = XMLGetScalar(categoryChilds->item(k));

						if (getLower(XMLString::transcode(categoryChilds->item(k)->getNodeName())) == "followerattitude")
							data->params.followerAttitude = XMLGetQuat(categoryChilds->item(k));

						if (getLower(XMLString::transcode(categoryChilds->item(k)->getNodeName())) == "followerposition")
							data->params.followerPosition = XMLGetVec3(categoryChilds->item(k));

						if (getLower(XMLString::transcode(categoryChilds->item(k)->getNodeName())) == "followerconvergence")
							data->params.followerConvergence = XMLGetScalar(categoryChilds->item(k));
					}
				}
			}

			break;
		}
	}

	return data;
}

void SpaceCraftBuilder::buildSpaceCraftNode(SpaceCraftData* data)
{
	PositionAttitudeTransform* transform = new PositionAttitudeTransform();
	transform->setScale(data->scale);
	transform->setAttitude(data->attitude);
	transform->setPosition(data->position);

	transform->addChild(ModelCache::get()->fromFile(data->modelFilename));

	data->node = transform;

	/* PositionAttitudeTransform* transform = new PositionAttitudeTransform();
	transform->setScale(Vec3(0.23, 0.3, 0.3));
	transform->setAttitude(getQuatFromEuler(0, 0,3.141/2));

	transform->addChild(readNodeFile("GameData/models/Corsair/model.3ds"));

	addChild(transform); */
}