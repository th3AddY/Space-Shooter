#pragma once

#include <vector>

#include <osg/Node>

#include "CacheContainer.h"
#include "Misc.h"

using namespace osg;
using namespace std;

namespace Shooter
{
	template <class T_DERIVED>
	class Cache
	{
	public:
		Node* fromFile(char* filename)
		{
			CacheContainer* container = findContainer(filename);

			if (container == 0)
			{
				container = load(filename);

				container->filename = filename;
				m_cachedData.push_back(container);
			}

			return getNode(container);
		}

		void clear()
		{
			for (unsigned int i=0; i<m_cachedData.size(); i++)
			{
				m_cachedData[i]->release();
				delete m_cachedData[i];
			}
			m_cachedData.clear();
		}

		static T_DERIVED& get()
		{
			static T_DERIVED instance;
			return instance;
		}
 
	protected:
		Cache() {}

		virtual CacheContainer* load(char* filename)
		{
			return new CacheContainer();
		}

		virtual Node* getNode(CacheContainer* container)
		{
			return container->node.get();
		}
 
	private:
		Cache(const Cache&);
		Cache& operator=(const Cache&) { return *this; }

		CacheContainer* findContainer(char* filename)
		{
			for (unsigned int i=0; i<m_cachedData.size(); i++)
				if (getLower(filename) == getLower(m_cachedData[i]->filename))
					return m_cachedData[i];

			return 0;
		}

		vector<CacheContainer*> m_cachedData;
	};
}