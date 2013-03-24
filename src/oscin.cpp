
/***************************************************************************
 *   This file is part of libdatanetwork                                   *
 *   Adapted and expanded from the swonder project, as below               *
 *                                                                         *
 *   Copyright (C) 2009 by Marije Baalman                                  *
 *   nescivi _at_ gmail _dot_ com                                          *
 *                                                                         */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 *                                                                                   *
 *  WONDER - Wave field synthesis Of New Dimensions of Electronic music in Realtime  *
 *  http://swonder.sourceforge.net                                                   *
 *                                                                                   *
 *                                                                                   *
 *  Simon Schampijer                                                                 *
 *  Technische Universit�t Berlin, Germany                                           *
 *  Audio Communication Group                                                        *
 *  www.ak.tu-berlin.de                                                              *
 *  Copyright 2006-2008                                                              *
 *                                                                                   *
 *                                                                                   *
 *  This program is free software; you can redistribute it and/or modify             *
 *  it under the terms of the GNU General Public License as published by             *
 *  the Free Software Foundation; either version 2 of the License, or                *
 *  (at your option) any later version.                                              *
 *                                                                                   *
 *  This program is distributed in the hope that it will be useful,                  *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of                   *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                    *
 *  GNU General Public License for more details.                                     *
 *                                                                                   *
 *  You should have received a copy of the GNU General Public License                *
 *  along with this program; if not, write to the Free Software                      *
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.       *
 *                                                                                   *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "oscin.h"

#include <sstream>


OSCServer::OSCServer( const char* port )
{
    serverThread = lo_server_thread_new( port, NULL );
    if( serverThread == NULL )
        throw EServ();
	server = lo_server_thread_get_server( serverThread );
}


OSCServer::~OSCServer()
{
    if( serverThread )
        lo_server_thread_free( serverThread );
}

int OSCServer::getPort()
{
	return lo_server_get_port( server );
}

void OSCServer::sendMessage( lo_address targ, const char *path, lo_message mess )
{
	lo_send_message_from( targ, server, path, mess );
}

void OSCServer::sendSimpleMessage( const char *path )
{
  lo_send_from( targ, server, LO_TT_IMMEDIATE, path );
}

void OSCServer::start() 
{
    lo_server_thread_start( serverThread );    
}


void OSCServer::stop() 
{
    lo_server_thread_stop( serverThread );
}


void OSCServer::addMethod( const char* path, const char* types, lo_method_handler h, void* user_data ) 
{
    lo_server_thread_add_method( serverThread, path, types, h, user_data );
}

void OSCServer::removeMethod( const char* path, const char* types ) 
{
    lo_server_thread_del_method( serverThread, path, types );
}

lo_message OSCServer::getMessage( const char* types, lo_arg** argv, int argc)
{
  lo_message msg = lo_message_new();
  for( int i = 0; i < argc; ++i )
    {
        switch( types[ i ] )
        { 
            case LO_FLOAT:
	      lo_message_add_float( msg,argv[ i ]->f );
              break;
            case LO_INT32:
	      lo_message_add_int32( msg,argv[ i ]->i );
              break;	      
            case LO_SYMBOL:
	      lo_message_add_symbol( msg, &argv[ i ]->S );
              break;
            case LO_STRING:
	      lo_message_add_string( msg,&argv[ i ]->s );
              break;
            case LO_CHAR:
	      lo_message_add_char( msg,argv[ i ]->c );
              break;
            case LO_DOUBLE:
	      lo_message_add_double( msg,argv[ i ]->d );
              break;
            case LO_INT64:
	      lo_message_add_int64( msg,argv[ i ]->h );
	      break;
	    case LO_MIDI:
	      lo_message_add_midi( msg,&argv[ i ]->m );
	      break;
	    case LO_TRUE:
	      lo_message_add_true( msg );
	      break;
	    case LO_FALSE:
	      lo_message_add_false( msg );
	      break;
	    case LO_NIL:
	      lo_message_add_nil( msg );
	      break;
	    case LO_INFINITUM:
	      lo_message_add_infinitum( msg );
	      break;
	    case LO_BLOB:
	      lo_message_add_blob( msg, (lo_blob) argv[ i ] );
	      break;
	    case LO_TIMETAG:
	      lo_message_add_timetag( msg, (lo_timetag) argv[ i ] );
	      break;
        }
    }
    return msg;
}


std::string OSCServer::getContent(const char* path, const char* types, lo_arg** argv, int argc)
{
    std::ostringstream contents;

    contents << "[OSCServer::"<< path << "]   ";
    for( int i = 0; i < argc; ++i )
    {
        contents << types[ i ] << "=";
        switch( types[ i ] )
        {
            case 's':
                contents << &argv[ i ]->s;
                break;
            case 'f':
                contents << argv[ i ]->f;
                break;
            case 'i':
                contents << argv[ i ]->i;
        }
        contents << "   ";
    }
    return contents.str();
}
