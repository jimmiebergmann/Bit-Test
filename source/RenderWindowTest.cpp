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
	Bit::Uint32 windowStyle =Bit::Style::TitleBar | Bit::Style::Close | Bit::Style::Minimize;
	Bit::Window * pWindow = new Bit::RenderWindow( Bit::VideoMode( Bit::Vector2u32( 800, 600 ) ), "Window", windowStyle );

	// Check if the window is open 
	TestAssert( pWindow->IsOpen( ) == true );

	// Run a loop until the window is being closed
	while( pWindow->IsOpen( ) )
	{
		// Poll the window events
		// ..

		// Update the window
		pWindow->Update( );
	}

	// Delete the window
	delete pWindow;

	// Print the finish text
	std::cout << "Finished RenderWindow Test." << std::endl;
	std::cout << "-------------------------------------------" << std::endl;
	
}