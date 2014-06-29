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

#include <TcpSocketTest.hpp>
#include <Bit/Network/TcpSocket.hpp>
#include <Bit/System/Timer.hpp>
#include <Bit/System/MemoryLeak.hpp>

// Constructor
TcpSocketTest::TcpSocketTest( ) :
	Test( )
{
}

// Virtual functions
void TcpSocketTest::Run( std::ostream & p_Trace )
{
	std::cout << "-------------------------------------------" << std::endl;
	std::cout << "Starting TCP Socket test." << std::endl;

	// Assert a connect to sunet.se
	Bit::TcpSocket tcp;
	TestAssert( tcp.Connect( Bit::Address( 109, 105, 111, 14 ), 80 ) == true );

	// Disconnect
	tcp.Disconnect( );

	// Assert the timeout again
	Bit::TcpSocket tcpTimeout;
	TestAssert( tcp.Connect( Bit::Address( 109, 105, 111, 14 ), 80, Bit::Seconds( 3 ) ) == true );

	// Assert the timeout connection again, but time it
	Bit::Timer timer;
	timer.Start( );
	TestAssert( tcp.Connect( Bit::Address( 127, 0, 0, 2 ), 87, Bit::Seconds( 3 ) ) == false );
	timer.Stop( );
	///TestAssert( timer.GetTime( ).AsSeconds( ) > 2.0f && timer.GetTime( ).AsSeconds( ) < 6.0f );

	// Print the finish text
	std::cout << "Finished TCP Socket Test." << std::endl;
	std::cout << "-------------------------------------------" << std::endl;

}
