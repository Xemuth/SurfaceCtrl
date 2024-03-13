#include "SurfaceCtrlLogic.h"

#include "Object3D.h"
#include "Camera.h"
#include "Shader.h"

#include <Core/Core.h>
#include <GLCtrl/GLCtrl.h>
#include <CtrlLib/CtrlLib.h>

namespace Upp{
	
	class SurfaceCtrlLogic::SurfaceCtrlLogicImpl{
		public:
			ArrayMap<String, OpenGLShader> shaders;
			ArrayMap<String, OpenGLProgram> programs;
		
		
			void InitShaders();
			void InitPrograms();
	};
			
	SurfaceCtrlLogic::SurfaceCtrlLogic(CameraPtr camera)
	{
		pImpl = std::make_shared<SurfaceCtrlLogic::SurfaceCtrlLogicImpl>();
	}
		
	SurfaceCtrlLogic::~SurfaceCtrlLogic();


	void SurfaceCtrlLogic::Draw() noexcept;

	Upp::Vector<Object3D>& SurfaceCtrlLogic::Objects() noexcept;
	
	Camera& SurfaceCtrlLogic::Camera() noexcept;
	
	
	virtual bool SurfaceCtrlLogic::Key(dword key,int count);
	virtual Image SurfaceCtrlLogic::HandleEvent(int event, Point p, int zdelta, dword)
	{
		
	}
	
	void SurfaceCtrlLogic::SurfaceCtrlLogicImpl::InitPrograms()
	{
		auto& shader1 =  programs.Create<OpenGLProgram>("draw_mesh_without_light");
		shader1.AttachShader(shaders.Get("vertex_simple")).AttachShader(shaders.Get("fragment_no_light"));
		shader1.Link();
		
		auto& shader2 =  programs.Create<OpenGLProgram>("draw_mesh_with_light");
		shader2.AttachShader(shaders.Get("vertex_simple")).AttachShader(shaders.Get("fragment_light"));
		shader2.Link();
		
		auto& shader3 =  programs.Create<OpenGLProgram>("draw_mesh_line");
		shader3.AttachShader(shaders.Get("vertex_simple")).AttachShader(shaders.Get("geometry_triangle")).AttachShader(shaders.Get("fragment_black"));
		shader3.Link();
		
		auto& shader4 =  programs.Create<OpenGLProgram>("draw_normal");
		shader4.AttachShader(shaders.Get("another_vertex")).AttachShader(shaders.Get("geometry_normal")).AttachShader(shaders.Get("fragment_black"));
		shader4.Link();
		
		for(const auto& program: ~programs)
		{
			if(!program.value.IsLinked())
			{
				ErrorOK("Error while linking program " + program.key+ ". See logs");
			}
		}
	}
	
	void SurfaceCtrlLogic::SurfaceCtrlLogicImpl::InitShaders()
	{
		shaders.Create<OpenGLShader>("vertex_simple", GL_VERTEX_SHADER,
			#include "shaders/VertexSimple.glsl"
		);
		shaders.Create<OpenGLShader>("another_vertex", GL_VERTEX_SHADER,
			#include "shaders/Vertex.glsl"
		);
		shaders.Create<OpenGLShader>("vertex_cubemap", GL_VERTEX_SHADER,
			#include "shaders/VertexCubeMap.glsl"
		);
		shaders.Create<OpenGLShader>("geometry_triangle", GL_GEOMETRY_SHADER,
			#include "shaders/GeometryTriangle.glsl"
		);
		shaders.Create<OpenGLShader>("geometry_normal", GL_GEOMETRY_SHADER,
			#include "shaders/GeometryNormal.glsl"
		);
		shaders.Create<OpenGLShader>("fragment_no_light", GL_FRAGMENT_SHADER,
			#include "shaders/FragmentNoLight.glsl"
		);
		shaders.Create<OpenGLShader>("fragment_light", GL_FRAGMENT_SHADER,
			#include "shaders/FragmentLight.glsl"
		);
		shaders.Create<OpenGLShader>("fragment_cubemap", GL_FRAGMENT_SHADER,
			#include "shaders/FragmentCubeMap.glsl"
		);
		shaders.Create<OpenGLShader>("fragment_black", GL_FRAGMENT_SHADER,
			#include "shaders/FragmentBlack.glsl"
		);
		
		for(const auto& shader: ~shaders)
		{
			if(!shader.value.IsCompiled())
			{
				ErrorOK("Error while compiling shader " + shader.key+ ". See logs");
			}
		}
	}
}