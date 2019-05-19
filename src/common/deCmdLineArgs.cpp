/* 
 * Drag[en]gine Library -- Game Engine
 *
 * Copyright (C) 2004, Plüss Roland ( roland@rptd.dnsalias.net )
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
#include "../config.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "deCmdLineArgs.h"
#include "../common/exceptions.h"


// class deCmdLineArgs
////////////////////////
// constructor, destructor
deCmdLineArgs::deCmdLineArgs(){
	pArgs = NULL;
	pCount = 0;
}
deCmdLineArgs::~deCmdLineArgs(){
	if(pArgs){
		for(int i=0; i<pCount; i++) delete [] pArgs[i];
		delete [] pArgs;
	}
}
// management
const char *deCmdLineArgs::GetArgument(int index) const{
	if(index<0 || index>=pCount) THROW(dueOutOfBoundary);
	return (const char *)pArgs[index];
}
void deCmdLineArgs::AddArgument(const char *arg){
	if(!arg) THROW(dueInvalidParam);
	// enlarge array
	int newCount = pCount + 1;
	char **newArray = new char*[newCount];
	if(!newArray) THROW(dueOutOfMemory);
	if(pArgs){
		for(int i=0; i<pCount; i++) newArray[i] = pArgs[i];
		delete [] pArgs;
	}
	pArgs = newArray;
	// create new string with argument
	pArgs[pCount] = new char[strlen(arg)+1];
	if(!pArgs[pCount]) THROW(dueOutOfMemory);
	strcpy( pArgs[ pCount ], arg );
	pCount++;
}
void deCmdLineArgs::AddArgsSplit( const char *argLine ){
	if( ! argLine ) THROW( dueInvalidParam );
	// parse command line
	char *buffer = NULL;
	int cur = 0, start = 0, next, len = strlen( argLine );
	while( start < len ){
		// skip spaces
		while( start < len && isspace( argLine[ start ] ) ) start++;
		// parse string
		if( argLine[ start ] == '"' ){
			start++;
			cur = start;
			while( cur < len && argLine[ cur ] != '"' ) cur++;
			next = cur + 1;
		// parse non-string
		}else{
			cur = start;
			while( cur < len && ! isspace( argLine[ cur ] ) ) cur++;
			next = cur;
		}
		// add argument if not empty
		if( cur - start > 0 ){
			try{
				buffer = new char[ cur - start + 1 ];
				if( ! buffer ) THROW( dueOutOfMemory );
				strncpy( buffer, argLine + start, cur - start );
				buffer[ cur - start ] = '\0';
				AddArgument( buffer );
				delete [] buffer;
				buffer = NULL;
			}catch( duException ){
				if( buffer ) delete [] buffer;
				throw;
			}
		}
		// next round
		start = next;
	}
}
