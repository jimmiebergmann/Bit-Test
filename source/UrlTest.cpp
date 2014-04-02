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

#include <UrlTest.hpp>
#include <Bit/Network/Url.hpp>
#include <Bit/System/MemoryLeak.hpp>

// Constructor
UrlTest::UrlTest( ) :
	Test( )
{
}

// Virtual functions
void UrlTest::Run( std::ostream & p_Trace )
{
	std::cout << "-------------------------------------------" << std::endl;
	std::cout << "Starting URL test." << std::endl;

	// Assert the constructor
	Bit::Url url1( "http://admin:losen@sv.wikipedia.org:80/w/index.php?title=Dator&action=edit#Historia" );
	TestAssert( url1.GetProtocol( ) == "http" );
	TestAssert( url1.GetUsername( ) == "admin" );
	TestAssert( url1.GetPassword( ) == "losen" );
	TestAssert( url1.GetDomain( ) == "sv.wikipedia.org" );
	TestAssert( url1.GetPort( ) == 80);
	TestAssert( url1.GetPath( ) == "w/index.php" );
	TestAssert( url1.GetQuery( ) == "title=Dator&action=edit" );
	TestAssert( url1.GetFragment( ) == "Historia" );

	// Assert the set function
	TestAssert( url1.Set( "scheme://domain:54/path?query_string#fragment_id" ) == true );
	TestAssert( url1.GetProtocol( ) == "scheme" );
	TestAssert( url1.GetUsername( ) == "" );
	TestAssert( url1.GetPassword( ) == "" );
	TestAssert( url1.GetDomain( ) == "domain" );
	TestAssert( url1.GetPort( ) == 54);
	TestAssert( url1.GetPath( ) == "path" );
	TestAssert( url1.GetQuery( ) == "query_string" );
	TestAssert( url1.GetFragment( ) == "fragment_id" );

	TestAssert( url1.Set( "www.google.com/" ) == true );
	TestAssert( url1.GetProtocol( ) == """" );
	TestAssert( url1.GetUsername( ) == "" );
	TestAssert( url1.GetPassword( ) == "" );
	TestAssert( url1.GetDomain( ) == "www.google.com" );
	TestAssert( url1.GetPort( ) == 0);
	TestAssert( url1.GetPath( ) == "" );
	TestAssert( url1.GetQuery( ) == "" );
	TestAssert( url1.GetFragment( ) == "" );

	TestAssert( url1.Set( "ftp://username:password@domain/path/file" ) == true );
	TestAssert( url1.GetProtocol( ) == "ftp" );
	TestAssert( url1.GetUsername( ) == "username" );
	TestAssert( url1.GetPassword( ) == "password" );
	TestAssert( url1.GetDomain( ) == "domain" );
	TestAssert( url1.GetPort( ) == 0);
	TestAssert( url1.GetPath( ) == "path/file" );
	TestAssert( url1.GetQuery( ) == "" );
	TestAssert( url1.GetFragment( ) == "" );

	// Print the finish text
	std::cout << "Finished URL Test." << std::endl;
	std::cout << "-------------------------------------------" << std::endl;
	
}