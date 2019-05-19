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
#include "svSprite.h"
#include "svSpriteImage.h"
#include "svSpriteLoader.h"
#include "../common/file/decBaseFileReader.h"
#include "../common/exceptions.h"



// definitions
////////////////

#define DRPG_SPRITE_1_0		0
#define DRPG_SPRITE_0_5		1

#define DRPG_RED(p)			( ( ( p ) >> 11 ) & 0x1f )
#define DRPG_GREEN(p)		( ( ( p ) >> 5 ) & 0x3f )
#define DRPG_BLUE(p)		( ( p ) & 0x1f )
#define DRPG_COLOR(r,g,b)	( unsigned short )( ( ( ( r ) & 0x1f ) << 11 ) \
								+ ( ( ( g ) & 0x3f ) << 5 ) + ( ( b ) & 0x1f ) )

struct svSpriteFrame{
	int width;
	int height;
	int offset;
};



// class svSpriteLoader
/////////////////////////

// constructor, destructor
////////////////////////////

svSpriteLoader::svSpriteLoader(){
	pDebugLevel = SV_DEBUG_LEVEL_NONE;
	//pDebugLevel = SV_DEBUG_LEVEL_MINIMAL;
	//pDebugLevel = SV_DEBUG_LEVEL_HEAVY;
}

svSpriteLoader::~svSpriteLoader(){
	pCleanUp();
}



// Management
///////////////

svSprite *svSpriteLoader::LoadSprite( decBaseFileReader *reader ){
	if( ! reader ) THROW( dueInvalidParam );
	svSprite *sprite = NULL;
	svSpriteImage *spriteImage = NULL;
	svColor *pixelLine;
	int i, j, x, y;
	char signature[ 12 ];
	int spriteType;
	int frameCount;
	svSpriteFrame *frames = NULL;
	int frameDataSize;
	unsigned short *framesData = NULL;
	int startOffset, endOffset, pos;
	int runCount, runOffset, runLength;
	unsigned short frameColor;
	int lineCount;
	try{
		// read header
		memset( &signature, '\0', 12 );
		reader->Read( &signature, 11 );
		if( strcmp( signature, "DCSPRITE10" ) == 0 ){
			if( pDebugLevel >= SV_DEBUG_LEVEL_MINIMAL ){
				printf( "[DEBUG] Sprite type 10 found.\n" );
			}
			spriteType = DRPG_SPRITE_1_0;
		}else if( strcmp( signature, "DCSPRITE0.5" ) == 0 ){
			if( pDebugLevel >= SV_DEBUG_LEVEL_MINIMAL ){
				printf( "[DEBUG] Sprite type 0.5 found.\n" );
			}
			spriteType = DRPG_SPRITE_0_5;
		}else{
			printf( "[DEBUG] Invalid signature '%s'.\n", signature );
			THROW( dueInvalidParam );
		}
		frameCount = reader->ReadInt();
		if( frameCount < 1 ){
			printf( "[DEBUG] Invalid frame count %i found.\n", frameCount );
			THROW( dueInvalidParam );
		}
		if( pDebugLevel >= SV_DEBUG_LEVEL_MINIMAL ){
			printf( "[DEBUG] Count of frames: %i\n", frameCount );
		}
		// read frames information
		frames = new svSpriteFrame[ frameCount ];
		if( ! frames ) THROW( dueOutOfMemory );
		for( i=0; i<frameCount; i++ ){
			frames[ i ].width = reader->ReadInt();
			if( frames[ i ].width < 1 ){
				printf( "[DEBUG] Invalid frame width %i found for frame %i.\n",
					frames[ i ].width, frameCount );
				THROW( dueInvalidParam );
			}
		}
		for( i=0; i<frameCount; i++ ){
			frames[ i ].height = reader->ReadInt();
			if( frames[ i ].height < 1 ){
				printf( "[DEBUG] Invalid frame height %i found for frame %i.\n",
					frames[ i ].height, frameCount );
				THROW( dueInvalidParam );
			}
		}
		frameDataSize = reader->ReadInt();
		if( frameDataSize < 1 ){
			printf( "[DEBUG] Invalid frame data size %i found.\n", frameDataSize );
			THROW( dueInvalidParam );
		}
		if( pDebugLevel >= SV_DEBUG_LEVEL_MINIMAL ){
			printf( "[DEBUG] Frame Data Size: %i.\n", frameDataSize );
		}
		for( i=0; i<frameCount; i++ ){
			frames[ i ].offset = reader->ReadInt();
			if( frames[ i ].offset < 0 || frames[ i ].offset > frameDataSize ){
				printf( "[DEBUG] Invalid frame offset %i found for frame %i.\n",
					frames[ i ].offset, frameCount );
				THROW( dueInvalidParam );
			}
		}
		// output debug information about the frames collected so far
		if( pDebugLevel >= SV_DEBUG_LEVEL_HEAVY ){
			for( i=0; i<frameCount; i++ ){
				printf( "[DEBUG] Frame %i: Width=%i Height=%i Offset=%i.\n",
					i, frames[ i ].width, frames[ i ].height, frames[ i ].offset );
			}
		}
		// read frama data
		framesData = new unsigned short[ frameDataSize ];
		if( ! framesData ) THROW( dueOutOfMemory );
		reader->Read( framesData, sizeof( unsigned short ) * frameDataSize );
		if( pDebugLevel >= SV_DEBUG_LEVEL_MINIMAL ){
			printf( "[DEBUG] %i frame data entries read.\n", frameDataSize );
		}
		
		// create sprite
		sprite = new svSprite;
		if( ! sprite ) THROW( dueOutOfMemory );
		// create an image for each sprite frame
		for( i=0; i<frameCount; i++ ){
			if( pDebugLevel >= SV_DEBUG_LEVEL_MEDIUM ){
				printf( "[DEBUG] Processing Frame %i...\n", i );
			}
			// create sprite image
			spriteImage = new svSpriteImage( frames[ i ].width, frames[ i ].height );
			if( ! spriteImage ) THROW( dueOutOfMemory );
			// fill the entire image with transparent black
			for( y=0; y<frames[ i ].height; y++ ){
				pixelLine = spriteImage->GetLineAt( y );
				memset( pixelLine, '\0', sizeof( svColor ) * frames[ i ].width );
			}
			// read pixel runs from frame data
			startOffset = frames[ i ].offset;
			if( i + 1 < frameCount ){
				endOffset = frames[ i + 1 ].offset;
			}else{
				endOffset = frameDataSize;
			}
			pos = startOffset;
			if( pDebugLevel >= SV_DEBUG_LEVEL_HEAVY ){
				printf( "[DEBUG] Reading Runs from %i to %i\n", startOffset, endOffset );
			}
			y = 0;
			x = 0;
			lineCount = framesData[ pos++ ];
			if( lineCount != frames[ i ].height ){
				printf( "[DEBUG] Line Count %i does not match frame height %i.\n",
					lineCount, frames[ i ].height );
				THROW( dueInvalidParam );
			}
			while( y < lineCount ){
				pixelLine = spriteImage->GetLineAt( y++ );
				if( pos > endOffset ){
					printf( "[DEBUG] Run Count leaks over frame boundary.\n" );
					THROW( dueInvalidParam );
				}
				runCount = framesData[ pos++ ];
				if( pDebugLevel >= SV_DEBUG_LEVEL_HEAVY ){
					printf( "[DEBUG] Line %i, Run Count: %i.\n", y, runCount );
				}
				x = 0;
				while( runCount > 0 ){
					if( pos + 2 > endOffset ){
						printf( "[DEBUG] Run Header leaks over frame boundary.\n" );
						THROW( dueInvalidParam );
					}
					runOffset = framesData[ pos++ ];
					if( x + runOffset > frames[ i ].width ){
						printf( "[DEBUG] Run Offset %i is larger than frame width %i.\n",
							x + runOffset, frames[ i ].width );
						THROW( dueInvalidParam );
					}
					x += runOffset;
					runLength = framesData[ pos++ ];
					if( pDebugLevel >= SV_DEBUG_LEVEL_HEAVY ){
						printf( "[DEBUG] Run: Offset=%i(%i) Length=%i.\n",
							runOffset, x, runLength );
					}
					if( pos + runLength > endOffset ){
						printf( "[DEBUG] Run Data leacks over frame boundary.\n" );
						THROW( dueInvalidParam );
					}
					if( x + runLength > frames[ i ].width ){
						printf( "[DEBUG] Run Data is longer than frame width.\n" );
						THROW( dueInvalidParam );
					}
					while( runLength > 0 ){
						frameColor = framesData[ pos++ ];
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
		if( framesData ) delete [] framesData;
		if( frames ) delete [] frames;
	}catch( duException ){
		if( spriteImage ) delete spriteImage;
		if( sprite ) delete sprite;
		if( framesData ) delete [] framesData;
		if( frames ) delete [] frames;
		throw;
	}
	// finished
	return sprite;
}



// Private Functions
//////////////////////

void svSpriteLoader::pCleanUp(){
}
