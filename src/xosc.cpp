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
  
  lo_address newaddr = addr;
  int port;
  if ( argc == 2 ){
    newaddr = lo_address_create_from( lo_address_get_hostname( addr ), argv[1]->i  );
    port = argv[1]->i;
  } else {
    port = lo_address_get_port_as_int(addr);
  }
//   string str( argv[2]->s, strnlen( argv[2]->s, 127 ) );
  bool res = server->registerClient( newaddr, port, (string) &argv[0]->s );
  server->sendConfirmation( newaddr, "/XOSC/register/client", res );
  return 0;
}

int XOscServer::registerOtherClientHandler( handlerArgs )
{
  lo_message msg = (lo_message) data;
  lo_address addr = lo_message_get_source( msg );
  XOscServer* server = ( XOscServer* ) user_data;
  
  if ( server->postDebug ){
 	cout << "[XOscServer:client register]: " + server->getContent( path, types, argv, argc ) + "from:" + (string)( lo_address_get_hostname( addr) ) + (string)( lo_address_get_port( addr ) ) + "\n";
  }
  
//  lo_address newaddr = lo_address_create_from( lo_address_get_hostname( addr ), argv[0]->i  );
  lo_address newaddr = lo_address_create_from( &argv[0]->s, argv[1]->i  );

  lo_address retaddr = addr;
  if ( argc == 4 ){
    retaddr = lo_address_create_from( lo_address_get_hostname( addr ), argv[3]->i  );
  }
  bool res = server->registerClient( newaddr, argv[1]->i, (string) &argv[2]->s );
  server->sendConfirmation( retaddr, "/XOSC/register/client", res );
  if ( argc == 4 ){
    lo_address_free( retaddr );
  }
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
  lo_address newaddr = addr;
  int port;
  if ( argc == 2 ){
    newaddr = lo_address_create_from( lo_address_get_hostname( addr ), argv[1]->i  );
    port = argv[1]->i;
  } else {
    port = lo_address_get_port_as_int(addr);
  }

  bool res = server->registerHost( newaddr, (string) &argv[0]->s );
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
  lo_address newaddr = lo_address_create_from( &argv[0]->s, argv[1]->i  );
  lo_address retaddr = addr;
  if ( argc == 4 ){
    retaddr = lo_address_create_from( lo_address_get_hostname( addr ), argv[3]->i  );
  }

  bool res = server->registerHost( newaddr, (string) &argv[2]->s );
  server->sendConfirmation( retaddr, "/XOSC/register/host", res );
  if ( argc == 4 ){
    lo_address_free( retaddr );
  }
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
  lo_address newaddr = addr;
  if ( argc == 1 ){
    newaddr = lo_address_create_from( lo_address_get_hostname( addr ), argv[0]->i  );
  }
  // send back info about available tags
    server->sendTagsInfo( newaddr );
  if ( argc == 1 ){  lo_address_free( newaddr ); }
  return 0;
}

int XOscServer::queryHostsHandler( handlerArgs )
{
  lo_message msg = (lo_message) data;
  lo_address addr = lo_message_get_source( msg );
  XOscServer* server = ( XOscServer* ) user_data;
  
    if ( server->postDebug )
    	cout << "[XOscServer::queryHosts] " + server->getContent( path, types, argv, argc ) << "\n";
  lo_address newaddr = addr;
  if ( argc == 1 ){
    newaddr = lo_address_create_from( lo_address_get_hostname( addr ), argv[0]->i  );
  }
  // send back info about available hosts
  server->sendHostsInfo( newaddr );
  if ( argc == 1 ){  lo_address_free( newaddr ); }
  return 0;
}

int XOscServer::queryClientsHandler( handlerArgs )
{
  lo_message msg = (lo_message) data;
  lo_address addr = lo_message_get_source( msg );
  XOscServer* server = ( XOscServer* ) user_data;
  
    if ( server->postDebug )
    	cout << "[XOscServer::queryClients] " + server->getContent( path, types, argv, argc ) << "\n";
  lo_address newaddr = addr;
  if ( argc == 1 ){
    newaddr = lo_address_create_from( lo_address_get_hostname( addr ), argv[0]->i  );
  }
  
  // send back info about present clients
  server->sendClientsInfo( newaddr );
  if ( argc == 1 ){  lo_address_free( newaddr ); }
  return 0;
}

int XOscServer::queryConnectionsTagHandler( handlerArgs )
{
  lo_message msg = (lo_message) data;
  lo_address addr = lo_message_get_source( msg );
  XOscServer* server = ( XOscServer* ) user_data;
  
    if ( server->postDebug )
    	cout << "[XOscServer::queryConnectionsTag] " + server->getContent( path, types, argv, argc ) << "\n";

  lo_address newaddr = addr;
  if ( argc == 2 ){
    newaddr = lo_address_create_from( lo_address_get_hostname( addr ), argv[1]->i  );
  }
        
  // send back info about existing connections
  server->sendConnectionTagInfo( newaddr, &argv[0]->s );
  if ( argc == 2 ){
    lo_address_free( newaddr );
  }
  return 0;
}

int XOscServer::queryConnectionsHostHandler( handlerArgs )
{
  lo_message msg = (lo_message) data;
  lo_address addr = lo_message_get_source( msg );
  XOscServer* server = ( XOscServer* ) user_data;
  
    if ( server->postDebug )
    	cout << "[XOscServer::queryConnectionsHost] " + server->getContent( path, types, argv, argc ) << "\n";

  lo_address hostaddr = lo_address_create_from( &argv[0]->s, argv[1]->i );
  
  lo_address newaddr = addr;
  if ( argc == 3 ){
    newaddr = lo_address_create_from( lo_address_get_hostname( addr ), argv[2]->i  );
  }

  XOscHost * myhost = server->hostExists( argv[1]->i, hostaddr );

  // send back info about existing connections
  server->sendConnectionHostInfo( newaddr, myhost );

  if ( argc == 3 ){
    lo_address_free( newaddr );
  }
  return 0;
}

int XOscServer::queryConnectionsHostnameHandler( handlerArgs )
{
  lo_message msg = (lo_message) data;
  lo_address addr = lo_message_get_source( msg );
  XOscServer* server = ( XOscServer* ) user_data;
  
    if ( server->postDebug )
    	cout << "[XOscServer::queryConnectionsHostname] " + server->getContent( path, types, argv, argc ) << "\n";

  lo_address newaddr = addr;
  if ( argc == 2 ){
    newaddr = lo_address_create_from( lo_address_get_hostname( addr ), argv[1]->i  );
  }
  // TODO
  // send back info about existing connections
//     server->sendConnectionHostInfo( newaddr, &argv[0]->s );
  if ( argc == 2 ){
    lo_address_free( newaddr );
  }
  return 0;
}

/*
int XOscServer::queryConnectionsClientHandler( handlerArgs )
{
  lo_message msg = (lo_message) data;
  lo_address addr = lo_message_get_source( msg );
  XOscServer* server = ( XOscServer* ) user_data;
  
    if ( server->postDebug )
    	cout << "[XOscServer::queryConnectionsClient] " + server->getContent( path, types, argv, argc ) << "\n";

  lo_address newaddr = addr;
  if ( argc == 2 ){
    newaddr = lo_address_create_from( lo_address_get_hostname( addr ), argv[1]->i  );
  }
  
  // TODO
  // send back info about existing connections
//     server->sendConnectionHostInfo( newaddr, &argv[0]->s );
  if ( argc == 2 ){
    lo_address_free( newaddr );
  }
  return 0;
}

int XOscServer::queryConnectionsClientnameHandler( handlerArgs )
{
  lo_message msg = (lo_message) data;
  lo_address addr = lo_message_get_source( msg );
  XOscServer* server = ( XOscServer* ) user_data;
  
    if ( server->postDebug )
    	cout << "[XOscServer::queryConnectionsClientname] " + server->getContent( path, types, argv, argc ) << "\n";

  lo_address newaddr = addr;
  if ( argc == 2 ){
    newaddr = lo_address_create_from( lo_address_get_hostname( addr ), argv[1]->i  );
  }
  
  // TODO
  // send back info about existing connections
//     server->sendConnectionHostInfo( newaddr, &argv[0]->s );
  if ( argc == 2 ){
    lo_address_free( newaddr );
  }
  return 0;
}
*/

int XOscServer::queryConnectionsHandler( handlerArgs )
{
  lo_message msg = (lo_message) data;
  lo_address addr = lo_message_get_source( msg );
  XOscServer* server = ( XOscServer* ) user_data;
  
    if ( server->postDebug )
    	cout << "[XOscServer::queryConnections] " + server->getContent( path, types, argv, argc ) << "\n";

  lo_address newaddr = addr;
  if ( argc == 1 ){
    newaddr = lo_address_create_from( lo_address_get_hostname( addr ), argv[0]->i  );
  }        
  // send back info about existing connections
    server->sendConnectionsInfo( newaddr ); // TODO: how to retrieve origin address?
  if ( argc == 1 ){  lo_address_free( newaddr ); }
  return 0;
}

int XOscServer::registerWatchHandler( handlerArgs )
{
  lo_message msg = (lo_message) data;
  lo_address addr = lo_message_get_source( msg );
  XOscServer* server = ( XOscServer* ) user_data;

  if ( server->postDebug )
    	cout << "[XOscServer::registerWatch] " + server->getContent( path, types, argv, argc ) << "\n";

  if ( argc == 1 ){
    lo_address newaddr = lo_address_create_from( lo_address_get_hostname( addr ), argv[0]->i  );
    bool res = server->registerWatcher( newaddr, argv[0]->i );
    server->sendConfirmation( newaddr, "/XOSC/register/watch", res );
//     lo_address_free( newaddr ); // TODO: check if this needs to be freed here!
  } else {
    bool res = server->registerWatcher( addr, lo_address_get_port_as_int(addr) );
    server->sendConfirmation( addr, "/XOSC/register/watch", res );
  }
    return 0;
}

int XOscServer::unregisterWatchHandler( handlerArgs )
{
  lo_message msg = (lo_message) data;
  lo_address addr = lo_message_get_source( msg );
  XOscServer* server = ( XOscServer* ) user_data;

  if ( server->postDebug )
    	cout << "[XOscServer::unregisterWatch] " + server->getContent( path, types, argv, argc ) << "\n";
  
  if ( argc == 1 ){
    lo_address newaddr = lo_address_create_from( lo_address_get_hostname( addr ), argv[0]->i  );
    bool res = server->unregisterWatcher( newaddr, argv[0]->i );
    server->sendConfirmation( newaddr, "/XOSC/unregister/watch", res );
    lo_address_free( newaddr );
  } else {
    bool res = server->unregisterWatcher( addr, lo_address_get_port_as_int(addr) );
    server->sendConfirmation( addr, "/XOSC/unregister/watch", res );
  }
  return 0;
}

int XOscServer::connectHostHandler( handlerArgs )
{ 
  lo_message msg = (lo_message) data;
  lo_address addr = lo_message_get_source( msg );
  XOscServer* server = ( XOscServer* ) user_data;

  if ( server->postDebug )
    cout << "[XOscServer::connectHost] " + server->getContent( path, types, argv, argc ) << "\n";
  
  // host ip, port, client ip, port
  lo_address clientaddr = lo_address_create_from( &argv[2]->s, argv[3]->i  );
  XOscClient * myclient = server->clientExists( argv[3]->i, clientaddr );
  if ( myclient == NULL ){
    myclient = server->createNewClient( argv[3]->i, clientaddr );
  }
  
  lo_address hostaddr = lo_address_create_from( &argv[0]->s, argv[1]->i  );
  XOscHost * myhost = server->hostExists( argv[1]->i, hostaddr );
  if ( myhost == NULL ) {
      myhost = server->createNewHost( argv[1]->i, hostaddr );
  }
  
  server->subscribeToHost( myclient, myhost );

  //bool res = server->registerHost( newaddr, (string) &argv[3]->s );
  if ( argc == 5 ){
    lo_address retaddr = lo_address_create_from( lo_address_get_hostname( addr ), argv[4]->i  );
    server->sendConfirmation( retaddr, "/XOSC/connect/host", true );
    lo_address_free( retaddr );
  } else {
    server->sendConfirmation( addr, "/XOSC/connect/host", true );
  }
  return 0;  
}

int XOscServer::disconnectHostHandler( handlerArgs )
{ 
  lo_message msg = (lo_message) data;
  lo_address addr = lo_message_get_source( msg );
  XOscServer* server = ( XOscServer* ) user_data;
  lo_address retaddr = addr;
  
  if ( server->postDebug )
    cout << "[XOscServer::disconnectHost] " + server->getContent( path, types, argv, argc ) << "\n";
  if ( argc == 5 ){
    retaddr = lo_address_create_from( lo_address_get_hostname( addr ), argv[4]->i  );
  }
  
  // host ip, port, client ip, port
  lo_address clientaddr = lo_address_create_from( &argv[2]->s, argv[3]->i  );
  XOscClient * myclient = server->clientExists( argv[3]->i, clientaddr );
  if ( myclient == NULL ){
    server->sendConfirmation( retaddr, "/XOSC/disconnect/host", true );
    if ( argc == 5 ){ lo_address_free( retaddr ); }
    return 0;
  }
  
  lo_address hostaddr = lo_address_create_from( &argv[0]->s, argv[1]->i  );
  XOscHost * myhost = server->hostExists( argv[1]->i, hostaddr );
  if ( myhost == NULL ) {
    server->sendConfirmation( retaddr, "/XOSC/disconnect/host", true );
    if ( argc == 5 ){ lo_address_free( retaddr ); }
    return 0;
  }

  server->unsubscribeFromHost( myclient, myhost );

//   myhost->removeSubscription( myclient );

  server->sendConfirmation( retaddr, "/XOSC/disconnect/host", true );
  //bool res = server->registerHost( newaddr, (string) &argv[3]->s );
  if ( argc == 5 ){ lo_address_free( retaddr ); }
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
  
  // tag, client ip, port
  lo_address clientaddr = lo_address_create_from( &argv[0]->s, argv[1]->i  );
  XOscClient * myclient = server->clientExists( argv[1]->i, clientaddr );
  if ( myclient == NULL ){
    myclient = server->createNewClient( argv[1]->i, clientaddr );
  }
  
  string tagname = &argv[2]->s;
  server->subscribeToTag( myclient, tagname );

  //bool res = server->registerHost( newaddr, (string) &argv[3]->s );
  if ( argc == 4 ){
    lo_address retaddr = lo_address_create_from( lo_address_get_hostname( addr ), argv[3]->i  );
    server->sendConfirmation( retaddr, "/XOSC/connect/tag", true );
    lo_address_free( retaddr );
  } else {
    server->sendConfirmation( addr, "/XOSC/connect/tag", true );
  }
  return 0;  
}

int XOscServer::disconnectTagHandler( handlerArgs )
{ 
  lo_message msg = (lo_message) data;
  lo_address addr = lo_message_get_source( msg );
  XOscServer* server = ( XOscServer* ) user_data;

  if ( server->postDebug )
    cout << "[XOscServer::disconnectTag] " + server->getContent( path, types, argv, argc ) << "\n";

  lo_address retaddr;
  if ( argc == 4 ){
    retaddr = lo_address_create_from( lo_address_get_hostname( addr ), argv[3]->i  );
  } else {
    retaddr = addr;
  }
  // tag, client ip, port
  lo_address clientaddr = lo_address_create_from( &argv[0]->s, argv[1]->i  );
  XOscClient * myclient = server->clientExists( argv[1]->i, clientaddr );
  if ( myclient != NULL ){
    string tagname = &argv[2]->s;
    server->unsubscribeFromTag( myclient, tagname );
  }
  
  server->sendConfirmation( retaddr, "/XOSC/disconnect/tag", true );
  if ( argc == 4 ){
    lo_address_free( retaddr );
  }
  return 0;
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


int XOscServer::subscribeHandler( handlerArgs )
{
  lo_message msg = (lo_message) data;
  lo_address addr = lo_message_get_source( msg );
  
  XOscServer* server = ( XOscServer* ) user_data;
  if ( server->postDebug )
     cout << "[XOscServer::subscribe] " + server->getContent( path, types, argv, argc ) << "\n";

  lo_address retaddr;
  int port;
  if ( argc == 1 ){
    port = argv[0]->i;
    retaddr = lo_address_create_from( lo_address_get_hostname( addr ), port );
  } else {
    retaddr = addr;
    port = lo_address_get_port_as_int(addr);
  }

  XOscClient * myclient = server->clientExists( port, retaddr );
  if ( myclient == NULL ){
    myclient = server->createNewClient( port, retaddr );
  }
  server->subscribeToAllTags( myclient );
  server->sendConfirmation( retaddr, "/XOSC/subscribe", true );

    return 0;
}

int XOscServer::unsubscribeHandler( handlerArgs )
{
  lo_message msg = (lo_message) data;
  lo_address addr = lo_message_get_source( msg );
  XOscServer* server = ( XOscServer* ) user_data;

  if ( server->postDebug )
    cout << "[XOscServer::unsubscribe] " + server->getContent( path, types, argv, argc ) << "\n";

  lo_address retaddr;
  int port;
  if ( argc == 1 ){
    port = argv[0]->i;
    retaddr = lo_address_create_from( lo_address_get_hostname( addr ), port );
  } else {
    retaddr = addr;
    port = lo_address_get_port_as_int(addr);
  }
  XOscClient * myclient = server->clientExists( port, retaddr );
  if ( myclient == NULL ){
    server->sendConfirmation( retaddr, "/XOSC/unsubscribe", true );
    return 0;
  }
  server->unsubscribeFromAllTags( myclient );

  server->sendConfirmation( retaddr, "/XOSC/unsubscribe", true );
  return 0;
}

int XOscServer::subscribeTagHandler( handlerArgs )
{ 
  lo_message msg = (lo_message) data;
  lo_address addr = lo_message_get_source( msg );
  XOscServer* server = ( XOscServer* ) user_data;

  if ( server->postDebug )
    cout << "[XOscServer::subscribeTag] " + server->getContent( path, types, argv, argc ) << "\n";

  lo_address retaddr;
  int port;
  if ( argc == 2 ){
    port = argv[1]->i;
    retaddr = lo_address_create_from( lo_address_get_hostname( addr ), port );
  } else {
    retaddr = addr;
    port = lo_address_get_port_as_int(addr);
  }
  XOscClient * myclient = server->clientExists( port, retaddr );
  if ( myclient == NULL ){
    myclient = server->createNewClient( port, retaddr );
  }
	// - if tag does not yet exist, create a tag, and a responder, even if it has no origin yet
  string tagname = &argv[0]->s;
  server->subscribeToTag( myclient, tagname );
	// - send confirmation
  server->sendConfirmation( retaddr, "/XOSC/subscribe", true );
  return 0;
}

int XOscServer::unsubscribeTagHandler( handlerArgs )
{
  lo_message msg = (lo_message) data;
  lo_address addr = lo_message_get_source( msg );
  XOscServer* server = ( XOscServer* ) user_data;
  
  if ( server->postDebug )
    cout << "[XOscServer::unsubscribeTag] " + server->getContent( path, types, argv, argc ) << "\n";

  lo_address retaddr;
  int port;
  if ( argc == 2 ){
    port = argv[1]->i;
    retaddr = lo_address_create_from( lo_address_get_hostname( addr ), port );
  } else {
    retaddr = addr;
    port = lo_address_get_port_as_int(addr);
  }
  XOscClient * myclient = server->clientExists( port, retaddr );
  if ( myclient == NULL ){
    server->sendConfirmation( retaddr, "/XOSC/unsubscribe/tag", true ); // did not succeed, as this was not a client yet
    return 0;
  }
  string tagname = &argv[0]->s;
  
  server->unsubscribeFromTag( myclient, tagname );
	// - send confirmation
  server->sendConfirmation( retaddr, "/XOSC/unsubscribe/tag", true );
  return 0;
}


int XOscServer::subscribeHostHandler( handlerArgs )
{ 
  lo_message msg = (lo_message) data;
  lo_address addr = lo_message_get_source( msg );
  XOscServer* server = ( XOscServer* ) user_data;
  lo_address retaddr;
  int port;

  if ( server->postDebug )
    cout << "[XOscServer::subscribeHost] " + server->getContent( path, types, argv, argc ) << "\n";

  if ( argc == 3 ){
    retaddr = lo_address_create_from( lo_address_get_hostname( addr ), argv[2]->i  );
    port = argv[2]->i;
  } else {
    retaddr = addr;
    port = lo_address_get_port_as_int( addr );
  }
  
  XOscClient * myclient = server->clientExists( port, retaddr );
  if ( myclient == NULL ){
    myclient = server->createNewClient( port, retaddr );
  }
  
  lo_address hostaddr = lo_address_create_from( &argv[0]->s, argv[1]->i  );
  
  XOscHost * myhost = server->hostExists( argv[1]->i, hostaddr );

  if ( myhost == NULL ) {
      myhost = server->createNewHost( argv[1]->i, hostaddr );
  }
  
  server->subscribeToHost( myclient, myhost );

  server->sendConfirmation( retaddr, "/XOSC/subscribe/host", true );
  return 0;
}

int XOscServer::subscribeHostnameHandler( handlerArgs )
{ 
  lo_message msg = (lo_message) data;
  lo_address addr = lo_message_get_source( msg );
  XOscServer* server = ( XOscServer* ) user_data;

  if ( server->postDebug )
    cout << "[XOscServer::subscribeNameHost] " + server->getContent( path, types, argv, argc ) << "\n";
  
  return 0;
}

int XOscServer::unsubscribeHostHandler( handlerArgs )
{ 
  lo_message msg = (lo_message) data;
  lo_address addr = lo_message_get_source( msg );
  lo_address retaddr;
  int port;
  XOscServer* server = ( XOscServer* ) user_data;

  if ( server->postDebug )
    cout << "[XOscServer::unsubscribeHost] " + server->getContent( path, types, argv, argc ) << "\n";
  
  if ( argc == 3 ){
    retaddr = lo_address_create_from( lo_address_get_hostname( addr ), argv[2]->i  );
    port = argv[2]->i;
  } else {
    retaddr = addr;
    port = lo_address_get_port_as_int( addr );
  }
  
  XOscClient * myclient = server->clientExists( port, retaddr );
  if ( myclient == NULL ){
    server->sendConfirmation( retaddr, "/XOSC/unsubscribe/host", true );
    return 0;
  }
  
  lo_address hostaddr = lo_address_create_from( &argv[0]->s, argv[1]->i  );

  XOscHost * myhost = server->hostExists( argv[1]->i, hostaddr );

  if ( myhost == NULL ){
      server->sendConfirmation( retaddr, "/XOSC/unsubscribe/host", true );
      return 0;
      //myhost = createNewHost( hostaddr );
  }
  
  server->unsubscribeFromHost( myclient, myhost );

  server->sendConfirmation( retaddr, "/XOSC/unsubscribe/host", true );
  return 0;
}

int XOscServer::unsubscribeHostnameHandler( handlerArgs )
{ 
  lo_message msg = (lo_message) data;
  lo_address addr = lo_message_get_source( msg );
  XOscServer* server = ( XOscServer* ) user_data;

  if ( server->postDebug )
    cout << "[XOscServer::unsubscribeNameHost] " + server->getContent( path, types, argv, argc ) << "\n";
  
  // TODO
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
	addMethod( "/XOSC/register/client",  "si", registerClientHandler, this );    // port, name
	addMethod( "/XOSC/register/client",  "s", registerClientHandler, this );    // port, name
	addMethod( "/XOSC/register/client",  "sisi", registerOtherClientHandler, this );    // ipaddress, port, name
	addMethod( "/XOSC/register/client",  "sis", registerOtherClientHandler, this );    // ipaddress, port, name
// 	addMethod( "/XOSC/unregister/client", "is", unregisterClientHandler, this ); // port, name

	addMethod( "/XOSC/register/host",  "si", registerHostHandler, this );    // port (to send confirm to), name
	addMethod( "/XOSC/register/host",  "s", registerHostHandler, this );    // port (to send confirm to), name
	addMethod( "/XOSC/register/host",  "sisi", registerOtherHostHandler, this );    // ip address, port, name
	addMethod( "/XOSC/register/host",  "sis", registerOtherHostHandler, this );    // ip address, port, name
// 	addMethod( "/XOSC/unregister/host", "is", unregisterHostHandler, this ); // port (to send confirm to), name
	
	addMethod( "/XOSC/register/watch",   "i",  registerWatchHandler, this ); // port to send back to
	addMethod( "/XOSC/register/watch",   "",  registerWatchHandler, this ); // port to send back to
	addMethod( "/XOSC/unregister/watch",   "i",  unregisterWatchHandler, this ); // port to send back to
	addMethod( "/XOSC/unregister/watch",   "",  unregisterWatchHandler, this ); // port to send back to

	addMethod( "/XOSC/query/tags",  "i",   queryTagsHandler, this ); // port to send back to
	addMethod( "/XOSC/query/tags",  "",   queryTagsHandler, this ); // port to send back to
	addMethod( "/XOSC/query/hosts",  "i",   queryHostsHandler, this ); // port to send back to
	addMethod( "/XOSC/query/hosts",  "",   queryHostsHandler, this ); // port to send back to
	addMethod( "/XOSC/query/clients",  "i",   queryClientsHandler, this ); // port to send back to
	addMethod( "/XOSC/query/clients",  "",   queryClientsHandler, this ); // port to send back to
	addMethod( "/XOSC/query/connections", "i",   queryConnectionsHandler, this ); // port to send back to
	addMethod( "/XOSC/query/connections", "",   queryConnectionsHandler, this ); // port to send back to
	addMethod( "/XOSC/query/connections/tag", "si",   queryConnectionsTagHandler, this ); // port to send back to, tag to query
	addMethod( "/XOSC/query/connections/tag", "s",   queryConnectionsTagHandler, this ); // port to send back to, tag to query
	addMethod( "/XOSC/query/connections/host", "sii",   queryConnectionsHostHandler, this ); // port to send back to
	addMethod( "/XOSC/query/connections/host", "si",   queryConnectionsHostHandler, this ); // port to send back to
	addMethod( "/XOSC/query/connections/hostname", "si",   queryConnectionsHostnameHandler, this ); // port to send back to
	addMethod( "/XOSC/query/connections/hostname", "s",   queryConnectionsHostnameHandler, this ); // port to send back to


	addMethod( "/XOSC/subscribe/tag",   "si",  subscribeTagHandler, this ); // port to send back to, tag
	addMethod( "/XOSC/subscribe/tag",   "s",  subscribeTagHandler, this ); // port to send back to, tag
	addMethod( "/XOSC/subscribe/host",   "sii",  subscribeHostHandler, this ); // port to send back to, host ip, host port to connect to
	addMethod( "/XOSC/subscribe/host",   "si",  subscribeHostHandler, this ); // port to send back to, host ip, host port to connect to
	addMethod( "/XOSC/subscribe/hostname",   "si",  subscribeHostnameHandler, this ); // port to send back to, host name
	addMethod( "/XOSC/subscribe/hostname",   "s",  subscribeHostnameHandler, this ); // port to send back to, host name

	addMethod( "/XOSC/unsubscribe/tag",   "si",  unsubscribeTagHandler, this ); // port to send back to, tag
	addMethod( "/XOSC/unsubscribe/tag",   "s",  unsubscribeTagHandler, this ); // port to send back to, tag
	addMethod( "/XOSC/unsubscribe/host",   "sii",  unsubscribeHostHandler, this ); // port to send back to, host ip, host port to connect to
	addMethod( "/XOSC/unsubscribe/host",   "si",  unsubscribeHostHandler, this ); // port to send back to, host ip, host port to connect to
	addMethod( "/XOSC/unsubscribe/hostname",   "si",  unsubscribeHostnameHandler, this ); // port to send back to, host name
	addMethod( "/XOSC/unsubscribe/hostname",   "s",  unsubscribeHostnameHandler, this ); // port to send back to, host name

	// all tags
	addMethod( "/XOSC/subscribe",   "i",  subscribeHandler, this ); // port to send back to
	addMethod( "/XOSC/subscribe",   "",  subscribeHandler, this ); // port to send back to
	addMethod( "/XOSC/unsubscribe",   "i",  unsubscribeHandler, this ); // port to send back to
	addMethod( "/XOSC/unsubscribe",   "",  unsubscribeHandler, this ); // port to send back to

	addMethod( "/XOSC/connect/tag",   "sis",  connectTagHandler, this ); // client ip, port, tag
	addMethod( "/XOSC/connect/tag",   "sisi",  connectTagHandler, this ); // client ip, port, tag, port for reply
	addMethod( "/XOSC/connect/tag",   "ss",  connectHostnameTagHandler, this ); // client name, tag
	addMethod( "/XOSC/connect/tag",   "ssi",  connectHostnameTagHandler, this ); // client name, tag, port to reply
	addMethod( "/XOSC/disconnect/tag",   "sis",  disconnectTagHandler, this ); // client ip, port, tag
	addMethod( "/XOSC/disconnect/tag",   "sisi",  disconnectTagHandler, this ); // client ip, port, tag, port to reply
	addMethod( "/XOSC/disconnect/tag",   "ss",  disconnectHostnameTagHandler, this ); // host name, tag
	addMethod( "/XOSC/disconnect/tag",   "ssi",  disconnectHostnameTagHandler, this ); // host name, tag, port to reply

	addMethod( "/XOSC/connect/host",   "sisi",  connectHostHandler, this ); // client host ip, client port, host ip, host port to connect to
	addMethod( "/XOSC/connect/host",   "sisii",  connectHostHandler, this ); // client host ip, client port, host ip, host port to connect to, port to reply
	addMethod( "/XOSC/connect/hostname",   "sis",  connectHostnameHandler, this ); // client host ip, client port, host ip, host port to connect to
	addMethod( "/XOSC/connect/hostname",   "sisi",  connectHostnameHandler, this ); // client host ip, client port, host ip, host port to connect to, port to reply

	addMethod( "/XOSC/connect/host",   "ssi",  connectHostnameHostHandler, this ); // client name, host ip, host port, 
	addMethod( "/XOSC/connect/host",   "ssii",  connectHostnameHostHandler, this ); // client name, host ip, host port, port to reply
	addMethod( "/XOSC/connect/hostname",   "ss",  connectHostnameHostnameHandler, this ); // client name, host name
	addMethod( "/XOSC/connect/hostname",   "ssi",  connectHostnameHostnameHandler, this ); // client name, host name, port to reply

	addMethod( "/XOSC/disconnect/host",   "sisi",  disconnectHostHandler, this ); // client host ip, client port, host ip, host port to connect to
	addMethod( "/XOSC/disconnect/host",   "sisii",  disconnectHostHandler, this ); // client host ip, client port, host ip, host port to connect to
	addMethod( "/XOSC/disconnect/hostname",   "sis",  disconnectHostnameHandler, this ); // client host ip, client port, host ip, host port to connect to
	addMethod( "/XOSC/disconnect/hostname",   "sisi",  disconnectHostnameHandler, this ); // client host ip, client port, host ip, host port to connect to

	addMethod( "/XOSC/disconnect/host",   "ssi",  disconnectHostnameHostHandler, this ); // client name, host ip, host port
	addMethod( "/XOSC/disconnect/host",   "ssii",  disconnectHostnameHostHandler, this ); // client name, host ip, host port, port to reply
	addMethod( "/XOSC/disconnect/hostname",   "ss",  disconnectHostnameHostnameHandler, this ); // client name, host name
	addMethod( "/XOSC/disconnect/hostname",   "ssi",  disconnectHostnameHostnameHandler, this ); // client name, host name, port to reply

	// The generic handler must be added last. 
	// Otherwise it would be called instead of the handlers. 
	addMethod( NULL, NULL, genericHandler, this );
}


void XOscServer::subscribeToAllTags( XOscClient * client ){
  tagMap::const_iterator end = oscTags.end(); 
  for (tagMap::const_iterator it = oscTags.begin(); it != end; ++it) {
      it->second->addSubscription( client );
      sendWatchersConnectionInfo( it->second, client, true );  
  }  
}

void XOscServer::unsubscribeFromAllTags( XOscClient * client ){
  tagNameList * clientTags = client->getTags();
  tagNameList::const_iterator end = clientTags->end(); 
  for (tagNameList::const_iterator it = clientTags->begin(); it != end; ++it) {
    XOscTag * xtag = tagExists( *it );
    if ( xtag != NULL ){
      sendWatchersConnectionInfo( xtag, client, true );
      xtag->removeSubscription( client );
      if ( !xtag->hasSubscriptions() ){
	deleteMethod( xtag );
      }
    }
  }  
}

void XOscServer::subscribeToHost( XOscClient * client, XOscHost * host ){

  XOscTag * tag;
  tagNameList * tags = host->getTags();
  // iterate over tags to set message
  tagNameList::const_iterator end = tags->end(); 
  for (tagNameList::const_iterator it = tags->begin(); it != end; ++it) {
    tag = tagExists( *it );
    if ( tag == NULL ){
      tag = createNewTag( *it );
    }
    // - if no subscriptions yet, create a responder for the tag
    if ( !tag->hasSubscriptions() ){
      createMethod( tag );
    }
  }
  host->addSubscription( client );
  sendWatchersConnectionInfo( host, client, true );
}

void XOscServer::unsubscribeFromHost( XOscClient * client, XOscHost * host ){

  XOscTag * tag;
  host->removeSubscription( client );
  tagNameList * tags = host->getTags();
  // iterate over tags to set message
  tagNameList::const_iterator end = tags->end(); 
  for (tagNameList::const_iterator it = tags->begin(); it != end; ++it) {
    tag = tagExists( *it );
    if ( tag == NULL ){
      tag = createNewTag( *it );
    }
    if ( !tag->hasSubscriptions() ){
      deleteMethod( tag );
    }
  }
  sendWatchersConnectionInfo( host, client, false );
}

void XOscServer::subscribeToTag( XOscClient * client, string tagname ){
  XOscTag * tag = tagExists( tagname );
  if ( tag == NULL ){
      tag = createNewTag( tagname );
  }
	// - if no subscriptions yet, create a responder for the tag
  if ( !tag->hasSubscriptions() ){
      createMethod( tag );
  }
	// - subscribe this client
  tag->addSubscription( client );
	// - if we have connection subscriptions, inform about the new connection
  sendWatchersConnectionInfo( tag, client, true );  
}

void XOscServer::unsubscribeFromTag( XOscClient * client, string tagname ){
  XOscTag * tag = tagExists( tagname );
  if ( tag == NULL ){
    return;
  }
  // - if we have connection subscriptions, inform about the lost connection
  sendWatchersConnectionInfo( tag, client, false );
  tag->removeSubscription( client );
  // tag has no subscriptions left, so remove method
  if ( !tag->hasSubscriptions() ){
    deleteMethod( tag );
//     return 0;
  }
  return;
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
  int port = lo_address_get_port_as_int(hostAddr);
  if ( hostExistsAndChangeName( port, hostAddr, name ) ){
      return true; // was already registered
  }
  XOscHost * host = createNewHost( port, hostAddr, name );
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


void XOscServer::sendTagsInfo( lo_address addr ){
  tagMap::const_iterator end = oscTags.end(); 
  for (tagMap::const_iterator it = oscTags.begin(); it != end; ++it) {
      it->second->sendTagInfo( addr );
  }
  if ( oscTags.size() == 0 ){
      sendConfirmation( addr, "/XOSC/query/tags", false );      
  }
}

void XOscServer::sendHostsInfo( lo_address addr ){
  hostMap::const_iterator endh = oscHosts.end();
  for (hostMap::const_iterator it = oscHosts.begin(); it != endh; ++it) {
      lo_message msg = it->second->getHostInfoMsg();    
      sendMessage( addr, "/XOSC/info/host", msg );  
      lo_message_free( msg );
  }
  if ( oscHosts.size() == 0 ){
      sendConfirmation( addr, "/XOSC/query/hosts", false );      
  }
}

void XOscServer::sendClientsInfo( lo_address addr ){
  clientMap::const_iterator endh = oscClients.end();
  for (clientMap::const_iterator it = oscClients.begin(); it != endh; ++it) {
      lo_message msg = it->second->getClientInfoMsg();
      sendMessage( addr, "/XOSC/info/client", msg );  
      lo_message_free( msg );
  }
  if ( oscClients.size() == 0 ){
      sendConfirmation( addr, "/XOSC/query/clients", false );      
  }
}

void XOscServer::sendConnectionsInfo( lo_address  addr ){
  bool res = false;
  tagMap::const_iterator end = oscTags.end(); 
  for (tagMap::const_iterator it = oscTags.begin(); it != end; ++it) {
      res = res | it->second->sendConnectionInfo( addr );
  }  
  hostMap::const_iterator endh = oscHosts.end();
  for (hostMap::const_iterator it = oscHosts.begin(); it != endh; ++it) {
      res = res | it->second->sendConnectionInfo( addr );
  }
  if ( !res ){
      sendConfirmation( addr, "/XOSC/query/connections", false );      
  }

}

void XOscServer::sendConnectionTagInfo( lo_address  addr, string tag ){
   bool res = false;
   XOscTag * xtag = tagExists( tag );
   if ( xtag != NULL ){
      res = xtag->sendConnectionInfo( addr );
   }
   if ( !res ){
      sendConfirmation( addr, "/XOSC/query/connection/tag", false );    
   }
}

void XOscServer::sendConnectionHostInfo( lo_address addr, XOscHost * host ){
   bool res = false;
   if ( host != NULL ){
     res = host->sendConnectionInfo( addr );
   } 
   if ( !res ) {
      sendConfirmation( addr, "/XOSC/query/connection/host", false );    
   }
}

// void XOscServer::sendConnectionClientInfo( lo_address  addr, XOscClient * client ){
  // TODO : how to store host connections of client?
//    if ( client != NULL ){
//      lo_message msg = client->getClientConnectionsMsg();
//      sendMessage( addr, "/XOSC/info/connection/client", msg );
//       client->sendConnectionInfo( addr );
//      lo_message_free( msg );
//    }
// }

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

void XOscServer::sendWatchersConnectionInfo( XOscHost * host, XOscClient * client, bool gotconnected ){
  lo_message msg = host->getSingleConnectionInfoMsg( client, gotconnected );
  clientMap::const_iterator end = oscWatchers.end(); 
  for (clientMap::const_iterator it = oscWatchers.begin(); it != end; ++it) {
    sendMessage( it->second->getAddress(), "/XOSC/info/connection/host", msg );  
//     xtag->sendSingleConnectionInfo( client, it->second->getAddress(), gotconnected );
  }
  lo_message_free( msg );
}

void XOscServer::sendWatchersConnectionInfo( XOscTag * xtag, XOscClient * client, bool gotconnected ){
  lo_message msg = xtag->getSingleConnectionInfoMsg( client, gotconnected );
  clientMap::const_iterator end = oscWatchers.end(); 
  for (clientMap::const_iterator it = oscWatchers.begin(); it != end; ++it) {
    sendMessage( it->second->getAddress(), "/XOSC/info/connection/tag", msg );  
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
    myhost = getHost( lo_address_get_port_as_int(originAddress), originAddress );
    xtag->setOrigin( myhost );
    return false;
}

void XOscServer::createNewTag( string name, lo_address originAddress ){
  // TODO: create a new tag instance, and add it to the map
  int port = lo_address_get_port_as_int(originAddress);
  XOscHost * myhost = hostExists( port, originAddress );
  XOscTag * newtag = new XOscTag( name );
  if ( myhost == NULL ){
      myhost = createNewHost( port, originAddress );
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

XOscHost*  XOscServer::hostExists( int port, lo_address addr ){
  hostMap::iterator iter = oscHosts.find( port );
  if ( iter != oscHosts.end() ){
    if ( lo_address_issame( addr, (iter->second->getAddress() ) ) ){
	return iter->second;
    }
  }
  return NULL;
}


bool XOscServer::hostExistsAndChangeName( int port, lo_address addr, string name ){
  XOscHost * host = hostExists( port, addr );
  if ( host == NULL ){
      return false;
  }
  host->setName( name );
  return true;
}

XOscHost * XOscServer::createNewHost( int port, lo_address addr, string name ){
  XOscHost * newhost = new XOscHost( addr );
  newhost->setName( name );
  newhost->setServer( this );
  oscHosts.insert( make_pair( port, newhost ) );
  return newhost;
}

XOscHost * XOscServer::createNewHost( int port, lo_address addr ){
  XOscHost * newhost = new XOscHost( addr );
  newhost->setServer( this );
  oscHosts.insert( make_pair( port, newhost ) );
  return newhost;
}

XOscHost * XOscServer::getHost( int port, lo_address addr ){
  XOscHost * host = hostExists( port, addr );
  if ( host == NULL ){
    host = createNewHost( port, addr );
  }
  return host;
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
