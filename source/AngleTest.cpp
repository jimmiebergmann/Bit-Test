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

#include <AngleTest.hpp>
#include <Bit/System/Math.hpp>
#include <Bit/System/Angle.hpp>
#include <Bit/System/MemoryLeak.hpp>

// Constructor
AngleTest::AngleTest( ) :
	Test( )
{
}

// Virtual functions
void AngleTest::Run( std::ostream & p_Trace )
{
	std::cout << "-------------------------------------------" << std::endl;
	std::cout << "Starting Angle test." << std::endl;

	// Create some angles
	Bit::Angle<Bit::Float64> angle1( Bit::Pi * 0.5f );
	Bit::Angle<Bit::Float64> angle2( Bit::Pi );
	Bit::Angle<Bit::Float64> angle3( Bit::Pi * 1.5f );
	Bit::Angle<Bit::Float64> angle4( Bit::Pi * 2.0f );

	// Asssert the ( ) operator (radians)
	TestAssert( Bit::Math::EqualEpsilon<Bit::Float64>( angle1( ), Bit::Pi * 0.5f ) );
	TestAssert( Bit::Math::EqualEpsilon<Bit::Float64>( angle2( ), Bit::Pi ) );
	TestAssert( Bit::Math::EqualEpsilon<Bit::Float64>( angle3( ), Bit::Pi * 1.5f ) );
	TestAssert( Bit::Math::EqualEpsilon<Bit::Float64>( angle4( ), Bit::Pi * 2.0f) );

	// Asssert the AsRadians function
	TestAssert( Bit::Math::EqualEpsilon<Bit::Float64>( angle1.AsRadians( ), Bit::Pi * 0.5f ) );
	TestAssert( Bit::Math::EqualEpsilon<Bit::Float64>( angle2.AsRadians( ), Bit::Pi ) );
	TestAssert( Bit::Math::EqualEpsilon<Bit::Float64>( angle3.AsRadians( ), Bit::Pi * 1.5f ) );
	TestAssert( Bit::Math::EqualEpsilon<Bit::Float64>( angle4.AsRadians( ), Bit::Pi * 2.0f) );

	// Asssert the AsDegrees function
	TestAssert( Bit::Math::EqualEpsilon<Bit::Float64>( angle1.AsDegrees( ), 90.0f ) );
	TestAssert( Bit::Math::EqualEpsilon<Bit::Float64>( angle2.AsDegrees( ), 180.0f ) );
	TestAssert( Bit::Math::EqualEpsilon<Bit::Float64>( angle3.AsDegrees( ), 270.0f ) );
	TestAssert( Bit::Math::EqualEpsilon<Bit::Float64>( angle4.AsDegrees( ), 360.0f ) );
	
	// Print the finish text
	std::cout << "Finished Angle Test." << std::endl;
	std::cout << "-------------------------------------------" << std::endl;
	
}