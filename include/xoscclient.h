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

#ifndef XOSCCLIENT_H
#define XOSCCLIENT_H

#include <string>
#include <lo/lo.h>

#include "xosctypes.h"

using namespace std;

namespace XOsc {

//   class XOscTag;
//   typedef std::map<std::string, XOsc::XOscTag*> tagMap;
  
  class XOscClient {
public:
    XOscClient( lo_address host );
    
    lo_address getAddress();
    int getPort();
    
    uint32_t getPortAddrInt();
    
    string getMapName();
    
    string getName();
    void setName( string newname );
    void unsetName();
    
    void unsubscribeAll();
    
    tagNameList * getTags();

    void addTagSubscription( string tagname ); // TAG
    void removeTagSubscription( string tagname ); // TAG
    
//     void addTagSubscription( XOscTag * tag ); // TAG
//     void removeTagSubscription( XOscTag * tag ); // TAG

 //   void addHostSubscription( XOscHost * host ); // HOST
 //   void removeHostSubscription( XOscHost * host ); // HOST
    
    lo_message getClientInfoMsg();
        
    ~XOscClient();

private:
  tagNameList tagSubscriptions;
//   tagMap tagSubscriptions;
//  hostMap hostSubscription;
  
  string name;
  lo_address hostAddress;
  uint32_t portAddrInt;
};
  
//   typedef std::map<int, XOsc::XOscClient*> clientPortMap; // order by port
  typedef std::map<uint32_t, XOsc::XOscClient*> clientAddrMap; // order by port & addr
  
}

#endif