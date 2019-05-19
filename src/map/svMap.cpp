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
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "svMap.h"
#include "svMapField.h"
#include "../sprite/svSprite.h"
#include "../common/exceptions.h"



// class svMap
///////////////////

// constructor, destructor
////////////////////////////

svMap::svMap( int fieldXCount, int fieldYCount, int fieldWidth, int fieldHeight ){
	if( fieldXCount < 1 || fieldYCount < 1 || fieldWidth < 1 || fieldHeight < 1 ) THROW( dueInvalidParam );
	int i, fieldCount = fieldXCount * fieldYCount;
	pMapName = NULL;
	pFieldXCount = fieldXCount;
	pFieldYCount = fieldYCount;
	pFieldWidth = fieldWidth;
	pFieldHeight = fieldHeight;
	pTiles = NULL;
	pTileCount = 0;
	pTileSize = 0;
	pObjects = NULL;
	pObjectCount = 0;
	pObjectSize = 0;
	pFields = NULL;
	pFieldCount = 0;
	pMapWidth = fieldXCount * fieldWidth;
	pMapHeight = fieldYCount * fieldHeight;
	try{
		SetMapName( "Map" );
		pFields = new svMapField[ fieldCount ];
		if( ! pFields ) THROW( dueOutOfMemory );
		pFieldCount = fieldCount;
	}catch( duException ){
		pCleanUp();
		throw;
	}
}

svMap::~svMap(){
	pCleanUp();
}



// Management
///////////////

void svMap::SetMapName( const char *name ){
	if( ! name || ! name[ 0 ] ) THROW( dueInvalidParam );
	char *newStr = new char[ strlen( name ) + 1 ];
	if( ! newStr ) THROW( dueOutOfMemory );
	strcpy( newStr, name );
	if( pMapName ) delete [] pMapName;
	pMapName = newStr;
}



// Tile  Management
/////////////////////////

svSprite *svMap::GetTileAt( int index ) const{
	if( index < 0 || index >= pTileCount ) THROW( dueInvalidParam );
	return pTiles[ index ];
}

bool svMap::HasTile( svSprite *tile ) const{
	return pFindTile( tile ) != -1;
}

void svMap::AddTile( svSprite *tile ){
	if( ! tile ) THROW( dueInvalidParam );
	if( HasTile( tile ) ) THROW( dueInvalidParam );
	if( pTileCount == pTileSize ){
		int i, newSize = pTileSize * 3 / 2 + 1;
		svSprite **newArray = new svSprite*[ newSize ];
		if( ! newArray ) THROW( dueOutOfMemory );
		if( pTiles ){
			for( i=0; i<pTileCount; i++ ) newArray[ i ] = pTiles[ i ];
			delete [] pTiles;
		}
		pTiles = newArray;
		pTileSize = newSize;
	}
	pTiles[ pTileCount ] = tile;
	pTileCount++;
}



// Object  Management
/////////////////////////

svSprite *svMap::GetObjectAt( int index ) const{
	if( index < 0 || index >= pObjectCount ) THROW( dueInvalidParam );
	return pObjects[ index ];
}

bool svMap::HasObject( svSprite *object ) const{
	return pFindObject( object ) != -1;
}

void svMap::AddObject( svSprite *object ){
	if( ! object ) THROW( dueInvalidParam );
	if( HasObject( object ) ) THROW( dueInvalidParam );
	if( pObjectCount == pObjectSize ){
		int i, newSize = pObjectSize * 3 / 2 + 1;
		svSprite **newArray = new svSprite*[ newSize ];
		if( ! newArray ) THROW( dueOutOfMemory );
		if( pObjects ){
			for( i=0; i<pObjectCount; i++ ) newArray[ i ] = pObjects[ i ];
			delete [] pObjects;
		}
		pObjects = newArray;
		pObjectSize = newSize;
	}
	pObjects[ pObjectCount ] = object;
	pObjectCount++;
}



// Field Management
/////////////////////

svMapField *svMap::GetFieldAt( int x, int y ) const{
	if( x < 0 || x >= pFieldXCount || y < 0 || y >= pFieldYCount ) THROW( dueInvalidParam );
	return pFields + ( pFieldXCount * y + x );
}



// Private Functions
//////////////////////

void svMap::pCleanUp(){
	int i;
	if( pFields ) delete [] pFields;
	if( pTiles ){
		for( i=0; i<pTileCount; i++ ){
			if( pTiles[ i ] ) delete pTiles[ i ];
		}
		delete [] pTiles;
	}
	if( pMapName ) delete [] pMapName;
}

int svMap::pFindTile( svSprite *tile ) const{
	int i;
	if( tile ){
		for( i=0; i<pTileCount; i++ ){
			if( pTiles[ i ] == tile ) return i;
		}
	}
	return -1;
}

int svMap::pFindObject( svSprite *object ) const{
	int i;
	if( object ){
		for( i=0; i<pObjectCount; i++ ){
			if( pObjects[ i ] == object ) return i;
		}
	}
	return -1;
}
