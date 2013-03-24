#ifndef XOSCCLIENT_H
#define XOSCCLIENT_H

#include <string>
#include <lo/lo.h>

#include "xosctypes.h"

namespace XOsc {

  class XOscClient {
public:
    XOscClient( lo_address * host, const char *name );
    
    lo_address * getAddress();
    
    void setName( string name );
    void unsetName();
    
    void unsubscribeAll();
    
    void addTagSubscription( XOscTag * tag ); // TAG
    void removeTagSubscription( XOscTag * tag ); // TAG

    void addHostSubscription( XOscHost * host ); // HOST
    void removeHostSubscription( XOscHost * host ); // HOST
        
    ~XOscClient();

private:
  tagMap tagSubscriptions;
  hostMap hostSubscription;
  
  string name;
  lo_address * hostAddress;
};
 
  
}

#endif