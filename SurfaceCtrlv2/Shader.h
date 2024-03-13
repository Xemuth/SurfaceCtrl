#ifndef _SurfaceCtrl_SurfaceCtrlv2_Shader_h_
#define _SurfaceCtrl_SurfaceCtrlv2_Shader_h_
#include <memory>

#define STRINGIFY(...) #__VA_ARGS__
#define SHADER(version, shader) "#version " #version "\n" STRINGIFY(shader)

typedef unsigned int GLenum;
typedef unsigned int GLuint;

namespace Upp
{
	
class String;
	
class OpenGLShader
{
	public:
		OpenGLShader() = delete;
		OpenGLShader(GLenum type, const char * data);
		~OpenGLShader();
		
		OpenGLShader(const OpenGLShader&) = delete;
		OpenGLShader(OpenGLShader&&) = delete;
		OpenGLShader& operator=(const OpenGLShader&) = delete;
		OpenGLShader& operator=(OpenGLShader&&) = delete;
		
		GLuint GetId()const noexcept;
		GLenum GetType()const noexcept;
		bool IsCompiled()const noexcept;
		
	private:
		class OpenGLShaderImpl;
		std::shared_ptr<OpenGLShaderImpl> pImpl;
};

class OpenGLProgram
{
	public:
		OpenGLProgram() = default;
		~OpenGLProgram();
	
		OpenGLProgram(const OpenGLProgram&) = delete;
		OpenGLProgram(OpenGLProgram&&) = delete;
		OpenGLProgram& operator=(const OpenGLProgram&) = delete;
		OpenGLProgram& operator=(OpenGLProgram&&) = delete;
	
	
		OpenGLProgram& Bind()noexcept;
		OpenGLProgram& UnBind()noexcept;
		bool HasShader(GLenum type) const noexcept;
		GLuint GetShaderId(GLenum type) const noexcept;
		
		OpenGLProgram& AttachShader(const OpenGLShader& shader)noexcept;
		bool Link()noexcept;
		bool IsLinked()const noexcept;
		
		extern template OpenGLProgram& SetUniform<bool>(const String& name, bool value);
		extern template OpenGLProgram& SetUniform<int>(const String& name, int value);
		extern template OpenGLProgram& SetUniform<float>(const String& name, float value);
		extern template OpenGLProgram& SetUniform<glm::vec2>(const String& name, const glm::vec2 &value);
		extern template OpenGLProgram& SetUniform<glm::vec3>(const String& name, const glm::vec3 &value);
		extern template OpenGLProgram& SetUniform<glm::vec4>(const String& name, const glm::vec4 &value);
		extern template OpenGLProgram& SetUniform<glm::mat2>(const String& name, const glm::mat2 &mat);
		extern template OpenGLProgram& SetUniform<glm::mat3>(const String& name, const glm::mat3 &mat);
		extern template OpenGLProgram& SetUniform<glm::mat4>(const String& name, const glm::mat4 &mat);
		
		
	private:
		class OpenGLProgramImpl;
		std::shared_ptr<OpenGLProgramImpl> pImpl;
};

}

#endif
