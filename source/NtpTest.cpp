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

#include <NtpTest.hpp>
#include <Bit/Network/Ntp.hpp>
#include <iostream>
#include <ctime>
#include <stdio.h>

// Constructor
NtpTest::NtpTest( ) :
	Test( )
{
}

// Virtual functions
void NtpTest::Run( std::ostream & p_Trace )
{
	std::cout << "-------------------------------------------" << std::endl;
	std::cout << "Starting NTP test." << std::endl;

	// Open a ntp client
	Bit::Ntp ntp( 0, 123 );

	// Assert a ntp header
	Bit::Ntp::Header header1( Bit::Ntp::Header::NoWarning, 4, Bit::Ntp::Header::Client );
	TestAssert( header1.GetLeapIndicator( ) == Bit::Ntp::Header::NoWarning );
	TestAssert( header1.GetVersion( ) == 4 );
	TestAssert( header1.GetMode( ) == Bit::Ntp::Header::Client );

	// Assert the ntp set and get functions
	Bit::Ntp::Header header2;
	header2.SetLeapIndicator( Bit::Ntp::Header::Remove );
	header2.SetVersion( 5 );
	header2.SetMode( Bit::Ntp::Header::Server );
	TestAssert( header2.GetLeapIndicator( ) == Bit::Ntp::Header::Remove );
	TestAssert( header2.GetVersion( ) == 5 );
	TestAssert( header2.GetMode( ) == Bit::Ntp::Header::Server );

	// Send request to NTP server
	Bit::Address serverAddress( 127, 0, 0, 1 );
	ntp.SendRequest( header1, serverAddress );
	std::cout << "Sent request." << std::endl;

	// Assert Receive response from NTP server
	Bit::Ntp::Header header3( Bit::Ntp::Header::NoWarning, 4, Bit::Ntp::Header::Client );
	TestAssert( ntp.ReceiveResponse( header3, serverAddress ) == true );
	std::cout << "Received response:" << std::endl;

	// Print the response
	std::cout << " Leap: "				<< (Bit::Uint32)header3.GetLeapIndicator( ) << std::endl;
	std::cout << " Version: "			<< (Bit::Uint32)header3.GetVersion( ) << std::endl;
	std::cout << " Mode: "				<< (Bit::Uint32)header3.GetMode( ) << std::endl;
	std::cout << " Stratum: "			<< (Bit::Uint32)header3.GetStratum( ) << std::endl;
	std::cout << " Polling interval: "	<< (Bit::Uint32)header3.GetPollInterval( ) << std::endl;
	std::cout << " Precision: "			<< (Bit::Uint32)header3.GetPrecision( ) << std::endl;
	std::cout << " Root delay: "		<< header3.GetRootDelay( ) << std::endl;
	std::cout << " Root dispersion: "	<< header3.GetRootDispersion( ) << std::endl;
	Bit::Address address( header3.GetReferenceClock( ) );
	std::cout << " Referense address: "	<< (int)address.GetA( ) << "."
								<< (int)address.GetB( ) << "."
								<< (int)address.GetC( ) << "."
								<< (int)address.GetD( ) << std::endl;
	std::cout << std::endl;
	std::cout	<< " Reference time       : " << header3.GetReferenceTimestamp( ).GetTimeString( )
				<< " ("	<< static_cast<Bit::Float64>( header3.GetReferenceTimestamp( ).GetFractions( ) ) / static_cast<Bit::Float64>( 0xFFFFFFFF ) <<  ")"  << std::endl;
	std::cout << " Reference local time : " << header3.GetTransmitTimestamp( ).GetLocalTimeString( )
				<< " ("	<< static_cast<Bit::Float64>( header3.GetReferenceTimestamp( ).GetFractions( ) ) / static_cast<Bit::Float64>( 0xFFFFFFFF ) <<  ")"  << std::endl;
	std::cout << std::endl;
	std::cout << " Origin time       : " << header3.GetOriginateTimestamp( ).GetTimeString( )
				<< " ("	<< static_cast<Bit::Float64>( header3.GetOriginateTimestamp( ).GetFractions( ) ) / static_cast<Bit::Float64>( 0xFFFFFFFF ) <<  ")"  << std::endl;
	std::cout << " Origin local time : " << header3.GetOriginateTimestamp( ).GetLocalTimeString( )
				<< " ("	<< static_cast<Bit::Float64>( header3.GetOriginateTimestamp( ).GetFractions( ) ) / static_cast<Bit::Float64>( 0xFFFFFFFF ) <<  ")"  << std::endl;
	std::cout << std::endl;
	std::cout << " Receive time       : " << header3.GetReceiveTimestamp( ).GetTimeString( )
				<< " ("	<< static_cast<Bit::Float64>( header3.GetReceiveTimestamp( ).GetFractions( ) ) / static_cast<Bit::Float64>( 0xFFFFFFFF ) <<  ")"  << std::endl;
	std::cout << " Receive local time : " << header3.GetReceiveTimestamp( ).GetLocalTimeString( )
				<< " ("	<< static_cast<Bit::Float64>( header3.GetReceiveTimestamp( ).GetFractions( ) ) / static_cast<Bit::Float64>( 0xFFFFFFFF ) <<  ")"  << std::endl;
	std::cout << std::endl;
	std::cout << " Transmit time       : " << header3.GetTransmitTimestamp( ).GetTimeString( )
				<< " ("	<< static_cast<Bit::Float64>( header3.GetTransmitTimestamp( ).GetFractions( ) ) / static_cast<Bit::Float64>( 0xFFFFFFFF ) <<  ")"  << std::endl;
	std::cout << " Transmit local time : " << header3.GetTransmitTimestamp( ).GetLocalTimeString( )
				<< " ("	<< static_cast<Bit::Float64>( header3.GetTransmitTimestamp( ).GetFractions( ) ) / static_cast<Bit::Float64>( 0xFFFFFFFF ) <<  ")"  << std::endl;
	std::cout << std::endl;
	

	// Close the ntp client
	ntp.Close( );

	// Print the finish text
	std::cout << "Finished NTP Test." << std::endl;
	std::cout << "-------------------------------------------" << std::endl;
	
}