#include "lo_extensions.h"

#include <cstdlib>
#include <cstring>
#include <cstdio>

int lo_address_issame( lo_address a, lo_address b )
{
    if( a == NULL || b == NULL )
        return -1; // at least one invalid address

    if( strcmp( lo_address_get_hostname( a ), lo_address_get_hostname( b ) ) == 0 && 
        strcmp( lo_address_get_port( a ), lo_address_get_port( b ) ) == 0 )
        return 1; // addresses are equal

    return 0; // adresses are not equal
}

lo_address lo_address_create_from( const char * host, int port ){
  char buffer [8];
  sprintf(buffer,"%d",port ); 
  lo_address newaddr = lo_address_new( host, buffer ); 
  return newaddr;
}

int lo_address_get_port_as_int( lo_address addr ){
    return( atoi( lo_address_get_port( addr ) ) );
}

