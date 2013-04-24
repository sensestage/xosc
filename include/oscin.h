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
 *  Simon Schampijer                                                                 *
 *  Technische Universität Berlin, Germany                                           *
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

#ifndef OSCIN_H
#define OSCIN_H

#include <lo/lo.h>
#include <string>

/// A wrapper class for the liblo osc server
class OSCServer
{

public:
    OSCServer( const char* port = "55000" );
    ~OSCServer();

    void start();
    void stop();

    int getPort();

    void sendMessage( lo_address targ, const char *path, lo_message mess );
    void sendSimpleMessage( lo_address targ, const char *path );
    
//     lo_message getMessage( const char* types, lo_arg** argv, int argc);

    void        addMethod ( const char* path, const char* types, lo_method_handler h, void* user_data = NULL );
    void        removeMethod ( const char* path, const char* types );
    std::string getContent( const char* path, const char* types, lo_arg** argv, int argc );

    lo_server_thread serverThread;
    lo_server server;
    int port;

    // internal exception class 
    class EServ { };
};

#endif
