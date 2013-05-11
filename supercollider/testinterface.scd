OSCFunc.trace( true, true );
n = NetAddr.new( "127.0.0.1", 57300 );

/// arbitrary message:
n.sendMsg( "/hello", 1 );
n.sendMsg( "/hello/world", 1 );



n.sendMsg( "/XOSC/query/tags", NetAddr.langPort );

n.sendMsg( "/hello", 1 );
n.sendMsg( "/XOSC/subscribe/tag", NetAddr.langPort, "/hello" );
n.sendMsg( "/hello", 1 );
n.sendMsg( "/XOSC/unsubscribe/tag", NetAddr.langPort, "/hello" );
n.sendMsg( "/hello", 1 );

n.sendMsg( "/XOSC/subscribe/tag", NetAddr.langPort, "/hello/world" );
n.sendMsg( "/XOSC/unsubscribe/tag", NetAddr.langPort, "/hello/world" );


n.sendMsg( "/XOSC/query/tag/connections", NetAddr.langPort, "/hello" );
n.sendMsg( "/XOSC/query/connections", NetAddr.langPort );
n.sendMsg( "/XOSC/query/tag/connections", NetAddr.langPort, "/hello/world" );

n.sendMsg( "/XOSC/unsubscribe/tag", NetAddr.langPort, "/hello/world" );

n.sendMsg( "/XOSC/register/client", NetAddr.langPort, "supercollider" );

n.sendMsg( "/XOSC/register/host", NetAddr.langPort, "supercolliderhost" );

// =---- up to here
n.sendMsg( "/XOSC/register/watch", NetAddr.langPort );


freqscope