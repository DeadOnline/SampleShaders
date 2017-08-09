#include "shader.h"

#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

#include <stdlib.h>
#include <string.h>

GLuint LoadFragmentShader(const char * fragment_file_path)
	{
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

#pragma region READ
	// Read the Fragment Shader code from the file
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream ( fragment_file_path, std::ios::in );
	if ( FragmentShaderStream.is_open () )
		{
		std::string Line = "";
		while ( getline ( FragmentShaderStream, Line ) )
			FragmentShaderCode += "\n" + Line;
		FragmentShaderStream.close ();
		}
#pragma endregion
#pragma region COMPILE
	// Compile Fragment Shader
	printf("Compiling shader : %s\n", fragment_file_path);
	char const * FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
	glCompileShader(FragmentShaderID);
#pragma endregion

	GLint Result = GL_FALSE;
	int InfoLogLength;

#pragma region CHECK
	// Check Fragment Shader
	glGetShaderiv ( FragmentShaderID, GL_COMPILE_STATUS, &Result );
	glGetShaderiv ( FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength );
	if ( InfoLogLength > 0 )
		{
		std::vector<char> FragmentShaderErrorMessage ( InfoLogLength + 1 );
		glGetShaderInfoLog ( FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[ 0 ] );
		printf ( "%s\n", &FragmentShaderErrorMessage[ 0 ] );
		}
#pragma endregion	

	return FragmentShaderID;
	}
GLuint LoadVertexShader ( const char * vertex_file_path )
	{
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	
#pragma region READ
	std::string VertexShaderCode;
	std::ifstream VertexShaderStream ( vertex_file_path, std::ios::in );
	if ( VertexShaderStream.is_open () )
		{
		std::string Line = "";
		while ( getline ( VertexShaderStream, Line ) )
			VertexShaderCode += "\n" + Line;
		VertexShaderStream.close ();
		}
	else
		{
		printf ( "Impossible to open %s. Are you in the right directory ?\n", vertex_file_path );
		return 0;
		}
#pragma endregion	
#pragma region COMPILE
	printf ( "Compiling shader : %s\n", vertex_file_path );
	char const * VertexSourcePointer = VertexShaderCode.c_str ();
	glShaderSource ( VertexShaderID, 1, &VertexSourcePointer, NULL );
	glCompileShader ( VertexShaderID );
#pragma endregion

	GLint Result = GL_FALSE;
	int InfoLogLength;

#pragma region CHECK
	glGetShaderiv ( VertexShaderID, GL_COMPILE_STATUS, &Result );
	glGetShaderiv ( VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength );
	if ( InfoLogLength > 0 )
		{
		std::vector<char> VertexShaderErrorMessage ( InfoLogLength + 1 );
		glGetShaderInfoLog ( VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[ 0 ] );
		printf ( "%s\n", &VertexShaderErrorMessage[ 0 ] );
		}
#pragma endregion
		
	return VertexShaderID;
	}

void DeleteShader ( GLuint ProgramID, GLuint ShaderID )
	{
	glDetachShader(ProgramID, ShaderID);
	glDeleteShader(ShaderID);
	}

GLuint LinkProgram (GLuint VertexShaderID, GLuint FragmentShaderID)
	{
	GLint Result = GL_FALSE;
	int InfoLogLength;

	// Link the program
	printf("Linking program\n");
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	// Check the program
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> ProgramErrorMessage(InfoLogLength+1);
		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
		}

	return ProgramID;
	}