/* 
 * Digimon RPG Map Viewer
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
#include "svMapLoader.h"
#include "../sprite/svSprite.h"
#include "../tile/svTileLoader.h"
#include "../common/file/decDiscFileReader.h"
#include "../common/file/decPath.h"
#include "../common/exceptions.h"



// definitions
////////////////

#define DRPG_MAP_1_08		0



// class svMapLoader
//////////////////////

// constructor, destructor
////////////////////////////

svMapLoader::svMapLoader(){
	pDebugLevel = SV_DEBUG_LEVEL_NONE;
	//pDebugLevel = SV_DEBUG_LEVEL_MINIMAL;
	//pDebugLevel = SV_DEBUG_LEVEL_HEAVY;
}

svMapLoader::~svMapLoader(){
	pCleanUp();
}



// Management
///////////////

svMap *svMapLoader::LoadMap( decBaseFileReader *reader ){
	if( ! reader ) THROW( dueInvalidParam );
	decDiscFileReader *linkedReader = NULL;
	svTileLoader tileLoader;
	svMap *map = NULL;
	svMapField *field;
	svSprite *tile = NULL;
	svSprite *object = NULL;
	int i, j, x, y;
	char signature[ 8 ];
	char mapName[ 22 ];
	char filename[ 21 ];
	int mapType;
	int fieldXCount;
	int fieldYCount;
	int fieldWidth;
	int fieldHeight;
	int flags;
	int objectIndex;
	int tileFileIndex;
	int tileIndex;
	int count;
	decPath path;
	try{
		// read header
		memset( &signature, '\0', 8 );
		reader->Read( &signature, 7 );
		if( strcmp( signature, "MAP1.08" ) == 0 ){
			if( pDebugLevel >= SV_DEBUG_LEVEL_MINIMAL ){
				printf( "[DEBUG] Map type 1.08 found.\n" );
			}
			mapType = DRPG_MAP_1_08;
		}else{
			printf( "[DEBUG] Invalid signature '%s'.\n", signature );
			THROW( dueInvalidParam );
		}
		memset( &mapName, '\0', 22 );
		reader->Read( &mapName, 21 );
		if( pDebugLevel >= SV_DEBUG_LEVEL_MINIMAL ){
			printf( "[DEBUG] Map Name '%s'\n", mapName );
		}
		fieldXCount = reader->ReadInt();
		if( fieldXCount < 1 ){
			printf( "[DEBUG] Invalid field X count %i found.\n", fieldXCount );
			THROW( dueInvalidParam );
		}
		fieldYCount = reader->ReadInt();
		if( fieldYCount < 1 ){
			printf( "[DEBUG] Invalid field Y count %i found.\n", fieldYCount );
			THROW( dueInvalidParam );
		}
		fieldWidth = reader->ReadInt();
		if( fieldWidth < 1 ){
			printf( "[DEBUG] Invalid field width %i found.\n", fieldWidth );
			THROW( dueInvalidParam );
		}
		fieldHeight = reader->ReadInt();
		if( fieldHeight < 1 ){
			printf( "[DEBUG] Invalid field height %i found.\n", fieldHeight );
			THROW( dueInvalidParam );
		}
		flags = reader->ReadInt();
		if( pDebugLevel >= SV_DEBUG_LEVEL_MINIMAL ){
			printf( "[DEBUG] Fields: XCount=%i YCount=%i Width=%i Height=%i.\n",
				fieldXCount, fieldYCount, fieldWidth, fieldHeight );
		}
		
		// create map
		map = new svMap( fieldXCount, fieldYCount, fieldWidth, fieldHeight );
		if( ! map ) THROW( dueOutOfMemory );
		
		// load fields. we do not check the indices right now as the
		// tiles and objects follow after the fields.
		for( y=0; y<fieldYCount; y++ ){
			for( x=0; x<fieldXCount; x++ ){
				field = map->GetFieldAt( x, y );
				// an unknown value
				reader->ReadShort();
				// another unknown value
				reader->ReadShort();
				// object index ( and some unknown index )
				objectIndex = reader->ReadInt();
				if( objectIndex == 9999 ) objectIndex = -1; // STRANGE CASE!
				reader->ReadInt(); // what for?
				field->SetObjectIndex( objectIndex );
				// tile file and tile index. accompained by an unknown
				// field with either 0 or some garbage.
				tileFileIndex = reader->ReadShort();
				reader->ReadShort(); // garbage
				tileIndex = reader->ReadInt();
				field->SetTileIndex( tileFileIndex, tileIndex );
				// some flags followed by a garbage field
				flags = reader->ReadShort();
				field->SetFlags( flags );
				reader->ReadShort(); // garbage
				// debug output
				if( pDebugLevel >= SV_DEBUG_LEVEL_HEAVY ){
					printf( "[DEBUG] Field %i,%i: Object=%i TileFile=%i Tile=%i Flags=%i.\n",
						x, y, objectIndex, tileFileIndex, tileIndex, flags );
				}
			}
		}
		
		// load tiles.
		count = reader->ReadShort();
		if( count < 0 ){
			printf( "[DEBUG] Invalid tile count %i found.\n", count );
			THROW( dueInvalidParam );
		}
		for( i=0; i<count; i++ ){
			// read tile filename
			memset( &filename, '\0', 21 );
			reader->Read( &filename, 20 );
			if( pDebugLevel >= SV_DEBUG_LEVEL_MINIMAL ){
				printf( "[DEBUG] Tile File %i: Filename '%s'\n", i, filename );
			}
			// init path to tile file
			path.SetFromNative( reader->GetFilename() );
			path.RemoveLastComponent();
			path.AddNativePath( filename );
			// open file for reading
			linkedReader = new decDiscFileReader( path.GetPathNative() );
			if( ! linkedReader ) THROW( dueFileNotFound );
			// load tile using a tile loader
			tile = tileLoader.LoadTile( linkedReader );
			// close file
			delete linkedReader;
			linkedReader = NULL;
			// make sure the tile is valid
			if( tile->GetImageCount() < 1 ) THROW( dueInvalidParam );
			// set filename to what we loaded it from
			tile->SetFilename( filename );
			// add tile
			map->AddTile( tile );
			tile = NULL;
		}
		
		// load objects.
		count = reader->ReadShort();
		if( count < 0 ){
			printf( "[DEBUG] Invalid object count %i found.\n", count );
			THROW( dueInvalidParam );
		}
		for( i=0; i<count; i++ ){
			// read object filename
			memset( &filename, '\0', 21 );
			reader->Read( &filename, 20 );
			if( pDebugLevel >= SV_DEBUG_LEVEL_MINIMAL ){
				printf( "[DEBUG] Object File %i: Filename '%s'\n", i, filename );
			}
			// create object ( temporary )
			object = new svSprite;
			if( ! object ) THROW( dueOutOfMemory );
			/*
			// init path to tile file
			path.SetFromNative( reader->GetFilename() );
			path.RemoveLastComponent();
			path.AddNativePath( filename );
			// open file for reading
			linkedReader = new decDiscFileReader( path.GetPathNative() );
			if( ! linkedReader ) THROW( dueFileNotFound );
			// load object using a tile loader
			tile = tileLoader.LoadSprite( linkedReader );
			// close file
			delete linkedReader;
			linkedReader = NULL;
			// make sure the tile is valid
			if( tile->GetImageCount() < 1 ) THROW( dueInvalidParam );
			*/
			// set filename to what we loaded it from
			object->SetFilename( filename );
			// add object
			map->AddObject( object );
			object = NULL;
		}
	}catch( duException ){
		if( linkedReader ) delete linkedReader;
		if( object ) delete object;
		if( tile ) delete tile;
		if( map ) delete [] map;
		throw;
	}
	// finished
	return map;
}



// Private Functions
//////////////////////

void svMapLoader::pCleanUp(){
}
