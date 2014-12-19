/***************************************************************************
 *   This file is part of xosc                                   *
 *                                                                         *
 *   Copyright (C) 2013 by Marije Baalman                                  *
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

#include "xosc.h"
#include "xoschost.h"
#include "xoscclient.h"

#include "lo_extensions.h"

// using namespace XOsc;

namespace XOsc {

XOscTag::XOscTag( string tag )
{
  originSet = false;
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
    originSet = true;
    host->addTag( tagname );
}

bool XOscTag::compareOrigin( lo_address addr ){
  if ( originSet ){
    return lo_address_issame( addr, origin->getAddress() );
  }
  return false;
}

bool XOscTag::hasOrigin(){
//   return (origin != NULL);
  return originSet;
}

void XOscTag::setServer( XOscServer * serv ){
    server = serv;
}

XOscServer * XOscTag::getServer(){
    return server;
}

lo_message XOscTag::getTagInfoMsg(){
  lo_message msg = lo_message_new();
  lo_message_add_string( msg, tagname.c_str() );

  if ( originSet ){
    lo_address hostAddress = origin->getAddress();
  
    lo_message_add_string( msg, lo_address_get_hostname( hostAddress ) );
    lo_message_add_string( msg, lo_address_get_port( hostAddress ) );
    lo_message_add_string( msg, origin->getName().c_str() );
  } else {
    lo_message_add_string( msg, "" );
    lo_message_add_string( msg, "" );
    lo_message_add_string( msg, "" );
  }
  return msg;  
}

void XOscTag::sendTagInfo( lo_address target ){

  lo_message msg = getTagInfoMsg();

  server->sendMessage( target, "/XOSC/info/tag", msg );
  
  lo_message_free( msg );
}

lo_message XOscTag::getSingleConnectionInfoMsg( XOscClient * client, bool connected ){
  lo_address clientAddress = client->getAddress();

  lo_message msg = lo_message_new();
  lo_message_add_string( msg, tagname.c_str() );  

  if ( originSet ){
    lo_address hostAddress = origin->getAddress();
  
    lo_message_add_string( msg, lo_address_get_hostname( hostAddress ) );
    lo_message_add_string( msg, lo_address_get_port( hostAddress ) );
    lo_message_add_string( msg, origin->getName().c_str() );
  } else {
    lo_message_add_string( msg, "" );
    lo_message_add_string( msg, "" );
    lo_message_add_string( msg, "" );
  }

  lo_message_add_string( msg, lo_address_get_hostname( clientAddress ) );
  lo_message_add_string( msg, lo_address_get_port( clientAddress ) );
  lo_message_add_string( msg, client->getName().c_str() );
  
  if ( connected )
    lo_message_add_true( msg );
  else
    lo_message_add_false( msg );
  
  return msg;
}

void XOscTag::sendSingleConnectionInfo( XOscClient * client, lo_address target, bool connected ){
  lo_message msg = getSingleConnectionInfoMsg( client, connected );
  
  server->sendMessage( target, "/XOSC/info/connection/tag", msg );
  
  lo_message_free( msg ); 
}

bool XOscTag::sendConnectionInfo( lo_address target ){
  clientAddrMap::const_iterator end = subscribers.end(); 
  for (clientAddrMap::const_iterator it = subscribers.begin(); it != end; ++it) {
    sendSingleConnectionInfo( it->second, target );
  }
  return (subscribers.size() > 0);
}

bool XOscTag::hasSubscriptions( ){
  bool ret;
  if ( originSet ){
      ret = origin->hasSubscriptions();
  }
  return (subscribers.size() > 0) || ret;
}

void XOscTag::addSubscription( XOscClient * client ){
  subscribers.insert( make_pair(client->getPortAddrInt(), client) );
}

void XOscTag::removeSubscription( XOscClient * client ){
  clientAddrMap::iterator iter = subscribers.find( client->getPortAddrInt() );
  if ( iter != subscribers.end() ){
    // iter->second free
    subscribers.erase( iter );
  }
}

void XOscTag::forwardMsgToSubscribers( const char * path, lo_message msg ){
  //   lo_message msg = server->getMessage( types, argv, argc );    
  clientAddrMap::const_iterator end = subscribers.end(); 
  for (clientAddrMap::const_iterator it = subscribers.begin(); it != end; ++it) {
      server->sendMessage( it->second->getAddress(), path, msg );
  }
  origin->sendMessageToSubscribers( server, path, msg );
}

int XOscTag::messageHandler( handlerArgs )
{
  
  lo_message msg = (lo_message) data;
  lo_address addr = lo_message_get_source( msg );
 
  XOscTag * tag = (XOscTag *) user_data;
  XOscServer * server = tag->getServer();
  if ( server->postDebug ){
    cout << "[XOscTag::tag_message] " + server->getContent( path, types, argv, argc ) << "\n";
  }
  if ( !tag->compareOrigin( addr ) ){
    return 1; // process generic handler
  }
  
  tag->forwardMsgToSubscribers( path, msg );
 
//   //   lo_message msg = server->getMessage( types, argv, argc );    
//   clientAddrMap::const_iterator end = tag->subscribers.end(); 
//   for (clientAddrMap::const_iterator it = tag->subscribers.begin(); it != end; ++it) {
//       server->sendMessage( it->second->getAddress(), path, msg );
//   }
  //FIXME:
  //   tag->origin->sendMessageToSubscribers( server, path, msg );
//   lo_message_free( msg );
  return 0;
}

}
