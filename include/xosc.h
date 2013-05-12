/***************************************************************************
 *   This file is part of xosc
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

#ifndef XOSC_H
#define XOSC_H

#include <string>
#include <map>
#include <lo/lo.h>
// #include <curl/curl.h>

#include "lo_extensions.h"

//#include "xosc.h"
#include "oscin.h"
#include "xosctypes.h"
#include "xoscclient.h"
#include "xosctag.h"
// #include "xoschost.h"


using namespace std;

namespace XOsc {

  typedef std::map<string, int> portMap;
  
  typedef std::map<int, XOsc::XOscHost*> hostMap;     // order by port

  
/**
	@author Marije Baalman <nescivi@gmail.com>
*/

class XOscServer : public OSCServer {
public:
    XOscServer( const char *port );
    ~XOscServer();
    void addBasicMethods();
    void debug( bool onoff );

    bool postDebug;

private:
  tagMap oscTags;
  clientMap oscClients;
  hostMap oscHosts;
  clientMap oscWatchers;
  
  portMap oscHostNames;
  portMap oscClientNames;
  
  void createMethod( XOscTag * osctag );
  void deleteMethod( XOscTag * osctag );

  void sendConfirmation( lo_address targ, const char *path, bool success );
  
  bool registerClient( lo_address clientAddr, int port, string name );
  bool registerHost( lo_address hostAddr, string name );
  
  bool registerWatcher( lo_address clientAddr, int port );
  bool unregisterWatcher( lo_address clientAddr, int port );
  
  void sendTagInfo( lo_address addr ); // FIXME
  void sendConnectionInfo( lo_address addr ); // FIXME
  void sendConnectionTagInfo( lo_address addr, string name ); // FIXME
  
  void sendWatchersClientInfo( XOscClient* client );  
  void sendWatchersHostInfo( XOscHost* host );  
  void sendWatchersTagInfo( XOscTag* xtag );  
  void sendWatchersConnectionInfo( XOscTag* xtag, XOscClient * client, bool gotconnected );

  void subscribeToAllTags( XOscClient * client );
  void unsubscribeFromAllTags( XOscClient * client );
  
  void subscribeToTag( XOscClient * client, string tagname );
  void unsubscribeFromTag( XOscClient * client, string tagname );
  
  XOscTag* tagExists( string name );  
  bool tagCheckAndChangeOrigin( XOscTag* xtag, lo_address originAddress );
  void createNewTag( string name, lo_address originAddress );
  XOscTag* createNewTag( string name );

  XOscClient* watcherExists( int port, lo_address addr );
  XOscClient* createNewWatcher( int port, lo_address addr );
  void removeWatcher( int port );
  
  XOscClient* clientExists( int port, lo_address addr );
  bool clientExistsAndChangeName( int port, lo_address addr, string name );
  XOscClient* createNewClient( int port, lo_address addr, string name );  
  XOscClient* createNewClient( int port, lo_address addr );
  void addClientName( int port, string name );
  void deleteClientName( string name );
  XOscClient * findClientByName( string name );
  
  XOscHost*  hostExists( int port, lo_address addr );
  bool hostExistsAndChangeName( int port, lo_address addr, string name );
  XOscHost* createNewHost( int port, lo_address addr, string name );
  XOscHost* createNewHost( int port, lo_address addr );
  XOscHost* getHost( int port, lo_address addr );
  void addHostName( int port, string name );
  void deleteHostName( string name );
  XOscHost * findHostByName( string name );
  
// 	void sendSimpleMessage( const char *path );
// 	void handleError( int errorid, const char *errorMsg, const char *prefix );

//   int port;

// ----------- osc handlers ---------------

// 	static int pingHandler( handlerArgs );
// 	static int errorHandler( handlerArgs );
// 	static int warnHandler( handlerArgs );

	static int registerClientHandler( handlerArgs );
	static int registerOtherClientHandler( handlerArgs );
// 	static int unregisterClientHandler( handlerArgs );
	static int registerHostHandler( handlerArgs );
	static int registerOtherHostHandler( handlerArgs );
// 	static int unregisterHostHandler( handlerArgs );
	static int registerWatchHandler( handlerArgs ); // to be automatically informed about connections and new tags
	static int unregisterWatchHandler( handlerArgs ); // to be automatically informed about connections and new tags

	static int queryTagsHandler( handlerArgs );
	static int queryConnectionsTagHandler( handlerArgs );
	static int queryConnectionsHandler( handlerArgs );

	static int subscribeHandler( handlerArgs ); // all
	static int unsubscribeHandler( handlerArgs ); // all

	static int subscribeTagHandler( handlerArgs );
	static int unsubscribeTagHandler( handlerArgs );

	static int subscribeHostHandler( handlerArgs );
	static int unsubscribeHostHandler( handlerArgs );

	static int subscribeHostnameHandler( handlerArgs );
	static int unsubscribeHostnameHandler( handlerArgs );

	static int connectTagHandler( handlerArgs );
	static int connectHostnameTagHandler( handlerArgs );	
	static int disconnectTagHandler( handlerArgs );
	static int disconnectHostnameTagHandler( handlerArgs );	

	static int connectHostHandler( handlerArgs );
	static int disconnectHostHandler( handlerArgs );
	static int connectHostnameHostHandler( handlerArgs );
	static int disconnectHostnameHostHandler( handlerArgs );

	static int connectHostnameHandler( handlerArgs );
	static int disconnectHostnameHandler( handlerArgs );
	static int connectHostnameHostnameHandler( handlerArgs );
	static int disconnectHostnameHostnameHandler( handlerArgs );

	static int genericHandler( handlerArgs );
//----------- end osc handlers ------------

};

}

#endif
