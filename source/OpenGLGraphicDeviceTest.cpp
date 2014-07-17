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
#include <Bit/Graphics/Framebuffer.hpp>
#include <Bit/Graphics/Renderbuffer.hpp>
#include <Bit/Graphics/VertexArray.hpp>
#include <Bit/Graphics/VertexBuffer.hpp>
#include <Bit/Graphics/ShaderProgram.hpp>
#include <Bit/Graphics/Shader.hpp>
#include <Bit/Graphics/Texture.hpp>
#include <Bit/System/MatrixManager.hpp>
#include <MyModelRenderer.hpp>
#include <Bit/Graphics/Model.hpp>
#include <Bit/Graphics/ModelRenderer.hpp>
#include <Bit/System/Timer.hpp>
#include <Bit/System/MemoryLeak.hpp>

// Global variables
static Bit::RenderWindow g_Window;
static Bit::GraphicDevice * g_pGraphicDevice = NULL;
static Bit::Framebuffer * g_pFramebuffer = NULL;
static Bit::Renderbuffer * g_pColorRenderbuffer = NULL;
static Bit::Renderbuffer * g_pDepthRenderbuffer = NULL;
static Bit::Texture * g_pFrameColorTexture = NULL;
static Bit::Texture * g_pFloorTexture = NULL;
static Bit::Texture * g_pQuadTexture = NULL;
static Bit::VertexBuffer * g_pFloorVboPositions = NULL;
static Bit::VertexBuffer * g_pFloorVboTextureCoords = NULL;
static Bit::VertexArray * g_pFloorVAO = NULL;
static Bit::VertexBuffer * g_pQuadVboPositions = NULL;
static Bit::VertexBuffer * g_pQuadVboTextureCoords = NULL;
static Bit::VertexArray * g_pQuadVAO = NULL;
static Bit::Shader * g_pVertexShader = NULL;
static Bit::Shader * g_pFragmentShader = NULL;
static Bit::ShaderProgram * g_pShaderProgram = NULL;
static Bit::Model * g_pModel = NULL;
static Bit::ModelRenderer * g_pModelRenderer = NULL;
static Bit::Vector2u32 g_WindowSize( 800, 600 );
static Bit::Matrix4x4f32 g_PerspectiveMatrix;
static Bit::Matrix4x4f32 g_OrthographicMatrix;
static Bit::Uint32 g_AnisotropicLevel = 0;
static Bit::Float32 g_Rotation = 0.0f;
static Bit::Float32 g_RotationSpeed = 0.3f;

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

	if( Load( ) == false )
	{
		Unload( );
		return;
	}

	// Start a timer
	Bit::Timer timer;
	timer.Start( );
	Bit::Float64 rotation = 0.0f;

	// Run the game loop
	while( g_Window.IsOpen( ) )
	{
		// Calculate the rotation
		Bit::Float32 time = static_cast<Bit::Float32>( timer.GetLapsedTime( ).AsSeconds( ) );
		g_Rotation = 45.0f + ( ( Bit::Math::Sin<Bit::Float32>( time * g_RotationSpeed ) ) * 45.0f );

		// Update the window
		g_Window.Update( );

		// Poll the events
		Bit::Event e;
		while( g_Window.PollEvent( e ) )
		{
			if( HandleEvent( e ) == false )
			{
			}
		}

		// Render
		Render( );
	}

	// Delete and close everything
	Unload( );

	// Print the finish text
	std::cout << "Finished OpenGL Graphic Device Test." << std::endl;
	std::cout << "-------------------------------------------" << std::endl;

}


Bit::Bool OpenGLGraphicDeviceTest::Load( )
{
	// Create the window
	const Bit::VideoMode videoMode( g_WindowSize, 24 );
	TestAssert( g_Window.Open( videoMode, "title" ) == true );
	TestAssert( g_Window.IsOpen( ) == true );

	// Create the graphic device
	g_pGraphicDevice = new Bit::OpenGLGraphicDevice( g_Window );
	TestAssert( g_pGraphicDevice->IsOpen( ) == true );
	g_pGraphicDevice->EnableDepthTest( );
	g_pGraphicDevice->EnableMultisampling( );
	g_pGraphicDevice->EnableFaceCulling( Bit::GraphicDevice::BackFace );

	std::cout << "Context version: " << g_pGraphicDevice->GetVersion( ).GetMajor( ) << "." << g_pGraphicDevice->GetVersion( ).GetMinor( ) << std::endl;

	// Set the clear color
	g_pGraphicDevice->SetClearColor( 16, 26, 37, 255 );


	// Create the framebuffer
	TestAssert( ( g_pFramebuffer = g_pGraphicDevice->CreateFramebuffer( ) ) != NULL );
	if( g_pFramebuffer == NULL )
	{
		Unload( );
		return false;
	}

	// Create color and depth renderbuffers.
	// Create the framebuffer
	TestAssert( ( g_pColorRenderbuffer = g_pGraphicDevice->CreateRenderbuffer( ) ) != NULL );
	if( g_pColorRenderbuffer == NULL )
	{
		Unload( );
		return false;
	}
	TestAssert( ( g_pDepthRenderbuffer = g_pGraphicDevice->CreateRenderbuffer( ) ) != NULL );
	if( g_pDepthRenderbuffer == NULL )
	{
		Unload( );
		return false;
	}
	g_pColorRenderbuffer->Load( g_WindowSize, Bit::Texture::Rgb, 8 );
	g_pDepthRenderbuffer->Load( g_WindowSize, Bit::Texture::DepthStencil, 8 );
	g_pFramebuffer->Attach( *g_pColorRenderbuffer );
	g_pFramebuffer->Attach( *g_pDepthRenderbuffer );




	// Create a floorVBO for the positions
	TestAssert( ( g_pFloorVboPositions = g_pGraphicDevice->CreateVertexBuffer( ) ) != NULL );
	if( g_pFloorVboPositions == NULL )
	{
		Unload( );
		return false;
	}

	const Bit::Float32 shapeSize = 100;
	Bit::Float32 pFloorPositionData[ ] =
	{
		-0.5f * shapeSize, 0.0f, -0.5f * shapeSize,
		-0.5f * shapeSize, 0.0f, 0.5f * shapeSize,
		0.5f * shapeSize, 0.0f, 0.5f * shapeSize,

		-0.5f * shapeSize, 0.0f, -0.5f * shapeSize,
		0.5f * shapeSize, 0.0f, 0.5f* shapeSize,
		0.5f * shapeSize, 0.0f, -0.5f * shapeSize
	};
	TestAssert( g_pFloorVboPositions->Load( 72, pFloorPositionData ) == true );

	// Create a floor VBO for the texture coords
	TestAssert( ( g_pFloorVboTextureCoords = g_pGraphicDevice->CreateVertexBuffer( ) ) != NULL );
	if( g_pFloorVboTextureCoords == NULL )
	{
		Unload( );
		return false;
	}
	Bit::Float32 pFloorTextureCoordData[ ] =
	{
		0.0f, 0.0f,
		1.0f * shapeSize, 0.0f,
		1.0f * shapeSize, 1.0f * shapeSize,

		0.0f, 0.0f,
		1.0f * shapeSize, 1.0f * shapeSize,
		0.0f, 1.0f * shapeSize
	};
	TestAssert( g_pFloorVboTextureCoords->Load( 48, pFloorTextureCoordData ) == true );

	// Create a floor VAO and add the VBO
	TestAssert( ( g_pFloorVAO = g_pGraphicDevice->CreateVertexArray( ) ) != NULL );
	TestAssert( g_pFloorVAO->AddVertexBuffer( *g_pFloorVboPositions, 3, Bit::DataType::Float32 ) == true );
	TestAssert( g_pFloorVAO->AddVertexBuffer( *g_pFloorVboTextureCoords, 2, Bit::DataType::Float32 ) == true );





	// Create a floorVBO for the positions
	TestAssert( ( g_pQuadVboPositions = g_pGraphicDevice->CreateVertexBuffer( ) ) != NULL );
	if( g_pFloorVboPositions == NULL )
	{
		Unload( );
		return false;
	}

	Bit::Float32 pQuadPositionData[ ] =
	{
		0.0f, 0.0f, 0.0f,
		100.0f, 0.0f, 0.0f,
		100.0f, 100.0f, 0.0f,

		0.0f, 0.0f, 0.0f,
		100.0f, 100.0f, 0.0f,
		0.0f, 100.0f, 0.0f
	};
	TestAssert( g_pQuadVboPositions->Load( 72, pQuadPositionData ) == true );

	// Create a floor VBO for the texture coords
	TestAssert( ( g_pQuadVboTextureCoords = g_pGraphicDevice->CreateVertexBuffer( ) ) != NULL );
	if( g_pQuadVboTextureCoords == NULL )
	{
		Unload( );
		return false;
	}
	Bit::Float32 pQuadTextureCoordData[ ] =
	{
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,

		0.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f
	};
	TestAssert( g_pQuadVboTextureCoords->Load( 48, pQuadTextureCoordData ) == true );

	// Create a floor VAO and add the VBO
	TestAssert( ( g_pQuadVAO = g_pGraphicDevice->CreateVertexArray( ) ) != NULL );
	TestAssert( g_pQuadVAO->AddVertexBuffer( *g_pQuadVboPositions, 3, Bit::DataType::Float32 ) == true );
	TestAssert( g_pQuadVAO->AddVertexBuffer( *g_pQuadVboTextureCoords, 2, Bit::DataType::Float32 ) == true );




	// Create a vertex shader and compile it
	TestAssert( ( g_pVertexShader = g_pGraphicDevice->CreateShader( Bit::ShaderType::Vertex ) ) != NULL );
	TestAssert( g_pVertexShader->CompileFromFile( "input/shader.vert" ) == true );

	// Create a fragment shader and compile it
	TestAssert( ( g_pFragmentShader = g_pGraphicDevice->CreateShader( Bit::ShaderType::Fragment ) ) != NULL );
	TestAssert( g_pFragmentShader->CompileFromFile( "input/shader.frag" ) == true );

	// Create a shader program, attach shader and link the program
	TestAssert( ( g_pShaderProgram = g_pGraphicDevice->CreateShaderProgram( ) ) != NULL );
	TestAssert( g_pShaderProgram->AttachShader( *g_pVertexShader ) == true );
	TestAssert( g_pShaderProgram->AttachShader( *g_pFragmentShader ) == true );
	g_pShaderProgram->SetAttributeLocation( "position", 0 );
	g_pShaderProgram->SetAttributeLocation( "texture", 1 );
	TestAssert( g_pShaderProgram->Link( ) == true );

	// Set the projection matrix
	g_PerspectiveMatrix.Perspective( 45.0f, (Bit::Float32)g_WindowSize.x / (Bit::Float32)g_WindowSize.y, 0.01f, 40.0f );
	g_OrthographicMatrix.Orthographic( 0.0f, (Bit::Float32)g_WindowSize.x, 0.0f, (Bit::Float32)g_WindowSize.y, -1.0f, 1.0f );
	g_pShaderProgram->Bind( );
	g_pShaderProgram->SetUniform1i( "colorTexture", 0 );
	g_pShaderProgram->Unbind( );

	// Initialize the matrix manager.
	Bit::MatrixManager::SetCurrentStack( Bit::MatrixManager::Projection );
	Bit::MatrixManager::SetMatrix( g_PerspectiveMatrix );
	Bit::MatrixManager::SetCurrentStack( Bit::MatrixManager::ModelView );
	Bit::MatrixManager::LoadIdentity( );

	// Create the floor texture
	TestAssert( ( g_pFloorTexture = g_pGraphicDevice->CreateTexture( ) ) != NULL );
	if( g_pFloorTexture == NULL )
	{
		Unload( );
		return false;
	}

	// Load the texture
	TestAssert( g_pFloorTexture->LoadFromFile( "input/grid.png", true ) == true );

	// Create the quad texture
	TestAssert( ( g_pQuadTexture = g_pGraphicDevice->CreateTexture( ) ) != NULL );
	if( g_pQuadTexture == NULL )
	{
		Unload( );
		return false;
	}
	static const Bit::Uint8 quadImageData[ 9 * 4 ] =
	{
		255, 50, 0, 255,		0, 255, 0, 255,			0, 0, 255, 255,
		255, 255, 255, 225,		0, 0, 0, 255,			255, 0, 255, 255,
		0, 255, 255, 255,		255, 127, 0, 255,		127, 127, 127, 255
	};
	TestAssert( g_pQuadTexture->LoadFromMemory( quadImageData, Bit::Vector2u32( 3, 3 ) ) == true );
	g_pQuadTexture->SetWrapping( Bit::Texture::Clamp, Bit::Texture::Clamp );


	// Create and load a model
	TestAssert( ( g_pModel = g_pGraphicDevice->CreateModel( ) ) != NULL );
	if( g_pModel == NULL )
	{
		Unload( );
		return false;
	}
	TestAssert( g_pModel->LoadFromFile( "input/objModel.obj" ) != false );

	// Create and load the model renderer.
	g_pModelRenderer = g_pGraphicDevice->CreateModelRenderer( );
	//g_pModelRenderer->Load( *g_pGraphicDevice );

	return true;
}

void OpenGLGraphicDeviceTest::Unload( )
{
	if( g_pModelRenderer )
	{
		delete g_pModelRenderer;
		g_pModelRenderer = NULL;
	}
	if( g_pModel )
	{
		delete g_pModel;
		g_pModel = NULL;
	}
	if( g_pFloorVboPositions )
	{
		delete g_pFloorVboPositions;
		g_pFloorVboPositions = NULL;
	}
	if( g_pFloorVboTextureCoords )
	{
		delete g_pFloorVboTextureCoords;
		g_pFloorVboTextureCoords = NULL;
	}
	if( g_pFloorVAO )
	{
		delete g_pFloorVAO;
		g_pFloorVAO = NULL;
	}
	if( g_pQuadVboPositions )
	{
		delete g_pQuadVboPositions;
		g_pQuadVboPositions = NULL;
	}
	if( g_pQuadVboTextureCoords )
	{
		delete g_pQuadVboTextureCoords;
		g_pQuadVboTextureCoords = NULL;
	}
	if( g_pQuadVAO )
	{
		delete g_pQuadVAO;
		g_pQuadVAO = NULL;
	}
	if( g_pVertexShader )
	{
		delete g_pVertexShader;
		g_pVertexShader = NULL;
	}
	if( g_pFragmentShader )
	{
		delete g_pFragmentShader;
		g_pFragmentShader = NULL;
	}
	if( g_pShaderProgram )
	{
		delete g_pShaderProgram;
		g_pShaderProgram = NULL;
	}
	if( g_pFloorTexture )
	{
		delete g_pFloorTexture;
		g_pFloorTexture = NULL;
	}
	if( g_pQuadTexture )
	{
		delete g_pQuadTexture;
		g_pQuadTexture = NULL;
	}
	if( g_pColorRenderbuffer )
	{
		delete g_pColorRenderbuffer;
		g_pColorRenderbuffer = NULL;
	}
	if( g_pDepthRenderbuffer )
	{
		delete g_pDepthRenderbuffer;
		g_pDepthRenderbuffer = NULL;
	}
	if( g_pFramebuffer )
	{
		delete g_pFramebuffer;
		g_pFramebuffer = NULL;
	}
	if( g_pGraphicDevice )
	{
		delete g_pGraphicDevice;
		g_pGraphicDevice = NULL;
	}

	g_Window.Close( );
}

void OpenGLGraphicDeviceTest::Render( )
{
	// Update the view matrix(rotate the primitive)
	Bit::Matrix4x4f32 viewMatrix;

	// Bind the framebuffer
	g_pFramebuffer->Bind( );

	// Clear the color
	g_pGraphicDevice->ClearColor( );
	g_pGraphicDevice->ClearDepth( );


	// Render the quad
	viewMatrix.Identity( );
	viewMatrix.Translate( 100.0f, 500.0f, 0.0f );
	viewMatrix.RotateZ( static_cast<Bit::Float32>( g_Rotation * 2.0f ) );
	viewMatrix.Translate( -50.0f, -50.0f, 0.0f );
	g_pShaderProgram->Bind( );
	g_pShaderProgram->SetUniformMatrix4x4f( "projectionMatrix", g_OrthographicMatrix );
	g_pShaderProgram->SetUniformMatrix4x4f( "viewMatrix", viewMatrix );

	g_pQuadTexture->Bind( );
	g_pQuadVAO->Render( Bit::PrimitiveMode::Triangles );
	g_pQuadTexture->Unbind( );
	g_pShaderProgram->Unbind( );


	// Render the model
	Bit::MatrixManager::Push( );
	Bit::MatrixManager::LoadIdentity( );
	Bit::MatrixManager::Translate( 0.0f, 0.0f, -1.0f );
	Bit::MatrixManager::Scale( 0.18f, 0.18f, 0.18f );
	Bit::MatrixManager::RotateY( g_Rotation * 4.0f );
	g_pFloorTexture->Bind( );
	g_pModelRenderer->Render( *g_pModel );
	Bit::MatrixManager::Pop( );

	/*
	// Render the floor
	viewMatrix.LookAt(	Bit::Vector3f32( 0.0f, 0.1f, 0.5f ),
						Bit::Vector3f32( 0.0f, 0.0f, 0.0f ),
						Bit::Vector3f32( 0.0f, 1.0f, 0.0f ) );
	viewMatrix.RotateY( g_Rotation );

	g_pShaderProgram->Bind( );
	g_pShaderProgram->SetUniformMatrix4x4f( "projectionMatrix", g_PerspectiveMatrix );
	g_pShaderProgram->SetUniformMatrix4x4f( "viewMatrix", viewMatrix );

	g_pFloorTexture->Bind( );
	g_pFloorVAO->Render( Bit::PrimitiveMode::Triangles );
	g_pFloorTexture->Unbind( );
	g_pShaderProgram->Unbind( );
	*/


	// Unbind the framebuffer
	g_pFramebuffer->Unbind( );

	g_pFramebuffer->Blit(	g_pGraphicDevice->GetDefaultFramebuffer( ),
							Bit::Vector2u32( 50, 50 ),
							Bit::Vector2u32( 750, 550 ),
							Bit::Vector2u32( 50, 50 ),
							Bit::Vector2u32( 750, 550 ) );

	// Swap the buffers
	g_pGraphicDevice->Present( );


}

Bit::Bool OpenGLGraphicDeviceTest::HandleEvent( const Bit::Event & p_Event )
{
	switch( p_Event.Type )
	{
		case Bit::Event::Closed:
		{
			g_Window.Close( );
		}
		break;
		case Bit::Event::KeyJustPressed:
		{
			switch( p_Event.Key )
			{
				case Bit::Keyboard::Escape:
				{
					g_Window.Close( );
				}
				break;
				case Bit::Keyboard::Up:
				{
					if( g_AnisotropicLevel < 16 )
					{
						g_AnisotropicLevel += 1;
					}
					g_pFloorTexture->SetAnisotropic( g_AnisotropicLevel );
				}
				break;
				case Bit::Keyboard::Down:
				{
					if( g_AnisotropicLevel > 0 )
					{
						g_AnisotropicLevel -= 1;
					}
					g_pFloorTexture->SetAnisotropic( g_AnisotropicLevel );
				}
				break;
				case Bit::Keyboard::Num1:
				{
					g_pFloorTexture->SetMagnificationFilter( Bit::Texture::Nearest );
				}
				break;
				case Bit::Keyboard::Num2:
				{
					g_pFloorTexture->SetMagnificationFilter( Bit::Texture::Linear );
				}
				break;
				case Bit::Keyboard::Num3:
				{
					g_pFloorTexture->SetMinificationFilter( Bit::Texture::Linear );
				}
				break;
				case Bit::Keyboard::Num4:
				{
					g_pFloorTexture->SetMinificationFilter( Bit::Texture::LinearMipmapNearest );
				}
				break;
				case Bit::Keyboard::Num5:
				{
					g_pFloorTexture->SetMinificationFilter( Bit::Texture::LinearMipmapLinear );
				}
				break;
				case Bit::Keyboard::Num6:
				{
					g_pFloorTexture->SetMinificationFilter( Bit::Texture::Nearest );
				}
				break;
				case Bit::Keyboard::Num7:
				{
					g_pFloorTexture->SetMinificationFilter( Bit::Texture::NearestMipmapNearest );
				}
				break;
				case Bit::Keyboard::Num8:
				{
					g_pFloorTexture->SetMinificationFilter( Bit::Texture::NearestMipmapLinear );
				}
				break;
				case Bit::Keyboard::Plus:
				{
					g_RotationSpeed += 0.1f;
				}
				break;
				case Bit::Keyboard::Minus:
				{
					g_RotationSpeed -= 0.1f;
				}
				break;
			default:
				break;
			}

		}
		break;
	}

	return true;
}
