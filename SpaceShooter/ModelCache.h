#pragma once

#include <iostream>

#include <xercesc/dom/DOM.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/sax/HandlerBase.hpp>

#include <osg/PositionAttitudeTransform>
#include <osg/Material>

#include "Cache.h"
#include "MeshCache.h"

using namespace osg;

namespace Shooter
{
	class ModelCache : public Cache<ModelCache>
	{
	protected:
		CacheContainer* load(char* filename);

	private:
		Node* parseXML(DOMDocument* doc);
		void parseShader(DOMNode* domnode, Node* node);
		void parseMaterial(DOMNode* domnode, Node* node);
		
		void loadShaderSource(Program* program, Shader::Type type, char* source);
		void loadShaderSampler(Node* node, char* file, char* uniform, int texLayer);
		void loadTangentAndBinormal(Program* program, Node* node, char* tangent, char* binormal);
	};
}