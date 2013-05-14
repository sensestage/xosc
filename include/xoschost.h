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
#ifndef XOSCHOST_H
#define XOSCHOST_H

#include <string>
#include <lo/lo.h>

#include "xosctypes.h"
#include "xoscclient.h"
#include "xosc.h"

using namespace std;
using namespace XOsc;

namespace XOsc {
  
//   class XOscServer;


  class XOscHost {
public:
    XOscHost( lo_address host );
    
    lo_address getAddress();
    
    void setName( string myname );
    string getName();
    void unsetName();
    
    void setServer( XOscServer * serv );
    XOscServer * getServer();

    //void addTag( XOscTag * tag );
    void addTag( string tagname );
    tagNameList * getTags();
    
    bool hasSubscriptions();
    void addSubscription( XOscClient * client );    // client
    void removeSubscription( XOscClient * client ); // client    
    
    void sendMessageToSubscribers( XOscServer * server, const char * path, lo_message );
    
    void sendInfoAboutTags( lo_address * target );
    
    lo_message getHostInfoMsg();
    lo_message getSingleConnectionInfoMsg( XOscClient * client, bool connected=true );
    
    void sendSingleConnectionInfo( XOscClient * client, lo_address target, bool connected=true );
    void sendConnectionInfo( lo_address target );
    
    ~XOscHost();

private:
//  tagMap sendingTags;    // tags I'm sending
  tagNameList sendingTags;    // tags I'm sending
  clientMap subscribers; // subscribers to this host
  XOscServer * server;

  string name;
  lo_address hostAddress;
};

  typedef std::map<int, XOscHost*> hostMap;     // order by port 
}

#endif