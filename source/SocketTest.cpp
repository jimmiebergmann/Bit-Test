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

#include <SocketTest.hpp>
#include <Bit/Network/Socket.hpp>
#include <Bit/System/MemoryLeak.hpp>

// Constructor
SocketTest::SocketTest( ) :
	Test( )
{
}

// Virtual functions
void SocketTest::Run( std::ostream & p_Trace )
{
	std::cout << "-------------------------------------------" << std::endl;
	std::cout << "Starting Socket test." << std::endl;

	// Assert hton16 and ntoh16
	TestAssert( Bit::Hton16( 43690 ) == Bit::Ntoh16( 43690 ) );
	TestAssert( Bit::Hton16( 43690 ) == 43690 );
	TestAssert( Bit::Hton16( 12345 ) == 14640 );
	Bit::Uint16 valueA = 32645;
	TestAssert( Bit::Hton16( Bit::Ntoh16( valueA ) ) == valueA );

	// Assert hton32 and ntoh32
	TestAssert( Bit::Hton32( 12345678 ) == Bit::Ntoh32( 12345678 ) );
	TestAssert( Bit::Hton32( 2863311530 ) == 2863311530 );
	TestAssert( Bit::Hton32( 1234567890 ) == 3523384905 );
	Bit::Uint32 valueB = 264512354;
	TestAssert( Bit::Hton32( Bit::Ntoh32( valueB ) ) == valueB );
	
	// Assert hton16 and ntoh16
	TestAssert( Bit::Hton64( 123456789012345ULL ) == Bit::Ntoh64( 123456789012345ULL ) );
	TestAssert( Bit::Hton64( 12297829382473034410ULL ) == 12297829382473034410ULL );
	TestAssert( Bit::Hton64( 1234745691234567890ULL ) == 15134059616762208785ULL );
	Bit::Uint64 valueC = 2645123541243545ULL;
	TestAssert( Bit::Hton64( Bit::Ntoh64( valueC ) ) == valueC );

	// Print the finish text
	std::cout << "Finished Socket Test." << std::endl;
	std::cout << "-------------------------------------------" << std::endl;
	
}