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

// #include "xoschost.h"
#include "xosctag.h"
#include "xosc.h"

namespace XOsc {

  XOscClient::XOscClient( lo_address host ){
      hostAddress = host;
  }

  lo_address XOscClient::getAddress(){
      return hostAddress;
  }
  
  int XOscClient::getPort(){
      int port = lo_address_get_port_as_int( hostAddress );
      return port;
  }
  
  string XOscClient::getMapName(){
      string myname = string( lo_address_get_url( hostAddress ) );
  }
  
  string XOscClient::getName(){
      return name;
  }
    
  void XOscClient::setName( string newname ){
    name = newname;
  }
  
  void XOscClient::unsetName(){
      name = "";
  }
    
  void XOscClient::unsubscribeAll(){
    
  }

  void XOscClient:: addTagSubscription( string tagname ){
//     tagSubscriptions.insert( tagname );
  }
  
  void XOscClient::removeTagSubscription( string tagname ){
//     tagSubscriptions.erase( tagname );
  }
  
  lo_message XOscClient::getClientInfoMsg(){
    lo_message msg = lo_message_new();
    lo_message_add_string( msg, lo_address_get_hostname( hostAddress ) );
    lo_message_add_string( msg, lo_address_get_port( hostAddress ) );
    lo_message_add_string( msg, name.c_str() );
    return msg;
  }

//   void XOscClient:: addTagSubscription( XOscTag * tag ){
//     
//   }
//   
//   void XOscClient::removeTagSubscription( XOscTag * tag ){
//     
//   }

  /*
  void XOscClient::addHostSubscription( XOscHost * host ){
    
  }
  
  void XOscClient::removeHostSubscription( XOscHost * host ){
    
  }
  */
        
  XOscClient::~XOscClient(){
    lo_address_free( hostAddress );
  }

}