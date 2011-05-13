#include "Misc.h"

using namespace Shooter;

void Shooter::checkKeysAndMouse(bool* keys, bool* mouse)
{
	for (int i=0; i<256; i++)
		if (keys[i])
			break;

	for (int i=0; i<8; i++)
		if (mouse[i])
			break;
}

Geode* Shooter::createSkyboxGeode(char* dir)
{
	char texture_string[128];

	Geode* skyboxgeode = new Geode();

	// faces, texcoords and colors
    DrawElementsUInt* faces = new DrawElementsUInt(PrimitiveSet::QUADS, 0);
    faces->push_back(0);
    faces->push_back(1);
    faces->push_back(3);
    faces->push_back(2);

	Vec2Array* texcoords = new Vec2Array();
	texcoords->push_back(Vec2(0.0f, 0.0f));
	texcoords->push_back(Vec2(1.0f, 0.0f));
	texcoords->push_back(Vec2(0.0f, 1.0f));
	texcoords->push_back(Vec2(1.0f, 1.0f));

	Vec4Array* colors = new Vec4Array;
	colors->push_back(Vec4(1.0f, 1.0f, 1.0f, 1.0f));

	Depth* depth = new Depth(Depth::LEQUAL, 1.0, 1.0);

	// textures
	Texture2D* texture_front = new Texture2D;
	texture_front->setDataVariance(Object::DYNAMIC);

	sprintf(&texture_string[0], "GameData/%s/posz.tga", dir);

	Image* image_front = readImageFile(&texture_string[0]);
	if (image_front) {
		texture_front->setImage(image_front);
		texture_front->setWrap(Texture::WRAP_S, Texture::CLAMP_TO_EDGE);
		texture_front->setWrap(Texture::WRAP_T, Texture::CLAMP_TO_EDGE);
	}

	Texture2D* texture_back = new Texture2D;
	texture_back->setDataVariance(Object::DYNAMIC); 

	sprintf(&texture_string[0], "GameData/%s/negz.tga", dir);

	Image* image_back = osgDB::readImageFile(&texture_string[0]);
	if (image_back) {
		texture_back->setImage(image_back);
		texture_back->setWrap(Texture::WRAP_S, Texture::CLAMP_TO_EDGE);
		texture_back->setWrap(Texture::WRAP_T, Texture::CLAMP_TO_EDGE);
	}

	Texture2D* texture_left = new Texture2D;
	texture_left->setDataVariance(Object::DYNAMIC); 

	sprintf(&texture_string[0], "GameData/%s/negx.tga", dir);

	Image* image_left = osgDB::readImageFile(&texture_string[0]);
	if (image_left) {
		texture_left->setImage(image_left);
		texture_left->setWrap(Texture::WRAP_S, Texture::CLAMP_TO_EDGE);
		texture_left->setWrap(Texture::WRAP_T, Texture::CLAMP_TO_EDGE);
	}

	Texture2D* texture_right = new Texture2D;
	texture_right->setDataVariance(Object::DYNAMIC); 

	sprintf(&texture_string[0], "GameData/%s/posx.tga", dir);

	Image* image_right = osgDB::readImageFile(&texture_string[0]);
	if (image_right) {
		texture_right->setImage(image_right);
		texture_right->setWrap(Texture::WRAP_S, Texture::CLAMP_TO_EDGE);
		texture_right->setWrap(Texture::WRAP_T, Texture::CLAMP_TO_EDGE);
	}

	Texture2D* texture_top = new Texture2D;
	texture_top->setDataVariance(Object::DYNAMIC); 

	sprintf(&texture_string[0], "GameData/%s/posy.tga", dir);

	Image* image_top = osgDB::readImageFile(&texture_string[0]);
	if (image_top) {
		texture_top->setImage(image_top);
		texture_top->setWrap(Texture::WRAP_S, Texture::CLAMP_TO_EDGE);
		texture_top->setWrap(Texture::WRAP_T, Texture::CLAMP_TO_EDGE);
	}

	Texture2D* texture_bottom = new Texture2D;
	texture_bottom->setDataVariance(Object::DYNAMIC); 

	sprintf(&texture_string[0], "GameData/%s/negy.tga", dir);

	Image* image_bottom = osgDB::readImageFile(&texture_string[0]);
	if (image_bottom) {
		texture_bottom->setImage(image_bottom);
		texture_bottom->setWrap(Texture::WRAP_S, Texture::CLAMP_TO_EDGE);
		texture_bottom->setWrap(Texture::WRAP_T, Texture::CLAMP_TO_EDGE);
	}

	// FRONT
	Geometry* skybox_front = new Geometry();

    Vec3Array* vertices_front = new Vec3Array;
	vertices_front->push_back(Vec3(-1.0f, 1.0f, -1.0f));
	vertices_front->push_back(Vec3(1.0f, 1.0f, -1.0f));
	vertices_front->push_back(Vec3(-1.0f, 1.0f, 1.0f));
	vertices_front->push_back(Vec3(1.0f, 1.0f, 1.0f));
    skybox_front->setVertexArray(vertices_front);
	skybox_front->addPrimitiveSet(faces);
	skybox_front->setTexCoordArray(0,texcoords);
	skybox_front->setColorArray(colors);
	skybox_front->setColorBinding(Geometry::BIND_OVERALL);
	skybox_front->getOrCreateStateSet()->
		setTextureAttributeAndModes(0, texture_front, StateAttribute::ON);

	skyboxgeode->addDrawable(skybox_front);

	// BACK
	Geometry* skybox_back = new Geometry();

    Vec3Array* vertices_back = new Vec3Array;
	vertices_back->push_back(Vec3(1.0f, -1.0f, -1.0f));
	vertices_back->push_back(Vec3(-1.0f, -1.0f, -1.0f));
	vertices_back->push_back(Vec3(1.0f, -1.0f, 1.0f));
	vertices_back->push_back(Vec3(-1.0f, -1.0f, 1.0f));
    skybox_back->setVertexArray(vertices_back);
	skybox_back->addPrimitiveSet(faces);
	skybox_back->setTexCoordArray(0, texcoords);
	skybox_back->setColorArray(colors);
	skybox_back->setColorBinding(Geometry::BIND_OVERALL);
	skybox_back->getOrCreateStateSet()->
		setTextureAttributeAndModes(0, texture_back, StateAttribute::ON);

	skyboxgeode->addDrawable(skybox_back);

	// LEFT
	Geometry* skybox_left = new Geometry();

    Vec3Array* vertices_left = new Vec3Array;
	vertices_left->push_back(Vec3(-1.0f, -1.0f, -1.0f));
	vertices_left->push_back(Vec3(-1.0f, 1.0f, -1.0f));
	vertices_left->push_back(Vec3(-1.0f, -1.0f, 1.0f));
	vertices_left->push_back(Vec3(-1.0f, 1.0f, 1.0f));
    skybox_left->setVertexArray(vertices_left);
	skybox_left->addPrimitiveSet(faces);
	skybox_left->setTexCoordArray(0, texcoords);
	skybox_left->setColorArray(colors);
	skybox_left->setColorBinding(Geometry::BIND_OVERALL);
	skybox_left->getOrCreateStateSet()->
		setTextureAttributeAndModes(0, texture_left, StateAttribute::ON);

	skyboxgeode->addDrawable(skybox_left);

	// RIGHT
	Geometry* skybox_right = new Geometry();

    Vec3Array* vertices_right = new Vec3Array;
	vertices_right->push_back(Vec3(1.0f, 1.0f, -1.0f));
	vertices_right->push_back(Vec3(1.0f, -1.0f, -1.0f));
	vertices_right->push_back(Vec3(1.0f, 1.0f, 1.0f));
	vertices_right->push_back(Vec3(1.0f, -1.0f, 1.0f));
    skybox_right->setVertexArray(vertices_right);
	skybox_right->addPrimitiveSet(faces);
	skybox_right->setTexCoordArray(0, texcoords);
	skybox_right->setColorArray(colors);
	skybox_right->setColorBinding(Geometry::BIND_OVERALL);
	skybox_right->getOrCreateStateSet()->
		setTextureAttributeAndModes(0, texture_right, StateAttribute::ON);

	skyboxgeode->addDrawable(skybox_right);

	// TOP
	Geometry* skybox_top = new Geometry();

    Vec3Array* vertices_top = new Vec3Array;
	vertices_top->push_back(Vec3(-1.0f, 1.0f, 1.0f));
	vertices_top->push_back(Vec3(1.0f, 1.0f, 1.0f));
	vertices_top->push_back(Vec3(-1.0f, -1.0f, 1.0f));
	vertices_top->push_back(Vec3(1.0f, -1.0f, 1.0f));
    skybox_top->setVertexArray(vertices_top);
	skybox_top->addPrimitiveSet(faces);
	skybox_top->setTexCoordArray(0, texcoords);
	skybox_top->setColorArray(colors);
	skybox_top->setColorBinding(Geometry::BIND_OVERALL);
	skybox_top->getOrCreateStateSet()->
		setTextureAttributeAndModes(0, texture_top, StateAttribute::ON);

	skyboxgeode->addDrawable(skybox_top);

	// BOTTOM
	Geometry* skybox_bottom = new Geometry();

    Vec3Array* vertices_bottom = new Vec3Array;
	vertices_bottom->push_back(Vec3(1.0f, 1.0f, -1.0f));
	vertices_bottom->push_back(Vec3(-1.0f, 1.0f, -1.0f));
	vertices_bottom->push_back(Vec3(1.0f, -1.0f, -1.0f));
	vertices_bottom->push_back(Vec3(-1.0f, -1.0f, -1.0f));
    skybox_bottom->setVertexArray(vertices_bottom);
	skybox_bottom->addPrimitiveSet(faces);
	skybox_bottom->setTexCoordArray(0, texcoords);
	skybox_bottom->setColorArray(colors);
	skybox_bottom->setColorBinding(Geometry::BIND_OVERALL);
	skybox_bottom->getOrCreateStateSet()->
		setTextureAttributeAndModes(0, texture_bottom, StateAttribute::ON);

	skyboxgeode->addDrawable(skybox_bottom);


	skyboxgeode->getOrCreateStateSet()->
		setMode(GL_LIGHTING, StateAttribute::OFF);
	skyboxgeode->getStateSet()->setAttributeAndModes(depth, StateAttribute::ON); 
	skyboxgeode->getStateSet()->setRenderBinDetails(-1000, "RenderBin");

	return skyboxgeode;
}

void Shooter::transformVector(Vec3* vec, Matrixd* mat)
{
	Vec3 cpy(*vec);

	(*vec)[0] = (*mat)(0,0)*cpy[0] + (*mat)(1,0)*cpy[1] + (*mat)(2,0)*cpy[2] + (*mat)(3,0);
	(*vec)[1] = (*mat)(0,1)*cpy[0] + (*mat)(1,1)*cpy[1] + (*mat)(2,1)*cpy[2] + (*mat)(3,1);
	(*vec)[2] = (*mat)(0,2)*cpy[0] + (*mat)(1,2)*cpy[1] + (*mat)(2,2)*cpy[2] + (*mat)(3,2);
}

Quat Shooter::getQuatFromEuler(double heading, double attitude, double bank)
{
	Quat q;

	double c1 = cos(heading/2.0);
	double s1 = sin(heading/2.0);
	double c2 = cos(attitude/2.0);
	double s2 = sin(attitude/2.0);
	double c3 = cos(bank/2.0);
	double s3 = sin(bank/2.0);

	double c1c2 = c1*c2;
	double s1s2 = s1*s2;

	q[0] = c1c2*s3 + s1s2*c3;
	q[1] = s1*c2*c3 + c1*s2*s3;
	q[2] = c1*s2*c3 - s1*c2*s3;
	q[3] = c1c2*c3 - s1s2*s3;

	return q;
}

string Shooter::getLower(const char* text)
{
	string result(text);
	transform(result.begin(), result.end(), result.begin(), tolower);

	return result;
}

float Shooter::XMLGetScalar(DOMNode* node)
{
	float value = 0;

	DOMNamedNodeMap* attributes = node->getAttributes();

	for (unsigned int i=0; i<attributes->getLength(); i++)
		if (getLower(XMLString::transcode(attributes->item(i)->getNodeName())) == "value")
		{
			value = atof(XMLString::transcode(attributes->item(i)->getNodeValue()));
			break;
		}

	return value;
}

Vec3 Shooter::XMLGetVec3(DOMNode* node)
{
	float x=0,y=0,z=0;

	DOMNamedNodeMap* attributes = node->getAttributes();

	for (unsigned int i=0; i<attributes->getLength(); i++)
	{
		if (getLower(XMLString::transcode(attributes->item(i)->getNodeName())) == "x")
			x = atof(XMLString::transcode(attributes->item(i)->getNodeValue()));
		if (getLower(XMLString::transcode(attributes->item(i)->getNodeName())) == "y")
			y = atof(XMLString::transcode(attributes->item(i)->getNodeValue()));
		if (getLower(XMLString::transcode(attributes->item(i)->getNodeName())) == "z")
			z = atof(XMLString::transcode(attributes->item(i)->getNodeValue()));
	}

	return Vec3(x, y, z);
}

Quat Shooter::XMLGetQuat(DOMNode* node)
{
	double x=0,y=0,z=0;

	DOMNamedNodeMap* attributes = node->getAttributes();

	for (unsigned int i=0; i<attributes->getLength(); i++)
	{
		if (getLower(XMLString::transcode(attributes->item(i)->getNodeName())) == "x")
			x = atof(XMLString::transcode(attributes->item(i)->getNodeValue()));
		if (getLower(XMLString::transcode(attributes->item(i)->getNodeName())) == "y")
			y = atof(XMLString::transcode(attributes->item(i)->getNodeValue()));
		if (getLower(XMLString::transcode(attributes->item(i)->getNodeName())) == "z")
			z = atof(XMLString::transcode(attributes->item(i)->getNodeValue()));
	}

	return getQuatFromEuler(x, y, z);
}

Vec4 Shooter::XMLGetColor(DOMNode* node)
{
	float r=0,g=0,b=0,a=0;

	DOMNamedNodeMap* attributes = node->getAttributes();

	for (unsigned int i=0; i<attributes->getLength(); i++)
	{
		if (getLower(XMLString::transcode(attributes->item(i)->getNodeName())) == "r")
			r = atof(XMLString::transcode(attributes->item(i)->getNodeValue()));
		if (getLower(XMLString::transcode(attributes->item(i)->getNodeName())) == "g")
			g = atof(XMLString::transcode(attributes->item(i)->getNodeValue()));
		if (getLower(XMLString::transcode(attributes->item(i)->getNodeName())) == "b")
			b = atof(XMLString::transcode(attributes->item(i)->getNodeValue()));
		if (getLower(XMLString::transcode(attributes->item(i)->getNodeName())) == "a")
			a = atof(XMLString::transcode(attributes->item(i)->getNodeValue()));
	}

	return Vec4(r, g, b, a);
}

void Shooter::generateTangentAndBinormal(Node* node)
{
	Group* group = node->asGroup();
	Geode* geode = node->asGeode();

	if (group)
	{
		for (unsigned int i=0; i<group->getNumChildren(); i++)
			generateTangentAndBinormal(group->getChild(i));
	} else if (geode)
	{
		for (unsigned int i=0; i<geode->getNumDrawables(); i++)
		{
			Geometry *geometry = geode->getDrawable(i)->asGeometry();
			if(geometry)
			{
				ref_ptr<osgUtil::TangentSpaceGenerator> tsg = new osgUtil::TangentSpaceGenerator();
				tsg->generate(geometry);

				geometry->setVertexAttribData(6, Geometry::ArrayData(tsg->getTangentArray(), Geometry::BIND_PER_VERTEX));
				geometry->setVertexAttribData(7, Geometry::ArrayData(tsg->getBinormalArray(), Geometry::BIND_PER_VERTEX, GL_FALSE));

				tsg.release();
			}
		}
	}
}