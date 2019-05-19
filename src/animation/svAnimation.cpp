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
#include "svAnimation.h"
#include "../common/exceptions.h"



// class svAnimation
//////////////////////

// constructor, destructor
////////////////////////////

svAnimation::svAnimation(){
	pName = NULL;
	pStartFrame = 0;
	pEndFrame = 0;
	pPlaybackSpeed = 1;
	SetName( "Animation" );
}

svAnimation::svAnimation( int startFrame, int endFrame ){
	pName = NULL;
	pPlaybackSpeed = 1;
	SetFrameRange( startFrame, endFrame );
	SetName( "Animation" );
}

svAnimation::~svAnimation(){
	if( pName ) delete [] pName;
}



// Management
///////////////

void svAnimation::SetFrameRange( int startFrame, int endFrame ){
	if( startFrame < 0 || endFrame < 0 || startFrame > endFrame ) THROW( dueInvalidParam );
	pStartFrame = startFrame;
	pEndFrame = endFrame;
}

void svAnimation::SetPlaybackSpeed( int playbackSpeed ){
	if( playbackSpeed < 1 ) THROW( dueInvalidParam );
	pPlaybackSpeed = playbackSpeed;
}

void svAnimation::SetName( const char *name ){
	if( ! name || ! name[ 0 ] ) THROW( dueInvalidParam );
	char *newStr = new char[ strlen( name ) + 1 ];
	if( ! newStr ) THROW( dueOutOfMemory );
	strcpy( newStr, name );
	if( pName ) delete [] pName;
	pName = newStr;
}
