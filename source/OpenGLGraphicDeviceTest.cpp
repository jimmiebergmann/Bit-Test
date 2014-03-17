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
	pGraphicDevice->SetClearColor( 255, 0, 0, 255 );

	// Create a VBO
	Bit::VertexBufferObject * pVBO = pGraphicDevice->CreateVertexBufferObject( );
	Bit::Float32 pVertexData[ ] =
	{
		0, 0, 0,
		100, 0, 0,
		100, 100, 0
	};
	TestAssert( pVBO->Load( 36, pVertexData ) == true );

	// Create a VAO and add the VBO
	Bit::VertexArrayObject * pVAO = pGraphicDevice->CreateVertexArrayObject( );
	TestAssert( pVAO->AddVertexBuffer( *pVBO, 3, Bit::DataType::Float32 ) == true );

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
	TestAssert( pShaderProgram->Link( ) == true );

	// Set the projection matrix
	Bit::Matrix4x4f32 matrix;
	matrix.Orthographic( 0.0f, 800.0f, 0.0f, 600.0f, -1.0f, 1.0f );
	pShaderProgram->Bind( );
	pShaderProgram->SetUniformMatrix4x4f( "projectionMatrix", matrix );
	pShaderProgram->Unbind( );

	// Run the game loop
	while( window.IsOpen( ) )
	{
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

		// Render
		pShaderProgram->Bind( );
		pVAO->Render( Bit::PrimitiveMode::Triangles );
		pShaderProgram->Unbind( );

		// Swap the buffers
		pGraphicDevice->Present( );
	}

	// Delete and close everything
	delete pVBO;
	delete pVAO;
	delete pShaderProgram;
	delete pGraphicDevice;
	window.Close( );

	// Print the finish text
	std::cout << "Finished OpenGL Graphic Device Test." << std::endl;
	std::cout << "-------------------------------------------" << std::endl;
	
}