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

#include <HashTest.hpp>
#include <Bit/System/Hash.hpp>
#include <Bit/System/MemoryLeak.hpp>

// Constructor
HashTest::HashTest( ) :
	Test( )
{
}

// Virtual functions
void HashTest::Run( std::ostream & p_Trace )
{
	std::cout << "-------------------------------------------" << std::endl;
	std::cout << "Starting Hash test." << std::endl;

	// Assert the hash constructor
	Bit::Hash hash1( "ak5o2" );
	TestAssert( hash1.AsRaw( ).size( ) == 5 );
	if( hash1.AsRaw( ).size( ) == 5 )
	{
		TestAssert( hash1.AsRaw( )[ 0 ] == 'a' );
		TestAssert( hash1.AsRaw( )[ 1 ] == 'k');
		TestAssert( hash1.AsRaw( )[ 2 ] == '5');
		TestAssert( hash1.AsRaw( )[ 3 ] == 'o');
		TestAssert( hash1.AsRaw( )[ 4 ] == '2');
	}

	const Bit::Uint8 hashValues[ 6 ] = { 'J', 'D', 'y', 'O', 'm', 'X' };
	Bit::Hash hash2( hashValues, 6 );
	TestAssert( hash2.AsRaw( ).size( ) == 6 );
	if( hash2.AsRaw( ).size( ) == 6 )
	{
		TestAssert( hash2.AsRaw( )[ 0 ] == 'J' );
		TestAssert( hash2.AsRaw( )[ 1 ] == 'D');
		TestAssert( hash2.AsRaw( )[ 2 ] == 'y');
		TestAssert( hash2.AsRaw( )[ 3 ] == 'O');
		TestAssert( hash2.AsRaw( )[ 4 ] == 'm');
		TestAssert( hash2.AsRaw( )[ 5 ] == 'X');
	}

	// Assert the AsString funtion
	TestAssert( hash1.AsString( ) == "ak5o2" );
	TestAssert( hash2.AsString( ) == "JDyOmX" );

	// Assert the AsHexString function
	TestAssert( hash1.AsHexString( false ) == "616b356f32" );
	TestAssert( hash2.AsHexString( false ) == "4a44794f6d58" );
	TestAssert( hash1.AsHexString( true ) == "616B356F32" );
	TestAssert( hash2.AsHexString( true ) == "4A44794F6D58" );

	// Assert the AsUrlEncodedString
	Bit::Hash hash3;
	hash3.SetHexString( "CA486CD52A47D77D4ED72D6A0A01E49987EEE82D" );
	TestAssert( hash3.AsUrlEncodedString( ) == "%caHl%d5%2aG%d7%7dN%d7-j%0a%01%e4%99%87%ee%e8-" );

	// Assert the clear function
	Bit::Hash hash4( "E3811B9539CACFF680E418124272177C47477157" );
	TestAssert( hash4.AsRaw( ).size( ) == 40 );
	hash4.Clear( );
	TestAssert( hash4.AsRaw( ).size( ) == 0 );

	// Assert the set functions
	hash3.Set( "3adfgtfasd" );
	TestAssert( hash3.AsString( ) == "3adfgtfasd");

	hash3.Clear( );
	hash3.Set( hashValues, 6 );
	TestAssert( hash3.AsString( ) == "JDyOmX");

	hash3.Clear( );
	TestAssert( hash3.SetHexString( "DF015j3c" ) == false );
	TestAssert( hash3.SetHexString( "DF015A3c" ) == true );
	TestAssert( hash3.AsRaw( ).size( ) == 4 );
	if( hash3.AsRaw( ).size( ) == 4 )
	{
		TestAssert( hash3.AsRaw( )[ 0 ] == 0xDF );
		TestAssert( hash3.AsRaw( )[ 1 ] == 0x01 );
		TestAssert( hash3.AsRaw( )[ 2 ] == 0x5A );
		TestAssert( hash3.AsRaw( )[ 3 ] == 0x3C );
	}

	// Print the finish text
	std::cout << "Finished Hash Test." << std::endl;
	std::cout << "-------------------------------------------" << std::endl;
	
}