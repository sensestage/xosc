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

#include "xoscclient.h"

#include "xoschost.h"

// #include "xosctag.h"
// #include "xosc.h"

using namespace XOsc;

namespace XOsc {

XOscHost::XOscHost( lo_address host )
{
  hostAddress = host;
  name = "";
}

XOscHost::~XOscHost()
{
}

void XOscHost::setServer( XOscServer * serv ){
    server = serv;
}

XOscServer * XOscHost::getServer(){
    return server;
}


lo_address XOscHost::getAddress(){
     return hostAddress;
}


void XOscHost::setName( string myname ){
    name = myname;
}

string XOscHost::getName(){
    return name;
}

void XOscHost::unsetName(){
    name = "";
}

lo_message XOscHost::getHostInfoMsg(){
    lo_message msg = lo_message_new();
    lo_message_add_string( msg, lo_address_get_hostname( hostAddress ) );
    lo_message_add_string( msg, lo_address_get_port( hostAddress ) );
    lo_message_add_string( msg, name.c_str() );
    return msg;
}

lo_message XOscHost::getSingleConnectionInfoMsg( XOscClient * client, bool connected ){
  lo_address clientAddress = client->getAddress();

  lo_message msg = lo_message_new();
  
  lo_message_add_string( msg, lo_address_get_hostname( hostAddress ) );
  lo_message_add_string( msg, lo_address_get_port( hostAddress ) );
  lo_message_add_string( msg, name.c_str() );

  lo_message_add_string( msg, lo_address_get_hostname( clientAddress ) );
  lo_message_add_string( msg, lo_address_get_port( clientAddress ) );
  lo_message_add_string( msg, client->getName().c_str() );
  
  if ( connected )
    lo_message_add_true( msg );
  else
    lo_message_add_false( msg );
  
  return msg;
}


void XOscHost::sendSingleConnectionInfo( XOscClient * client, lo_address target, bool connected ){
  lo_address clientAddress = client->getAddress();
  
  lo_message msg = getSingleConnectionInfoMsg( client, connected );
  
  server->sendMessage( target, "/XOSC/info/connection/host", msg );
  
  lo_message_free( msg ); 
}

void XOscHost::sendConnectionInfo( lo_address target ){
  clientMap::const_iterator end = subscribers.end(); 
  for (clientMap::const_iterator it = subscribers.begin(); it != end; ++it) {
    sendSingleConnectionInfo( it->second, target );
  }
}

// void XOscHost::addTag( XOscTag * tag ){
//   sendingTags.insert( make_pair( tag->getTag(), tag ) );    
// }

  void XOscHost::addTag( string tagname ){
    sendingTags.insert( tagname );
  }

  tagNameList * XOscHost::getTags(){
      return &sendingTags;
  }

  void XOscHost::sendMessageToSubscribers( XOscServer * server, const char * path, lo_message msg ){
    clientMap::const_iterator end = subscribers.end(); 
    for (clientMap::const_iterator it = subscribers.begin(); it != end; ++it) {
	server->sendMessage( it->second->getAddress(), path, msg );
    }
  }

// void XOscHost::sendInfoAboutTags( lo_address * target ){
  // TODO: Iterate over tags and call sendTagInfo on it
//   tagMap::const_iterator end = sendingTags.end(); 
//   for (tagMap::const_iterator it = sendingTags.begin(); it != end; ++it) {
//       it->second->sendTagInfo( target );
//   }
// }

bool XOscHost::hasSubscriptions(){
    return subscribers.size() > 0;
}

void XOscHost::addSubscription( XOscClient * client ){
  subscribers.insert( make_pair(client->getPort(), client) );
}

void XOscHost::removeSubscription( XOscClient * client ){
  clientMap::iterator iter = subscribers.find( client->getPort() );
  if ( iter != subscribers.end() ){
    // iter->second free
    subscribers.erase( iter );
  }
}

}
