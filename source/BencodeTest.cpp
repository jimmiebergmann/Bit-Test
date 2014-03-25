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

#include <BencodeTest.hpp>
#include <Bit/System/Bencode/Bencode.hpp>
#include <fstream>
#include <Bit/System/MemoryLeak.hpp>

// Constructor
BencodeTest::BencodeTest( ) :
	Test( )
{
}

// Virtual functions
void BencodeTest::Run( std::ostream & p_Trace )
{
	std::cout << "-------------------------------------------" << std::endl;
	std::cout << "Starting Bencode test." << std::endl;

	////////////////////////////////////////////////////////////////////////////////
	// Parse from string
	Bit::Bencode::Value nilRoot;
	Bit::Bencode::Value stringRootInteger;
	Bit::Bencode::Value stringRootString;
	Bit::Bencode::Value stringRootList;
	Bit::Bencode::Value stringRootDictionary;
	Bit::Bencode::Reader stringReader;

	TestAssert( stringReader.Parse( "www.google.com", nilRoot ) == false );

	TestAssert( stringReader.Parse( "i123e", stringRootInteger ) == true );
	TestAssert( stringRootInteger.AsInt( ) == 123 );
	
	TestAssert( stringReader.Parse( " 28:This is some kind of string.", stringRootString ) == true );
	TestAssert( stringRootString.AsString( ) == "This is some kind of string." );

	TestAssert( stringReader.Parse( "	li1234ei1337ee", stringRootList ) == true );
	TestAssert( stringRootList.GetType( ) == Bit::Bencode::Value::List );
	TestAssert( stringRootList.GetSize( ) == 2 );
	TestAssert( stringRootList[ 0 ].AsInt( ) == 1234 );
	TestAssert( stringRootList[ 1 ].AsInt( ) == 1337 );

	TestAssert( stringReader.Parse( "	\r d5:alphai987e4:beta5:helloe", stringRootDictionary ) == true );
	TestAssert( stringRootDictionary.GetType( ) == Bit::Bencode::Value::Dictionary );
	TestAssert( stringRootDictionary[ "alpha" ].AsInt( ) == 987 );
	TestAssert( stringRootDictionary[ "beta" ].AsString( ) == "hello" );
	

	////////////////////////////////////////////////////////////////////////////////
	//  Parse from file
	Bit::Bencode::Value fileRoot;
	Bit::Bencode::Reader fileReader;

	// Parse from a file
	TestAssert( fileReader.ParseFromFile( "ubuntu.torrent", fileRoot ) == true );

	// Erase the "pieces" field, it's way too much data to display
	fileRoot[ "info" ].Erase( "pieces" );


	////////////////////////////////////////////////////////////////////////////////
	// Try to create a bencode table of different data types
	Bit::Bencode::Value tableRoot;
	Bit::Bencode::Value dicRoot;
	Bit::Bencode::Value listRoot;

	// Add values to the dictionary root
	dicRoot[ "address"] = "127.0.0.1";
	dicRoot[ "port"] = 1337;

	// Assert the dictionary root
	TestAssert( dicRoot.GetType( ) == Bit::Bencode::Value::Dictionary );
	TestAssert( dicRoot[ "address"].AsString( ) == "127.0.0.1" );
	TestAssert( dicRoot[ "port"].AsInt( ) == 1337 );
	TestAssert( dicRoot[ "port"].AsString( ) == "1337" );

	// Append values to the list root
	listRoot.Append( 123 );
	listRoot.Append( 13579 );
	listRoot.Append( "This is a string." );
	listRoot.Append( dicRoot );

	// Assert the list root
	TestAssert( listRoot.GetType( ) == Bit::Bencode::Value::List );
	TestAssert( listRoot.GetSize( ) == 4 );
	TestAssert( listRoot[ 0 ].AsInt( ) == 123 );
	TestAssert( listRoot[ 0 ].AsString( ) == "123" );
	TestAssert( listRoot[ 1 ].AsInt( ) == 13579 );
	TestAssert( listRoot[ 1 ].AsString( ) == "13579" );
	TestAssert( listRoot[ 2 ].AsString( ) == "This is a string." );
	TestAssert( listRoot[ 3 ].GetType( ) == Bit::Bencode::Value::Dictionary );

	// Add values to the table root
	tableRoot[ "alpha" ] = 123456789;
	tableRoot[ "beta" ] = "This is another string.";
	tableRoot[ "list" ]  = listRoot;
	tableRoot[ "dictionary" ]  = dicRoot;

	// Assert the table root
	TestAssert( tableRoot.GetType( ) == Bit::Bencode::Value::Dictionary );
	TestAssert( tableRoot[ "alpha" ].AsInt( ) == 123456789 );
	TestAssert( tableRoot[ "alpha" ].AsString( ) == "123456789" );
	TestAssert( tableRoot[ "beta" ].AsString( ) == "This is another string." );
	TestAssert( tableRoot[ "list" ].GetType( ) == Bit::Bencode::Value::List );
	TestAssert( tableRoot[ "list" ].GetSize( ) == 4 );
	TestAssert( tableRoot[ "list" ][ 0 ].AsInt( ) == 123 );
	TestAssert( tableRoot[ "list" ][ 0 ].AsString( ) == "123" );
	TestAssert( tableRoot[ "list" ][ 1 ].AsInt( ) == 13579 );
	TestAssert( tableRoot[ "list" ][ 1 ].AsString( ) == "13579" );
	TestAssert( tableRoot[ "list" ][ 2 ].AsString( ) == "This is a string." );
	TestAssert( tableRoot[ "list" ][ 3 ].GetType( ) == Bit::Bencode::Value::Dictionary );
	TestAssert( tableRoot[ "list" ][ 3 ].GetType( ) == Bit::Bencode::Value::Dictionary );
	TestAssert( tableRoot[ "list" ][ 3 ][ "address"].AsString( ) == "127.0.0.1" );
	TestAssert( tableRoot[ "list" ][ 3 ][ "port"].AsInt( ) == 1337 );
	TestAssert( tableRoot[ "list" ][ 3 ][ "port"].AsString( ) == "1337" );
	TestAssert( tableRoot[ "dictionary" ].GetType( ) == Bit::Bencode::Value::Dictionary );
	TestAssert( tableRoot[ "dictionary" ][ "address"].AsString( ) == "127.0.0.1" );
	TestAssert( tableRoot[ "dictionary" ][ "port"].AsInt( ) == 1337 );
	TestAssert( tableRoot[ "dictionary" ][ "port"].AsString( ) == "1337" );

	// Erase some values
	tableRoot.Erase( "alpha" );
	TestAssert( tableRoot[ "alpha" ] == Bit::Bencode::Value::NilValue );
	tableRoot[ "list" ].Erase( 1 );
	TestAssert( tableRoot[ "list" ].GetSize( ) == 3 );
	TestAssert( tableRoot[ "list" ][ 0 ].AsInt( ) == 123 );
	TestAssert( tableRoot[ "list" ][ 0 ].AsString( ) == "123" );
	TestAssert( tableRoot[ "list" ][ 1 ].AsString( ) == "This is a string." );
	TestAssert( tableRoot[ "list" ][ 2 ].GetType( ) == Bit::Bencode::Value::Dictionary );
	TestAssert( tableRoot[ "list" ][ 2 ].GetType( ) == Bit::Bencode::Value::Dictionary );
	TestAssert( tableRoot[ "list" ][ 2 ][ "address"].AsString( ) == "127.0.0.1" );
	TestAssert( tableRoot[ "list" ][ 2 ][ "port"].AsInt( ) == 1337 );
	TestAssert( tableRoot[ "list" ][ 2 ][ "port"].AsString( ) == "1337" );
	
	////////////////////////////////////////////////////////////////////////////////
	// Assert the writer
	// Styled writer
	Bit::Bencode::StyledWriter styledWriter;
	std::string output;
	TestAssert( styledWriter.Write( output, dicRoot ) == true );
	output.clear( );
	TestAssert( styledWriter.Write( output, listRoot ) == true );
	output.clear( );
	TestAssert( styledWriter.Write( output, tableRoot ) == true );
	output.clear( );
	
	// Styled writer
	Bit::Bencode::Writer writer;
	TestAssert( writer.Write( output, dicRoot ) == true );
	TestAssert( output == "d7:address9:127.0.0.14:porti1337ee" );
	output.clear( );
	TestAssert( writer.Write( output, listRoot ) == true );
	TestAssert( output == "li123ei13579e17:This is a string.d7:address9:127.0.0.14:porti1337eee" );
	output.clear( );
	TestAssert( writer.Write( output, tableRoot ) == true );
	TestAssert( output == "d4:beta23:This is another string.4:listli123e17:This is a string.d7:address9:127.0.0.14:porti1337eee10:dictionaryd7:address9:127.0.0.14:porti1337eee" );
	output.clear( );
	
	// Compare writer output with original file data
	Bit::Bencode::Value torrentRoot;
	TestAssert( fileReader.ParseFromFile( "ubuntu.torrent", torrentRoot ) == true );
	TestAssert( writer.Write( output, torrentRoot ) == true );

	// Read the raw data from the torrent file
	std::ifstream fin( "ubuntu.torrent", std::ifstream::binary );
	TestAssert( fin.is_open( ) == true );
	fin.seekg( 0, std::ifstream::end );
	Bit::SizeType torrentFileSize = static_cast<Bit::SizeType>( fin.tellg( ) );
	fin.seekg( 0, std::ifstream::beg );
	char * pBuffer = new char[ torrentFileSize ];
	fin.read( pBuffer, torrentFileSize );
	fin.close( );

	// Go throguh all the characters and compare them to the output from our writer
	for( Bit::SizeType i = 0; i < torrentFileSize; i++ )
	{
		TestAssert( pBuffer[ i ] == output[ i ] );
		
		if( pBuffer[ i ] != output[ i ] )
		{
			break;
		}
	}

	delete [ ] pBuffer;
	
	// Print the finish text
	std::cout << "Finished Bencode Test." << std::endl;
	std::cout << "-------------------------------------------" << std::endl;
	
}