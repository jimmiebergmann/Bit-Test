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

#include <TcpListenerTest.hpp>
#include <Bit/Network/TcpSocket.hpp>
#include <Bit/Network/TcpListener.hpp>
#include <Bit/System/Thread.hpp>
#include <Bit/System/Sleep.hpp>
#include <string>
#include <Bit/System/MemoryLeak.hpp>

// Constructor
TcpListenerTest::TcpListenerTest( ) :
	Test( )
{
}

// Virtual functions
void TcpListenerTest::Run( std::ostream & p_Trace )
{
	std::cout << "-------------------------------------------" << std::endl;
	std::cout << "Starting TCP Listener test." << std::endl;

	// Assert values
	Bit::Bool clientConnected = false;
	Bit::Bool clientSent = false;
	Bit::Bool clientRecv = false;
	Bit::Bool serverStarted = false;
	Bit::Bool serverAccepted = false;
	Bit::Bool serverSent = false;
	Bit::Bool serverRecv = false;

	// Start a server and client thread
	Bit::Thread serverThread(
		[ &serverSent, &serverRecv, &serverStarted, &serverAccepted ] ( )
		{
			// Start a tcp listerner
			Bit::TcpListener tcp;
			if( ( serverStarted = tcp.Start( 12345 ) ) == false )
			{
				return;
			}
			std::cout << "Listener: Started." << std::endl;

			// Listen for incoming connections
			Bit::TcpSocket client;
			if( ( serverAccepted = tcp.Listen( client ) ) == false )
			{
				return;
			}
			std::cout << "Listener: Accepted client." << std::endl;

			// Receive message
			const Bit::SizeType recvMessageSize = 14;
			Bit::Uint8 recvMessage[ recvMessageSize ];
			if( client.Receive( recvMessage, recvMessageSize ) != recvMessageSize )
			{
				return;
			}

			// Check if the received message is ok.
			if( std::string( (const char *)recvMessage ) != "Hello server." )
			{
				return;
			}
			std::cout << "Listener: Received messsage: " << recvMessage << std::endl;
			serverRecv = true;

			// Send message
			const Bit::SizeType sendMessageSize = 14;
			Bit::Uint8 sendMessage[ sendMessageSize ] = "Hello client.";
			if( client.Send( sendMessage, sendMessageSize ) != sendMessageSize )
			{
				return;
			}
			std::cout << "Listener: Sent messsage: " << sendMessage << std::endl;
			serverSent = true;

		}
	);

	Bit::Thread clientThread(
		[ &clientConnected, &clientSent, &clientRecv ] ( )
		{
			// Sleep for some time
			Bit::Sleep( Bit::Seconds( 0.5f ) );

			// Connect to local host
			Bit::TcpSocket tcp;
			if( ( clientConnected = tcp.Connect( Bit::Address( 127, 0, 0, 1 ), 12345 ) ) == false )
			{
				return;
			}
			std::cout << "Client: Connected." << std::endl;

			// Send message
			const Bit::SizeType sendMessageSize = 14;
			Bit::Uint8 sendMessage[ sendMessageSize ] = "Hello server.";
			if( tcp.Send( sendMessage, sendMessageSize ) != sendMessageSize )
			{
				return;
			}
			std::cout << "Client: Sent messsage: " << sendMessage << std::endl;
			clientSent = true;

			// Receive message
			const Bit::SizeType recvMessageSize = 14;
			Bit::Uint8 recvMessage[ recvMessageSize ];
			if( tcp.Receive( recvMessage, recvMessageSize ) != recvMessageSize )
			{
				return;
			}

			// Check if the received message is ok.
			if( std::string( (const char *)recvMessage ) != "Hello client." )
			{
				return;
			}
			std::cout << "Client: Received messsage: " << recvMessage << std::endl;
			clientRecv = true;
		}
	);

	// Wait for the threads.
	clientThread.Finish( );
	serverThread.Finish( );

	// Assert the assert values
	TestAssert( clientConnected == true );
	TestAssert( clientSent == true );
	TestAssert( clientRecv == true );
	TestAssert( serverStarted == true );
	TestAssert( serverAccepted == true );
	TestAssert( serverSent == true );
	TestAssert( serverRecv == true );


	// Assert the timeout functionallity
	Bit::Bool conntectAttempt1 = false;
	Bit::Bool conntectAttempt2 = false;
	Bit::Bool listenAttempt1 = false;
	Bit::Bool receiveAttempt1 = false;
	Bit::Bool receiveAttempt2 = false;

	Bit::Thread clientThread2(
		[ &conntectAttempt1, &conntectAttempt2 ] ( )
		{
			Bit::Sleep( Bit::Seconds( 0.5f ) );

			// Try to connect
			Bit::TcpSocket tcp;
			tcp.SetBlocking( false );
			conntectAttempt1 = tcp.Connect( Bit::Address( 127, 0, 0, 1 ), 12343, Bit::Seconds( 1 ) );
			conntectAttempt2 = tcp.Connect( Bit::Address( 127, 0, 0, 1 ), 12343, Bit::Seconds( 2 ) );

			// Sleep for 1 second
			Bit::Sleep( Bit::Seconds( 1.0f ) );

			// Send a message
			const Bit::SizeType sendMessageSize = 14;
			Bit::Uint8 sendMessage[ sendMessageSize ] = "Hello server.";
			if( tcp.Send( sendMessage, sendMessageSize ) != sendMessageSize )
			{
				return;
			}
			std::cout << "Client: Sent messsage: " << sendMessage << std::endl;
			
		}
	);

	Bit::Thread serverThread2(
		[ &listenAttempt1, &receiveAttempt1, &receiveAttempt2 ] ( )
		{
			Bit::TcpListener tcpListener( 12343 );
			Bit::Sleep( Bit::Seconds( 2.0f ) );

			// Listen for incomming connections( client connection attempt 2 )
			Bit::TcpSocket tcp;
			listenAttempt1 = tcpListener.Listen( tcp );
			if( listenAttempt1 )
			{
				std::cout << "Server: Connected." << std::endl;
			}

			// Receive message
			const Bit::SizeType recvMessageSize = 14;
			Bit::Uint8 recvMessage[ recvMessageSize ];
			receiveAttempt1 = tcp.Receive( recvMessage, recvMessageSize, Bit::Milliseconds( 500 ) ) == recvMessageSize;
			std::cout << "Server: Failed to recv message after 0.5 seconds." << std::endl;
			receiveAttempt2 = tcp.Receive( recvMessage, recvMessageSize, Bit::Milliseconds( 1000 ) ) == recvMessageSize;
			std::cout << "Server: Recv message 1: " << recvMessage << std::endl;

		}
	);


	// Wait for the threads to finish
	clientThread2.Finish( );
	serverThread2.Finish( );

	// Assert the assert values
	TestAssert( conntectAttempt1 == false );
	TestAssert( conntectAttempt2 == true );
	TestAssert( listenAttempt1 == true );
	TestAssert( receiveAttempt1 == false );
	TestAssert( receiveAttempt2 == true );

	// Print the finish text
	std::cout << "Finished TCP Listener Test." << std::endl;
	std::cout << "-------------------------------------------" << std::endl;
	
}