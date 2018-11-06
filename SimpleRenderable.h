#pragma once
#include <IRenderable.h>
#include <vector>
#include <memory>

#include "RainOpenGL.h"
#include "Singleton.h"


namespace Rain
{
	struct TessellationData
	{
		std::vector<RainPoint3D> m_vertices;
		std::vector<unsigned> m_indices;
	};

	class SimpleRenderable : IRenderable
	{
		SimpleRenderable( std::vector<RainPoint3D>&& vertices, std::vector<unsigned>&& indices, RainPrimType primType);

		void render( RainOpenGLFuncs* pContext ) override;
		void create(RainOpenGLFuncs* pContext)  override;
		void destory(RainOpenGLFuncs* pContext) override;


	private:
		GLuint m_verticesVBO = 0;
		GLuint m_indicesVBO = 0;
		GLenum m_primType = 0;
	};

	class SimpleRenderableShelve
	{
	public:
		static util::Singletion<SimpleRenderableShelve> getSingleton;

	private:
		std::map<SimpleRenderable*, std::unique_ptr<TessellationData> > m_cacheDatas;
		
		void pushData(SimpleRenderable*, std::unique_ptr<TessellationData> );
		std::unique_ptr<TessellationData> popData(SimpleRenderable*);

	};
}