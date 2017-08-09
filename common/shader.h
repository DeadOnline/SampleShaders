#ifndef SHADER_HPP
#define SHADER_HPP

#include "..\glut\glew-1.11.0\include\GL\glew.h"

GLuint	LoadVertexShader(const char * vertex_file_path);
GLuint	LoadFragmentShader(const char * fragment_file_path);
void	DeleteShader(GLuint ProgramID, GLuint ShaderID);
GLuint	LinkProgram (GLuint VertexShaderID, GLuint FragmentShaderID);

#endif
