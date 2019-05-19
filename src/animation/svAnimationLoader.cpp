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
#include "svAnimationSet.h"
#include "svAnimation.h"
#include "svAnimationLoader.h"
#include "../common/file/decBaseFileReader.h"
#include "../common/exceptions.h"



// definitions
////////////////

#define DRPG_ANIMATION_0_5		0



// class svAnimationLoader
////////////////////////////

// constructor, destructor
////////////////////////////

svAnimationLoader::svAnimationLoader(){
	pDebugLevel = SV_DEBUG_LEVEL_NONE;
	//pDebugLevel = SV_DEBUG_LEVEL_MINIMAL;
	//pDebugLevel = SV_DEBUG_LEVEL_HEAVY;
}

svAnimationLoader::~svAnimationLoader(){
	pCleanUp();
}



struct svAnimInfo{
	int unknown1;
	int unknown2;
	int unknown3;
};



// Management
///////////////

svAnimationSet *svAnimationLoader::LoadAnimation( decBaseFileReader *reader ){
	if( ! reader ) THROW( dueInvalidParam );
	svAnimationSet *animSet = NULL;
	svAnimation *anim = NULL;
	int animType, animFlag;
	int i;
	char signature[ 15 ];
	char spriteFile[ 21 ];
	char animName[ 20 ];
	int animCount;
	int startFrame, endFrame, frameCount;
	svAnimInfo *animInfos = NULL;
	try{
		// read header
		memset( &signature, '\0', 15 );
		reader->Read( &signature, 14 );
		if( strcmp( signature, "DCANIMATION0.5" ) == 0 ){
			if( pDebugLevel >= SV_DEBUG_LEVEL_MINIMAL ){
				printf( "[DEBUG] Animation type 0.5 found.\n" );
			}
			animType = DRPG_ANIMATION_0_5;
		}else{
			printf( "[DEBUG] Invalid signature '%s'.\n", signature );
			THROW( dueInvalidParam );
		}
		// create animation set
		animSet = new svAnimationSet;
		if( ! animSet ) THROW( dueOutOfMemory );
		// read sprite file to use
		memset( &spriteFile, '\0', 21 );
		reader->Read( &spriteFile, 20 );
		animSet->SetSpriteFile( spriteFile );
		if( pDebugLevel >= SV_DEBUG_LEVEL_MINIMAL ){
			printf( "[DEBUG] Sprite file: %s\n", spriteFile );
		}
		// read animation frame informations
		animFlag = reader->ReadInt();
		if( pDebugLevel >= SV_DEBUG_LEVEL_MINIMAL ){
			printf( "[DEBUG] Animation flag: %i\n", animFlag );
		}
		animCount = reader->ReadInt();
		if( animCount < 1 ){
			printf( "[DEBUG] Invalid animation count %i found.\n", animCount );
			THROW( dueInvalidParam );
		}
		if( pDebugLevel >= SV_DEBUG_LEVEL_MINIMAL ){
			printf( "[DEBUG] Count of animations: %i\n", animCount );
		}
		animInfos = new svAnimInfo[ animCount ];
		if( ! animInfos ) THROW( dueOutOfMemory );
		for( i=0; i<animCount; i++ ){
			animInfos[ i ].unknown1 = reader->ReadInt();
			animInfos[ i ].unknown2 = reader->ReadInt();
			animInfos[ i ].unknown3 = reader->ReadInt();
		}
		// output debug information about the animations collected so far
		if( pDebugLevel >= SV_DEBUG_LEVEL_HEAVY ){
			for( i=0; i<animCount; i++ ){
				printf( "[DEBUG] Animation %i: %i, %i, %i.\n",
					i, animInfos[ i ].unknown1, animInfos[ i ].unknown2, animInfos[ i ].unknown3 );
			}
		}
		// read animations
		for( i=0; i<animCount; i++ ){
			startFrame = reader->ReadShort();
			if( startFrame < 0 ){
				printf( "[DEBUG] Invalid start frame %i.\n", startFrame );
				THROW( dueInvalidParam );
			}
			endFrame = reader->ReadShort();
			if( endFrame < startFrame ){
				printf( "[DEBUG] Invalid end frame %i ( start frame %i ).\n",
					endFrame, startFrame );
				THROW( dueInvalidParam );
			}
			frameCount = reader->ReadShort();
			if( frameCount > 0 && frameCount != endFrame - startFrame + 1 ){
				printf( "[DEBUG] Invalid frame count %i ( start frame %i, end frame %i ).\n",
					frameCount, startFrame, endFrame );
				THROW( dueInvalidParam );
			}
			if( pDebugLevel >= SV_DEBUG_LEVEL_HEAVY ){
				printf( "[DEBUG] Animation %i: Start=%i, End=%i, Count=%i.\n",
					i, startFrame, endFrame, frameCount );
			}
			// create animation
			anim = new svAnimation( startFrame, endFrame );
			if( ! anim ) THROW( dueOutOfMemory );
			sprintf( ( char* )&animName, "Animation %i", i );
			anim->SetName( animName );
			anim->SetPlaybackSpeed( 2 );
			animSet->AddAnimation( anim );
			anim = NULL;
		}
		
		// clean up
		if( pDebugLevel >= SV_DEBUG_LEVEL_MINIMAL ){
			printf( "[DEBUG] Finished loading animation.\n" );
		}
		if( animInfos ) delete [] animInfos;
	}catch( duException ){
		if( anim ) delete anim;
		if( animSet ) delete animSet;
		if( animInfos ) delete [] animInfos;
		throw;
	}
	// finished
	return animSet;
}



// Private Functions
//////////////////////

void svAnimationLoader::pCleanUp(){
}
