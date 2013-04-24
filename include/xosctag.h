#ifndef XOSCTAG_H
#define XOSCTAG_H

#include "lo_extensions.h"
// #include "xosctypes.h"

#include <string>
#include <map>
#include <lo/lo.h>

using namespace std;

namespace XOsc {
  
  class XOscServer;
  class XOscClient; // application subscribing to osc messages
  class XOscHost;   // application sending osc messages
  typedef std::map<int, XOsc::XOscClient*> clientMap; // order by port
  

   class XOscTag {
     
public:
//     XOscTag( string tag, XOscClient * origin );
    XOscTag( string tag );
    
    void setOrigin( XOscHost * host );
    bool hasOrigin();
    bool compareOrigin( lo_address addr );
    
    void setServer( XOscServer * serv );
    XOscServer * getServer();
    
    void sendSingleConnectionInfo( XOscClient * client, lo_address * target );
    void sendConnectionInfo( lo_address * target );
    void sendTagInfo( lo_address * target );
    
//     bool fromSame( XOscClient * origin ); // check whether the message came from the same host
        
    void addSubscription( XOscClient * client );    // client
    void removeSubscription( XOscClient * client ); // client
    bool hasSubscriptions();
    
    string getTag();
        
    ~XOscTag();

    static int messageHandler( handlerArgs );

private:
  string tagname;
  XOscServer * server;
  XOscHost * origin;
  clientMap subscribers;
};
  
}

#endif