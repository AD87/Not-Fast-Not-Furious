#include <iostream>
#include <assert.h>
#include <fstream>
#include "Shader.h"
#include "MyGL.h"

void ReportError(const char* buf)
{
	std::cout << buf << "\n";
}

Shader::Shader()
{
	m_program = 0;
}

void Shader::Set(const std::string& name, float f)
{
	int loc = glGetUniformLocation(m_program, name.c_str());
	assert(loc != -1);
	glUniform1f(loc, f);
}

static bool LoadFile(const std::string& filename, std::string* result)
{
	std::ifstream file;
	file.open(filename);
	if (!file.is_open())
	{
		return false;
	}
	std::string str;
	while (std::getline(file, str))
	{
		*result += str + "\r\n";
	}
	return true;
}

bool Shader::Load(const std::string& vertexFile, const std::string& fragmentFile)
{
	std::string vert;
	if (!LoadFile(vertexFile, &vert))
	{
		return false;
	}

	std::string frag;
	if (!LoadFile(fragmentFile, &frag))
	{
		return false;
	}

	return Create(vert, frag);
}

bool Shader::Create(const std::string& vertexSource, const std::string& fragmentSource)
{
	GLuint vertSh = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragSh = glCreateShader(GL_FRAGMENT_SHADER);

	const GLint vlength = vertexSource.size();
	const GLint flength = fragmentSource.size();
	const char* vStr = vertexSource.c_str();
	const char* fStr = fragmentSource.c_str();
	glShaderSource(vertSh, 1, &vStr, &vlength);
	glShaderSource(fragSh, 1, &fStr, &flength);

	GLint compiled = 0;
	static const int ERROR_BUF_SIZE = 2000;
	GLcharARB buf[ERROR_BUF_SIZE]; // error string buffer

	glCompileShader(vertSh);

	glGetShaderiv(vertSh, GL_COMPILE_STATUS, &compiled);
	if (!compiled)
	{
		glGetShaderInfoLog(vertSh, ERROR_BUF_SIZE, 0, buf);
		ReportError(buf);
		return false;
	}

	glCompileShader(fragSh);

	glGetShaderiv(fragSh, GL_COMPILE_STATUS, &compiled);
	if (!compiled)
	{
		glGetShaderInfoLog(fragSh, ERROR_BUF_SIZE, 0, buf);
		ReportError(buf);
		return false;
	}

	m_program = glCreateProgram();
	glAttachShader(m_program, vertSh);
	glAttachShader(m_program, fragSh);
	glLinkProgram(m_program);
	GLint linked;
	glGetProgramiv(m_program, GL_OBJECT_LINK_STATUS_ARB, &linked);
	if (!linked)
	{
		glGetProgramInfoLog(m_program, ERROR_BUF_SIZE, 0, buf);
		ReportError(buf);
		return false;
	}

	return true;
}

void Shader::UseThisShader()
{
	glUseProgram(m_program);
}

void Shader::StopUsingThisShader()
{
	glUseProgram(0);
}