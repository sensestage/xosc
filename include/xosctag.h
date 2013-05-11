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
    void sendConnectionInfo( lo_address target );
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
  clientMap subscribers;
};

  typedef std::map<std::string, XOsc::XOscTag*> tagMap;
}

#endif