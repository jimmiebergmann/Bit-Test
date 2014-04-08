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

#include <TimerTest.hpp>
#include <Bit/System/Timer.hpp>
#include <Bit/System/Sleep.hpp>
#include <Bit/System/MemoryLeak.hpp>

// Constructor
TimerTest::TimerTest( ) :
	Test( )
{
}

// Virtual functions
void TimerTest::Run( std::ostream & p_Trace )
{
	std::cout << "-------------------------------------------" << std::endl;
	std::cout << "Starting Timer test." << std::endl;

	const Bit::Float64 sleepTime = 0.5f;
	const Bit::Float64 diff = 0.05f;
	Bit::Timer timer;

	// Run a Start/Stop/GetTime test
	timer.Start( );
	Bit::Sleep( static_cast<Bit::Uint32>( sleepTime * 1000.0f ) );
	timer.Stop( );
	
	// Assert the time
	TestAssert( timer.GetTime( ).AsSeconds( ) >= sleepTime - diff &&
				timer.GetTime( ).AsSeconds( ) <= sleepTime + diff );
	TestAssert( timer.GetTime( ).AsMilliseconds( ) >= (sleepTime - diff) * 1000.0f &&
				timer.GetTime( ).AsMilliseconds( ) <= (sleepTime + diff) * 1000.0f );
	TestAssert( timer.GetTime( ).AsMicroseconds( ) >= (sleepTime - diff) * 1000000.0f &&
				timer.GetTime( ).AsMicroseconds( ) <= (sleepTime + diff) * 1000000.0f );
	std::cout << "Result: " << timer.GetTime( ).AsSeconds( ) << "/" << sleepTime << "(" << ( sleepTime - diff ) << " - " << ( sleepTime + diff ) << ")." << std::endl;

	// Run a Start/GetLapsedTime test
	timer.Start( );
	Bit::Sleep( static_cast<Bit::Uint32>( sleepTime * 1000.0f ) );
	Bit::Float64 time = timer.GetLapsedTime( ).AsSeconds( );
	
	// Assert the time
	TestAssert( time >= sleepTime - diff &&
				time <= sleepTime + diff );

	std::cout << "Result: " << timer.GetTime( ).AsSeconds( ) << "/" << sleepTime << "(" << ( sleepTime - diff ) << " - " << ( sleepTime + diff ) << ")." << std::endl;

	// Print the finish text
	std::cout << "Finished Timer Test." << std::endl;
	std::cout << "-------------------------------------------" << std::endl;
	
}