#ifndef LOEXTENSIONS_H
#define LOEXTENSIONS_H

#include <lo/lo.h>

#define handlerArgs const char* path, const char* types, lo_arg** argv, int argc, lo_message data, void* user_data

// 1 = addresses are the same, 0 = addresses are not the same, -1 = at least one adress is invalid
bool lo_address_issame( lo_address a, lo_address b );
lo_address lo_address_copy( lo_address addr );
lo_address lo_address_create_from( const char * host, int port );
int lo_address_get_port_as_int( lo_address addr );

uint32_t lo_address_get_hostname_as_short_int( lo_address addr );
uint32_t lo_address_get_addr_as_int( lo_address addr );

uint32_t lo_address_get_hostname_as_int( lo_address addr );
unsigned long lo_address_get_addr_as_long( lo_address addr );

#endif