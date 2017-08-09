#pragma once

#include "glut\glew-1.11.0\include\GL\glew.h"
#include "glm-0.9.7.1/glm/glm.hpp"

#define BUFFERPOINTSQUANTITY 6
#define TEXTURESQUANTITY 4
#define STEP 0.1
#define DEFAULT_X 10
#define DEFAULT_Y 10

class PLANARMESH
	{
	public:
		enum textureNumbers { first, second, third, fourth } textureNumber;

		PLANARMESH ();
		~PLANARMESH ();

		void LoadTexture (textureNumbers _textureNumber, const char * fragment_file_path );
		void ChangeMeshSize (int _x, int _y);
		void CreateUVBuffer ();
		
	public:

		int x, y;

		GLuint	Textures[ TEXTURESQUANTITY ];
		GLfloat Vertices [BUFFERPOINTSQUANTITY * 3];
		GLfloat uvVertices [BUFFERPOINTSQUANTITY * 2];
		GLuint	VertexShaderID, FragmentShaderID;

		GLuint vertexShaderID;
		GLuint fragmentShaderID;
		GLuint programID;

		GLuint TextureID1;
		GLuint TextureID2;
		GLuint TextureID3;
		GLuint TextureID4;

		GLuint vertexbuffer;
		GLuint uvbuffer;

		GLuint VertexArrayID;

		GLuint MatrixID;
		glm::mat4 MVP;
	};