#pragma once
#include <glm/glm.hpp>
#include <glad/glad.h>
#include <string>

class Shader
{
public:
	Shader(const std::string& sVertexPath, const std::string& sFragmentPath,
		const std::string& sTcsPath = "", const std::string& sTesPath = "",
		const std::string& sGeometryPath = "");
	~Shader();
	void Use();
	void SetBool(const std::string& sName, bool bValue)const;
	void SetInt(const std::string& sName, int iValue)const;
	void SetFloat(const std::string& sName, float fValue)const;
	void SetVec2(const std::string& sName, const glm::vec2& vec2Value)const;
	void SetVec2(const std::string& sName, float x, float y)const;
	void SetVec3(const std::string& sName, const glm::vec3& vec3Value)const;
	void SetVec3(const std::string& sName, float x, float y, float z)const;
	void SetVec4(const std::string& sName, const glm::vec4& vec4Value)const;
	void SetVec4(const std::string& sName, float x, float y, float z, float w)const;
	void SetMat2(const std::string& sName, const glm::mat2& mat)const;
	void SetMat3(const std::string& sName, const glm::mat3& mat)const;
	void SetMat4(const std::string& sName, const glm::mat4& mat)const;
private:
	void ReadShaderCode(const std::string& sPath, std::string& sShaderCode);
	void CheckCompileErrors(GLuint uiShader, const std::string& sType);
private:
	int m_iProgramID;
};