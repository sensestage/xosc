OSCFunc.trace( true, true );
n = NetAddr.new( "127.0.0.1", 57300 );

/// arbitrary message:
n.sendMsg( "/hello", 1 );
n.sendMsg( "/hello/world", 1 );

n.sendMsg( "/XOSC/query/tags" );
n.sendMsg( "/XOSC/query/tags", NetAddr.langPort );

n.sendMsg( "/XOSC/query/clients" );
n.sendMsg( "/XOSC/query/clients", NetAddr.langPort );

n.sendMsg( "/XOSC/query/hosts" );
n.sendMsg( "/XOSC/query/hosts", NetAddr.langPort );

n.sendMsg( "/XOSC/query/connections", NetAddr.langPort );
n.sendMsg( "/XOSC/query/connections/tag", "/hello",NetAddr.langPort );
n.sendMsg( "/XOSC/query/connections/tag", "/hello/world", NetAddr.langPort );
n.sendMsg( "/XOSC/query/connections/host", "127.0.0.1", 57120, NetAddr.langPort );
// n.sendMsg( "/XOSC/query/connections/hostname", "supercollider", NetAddr.langPort );

n.sendMsg( "/XOSC/query/connections" );
n.sendMsg( "/XOSC/query/connections/tag", "/hello" );
n.sendMsg( "/XOSC/query/connections/host", "127.0.0.1", 57120 );
// n.sendMsg( "/XOSC/query/connections/hostname", "supercollider" );

n.sendMsg( "/hello", 1 );
n.sendMsg( "/XOSC/subscribe/tag", "/hello" );
n.sendMsg( "/hello", 1 );
n.sendMsg( "/XOSC/unsubscribe/tag", "/hello" );

n.sendMsg( "/XOSC/subscribe/tag", "/hello", NetAddr.langPort );
n.sendMsg( "/hello", 1 );
n.sendMsg( "/XOSC/unsubscribe/tag", "/hello", NetAddr.langPort );
n.sendMsg( "/hello", 1 );

n.sendMsg( "/XOSC/subscribe/host", "127.0.0.1", 57120, NetAddr.langPort );
n.sendMsg( "/hello", 1 );
n.sendMsg( "/XOSC/unsubscribe/host", "127.0.0.1", 57120, NetAddr.langPort );
n.sendMsg( "/hello", 1 );

n.sendMsg( "/XOSC/subscribe/host", "127.0.0.1", 57120);
n.sendMsg( "/hello", 1 );
n.sendMsg( "/XOSC/unsubscribe/host", "127.0.0.1", 57120);
n.sendMsg( "/hello", 1 );

n.sendMsg( "/XOSC/register/client", "supercollider" );
n.sendMsg( "/XOSC/register/client", "supercollider", NetAddr.langPort );

n.sendMsg( "/XOSC/register/host", "supercolliderhost" );
n.sendMsg( "/XOSC/register/host", "supercolliderhost", NetAddr.langPort );

n.sendMsg( "/XOSC/register/client", "127.0.0.1", 57120, "supercollider" );
n.sendMsg( "/XOSC/register/client", "127.0.0.1", 57120, "supercollider", NetAddr.langPort );

n.sendMsg( "/XOSC/register/host", "127.0.0.1", 57120, "supercolliderhost" );
n.sendMsg( "/XOSC/register/host", "127.0.0.1", 57120, "supercolliderhost", NetAddr.langPort );

// these do not work yet...
// n.sendMsg( "/XOSC/subscribe" );
// n.sendMsg( "/XOSC/unsubscribe" );

// n.sendMsg( "/XOSC/subscribe/hostname", "supercolliderhost", NetAddr.langPort );
n.sendMsg( "/hello", 1 );
// n.sendMsg( "/XOSC/unsubscribe/hostname", "supercolliderhost", NetAddr.langPort );
n.sendMsg( "/hello", 1 );

// n.sendMsg( "/XOSC/subscribe/hostname", "supercolliderhost");
n.sendMsg( "/hello", 1 );
// n.sendMsg( "/XOSC/unsubscribe/hostname", "supercolliderhost");
n.sendMsg( "/hello", 1 );

n.sendMsg( "/XOSC/register/watch" );
n.sendMsg( "/XOSC/register/watch", NetAddr.langPort );

n.sendMsg( "/XOSC/unregister/watch" );
n.sendMsg( "/XOSC/unregister/watch", NetAddr.langPort );

n.sendMsg( "/hello", 1 );

n.sendMsg( "/XOSC/connect/tag", "127.0.0.1", 57120, "/hello" );
n.sendMsg( "/XOSC/connect/tag", "127.0.0.1", 57120, "/hello", NetAddr.langPort );

n.sendMsg( "/hello", 1 );

n.sendMsg( "/XOSC/disconnect/tag", "127.0.0.1", 57120, "/hello" );
n.sendMsg( "/XOSC/disconnect/tag", "127.0.0.1", 57120, "/hello", NetAddr.langPort );


n.sendMsg( "/XOSC/register/host", "127.0.0.1", 57120, "supercolliderhost" );
// n.sendMsg( "/XOSC/connect/tag", "supercolliderhost", "/hello" );
n.sendMsg( "/hello", 1 );
// n.sendMsg( "/XOSC/disconnect/tag", "supercolliderhost", "/hello" );
n.sendMsg( "/hello", 1 );

n.sendMsg( "/XOSC/connect/host", "127.0.0.1", 57120, "127.0.0.1", 57120 );
n.sendMsg( "/hello", 1 );
n.sendMsg( "/XOSC/disconnect/host", "127.0.0.1", 57120, "127.0.0.1", 57120 );
n.sendMsg( "/hello", 1 );

n.sendMsg( "/XOSC/connect/host", "127.0.0.1", 57120, "127.0.0.1", 57120, NetAddr.langPort );
n.sendMsg( "/hello", 1 );
n.sendMsg( "/XOSC/disconnect/host", "127.0.0.1", 57120, "127.0.0.1", 57120, NetAddr.langPort );
n.sendMsg( "/hello", 1 );

