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

#ifndef XOSC_H
#define XOSC_H

#include <string>
#include <map>
#include <lo/lo.h>
// #include <curl/curl.h>

#include "oscin.h"
#include "xosctypes.h"

#include "xosctag.h"
#include "xoscclient.h"
#include "xoschost.h"

using namespace std;

namespace XOsc {
  
/**
	@author Marije Baalman <nescivi@gmail.com>
*/

class XOscServer : public OSCServer {
public:
    XOscServer(const char *hostip, const char *myport, const char *myName );
	void addBasicMethods();
	bool postDebug;
    ~XOscServer();

private:
  tagMap oscTags;
  clientMap oscClients;
  hostMap oscHosts;
  
  void createMethod( XOscTag * osctag );
  void removeMethod( XOscTag * osctag );
  
  void addOSCTag( const char *tag );
  bool tagExists( const char *tag );
  
  void addOSCClient(); // TODO: arguments
  void clientExists(); // TODO: arguments
  void removeClientFromMap(); // TODO: arguments

  void addOSCHost(); // TODO: arguments
  void hostExists(); // TODO: arguments
  void removeHostFromMap(); // TODO: arguments
  
// 	void sendSimpleMessage( const char *path );
// 	void handleError( int errorid, const char *errorMsg, const char *prefix );

  int port;

// ----------- osc handlers ---------------

// 	static int pingHandler( handlerArgs );
// 	static int errorHandler( handlerArgs );
// 	static int warnHandler( handlerArgs );

	static int registerHandler( handlerArgs );
	static int unregisterHandler( handlerArgs );
	static int registerWatchHandler( handlerArgs ); // to be automatically informed about connections and new tags
	static int unregisterWatchHandler( handlerArgs ); // to be automatically informed about connections and new tags

	static int queryTagHandler( handlerArgs );
	static int queryConnectionsHandler( handlerArgs );
	static int queryConnectionsTagHandler( handlerArgs );

	static int subscribeHandler( handlerArgs ); // all
	static int unSubscribeHandler( handlerArgs ); // all

	static int subscribeTagHandler( handlerArgs );
	static int unSubscribeTagHandler( handlerArgs );

	static int subscribeHostHandler( handlerArgs );
	static int unSubscribeHostHandler( handlerArgs );

	static int subscribeHostNameHandler( handlerArgs );
	static int unSubscribeHostNameHandler( handlerArgs );

	static int connectTagHandler( handlerArgs );
	static int connectHostnameTagHandler( handlerArgs );	
	static int disconnectHostHandler( handlerArgs );
	static int disconnectHostnameTagHandler( handlerArgs );	

	static int connectHostHandler( handlerArgs );
	static int disonnectHostHandler( handlerArgs );
	static int connectHostnameHostHandler( handlerArgs );
	static int disonnectHostnameHostHandler( handlerArgs );

	static int connectHostnameHandler( handlerArgs );
	static int disonnectHostnameHandler( handlerArgs );
	static int connectHostnameHostnameHandler( handlerArgs );
	static int disonnectHostnameHostnameHandler( handlerArgs );

	static int genericHandler( handlerArgs );
//----------- end osc handlers ------------

};

}

#endif
