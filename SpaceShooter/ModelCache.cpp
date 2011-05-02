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

	CacheContainer* container = new CacheContainer();
	container->node = parseXML(parser->getDocument());

	delete errorHandler;
	delete parser;

	return container;
}

Node* ModelCache::parseXML(DOMDocument* doc)
{
	Group* group = new Group();

	if (getLower(XMLString::transcode(doc->getDocumentElement()->getNodeName())) != "model")
		return 0;

	DOMNodeList* meshList = doc->getDocumentElement()->getElementsByTagName(XMLString::transcode("mesh"));

	for (unsigned int i=0; i<meshList->getLength(); i++)
	{
		DOMElement* meshElement = static_cast<DOMElement*>(meshList->item(i));

		PositionAttitudeTransform* transform = new PositionAttitudeTransform();
		group->addChild(transform);

		DOMNamedNodeMap* meshAttributes = meshElement->getAttributes();
		for (unsigned int j=0; j<meshAttributes->getLength(); j++)
			if (getLower(XMLString::transcode(meshAttributes->item(j)->getNodeName())) == "file")
			{
				transform->addChild(MeshCache::get().fromFile(XMLString::transcode(meshAttributes->item(j)->getNodeValue())));
				break;
			}

		DOMNode* positionNode = meshElement->getElementsByTagName(XMLString::transcode("position"))->item(0);
		if (positionNode != 0)
			transform->setPosition(XMLGetVec3(positionNode));

		DOMNode* scaleNode = meshElement->getElementsByTagName(XMLString::transcode("scale"))->item(0);
		if (scaleNode != 0)
			transform->setScale(XMLGetVec3(scaleNode));

		DOMNode* attitudeNode = meshElement->getElementsByTagName(XMLString::transcode("attitude"))->item(0);
		if (attitudeNode != 0)
			transform->setAttitude(XMLGetQuat(attitudeNode));

		DOMNode* shaderNode = meshElement->getElementsByTagName(XMLString::transcode("shader"))->item(0);
		if (shaderNode != 0)
			parseShader(shaderNode, transform);

		DOMNode* materialNode = meshElement->getElementsByTagName(XMLString::transcode("material"))->item(0);
		if (materialNode != 0)
			parseMaterial(materialNode, transform);
	}

	return group;
}

void ModelCache::parseShader(DOMNode* domnode, Node* node)
{
	Program* program = new Program();

	DOMElement* shaderElement = static_cast<DOMElement*>(domnode);

	DOMNamedNodeMap* shaderAttributes = shaderElement->getAttributes();

	for (unsigned int i=0; i<shaderAttributes->getLength(); i++)
	{
		if (getLower(XMLString::transcode(shaderAttributes->item(i)->getNodeName())) == "fragment")
		{
			loadShaderSource(program, Shader::FRAGMENT, XMLString::transcode(shaderAttributes->item(i)->getNodeValue()));
			continue;
		}

		if (getLower(XMLString::transcode(shaderAttributes->item(i)->getNodeName())) == "vertex")
		{
			loadShaderSource(program, Shader::VERTEX, XMLString::transcode(shaderAttributes->item(i)->getNodeValue()));
			continue;
		}

		if (getLower(XMLString::transcode(shaderAttributes->item(i)->getNodeName())) == "geometry")
		{
			loadShaderSource(program, Shader::GEOMETRY, XMLString::transcode(shaderAttributes->item(i)->getNodeValue()));
			continue;
		}

		 if (getLower(XMLString::transcode(shaderAttributes->item(i)->getNodeName())) == "tesscontrol")
		 {
		 	loadShaderSource(program, Shader::TESSCONTROL, XMLString::transcode(shaderAttributes->item(i)->getNodeValue()));
			continue;
		 }

		if (getLower(XMLString::transcode(shaderAttributes->item(i)->getNodeName())) == "tessevaluation")
		{
			loadShaderSource(program, Shader::TESSEVALUATION, XMLString::transcode(shaderAttributes->item(i)->getNodeValue()));
			continue;
		}

		if (getLower(XMLString::transcode(shaderAttributes->item(i)->getNodeName())) == "undefined")
		{
			loadShaderSource(program, Shader::UNDEFINED, XMLString::transcode(shaderAttributes->item(i)->getNodeValue()));
			continue;
		}

	}

	int texLayer = 1;
	DOMNodeList* samplerNodes = shaderElement->getElementsByTagName(XMLString::transcode("sampler"));
	for (unsigned int i=0; i<samplerNodes->getLength(); i++)
	{

		char* file = "";
		char* uniform = "";

		DOMNamedNodeMap* samplerAttributes = samplerNodes->item(i)->getAttributes();
		for (unsigned int j=0; j<samplerAttributes->getLength(); j++)
		{
			if (getLower(XMLString::transcode(samplerAttributes->item(j)->getNodeName())) == "file")
				file = XMLString::transcode(samplerAttributes->item(j)->getNodeValue());

			if (getLower(XMLString::transcode(samplerAttributes->item(j)->getNodeName())) == "uniform")
				uniform = XMLString::transcode(samplerAttributes->item(j)->getNodeValue());
		}

		loadShaderSampler(node, file, uniform, texLayer);
		texLayer++;
	}

	DOMNodeList* uniformNodes = shaderElement->getElementsByTagName(XMLString::transcode("uniform"));
	for (unsigned int i=0; i<uniformNodes->getLength(); i++)
	{
		char* uniform;
		float value;

		DOMNamedNodeMap* uniformAttributes = uniformNodes->item(i)->getAttributes();
		for (unsigned int j=0; j<uniformAttributes->getLength(); j++)
		{
			if (getLower(XMLString::transcode(uniformAttributes->item(j)->getNodeName())) == "name")
				uniform = XMLString::transcode(uniformAttributes->item(j)->getNodeValue());

			if (getLower(XMLString::transcode(uniformAttributes->item(j)->getNodeName())) == "value")
				value = atof(XMLString::transcode(uniformAttributes->item(j)->getNodeValue()));
		}

		Uniform* suniform = new Uniform(uniform, value);
		node->getOrCreateStateSet()->addUniform(suniform);
	}

	DOMElement* tangentElement = static_cast<DOMElement*>(shaderElement->getElementsByTagName(XMLString::transcode("useTangentAndBinormal"))->item(0));
	if (tangentElement != 0)
	{
		char* tangent = "";
		char* binormal = "";

		DOMNamedNodeMap* tangentAttributes = tangentElement->getAttributes();
		for (unsigned int j=0; j<tangentAttributes->getLength(); j++)
		{
			if (getLower(XMLString::transcode(tangentAttributes->item(j)->getNodeName())) == "tangent")
			{
				tangent = XMLString::transcode(tangentAttributes->item(j)->getNodeValue());
				continue;
			}

			if (getLower(XMLString::transcode(tangentAttributes->item(j)->getNodeName())) == "binormal")
			{
				binormal = XMLString::transcode(tangentAttributes->item(j)->getNodeValue());
				continue;
			}
			
		}

		loadTangentAndBinormal(program, node, tangent, binormal);
	}

	node->getOrCreateStateSet()->setAttributeAndModes(program, StateAttribute::ON);
}

void ModelCache::parseMaterial(DOMNode* domnode, Node* node)
{
	Material* material = new Material();
	DOMElement* materialElement = static_cast<DOMElement*>(domnode);

	DOMNode* shininessNode = materialElement->getElementsByTagName(XMLString::transcode("shininess"))->item(0);
	if (shininessNode != 0)
		material->setShininess(Material::FRONT_AND_BACK, XMLGetScalar(shininessNode));

	DOMNode* ambientNode = materialElement->getElementsByTagName(XMLString::transcode("ambient"))->item(0);
	if (ambientNode != 0)
		material->setAmbient(Material::FRONT_AND_BACK, XMLGetColor(ambientNode));

	DOMNode* diffuseNode = materialElement->getElementsByTagName(XMLString::transcode("diffuse"))->item(0);
	if (diffuseNode != 0)
		material->setDiffuse(Material::FRONT_AND_BACK, XMLGetColor(diffuseNode));

	DOMNode* specularNode = materialElement->getElementsByTagName(XMLString::transcode("specular"))->item(0);
	if (specularNode != 0)
		material->setSpecular(Material::FRONT_AND_BACK, XMLGetColor(specularNode));

	DOMNode* emissionNode = materialElement->getElementsByTagName(XMLString::transcode("emission"))->item(0);
	if (emissionNode != 0)
		material->setEmission(Material::FRONT_AND_BACK, XMLGetColor(emissionNode));

	node->getOrCreateStateSet()->setAttribute(material, StateAttribute::ON);
}

void ModelCache::loadShaderSource(Program* program, Shader::Type type, char* source)
{
	Shader* shader = new Shader(type);
	shader->loadShaderSourceFromFile(source);
	program->addShader(shader);
}

void ModelCache::loadShaderSampler(Node* node, char* file, char* uniform, int texLayer)
{
	Texture2D* sampler = new Texture2D();
	sampler->setDataVariance(Object::DYNAMIC);
	// sampler->setWrap(Texture::WRAP_S, Texture::CLAMP_TO_EDGE);
	sampler->setFilter(Texture::MIN_FILTER, Texture::LINEAR);
	sampler->setFilter(Texture::MAG_FILTER, Texture::LINEAR_MIPMAP_LINEAR);
	// sampler->setMaxAnisotropy(8);
	Image* image = osgDB::readImageFile(file);
	if (image)
		sampler->setImage(image);

	Uniform* suniform = new Uniform(uniform, texLayer);

	StateSet* state = node->getOrCreateStateSet();
	state->setTextureAttributeAndModes(texLayer, sampler, StateAttribute::ON);
	state->addUniform(suniform);
}

void ModelCache::loadTangentAndBinormal(Program* program, Node* node, char* tangent, char* binormal)
{
	program->addBindAttribLocation(tangent, 6);
	program->addBindAttribLocation(binormal, 7);

	generateTangentAndBinormal(node);
}