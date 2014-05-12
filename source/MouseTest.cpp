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

#include <MouseTest.hpp>
#include <Bit/System/Mouse.hpp>
#include <Bit/System/Sleep.hpp>
#include <Bit/System/Timer.hpp>
#include <Windows.h>
#include <Bit/System/MemoryLeak.hpp>

// Constructor
MouseTest::MouseTest( ) :
	Test( )
{
}

// Virtual functions
void MouseTest::Run( std::ostream & p_Trace )
{
	std::cout << "-------------------------------------------" << std::endl;
	std::cout << "Starting Mouse test." << std::endl;

	// Create a mouse
	Bit::Mouse mouse;
	
	// Print the position 3 times with some delay
	for( Bit::SizeType i = 0; i < 3; i++ )
	{
		Bit::Vector2i32 position = mouse.GetPosition( );
		std::cout << "Position: " << position.x << "  " << position.y << std::endl;
		Bit::Sleep( Bit::Seconds( 1.0f ) );
	}
	
	// Mouse button test
	bool buttonPressed[ 3 ] = { false, false, false };
	Bit::Timer timer;
	
	// Run the button test for 3 seconds
	std::cout << "Press all mouse buttons:" << std::endl;
	timer.Start( );
	while(	timer.GetLapsedTime( ).AsSeconds( ) < 10.0f && !( buttonPressed[ 0 ] && buttonPressed[ 1 ] && buttonPressed[ 2 ] ) )
	{
		mouse.Update( );

		if( mouse.ButtonIsJustPressed( Bit::Mouse::Left  ) )
		{
			buttonPressed[ 0 ] = true;
			std::cout << "Just pressed left mouse button." << std::endl;
		}
		if( mouse.ButtonIsJustPressed( Bit::Mouse::Middle ) )
		{
			buttonPressed[ 1 ] = true;
			std::cout << "Just pressed middle mouse button." << std::endl;
		}
		if( mouse.ButtonIsJustPressed( Bit::Mouse::Right ) )
		{
			buttonPressed[ 2 ] = true;
			std::cout << "Just pressed right mouse button." << std::endl;
		}
	}

	// Assert the pressed buttons
	TestAssert( buttonPressed[ 0 ] );
	TestAssert( buttonPressed[ 1 ] );
	TestAssert( buttonPressed[ 2 ] );


	// Print the finish text
	std::cout << "Finished Mouse Test." << std::endl;
	std::cout << "-------------------------------------------" << std::endl;
	
}