#include "UGKShaderProgram.h"
#include <iostream>

#define CSHDP_NO_PROGRAM 0

/**
* \fn void CShaderProgram::CShaderProgram()
* Class constructor. Builds an unitialized shader program
*/
CShaderProgram::CShaderProgram(){
	ProgramId = CSHDP_NO_PROGRAM;
	Linked = GL_FALSE;
}

/**
* \fn void CShaderProgram::~CShaderProgram()
* Class destructor.
*/
CShaderProgram::~CShaderProgram(){
	glDeleteProgram(ProgramId);
	ProgramId = 0;
}


/**
* \fn bool CShaderProgram::AddShaders(std::string source, CSHDR_TYPE type)
* Add a shader from a file
* \param source The path for the file containing the shader code
* \param type The type of the shader
* \return true if the shader get compiled
*/
bool CShaderProgram::AddShaders(std::string source, CSHDR_TYPE type){
	Shaders[type] = CShader::CompileFromSource(source, type);
	Linked = GL_FALSE;
	return Shaders[type] != nullptr;
}

/**
* \fn bool CShaderProgram::AddShaders(const std::vector<std::string> source, CSHDR_TYPE type)
* Add a shader from memory
* \param source The lines of the shader code
* \param type The type of the shader
* \return true if the shader get compiled
*/
bool CShaderProgram::AddShaders(const std::vector<std::string> source, CSHDR_TYPE type){
	Shaders[type] = CShader::CompileFromMemory(source, type);
	Linked = GL_FALSE;
	return Shaders[type] != nullptr;
}

/**
* \fn bool CShaderProgram::AddShaders(std::shared_ptr<CShader> shader)
* Add a compiled shader
* \param shader The shader 
* \return true if the shader get compiled
*/
bool CShaderProgram::AddShaders(std::shared_ptr<CShader> shader){
	if (shader->GetId() == CSHDR_NO_SHADER) return false;
	Shaders[shader->GetType()] = shader;
	Linked = GL_FALSE;
	return Shaders[shader->GetType()] != nullptr;
}

/**
* \fn bool  CShaderProgram::Link()
* Link the program
* \return true if the program get linked
*/
bool CShaderProgram::Link(){
	GLint program_ok;

	if (ProgramId != 0) {
		glDeleteProgram(ProgramId);
		ProgramId = 0;
	}

	ProgramId = glCreateProgram();

	bindAttribs();

	for (int i = 0; i < CSHDR_MAX_TYPES; i++){
		if (Shaders[i]!=nullptr){
			glAttachShader(ProgramId, Shaders[i]->GetId());
		}
	}

	glLinkProgram(ProgramId);
	glGetProgramiv(ProgramId, GL_LINK_STATUS, &program_ok);
	if (!program_ok) {
		std::cerr << "there was a problem when linking the shader" << std::endl;

		GLint maxLenght = 0;
		glGetProgramiv(ProgramId,GL_INFO_LOG_LENGTH,&maxLenght);
		std::vector<GLchar> infolog(maxLenght);

		glGetProgramInfoLog(ProgramId,maxLenght,&maxLenght,&infolog[0]);

		glDeleteProgram(ProgramId);
		ProgramId = 0;
		return false;

	}
	Linked = true;
	return true;
}

/**
* \fn void CShaderProgram::Bind()
* makes the gpu use the program
*/
void CShaderProgram::Bind(){
	if (Linked){
		glUseProgram(ProgramId);

	}
	else{
		std::cerr << "the shader isn't linked" << std::endl;
	}

}

/**
* \fn void CShaderProgram::Unbind()
* Stop the gpu from using a program
*/
void CShaderProgram::Unbind(){
	glUseProgram(CSHDP_NO_PROGRAM);
}

/**
* \fn void CShaderProgram::BindAtributeLocation(const char * name, int location)
* Tell the program the location of the attrbutes
* \warning Call before compilling the program
* \param name Variable name of the attribute
* \param loc Postion of the attribute

*/
void CShaderProgram::BindAttributeLocation(const char * name, int location){
	Attribute at;
	at.loc = location;
	at.name = name;

	attribs.push_back(at);
}

void CShaderProgram::BindAttributeLocation(std::string name, int location){
	BindAttributeLocation(name.c_str(),location);
}

void CShaderProgram::bindAttribs(){
	for (unsigned int i = 0; i < attribs.size(); i++)
		glBindAttribLocation(ProgramId, attribs[i].loc, attribs[i].name.c_str());

}

void CShaderProgram::SetUniform(GLint location, GLfloat v0){
	glUniform1f(location, v0);
}

void CShaderProgram::SetUniform(GLint location, GLfloat v0, GLfloat v1){
	glUniform2f(location, v0, v1);
}

void CShaderProgram::SetUniform(GLint location, GLfloat v0, GLfloat v1, GLfloat v2){
	glUniform3f(location, v0, v1, v2);
}

void CShaderProgram::SetUniform(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3){
	glUniform4f(location, v0, v1, v2, v3);
}

void CShaderProgram::SetUniform(GLint location, GLint v0){
	glUniform1i(location, v0);
}

void CShaderProgram::SetUniform(GLint location, GLint v0, GLint v1){
	glUniform2i(location, v0, v1);
}

void CShaderProgram::SetUniform(GLint location, GLint v0, GLint v1, GLint v2){
	glUniform3i(location, v0, v1, v2);
}

void CShaderProgram::SetUniform(GLint location, GLint v0, GLint v1, GLint v2, GLint v3){
	glUniform4i(location, v0, v1, v2, v3);
}

void CShaderProgram::SetUniform(GLint location, GLuint v0){
	glUniform1ui(location, v0);
}

void CShaderProgram::SetUniform(GLint location, GLuint v0, GLuint v1){
	glUniform2ui(location, v0, v1);
}

void CShaderProgram::SetUniform(GLint location, GLuint v0, GLuint v1, GLuint v2){
	glUniform3ui(location, v0, v1, v2);
}

void CShaderProgram::SetUniform(GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3){
	glUniform4ui(location, v0, v1, v2, v3);
}

void CShaderProgram::SetUniformArray(GLint location, GLsizei elementSize, GLsizei count, const GLfloat *value){
	switch (elementSize){
	case 1:
		glUniform1fv(location, count, value);
		break;
	case 2:
		glUniform2fv(location, count, value);
		break;
	case 3:
		glUniform3fv(location, count, value);
		break;
	case 4:
		glUniform4fv(location, count, value);
		break;
	default:
		std::cerr << "wrong element size, must be in range 1-4" << std::endl;
	}
}

void CShaderProgram::SetUniformArray(GLint location, GLsizei elementSize, GLsizei count, const GLint *value){
	switch (elementSize){
	case 1:
		glUniform1iv(location, count, value);
		break;
	case 2:
		glUniform2iv(location, count, value);
		break;
	case 3:
		glUniform3iv(location, count, value);
		break;
	case 4:
		glUniform4iv(location, count, value);
		break;
	default:
		std::cerr << "wrong element size, must be in range 1-4" << std::endl;
	}
}

void CShaderProgram::SetUniformArray(GLint location, GLsizei elementSize, GLsizei count, const GLuint *value){
	switch (elementSize){
	case 1:
		glUniform1uiv(location, count, value);
		break;
	case 2:
		glUniform2uiv(location, count, value);
		break;
	case 3:
		glUniform3uiv(location, count, value);
		break;
	case 4:
		glUniform4uiv(location, count, value);
		break;
	default:
		std::cerr << "wrong element size, must be in range 1-4" << std::endl;
	}
}

void CShaderProgram::SetUniformMatrix(GLint location, GLsizei rows, GLsizei columns, GLsizei count, const GLfloat *value, GLboolean transpose){
	switch (columns){
	case 2:
		switch (rows){
		case 2:
			glUniformMatrix2fv(location, count, transpose, value);
			break;
		case 3:
			glUniformMatrix2x3fv(location, count, transpose, value);
			break;
		case 4:
			glUniformMatrix2x4fv(location, count, transpose, value);
			break;
		default:
			std::cerr << "wrong number of rows, range in 2-4" << std::endl;
		}
		break;
	case 3:
		switch (rows){
		case 2:
			glUniformMatrix3x2fv(location, count, transpose, value);
			break;
		case 3:
			glUniformMatrix3fv(location, count, transpose, value);
			break;
		case 4:
			glUniformMatrix3x4fv(location, count, transpose, value);
			break;
		default:
			std::cerr << "wrong number of rows, range in 2-4" << std::endl;
		}
		break;
	case 4:
		switch (rows){
		case 2:
			glUniformMatrix4x2fv(location, count, transpose, value);
			break;
		case 3:
			glUniformMatrix4x3fv(location, count, transpose, value);
			break;
		case 4:
			glUniformMatrix4fv(location, count, transpose, value);
			break;
		default:
			std::cerr << "wrong number of rows, range in 2-4" << std::endl;
		}
		break;
	default:
		std::cerr << "wrong number of columns, range in 2-4" << std::endl;
	}
}

GLint CShaderProgram::GetUniformLocation(const GLchar *name){

	return glGetUniformLocation(ProgramId, name);

}