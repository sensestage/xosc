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

#include "datanetworkosc.h"
#include "datanetwork.h"


#include <iostream>
#include <lo/lo.h>
#include <string>

namespace XOsc {

XOscServer::XOscServer( const char *port ) : OSCServer( port )
{
	postDebug = false;
}

XOscServer::~XOscServer()
{
}

//-------------- basic message interface -----------------

void XOscServer::addBasicMethods()
{
// 	addMethod( "/ping", "is", pingHandler, this );
// 	addMethod( "/error", "ssi", errorHandler, this );
// 	addMethod( "/warn",  "ssi", warnHandler, this );

	addMethod( "/XOSC/register",  "is", registereHandler, this );    // port, name
	addMethod( "/XOSC/unregister", "is", unregistereHandler, this ); // port, name
	// about connections
	addMethod( "/XOSC/register/watch",   "i",  registerWatchHandler, this ); // port to send back to
	addMethod( "/XOSC/unregister/watch",   "i",  unregisterWatchHandler, this ); // port to send back to

	addMethod( "/XOSC/query/tags",  "i",   queryTagsHandler, this ); // port to send back to
	addMethod( "/XOSC/query/connections", "i",   queryConnectionsHandler, this ); // port to send back to
	addMethod( "/XOSC/query/connections/tag", "is",   queryConnectionsTagHandler, this ); // port to send back to, tag to query

	addMethod( "/XOSC/subscribe/tag",   "is",  subscribeTagHandler, this ); // port to send back to, tag
	addMethod( "/XOSC/subscribe/host",   "isi",  subscribeHostHandler, this ); // port to send back to, host ip, host port to connect to
	addMethod( "/XOSC/subscribe/host",   "is",  subscribeHostnameHandler, this ); // port to send back to, host name

	addMethod( "/XOSC/unsubscribe/tag",   "is",  unSubscribeTagHandler, this ); // port to send back to, tag
	addMethod( "/XOSC/unsubscribe/host",   "isi",  unSubscribeHostHandler, this ); // port to send back to, host ip, host port to connect to
	addMethod( "/XOSC/unsubscribe/host",   "is",  unSubscribeHostnameHandler, this ); // port to send back to, host name

	// all tags
	addMethod( "/XOSC/subscribe",   "i",  subscribeHandler, this ); // port to send back to
	addMethod( "/XOSC/unsubscribe",   "i",  unSubscribeHandler, this ); // port to send back to

	addMethod( "/XOSC/connect/tag",   "sis",  connectTagHandler, this ); // host ip, host port to send back to, tag
	addMethod( "/XOSC/connect/tag",   "ss",  connectHostnameTagHandler, this ); // host name to send back to, tag
	addMethod( "/XOSC/disconnect/tag",   "sis",  disconnectTagHandler, this ); // host ip, host port to send back to, tag
	addMethod( "/XOSC/disconnect/tag",   "ss",  disconnectHostnameTagHandler, this ); // host name to send back to, tag

	addMethod( "/XOSC/connect/host",   "sisi",  connectHostHandler, this ); // client host ip, client port, host ip, host port to connect to
	addMethod( "/XOSC/connect/host",   "sis",  connectHostnameHandler, this ); // client host ip, client port, host ip, host port to connect to
	addMethod( "/XOSC/connect/host",   "ssi",  connectHostnameHostHandler, this ); // client name, host ip, host port
	addMethod( "/XOSC/connect/host",   "ss",  connectHostnameHostnameHandler, this ); // client name, host name

	addMethod( "/XOSC/disconnect/host",   "sisi",  disconnectHostHandler, this ); // client host ip, client port, host ip, host port to connect to
	addMethod( "/XOSC/disconnect/host",   "sis",  disconnectHostnameHandler, this ); // client host ip, client port, host ip, host port to connect to
	addMethod( "/XOSC/disconnect/host",   "ssi",  disconnectHostnameHostHandler, this ); // client name, host ip, host port
	addMethod( "/XOSC/disconnect/host",   "ss",  disconnectHostnameHostnameHandler, this ); // client name, host name


	// The generic handler must be added last. 
	// Otherwise it would be called instead of the handlers. 
	addMethod( NULL, NULL, genericHandler, this );
}

int XOscServer::registerHandler( handlerArgs )
{
	if ( ( ( XOscServer* ) user_data )->postDebug )
 		cout << "[XOscServer:register]: " + ( ( XOscServer* ) user_data )->getContent( path, types, argv, argc ) << "\n";

  ///TODO: register the host ip, host port, with the given name
	// - send confirmation
  return 0;
}

int XOscServer::unregisterHandler( handlerArgs )
{
  if ( ( ( XOscServer* ) user_data )->postDebug )
    cout << "[XOscServer:unregistered]: " + ( ( XOscServer* ) user_data )->getContent( path, types, argv, argc ) << "\n";
  ///TODO: unregister the host ip, host port, with the given name
	// - send confirmation
  return 0;
}


int XOscServer::queryTagsHandler( handlerArgs )
{
    if ( ( ( XOscServer* ) user_data )->postDebug )
    	cout << "[XOscServer::queryTags] " + ( ( XOscServer* ) user_data )->getContent( path, types, argv, argc ) << "\n";
    
  // TODO: send back info about available tags
    ( ( XOscServer* ) user_data )->sendTagInfo( argv[0]->i ); // TODO: how to retrieve origin address?
    return 0;
}

int XOscServer::queryConnectionsHandler( handlerArgs )
{
    if ( ( ( XOscServer* ) user_data )->postDebug )
    	cout << "[XOscServer::queryConnections] " + ( ( XOscServer* ) user_data )->getContent( path, types, argv, argc ) << "\n";
    
  // TODO: send back info about existing connections
    ( ( XOscServer* ) user_data )->sendConnectionInfo( argv[0]->i ); // TODO: how to retrieve origin address?
    return 0;
}

int XOscServer::registerWatchHandler( handlerArgs )
{
    if ( ( ( XOscServer* ) user_data )->postDebug )
    	cout << "[XOscServer::registerWatch] " + ( ( XOscServer* ) user_data )->getContent( path, types, argv, argc ) << "\n";
    
  // TODO: subscribe to connections and tags info
	// - send confirmation
    
    return 0;
}

int XOscServer::unregisterWatchHandler( handlerArgs )
{
    if ( ( ( XOscServer* ) user_data )->postDebug )
    	cout << "[XOscServer::unregisterWatch] " + ( ( XOscServer* ) user_data )->getContent( path, types, argv, argc ) << "\n";
    
  // TODO: unsubscribe to connections and tags info
    	// - send confirmation
    return 0;
}

int XOscServer::subscribeHandler( handlerArgs )
{
	if ( ( ( XOscServer* ) user_data )->postDebug )
    	cout << "[XOscServer::subscribe] " + ( ( XOscServer* ) user_data )->getContent( path, types, argv, argc ) << "\n";


    // TODO: subscribe the client to all tags
	// - if no subscriptions yet, create a responder for the tag
	// - subscribe this client
	// - if we have connection subscriptions, inform about the new connection
	// - send confirmation
    return 0;
}

int XOscServer::unsubscribeHandler( handlerArgs )
{
	if ( ( ( XOscServer* ) user_data )->postDebug )
    	cout << "[XOscServer::unsubscribe] " + ( ( XOscServer* ) user_data )->getContent( path, types, argv, argc ) << "\n";


    // TODO: unsubscribe the client to all tags
	// - if no subscriptions left, remove responder for the tag
	// - unsubscribe this client
	// - if we have connection subscriptions, inform about the new connection
	// - send confirmation
    return 0;
}


int XOscServer::subscribeTagHandler( handlerArgs )
{
	if ( ( ( XOscServer* ) user_data )->postDebug )
    	cout << "[XOscServer::subscribeTag] " + ( ( XOscServer* ) user_data )->getContent( path, types, argv, argc ) << "\n";


    // TODO: subscribe the client to the tags
	// - if no subscriptions yet, create a responder for the tag
	// - subscribe this client
	// - if we have connection subscriptions, inform about the new connection
	// - send confirmation
    return 0;
}

int XOscServer::unsubscribeTagHandler( handlerArgs )
{
	if ( ( ( XOscServer* ) user_data )->postDebug )
    	cout << "[XOscServer::unsubscribeTag] " + ( ( XOscServer* ) user_data )->getContent( path, types, argv, argc ) << "\n";


    // TODO: unsubscribe the client to the tags
	// - if no subscriptions left, remove responder for the tag
	// - unsubscribe this client
	// - if we have connection subscriptions, inform about the new connection
	// - send confirmation
    return 0;
}


int XOscServer::genericHandler( handlerArgs )
{
  if ( ( ( XOscServer* ) user_data )->postDebug )
    cout << "[XOscServer::genericHandler] arbitrary osc tag: " + ( ( XOscServer* ) user_data )->getContent( path, types, argv, argc ) << "\n";
  
  // TODO: check if osctag exists in map
  //   - if not, create OSC tag and add to map
  //   - if yes, store some info about it? (host? types?)
  
  return 0;
}

// ------------- end basic message interface -----------

bool XOscServer::tagExists( ){
  // TODO: find tag, and return result
}

void XOscServer::createNewTag(  ){
  // TODO: create a new tag instance, and add it to the map
}



// ------------- flexible message interface ------------

void XOscServer::createMethod( XOscTag * osctag ){
  const char *path = osctag->getTag().c_str();
  addMethod( path, NULL, oscTag::messageHandler, oscTag );
}

void XOscServer::removeMethod( XOscTag * osctag ){
  const char *path = osctag->getTag().c_str();
  removeMethod( path, NULL );
}

//-------------- messages to the host -----------------

/*
void XOscServer::querySubscriptions()
{
	sendSimpleMessage( "/query/subscriptions" );
}

void XOscServer::setData( int id, int size, string data[] )
{
	lo_message msg = lo_message_new();
	lo_message_add_int32( msg, port );
	lo_message_add_string( msg, name.data() );
	lo_message_add_int32( msg, id );

	for (int n=0; n<size; n++)
		lo_message_add_string( msg, data[n].data() );

	sendMessage( hostAddress, "/set/data", msg );

	lo_message_free( msg );	
}
*/

//-------------- end messages to the host -----------------
}
