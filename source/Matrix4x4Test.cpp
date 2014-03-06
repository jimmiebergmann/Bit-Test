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

#include <Matrix4x4Test.hpp>
//#include <Bit/System/Math.hpp>
#include <Bit/System/Matrix4x4.hpp>

// Constructor
Matrix4x4Test::Matrix4x4Test( ) :
	Test( )
{
}

// Virtual functions
void Matrix4x4Test::Run( std::ostream & p_Trace )
{
	std::cout << "-------------------------------------------" << std::endl;
	std::cout << "Starting Matrix4x4 test." << std::endl;

	// Assert the constructors
	Bit::Matrix4x4f32 matConst1( 0.0f );
	for( Bit::SizeType i = 0; i < 16; i++ )
	{
		TestAssert( matConst1.m[ i ] == 0.0f );
	}

	Bit::Matrix4x4<Bit::UInt32> matConst2(	0, 1, 2, 3,
											4, 5, 6, 7,
											8, 9, 10, 11,
											12, 13, 14, 15 );
	for( Bit::SizeType i = 0; i < 16; i++ )
	{
		TestAssert( matConst2.m[ Bit::Math::RowToColumnIndex<Bit::SizeType>( i, 4, 4 ) ] == i );
	}

	// Assert the Identity function
	Bit::Matrix4x4<Bit::UInt32> matIdent;
	matIdent.Identity( );
	TestAssert( matIdent.m[ 0 ] == 1 );
	TestAssert( matIdent.m[ 1 ] == 0 );
	TestAssert( matIdent.m[ 2 ] == 0 );
	TestAssert( matIdent.m[ 3 ] == 0 );
	TestAssert( matIdent.m[ 4 ] == 0 );
	TestAssert( matIdent.m[ 5 ] == 1 );
	TestAssert( matIdent.m[ 6 ] == 0 );
	TestAssert( matIdent.m[ 7 ] == 0 );
	TestAssert( matIdent.m[ 8 ] == 0 );
	TestAssert( matIdent.m[ 9 ] == 0 );
	TestAssert( matIdent.m[ 10 ] == 1 );
	TestAssert( matIdent.m[ 11 ] == 0 );
	TestAssert( matIdent.m[ 12 ] == 0 );
	TestAssert( matIdent.m[ 13 ] == 0 );
	TestAssert( matIdent.m[ 14 ] == 0 );
	TestAssert( matIdent.m[ 15 ] == 1 );

	// Assert the Position function
	Bit::Matrix4x4<Bit::UInt32> matPos;
	matPos.Position( Bit::Vector3u32( 11, 12, 13 ) );
	TestAssert( matPos.m[ 0 ] == 1 );
	TestAssert( matPos.m[ 1 ] == 0 );
	TestAssert( matPos.m[ 2 ] == 0 );
	TestAssert( matPos.m[ 3 ] == 0 );
	TestAssert( matPos.m[ 4 ] == 0 );
	TestAssert( matPos.m[ 5 ] == 1 );
	TestAssert( matPos.m[ 6 ] == 0 );
	TestAssert( matPos.m[ 7 ] == 0 );
	TestAssert( matPos.m[ 8 ] == 0 );
	TestAssert( matPos.m[ 9 ] == 0 );
	TestAssert( matPos.m[ 10 ] == 1 );
	TestAssert( matPos.m[ 11 ] == 0 );
	TestAssert( matPos.m[ 12 ] == 11 );
	TestAssert( matPos.m[ 13 ] == 12 );
	TestAssert( matPos.m[ 14 ] == 13 );
	TestAssert( matPos.m[ 15 ] == 1 );

	// Assert the Translate function
	Bit::Matrix4x4<Bit::UInt32> matTrans;
	matTrans.Identity( );
	matTrans.Translate( 3, 4, 5 );
	TestAssert( matTrans.m[ 0 ] == 1 );
	TestAssert( matTrans.m[ 1 ] == 0 );
	TestAssert( matTrans.m[ 2 ] == 0 );
	TestAssert( matTrans.m[ 3 ] == 0 );
	TestAssert( matTrans.m[ 4 ] == 0 );
	TestAssert( matTrans.m[ 5 ] == 1 );
	TestAssert( matTrans.m[ 6 ] == 0 );
	TestAssert( matTrans.m[ 7 ] == 0 );
	TestAssert( matTrans.m[ 8 ] == 0 );
	TestAssert( matTrans.m[ 9 ] == 0 );
	TestAssert( matTrans.m[ 10 ] == 1 );
	TestAssert( matIdent.m[ 11 ] == 0 );
	TestAssert( matTrans.m[ 12 ] == 3 );
	TestAssert( matTrans.m[ 13 ] == 4 );
	TestAssert( matTrans.m[ 14 ] == 5 );
	TestAssert( matTrans.m[ 15 ] == 1 );

	// Assert the Scale function
	Bit::Matrix4x4<Bit::UInt32> matScale;
	matScale.Identity( );
	matScale.Scale( 3, 4, 5 );
	TestAssert( matScale.m[ 0 ] == 3 );
	TestAssert( matScale.m[ 1 ] == 0 );
	TestAssert( matScale.m[ 2 ] == 0 );
	TestAssert( matScale.m[ 3 ] == 0 );
	TestAssert( matScale.m[ 4 ] == 0 );
	TestAssert( matScale.m[ 5 ] == 4 );
	TestAssert( matScale.m[ 6 ] == 0 );
	TestAssert( matScale.m[ 7 ] == 0 );
	TestAssert( matScale.m[ 8 ] == 0 );
	TestAssert( matScale.m[ 9 ] == 0 );
	TestAssert( matScale.m[ 10 ] == 5 );
	TestAssert( matScale.m[ 11 ] == 0 );
	TestAssert( matScale.m[ 12 ] == 0 );
	TestAssert( matScale.m[ 13 ] == 0 );
	TestAssert( matScale.m[ 14 ] == 0 );
	TestAssert( matScale.m[ 15 ] == 1 );

	// Print the finish text
	std::cout << "Finished Matrix4x4 Test." << std::endl;
	std::cout << "-------------------------------------------" << std::endl;
	
}