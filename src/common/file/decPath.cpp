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
#include "../../config.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "decPath.h"
#include "../exceptions.h"



// definitions
////////////////

#define PATH_CURDIR				"."
#define PATH_PARENTDIR			".."
#if defined( OS_UNIX )
#	define PATH_SEPARATOR_CHAR		'/'
#	define PATH_SEPARATOR_STRING	"/"
#elif defined( OS_W32 )
#	define PATH_SEPARATOR_CHAR		'\\'
#	define PATH_SEPARATOR_STRING	"\\"
#endif



// class decPath
//////////////////

// Constructors and Destructors
/////////////////////////////////

decPath::decPath(){
	pPrefix = NULL;
	pComponents = NULL;
	pComponentCount = 0;
	pComponentSize = 0;
	pPath = NULL;
	SetPrefix( "" );
}

decPath::decPath( const decPath &path ){
	pPrefix = NULL;
	pComponents = NULL;
	pComponentCount = 0;
	pComponentSize = 0;
	pPath = NULL;
	try{
		SetFrom( path );
	}catch( duException ){
		pCleanUp();
		throw;
	}
}

decPath::~decPath(){
	pCleanUp();
}



// Management
///////////////

void decPath::SetPrefix( const char *prefix ){
	if( ! prefix ) THROW( dueInvalidParam );
	char *newStr = new char[ strlen( prefix ) + 1 ];
	if( ! newStr ) THROW( dueOutOfMemory );
	strcpy( newStr, prefix );
	if( pPrefix ) delete [] pPrefix;
	pPrefix = newStr;
}

void decPath::SetFromUnix( const char *path ){
	if( ! path ) THROW( dueInvalidParam );
	if( path[ 0 ] == '/' ){
		SetPrefix( "/" );
		RemoveAllComponents();
		pParseRelativePath( path + 1, '/' );
	}else{
		SetPrefix( "" );
		RemoveAllComponents();
		pParseRelativePath( path, '/' );
	}
}

void decPath::SetFromNative( const char *path ){
	if( ! path ) THROW( dueInvalidParam );
	int prefixLen = pGetPrefixLength( path );
	pSetPrefix( path, prefixLen );
	RemoveAllComponents();
	pParseRelativePath( path + prefixLen, PATH_SEPARATOR_CHAR );
}

void decPath::SetEmpty(){
	SetPrefix( "" );
	RemoveAllComponents();
}

const char *decPath::GetPathUnix(){
	if( pPath ){
		delete [] pPath;
		pPath = NULL;
	}
	pPath = pBuildPath( "/" );
	return ( const char * )pPath;
}

const char *decPath::GetPathNative(){
	if( pPath ){
		delete [] pPath;
		pPath = NULL;
	}
	pPath = pBuildPath( PATH_SEPARATOR_STRING );
	return ( const char * )pPath;
}

bool decPath::IsEmpty() const{
	return pComponentCount == 0;
}

bool decPath::IsAbsolute() const{
	return pPrefix[ 0 ] != '\0';
}

bool decPath::IsRelative() const{
	return pPrefix[ 0 ] == '\0';
}

void decPath::SetFrom( const decPath &path ){
	SetPrefix( path.GetPrefix() );
	RemoveAllComponents();
	AddPath( path );
}

void decPath::AddPath( const decPath &path ){
	int i, count = path.GetComponentCount();
	for( i=0; i<count; i++ ){
		AddComponent( path.GetComponent( i ) );
	}
}

void decPath::AddUnixPath( const char *path ){
	if( ! path ) THROW( dueInvalidParam );
	if( path[ 0 ] == '/' ){
		pParseRelativePath( path + 1, '/' );
	}else{
		pParseRelativePath( path, '/' );
	}
}

void decPath::AddNativePath( const char *path ){
	if( ! path ) THROW( dueInvalidParam );
	int prefixLen = pGetPrefixLength( path );
	if( prefixLen > 0 ){
		pParseRelativePath( path + prefixLen, PATH_SEPARATOR_CHAR );
	}else{
		pParseRelativePath( path, PATH_SEPARATOR_CHAR );
	}
}



// Component Management
/////////////////////////

const char *decPath::GetComponent( int index ) const{
	if( index < 0 || index >= pComponentCount ) THROW( dueInvalidParam );
	return ( const char * )pComponents[ index ];
}

const char *decPath::GetLastComponent() const{
	return GetComponent( pComponentCount - 1 );
}

void decPath::AddComponent( const char *component ){
	if( ! component ) THROW( dueInvalidParam );
	if( pComponentCount == pComponentSize ){
		int i, newSize = pComponentSize * 3 / 2 + 1;
		char **newArray = new char*[ newSize ];
		if( ! newArray ) THROW( dueOutOfMemory );
		if( pComponents ){
			for( i=0; i<pComponentCount; i++ ) newArray[ i ] = pComponents[ i ];
			delete [] pComponents;
		}
		pComponents = newArray;
		pComponentSize = newSize;
	}
	pComponents[ pComponentCount ] = new char[ strlen( component ) + 1 ];
	if( ! pComponents[ pComponentCount ] ) THROW( dueOutOfMemory );
	strcpy( pComponents[ pComponentCount ], component );
	pComponentCount++;
}

void decPath::RemoveComponent( int index ){
	if( index < 0 || index >= pComponentCount ) THROW( dueInvalidParam );
	int i;
	if( pComponents[ index ] ) delete [] pComponents[ index ];
	for( i=index+1; i<pComponentCount; i++ ) pComponents[ i - 1 ] = pComponents[ i ];
	pComponents[ pComponentCount - 1 ] = NULL;
	pComponentCount--;
}

void decPath::RemoveLastComponent(){
	RemoveComponent( pComponentCount - 1 );
}

void decPath::RemoveAllComponents(){
	int i;
	for( i=0; i<pComponentCount; i++ ){
		if( pComponents[ i ] ){
			delete [] pComponents[ i ];
			pComponents[ i ] = NULL;
		}
	}
	pComponentCount = 0;
}


	
// String Path Testing
////////////////////////

bool decPath::IsUnixPathAbsolute( const char *path ){
	if( ! path ) THROW( dueInvalidParam );
	return path[ 0 ] == '/';
}

bool decPath::IsNativePathAbsolute( const char *path ){
	if( ! path ) THROW( dueInvalidParam );
#if defined( OS_UNIX )
	return path[ 0 ] == '/';
#elif defined( OS_W32 )
	if( strlen( path ) < 3 ) return false;
	if( path[ 2 ] != '\\' ) return false;
	if( path[ 1 ] != ':' ) return false;
	if( path[ 0 ] >= 'A' && path[ 0 ] <= 'Z' ) return true;
	if( path[ 0 ] >= 'a' && path[ 0 ] <= 'z' ) return true;
	return 0;
#endif
}



// private functions
//////////////////////

void decPath::pParseRelativePath( const char *filename, int separator ){
	int offset = 0, deliIndex, len = strlen( filename );
	char *deli, *tempComp = NULL;
	// parse filename
	while( offset < len ){
		// find path separator
		deli = strchr( filename + offset, separator );
		deliIndex = deli ? deli - filename : len;
		// if delimiter is the first skip it
		if( deliIndex == 0 ){
			offset = deliIndex++;
			continue;
		}
		// do the parsing
		try{
			// extract component
			tempComp = new char[ deliIndex - offset + 1 ];
			if( ! tempComp ) THROW( dueOutOfMemory );
			strncpy( tempComp, filename + offset, deliIndex - offset );
			tempComp[ deliIndex - offset ] = '\0';
			offset = deliIndex + 1;
			// merge component with current components
			if( strcmp( tempComp, PATH_PARENTDIR ) == 0 ){
				if( pComponentCount == 0 ) THROW_INFO( dueInvalidParam, "Can not move into parent directory" );
				RemoveLastComponent();
			}else if( strcmp( tempComp, PATH_CURDIR ) != 0 ){
				AddComponent( tempComp );
			}
			// free temp comp
			delete [] tempComp;
			tempComp = NULL;
		}catch( duException ){
			if( tempComp ) delete [] tempComp;
			throw;
		}
	}
}

int decPath::pGetPrefixLength( const char *path ) const{
#if defined( OS_UNIX )
	return path[ 0 ] == '/' ? 1 : 0;
#elif defined( OS_W32 )
	if( strlen( path ) < 3 ) return 0;
	if( path[ 2 ] != '\\' ) return 0;
	if( path[ 1 ] != ':' ) return 0;
	if( path[ 0 ] >= 'A' && path[ 0 ] <= 'Z' ) return 3;
	if( path[ 0 ] >= 'a' && path[ 0 ] <= 'z' ) return 3;
	return 0;
#endif
}

void decPath::pSetPrefix( const char *path, int prefixLength ){
	if( ! path || prefixLength < 0  ) THROW( dueInvalidParam );
	char *newStr = new char[ prefixLength + 1 ];
	if( ! newStr ) THROW( dueOutOfMemory );
	strncpy( newStr, path, prefixLength );
	newStr[ prefixLength ] = '\0';
	if( pPrefix ) delete [] pPrefix;
	pPrefix = newStr;
}

char *decPath::pBuildPath( const char *separator ) const{
	int i, len;
	char *newPath = NULL;
	// determine length of buffer needed to hold path
	len = strlen( pPrefix );
	for( i=0; i<pComponentCount; i++ ){
		if( i > 0 ) len++;
		len += strlen( pComponents[ i ] );
	}
	// create buffer and build path
	try{
		newPath = new char[ len + 1 ];
		if( ! newPath ) THROW( dueOutOfMemory );
		strcpy( newPath, pPrefix );
		for( i=0; i<pComponentCount; i++ ){
			if( i > 0 ) strcat( newPath, separator );
			strcat( newPath, pComponents[ i ] );
		}
	}catch( duException ){
		if( newPath ) delete [] newPath;
		throw;
	}
	// finished
	return newPath;
}

void decPath::pCleanUp(){
	RemoveAllComponents();
	if( pComponents ) delete [] pComponents;
	if( pPrefix ) delete [] pPrefix;
	if( pPath ) delete [] pPath;
}
