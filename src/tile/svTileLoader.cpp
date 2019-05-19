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
#include "../sprite/svSprite.h"
#include "../sprite/svSpriteImage.h"
#include "svTileLoader.h"
#include "../common/file/decBaseFileReader.h"
#include "../common/exceptions.h"



// definitions
////////////////

#define DRPG_TILE_0_03		0

#define DRPG_RED(p)			( ( ( p ) >> 11 ) & 0x1f )
#define DRPG_GREEN(p)		( ( ( p ) >> 5 ) & 0x3f )
#define DRPG_BLUE(p)		( ( p ) & 0x1f )
#define DRPG_COLOR(r,g,b)	( unsigned short )( ( ( ( r ) & 0x1f ) << 11 ) \
								+ ( ( ( g ) & 0x3f ) << 5 ) + ( ( b ) & 0x1f ) )

struct svTileDef{
	int width;
	int height;
	int offset;
	int value;
};



// class svTileLoader
///////////////////////

// constructor, destructor
////////////////////////////

svTileLoader::svTileLoader(){
	//pDebugLevel = SV_DEBUG_LEVEL_NONE;
	pDebugLevel = SV_DEBUG_LEVEL_MINIMAL;
	//pDebugLevel = SV_DEBUG_LEVEL_HEAVY;
}

svTileLoader::~svTileLoader(){
	pCleanUp();
}



// Management
///////////////

svSprite *svTileLoader::LoadTile( decBaseFileReader *reader ){
	if( ! reader ) THROW( dueInvalidParam );
	svSprite *sprite = NULL;
	svSpriteImage *spriteImage = NULL;
	svColor *pixelLine;
	int i, j, x, y;
	char signature[ 11 ];
	int tileType;
	int tileCount;
	svTileDef *tiles = NULL;
	int lastTileOffset;
	unsigned short *tilesData = NULL;
	int startOffset, endOffset, pos;
	int runCount, runOffset, runLength;
	unsigned short frameColor;
	int lineCount;
	int unknown;
	try{
		// read header
		memset( &signature, '\0', 11 );
		reader->Read( &signature, 10 );
		if( strcmp( signature, "DCTILE0.03" ) == 0 ){
			if( pDebugLevel >= SV_DEBUG_LEVEL_MINIMAL ){
				printf( "[DEBUG] Tile type 0.03 found.\n" );
			}
			tileType = DRPG_TILE_0_03;
		}else{
			printf( "[DEBUG] Invalid signature '%s'.\n", signature );
			THROW( dueInvalidParam );
		}
		unknown = reader->ReadInt(); // unknown1
		if( pDebugLevel >= SV_DEBUG_LEVEL_MINIMAL ){
			printf( "[DEBUG] Value %i\n", unknown );
		}
		unknown = reader->ReadInt(); // unknown2
		if( pDebugLevel >= SV_DEBUG_LEVEL_MINIMAL ){
			printf( "[DEBUG] Value %i\n", unknown );
		}
		tileCount = reader->ReadInt();
		if( tileCount < 1 ){
			printf( "[DEBUG] Invalid tile count %i found.\n", tileCount );
			THROW( dueInvalidParam );
		}
		if( pDebugLevel >= SV_DEBUG_LEVEL_MINIMAL ){
			printf( "[DEBUG] Count of tiles: %i\n", tileCount );
		}
		// read tiles information
		tiles = new svTileDef[ tileCount ];
		if( ! tiles ) THROW( dueOutOfMemory );
		for( i=0; i<tileCount; i++ ){
			tiles[ i ].width = reader->ReadInt();
			if( tiles[ i ].width < 1 ){
				printf( "[DEBUG] Invalid tile width %i found for tile %i.\n",
					tiles[ i ].width, i );
				THROW( dueInvalidParam );
			}
		}
		for( i=0; i<tileCount; i++ ){
			tiles[ i ].height = reader->ReadInt();
			if( tiles[ i ].height < 1 ){
				printf( "[DEBUG] Invalid tile height %i found for tile %i.\n",
					tiles[ i ].height, i );
				THROW( dueInvalidParam );
			}
		}
		for( i=0; i<tileCount; i++ ){
			tiles[ i ].offset = reader->ReadInt();
			if( tiles[ i ].offset < 0 ){
				printf( "[DEBUG] Invalid tile offset %i found for tile %i.\n",
					tiles[ i ].offset, i );
				THROW( dueInvalidParam );
			}
		}
		lastTileOffset = reader->ReadInt();
		if( lastTileOffset < 1 ){
			printf( "[DEBUG] Invalid last tile offset %i found.\n", lastTileOffset );
			THROW( dueInvalidParam );
		}
		if( pDebugLevel >= SV_DEBUG_LEVEL_MINIMAL ){
			printf( "[DEBUG] Last Tile Offset: %i.\n", lastTileOffset );
		}
		// output debug information about the tiles collected so far
		if( pDebugLevel >= SV_DEBUG_LEVEL_HEAVY ){
			for( i=0; i<tileCount; i++ ){
				printf( "[DEBUG] Tile %i: Width=%i Height=%i Offset=%i.\n",
					i, tiles[ i ].width, tiles[ i ].height, tiles[ i ].offset );
			}
		}
		// read tile data
		tilesData = new unsigned short[ lastTileOffset ];
		if( ! tilesData ) THROW( dueOutOfMemory );
		reader->Read( tilesData, sizeof( unsigned short ) * lastTileOffset );
		if( pDebugLevel >= SV_DEBUG_LEVEL_MINIMAL ){
			printf( "[DEBUG] %i tile data entries read.\n", lastTileOffset );
		}
		// read tile 'additional' value.
		for( i=0; i<tileCount; i++ ){
			tiles[ i ].value = reader->ReadByte();
		}
		
		// create sprite
		sprite = new svSprite;
		if( ! sprite ) THROW( dueOutOfMemory );
		// create an image for each tile
		for( i=0; i<tileCount; i++ ){
			if( pDebugLevel >= SV_DEBUG_LEVEL_MEDIUM ){
				printf( "[DEBUG] Processing Tile %i...\n", i );
			}
			// create sprite image
			spriteImage = new svSpriteImage( tiles[ i ].width, tiles[ i ].height );
			if( ! spriteImage ) THROW( dueOutOfMemory );
			//spriteImage->SetBlocking( tiles[ i ].blocking );
			// fill the entire image with transparent black
			for( y=0; y<tiles[ i ].height; y++ ){
				pixelLine = spriteImage->GetLineAt( y );
				memset( pixelLine, '\0', sizeof( svColor ) * tiles[ i ].width );
			}
			// read pixel runs from tile data
			startOffset = tiles[ i ].offset;
			if( i + 1 < tileCount ){
				endOffset = tiles[ i + 1 ].offset;
			}else{
				endOffset = lastTileOffset;
			}
			pos = startOffset;
			if( pDebugLevel >= SV_DEBUG_LEVEL_HEAVY ){
				printf( "[DEBUG] Reading Runs from %i to %i\n", startOffset, endOffset );
			}
			y = 0;
			x = 0;
			lineCount = tilesData[ pos++ ];
			if( lineCount != tiles[ i ].height ){
				printf( "[DEBUG] Line Count %i does not match tile height %i.\n",
					lineCount, tiles[ i ].height );
				THROW( dueInvalidParam );
			}
			while( y < lineCount ){
				pixelLine = spriteImage->GetLineAt( y++ );
				if( pos > endOffset ){
					printf( "[DEBUG] Run Count leaks over tile boundary.\n" );
					THROW( dueInvalidParam );
				}
				runCount = tilesData[ pos++ ];
				if( pDebugLevel >= SV_DEBUG_LEVEL_HEAVY ){
					printf( "[DEBUG] Line %i, Run Count: %i.\n", y, runCount );
				}
				x = 0;
				while( runCount > 0 ){
					if( pos + 2 > endOffset ){
						printf( "[DEBUG] Run Header leaks over tile boundary.\n" );
						THROW( dueInvalidParam );
					}
					runOffset = tilesData[ pos++ ];
					if( x + runOffset > tiles[ i ].width ){
						printf( "[DEBUG] Run Offset %i is larger than tile width %i.\n",
							x + runOffset, tiles[ i ].width );
						THROW( dueInvalidParam );
					}
					x += runOffset;
					runLength = tilesData[ pos++ ];
					if( pDebugLevel >= SV_DEBUG_LEVEL_HEAVY ){
						printf( "[DEBUG] Run: Offset=%i(%i) Length=%i.\n",
							runOffset, x, runLength );
					}
					if( pos + runLength > endOffset ){
						printf( "[DEBUG] Run Data leacks over tile boundary.\n" );
						THROW( dueInvalidParam );
					}
					if( x + runLength > tiles[ i ].width ){
						printf( "[DEBUG] Run Data is longer than tile width.\n" );
						THROW( dueInvalidParam );
					}
					while( runLength > 0 ){
						frameColor = tilesData[ pos++ ];
						pixelLine[ x ].red = DRPG_RED( frameColor ) << 3;
						pixelLine[ x ].green = DRPG_GREEN( frameColor ) << 2;
						pixelLine[ x ].blue = DRPG_BLUE( frameColor ) << 3;
						pixelLine[ x ].alpha = 255;
						x++;
						runLength--;
					}
					runCount--;
				}
			}
			// add sprite image
			sprite->AddImage( spriteImage );
			spriteImage = NULL;
		}
		
		// clean up
		if( tilesData ) delete [] tilesData;
		if( tiles ) delete [] tiles;
	}catch( duException ){
		if( spriteImage ) delete spriteImage;
		if( sprite ) delete sprite;
		if( tilesData ) delete [] tilesData;
		if( tiles ) delete [] tiles;
		throw;
	}
	// finished
	return sprite;
}



// Private Functions
//////////////////////

void svTileLoader::pCleanUp(){
}
