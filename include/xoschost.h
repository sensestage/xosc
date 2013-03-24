#ifndef XOSCCLIENT_H
#define XOSCCLIENT_H

#include <string>
#include <lo/lo.h>

#include "xosctypes.h"

namespace XOsc {

  class XOscHost {
public:
    XOscHost( lo_address * host );
    
    lo_address * getAddress();
    
    void setName( string myname );
    string getName();
    void unsetName();
    
    void addTag( XOscTag * tag );
    
    void addSubscription( XOscClient * client );    // client
    void removeSubscription( XOscClient * client ); // client    
    
    void sendMessageToSubscribers( XOscServer * server, const char * path, lo_message );
    void sendInfoAboutTags( lo_address * target );
    
    ~XOscHost();

private:
  tagMap sendingTags;    // tags I'm sending
  clientMap subscribers; // subscribers to this host
  
  string name;
  lo_address * hostAddress;
};
 
  
}

#endif