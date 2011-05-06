#include "Universe.h"

using namespace Shooter;

Universe::Universe()
	: Group(),
	  m_skyboxDirectory(""),
	  m_built(false),
	  m_humanPlayer(0)
{
	m_sceneGroup = new Group();
	m_menuGroup = new Group();

	addChild(m_menuGroup);
}

Universe::~Universe()
{
	m_sceneGroup.release();
	m_menuGroup.release();
}

void Universe::loadFromFile(char* filename)
{
	XercesDOMParser* parser    = new XercesDOMParser();
	ErrorHandler* errorHandler = new HandlerBase();

	parser->setValidationScheme(XercesDOMParser::Val_Always);
	parser->setErrorHandler(errorHandler);

	try
	{
		parser->parse(filename);
		loadFromDocument(parser->getDocument());
	}
	catch(const XMLException& e)
	{
		std::cout << e.getMessage() << std::endl;
	}
	catch(const DOMException& e)
	{
		std::cout << e.getMessage() << std::endl;
	}
	catch(const SAXException& e)
	{
		std::cout << e.getMessage() << std::endl;
	}

	delete errorHandler;
	delete parser;
}

void Universe::loadFromDocument(DOMDocument* doc)
{
	if (getLower(XMLString::transcode(doc->getDocumentElement()->getNodeName())) == "level")
	{
		DOMNode* skyboxNode = doc->getDocumentElement()->getElementsByTagName(XMLString::transcode("skybox"))->item(0);
		if (skyboxNode != 0)
		{
			DOMNamedNodeMap* skyboxAttributes = skyboxNode->getAttributes();
			for (unsigned int i=0; i<skyboxAttributes->getLength(); i++)
			{
				if (getLower(XMLString::transcode(skyboxAttributes->item(i)->getNodeName())) == "dir")
				{
					addSkybox(XMLString::transcode(skyboxAttributes->item(i)->getNodeValue()));
				}
			}
		}

		DOMElement* lightmodelElement = static_cast<DOMElement*>(doc->getDocumentElement()->getElementsByTagName(XMLString::transcode("lightmodel"))->item(0));
		if (lightmodelElement != 0)
		{
			DOMNode* lightmodelAmbientNode = lightmodelElement->getElementsByTagName(XMLString::transcode("ambient"))->item(0);
			if (lightmodelAmbientNode != 0)
			{
				LightModel* lm = new LightModel();
				lm->setAmbientIntensity(XMLGetColor(lightmodelAmbientNode));
				m_sceneGroup->getOrCreateStateSet()->setAttribute(lm, StateAttribute::ON);
			}

			DOMNodeList* lightSourceNodes = lightmodelElement->getElementsByTagName(XMLString::transcode("lightsource"));
			for (unsigned int i=0; i<lightSourceNodes->getLength(); i++)
			{
				DOMElement* lightSourceElement = static_cast<DOMElement*>(lightSourceNodes->item(i));
				LightSource* ls = new LightSource();

				DOMNode* positionNode = lightSourceElement->getElementsByTagName(XMLString::transcode("position"))->item(0);
				if (positionNode != 0)
					ls->getLight()->setPosition(Vec4(XMLGetVec3(positionNode), 1));

				DOMNode* directionNode = lightSourceElement->getElementsByTagName(XMLString::transcode("direction"))->item(0);
				if (directionNode != 0)
					ls->getLight()->setPosition(Vec4(XMLGetVec3(directionNode), 0));

				DOMNode* ambientNode = lightSourceElement->getElementsByTagName(XMLString::transcode("ambient"))->item(0);
				if (ambientNode != 0)
					ls->getLight()->setAmbient(XMLGetColor(ambientNode));

				DOMNode* diffuseNode = lightSourceElement->getElementsByTagName(XMLString::transcode("diffuse"))->item(0);
				if (diffuseNode != 0)
					ls->getLight()->setDiffuse(XMLGetColor(diffuseNode));

				DOMNode* specularNode = lightSourceElement->getElementsByTagName(XMLString::transcode("specular"))->item(0);
				if (specularNode != 0)
					ls->getLight()->setSpecular(XMLGetColor(specularNode));

				m_sceneGroup->addChild(ls);
			}
		}
	}
}

void Universe::addSkybox(char *dir)
{
	m_skyboxDirectory = dir;
}

void Universe::addPlayer(Player* player)
{
	m_players.push_back(player);

	try
	{
		Human* human = static_cast<Human*>(player);
		m_humanPlayer = human;
	} catch(int)
	{
	}
}

void Universe::addSpaceCraft(SpaceCraft* spaceCraft)
{
	m_spaceCrafts.push_back(spaceCraft);
}

Player* Universe::getPlayer(unsigned int i)
{
	return m_players[i];
}

unsigned int Universe::getPlayerCount()
{
	return m_players.size();
}

Human* Universe::getHumanPlayer()
{
	if (m_humanPlayer != 0)
		return m_humanPlayer;

	return 0;
}

Group* Universe::getSceneGroup()
{
	return m_sceneGroup;
}

Group* Universe::getMenuGroup()
{
	return m_menuGroup;
}

void Universe::useSceneGroup()
{
	removeChild(m_menuGroup);
	addChild(m_sceneGroup);

	for (unsigned int i=0; i<m_spaceCrafts.size(); i++)
		m_spaceCrafts[i]->setUpdateCallback(new MatterCallback());
	
}

void Universe::useMenuGroup()
{
	removeChild(m_sceneGroup);
	addChild(m_menuGroup);
}

int Universe::build()
{
	if (m_built==false) {

		// build skybox
		m_skyboxTransform = new PositionAttitudeTransform();
		if (m_skyboxDirectory) {
			Geode* skybox = createSkyboxGeode(m_skyboxDirectory);

			m_skyboxTransform->addChild(skybox);
			m_skyboxTransform->setScale(Vec3(10, 10, 10));
			m_sceneGroup->addChild(m_skyboxTransform);
		}

		// setup root stateset
		m_sceneGroup->getOrCreateStateSet()->setMode(GL_CULL_FACE, StateAttribute::ON);
		m_sceneGroup->getStateSet()->setMode(GL_NORMALIZE, StateAttribute::ON);
		m_sceneGroup->getStateSet()->setMode(GL_DEPTH_TEST, StateAttribute::ON);
		m_sceneGroup->getStateSet()->setMode(GL_LIGHTING, StateAttribute::ON);
		m_sceneGroup->getStateSet()->setMode(GL_LIGHT0, StateAttribute::ON);
		//////////////

		for (unsigned int i=0; i<m_spaceCrafts.size(); i++)
			m_sceneGroup->addChild(m_spaceCrafts[i]);

		m_built=true;
		return 0;
	} else
		return 1;
}

void Universe::destruct()
{
	if (m_skyboxDirectory!="")
	{
		removeChild(m_skyboxTransform);
		m_skyboxDirectory = "";
	}

	for (unsigned int i=0; i<m_spaceCrafts.size(); i++)
		m_sceneGroup->removeChild(m_spaceCrafts[i]);

	for (unsigned int i=0; i<m_players.size(); i++)
		delete m_players[i];
}

void Universe::updateSkybox(Follower* follower)
{
	m_skyboxTransform->setPosition(follower->getPosition());
}

bool Universe::isRunning()
{
	return true;
}