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

#include <VideoModeTest.hpp>
#include <Bit/Window/VideoMode.hpp>
#include <Bit/System/MemoryLeak.hpp>

// Constructor
VideoModeTest::VideoModeTest( ) :
	Test( )
{
}

// Virtual functions
void VideoModeTest::Run( std::ostream & p_Trace )
{
	std::cout << "-------------------------------------------" << std::endl;
	std::cout << "Starting Video Mode test." << std::endl;

	// Assert the constructors
	Bit::VideoMode videoMode1;
	TestAssert( videoMode1.GetSize( ).x == 0 );
	TestAssert( videoMode1.GetSize( ).y == 0 );
	TestAssert( videoMode1.GetBitsPerPixel( ) == 0 );

	Bit::VideoMode videoMode2( Bit::Vector2u32( 123, 456 ), 24 );
	TestAssert( videoMode2.GetSize( ).x == 123 );
	TestAssert( videoMode2.GetSize( ).y == 456 );
	TestAssert( videoMode2.GetBitsPerPixel( ) == 24 );

	// Assert the set / get functions
	Bit::VideoMode videoMode3;
	videoMode3.SetSize( Bit::Vector2u32( 135, 790 ) );
	TestAssert( videoMode3.GetSize( ).x == 135 );
	TestAssert( videoMode3.GetSize( ).y == 790 );
	videoMode3.SetBitsPerPixel( 123 );
	TestAssert( videoMode3.GetBitsPerPixel( ) == 123 );

	// Print the finish text
	std::cout << "Finished Video Mode Test." << std::endl;
	std::cout << "-------------------------------------------" << std::endl;
	
}