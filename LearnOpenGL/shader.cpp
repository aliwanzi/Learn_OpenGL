#include "shader.h"
#include <iostream>
#include <fstream>
#include <sstream>

Shader::Shader(const std::string& sVertexPath, 
	const std::string& sFragmentPath,
	const std::string& sTcsPath /*= ""*/, 
	const std::string& sTesPath/* = ""*/,
	const std::string& sGeometryPath/*=""*/)
{
	std::string sVertexCode(""), sFragmentCode(""), sTcsCode(""), sTesCode(""), sGeometryCode("");;

	try
	{
		ReadShaderCode(sVertexPath, sVertexCode);
		ReadShaderCode(sFragmentPath, sFragmentCode);
		if (!sTcsPath.empty())
		{
			ReadShaderCode(sTcsPath, sTcsCode);
		}
		if (!sTesPath.empty())
		{
			ReadShaderCode(sTesPath, sTesCode);
		}
		if (!sGeometryPath.empty())
		{
			ReadShaderCode(sGeometryPath, sGeometryCode);
		}
	}
	catch (std::ifstream::failure& e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ:" << e.what() << std::endl;
	}

	const char* pcVertexCode = sVertexCode.c_str();
	unsigned int uiVertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(uiVertex, 1, &pcVertexCode, NULL);
	glCompileShader(uiVertex);
	CheckCompileErrors(uiVertex, "VERTEX");

	const char* pcFragmentCode = sFragmentCode.c_str();
	unsigned int uiFragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(uiFragment, 1, &pcFragmentCode, NULL);
	glCompileShader(uiFragment);
	CheckCompileErrors(uiFragment, "FRAGMENT");

	unsigned int uiTcs(0);
	if (!sTcsPath.empty())
	{
		const char* pcTcsCode = sTcsCode.c_str();
		uiTcs = glCreateShader(GL_TESS_CONTROL_SHADER);
		glShaderSource(uiTcs, 1, &pcTcsCode, NULL);
		glCompileShader(uiTcs);
		CheckCompileErrors(uiTcs, "GEOMETRY");
	}

	unsigned int uiTes(0);
	if (!sTesPath.empty())
	{
		const char* pcTesCode = sTesCode.c_str();
		uiTes = glCreateShader(GL_TESS_EVALUATION_SHADER);
		glShaderSource(uiTes, 1, &pcTesCode, NULL);
		glCompileShader(uiTes);
		CheckCompileErrors(uiTes, "GEOMETRY");
	}

	unsigned int uiGeometry(0);
	if (!sGeometryPath.empty())
	{
		const char* pcGeometryCode = sGeometryCode.c_str();
		uiGeometry = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(uiGeometry, 1, &pcGeometryCode, NULL);
		glCompileShader(uiGeometry);
		CheckCompileErrors(uiGeometry, "GEOMETRY");
	}

	m_iProgramID = glCreateProgram();
	glAttachShader(m_iProgramID, uiVertex);
	glAttachShader(m_iProgramID, uiFragment);
	if (!sTcsPath.empty())
	{
		glAttachShader(m_iProgramID, uiTcs);
	}
	if (!sTesPath.empty())
	{
		glAttachShader(m_iProgramID, uiTes);
	}
	if (!sGeometryPath.empty())
	{
		glAttachShader(m_iProgramID, uiGeometry);
	}
	glLinkProgram(m_iProgramID);
	CheckCompileErrors(m_iProgramID, "PROGRAM");

	glDeleteShader(uiVertex);
	glDeleteShader(uiFragment);
	if (!sTesPath.empty())
	{
		glDeleteShader(uiTcs);
	}
	if (!sTesPath.empty())
	{
		glDeleteShader(uiTes);
	}
	if (!sGeometryPath.empty())
	{
		glDeleteShader(uiGeometry);
	}
}

Shader::~Shader()
{

}

void Shader::Use()
{
	glUseProgram(m_iProgramID);
}

void Shader::SetBool(const std::string& sName, bool bValue)const
{
	glUniform1i(glGetUniformLocation(m_iProgramID, sName.c_str()), static_cast<int>(bValue));
}

void Shader::SetInt(const std::string& sName, int iValue)const
{
	glUniform1i(glGetUniformLocation(m_iProgramID, sName.c_str()), iValue);
}

void Shader::SetFloat(const std::string& sName, float fValue)const
{
	glUniform1f(glGetUniformLocation(m_iProgramID, sName.c_str()), fValue);
}

void Shader::SetVec2(const std::string& sName, const glm::vec2& vec2Value)const
{
	glUniform2fv(glGetUniformLocation(m_iProgramID, sName.c_str()), 1, &vec2Value[0]);
}

void Shader::SetVec2(const std::string& sName, float x, float y)const
{
	glUniform2f(glGetUniformLocation(m_iProgramID, sName.c_str()), x, y);
}

void Shader::SetVec3(const std::string& sName, const glm::vec3& vec3Value)const
{
	glUniform3fv(glGetUniformLocation(m_iProgramID, sName.c_str()), 1, &vec3Value[0]);
}

void Shader::SetVec3(const std::string& sName, float x, float y, float z)const
{
	glUniform3f(glGetUniformLocation(m_iProgramID, sName.c_str()), x, y, z);
}

void Shader::SetVec4(const std::string& sName, const glm::vec4& vec4Value)const
{
	glUniform4fv(glGetUniformLocation(m_iProgramID, sName.c_str()), 1, &vec4Value[0]);
}

void Shader::SetVec4(const std::string& sName, float x, float y, float z, float w)const
{
	glUniform4f(glGetUniformLocation(m_iProgramID, sName.c_str()), x, y, z, w);
}

void Shader::SetMat2(const std::string& sName, const glm::mat2& mat)const
{
	glUniformMatrix2fv(glGetUniformLocation(m_iProgramID, sName.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::SetMat3(const std::string& sName, const glm::mat3& mat)const
{
	glUniformMatrix3fv(glGetUniformLocation(m_iProgramID, sName.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::SetMat4(const std::string& sName, const glm::mat4& mat)const
{
	glUniformMatrix4fv(glGetUniformLocation(m_iProgramID, sName.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::ReadShaderCode(const std::string& sPath, std::string& sShaderCode)
{
	std::ifstream iFileStream;
	iFileStream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	iFileStream.open(sPath);

	std::stringstream sSteam;
	sSteam << iFileStream.rdbuf();
	iFileStream.close();

	sShaderCode = sSteam.str();
}

void Shader::CheckCompileErrors(GLuint uiShader, const std::string& sType)
{
	GLint iSuccess;
	GLchar cInfoLog[1024];
	if (sType != "PROGRAM")
	{
		glGetShaderiv(uiShader, GL_COMPILE_STATUS, &iSuccess);
		if (!iSuccess)
		{
			glGetShaderInfoLog(uiShader, 1024, NULL, cInfoLog);
			std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << sType << "\n" << cInfoLog << "\n";
		}
	}
	else
	{
		glGetProgramiv(uiShader, GL_LINK_STATUS, &iSuccess);
		if (!iSuccess)
		{
			glGetProgramInfoLog(uiShader, 1024, NULL, cInfoLog);
			std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << sType << "\n" << cInfoLog << "\n";
		}
	}
}