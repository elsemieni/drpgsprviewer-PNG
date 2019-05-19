/* 
 * Digimon RPG Sprite Viewer
 *
 * Copyright (C) 2004, Plüss Roland ( rptd@gmx.net )
 * 
 * This program is free software; you can redistribute it and/or 
 * modify it under the terms of the GNU General Public License 
 * as published by the Free Software Foundation; either 
 * version 2 of the License, or (at your option) any later 
 * version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

// includes
/////////////
#include "drpgsprviewer.h"
#include "foxtoolkit.h"
#include "gui/svWindowMain.h"
#include "common/deCmdLineArgs.h"
#include "common/exceptions.h"


// variables
//////////////



// function definitions
/////////////////////////
// application


// entry point
int main( int argc, char **argv ){
	bool doRun = true;
	int i;
#ifdef DEBUG_RELOCATE_STDOUT
	FILE *w32ConH4xFile = freopen( "drpgsprviewer.log", "w", stdout );
	if( ! w32ConH4xFile ) return -1;
	setvbuf( w32ConH4xFile, NULL, _IONBF, 0 );
#endif
	try{
		// fill command line object. easier to work with if more
		// command line arguments arrive later on
		deCmdLineArgs cmdArgs;
		for( i=1; i<argc; i++ ) cmdArgs.AddArgument( argv[ i ] );
		// check command line for start up arguments
		for( i=0; i<cmdArgs.GetCount(); i++ ){
			if( strcmp( cmdArgs.GetArgument( i ), "-help" ) == 0 ||
			strcmp( cmdArgs.GetArgument( i ), "--help" ) == 0 ){
				printf( "Digimon RPG Sprite Viewer\n"
					"Written By Plüss Roland\n"
					"Release 1.0\n"
					"Contact: roland@rptd.dnsalias.net\n"
					"\n" );
				doRun = false;
				break;
			}
		}
		// the rest only happens if we have not something else blocking
		if( doRun ){
			// Make application
			FXApp *app = new FXApp( "Digimon RPG Sprite Viewer", "RPTD" );
			// Open display
			app->init( argc, argv );
			// Make window
			svWindowMain *wndMain = new svWindowMain( app, &cmdArgs );
			// Create it
			app->create();
			// Run
			app->run();
		}
	}catch( duException e ){
		e.PrintError();
#ifdef DEBUG_RELOCATE_STDOUT
		fflush( stdout );
#endif
		return -1;
	}
#ifdef DEBUG_RELOCATE_STDOUT
	fflush( stdout );
#endif
	// return
	return 0;
}
