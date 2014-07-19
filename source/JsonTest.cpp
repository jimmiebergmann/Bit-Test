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

	std::cout << "-------------------------------------------" << std::endl;
	std::cout << "Starting Json test." << std::endl;


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
	

	////////////////////////////////////////////////////////////////////////////////
	// Parse from string
	Bit::Json::Value nullRoot;
	Bit::Json::Value stringRoot;
	Bit::Json::Value stringRootString;
	Bit::Json::Value stringRootNumber;
	Bit::Json::Value stringRootBoolean;
	Bit::Json::Value stringRootArray;
	Bit::Json::Value stringRootObject;
	Bit::Json::Reader stringReader;

	TestAssert( stringReader.Parse( "    ", nullRoot ) == false );
	TestAssert( stringReader.Parse( "     www.google.com  ", nullRoot ) == false );

	// String parse test
	TestAssert( stringReader.Parse( "   { \"name\" : \"Bert Karlsson\", \"street\" : \"FIFTH AVENUE, NEW YORK, NY\" }  ", stringRootString ) == true );
	TestAssert( stringRootString[ "name"].GetType( ) == Bit::Json::Value::String );
	TestAssert( stringRootString[ "name"].AsString( ) == "Bert Karlsson" );
	TestAssert( stringRootString[ "street"].GetType( ) == Bit::Json::Value::String );
	TestAssert( stringRootString[ "street"].AsString( ) == "FIFTH AVENUE, NEW YORK, NY" );

	// Number parse test
	TestAssert( stringReader.Parse( "   { \"integerPos\" : 918273645, \"integerNeg\" : -192837465, \t\t\n"
									" \"floatPos\" : 17545.75, \"floatNeg\" : -47345.25,  \n"
									" \"expPos1\" : 96.875E+2, \"expPos2\" : 96.875e2, \"expPos3\" : 96.875e-2, \"expPos4\" : 961534e-2, "
									" \"expNeg1\" : -96.875E+2, \"expNeg2\" : -96.875e2, \"expNeg3\" : -96.875e-2,  \"expNeg4\" : -961534e-2  }  ", stringRootNumber ) == true );
	TestAssert( stringRootNumber[ "integerPos"].GetType( ) == Bit::Json::Value::Number );
	TestAssert( stringRootNumber[ "integerPos"].GetIntegerFlag( ) == true );
	TestAssert( stringRootNumber[ "integerPos"].AsInteger( ) == 918273645 );
	TestAssert( stringRootNumber[ "integerNeg"].GetType( ) == Bit::Json::Value::Number );
	TestAssert( stringRootNumber[ "integerNeg"].GetIntegerFlag( ) == true );
	TestAssert( stringRootNumber[ "integerNeg"].AsInteger( ) == -192837465 );
	TestAssert( stringRootNumber[ "floatPos"].GetType( ) == Bit::Json::Value::Number );
	TestAssert( stringRootNumber[ "floatPos"].GetIntegerFlag( ) == false );
	TestAssert( stringRootNumber[ "floatPos"].AsNumber( ) == 17545.75f );
	TestAssert( stringRootNumber[ "floatNeg"].GetType( ) == Bit::Json::Value::Number );
	TestAssert( stringRootNumber[ "floatNeg"].GetIntegerFlag( ) == false );
	TestAssert( stringRootNumber[ "floatNeg"].AsNumber( ) == -47345.25f );
	TestAssert( stringRootNumber[ "expPos1"].GetType( ) == Bit::Json::Value::Number );
	TestAssert( stringRootNumber[ "expPos1"].GetIntegerFlag( ) == false );
	TestAssert( stringRootNumber[ "expPos1"].AsNumber( ) == 9687.5f );
	TestAssert( stringRootNumber[ "expPos2"].GetType( ) == Bit::Json::Value::Number );
	TestAssert( stringRootNumber[ "expPos2"].GetIntegerFlag( ) == false );
	TestAssert( stringRootNumber[ "expPos2"].AsNumber( ) == 9687.5f );
	TestAssert( stringRootNumber[ "expPos3"].GetType( ) == Bit::Json::Value::Number );
	TestAssert( stringRootNumber[ "expPos3"].GetIntegerFlag( ) == false );
	TestAssert( stringRootNumber[ "expPos3"].AsNumber( ) == 0.96875f );
	TestAssert( stringRootNumber[ "expPos4"].GetType( ) == Bit::Json::Value::Number );
	TestAssert( stringRootNumber[ "expPos4"].GetIntegerFlag( ) == true );
	TestAssert( stringRootNumber[ "expPos4"].AsInteger( ) == 9615 );
	TestAssert( stringRootNumber[ "expNeg1"].GetType( ) == Bit::Json::Value::Number );
	TestAssert( stringRootNumber[ "expNeg1"].GetIntegerFlag( ) == false );
	TestAssert( stringRootNumber[ "expNeg1"].AsNumber( ) == -9687.5f );
	TestAssert( stringRootNumber[ "expNeg2"].GetType( ) == Bit::Json::Value::Number );
	TestAssert( stringRootNumber[ "expNeg2"].GetIntegerFlag( ) == false );
	TestAssert( stringRootNumber[ "expNeg2"].AsNumber( ) == -9687.5f );
	TestAssert( stringRootNumber[ "expNeg3"].GetType( ) == Bit::Json::Value::Number );
	TestAssert( stringRootNumber[ "expNeg3"].GetIntegerFlag( ) == false );
	TestAssert( stringRootNumber[ "expNeg3"].AsNumber( ) == -0.96875f );
	TestAssert( stringRootNumber[ "expNeg4"].GetType( ) == Bit::Json::Value::Number );
	TestAssert( stringRootNumber[ "expNeg4"].GetIntegerFlag( ) == true );
	TestAssert( stringRootNumber[ "expNeg4"].AsInteger( ) == -9615 );

	// Boolean parse test
	TestAssert( stringReader.Parse( "   { \"healty\" : true, \"happy\" : false, \"emotional\" : true }  ", stringRootBoolean ) == true );
	TestAssert( stringRootBoolean[ "healty"].GetType( ) == Bit::Json::Value::Boolean );
	TestAssert( stringRootBoolean[ "healty"].AsBoolean( ) == true );
	TestAssert( stringRootBoolean[ "happy"].GetType( ) == Bit::Json::Value::Boolean );
	TestAssert( stringRootBoolean[ "happy"].AsBoolean( ) == false );
	TestAssert( stringRootBoolean[ "emotional"].GetType( ) == Bit::Json::Value::Boolean );
	TestAssert( stringRootBoolean[ "emotional"].AsBoolean( ) == true );

	// Array test
	TestAssert( stringReader.Parse( "   { \"array1\" : [ \"Bert\", 12345, true, { }, [], null ] }  ", stringRootArray ) == true );
	TestAssert( stringRootArray[ "array1"].GetType( ) == Bit::Json::Value::Array );
	TestAssert( stringRootArray[ "array1"].GetSize( ) == 6 );
	TestAssert( stringRootArray[ "array1"][ 0 ].GetType( ) == Bit::Json::Value::String );
	TestAssert( stringRootArray[ "array1"][ 0 ].AsString( ) == "Bert" );
	TestAssert( stringRootArray[ "array1"][ 1 ].GetType( ) == Bit::Json::Value::Number );
	TestAssert( stringRootArray[ "array1"][ 1 ].AsInteger( ) == 12345 );
	TestAssert( stringRootArray[ "array1"][ 2 ].GetType( ) == Bit::Json::Value::Boolean );
	TestAssert( stringRootArray[ "array1"][ 2 ].AsBoolean( ) == true );
	TestAssert( stringRootArray[ "array1"][ 3 ].GetType( ) == Bit::Json::Value::Object );
	TestAssert( stringRootArray[ "array1"][ 4 ].GetType( ) == Bit::Json::Value::Array );
	TestAssert( stringRootArray[ "array1"][ 4 ].GetSize( ) == 0 );
	TestAssert( stringRootArray[ "array1"][ 5 ].GetType( ) == Bit::Json::Value::Null );

	// Object parse test
	TestAssert( stringReader.Parse( "   {  }  ", stringRootObject ) == true );
	TestAssert( stringReader.Parse( "   { \"object\" : { \"child\" : { \"name\" : \"Bert\", \"data\" : null  }  } }  ", stringRootObject ) == true );
	TestAssert( stringRootObject[ "object"].GetType( ) == Bit::Json::Value::Object );
	TestAssert( stringRootObject[ "object"]["child"].GetType( ) == Bit::Json::Value::Object );
	TestAssert( stringRootObject[ "object"]["child"]["name"].GetType( ) == Bit::Json::Value::String );
	TestAssert( stringRootObject[ "object"]["child"]["name"].AsString( ) == "Bert" );
	TestAssert( stringRootObject[ "object"]["child"]["data"].GetType( ) == Bit::Json::Value::Null );

	////////////////////////////////////////////////////////////////////////////////
	// Parse from file

	// Compare writer output with original file data
	Bit::Json::Value fileRoot;
	Bit::Json::Reader fileReader;
	TestAssert( fileReader.ParseFromFile( "input/test.json", fileRoot ) == true );

	////////////////////////////////////////////////////////////////////////////////
	// Write to file

	// Compare writer output with original file data
	Bit::Json::StyledWriter fileStyledWriter;
	std::string output;
	TestAssert( fileStyledWriter.Write( output, stringRootString ) == true );
	TestAssert( fileStyledWriter.Write( output, stringRootObject ) == true );
	TestAssert( fileStyledWriter.Write( output, stringRootBoolean ) == true );
	TestAssert( fileStyledWriter.Write( output, stringRootNumber ) == true );
	TestAssert( fileStyledWriter.Write( output, stringRootArray ) == true );
	TestAssert( fileStyledWriter.Write( output, fileRoot ) == true );

	Bit::Json::Writer fileWriter;
	TestAssert( fileWriter.Write( output, stringRootString ) == true );
	TestAssert( fileWriter.Write( output, stringRootObject ) == true );
	TestAssert( fileWriter.Write( output, stringRootBoolean ) == true );
	TestAssert( fileWriter.Write( output, stringRootNumber ) == true );
	TestAssert( fileWriter.Write( output, stringRootArray ) == true );
	TestAssert( fileWriter.Write( output, fileRoot ) == true );

	
	// Print the finish text
	std::cout << "Finished Json Test." << std::endl;
	std::cout << "-------------------------------------------" << std::endl;
	
}