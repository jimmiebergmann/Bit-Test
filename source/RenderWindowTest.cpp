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

#include <RenderWindowTest.hpp>
#include <Bit/Window/RenderWindow.hpp>

// Constructor
RenderWindowTest::RenderWindowTest( ) :
	Test( )
{
}

// Virtual functions
void RenderWindowTest::Run( std::ostream & p_Trace )
{
	std::cout << "-------------------------------------------" << std::endl;
	std::cout << "Starting RenderWindow test." << std::endl;

	// Create an instace of the render window
	Bit::RenderWindow window;

	// Assert the open function
	TestAssert( window.Open( Bit::VideoMode( Bit::Vector2u32( 800, 600 ) ) ) == true );

	// Assert the is open flag
	TestAssert( window.IsOpen( ) == true );

	// Close the first window
	window.Close( );

	// Run a more advanced render window test( requires human brain powerzzz )
	Bit::Uint32 windowStyle =Bit::Style::TitleBar | Bit::Style::Close | Bit::Style::Minimize | Bit::Style::Resize;
	Bit::Window * pWindow = new Bit::RenderWindow( Bit::VideoMode( Bit::Vector2u32( 800, 600 ) ), "Window", windowStyle );

	// Set a new title and assert it
	pWindow->SetTitle( "New Window Title" );
	TestAssert( pWindow->GetTitle( ) == "New Window Title" );

	// Check if the window is open 
	TestAssert( pWindow->IsOpen( ) == true );

	// Check if the window is focused
	TestAssert( pWindow->IsFocused( ) == true );

	// Run a loop until the window event test is done
	Bit::Uint32 testFlags = 0;

	while( testFlags != 1 + 2 + 4 + 8 + 16 )
	{
		// Update the window
		pWindow->Update( );

		// Poll the window events
		Bit::Event e;
		while( pWindow->PollEvent( e ) )
		{
			switch( e.Type )
			{
			case Bit::Event::Closed:
				std::cout << "Closed window." << std::endl;
				testFlags |= 1;
				break;
			case Bit::Event::GainedFocus:
				std::cout << "Window gained focus." << std::endl;
				testFlags |= 2;
				break;
			case Bit::Event::LostFocus:
				std::cout << "Window lost focus." << std::endl;
				testFlags |= 4;
				break;
			case Bit::Event::Resized:
				std::cout << "Resized window: " << e.Size.x << ", " << e.Size.y << std::endl;
				testFlags |= 8;
				break;
			case Bit::Event::Moved:
				std::cout << "Moved window: " << e.Position.x << ", " << e.Position.y << std::endl;
				testFlags |= 16;
				break;
			default:
				break;
			}
		}
	}

	// Delete(close) the window
	delete pWindow;

	// Print the finish text
	std::cout << "Finished RenderWindow Test." << std::endl;
	std::cout << "-------------------------------------------" << std::endl;
	
}