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

#include <Sha1Test.hpp>
#include <Bit/System/Sha1.hpp>
#include <fstream>
#include <Bit/System/MemoryLeak.hpp>

// Constructor
Sha1Test::Sha1Test( ) :
	Test( )
{
}

// Virtual functions
void Sha1Test::Run( std::ostream & p_Trace )
{
	std::cout << "-------------------------------------------" << std::endl;
	std::cout << "Starting Sha1 test." << std::endl;

	// Assert the sha1 hash function
	Bit::Sha1 sha1;
	sha1.Generate( "Hello world." );
	TestAssert( sha1.GetHash( ).AsHexString( false ) == "e44f3364019d18a151cab7072b5a40bb5b3e274f" );

	sha1.Generate( "kahkahajkdhajkdhajkshdjkahjkdaudhauksuadukahukdhaudhukadukask" );
	TestAssert( sha1.GetHash( ).AsHexString( false ) == "339405150806d816521c3f1da8e5186811ca1e0b" );

	sha1.Generate( "kahkahajkdhajkdhajkshdjkahjkdaudhauksuadukahukdhaudhukadukaskahsdasjdaaksdasasdasd" );
	TestAssert( sha1.GetHash( ).AsHexString( false ) == "3dccfecf5ad959e80935d0ea460c65e12ade0618" );

	sha1.Generate( "The quick brown fox jumps over the lazy dog" );
	TestAssert( sha1.GetHash( ).AsHexString( false ) == "2fd4e1c67a2d28fced849ee1bb76e7391b93eb12" );

	sha1.Generate( "The Hypertext Transfer Protocol (HTTP) is an application protocol for distributed, collaborative, hypermedia information systems.[1] HTTP is the foundation of data communication for the World Wide Web." );
	TestAssert( sha1.GetHash( ).AsHexString( false ) == "954a3883242dcc81f416be4414dafed91eb5969e" );

	// Assert a hash generation of a larger file.
	std::ifstream fin( "input/ubuntu.torrent", std::fstream::binary );
	TestAssert( fin.is_open( ) == true );
	if( fin.is_open( ) == false )
	{
		return;
	}

	// Get the file size
	fin.seekg( 0, std::fstream::end );
	const Bit::SizeType bufferSize = static_cast<Bit::SizeType>( fin.tellg( ) );
	fin.seekg( 0, std::fstream::beg );

	// Read the data
	Bit::Uint8 * pBuffer = new Bit::Uint8[ bufferSize ];
	fin.read( reinterpret_cast<char*>( pBuffer ), bufferSize );

	// Close the file
	fin.close( );

	// Hash the file data
	Bit::Sha1 sha2;
	sha2.Generate( pBuffer, bufferSize );
	TestAssert( sha2.GetHash( ).AsHexString( false ) == "94afbf3ac823523b5c35a113a0a31ab70830558b" );
		
	// Free the buffer
	delete [ ] pBuffer;	

	// Print the finish text
	std::cout << "Finished Sha1 Test." << std::endl;
	std::cout << "-------------------------------------------" << std::endl;
	
}