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

#include <HttpTest.hpp>
#include <Bit/Network/Http.hpp>
#include <Bit/Network/TcpSocket.hpp>
#include <fstream>
#include <Bit/System/MemoryLeak.hpp>

// Constructor
HttpTest::HttpTest( ) :
	Test( )
{
}

// Virtual functions
void HttpTest::Run( std::ostream & p_Trace )
{
	std::cout << "-------------------------------------------" << std::endl;
	std::cout << "Starting HTTP test." << std::endl;

	// Send a request to google.com
	Bit::Http http;
	Bit::Http::Request request( Bit::Http::Get, "/wikipedia/commons/thumb/8/8d/Greater_coat_of_arms_of_Sweden.svg/527px-Greater_coat_of_arms_of_Sweden.svg.png" );
	const std::string host = "upload.wikimedia.org";
	request.SetField( "Host", host );
	Bit::Http::Response response;

	TestAssert( http.SendRequest( request, response, Bit::Address( host ) ) == true );
	TestAssert( response.GetStatusCode( ) == Bit::Http::Ok );

	// Save the file
	std::ofstream fout( "httpDownload.png", std::ofstream::binary );
	if( fout.is_open( ) == false )
	{
		return;
	}

	fout.write( response.GetBody( ).c_str( ), response.GetBody( ).size( ) );

	fout.close( );
	
	// Print the finish text
	std::cout << "Finished HTTP Test." << std::endl;
	std::cout << "-------------------------------------------" << std::endl;
	
}