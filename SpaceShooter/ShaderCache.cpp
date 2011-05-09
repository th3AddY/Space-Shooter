#include "ShaderCache.h"

using namespace Shooter;

Program* ShaderCache::loadProgram(const char* shaderSource)
{
	return static_cast<Program*>(fromFile(shaderSource));
}

CacheContainer* ShaderCache::load(const char* filename)
{
	CacheContainer* container = new	CacheContainer();
	Program* program = new Program();

	vector<string> sourceList;
	split(filename, sourceList, ',');
	for (unsigned int i=0; i<sourceList.size(); i++)
	{
		if (sourceList[i] != "/")
		{
			Shader* shader;

			switch (i)
			{
			case 0:
				{
					shader = new Shader(Shader::FRAGMENT);
					break;
				}
			case 1:
				{
					shader = new Shader(Shader::VERTEX);
					break;
				}
			case 2:
				{
					shader = new Shader(Shader::GEOMETRY);
					break;
				}
			case 3:
				{
					shader = new Shader(Shader::TESSCONTROL);
					break;
				}
			case 4:
				{
					shader = new Shader(Shader::TESSEVALUATION);
					break;
				}
			default:
				{
					shader = new Shader(Shader::UNDEFINED);
					break;
				}
			}

			shader->loadShaderSourceFromFile(sourceList[i]);
			program->addShader(shader);
		}
	}

	container->referenced = program;
	return container;
}