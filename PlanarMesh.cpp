#include "PlanarMesh.h"
#include "common\texture.hpp"

PLANARMESH::PLANARMESH () {}

PLANARMESH::~PLANARMESH ()
	{
	glDeleteBuffers ( 1, &vertexbuffer );
	glDeleteBuffers ( 1, &uvbuffer );

	glDeleteTextures ( 1, &TextureID1 );
	glDeleteTextures ( 1, &TextureID2 );
	glDeleteTextures ( 1, &TextureID3 );
	glDeleteTextures ( 1, &TextureID4 );
	}

void PLANARMESH::LoadTexture ( textureNumbers _textureNumber, const char * fragment_file_path )
	{
	int result = loadBMP_custom ( fragment_file_path );
	if ( result )
		{
		switch ( _textureNumber )
			{
			case PLANARMESH::first:
				//glDeleteTextures ( 1, &TextureID1 );
				Textures[ 0 ] = result; TextureID1 = glGetUniformLocation ( programID, "Texture1" );
				break;
			case PLANARMESH::second:
				//glDeleteTextures ( 1, &TextureID2 );
				Textures[ 1 ] = result; TextureID2 = glGetUniformLocation ( programID, "Texture2" );
				break;
			case PLANARMESH::third:
				//glDeleteTextures ( 1, &TextureID3 );
				Textures[ 2 ] = result; TextureID3 = glGetUniformLocation ( programID, "Texture3" );
				break;
			case PLANARMESH::fourth:
				//glDeleteTextures ( 1, &TextureID4 );
				Textures[ 3 ] = result; TextureID4 = glGetUniformLocation ( programID, "Texture4" );
				break;
			default:
				break;
			}
		}

	}

void PLANARMESH::ChangeMeshSize ( int _x, int _y )
	{
	Vertices[ 0 ] = -STEP*_x; Vertices[ 1 ] = 0; Vertices[ 2 ] = STEP*_y;
	Vertices[ 3 ] = STEP*_x; Vertices[ 4 ] = 0; Vertices[ 5 ] = STEP*_y;
	Vertices[ 6 ] = -STEP*_x; Vertices[ 7 ] = 0; Vertices[ 8 ] = -STEP*_y;

	Vertices[ 9 ] = -STEP*_x; Vertices[ 10 ] = 0; Vertices[ 11 ] = -STEP*_y;
	Vertices[ 12 ] = STEP*_x; Vertices[ 13 ] = 0; Vertices[ 14 ] = STEP*_y;
	Vertices[ 15 ] = STEP*_x; Vertices[ 16 ] = 0; Vertices[ 17 ] = -STEP*_y;

	glDeleteBuffers ( 1, &vertexbuffer );

	glGenBuffers ( 1, &vertexbuffer );
	glBindBuffer ( GL_ARRAY_BUFFER, vertexbuffer );
	glBufferData ( GL_ARRAY_BUFFER, sizeof ( Vertices ), Vertices, GL_STATIC_DRAW );
	}

void PLANARMESH::CreateUVBuffer ()
	{
	uvVertices[ 0 ] = 0; uvVertices[ 1 ] = 1;
	uvVertices[ 2 ] = 1; uvVertices[ 3 ] = 1;
	uvVertices[ 4 ] = 0; uvVertices[ 5 ] = 0;

	uvVertices[ 6 ] = 0; uvVertices[ 7 ] = 0;
	uvVertices[ 8 ] = 1; uvVertices[ 9 ] = 1;
	uvVertices[ 10 ] = 1; uvVertices[ 11 ] = 0;

	glDeleteBuffers ( 1, &uvbuffer );

	glGenBuffers ( 1, &uvbuffer );
	glBindBuffer ( GL_ARRAY_BUFFER, uvbuffer );
	glBufferData ( GL_ARRAY_BUFFER, sizeof ( uvVertices ), uvVertices, GL_STATIC_DRAW );
	}
