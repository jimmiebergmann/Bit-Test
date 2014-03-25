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

// Headers
#include <vector>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <Bit/Build.hpp>
#include <Bit/System/Timer.hpp>

// Test classes
#include <TimerTest.hpp>
#include <MathTest.hpp>
#include <AngleTest.hpp>
#include <Vector2Test.hpp>
#include <Vector3Test.hpp>
#include <Matrix4x4Test.hpp>
#include <ThreadTest.hpp>
#include <BencodeTest.hpp>
#include <AddressTest.hpp>
#include <SocketTest.hpp>
#include <TcpSocketTest.hpp>
#include <TcpListenerTest.hpp>
#include <UdpSocketTest.hpp>
#include <NtpTest.hpp>
#include <VideoModeTest.hpp>
#include <RenderWindowTest.hpp>
#include <OpenGLGraphicDeviceTest.hpp>
#include <Bit/System/MemoryLeak.hpp>

// Global typedefs
typedef std::vector< Test * > TestVector;

// Global variables
static TestVector g_Tests;
static Bit::Timer g_Timer;
static std::ostream & g_Trace = std::cerr;
static Bit::Uint32 g_TotalSuccess = 0;
static Bit::Uint32 g_TotalErrors = 0;

// Global functions
static Bit::Bool InitializeTest( );
static void FinalizeTest( );
static void RunTests( );

int main( )
{
	// Initialize the memory leak detector( only works for windows )
	BitInitMemoryLeak( NULL );


	std::cout << "Starting the test program for Bit Engine." << std::endl;
	std::cout << "-------------------------------------------" << std::endl << std::endl;

	// Inialize the tests
	if( InitializeTest( ) != true )
	{
		std::cout << "Failed to initialize the test program." << std::endl;
		FinalizeTest( );
		return 0;
	}
	else
	{
		std::cout << "Successfully initialized the test program." << std::endl << std::endl;
	}

	// Run the tests
	RunTests( );

	// Close the test
	FinalizeTest( );
	std::cin.get( );
	return 0;
}

Bit::Bool InitializeTest( )
{
	// System tests
	g_Tests.push_back( new BencodeTest );
	g_Tests.push_back( new TimerTest );
	g_Tests.push_back( new MathTest );
	g_Tests.push_back( new AngleTest );
	g_Tests.push_back( new Vector2Test );
	g_Tests.push_back( new Vector3Test );
	g_Tests.push_back( new Matrix4x4Test );
	g_Tests.push_back( new ThreadTest );
	
	// Network tests
	g_Tests.push_back( new AddressTest );
	g_Tests.push_back( new SocketTest );
	g_Tests.push_back( new TcpSocketTest );
	g_Tests.push_back( new TcpListenerTest );
	g_Tests.push_back( new UdpSocketTest );
	g_Tests.push_back( new NtpTest );

	// Graphic/window tests
	g_Tests.push_back( new VideoModeTest );
	g_Tests.push_back( new RenderWindowTest );
	g_Tests.push_back( new OpenGLGraphicDeviceTest );
	
	return true;
}

void FinalizeTest( )
{
	// Delete the test class pointers
	for( TestVector::iterator it = g_Tests.begin( ); it != g_Tests.end( ); it++ )
	{
		delete (*it);
	}
}

void RunTests( )
{
	// Start the timer
	g_Timer.Start( );

	// Run the tests
	for( TestVector::iterator it = g_Tests.begin( ); it != g_Tests.end( ); it++ )
	{
		// Run the current test
		(*it)->Run( g_Trace );

		bool status = (*it)->GetStatus( );

		// Evaluate the status
		if( status )
		{
			g_TotalSuccess++;
		}
		else
		{
			g_TotalErrors++;
		}
		
	}

	// Stop the timer
	g_Timer.Stop( );

	// Print the output
	const std::streamsize wSize = 22;
	std::cout << std::endl;
	std::cout << "Results:" << std::endl;
	std::cout << "-------------------------------------------" << std::endl;
	std::cout << std::left << std::setw( wSize ) << "Tests finished in: " << g_Timer.GetTime( ) << " seconds." << std::endl;
	std::cout << std::left << std::setw( wSize ) << "Succeeded: " << g_TotalSuccess <<  "/" << g_Tests.size( ) << " tests succeeded." << std::endl;
	std::cout << std::left << std::setw( wSize ) << "Errors: " << g_TotalErrors <<  "/" << g_Tests.size( ) << " tests failed." << std::endl;
}