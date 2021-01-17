/*	Treatment of the OpenGL errors management

	@author Ramon Molla
	@version 2014-10
*/

#include <UGKglError.h>
#include <UGKLog.h>

namespace UGK
{
/**
	* @fn gl_Error
	* Function to display errors that can generated in the execution of the game
	* These errors are defined for teams that are not compatible with the requirements set
    * Shows the errors generated in the execution of the game
    * These errors are defined for compatibility and play requirements
*/
GLenum UGKGLE_glError()
{
	GLenum Error; /// Create a variable to store the error

	Error = glGetError(); /// Rescuing the error is generated
	/// See what the error was generated if there was
  	switch(Error)
	{
	case GL_INVALID_ENUM: /// Texture error loaded the Game
		BOX(LPCTSTR("Error: amount of textures to be generated is invalid.")); 
		break;
	case GL_INVALID_VALUE:  /// /Error de textura fuera de los rangos
		BOX(LPCTSTR("Error: amount of textures to be generated is out of range."));
		break;
	case GL_INVALID_OPERATION: /// The operation is not allowed in the current state
		BOX(LPCTSTR("Error: The specified operation is not allowed in the current state."));
		break;
	case GL_NO_ERROR: 
		//BOX("Error: No error has been recorded.");
		break;
	case GL_STACK_OVERFLOW: /// It has generated an error stack overflow
		BOX(LPCTSTR("Error: This function would cause a stack overflow."));
		break;
	case GL_STACK_UNDERFLOW:  /// It has generated an error stack overflow
		BOX(LPCTSTR("Error: This function would cause a stack underflow."));
		break;
	case GL_OUT_OF_MEMORY: /// Not enough memory to run the function
		BOX(LPCTSTR("Error: There is not enough memory left to execute the function."));
		break;
	default:
		BOX(LPCTSTR("Unknown error."));
		break;
	}
	return Error;
}
}	//namespace
