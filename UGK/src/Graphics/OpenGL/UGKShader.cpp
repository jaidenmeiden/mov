/**	Definition of the class CShader

*	Prefix: CSHD_

*	@author Joaquim Montell
*	@version 2012-09
*/

#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include "UGKShader.h"

const GLuint GLTypes[] = { GL_VERTEX_SHADER, GL_FRAGMENT_SHADER };

/**
* \fn void CShader::~CShader()
* Class constructor. Builds an unitialized shader
*/
CShader::CShader()
{
	ShaderId = CSHDR_NO_SHADER;
};

/**
* \fn void CShader::~CShader()
* Class destructor
*/
CShader::~CShader()
{
	if (CSHDR_NO_SHADER != ShaderId)
		glDeleteShader(ShaderId);
};

/**
* \fn void CShader::CompileFromSource(UGKS_String source, CSHDR_TYPE type)
* Loads the shader source code and compiles it. If necessary, free memory.
* \param source path to file containing the source of the shader
* \param type type of the shader. Only supported Vertex and Fragment
* Return the compiled shader identifier, or CSHD_NO_SHADER in the attribute ShaderId
*/
std::shared_ptr<CShader> CShader::CompileFromSource(std::string source, CSHDR_TYPE type)
{
	std::ifstream file;
	std::string st;
	std::vector<std::string> src;

	file.open(source);
	if (!file) {
		std::cerr << "Could not open source file " << source << std::endl;
		return nullptr;
	}
	else
		std::cerr << std::endl << "Compiling " << source << "..." << std::endl;

	while (!file.eof()) {
		getline(file, st);
		st.push_back('\n');
		src.push_back(st);
	}
	file.close();

	return CompileFromMemory(src, type);
}

/**
* \fn void CShader::CompileFromSource(UGKS_String source, CSHDR_TYPE type)
* Loads the shader source code and compiles it. If necessary, free memory.
* \param source source code of the shader
* \param type type of the shader. Only supported Vertex and Fragment
* \return the compiled shader identifier, or CSHD_NO_SHADER in the attribute ShaderId
*/
std::shared_ptr<CShader> CShader::CompileFromMemory(const std::vector<std::string> source, CSHDR_TYPE type){

	std::shared_ptr<CShader> result = std::shared_ptr<CShader>(new CShader());
	result->Type = type;
	result->ShaderId = glCreateShader(GLTypes[type]);
	if (CSHDR_NO_SHADER == result->ShaderId){
		std::cerr << "there was a problem when creating the shader" << std::endl;
		return nullptr;
	}
	unsigned int nlines = (GLsizei)source.size();

#ifdef _DEBUG
	std::cerr << std::endl << "Codigo fuente del CShader: " << std::endl;
	for (GLsizei j = 0; j<nlines; j++)
		std::cerr << std::setw(3) << j + 1 << " |" << source[j]; // << std::endl;
#endif

	GLchar* *src;
	src = new GLchar*[nlines];
	if (src == NULL){
		return nullptr;
	}
	for (int i = 0; i < nlines; i++){
		src[i] = (GLchar*)source[i].c_str();
	}

	glShaderSource(result->ShaderId, nlines, (const GLchar* *)src, NULL);
	if (GL_NO_ERROR != glGetError()){
		std::cerr << "there was a problem when loading the shader" << std::endl;
		return nullptr;
	}
	GLint compiled;
	glCompileShader(result->ShaderId);
	glGetShaderiv(result->ShaderId, GL_COMPILE_STATUS, &compiled);

	delete[]src;

	if (GL_FALSE == compiled) {
		GLint length;
		GLchar* log;
		glGetShaderiv(result->ShaderId, GL_INFO_LOG_LENGTH, &length);
		log = new GLchar[length];
		glGetShaderInfoLog(result->ShaderId, length, &length, log);
		std::cerr << "Error compilando el shader:" << std::endl;
		std::cerr << log << std::endl;
		delete[] log;
		glDeleteShader(result->ShaderId);
		result->ShaderId = CSHDR_NO_SHADER;
		return nullptr;
	}
	return result;
}