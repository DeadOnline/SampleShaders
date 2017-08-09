#pragma once

#include "PlanarMesh.h"
#include "common\shader.h"
#include "common\texture.hpp"

#include "glut\freeglut\include\GL\freeglut.h"
#include "glm-0.9.7.1\glm\gtc\matrix_transform.hpp"
#include "glui-2.35\include\GL\glui.h"

#include <iostream>

#pragma region PLANARMESH
PLANARMESH mesh;
#pragma endregion

#pragma region GLUT
int   main_window;

#define TEX1ADRESS "assets/1.bmp"
#define TEX2ADRESS "assets/2.bmp"
#define TEX3ADRESS "assets/3.bmp"
#define TEX4ADRESS "assets/4.bmp"

#pragma region GLM
void preload ()
	{
	// Dark blue background
	glClearColor ( 0.0f, 0.0f, 0.0f, 0.0f );

	// Enable depth test
	glEnable ( GL_DEPTH_TEST );
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc ( GL_LESS );

	glGenVertexArrays ( 1, &mesh.VertexArrayID );
	glBindVertexArray ( mesh.VertexArrayID );

	// Create and compile our GLSL program from the shaders

	mesh.vertexShaderID = LoadVertexShader ( "assets/TransformVertexShader.vertexshader" );
	mesh.fragmentShaderID = LoadFragmentShader ( "assets/TextureFragmentShader.fragmentshader" );
	mesh.programID = LinkProgram ( mesh.vertexShaderID, mesh.fragmentShaderID );

	// Get a handle for our "MVP" uniform
	mesh.MatrixID = glGetUniformLocation ( mesh.programID, "MVP" );

	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	glm::mat4 Projection = glm::perspective ( 45.0f, 4.0f / 3.0f, 0.1f, 100.0f );
	// Camera matrix
	glm::mat4 View = glm::lookAt (
		glm::vec3 ( 1, -3, -1 ), // Camera is at (4,3,3), in World Space
		glm::vec3 ( 0, 0, 0 ), // and looks at the origin
		glm::vec3 ( 0, -1, 0 )  // Head is up (set to 0,-1,0 to look upside-down)
		);
	// Model matrix : an identity matrix (model will be at the origin)
	glm::mat4 Model = glm::mat4 ( 1.0f );
	// Our ModelViewProjection : multiplication of our 3 matrices
	mesh.MVP = Projection * View * Model; // Remember, matrix multiplication is the other way around

	mesh.ChangeMeshSize (DEFAULT_X, DEFAULT_Y);
	mesh.CreateUVBuffer ();

	mesh.LoadTexture ( PLANARMESH::first, TEX1ADRESS );
	mesh.LoadTexture ( PLANARMESH::second, TEX2ADRESS );
	mesh.LoadTexture ( PLANARMESH::third, TEX3ADRESS );
	mesh.LoadTexture ( PLANARMESH::fourth, TEX4ADRESS );
	};
#pragma endregion
void changeViewPort ( int w, int h )
	{
	glViewport ( 0, 0, w, h );
	}
void render ()
	{
	// Clear the screen
	glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	// Use our shader
	glUseProgram ( mesh.programID );

	// Send our transformation to the currently bound shader, 
	// in the "MVP" uniform
	glUniformMatrix4fv ( mesh.MatrixID, 1, GL_FALSE, &mesh.MVP[ 0 ][ 0 ] );

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray ( 0 );
	glBindBuffer ( GL_ARRAY_BUFFER, mesh.vertexbuffer );
	glVertexAttribPointer (
		0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		( void* ) 0            // array buffer offset
		);

	// 2nd attribute buffer : UVs
	glEnableVertexAttribArray ( 1 );
	glBindBuffer ( GL_ARRAY_BUFFER, mesh.uvbuffer );
	glVertexAttribPointer (
		1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
		2,                                // size : U+V => 2
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		( void* ) 0                          // array buffer offset
		);

	glActiveTexture ( GL_TEXTURE0 );
	glBindTexture ( GL_TEXTURE_2D, mesh.Textures[0] );

	glActiveTexture ( GL_TEXTURE1 );
	glBindTexture ( GL_TEXTURE_2D, mesh.Textures[1] );

	glActiveTexture ( GL_TEXTURE2 );
	glBindTexture ( GL_TEXTURE_2D, mesh.Textures[2] );

	glActiveTexture ( GL_TEXTURE3 );
	glBindTexture ( GL_TEXTURE_2D, mesh.Textures[3] );

	glUniform1i ( mesh.TextureID1, 0 );
	glUniform1i ( mesh.TextureID2, 1 );
	glUniform1i ( mesh.TextureID3, 2 );
	glUniform1i ( mesh.TextureID4, 3 );

	glDrawArrays ( GL_TRIANGLES, 0, BUFFERPOINTSQUANTITY );

	glDisableVertexAttribArray ( 0 );
	glDisableVertexAttribArray ( 1 );

	glutSwapBuffers ();
	}

void myGlutMouse(int button, int button_state, int x, int y )
	{
	if ( button == GLUT_LEFT_BUTTON && button_state == GLUT_DOWN ) {
		mesh.x = x;
		mesh.y = y;
		}
	}
#pragma endregion
#pragma region GLUI
GLUI_Spinner    *spinnerX, *spinnerY;
GLUI_EditText	*A_text, *B_text, *C_text, *D_text;

/** These are the live variables passed into GLUI ***/
int   segments = 6;

void control_cb( int control )
	{
	/********************************************************************
	Here we'll print the user id of the control that generated the
	callback, and we'll also explicitly get the values of each control.
	Note that we really didn't have to explicitly get the values, since
	they are already all contained within the live variables:
	'wireframe',  'segments',  'obj',  and 'text'  
	********************************************************************/

	printf( "callback: %d\n", control );
	printf( "              spinnerX: %d\n", spinnerX->get_int_val() );
	printf( "              spinnerY: %d\n", spinnerY->get_int_val() );

	switch ( control )
		{
		case 0:
		case 1:
			mesh.ChangeMeshSize ( spinnerX->get_int_val (), spinnerY->get_int_val () );
			break;
		case 2:
			mesh.LoadTexture ( PLANARMESH::first, A_text->get_text() );
			break;
		case 3:
			mesh.LoadTexture ( PLANARMESH::second, B_text->get_text() );
			break;
		case 4:
			mesh.LoadTexture ( PLANARMESH::third, C_text->get_text() );
			break;
		case 5:
			mesh.LoadTexture ( PLANARMESH::fourth, D_text->get_text() );
			break;
		default:
			break;
		}

	}
#pragma endregion

using namespace glm;
using namespace std;

void cleanup ()
	{
	DeleteShader ( mesh.programID, mesh.vertexShaderID );
	DeleteShader ( mesh.programID, mesh.fragmentShaderID );

	glDeleteProgram ( mesh.programID );
	glDeleteVertexArrays ( 1, &mesh.VertexArrayID );
	}

void hideConsole ()
	{
#ifdef WIN32
	FreeConsole ();
#endif
	}

int main(int argc, char* argv[]) {

	//hideConsole ();

#pragma region GLUT
	glutInit ( &argc, argv );
	glutInitDisplayMode ( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH );
	glutInitWindowSize ( 1980, 1080 );
	main_window = glutCreateWindow ( "SimpleShader" );
	glutReshapeFunc ( changeViewPort );
	glutDisplayFunc ( render );
	glutMouseFunc( myGlutMouse );

	GLenum err = glewInit ();
	if ( GLEW_OK != err )
		{
		fprintf ( stderr, "GLEW error" );
		return 1;
		}

	preload ();

#pragma region GLUI
	GLUI *glui = GLUI_Master.create_glui ( "GLUI", 0, 800, 800 ); /* name, flags,
																 x, and y */
	new GLUI_StaticText ( glui, "Controls" );
	new GLUI_Separator ( glui );
	spinnerX = new GLUI_Spinner ( glui, "X:", &segments, 0, control_cb );
	spinnerX->set_int_limits ( 1, 20 );
	spinnerX->set_int_val ( 10 );
	spinnerY = new GLUI_Spinner ( glui, "Y:", &segments, 1, control_cb );
	spinnerY->set_int_limits ( 1, 20 );
	spinnerY->set_int_val ( 10 );
	GLUI_Panel *obj_panel = new GLUI_Panel ( glui, "Object Type" );

	A_text = new GLUI_EditText(glui, "Texture A name:");
	A_text->text = TEX1ADRESS;
	new GLUI_Button ( glui, "Change texture A", 2, control_cb );
	B_text = new GLUI_EditText(glui, "Texture B name:");
	B_text->text = TEX2ADRESS;
	new GLUI_Button ( glui, "Change texture B", 3, control_cb );
	C_text = new GLUI_EditText(glui, "Texture C name:");
	C_text->text = TEX3ADRESS;
	new GLUI_Button ( glui, "Change texture C", 4, control_cb );
	D_text = new GLUI_EditText(glui, "Texture D name:");
	D_text->text = TEX4ADRESS;
	new GLUI_Button ( glui, "Change texture D", 5, control_cb );

	new GLUI_Button ( glui, "Quit", 0, ( GLUI_Update_CB ) exit );

	glui->set_main_gfx_window( main_window );
	GLUI_Master.set_glutIdleFunc( NULL );
#pragma endregion

	glutMainLoop ();
#pragma endregion

	cleanup ();
	
	return EXIT_SUCCESS;;
	}