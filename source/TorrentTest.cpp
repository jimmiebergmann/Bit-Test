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

#include <TorrentTest.hpp>
#include <Bit/Network/Torrent.hpp>
#include <Bit/System/MemoryLeak.hpp>

// Constructor
TorrentTest::TorrentTest( ) :
	Test( )
{
}

// Virtual functions
void TorrentTest::Run( std::ostream & p_Trace )
{
	std::cout << "-------------------------------------------" << std::endl;
	std::cout << "Starting Torrent test." << std::endl;

	// Assert the torrent file reading
	Bit::Torrent torrent;
	TestAssert( torrent.ReadTorrentFile( "ubuntu.torrent" ) == true );
	TestAssert( torrent.GetTrackerCount( ) > 0 );

	// Assert the tracker
	Bit::Torrent::Tracker & tracker = torrent.GetTracker( 0 );
	Bit::Torrent::Tracker::Response response;
	TestAssert( tracker.SendRequest( response, torrent ) == true );

	// Assert the response
	TestAssert( response.GetPeerCount( ) > 0 );

	// Assert the peer
	Bit::Torrent::Peer & peer = response.GetPeer( 0 );
	

	// Print the finish text
	std::cout << "Finished Torrent Test." << std::endl;
	std::cout << "-------------------------------------------" << std::endl;
	
}