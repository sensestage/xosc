/***************************************************************************
 *   This file is the main xosc server program                             *
 *                                                                         *
 *   Copyright (C) 2013 by Marije Baalman                                  *
 *   nescivi _at_ gmail _dot_ com                                          *
 *                                                                         *
 *   This library is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License as        *
 *   published by the Free Software Foundation; either version 3 of the    *
 *   License, or (at your option) any later version.                       *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

// #ifdef HAVE_CONFIG_H
// #include <config.h>
// #endif

// #include <iostream>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>

#include "xosc.h"

using namespace std;

/// this is the namespace used by the xosc classes
using namespace XOsc;


int main(int argc, char *argv[])
{
  XOscServer * xosc;

  if ( argc < 2 ){
    printf( "Start XOSC with 1 arguments:\n");
//     printf( "host ip (e.g. 127.0.0.1), the IP address of the host running the DataNetwork server\n");
    printf( "port (e.g. 7000), the port this client will use for OSC messages\n");
//     printf( "name (e.g. example_client), the name by which this client will be identified in the DataNetwork\n");
    printf( "For example:\n");
    printf( "%s 7000\n", argv[0]); 
    return EXIT_SUCCESS;
  }
  printf( "Started XOSC at port %s\n", argv[1]);

  // create an osc client interface for it:
  xosc = new XOscServer( argv[1] );
  xosc->debug( true ); // is false by default, but turn on if you want --- make this an option!!!
  xosc->addBasicMethods();
  xosc->start();

  while( true ){
    sleep( 5 );
  }

  return EXIT_SUCCESS;
}
