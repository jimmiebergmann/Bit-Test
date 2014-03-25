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

#include <Vector2Test.hpp>
#include <Bit/System/Vector2.hpp>
#include <Bit/System/MemoryLeak.hpp>

// Constructor
Vector2Test::Vector2Test( ) :
	Test( )
{
}

// Virtual functions
void Vector2Test::Run( std::ostream & p_Trace )
{
	std::cout << "-------------------------------------------" << std::endl;
	std::cout << "Starting Vector2 test." << std::endl;

	// Run a constuctor test for the different types
	Bit::Vector2i8 veci8( 1, 2 );
	Bit::Vector2u8 vecu8( 1, 2 );
	Bit::Vector2i16 veci16( 1, 2 );
	Bit::Vector2u16 vecu16( 1, 2 );
	Bit::Vector2i32 veci32( 1, 2 );
	Bit::Vector2u32 vecu32( 1, 2 );
	Bit::Vector2i64 veci64( 1, 2 );
	Bit::Vector2u64 vecu64( 1, 2 );
	Bit::Vector2f32 vecf32( 1.0f, 2.0f );
	Bit::Vector2f64 vecf64( 1.0f, 2.0f );

	// Assert the vectors
	TestAssert( veci8.x == 1 && veci8.y == 2 );
	TestAssert( vecu8.x == 1 && vecu8.y == 2 );
	TestAssert( veci16.x == 1 && veci16.y == 2 );
	TestAssert( vecu16.x == 1 && vecu16.y == 2 );
	TestAssert( veci32.x == 1 && veci32.y == 2 );
	TestAssert( vecu32.x == 1 && vecu32.y == 2 );
	TestAssert( veci64.x == 1 && veci64.y == 2 );
	TestAssert( vecu64.x == 1 && vecu64.y == 2 );
	TestAssert( vecf32.x == 1.0f && vecf32.y == 2.0f );
	TestAssert( vecf64.x == 1.0f && vecf64.y == 2.0f );

	// Casting tests
	Bit::Vector2f64 vecCast1( vecf32 );
	Bit::Vector2f32 vecCast2( vecf64 );
	TestAssert( vecCast1.x == vecf32.x && vecCast1.y == vecf32.y);
	TestAssert( vecCast2.x == vecf64.x && vecCast2.y == vecf64.y);

	// Assert Magnitude function
	Bit::Vector2f32 vecLength( 100.0f, 0.0f );
	TestAssert( vecLength.Length( ) == 100.0f );

	// Assert normal function
	Bit::Vector2f32 vecNormal1 = Bit::Vector2f32( 123.0f, 0.0f ).Normal( );
	TestAssert( vecNormal1.x == 1.0f && vecNormal1.y == 0.0f );

	// Assert normalize function
	Bit::Vector2f32 vecNormal2( 123.0f, 0.0f );
	vecNormal2.Normalize( );
	TestAssert( vecNormal2.x == 1.0f && vecNormal2.y == 0.0f );
	
	// Assert dot product function
	TestAssert( Bit::Vector2f32( -1.0f, 0.0f ).Dot( Bit::Vector2f32( 1.0f, 0.0f ) ) == -1.0f );
	TestAssert( Bit::Vector2f32( 0.0f, 1.0f ).Dot( Bit::Vector2f32( 1.0f, 0.0f ) ) == 0.0f );
	TestAssert( Bit::Vector2f32( 1.0f, 0.0f ).Dot( Bit::Vector2f32( 1.0f, 0.0f ) ) == 1.0f );

	// Assert angle between vectors function
	Bit::Vector2f32 vecAngle1( -1.0f, 0.0f );
	Bit::Vector2f32 vecAngle2( 0.0f, 1.0f );
	TestAssert( Bit::Math::EqualEpsilonHalf<Bit::Float64>( Bit::Vector2f32::AngleBetweenVectors( vecAngle1, vecAngle2 ).AsDegrees( ), 90.0f ) );

	// Assert the absolute function
	Bit::Vector2f32 vecAbs1 = Bit::Vector2f32( -1.0f, -2.0f ).Absolute( );
	Bit::Vector2f32 vecAbs2 = Bit::Vector2f32( 1.0f, -2.0f ).Absolute( );
	Bit::Vector2f32 vecAbs3 = Bit::Vector2f32( -1.0f, 2.0f ).Absolute( );
	Bit::Vector2f32 vecAbs4 = Bit::Vector2f32( 1.0f, 2.0f ).Absolute( );
	TestAssert( vecAbs1.x == 1.0f && vecAbs1.y == 2.0f );
	TestAssert( vecAbs2.x == 1.0f && vecAbs2.y == 2.0f );
	TestAssert( vecAbs3.x == 1.0f && vecAbs3.y == 2.0f );
	TestAssert( vecAbs4.x == 1.0f && vecAbs4.y == 2.0f );

	// Assert the rotate function
	Bit::Vector2f32 vecRotate( 0.0f, 1.0f );
	vecRotate.Rotate( 90.0f );
	TestAssert( Bit::Math::EqualEpsilonHalf<Bit::Float64>( vecRotate.x, -1.0f ) &&
				Bit::Math::EqualEpsilonHalf<Bit::Float64>( vecRotate.y, 0.0f ) );
	
	
	// Print the finish text
	std::cout << "Finished Vector2 Test." << std::endl;
	std::cout << "-------------------------------------------" << std::endl;
}