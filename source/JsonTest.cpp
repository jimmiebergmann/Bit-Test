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

#include <JsonTest.hpp>
#include <Bit/System/Json.hpp>
#include <Bit/System/MemoryLeak.hpp>

// Constructor
JsonTest::JsonTest( ) :
	Test( )
{
}

// Virtual functions
void JsonTest::Run( std::ostream & p_Trace )
{
	// NEED FIX IN THIS TEST.
    // THE ORDER OF THE JSON ELEMENTS DEPENDS ON THE HASH MAP FUNCTION.
    // WE NEED ANOTHER WAY FOR COMPARING OUTPUT DATA FROM THE PARSERS.

	// WE NEED AN INTEGER DATA TYPE FOR THE JSON VALUE CLASS!

	std::cout << "-------------------------------------------" << std::endl;
	std::cout << "Starting Json test." << std::endl;

	////////////////////////////////////////////////////////////////////////////////
	// Parse from string
	Bit::Json::Value nullRoot;
	Bit::Json::Value root;
	/*Bit::Json::Value stringRootInteger;
	Bit::Json::Value stringRootString;
	Bit::Json::Value stringRootList;
	Bit::Json::Value stringRootDictionary;*/
	Bit::Json::Reader stringReader;

	TestAssert( stringReader.Parse( "    ", nullRoot ) == false );
	TestAssert( stringReader.Parse( "     www.google.com  ", nullRoot ) == false );
	TestAssert( stringReader.Parse( "  {  \"name\" : \"Jimmie Bergmann\"   ,  \"age\":\"123\"  } ", nullRoot ) == true );
	TestAssert( stringReader.Parse( "{\"name\":\"Jimmie Bergmann\",\"age\":\"123\"} ", root ) == true );

	TestAssert( root[ "name"].AsString( ) == "Jimmie Bergmann" );
	TestAssert( root[ "age"].AsString( ) == "123" );
	TestAssert( root[ "age"].AsInteger( ) == 123 );


	////////////////////////////////////////////////////////////////////////////////
	// Try to create a json table of different data types
	Bit::Json::Value tableRoot;
	Bit::Json::Value objRoot;
	Bit::Json::Value arrayRoot;

	// Add values to the dictionary root
	objRoot[ "address"] = "127.0.0.1";
	objRoot[ "port"] = 1337;
	objRoot[ "time"] = 12345.75f;
	objRoot[ "connected"] = true;

	// Assert the dictionary root
	TestAssert( objRoot.GetType( ) == Bit::Json::Value::Object );
	TestAssert( objRoot[ "address"].AsString( ) == "127.0.0.1" );
	TestAssert( objRoot[ "port"].AsNumber( ) == 1337.0f );
	TestAssert( objRoot[ "port"].AsInteger( ) == 1337 );
	TestAssert( objRoot[ "port"].AsString( ) == "1337" );
	TestAssert( objRoot[ "port"].AsBoolean( ) == true );

	TestAssert( objRoot[ "time"].AsNumber( ) == 12345.75f );
	TestAssert( objRoot[ "time"].AsInteger( ) == 12345 );
	TestAssert( objRoot[ "time"].AsString( ) == "12345.7500" );
	TestAssert( objRoot[ "time"].AsBoolean( ) == true );

	TestAssert( objRoot[ "connected"].AsBoolean( ) == true );
	TestAssert( objRoot[ "connected"].AsString( ) == "True" );

	// Assert the Get function
	TestAssert( objRoot.Get( "address", 0.0f ).AsString( ) == "127.0.0.1" );
	TestAssert( objRoot.Get( "alpha", 3567.0f ).AsNumber( ) == 3567.0f );
	TestAssert( objRoot.Get( "beta", 987.0f ).AsNumber( ) == 987.0f );
	
	// Append values to the list root
	arrayRoot.Append( 123 );
	arrayRoot.Append( 13579.0f );
	arrayRoot.Append( "This is a string." );
	arrayRoot.Append( true );
	arrayRoot.Append( objRoot );

	// Assert the list root
	TestAssert( arrayRoot.GetType( ) == Bit::Json::Value::Array );
	TestAssert( arrayRoot.GetSize( ) == 5 );
	TestAssert( arrayRoot[ 0 ].AsInteger( ) == 123 );
	TestAssert( arrayRoot[ 0 ].AsString( ) == "123" );
	TestAssert( arrayRoot[ 1 ].AsNumber( ) == 13579.0f );
	TestAssert( arrayRoot[ 1 ].AsString( ) == "13579.0000" );
	TestAssert( arrayRoot[ 2 ].AsString( ) == "This is a string." );
	TestAssert( arrayRoot[ 3 ].AsBoolean( ) == true );
	TestAssert( arrayRoot[ 3 ].AsString( ) == "True" );
	TestAssert( arrayRoot[ 3 ].AsNumber( ) == 1.0f );
	TestAssert( arrayRoot[ 4 ].GetType( ) == Bit::Json::Value::Object );
	
	// Add values to the table root
	tableRoot[ "alpha" ]	= 123456789;
	tableRoot[ "beta" ]		= "This is another string.";
	tableRoot[ "array" ]	= arrayRoot;
	tableRoot[ "object" ]	= objRoot;
	
	// Assert the table root
	TestAssert( tableRoot.GetType( ) == Bit::Json::Value::Object );
	TestAssert( tableRoot[ "alpha" ].AsInteger( ) == 123456789 );
	//TestAssert( tableRoot[ "alpha" ].AsString( ) == "123456789" );
	TestAssert( tableRoot[ "beta" ].AsString( ) == "This is another string." );
	TestAssert( tableRoot[ "array" ].GetType( ) == Bit::Json::Value::Array );
	TestAssert( tableRoot[ "array" ].GetSize( ) == 5 );
	TestAssert( tableRoot[ "array" ][ 0 ].AsInteger( ) == 123 );
	TestAssert( tableRoot[ "array" ][ 0 ].AsString( ) == "123" );
	TestAssert( tableRoot[ "array" ][ 1 ].AsNumber( ) == 13579.0f );
	TestAssert( tableRoot[ "array" ][ 1 ].AsString( ) == "13579.0000" );
	TestAssert( tableRoot[ "array" ][ 2 ].AsString( ) == "This is a string." );
	TestAssert( tableRoot[ "array" ][ 3 ].AsString( ) == "True" );
	TestAssert( tableRoot[ "array" ][ 4 ].GetType( ) == Bit::Json::Value::Object );
	TestAssert( tableRoot[ "array" ][ 4 ][ "address"].AsString( ) == "127.0.0.1" );
	TestAssert( tableRoot[ "array" ][ 4 ][ "port"].AsInteger( ) == 1337 );
	TestAssert( tableRoot[ "array" ][ 4 ][ "port"].AsString( ) == "1337" );
	TestAssert( tableRoot[ "object" ].GetType( ) == Bit::Json::Value::Object );
	TestAssert( tableRoot[ "object" ][ "address"].AsString( ) == "127.0.0.1" );
	TestAssert( tableRoot[ "object" ][ "port"].AsInteger( ) == 1337 );
	TestAssert( tableRoot[ "object" ][ "port"].AsString( ) == "1337" );
	
	// Erase some values
	tableRoot.Erase( "alpha" );
	TestAssert( tableRoot[ "alpha" ] == Bit::Json::Value::NullValue );
	tableRoot[ "array" ].Erase( 1 );
	TestAssert( tableRoot[ "array" ].GetSize( ) == 4 );
	TestAssert( tableRoot[ "array" ][ 0 ].AsInteger( ) == 123 );
	TestAssert( tableRoot[ "array" ][ 0 ].AsString( ) == "123" );
	TestAssert( tableRoot[ "array" ][ 1 ].AsString( ) == "This is a string." )
	TestAssert( tableRoot[ "array" ][ 2 ].AsString( ) == "True" );
	TestAssert( tableRoot[ "array" ][ 3 ].GetType( ) == Bit::Json::Value::Object );
	TestAssert( tableRoot[ "array" ][ 3 ].GetType( ) == Bit::Json::Value::Object );
	TestAssert( tableRoot[ "array" ][ 3 ][ "address"].AsString( ) == "127.0.0.1" );
	TestAssert( tableRoot[ "array" ][ 3 ][ "port"].AsInteger( ) == 1337 );
	TestAssert( tableRoot[ "array" ][ 3 ][ "port"].AsString( ) == "1337" );
	
	// Print the finish text
	std::cout << "Finished Json Test." << std::endl;
	std::cout << "-------------------------------------------" << std::endl;
	
}