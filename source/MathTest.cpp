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

#include <MathTest.hpp>
#include <Bit/System/Math.hpp>

// Constructor
MathTest::MathTest( ) :
	Test( )
{
}

// Virtual functions
void MathTest::Run( std::ostream & p_Trace )
{
	std::cout << "-------------------------------------------" << std::endl;
	std::cout << "Starting Math test." << std::endl;

	// Assert DegreesToRadians function
	TestAssert( Bit::Math::EqualEpsilon<Bit::Float64>( Bit::Math::DegreesToRadians<Bit::Float64>( 90.0f ), Bit::Pi * 0.5f) );
	TestAssert( Bit::Math::EqualEpsilon<Bit::Float64>( Bit::Math::DegreesToRadians<Bit::Float64>( 180.0f ), Bit::Pi ) );
	TestAssert( Bit::Math::EqualEpsilon<Bit::Float64>( Bit::Math::DegreesToRadians<Bit::Float64>( 270.0f ), Bit::Pi * 1.5f ) );
	TestAssert( Bit::Math::EqualEpsilon<Bit::Float64>( Bit::Math::DegreesToRadians<Bit::Float64>( 360.0f ), Bit::Pi * 2.0f ) );

	// Assert RadiansToDegrees function
	TestAssert( Bit::Math::EqualEpsilon<Bit::Float64>( Bit::Math::RadiansToDegrees<Bit::Float64>( Bit::Pi * 0.5f ), 90.0f ) );
	TestAssert( Bit::Math::EqualEpsilon<Bit::Float64>( Bit::Math::RadiansToDegrees<Bit::Float64>( Bit::Pi ),		180.0f ) );
	TestAssert( Bit::Math::EqualEpsilon<Bit::Float64>( Bit::Math::RadiansToDegrees<Bit::Float64>( Bit::Pi * 1.5f ), 270.0f ) );
	TestAssert( Bit::Math::EqualEpsilon<Bit::Float64>( Bit::Math::RadiansToDegrees<Bit::Float64>( Bit::Pi * 2.0f ), 360.0f ) );

	// Assert Sin function
	TestAssert( Bit::Math::EqualEpsilon<Bit::Float64>( Bit::Math::Sin<Bit::Float64>( 0 ),				0.0f ) );
	TestAssert( Bit::Math::EqualEpsilon<Bit::Float64>( Bit::Math::Sin<Bit::Float64>( Bit::Pi * 0.5 ),	1.0f ) );
	TestAssert( Bit::Math::EqualEpsilon<Bit::Float64>( Bit::Math::Sin<Bit::Float64>( Bit::Pi ),			0.0f ) );
	TestAssert( Bit::Math::EqualEpsilon<Bit::Float64>( Bit::Math::Sin<Bit::Float64>( Bit::Pi * 1.5f ),	-1.0f ) );
	TestAssert( Bit::Math::EqualEpsilon<Bit::Float64>( Bit::Math::Sin<Bit::Float64>( Bit::Pi * 2.0f ),	0.0f ) );

	// Assert Cos function
	TestAssert( Bit::Math::EqualEpsilon<Bit::Float64>( Bit::Math::Cos<Bit::Float64>( 0 ),				1.0f ) );
	TestAssert( Bit::Math::EqualEpsilon<Bit::Float64>( Bit::Math::Cos<Bit::Float64>( Bit::Pi * 0.5 ),	0.0f ) );
	TestAssert( Bit::Math::EqualEpsilon<Bit::Float64>( Bit::Math::Cos<Bit::Float64>( Bit::Pi ),			-1.0f ) );
	TestAssert( Bit::Math::EqualEpsilon<Bit::Float64>( Bit::Math::Cos<Bit::Float64>( Bit::Pi * 1.5f ),	0.0f ) );
	TestAssert( Bit::Math::EqualEpsilon<Bit::Float64>( Bit::Math::Cos<Bit::Float64>( Bit::Pi * 2.0f ),	1.0f ) );

	// Assert the Tan function
	// ...

	// Assert RowToColumnIndex function
	TestAssert( Bit::Math::RowToColumnIndex( 0, 4, 4 ) == 0 );
	TestAssert( Bit::Math::RowToColumnIndex( 1, 4, 4 ) == 4 );
	TestAssert( Bit::Math::RowToColumnIndex( 2, 4, 4 ) == 8 );
	TestAssert( Bit::Math::RowToColumnIndex( 3, 4, 4 ) == 12 );

	TestAssert( Bit::Math::RowToColumnIndex( 4, 4, 4 ) == 1 );
	TestAssert( Bit::Math::RowToColumnIndex( 5, 4, 4 ) == 5 );
	TestAssert( Bit::Math::RowToColumnIndex( 6, 4, 4 ) == 9 );
	TestAssert( Bit::Math::RowToColumnIndex( 7, 4, 4 ) == 13 );

	TestAssert( Bit::Math::RowToColumnIndex( 8, 4, 4 ) == 2 );
	TestAssert( Bit::Math::RowToColumnIndex( 9, 4, 4 ) == 6 );
	TestAssert( Bit::Math::RowToColumnIndex( 10, 4, 4 ) == 10 );
	TestAssert( Bit::Math::RowToColumnIndex( 11, 4, 4 ) == 14 );

	TestAssert( Bit::Math::RowToColumnIndex( 12, 4, 4 ) == 3 );
	TestAssert( Bit::Math::RowToColumnIndex( 13, 4, 4 ) == 7 );
	TestAssert( Bit::Math::RowToColumnIndex( 14, 4, 4 ) == 11 );
	TestAssert( Bit::Math::RowToColumnIndex( 15, 4, 4 ) == 15 );

	// Print the finish text
	std::cout << "Finished Math Test." << std::endl;
	std::cout << "-------------------------------------------" << std::endl;
	
}