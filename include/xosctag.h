#ifndef XOSCTAG_H
#define XOSCTAG_H

#include "xosctypes.h"

namespace XOsc {

   class XOscTag {
     
public:
//     XOscTag( string tag, XOscClient * origin );
    XOscTag( string tag );
    
    void setOrigin( XOscHost * host );
    
    void setServer( XOscServer * serv );
    XOscServer * getServer();
    
    void sendSingleConnectionInfo( XOscClient * client, lo_address * target );
    void sendConnectionInfo( lo_address * target );
    void sendTagInfo( lo_address * target );
    
//     bool fromSame( XOscClient * origin ); // check whether the message came from the same host
        
    void addSubscription( XOscClient * client );    // client
    void removeSubscription( XOscClient * client ); // client
    
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