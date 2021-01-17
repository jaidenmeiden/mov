/**	Definition of the class UGKShaderProgram
*	Class for managing a shader program
*	Prefix: CSHDP_

*	@author Joaquim Montell
*	@version 2015-16
*/

#include <vector>
#include <string>
#include <memory>
#include "UGKShader.h"

#ifndef CSHDP_H
#define CSHDP_H


class CShaderProgram {

private:
	/**
	* OpenGL program's ID
	*/
	GLuint ProgramId; // OpenGL program's ID
	std::shared_ptr<CShader> Shaders[CSHDR_MAX_TYPES];
	GLboolean Linked;
	struct Attribute {
		unsigned int loc;
		std::string name;
	};
	std::vector<Attribute> attribs;
	void bindAttribs();

public:

	CShaderProgram();
	~CShaderProgram();

	bool AddShaders(std::string source, CSHDR_TYPE type);
	bool AddShaders(const std::vector<std::string>, CSHDR_TYPE type);
	bool AddShaders(std::shared_ptr<CShader> shader);

	bool Link();

	void Bind();
	void Unbind();
	void BindAttributeLocation(const char * name, int location);
	void BindAttributeLocation(std::string name, int location);
	inline GLuint GetProgramId(){ return ProgramId; }

	void SetUniform(GLint location, GLfloat v0);
	void SetUniform(GLint location, GLfloat v0, GLfloat v1);
	void SetUniform(GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
	void SetUniform(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
	void SetUniform(GLint location, GLint v0);
	void SetUniform(GLint location, GLint v0, GLint v1);
	void SetUniform(GLint location, GLint v0, GLint v1, GLint v2);
	void SetUniform(GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
	void SetUniform(GLint location, GLuint v0);
	void SetUniform(GLint location, GLuint v0, GLuint v1);
	void SetUniform(GLint location, GLuint v0, GLuint v1, GLuint v2);
	void SetUniform(GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
	void SetUniformArray(GLint location, GLsizei elementSize, GLsizei count, const GLfloat *value);
	void SetUniformArray(GLint location, GLsizei elementSize, GLsizei count, const GLint *value);
	void SetUniformArray(GLint location, GLsizei elementSize, GLsizei count, const GLuint *value);
	void SetUniformMatrix(GLint location, GLsizei rows, GLsizei columns, GLsizei count, const GLfloat *value, GLboolean transpose = GL_FALSE);

	GLint GetUniformLocation(const GLchar *name);


};

#endif