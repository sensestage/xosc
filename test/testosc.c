
#include <stdio.h>

#include <lo/lo.h>

lo_address t;
lo_server s;
lo_server_thread st;


void error(int num, const char *m, const char *path);

int generic_handler(const char *path, const char *types, lo_arg **argv,
		    int argc, void *data, void *user_data);

int done = 0;

int main(int argc, char** argv)
{

    char *port = "57151";
    char *outport = "57120";
    char *ip = "127.0.0.1";

//     printf("argv: %s %s %s %s %s %s %i\n", argv[0], argv[1], argv[2], argv[3], argc );
        
    if ( argc == 4 )
	    {
	    ip = argv[3];
	    port = argv[3];
	    outport = argv[1];
	    }
    else if ( argc == 3 )
	    {
	    port = argv[2];
	    outport = argv[1];
	    }
    else if ( argc == 2 )
	    {
	    outport = argv[1];
	    }

    printf("============================================================================\n");
    printf("testosc - v0.1 - dumps incoming osc data based on video recording\n");
    printf("                     (c) 2013, Marije Baalman\n");
    printf("This is free software released under the GNU/General Public License\n");
    printf("start with \"testosc <target_port> <recv_port> <target_ip>\" \n");
    printf("============================================================================\n\n");
    printf("Listening to port: %s\n", port );
    printf("Sending to ip and port: %s %s\n", ip, outport );
    fflush(stdout);

    /* create liblo addres */
    t = lo_address_new(ip, outport); // change later to use other host

    lo_server_thread st = lo_server_thread_new(port, error);

    lo_server_thread_add_method(st, NULL, NULL, generic_handler, NULL);

    lo_server_thread_start(st);
 
//     lo_server s = lo_server_thread_get_server( st );

//     lo_send_from( t, s, LO_TT_IMMEDIATE, "/videoplay/started", "" );
        
	while( !done ){
	  sleep(1);
	}

//    lo_send_from( t, s, LO_TT_IMMEDIATE, "/videoplay/quit", "s", "nothing more to do, quitting" );
//    lo_server_thread_free( st );
//    lo_address_free( t );

   return 0;
}

void error(int num, const char *msg, const char *path)
{
     printf("liblo server error %d in path %s: %s\n", num, path, msg);
     fflush(stdout);
}


/* catch any incoming messages and display them. returning 1 means that the
 * message has not been fully handled and the server should try other methods */
int generic_handler(const char *path, const char *types, lo_arg **argv,
		    int argc, void *data, void *user_data)
{
    int i;
    lo_message msg = (lo_message) data;
    lo_address addr = lo_message_get_source( msg );
    printf( "from: %s, %s, %s", lo_address_get_hostname( addr), lo_address_get_port( addr ), lo_address_get_url( addr ) );
    
    printf("path: <%s>\n", path);
    for (i=0; i<argc; i++) {
	printf("arg %d '%c' ", i, types[i]);
	lo_arg_pp(types[i], argv[i]);
	printf("\n");
    }
    printf("\n");
    fflush(stdout);

    return 1;
}
