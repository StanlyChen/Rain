#include "SimpleRenderable.h"

namespace Rain
{
	SimpleRenderable::SimpleRenderable(std::vector<RainPoint3D>&& vertices, std::vector<unsigned>&& indices, RainPrimType primType)
	{

	}

	void SimpleRenderable::render(RainOpenGLFuncs* pContext)
	{

	}

	void SimpleRenderable::create(RainOpenGLFuncs* pContext)
	{

	}

	void SimpleRenderable::destory(RainOpenGLFuncs* pContext)
	{

	}

	void SimpleRenderableShelve::pushData(SimpleRenderable* pRenderable, std::unique_ptr<TessellationData> pTessData)
	{
		//TODO add lock 
		if (m_cacheDatas.find(pRenderable) == m_cacheDatas.end())
		{
			throw std::exception("Program Error");
		}

		m_cacheDatas.insert( std::make_pair(pRenderable,std::move( pTessData) ));
	}

	std::unique_ptr<TessellationData> SimpleRenderableShelve::popData(SimpleRenderable* pRenderable)
	{
		//TODO add lock 
		 auto it = m_cacheDatas.find(pRenderable);

		if ( it != m_cacheDatas.end())
		{
			std::unique_ptr<TessellationData> ret = std::move(it->second);
			m_cacheDatas.erase(it);
			return ret;
		}

		return nullptr;
	}
}