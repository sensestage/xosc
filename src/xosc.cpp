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

#include <cstring>

#include "lo_extensions.h"

// #include "xosctypes.h"

#include "xoscclient.h"
#include "xoschost.h"
#include "xosctag.h"
#include "xosc.h"


using namespace std;

namespace XOsc {

int XOscServer::registerClientHandler( handlerArgs )
{
  lo_message msg = (lo_message) data;
  lo_address addr = lo_message_get_source( msg );
  XOscServer* server = ( XOscServer* ) user_data;
  
  if ( server->postDebug ){
 	cout << "[XOscServer:client register]: " + server->getContent( path, types, argv, argc ) + "from:" + (string)( lo_address_get_hostname( addr) ) + (string)( lo_address_get_port( addr ) ) + "\n";
  }
  
  lo_address newaddr = lo_address_create_from( lo_address_get_hostname( addr ), argv[0]->i  );
//   string str( argv[2]->s, strnlen( argv[2]->s, 127 ) );
  bool res = server->registerClient( newaddr, argv[0]->i, (string) &argv[1]->s );
  server->sendConfirmation( newaddr, "/XOSC/register/client", res );
  return 0;
}

int XOscServer::registerOtherClientHandler( handlerArgs )
{
  // TODO: return port should be given
  lo_message msg = (lo_message) data;
  lo_address addr = lo_message_get_source( msg );
  XOscServer* server = ( XOscServer* ) user_data;
  
  if ( server->postDebug ){
 	cout << "[XOscServer:client register]: " + server->getContent( path, types, argv, argc ) + "from:" + (string)( lo_address_get_hostname( addr) ) + (string)( lo_address_get_port( addr ) ) + "\n";
  }
  
//  lo_address newaddr = lo_address_create_from( lo_address_get_hostname( addr ), argv[0]->i  );
  lo_address newaddr = lo_address_create_from( &argv[1]->s, argv[2]->i  );
  lo_address retaddr = lo_address_create_from( lo_address_get_hostname( addr ), argv[0]->i  );
//   string str( argv[2]->s, strnlen( argv[2]->s, 127 ) );
  bool res = server->registerClient( newaddr, argv[2]->i, (string) &argv[3]->s );
  server->sendConfirmation( retaddr, "/XOSC/register/client", res );
  lo_address_free( retaddr );
  return 0;
}

int XOscServer::registerHostHandler( handlerArgs )
{
  lo_message msg = (lo_message) data;
  lo_address addr = lo_message_get_source( msg );
  XOscServer* server = ( XOscServer* ) user_data;
    
  if ( server->postDebug ){
 	cout << "[XOscServer:host register]: " + server->getContent( path, types, argv, argc ) + "from:" + (string)(lo_address_get_hostname( addr) ) + (string) (lo_address_get_port( addr ) ) << "\n";
  }
  lo_address newaddr = lo_address_create_from( lo_address_get_hostname( addr ), argv[0]->i  );
  bool res = server->registerHost( newaddr, (string) &argv[1]->s );
  server->sendConfirmation( newaddr, "/XOSC/register/host", res );
  return 0;
}

int XOscServer::registerOtherHostHandler( handlerArgs )
{
  // TODO: return port should be given
  lo_message msg = (lo_message) data;
  lo_address addr = lo_message_get_source( msg );
  XOscServer* server = ( XOscServer* ) user_data;
    
  if ( server->postDebug ){
 	cout << "[XOscServer:host register]: " + server->getContent( path, types, argv, argc ) + "from:" + (string)(lo_address_get_hostname( addr) ) + (string) (lo_address_get_port( addr ) ) << "\n";
  }
  lo_address newaddr = lo_address_create_from( &argv[1]->s, argv[2]->i  );
  lo_address retaddr = lo_address_create_from( lo_address_get_hostname( addr ), argv[0]->i  );

  bool res = server->registerHost( newaddr, (string) &argv[3]->s );
  server->sendConfirmation( retaddr, "/XOSC/register/host", res );
  lo_address_free( retaddr );
  return 0;
}

// int XOscServer::unregisterClientHandler( handlerArgs )
// {
//   lo_address addr = lo_message_get_source( msg );
//   
//   if ( server->postDebug ){
//  	cout << "[XOscServer:client unregister]: " + server->getContent( path, types, argv, argc ) + "from:", lo_address_get_hostname( addr) + lo_address_get_port( addr ) );
// 	<< "\n";
//   }
//   
//   lo_address newaddr = lo_address_create_from( lo_address_get_hostname( addr ), argv[1]->i  );
//   res = unregisterClient( newaddr, argv[1]->i, string (argv[2]->s ) );
//   sendConfirmation( newaddr, "/XOSC/unegister/client", res );
//   return 0;
// }


int XOscServer::queryTagsHandler( handlerArgs )
{
  lo_message msg = (lo_message) data;
  lo_address addr = lo_message_get_source( msg );
  XOscServer* server = ( XOscServer* ) user_data;
  
    if ( server->postDebug )
    	cout << "[XOscServer::queryTags] " + server->getContent( path, types, argv, argc ) << "\n";

  lo_address newaddr = lo_address_create_from( lo_address_get_hostname( addr ), argv[0]->i  );
    
  // TODO: send back info about available tags
    server->sendTagInfo( newaddr ); // TODO: how to retrieve origin address?
    lo_address_free( newaddr );
    return 0;
}

int XOscServer::queryConnectionsTagHandler( handlerArgs )
{
  lo_message msg = (lo_message) data;
  lo_address addr = lo_message_get_source( msg );
  XOscServer* server = ( XOscServer* ) user_data;
  
    if ( server->postDebug )
    	cout << "[XOscServer::queryConnectionsTag] " + server->getContent( path, types, argv, argc ) << "\n";

  lo_address newaddr = lo_address_create_from( lo_address_get_hostname( addr ), argv[0]->i  );
        
  // TODO: send back info about existing connections
    server->sendConnectionTagInfo( newaddr, &argv[1]->s ); // TODO: how to retrieve origin address?
    lo_address_free( newaddr );
    return 0;
}

int XOscServer::queryConnectionsHandler( handlerArgs )
{
  lo_message msg = (lo_message) data;
  lo_address addr = lo_message_get_source( msg );
  XOscServer* server = ( XOscServer* ) user_data;
  
    if ( server->postDebug )
    	cout << "[XOscServer::queryConnections] " + server->getContent( path, types, argv, argc ) << "\n";

  lo_address newaddr = lo_address_create_from( lo_address_get_hostname( addr ), argv[0]->i  );
        
  // TODO: send back info about existing connections
    server->sendConnectionInfo( newaddr ); // TODO: how to retrieve origin address?
    lo_address_free( newaddr );
    return 0;
}

int XOscServer::registerWatchHandler( handlerArgs )
{
  lo_message msg = (lo_message) data;
  lo_address addr = lo_message_get_source( msg );
  XOscServer* server = ( XOscServer* ) user_data;

  if ( server->postDebug )
    	cout << "[XOscServer::registerWatch] " + server->getContent( path, types, argv, argc ) << "\n";

  lo_address newaddr = lo_address_create_from( lo_address_get_hostname( addr ), argv[0]->i  );
  bool res = server->registerWatcher( newaddr, argv[0]->i );
  server->sendConfirmation( newaddr, "/XOSC/register/watch", res );
    
    return 0;
}

int XOscServer::unregisterWatchHandler( handlerArgs )
{
  lo_message msg = (lo_message) data;
  lo_address addr = lo_message_get_source( msg );
  XOscServer* server = ( XOscServer* ) user_data;

  if ( server->postDebug )
    	cout << "[XOscServer::unregisterWatch] " + server->getContent( path, types, argv, argc ) << "\n";
    
  lo_address newaddr = lo_address_create_from( lo_address_get_hostname( addr ), argv[0]->i  );
  bool res = server->unregisterWatcher( newaddr, argv[0]->i );
  server->sendConfirmation( newaddr, "/XOSC/unregister/watch", res );
    return 0;
}

int XOscServer::subscribeHandler( handlerArgs )
{
  lo_message msg = (lo_message) data;
  lo_address addr = lo_message_get_source( msg );
  XOscServer* server = ( XOscServer* ) user_data;
  if ( server->postDebug )
     cout << "[XOscServer::subscribe] " + server->getContent( path, types, argv, argc ) << "\n";


    // TODO: subscribe the client to all tags
	// - if no subscriptions yet, create a responder for the tag
	// - subscribe this client
	// - if we have connection subscriptions, inform about the new connection
	// - send confirmation
    return 0;
}

int XOscServer::unsubscribeHandler( handlerArgs )
{
  lo_message msg = (lo_message) data;
  lo_address addr = lo_message_get_source( msg );
  XOscServer* server = ( XOscServer* ) user_data;

  if ( server->postDebug )
    cout << "[XOscServer::unsubscribe] " + server->getContent( path, types, argv, argc ) << "\n";


    // TODO: unsubscribe the client to all tags
	// - if no subscriptions left, remove responder for the tag
	// - unsubscribe this client
	// - if we have connection subscriptions, inform about the new connection
	// - send confirmation
    return 0;
}

int XOscServer::subscribeHostHandler( handlerArgs )
{ 
  lo_message msg = (lo_message) data;
  lo_address addr = lo_message_get_source( msg );
  XOscServer* server = ( XOscServer* ) user_data;

  if ( server->postDebug )
    cout << "[XOscServer::subscribeHost] " + server->getContent( path, types, argv, argc ) << "\n";
  
  // TODO
}

int XOscServer::subscribeHostnameHandler( handlerArgs )
{ 
  lo_message msg = (lo_message) data;
  lo_address addr = lo_message_get_source( msg );
  XOscServer* server = ( XOscServer* ) user_data;

  if ( server->postDebug )
    cout << "[XOscServer::subscribeNameHost] " + server->getContent( path, types, argv, argc ) << "\n";
  
  // TODO
}

int XOscServer::unsubscribeHostHandler( handlerArgs )
{ 
  lo_message msg = (lo_message) data;
  lo_address addr = lo_message_get_source( msg );
  XOscServer* server = ( XOscServer* ) user_data;

  if ( server->postDebug )
    cout << "[XOscServer::unsubscribeHost] " + server->getContent( path, types, argv, argc ) << "\n";
  
  // TODO
}

int XOscServer::unsubscribeHostnameHandler( handlerArgs )
{ 
  lo_message msg = (lo_message) data;
  lo_address addr = lo_message_get_source( msg );
  XOscServer* server = ( XOscServer* ) user_data;

  if ( server->postDebug )
    cout << "[XOscServer::unsubscribeNameHost] " + server->getContent( path, types, argv, argc ) << "\n";
  
  // TODO
}

int XOscServer::connectHostHandler( handlerArgs )
{ 
  lo_message msg = (lo_message) data;
  lo_address addr = lo_message_get_source( msg );
  XOscServer* server = ( XOscServer* ) user_data;

  if ( server->postDebug )
    cout << "[XOscServer::connectHost] " + server->getContent( path, types, argv, argc ) << "\n";
  
  // TODO
}

int XOscServer::disconnectHostHandler( handlerArgs )
{ 
  lo_message msg = (lo_message) data;
  lo_address addr = lo_message_get_source( msg );
  XOscServer* server = ( XOscServer* ) user_data;

  if ( server->postDebug )
    cout << "[XOscServer::disconnectHost] " + server->getContent( path, types, argv, argc ) << "\n";
  
  // TODO
}

int XOscServer::connectHostnameHandler( handlerArgs )
{ 
  lo_message msg = (lo_message) data;
  lo_address addr = lo_message_get_source( msg );
  XOscServer* server = ( XOscServer* ) user_data;

  if ( server->postDebug )
    cout << "[XOscServer::connectNameHost] " + server->getContent( path, types, argv, argc ) << "\n";
  
  // TODO
}

int XOscServer::disconnectHostnameHandler( handlerArgs )
{ 
  lo_message msg = (lo_message) data;
  lo_address addr = lo_message_get_source( msg );
  XOscServer* server = ( XOscServer* ) user_data;

  if ( server->postDebug )
    cout << "[XOscServer::disconnectNameHost] " + server->getContent( path, types, argv, argc ) << "\n";
  
  // TODO
}

int XOscServer::connectHostnameTagHandler( handlerArgs )
{ 
  lo_message msg = (lo_message) data;
  lo_address addr = lo_message_get_source( msg );
  XOscServer* server = ( XOscServer* ) user_data;

  if ( server->postDebug )
    cout << "[XOscServer::connectNameHostTag] " + server->getContent( path, types, argv, argc ) << "\n";
  
  // TODO
}

int XOscServer::disconnectHostnameTagHandler( handlerArgs )
{ 
  lo_message msg = (lo_message) data;
  lo_address addr = lo_message_get_source( msg );
  XOscServer* server = ( XOscServer* ) user_data;

  if ( server->postDebug )
    cout << "[XOscServer::disconnectNameHostTag] " + server->getContent( path, types, argv, argc ) << "\n";
  
  // TODO
}

int XOscServer::connectHostnameHostHandler( handlerArgs )
{ 
  lo_message msg = (lo_message) data;
  lo_address addr = lo_message_get_source( msg );
  XOscServer* server = ( XOscServer* ) user_data;

  if ( server->postDebug )
    cout << "[XOscServer::connectNameHostHost] " + server->getContent( path, types, argv, argc ) << "\n";
  
  // TODO
}

int XOscServer::disconnectHostnameHostHandler( handlerArgs )
{ 
  lo_message msg = (lo_message) data;
  lo_address addr = lo_message_get_source( msg );
  XOscServer* server = ( XOscServer* ) user_data;

  if ( server->postDebug )
    cout << "[XOscServer::disconnectNameHostHost] " + server->getContent( path, types, argv, argc ) << "\n";
  
  // TODO
}

int XOscServer::connectHostnameHostnameHandler( handlerArgs )
{ 
  lo_message msg = (lo_message) data;
  lo_address addr = lo_message_get_source( msg );
  XOscServer* server = ( XOscServer* ) user_data;

  if ( server->postDebug )
    cout << "[XOscServer::connectNameHostHostname] " + server->getContent( path, types, argv, argc ) << "\n";
  
  // TODO
}

int XOscServer::disconnectHostnameHostnameHandler( handlerArgs )
{ 
  lo_message msg = (lo_message) data;
  lo_address addr = lo_message_get_source( msg );
  XOscServer* server = ( XOscServer* ) user_data;

  if ( server->postDebug )
    cout << "[XOscServer::disconnectNameHostHostname] " + server->getContent( path, types, argv, argc ) << "\n";
  
  // TODO
}


int XOscServer::connectTagHandler( handlerArgs )
{ 
  lo_message msg = (lo_message) data;
  lo_address addr = lo_message_get_source( msg );
  XOscServer* server = ( XOscServer* ) user_data;

  if ( server->postDebug )
    cout << "[XOscServer::connectTag] " + server->getContent( path, types, argv, argc ) << "\n";
  
  // TODO
}

int XOscServer::disconnectTagHandler( handlerArgs )
{ 
  lo_message msg = (lo_message) data;
  lo_address addr = lo_message_get_source( msg );
  XOscServer* server = ( XOscServer* ) user_data;

  if ( server->postDebug )
    cout << "[XOscServer::disconnectTag] " + server->getContent( path, types, argv, argc ) << "\n";
  
  // TODO
}


int XOscServer::subscribeTagHandler( handlerArgs )
{ 
  lo_message msg = (lo_message) data;
  lo_address addr = lo_message_get_source( msg );
  XOscServer* server = ( XOscServer* ) user_data;

  if ( server->postDebug )
    cout << "[XOscServer::subscribeTag] " + server->getContent( path, types, argv, argc ) << "\n";

    // TODO: subscribe the client to the tags
	// - if client does not yet exist, create a client
  lo_address newaddr = lo_address_create_from( lo_address_get_hostname( addr ), argv[0]->i  );
  XOscClient * myclient = server->clientExists( argv[0]->i, newaddr );
  if ( myclient == NULL ){
    myclient = server->createNewClient( argv[0]->i, newaddr );
  }
	// - if tag does not yet exist, create a tag, and a responder, even if it has no origin yet
//FIXME   
  string tagname = &argv[1]->s;
  XOscTag * tag = server->tagExists( tagname );
  if ( tag == NULL ){
      tag = server->createNewTag( tagname );
  }
	// - if no subscriptions yet, create a responder for the tag
  if ( !tag->hasSubscriptions() ){
      server->createMethod( tag );
  }
	// - subscribe this client
  tag->addSubscription( myclient );
	// - if we have connection subscriptions, inform about the new connection
  server->sendWatchersConnectionInfo( tag, myclient, true );
	// - send confirmation
  server->sendConfirmation( newaddr, "/XOSC/subscribe/tag", true );
    return 0;
}

int XOscServer::unsubscribeTagHandler( handlerArgs )
{
  lo_message msg = (lo_message) data;
  lo_address addr = lo_message_get_source( msg );
  XOscServer* server = ( XOscServer* ) user_data;
  
  if ( server->postDebug )
    cout << "[XOscServer::unsubscribeTag] " + server->getContent( path, types, argv, argc ) << "\n";

  lo_address newaddr = lo_address_create_from( lo_address_get_hostname( addr ), argv[0]->i  );
  XOscClient * myclient = server->clientExists( argv[0]->i, newaddr );
  if ( myclient == NULL ){
    server->sendConfirmation( newaddr, "/XOSC/unsubscribe/tag", true ); // did not succeed, as this was not a client yet
    return 0;
  }
  string tagname = &argv[1]->s;
  XOscTag * tag = server->tagExists( tagname );
  if ( tag == NULL ){
    // tag did not exist, so we could not be subscribed to it;
    server->sendConfirmation( newaddr, "/XOSC/unsubscribe/tag", true ); // did not succeed, as this was not a client yet
    return 0;
  }
  // - if we have connection subscriptions, inform about the lost connection
  server->sendWatchersConnectionInfo( tag, myclient, false );
  tag->removeSubscription( myclient );
  // tag has no subscriptions left, so remove method
  if ( !tag->hasSubscriptions() ){
    server->deleteMethod( tag );
//     return 0;
  }
	// - send confirmation
  server->sendConfirmation( newaddr, "/XOSC/unsubscribe/tag", true );
  return 0;
}


int XOscServer::genericHandler( handlerArgs )
{
  lo_message msg = (lo_message) data;
  lo_address addr = lo_message_get_source( msg );
  lo_address newaddr = lo_address_copy( addr );
  XOscServer* server = ( XOscServer* ) user_data;

  string tag = string( path );
  
  if ( server->postDebug )
    cout << "[XOscServer::genericHandler] arbitrary osc tag: " + server->getContent( path, types, argv, argc ) << "\n";
  
  // TODO: 
  //   - store some more info about it? (types?)
  XOscTag * xtag = server->tagExists( tag );
  if ( xtag != NULL ){
     if ( !server->tagCheckAndChangeOrigin( xtag, newaddr ) ){
        server->sendWatchersTagInfo( xtag );
     } // else, no changes
  } else { // else, create a new tag
      server->createNewTag( tag, newaddr );
  }
  return 1;
}

// ------------- end basic message interface -----------
  
  
XOscServer::XOscServer( const char *port ) : OSCServer( port )
{
    postDebug = false;
}

void XOscServer::debug( bool onoff ){
     postDebug = onoff;
     if ( postDebug ){
	cout << "debug posting on\n";
     } else {
       cout << "debug posting off\n";
     }
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

	addMethod( "/XOSC/register/client",  "is", registerClientHandler, this );    // port, name
	addMethod( "/XOSC/register/client",  "isis", registerOtherClientHandler, this );    // ipaddress, port, name
// 	addMethod( "/XOSC/unregister/client", "is", unregisterClientHandler, this ); // port, name

	addMethod( "/XOSC/register/host",  "is", registerHostHandler, this );    // port (to send confirm to), name
	addMethod( "/XOSC/register/host",  "isis", registerOtherHostHandler, this );    // ip address, port, name
// 	addMethod( "/XOSC/unregister/host", "is", unregisterHostHandler, this ); // port (to send confirm to), name
	
	addMethod( "/XOSC/register/watch",   "i",  registerWatchHandler, this ); // port to send back to
	addMethod( "/XOSC/unregister/watch",   "i",  unregisterWatchHandler, this ); // port to send back to

	addMethod( "/XOSC/query/tags",  "i",   queryTagsHandler, this ); // port to send back to
	addMethod( "/XOSC/query/tag/connections", "is",   queryConnectionsTagHandler, this ); // port to send back to, tag to query
	addMethod( "/XOSC/query/connections", "i",   queryConnectionsHandler, this ); // port to send back to

	addMethod( "/XOSC/subscribe/tag",   "is",  subscribeTagHandler, this ); // port to send back to, tag
	addMethod( "/XOSC/subscribe/host",   "isi",  subscribeHostHandler, this ); // port to send back to, host ip, host port to connect to
	addMethod( "/XOSC/subscribe/host",   "is",  subscribeHostnameHandler, this ); // port to send back to, host name

	addMethod( "/XOSC/unsubscribe/tag",   "is",  unsubscribeTagHandler, this ); // port to send back to, tag
	addMethod( "/XOSC/unsubscribe/host",   "isi",  unsubscribeHostHandler, this ); // port to send back to, host ip, host port to connect to
	addMethod( "/XOSC/unsubscribe/host",   "is",  unsubscribeHostnameHandler, this ); // port to send back to, host name

	// all tags
	addMethod( "/XOSC/subscribe",   "i",  subscribeHandler, this ); // port to send back to
	addMethod( "/XOSC/unsubscribe",   "i",  unsubscribeHandler, this ); // port to send back to

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

void XOscServer::sendConfirmation( lo_address targ, const char *path, bool success ){
    lo_message msg = lo_message_new();
    if ( success )
      lo_message_add_true( msg );
    else
      lo_message_add_false( msg );
    sendMessage( targ, path, msg );
    lo_message_free( msg );
}

bool XOscServer::registerClient( lo_address clientAddr, int port, string name ){
  if ( clientExistsAndChangeName( port, clientAddr, name ) ){
      return true; // was already registered
  }
  XOscClient * client = createNewClient( port, clientAddr, name );
  sendWatchersClientInfo( client );
  return true;
}

bool XOscServer::registerHost( lo_address hostAddr, string name ){
  
  if ( hostExistsAndChangeName( hostAddr, name ) ){
      return true; // was already registered
  }
  XOscHost * host = createNewHost( hostAddr, name );
  sendWatchersHostInfo( host );
  return true;
}

bool XOscServer::registerWatcher( lo_address clientAddr, int port ){
  if ( watcherExists( port, clientAddr ) ){
      return true; // was already registered
  }
  createNewWatcher( port, clientAddr );
  return true;
}

bool XOscServer::unregisterWatcher( lo_address clientAddr, int port ){
  if ( watcherExists( port, clientAddr ) ){
      removeWatcher( port );
      return true;
  }
  return false;
}


void XOscServer::sendTagInfo( lo_address addr ){
    // TODO: Iterate over tags and call sendTagInfo on it
  tagMap::const_iterator end = oscTags.end(); 
  for (tagMap::const_iterator it = oscTags.begin(); it != end; ++it) {
      it->second->sendTagInfo( addr );
  }
//   
}

void XOscServer::sendConnectionInfo( lo_address  addr ){
    // TODO: iterate over tags, and send which clients are connected
  tagMap::const_iterator end = oscTags.end(); 
  for (tagMap::const_iterator it = oscTags.begin(); it != end; ++it) {
      it->second->sendConnectionInfo( addr );
  }  
}

void XOscServer::sendConnectionTagInfo( lo_address  addr, string tag ){
   XOscTag * xtag = tagExists( tag );
   if ( xtag != NULL ){
      xtag->sendConnectionInfo( addr );
   }
}

void XOscServer::sendWatchersClientInfo( XOscClient * client ){
  lo_message msg = client->getClientInfoMsg();    
  clientMap::const_iterator end = oscWatchers.end(); 
  for (clientMap::const_iterator it = oscWatchers.begin(); it != end; ++it) {
    sendMessage( it->second->getAddress(), "/XOSC/info/client", msg );  
  }  
  lo_message_free( msg );
}

void XOscServer::sendWatchersHostInfo( XOscHost * host ){
  lo_message msg = host->getHostInfoMsg();    
  clientMap::const_iterator end = oscWatchers.end(); 
  for (clientMap::const_iterator it = oscWatchers.begin(); it != end; ++it) {
    sendMessage( it->second->getAddress(), "/XOSC/info/host", msg );  
  }  
  lo_message_free( msg );
}

void XOscServer::sendWatchersTagInfo( XOscTag * xtag ){
  lo_message msg = xtag->getTagInfoMsg();
  clientMap::const_iterator end = oscWatchers.end(); 
  for (clientMap::const_iterator it = oscWatchers.begin(); it != end; ++it) {
//     xtag->sendTagInfo( it->second->getAddress() );
    sendMessage( it->second->getAddress(), "/XOSC/info/tag", msg );  
  }
  lo_message_free( msg );
}

void XOscServer::sendWatchersConnectionInfo( XOscTag * xtag, XOscClient * client, bool gotconnected ){
  lo_message msg = xtag->getSingleConnectionInfoMsg( client, gotconnected );
  clientMap::const_iterator end = oscWatchers.end(); 
  for (clientMap::const_iterator it = oscWatchers.begin(); it != end; ++it) {
    sendMessage( it->second->getAddress(), "/XOSC/info/connection", msg );  
//     xtag->sendSingleConnectionInfo( client, it->second->getAddress(), gotconnected );
  }
  lo_message_free( msg );
}

XOscTag * XOscServer::tagExists( string name ){
  tagMap::iterator iter = oscTags.find( name );
  if ( iter != oscTags.end() ){
    return iter->second;
  }
  return NULL;
}

bool XOscServer::tagCheckAndChangeOrigin( XOscTag * xtag, lo_address originAddress ){
    if ( xtag->hasOrigin() ){
	if ( xtag->compareOrigin( originAddress ) ){
	  // all good, early return
	  return true;
	}
    }
    XOscHost * myhost;
    // tag had no origin yet, or it was different from what was known, so create one and add it to the list
    myhost = getHost( originAddress );
    xtag->setOrigin( myhost );
    return false;
}

void XOscServer::createNewTag( string name, lo_address originAddress ){
  // TODO: create a new tag instance, and add it to the map
  XOscHost * myhost;
  XOscTag * newtag = new XOscTag( name );
  if ( hostExists( originAddress ) ){
      hostMap::iterator iter = oscHosts.find( lo_address_get_port_as_int( originAddress ) );
      myhost = iter->second;
  } else {
      myhost = createNewHost( originAddress );
  }
  newtag->setOrigin( myhost );
  newtag->setServer( this );
  oscTags.insert( make_pair( name, newtag ) );
  sendWatchersTagInfo( newtag );
}

XOscTag * XOscServer::createNewTag( string name ){
  // TODO: create a new tag instance, and add it to the map
  XOscTag * newtag = new XOscTag( name );
  newtag->setServer( this );
  oscTags.insert( make_pair( name, newtag ) );
  sendWatchersTagInfo( newtag );
  return newtag;
}

XOscClient * XOscServer::watcherExists( int port, lo_address addr ){
  clientMap::iterator iter = oscWatchers.find( port );
  if ( iter != oscWatchers.end() ){
    if ( lo_address_issame( addr, iter->second->getAddress() ) ){
      return iter->second;
// 	return true;
    }
  }
  return NULL;
}

XOscClient * XOscServer::createNewWatcher( int port, lo_address addr ){
  XOscClient * newclient = new XOscClient( addr );
  oscWatchers.insert( make_pair( port, newclient) );
  return newclient;
}

void XOscServer::removeWatcher( int port ){
  clientMap::iterator iter = oscWatchers.find( port );
  if ( iter != oscWatchers.end() ){
    oscWatchers.erase( iter );
  }
}

XOscClient * XOscServer::clientExists( int port, lo_address addr ){
  clientMap::iterator iter = oscClients.find( port );
  if ( iter != oscClients.end() ){
    if ( lo_address_issame( addr, iter->second->getAddress() ) ){
      return iter->second;
// 	return true;
    }
  }
  return NULL;
}

bool XOscServer::clientExistsAndChangeName( int port, lo_address addr, string name ){
  clientMap::iterator iter = oscClients.find( port );
  if ( iter != oscClients.end() ){
    if ( lo_address_issame( addr, iter->second->getAddress() ) ){
	iter->second->setName( name );
	return true;
    }
  }
  return false;
}

XOscClient * XOscServer::createNewClient( int port, lo_address addr, string name ){
  XOscClient * newclient = new XOscClient( addr );
  newclient->setName( name );
  oscClients.insert( make_pair( port, newclient) );
  return newclient;
}

XOscClient * XOscServer::createNewClient( int port, lo_address addr ){
  XOscClient * newclient = new XOscClient( addr );
//   newclient->setName( name );
  oscClients.insert( make_pair( port, newclient) );
  return newclient;
}

bool XOscServer::hostExists( lo_address addr ){
  hostMap::iterator iter = oscHosts.find( lo_address_get_port_as_int( addr ) );
  if ( iter != oscHosts.end() ){
    if ( lo_address_issame( addr, (iter->second->getAddress() ) ) ){
	return true;
    }
  }
  return false;
}


bool XOscServer::hostExistsAndChangeName( lo_address addr, string name ){
  hostMap::iterator iter = oscHosts.find( lo_address_get_port_as_int( addr ) );
  if ( iter != oscHosts.end() ){
    if ( lo_address_issame( addr, (iter->second->getAddress()) ) ){
	iter->second->setName( name );
	return true;
    }
  }
  return false;
}

XOscHost * XOscServer::createNewHost( lo_address addr, string name ){
  XOscHost * newhost = new XOscHost( addr );
  newhost->setName( name );
  oscHosts.insert( make_pair( lo_address_get_port_as_int( addr ), newhost ) );
  return newhost;
}

XOscHost * XOscServer::createNewHost( lo_address addr ){
  XOscHost * newhost = new XOscHost( addr );
  oscHosts.insert( make_pair( lo_address_get_port_as_int( addr ), newhost ) );
  return newhost;
}

XOscHost * XOscServer::getHost( lo_address addr ){
  hostMap::iterator iter = oscHosts.find( lo_address_get_port_as_int( addr ) );
  if ( iter != oscHosts.end() ){ 
    if ( lo_address_issame( addr, ( iter->second->getAddress() ) ) ){
	return iter->second;
    }
  }
  return createNewHost( addr );
}

// ------------- flexible message interface ------------

void XOscServer::createMethod( XOscTag * osctag ){
  const char *path = osctag->getTag().c_str();
  removeMethod(NULL,NULL);
  addMethod( path, NULL, osctag->messageHandler, osctag );
  addMethod( NULL, NULL, genericHandler, this );
}

void XOscServer::deleteMethod( XOscTag * osctag ){
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
