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

#ifndef BIT_MY_MODEL_RENDERER_HPP
#define BIT_MY_MODEL_RENDERER_HPP

#include <Bit/Build.hpp>
#include <Bit/Graphics/ModelRenderer.hpp>
#include <Bit/Graphics/Model.hpp>
#include <Bit/Graphics/VertexArray.hpp>
#include <Bit/Graphics/GraphicDevice.hpp>
#include <Bit/System/MatrixManager.hpp>

class MyModelRenderer : public Bit::ModelRenderer
{

public:

	// Constructor
	MyModelRenderer( )
	{
	}

	~MyModelRenderer( )
	{
		Unload( );
	}

	////////////////////////////////////////////////////////////////
	/// \brief Load model renderer.
	///
	////////////////////////////////////////////////////////////////
	virtual Bit::Bool Load( const Bit::GraphicDevice & p_GraphicDevice )
	{
		m_pVertexShader = p_GraphicDevice.CreateShader( Bit::ShaderType::Vertex );
		m_pFragmentShader = p_GraphicDevice.CreateShader( Bit::ShaderType::Fragment );
		m_pShaderProgram = p_GraphicDevice.CreateShaderProgram( );

		static const std::string vertexSource = 
			"#version 330\n"

			"uniform mat4 projectionMatrix;\n"
			"uniform mat4 modelViewMatrix;\n"

			"in vec3 position;\n"

			"void main( )\n"
			"{\n"
			"	gl_Position = projectionMatrix * modelViewMatrix * vec4( position, 1.0 );\n"
			"}\n";
		m_pVertexShader->CompileFromMemory( vertexSource );

		static const std::string fragmentSource = 
			"#version 330\n"

			"out vec4 color;\n"

			"void main( )\n"
			"{ \n"
			"	color = vec4( 1.0, 0.0, 0.0, 1.0 );\n"
			"}\n";
		m_pFragmentShader->CompileFromMemory( fragmentSource );

		m_pShaderProgram->AttachShader( *m_pVertexShader );
		m_pShaderProgram->AttachShader( *m_pFragmentShader );
		m_pShaderProgram->SetAttributeLocation( "position", 0 );
		m_pShaderProgram->Link( );

		return true;
	}

	////////////////////////////////////////////////////////////////
	/// \brief Unload model renderer.
	///
	////////////////////////////////////////////////////////////////
	virtual void Unload( )
	{
		if( m_pFragmentShader )
		{
			delete m_pFragmentShader;
		}
		if( m_pVertexShader )
		{
			delete m_pVertexShader;
		}
		if( m_pShaderProgram )
		{
			delete m_pShaderProgram;
		}
	}

	////////////////////////////////////////////////////////////////
	/// \brief Function for rendering a model.
	///
	////////////////////////////////////////////////////////////////
	virtual void Render( Bit::Model & p_Model )
	{
		// Error check the vertex data.
		if( p_Model.GetVertexData( ).GetVertexArray( ) == NULL )
		{
			return;
		}

		m_pShaderProgram->Bind( );
		m_pShaderProgram->SetUniformMatrix4x4f( "projectionMatrix", Bit::MatrixManager::GetProjectionMatrix( ) );
		m_pShaderProgram->SetUniformMatrix4x4f( "modelViewMatrix", Bit::MatrixManager::GetModelViewMatrix( ) );

		// Render the model.
		p_Model.GetVertexData( ).GetVertexArray( )->Render( Bit::PrimitiveMode::Triangles );

		m_pShaderProgram->Unbind( );
	}

private:

	Bit::ShaderProgram * m_pShaderProgram;
	Bit::Shader * m_pVertexShader;
	Bit::Shader * m_pFragmentShader;


};

#endif