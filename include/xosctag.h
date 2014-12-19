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

#ifndef XOSCTAG_H
#define XOSCTAG_H

#include "lo_extensions.h"
#include "xosctypes.h"
#include "xoscclient.h"

#include <string>
#include <map>
#include <lo/lo.h>

using namespace std;

namespace XOsc {
  
  class XOscServer;
//   class XOscClient; // application subscribing to osc messages
  class XOscHost;   // application sending osc messages
//   typedef std::map<int, XOsc::XOscClient*> clientMap; // order by port
  

   class XOscTag {
     
public:
//     XOscTag( string tag, XOscClient * origin );
    XOscTag( string tag );
    
    void setOrigin( XOscHost * host );
    bool hasOrigin();
    bool compareOrigin( lo_address addr );
    
    void setServer( XOscServer * serv );
    XOscServer * getServer();
    
    void sendSingleConnectionInfo( XOscClient * client, lo_address target, bool connected=true );
    bool sendConnectionInfo( lo_address target );
    void sendTagInfo( lo_address target );
    
    lo_message getSingleConnectionInfoMsg( XOscClient * client, bool connected=true );
    lo_message getTagInfoMsg();
    
    
//     bool fromSame( XOscClient * origin ); // check whether the message came from the same host
        
    void addSubscription( XOscClient * client );    // client
    void removeSubscription( XOscClient * client ); // client
    bool hasSubscriptions();
    
    void forwardMsgToSubscribers( const char * path, lo_message msg );
    
    string getTag();
        
    ~XOscTag();

    static int messageHandler( handlerArgs );

private:
  bool originSet;
  string tagname;
  XOscServer * server;
  XOscHost * origin;
  clientAddrMap subscribers;
};

  typedef std::map<std::string, XOsc::XOscTag*> tagMap;
}

#endif