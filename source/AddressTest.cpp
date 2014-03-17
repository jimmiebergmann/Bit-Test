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

#include <AddressTest.hpp>
#include <Bit/Network/Address.hpp>

// Constructor
AddressTest::AddressTest( ) :
	Test( )
{
}

// Virtual functions
void AddressTest::Run( std::ostream & p_Trace )
{
	std::cout << "-------------------------------------------" << std::endl;
	std::cout << "Starting Address test." << std::endl;

	// Assert the constructor
	Bit::Address address( 1, 2, 3, 4 );
	TestAssert( address.GetA( ) == 1 );
	TestAssert( address.GetB( ) == 2 );
	TestAssert( address.GetC( ) == 3 );
	TestAssert( address.GetD( ) == 4 );

	// Assert the address from string
	TestAssert( address.SetAddressFromString( "127.0.0.1" ) == true );
	TestAssert( address.GetA( ) == 127 );
	TestAssert( address.GetB( ) == 0 );
	TestAssert( address.GetC( ) == 0 );
	TestAssert( address.GetD( ) == 1 );

	TestAssert( address.SetAddressFromString( "1.2.3.4" ) == true );
	TestAssert( address.GetA( ) == 1 );
	TestAssert( address.GetB( ) == 2 );
	TestAssert( address.GetC( ) == 3 );
	TestAssert( address.GetD( ) == 4 );

	TestAssert( address.SetAddressFromString( "255.255.255.255" ) == true );
	TestAssert( address.GetA( ) == 255 );
	TestAssert( address.GetB( ) == 255 );
	TestAssert( address.GetC( ) == 255 );
	TestAssert( address.GetD( ) == 255 );

	TestAssert( address.SetAddressFromString( "192.168.0.1" ) == true );
	TestAssert( address.GetA( ) == 192 );
	TestAssert( address.GetB( ) == 168 );
	TestAssert( address.GetC( ) == 0 );
	TestAssert( address.GetD( ) == 1 );

	TestAssert( address.SetAddressFromString( "0.0.0.0" ) == true );
	TestAssert( address.SetAddressFromString( "000.000.000.000" ) == true );
	TestAssert( address.SetAddressFromString( "0192.0168.000000.0001" ) == true );
	TestAssert( address.SetAddressFromString( "192.168.0.1111" ) == false );
	TestAssert( address.SetAddressFromString( "192.1680.0.1" ) == false );
	TestAssert( address.SetAddressFromString( "255.255.256.255" ) == false );

	// Print the finish text
	std::cout << "Finished Address Test." << std::endl;
	std::cout << "-------------------------------------------" << std::endl;
	
}