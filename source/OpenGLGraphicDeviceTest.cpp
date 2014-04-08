///////////////////////////////////////////////////////////////////////////
// Copyright (C) 2013 Jimmie Bergmann - jimmiebergmann@gmail.com
//
// This software is provided 'as-is', without any express or
// implied warranty. In no event will the authors be held
// liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute
// it freely, subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but
//    is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any
//    source distribution.
// ///////////////////////////////////////////////////////////////////////////

#include <OpenGLGraphicDeviceTest.hpp>
#include <Bit/Graphics/OpenGL/OpenGLGraphicDevice.hpp>
#include <Bit/Graphics/VertexArrayObject.hpp>
#include <Bit/Graphics/ShaderProgram.hpp>
#include <Bit/Graphics/Shader.hpp>
#include <Bit/Graphics/Texture.hpp>
#include <Bit/System/Timer.hpp>
#include <Bit/System/MemoryLeak.hpp>

// Constructor
OpenGLGraphicDeviceTest::OpenGLGraphicDeviceTest( ) :
	Test( )
{
}

// Virtual functions
void OpenGLGraphicDeviceTest::Run( std::ostream & p_Trace )
{
	std::cout << "-------------------------------------------" << std::endl;
	std::cout << "Starting OpenGL Graphic Device test." << std::endl;

	// Create the window
	const Bit::VideoMode videoMode( Bit::Vector2u32( 800, 600 ), 24 );
	Bit::RenderWindow window( videoMode, "title" );
	TestAssert( window.IsOpen( ) == true );

	// Create the graphic device
	Bit::GraphicDevice * pGraphicDevice = new Bit::OpenGLGraphicDevice( window );
	TestAssert( pGraphicDevice->IsOpen( ) == true );

	std::cout << "Context version: " << pGraphicDevice->GetVersion( ).Major << "." << pGraphicDevice->GetVersion( ).Minor << std::endl;

	// Set the clear color
	pGraphicDevice->SetClearColor( 16, 26, 37, 255 );

	// Create a VBO for the positions
	Bit::VertexBufferObject * pVboPositions = pGraphicDevice->CreateVertexBufferObject( );
	Bit::Float32 pPositionData[ ] =
	{
		0.0f, 0.0f, 0.0f,
		100.0f, 0.0f, 0.0f,
		100.0f, 100.0f, 0.0f,

		0.0f, 0.0f, 0.0f,
		100.0f, 100.0f, 0.0f,
		0.0f, 100.0f, 0.0f
	};
	TestAssert( pVboPositions->Load( 72, pPositionData ) == true );

	// Create a VBO for the texture coords
	Bit::VertexBufferObject * pVboTextureCoords = pGraphicDevice->CreateVertexBufferObject( );
	Bit::Float32 pTextureCoordData[ ] =
	{
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,

		0.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f
	};
	TestAssert( pVboTextureCoords->Load( 48, pTextureCoordData ) == true );

	// Create a VAO and add the VBO
	Bit::VertexArrayObject * pVAO = pGraphicDevice->CreateVertexArrayObject( );
	TestAssert( pVAO->AddVertexBuffer( *pVboPositions, 3, Bit::DataType::Float32 ) == true );
	TestAssert( pVAO->AddVertexBuffer( *pVboTextureCoords, 2, Bit::DataType::Float32 ) == true );

	// Create a vertex shader and compile it
	Bit::Shader * pVertexShader = pGraphicDevice->CreateShader( Bit::ShaderType::Vertex );
	TestAssert( pVertexShader->CompileFromFile( "shader.vert" ) == true );

	// Create a fragment shader and compile it
	Bit::Shader * pFragmentShader = pGraphicDevice->CreateShader( Bit::ShaderType::Fragment );
	TestAssert( pFragmentShader->CompileFromFile( "shader.frag" ) == true );

	// Create a shader program, attach shader and link the program
	Bit::ShaderProgram * pShaderProgram = pGraphicDevice->CreateShaderProgram( );
	TestAssert( pShaderProgram->AttachShader( *pVertexShader ) == true );
	TestAssert( pShaderProgram->AttachShader( *pFragmentShader ) == true );
	pShaderProgram->SetAttributeLocation( "position", 0 );
	pShaderProgram->SetAttributeLocation( "texture", 1 );
	TestAssert( pShaderProgram->Link( ) == true );

	// Set the projection matrix
	Bit::Matrix4x4f32 projMatrix;
	projMatrix.Orthographic( 0.0f, 800.0f, 0.0f, 600.0f, -1.0f, 1.0f );
	Bit::Matrix4x4f32 viewMatrix;
	viewMatrix.Identity( );
	pShaderProgram->Bind( );
	pShaderProgram->SetUniformMatrix4x4f( "projectionMatrix", projMatrix );
	pShaderProgram->SetUniformMatrix4x4f( "viewMatrix", viewMatrix );
	pShaderProgram->SetUniform1i( "colorTexture", 0 );
	pShaderProgram->Unbind( );
	
	// Create a texture
	Bit::Texture * pTexture = pGraphicDevice->CreateTexture( );
	static const Bit::Uint8 imageData[ 9 * 4 ] =
	{
		255, 50, 0, 255,		0, 255, 0, 255,			0, 0, 255, 255,
		255, 255, 255, 225,		0, 0, 0, 255,			255, 0, 255, 255,
		0, 255, 255, 255,		255, 127, 0, 255,		127, 127, 127, 255
	};
	TestAssert( pTexture->LoadFromMemory( imageData, Bit::Vector2u32( 3, 3 ) ) == true );

	// Start a timer
	Bit::Timer timer;
	timer.Start( );
	Bit::Float64 rotation = 0.0f;

	// Run the game loop
	while( window.IsOpen( ) )
	{
		// Add the delta time to the rotation
		rotation += timer.GetLapsedTime( ).AsSeconds( ) * 60.0f;
		if( rotation >= 360.0f )
		{
			rotation -= 360.0f;
		}
		timer.Start( );

		// Update the window
		window.Update( );

		// Poll the events
		Bit::Event e;
		while( window.PollEvent( e ) )
		{
			switch( e.Type )
			{
				case Bit::Event::Closed:
				{
					window.Close( );
				}
				break;
			}
		}

		// Clear the color
		pGraphicDevice->ClearColor( );
		pGraphicDevice->ClearDepth( );

		// Update the view matrix(rotate the primitive)
		viewMatrix.Identity( );
		viewMatrix.Translate( 400.0f, 300.0f, 0.0f );
		viewMatrix.RotateZ( static_cast<Bit::Float32>( rotation ) );
		viewMatrix.Translate( -50.0f, -50.0f, 0.0f );
		

		// Render
		pShaderProgram->Bind( );
		pShaderProgram->SetUniformMatrix4x4f( "viewMatrix", viewMatrix );
		pTexture->Bind( );
		pVAO->Render( Bit::PrimitiveMode::Triangles );
		pTexture->Unbind( );
		pShaderProgram->Unbind( );

		// Swap the buffers
		pGraphicDevice->Present( );
	}

	// Delete and close everything
	delete pVboPositions;
	delete pVboTextureCoords;
	delete pVAO;
	delete pVertexShader;
	delete pFragmentShader;
	delete pShaderProgram;
	delete pTexture;
	delete pGraphicDevice;
	window.Close( );

	// Print the finish text
	std::cout << "Finished OpenGL Graphic Device Test." << std::endl;
	std::cout << "-------------------------------------------" << std::endl;
	
}