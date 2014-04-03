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

#include <KeyboardTest.hpp>
#include <Bit/System/MemoryLeak.hpp>
#include <Bit/System/Timer.hpp>
#include <Bit/System/Keyboard.hpp>

// Constructor
KeyboardTest::KeyboardTest( ) :
	Test( )
{
}

// Virtual functions
void KeyboardTest::Run( std::ostream & p_Trace )
{
	std::cout << "-------------------------------------------" << std::endl;
	std::cout << "Starting Keyboard test." << std::endl;

	// Assert the keyboard
	Bit::Keyboard keyboard;

	// Start the test
	Bit::Timer timer;
	timer.Start( );
	Bit::Bool running = true;
	while( timer.GetLapsedTime( ) < 10.0f && running == true )
	{
		keyboard.Update( );

		for( Bit::SizeType i = 0; i < Bit::Keyboard::KeyCount; i++ )
		{
			Bit::Keyboard::eKey key = static_cast<Bit::Keyboard::eKey>( i );

			if( keyboard.KeyIsJustPressed( Bit::Keyboard::Escape ) )
			{
				std::cout << "Breaking test." << std::endl;
				running = false;
				break;
			}

			if( keyboard.KeyIsJustPressed( key ) )
			{
				std::cout << "Just pressed key: " << i << "(" << (char)keyboard.TranslateKeyToSystemKey( key ) << ")" << std::endl;
			}

			if( keyboard.KeyIsJustReleased( static_cast<Bit::Keyboard::eKey>( i ) ) )
			{
				std::cout << "Just released key: " << i << "(" << (char)keyboard.TranslateKeyToSystemKey( key ) << ")" << std::endl;
			}
		}
	}

	// Print the finish text
	std::cout << "Finished Keyboard Test." << std::endl;
	std::cout << "-------------------------------------------" << std::endl;
	
}