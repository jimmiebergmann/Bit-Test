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

#include <MatrixManagerTest.hpp>
#include <Bit/System/MatrixManager.hpp>
#include <Bit/System/MemoryLeak.hpp>

// Constructor
MatrixManagerTest::MatrixManagerTest( ) :
	Test( )
{
}

// Virtual functions
void MatrixManagerTest::Run( std::ostream & p_Trace )
{
	std::cout << "-------------------------------------------" << std::endl;
	std::cout << "Starting Matrix Manager test." << std::endl;

	// Check the stack index.
	TestAssert( Bit::MatrixManager::GetStackCount( ) == 2 );
	Bit::MatrixManager::SetCurrentStack( 0 );
	TestAssert( Bit::MatrixManager::GetCurrentStack( ) == 0 );
	Bit::MatrixManager::SetCurrentStack( 1 );
	TestAssert( Bit::MatrixManager::GetCurrentStack( ) == 1 );
	Bit::MatrixManager::SetCurrentStack( Bit::MatrixManager::ModelView );
	TestAssert( Bit::MatrixManager::GetCurrentStack( ) == 0 );
	Bit::MatrixManager::SetCurrentStack( Bit::MatrixManager::Projection );
	TestAssert( Bit::MatrixManager::GetCurrentStack( ) == 1 );

	// Set matrices
	Bit::Matrix4x4f32 mat1(	1.0f,	2.0f,	3.0f,	4.0f,
							5.0f,	6.0f,	7.0f,	8.0f,
							9.0f,	10.0f,	11.0f,	12.0f,
							13.0f,	14.0f,	15.0f,	16.0f );
	Bit::MatrixManager::SetCurrentStack( Bit::MatrixManager::Projection );
	Bit::MatrixManager::SetMatrix( mat1 );
	TestAssert( Bit::MatrixManager::GetMatrix( Bit::MatrixManager::Projection ) == mat1 );
	TestAssert( Bit::MatrixManager::GetMatrix( 1 ) == mat1 );
	TestAssert( Bit::MatrixManager::GetProjectionMatrix( ) == mat1 );

	// Print the finish text
	std::cout << "Finished Matrix Manager Test." << std::endl;
	std::cout << "-------------------------------------------" << std::endl;
	
}