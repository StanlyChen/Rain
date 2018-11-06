#pragma once
#include "RainOpenGL.h"
namespace Rain
{

	enum RainPrimType
	{
		Point,
		Line,
		Triangle,
		Quad,
	};

	//TODO introduce glm
	struct RainPoint3D
	{
		float x;
		float y;
		float z;
	};


	class IRenderable
	{
	public:
		virtual ~IRenderable() {};
		virtual void render(RainOpenGLFuncs* pContext) = 0 {};
		virtual void create(RainOpenGLFuncs* pContext) = 0 {};
		virtual void destory(RainOpenGLFuncs* pContext) = 0 {};
	};
}