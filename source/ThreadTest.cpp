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

#include <ThreadTest.hpp>
#include <Bit/System/Thread.hpp>
#include <Bit/System/SmartMutex.hpp>
#include <Bit/System/Sleep.hpp>

// Constructor
ThreadTest::ThreadTest( ) :
	Test( )
{
}

// Virtual functions
void ThreadTest::Run( std::ostream & p_Trace )
{
	std::cout << "-------------------------------------------" << std::endl;
	std::cout << "Starting Thread test." << std::endl;

	// Run a thread via construcor
	int returnValue = 0;
	Bit::Thread thread(
		[ &returnValue ]( )
		{
			returnValue = 123;
			Bit::Sleep( 500 );
		}
	);

	// Wait for the thread to finish
	thread.Finish( );

	// Assert the return value
	TestAssert( returnValue == 123 );

	// Run a mutex test
	Bit::Mutex mutex;
	bool flag = false;
	bool mutexError = false;
	const Bit::SizeType mutexTests = 3;
	// Create the first mutex
	Bit::Thread thread1(
		[ &mutex, mutexTests, &flag, &mutexError ]( )
		{
			// Create a smart mutex
			Bit::SmartMutex smartMutex( mutex );

			for( Bit::SizeType i = 0; i < mutexTests; i++ )
			{
				// Lock the mutex
				smartMutex.Lock( );
				std::cout << "Hello from thread 1" << std::endl;
				
				// Check the flag and set it.
				if( flag != false )
				{
					mutexError = true;
					break;
				}
				flag = true;

				// Unload the mutex
				smartMutex.Unlock( );

				// Sleep for some time
				Bit::Sleep( 500 );
			}
		}
	);

	// Create the second mutex
	Bit::Thread thread2(
		[ &mutex, mutexTests, &flag, &mutexError ]( )
		{
			// Sleep for some time
			Bit::Sleep( 500 );

			// Create a smart mutex
			Bit::SmartMutex smartMutex( mutex );

			for( Bit::SizeType i = 0; i < mutexTests; i++ )
			{
				// Lock the mutex
				smartMutex.Lock( );
				std::cout << "Hello from thread 2" << std::endl;
				
				// Check the flag and set it.
				if( flag != true )
				{
					mutexError = true;
					break;
				}
				flag = false;

				// Unload the mutex
				smartMutex.Unlock( );

				// Sleep for some time
				Bit::Sleep( 500 );
			}
		}
	);

	// Sleep for some time
	Bit::Sleep( 500 );

	// Assert the IsRunning function
	TestAssert( thread1.IsRunning( ) == true );
	TestAssert( thread2.IsRunning( ) == true );

	// Wait for the threads to finish
	thread1.Finish( );
	thread2.Finish( );

	// Assert the mutex test
	TestAssert( mutexError == false );
	TestAssert( thread1.IsRunning( ) == false );
	TestAssert( thread2.IsRunning( ) == false );

	// Print the finish text
	std::cout << "Finished Thread Test." << std::endl;
	std::cout << "-------------------------------------------" << std::endl;
	
}