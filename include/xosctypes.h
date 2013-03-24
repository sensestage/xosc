#ifndef XOSCTYPES_H
#define XOSCTYPES_H

#include <string>
#include <map>

#include <lo/lo.h>

/// containing forward declarations of classes and typedefs

namespace XOsc {

  // arguments of the handler functions
#define handlerArgs const char* path, const char* types, lo_arg** argv, int argc, lo_message msg, void* user_data

  class XOscServer;
  class XOscClient; // application subscribing to osc messages
  class XOscHost;   // application sending osc messages
  class XOscTag;
    
  typedef std::map<std::string, XOscTag*> tagMap;
  typedef std::map<int, XOscClient*> clientMap; // order by port
  typedef std::map<int, XOscHost*> hostMap;     // order by port

}

#endif