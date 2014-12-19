#include "lo_extensions.h"

#include <cstdlib>
#include <cstring>
#include <cstdio>


bool lo_address_issame( lo_address a, lo_address b ){
    if( a == NULL || b == NULL )
        return false; // at least one invalid address

//     if( strcmp( lo_address_get_hostname( a ), lo_address_get_hostname( b ) ) == 0 && 
//         strcmp( lo_address_get_port( a ), lo_address_get_port( b ) ) == 0 )
//         return 1; // addresses are equal

    int res;
//     const char * host1 = lo_address_get_hostname(a);
//     const char * host2 = lo_address_get_hostname(b);
    res = strcmp(lo_address_get_hostname(a), lo_address_get_hostname(b));
    if (!res) {
      res = strcmp(lo_address_get_port(a), lo_address_get_port(b));
    }
  
    return res == 0;        
        
//     return 0; // adresses are not equal
}

lo_address lo_address_copy( lo_address addr ){
//   char buffer [5];
//   sprintf(buffer,"%d",port ); 
  lo_address newaddr = lo_address_new( lo_address_get_hostname( addr ), lo_address_get_port( addr ) ); 
  return newaddr;
}

lo_address lo_address_create_from( const char * host, int port ){
  char buffer [5];
  sprintf(buffer,"%d",port ); 
  lo_address newaddr = lo_address_new( host, buffer ); 
  return newaddr;
}

int lo_address_get_port_as_int( lo_address addr ){
    return( atoi( lo_address_get_port( addr ) ) );
}

uint32_t lo_address_get_hostname_as_short_int( lo_address a ){
  const char * hostname = lo_address_get_hostname(a);
  int ipbytes[4];
  std::sscanf(hostname, "%d.%d.%d.%d", &ipbytes[3], &ipbytes[2], &ipbytes[1], &ipbytes[0]);
  return ipbytes[0] | ipbytes[1] << 8; // | ipbytes[2] << 16 | ipbytes[3] << 24;
}

uint32_t lo_address_get_addr_as_int( lo_address addr ){
  uint32_t hostint = lo_address_get_hostname_as_short_int( addr );
  uint32_t port = (uint32_t) lo_address_get_port_as_int( addr );
  uint32_t addrint = (hostint << 16) | port;
  printf( "addrint: %d", addrint );
  return addrint;
}


uint32_t lo_address_get_hostname_as_int( lo_address a ){
  const char * hostname = lo_address_get_hostname(a);
  int ipbytes[4];
  std::sscanf(hostname, "%d.%d.%d.%d", &ipbytes[3], &ipbytes[2], &ipbytes[1], &ipbytes[0]);
  return ipbytes[0] | ipbytes[1] << 8 | ipbytes[2] << 16 | ipbytes[3] << 24;
}

unsigned long lo_address_get_addr_as_long( lo_address addr ){
  uint32_t hostlong = lo_address_get_hostname_as_int( addr );
  int port = lo_address_get_port_as_int( addr );
  unsigned long addrlong = ((unsigned long) hostlong << 16) | ( (unsigned long) port );
  return addrlong;
}


/*
char ipAddressString[16] = "192.168.125.5"
char netMaskString[16] = "255.255.0.0"
char subnetString[16] = "192.168.0.0"

uint32_t ipAddress = parseIPV4string(ipAddressString);
uint32_t netmask = parseIPV4string(netmaskString);
uint32_t subnet = parseIPV4string(subnetString);

if (ipAddress & netmask == subnet) {
  return true;
}

uint32_t parseIPV4string(char* ipAddress) {
  char ipbytes[4];
  sscanf(ipAddress, "%d.%d.%d.%d", &ipbytes[3], &ipbytes[2], &ipbytes[1], &ipbytes[0]);
  return ipbytes[0] | ipbytes[1] << 8 | ipbytes[2] << 16 | ipbytes[3] << 24;
}
*/
