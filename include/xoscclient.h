#ifndef XOSCCLIENT_H
#define XOSCCLIENT_H

#include <string>
#include <map>
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
    
    string getMapName();
    
    string getName();
    void setName( string newname );
    void unsetName();
    
    void unsubscribeAll();

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
};
  
  typedef std::map<int, XOsc::XOscClient*> clientMap; // order by port
}

#endif