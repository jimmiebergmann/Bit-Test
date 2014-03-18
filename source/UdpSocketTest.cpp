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

#include <UdpSocketTest.hpp>
#include <Bit/Network/UdpSocket.hpp>

// Constructor
UdpSocketTest::UdpSocketTest( ) :
	Test( )
{
}

// Virtual functions
void UdpSocketTest::Run( std::ostream & p_Trace )
{
	std::cout << "-------------------------------------------" << std::endl;
	std::cout << "Starting UDP Socket test." << std::endl;

	// Start a udp socket
	Bit::Uint16 client1Port = 0;
	Bit::Uint16 client2Port = 12346;
	Bit::UdpSocket client1( client1Port );
	Bit::UdpSocket client2( client2Port );	

	// Let client 1 send a message to client 2
	const Bit::SizeType messageLength = 14;
	char client1SendMessage[ messageLength ] = "Hello client2";
	TestAssert( client1.Send( client1SendMessage, messageLength, Bit::Address( 127, 0, 0, 1 ), client2Port ) == messageLength );
	std::cout << "Client 1: Sent messsage: " << client1SendMessage << std::endl;

	// Let client 2 receive the message from client 1
	char client2RecvMessage[ messageLength ];
	Bit::Address address;
	TestAssert( client2.Receive( client2RecvMessage, messageLength, address, client1Port ) == messageLength );
	std::cout << "Client 2: Received messsage( "	<< (int)address.GetA( ) << "."
													<< (int)address.GetB( ) << "."
													<< (int)address.GetC( ) << "."
													<< (int)address.GetD( ) << ":"
													<< client1Port  << " ): " << client2RecvMessage << std::endl;
	// Let client 2 answer client 1
	char client2SendMessage[ messageLength ] = "Hello client1";
	TestAssert( client2.Send( client2SendMessage, messageLength, address, client1Port ) == messageLength );
	std::cout << "Client 2: Sent messsage: " << client2SendMessage << std::endl;

	// Let client 2 receive the message from client 1
	char client1RecvMessage[ messageLength ];
	TestAssert( client1.Receive( client1RecvMessage, messageLength, address, client2Port ) == messageLength );
	std::cout << "Client 1: Received messsage( "	<< (int)address.GetA( ) << "."
													<< (int)address.GetB( ) << "."
													<< (int)address.GetC( ) << "."
													<< (int)address.GetD( ) << ":"
													<< client2Port  << " ): " << client1RecvMessage << std::endl;

	// Stop udp socket
	client1.Stop( );
	client2.Stop( );

	// Print the finish text
	std::cout << "Finished UDP Socket Test." << std::endl;
	std::cout << "-------------------------------------------" << std::endl;
	
}