#ifndef XOSCHOST_H
#define XOSCHOST_H

#include <string>
#include <map>
#include <list>
#include <lo/lo.h>

#include "xosctypes.h"
#include "xoscclient.h"

using namespace std;
using namespace XOsc;

namespace XOsc {

  class XOscHost {
public:
    XOscHost( lo_address host );
    
    lo_address getAddress();
    
    void setName( string myname );
    string getName();
    void unsetName();
    
    //void addTag( XOscTag * tag );
    void addTag( string tagname );
    
    void addSubscription( XOscClient * client );    // client
    void removeSubscription( XOscClient * client ); // client    
    
//     void sendMessageToSubscribers( XOscServer * server, const char * path, lo_message );
    void sendInfoAboutTags( lo_address * target );
    
//     void sendSingleConnectionInfo( XOscServer * server, XOscClient * client, lo_address * target );
//     void sendConnectionInfo( XOscServer * server, lo_address * target );
    
    ~XOscHost();

private:
//  tagMap sendingTags;    // tags I'm sending
  tagNameList sendingTags;    // tags I'm sending
  clientMap subscribers; // subscribers to this host
  
  string name;
  lo_address hostAddress;
};

  typedef std::map<int, XOscHost*> hostMap;     // order by port 
}

#endif