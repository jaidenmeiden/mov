/**	Definition of the class UGKShader
*	Class for managing a shader program
*	Prefix: CSHDR_

*	@author Joaquim Montell
*	@version 2015-16
*/

#include <glee/GLee.h>
#include <memory>


#ifndef CSHDR_H
#define CSHDR_H

#define CSHDR_NO_SHADER 0

typedef enum CSHDR_TYPE{
	CSHDR_VERTEX,
	CSHDR_FRAGMENT,
	CSHDR_MAX_TYPES
};


class CShader{

	GLuint Type,		///< GL_VERTEX_SHADER / GL_FRAGMENT_SHADER
		   ShaderId;	///< CShader identifier

	CShader();
public:
	~CShader();

	static std::shared_ptr<CShader> CompileFromSource(std::string source, CSHDR_TYPE type);
	static std::shared_ptr<CShader> CompileFromMemory(const std::vector<std::string> source, CSHDR_TYPE type);

	inline GLuint GetType(){ return Type; }
	inline GLuint GetId(){ return ShaderId; }
	//add a method to manage preprocessor like directive as #include or #define.

};

#endif