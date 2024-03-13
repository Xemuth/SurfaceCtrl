#include "Shader.h"

#include <Core/Core.h>
#include <GLCtrl/GLCtrl.h>

#define GLM_ENABLE_EXPERIMENTAL
#include <plugin/glm/glm.hpp>
#include <plugin/glm/gtc/matrix_transform.hpp>
#include <plugin/glm/gtc/type_ptr.hpp>
#include <plugin/glm/gtx/quaternion.hpp>
#include <plugin/glm/ext/quaternion_trigonometric.hpp>
#include <plugin/glm/gtc/constants.hpp>
#include <plugin/glm/gtx/norm.hpp>
#include <plugin/glm/gtx/compatibility.hpp>
#include <plugin/glm/gtx/string_cast.hpp>
#include <plugin/glm/gtx/vector_angle.hpp>

namespace Upp
{

	class OpenGLShader::OpenGLShaderImpl
	{
		public:
			GLenum shaderType = GL_INVALID_INDEX;
			GLuint id = GL_INVALID_INDEX;
			
			bool   compiled = false;
			bool CheckForCompilationError()noexcept;
			const char* GetShaderTypeStr()noexcept;
	};
	
	OpenGLShader::OpenGLShader(GLenum type, const char * data)
	{
		pImpl = std::make_shared<OpenGLShader::OpenGLShaderImpl>();
		pImpl->shaderType = type;
		pImpl->id = glCreateShader(pImpl->shaderType);
		if(pImpl->id == 0)
		{
			pImpl->id = GL_INVALID_INDEX;
			LOG("ERROR::SHADER::"+ String(pImpl->GetShaderTypeStr()) +"::CREATION_FAILED");
			return;
		}
		// Shader compilation
		glShaderSource(pImpl->id, 1, &data, nullptr);
		glCompileShader(pImpl->id);
		pImpl->compiled = pImpl->CheckForCompilationError();
	}
	
	OpenGLShader::~OpenGLShader()
	{
		glDeleteShader(pImpl->id);
		pImpl->compiled = false;
		pImpl->shaderType = GL_INVALID_INDEX;
		pImpl->id = GL_INVALID_INDEX;
	}
	
	GLuint OpenGLShader::GetId()const noexcept
	{
		return pImpl->id;
	}
	
	GLenum OpenGLShader::GetType()const noexcept
	{
		return pImpl->shaderType;
	}
	
	bool OpenGLShader::IsCompiled()const noexcept
	{
		return pImpl->compiled;
	}
	
	bool OpenGLShader::OpenGLShaderImpl::CheckForCompilationError()noexcept
	{
		int success;
	    glGetShaderiv(id, GL_COMPILE_STATUS, &success);
	    if (!success)
	    {
	        char infoLog[1024];
			glGetShaderInfoLog(id, 1024, NULL, infoLog);
			LOG("ERROR::SHADER::" + String(pImpl->GetShaderTypeStr()) + "::" + AsString(id) + "::COMPILATION_FAILED\n" + String(infoLog));
	    }
	    return success;
	}
	
	const char* OpenGLShader::OpenGLShaderImpl::GetShaderTypeStr()noexcept
	{
        switch(shaderType){
			case GL_VERTEX_SHADER:
				return "VERTEX";
			case GL_FRAGMENT_SHADER:
				return "FRAGMENT";
			case GL_TESS_CONTROL_SHADER:
				return "TESSELATION_CONTROL";
			case GL_TESS_EVALUATION_SHADER:
				return "TESSELATION_EVALUATION";
			case GL_GEOMETRY_SHADER:
				return "GEOMETRY";
			default:
				return "UNKNOW";
        };
	}
	
	class OpenGLProgram::OpenGLProgramImpl
	{
		public:
			GLuint id = GL_INVALID_INDEX;
			
			GLuint vertex   = GL_INVALID_INDEX;
			GLuint tcs      = GL_INVALID_INDEX;
			GLuint tes      = GL_INVALID_INDEX;
			GLuint geometry = GL_INVALID_INDEX;
			GLuint fragment = GL_INVALID_INDEX;
			
			bool linked = false;
			
			ArrayMap<String, GLint> uniforms_locations;
			GLint GetUniformLocation(const Upp::String& name);
			bool  CheckForLinkingError();
	};
	
	OpenGLProgram::~OpenGLProgram()
	{
		if(pImpl->id != GL_INVALID_INDEX)
			glDeleteProgram(pImpl->id);
	}
	
	OpenGLProgram& OpenGLProgram::Bind()noexcept
	{
		if(pImpl->linked)
			glUseProgram(pImpl->id);
		return *this;
	}
	
	OpenGLProgram& OpenGLProgram::UnBind()noexcept
	{
		glUseProgram(0);
	}
	
	bool OpenGLProgram::HasShader(GLenum type) const noexcept
	{
		return GetShaderId(type) != -1;
	}
		
	GLuint OpenGLProgram::GetShaderId(GLenum type) const noexcept
	{
		switch(type)
		{
			case GL_VERTEX_SHADER:
				return pImpl->vertex;
			case GL_TESS_CONTROL_SHADER:
				return pImpl->tcs;
			case GL_TESS_EVALUATION_SHADER:
				return pImpl->tes;
			case GL_GEOMETRY_SHADER:
				return pImpl->geometry;
			case GL_FRAGMENT_SHADER:
				return pImpl->fragment;
			default:
				return GL_INVALID_INDEX;
		};
	}
	
	OpenGLProgram& OpenGLProgram::AttachShader(const OpenGLShader& shader)noexcept
	{
		if(!shader.IsCompiled())
		{
			LOG("Error: shader "+ shader.GetId() +" is not compiled");
			return *this;
		}
			
		switch(shader.GetType())
		{
			case GL_VERTEX_SHADER:
				pImpl->vertex = shader.GetId();
			case GL_TESS_CONTROL_SHADER:
				pImpl->tcs = shader.GetId();
			case GL_TESS_EVALUATION_SHADER:
				pImpl->tes = shader.GetId();
			case GL_GEOMETRY_SHADER:
				pImpl->geometry = shader.GetId();
			case GL_FRAGMENT_SHADER:
				pImpl->fragment = shader.GetId();
			default:
				LOG("Error: shader "+ shader.GetId() +" has unknown shader type");;
		};
		return *this;
	}
	
	bool OpenGLProgram::Link()noexcept
	{
		pImpl->id = glCreateProgram();
		if(pImpl->id == 0)
		{
			pImpl->id = GL_INVALID_INDEX;
			LOG("ERROR::PROGRAM::CREATION_FAILED");
			return false;
		}
	
		if(pImpl->vertex != GL_INVALID_INDEX) glAttachShader(pImpl->id, pImpl->vertex);
		if(pImpl->tcs != GL_INVALID_INDEX) glAttachShader(pImpl->id, pImpl->tcs);
		if(pImpl->tes != GL_INVALID_INDEX) glAttachShader(pImpl->id, pImpl->tes);
		if(pImpl->geometry != GL_INVALID_INDEX) glAttachShader(pImpl->id, pImpl->geometry);
		if(pImpl->fragment != GL_INVALID_INDEX) glAttachShader(pImpl->id, pImpl->fragment);
		
		glLinkProgram(pImpl->id);
		pImpl->linked = pImpl->CheckForLinkingError();
		return pImpl->linked;
	}
	
	bool OpenGLProgram::IsLinked()const noexcept
	{
		return pImpl->linked;
	}
	
	OpenGLProgram& OpenGLProgram::SetUniform<bool>(const String& name, bool value)
	{
		if(pImpl->linked)
			glUniform1i(pImpl->GetUniformLocation(name), (int)value);
		return *this;
	}

	OpenGLProgram& OpenGLProgram::SetUniform<int>(const String& name, int value)
	{
		if(pImpl->linked)
			glUniform1i(pImpl->GetUniformLocation(name), value);
		return *this;
	}

	OpenGLProgram& OpenGLProgram::SetUniform<float>(const String& name, float value)
	{
		if(pImpl->linked)
			glUniform1f(pImpl->GetUniformLocation(name), value);
		return *this;
	}

	OpenGLProgram& OpenGLProgram::SetUniform<glm::vec2>(const String& name, const glm::vec2 &value)
	{
		if(pImpl->linked)
			glUniform2fv(pImpl->GetUniformLocation(name), 1, &value[0]);
		return *this;
	}

	OpenGLProgram& OpenGLProgram::SetUniform<glm::vec3>(const String& name, const glm::vec3 &value)
	{
		if(pImpl->linked)
			glUniform3fv(pImpl->GetUniformLocation(name), 1, &value[0]);
		return *this;
	}

	OpenGLProgram& OpenGLProgram::SetUniform<glm::vec4>(const String& name, const glm::vec4 &value)
	{
		if(pImpl->linked)
			glUniform4fv(pImpl->GetUniformLocation(name), 1, &value[0]);
		return *this;
	}
	
	OpenGLProgram& OpenGLProgram::SetUniform<glm::mat2>(const String& name, const glm::mat2 &mat)
	{
		if(pImpl->linked)
			glUniformMatrix2fv(pImpl->GetUniformLocation(name), 1, GL_FALSE, &mat[0][0]);
		return *this;
	}

	OpenGLProgram& OpenGLProgram::SetUniform<glm::mat3>(const String& name, const glm::mat3 &mat)
	{
		if(pImpl->linked)
			glUniformMatrix3fv(pImpl->GetUniformLocation(name), 1, GL_FALSE, &mat[0][0]);
		return *this;
	}

	OpenGLProgram& OpenGLProgram::SetUniform<glm::mat4>(const String& name, const glm::mat4 &mat)
	{
		if(pImpl->linked)
			glUniformMatrix4fv(pImpl->GetUniformLocation(name), 1, GL_FALSE, &mat[0][0]);
		return *this;
	}
	
	GLint OpenGLProgram::OpenGLProgramImpl::GetUniformLocation(const Upp::String& name)
	{
		if((auto index = uniforms_locations.Find(name)) != -1)
		{
			return uniforms_locations.Get(index);
		}
		
		if((auto location = glGetUniformLocation(id, name.ToStd().c_str())) == -1)
		{
			RLOG("Error: uniform named " + name +" can't be find in program number " + AsString(id));
			return location;
		}
		uniforms_locations.Add(name, location);
		return location;
	}
	
	bool OpenGLProgram::OpenGLProgramImpl::CheckForLinkingError()
	{
		int success;
	    glGetProgramiv(id, GL_LINK_STATUS, &success);
	    if (!success)
	    {
	        char infoLog[1024];
			glGetProgramInfoLog(id, 1024, NULL, infoLog);
			LOG("ERROR::PROGRAM::LINKING_FAILED\n" + String(infoLog));
	    }
	    return success;
	}
}
