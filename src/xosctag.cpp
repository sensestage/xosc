/***************************************************************************
 *   This file is part of libdatanetwork                                   *
 *                                                                         *
 *   Copyright (C) 2009 by Marije Baalman                                  *
 *   nescivi _at_ gmail _dot_ com                                          *
 *                                                                         *
 *   This library is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License as        *
 *   published by the Free Software Foundation; either version 3 of the    *
 *   License, or (at your option) any later version.                       *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include <iostream>
#include <lo/lo.h>
#include <string>

#include "xosctag.h"
// #include "xosc.h"
// #include "xoschost.h"
// #include "xoscclient.h"

namespace XOsc {

XOscTag::XOscTag( string tag )
{
  tagname = tag;
}

XOscTag::~XOscTag()
{
}

string XOscTag::getTag(){
    return tagname;
}

void XOscTag::setOrigin( XOscHost * host ){
    origin = host;
}

void XOscTag::setServer( XOscServer * serv ){
    server = serv;
}

XOscServer * XOscTag::getServer(){
    return server;
}

void XOscTag::sendTagInfo( lo_address * target ){

  lo_message msg = lo_message_new();
  lo_message_add_string( tagname.c_str() );
  lo_address * hostAddress = host->getAddress();
  lo_message_add_string( lo_address_get_hostname( hostAddress ) );
  lo_message_add_string( lo_address_get_port( hostAddress ) );
  lo_message_add_string( host->getName().c_str() );
  
  server.sendMessage( target, "/XOSC/info/tag", msg );
  
  lo_message_free( msg );
}

void XOscTag::sendSingleConnectionInfo( XOSCClient * client, lo_address * target ){

  lo_message msg = lo_message_new();
  lo_message_add_string( tagname.c_str() );
  
  lo_address * clientAddress = client->getAddress();
  lo_message_add_string( lo_address_get_hostname( clientAddress ) );
  lo_message_add_string( lo_address_get_port(  clientAddress ) );
  lo_message_add_string( client->getName().c_str() );
  
  server.sendMessage( target, "/XOSC/info/connection", msg );
  
  lo_message_free( msg );
  
}

void XOscTag::sendConnectionInfo( lo_address * target ){
  clientMap::const_iterator end = tag->subscribers.end(); 
  for (clientMap::const_iterator it = tag->subscribers.begin(); it != end; ++it) {
    sendSingleConnectionInfo( it->second, target );
  }
}

void XOscTag::addSubscription( XOscClient * client ){
  subscribers.insert( make_pair(client->port, client) );
}

void XOscTag::removeSubscription( XOscClient * client ){
  clientMap::iterator iter = subscribers.find( client->port );
  if ( iter != subscribers.end() ){
    // iter->second free
    subscribers.erase( iter );
  }
}

int XOscTag::messageHandler( handlerArgs )
{
  XOscTag * tag = (XOscTag *) user_data;
  XOscServer * server = tag->getServer();
  if ( ( server->postDebug )
    cout << "[XOscTag::tag_message] " + server->getContent( path, types, argv, argc ) << "\n";

    // TODO: send message on to all subscribed clients
  lo_message msg = server->getMessage( types, argv, argc );    
  clientMap::const_iterator end = tag->subscribers.end(); 
  for (clientMap::const_iterator it = tag->subscribers.begin(); it != end; ++it) {
      server.sendMessage( it->second->getAddress(), path, msg );
  }
  origin->sendMessageToSubscribers( server, path, msg );
  lo_message_free( msg );
  return 0;
}

}
