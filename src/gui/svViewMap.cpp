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
#include "svViewMap.h"
#include "svWindowMain.h"
#include "svViewRenderMap.h"
#include "../sprite/svSprite.h"
#include "../sprite/svSpriteImage.h"
#include "../map/svMap.h"
#include "../map/svMapField.h"
#include "../map/svMapLoader.h"
#include "../common/file/decDiscFileReader.h"
#include "../common/file/decDiscFileWriter.h"
#include "../common/file/decPath.h"
#include "../common/exceptions.h"



// events
///////////
FXDEFMAP( svViewMap ) svViewMapMap[]={
	FXMAPFUNC( SEL_CHANGED, svViewMap::ID_SCROLLX, svViewMap::onScrollXChanged ),
	FXMAPFUNC( SEL_CHANGED, svViewMap::ID_SCROLLY, svViewMap::onScrollYChanged ),
};



// class svViewMap
///////////////////////

FXIMPLEMENT( svViewMap, FXVerticalFrame, svViewMapMap, ARRAYNUMBER( svViewMapMap ) )

svViewMap::svViewMap(){ }



// constructor, destructor
////////////////////////////

svViewMap::svViewMap( svWindowMain *wndMain, FXComposite *parent ) : 
FXVerticalFrame( parent, LAYOUT_FILL_X | LAYOUT_FILL_Y | LAYOUT_TOP
| LAYOUT_LEFT | FRAME_RAISED,
0, 0, 0, 0, 10, 10, 10, 10 ){
	if( ! wndMain ) THROW( dueInvalidParam );
	// prepare
	pWndMain = wndMain;
	pScrollX = NULL;
	pScrollY = NULL;
	pEditFieldCount = NULL;
	pEditFieldSize = NULL;
	pEditTileCount = NULL;
	pEditObjectCount = NULL;
	pEditField = NULL;
	pEditFlags = NULL;
	pEditTile = NULL;
	pEditObject = NULL;
	pEditTileFile = NULL;
	pEditObjectFile = NULL;
	pMap = NULL;
	pViewRenderMap = NULL;
	
	// create image view panel
	FXHorizontalFrame *viewPanel = new FXHorizontalFrame( this,
		LAYOUT_SIDE_TOP | LAYOUT_FILL_X | LAYOUT_FILL_Y, 0, 0, 0, 0, 0, 0, 0, 0 );
	
	pViewRenderMap = new svViewRenderMap( this, viewPanel );

	pScrollY = new FXScrollBar( viewPanel, this, ID_SCROLLY, LAYOUT_FILL_Y | SCROLLBAR_VERTICAL );
	
	pScrollX = new FXScrollBar( this, this, ID_SCROLLX, LAYOUT_FILL_X | SCROLLBAR_HORIZONTAL );
	
	// create map panel
	FXHorizontalFrame *mapPanel = new FXHorizontalFrame( this,
		LAYOUT_SIDE_TOP | LAYOUT_FILL_X, 0, 0, 0, 0, 0, 0, 2, 0 );
		
	new FXLabel( mapPanel, "Field Count:" );
	pEditFieldCount = new FXTextField( mapPanel, 8, NULL, 0,
		FRAME_SUNKEN | TEXTFIELD_READONLY );
	pEditFieldCount->setText( "1x1" );
		
	new FXLabel( mapPanel, "Field Size:" );
	pEditFieldSize = new FXTextField( mapPanel, 8, NULL, 0,
		FRAME_SUNKEN | TEXTFIELD_READONLY );
	pEditFieldSize->setText( "1x1" );
		
	new FXLabel( mapPanel, "Tiles:" );
	pEditTileCount = new FXTextField( mapPanel, 5, NULL, 0,
		FRAME_SUNKEN | TEXTFIELD_READONLY );
	pEditTileCount->setText( "0" );
		
	new FXLabel( mapPanel, "Objects:" );
	pEditObjectCount = new FXTextField( mapPanel, 5, NULL, 0,
		FRAME_SUNKEN | TEXTFIELD_READONLY );
	pEditObjectCount->setText( "0" );
	
	// create field panel
	FXHorizontalFrame *fieldPanel = new FXHorizontalFrame( this,
		LAYOUT_SIDE_TOP | LAYOUT_FILL_X, 0, 0, 0, 0, 0, 0, 2, 0 );
		
	new FXLabel( fieldPanel, "Field:" );
	pEditField = new FXTextField( fieldPanel, 7, NULL, 0,
		FRAME_SUNKEN | TEXTFIELD_READONLY );
	pEditField->setText( "0;0" );
		
	new FXLabel( fieldPanel, "Flags:" );
	pEditFlags = new FXTextField( fieldPanel, 7, NULL, 0,
		FRAME_SUNKEN | TEXTFIELD_READONLY );
	pEditFlags->setText( "0" );
		
	new FXLabel( fieldPanel, "Tile:" );
	pEditTile = new FXTextField( fieldPanel, 8, NULL, 0,
		FRAME_SUNKEN | TEXTFIELD_READONLY );
	pEditTile->setText( "-1;-1" );
		
	new FXLabel( fieldPanel, "Object:" );
	pEditObject = new FXTextField( fieldPanel, 5, NULL, 0,
		FRAME_SUNKEN | TEXTFIELD_READONLY );
	pEditObject->setText( "-1" );
	
	// create field panel part 2
	fieldPanel = new FXHorizontalFrame( this,
		LAYOUT_SIDE_TOP | LAYOUT_FILL_X, 0, 0, 0, 0, 0, 0, 2, 0 );
		
	new FXLabel( fieldPanel, "Tile File:" );
	pEditTileFile = new FXTextField( fieldPanel, 15, NULL, 0,
		FRAME_SUNKEN | TEXTFIELD_READONLY );
	pEditTileFile->setText( "" );
	
	new FXLabel( fieldPanel, "Object File:" );
	pEditObjectFile = new FXTextField( fieldPanel, 15, NULL, 0,
		FRAME_SUNKEN | TEXTFIELD_READONLY );
	pEditObjectFile->setText( "" );
	
	// create an new map
	NewMap();
}

svViewMap::~svViewMap(){
	if( pMap ) delete pMap;
}

void svViewMap::Update(){
}



// management
///////////////

void svViewMap::CleanUp(){
}



// callbacks
//////////////

long svViewMap::onScrollXChanged( FXObject *sender, FXSelector selector, void *data ){
	pViewRenderMap->SetPositionX( pScrollX->getPosition() );
	pViewRenderMap->Update();
	return 1;
}

long svViewMap::onScrollYChanged( FXObject *sender, FXSelector selector, void *data ){
	pViewRenderMap->SetPositionY( pScrollY->getPosition() );
	pViewRenderMap->Update();
	return 1;
}



// Map
////////

void svViewMap::NewMap(){
	svMap *map = NULL;
	// create new map with a couple of fields
	map = pNewMap();
	// replace
	if( pMap ) delete pMap;
	pMap = map;
	// select first tile
	pViewRenderMap->SetMap( pMap );
	UpdateRanges();
	pViewRenderMap->SetField( 0, 0 );
	pViewRenderMap->SetPositionX( 0 );
	pViewRenderMap->SetPositionY( 0 );
	pScrollX->setPosition( 0 );
	pScrollY->setPosition( 0 );
	UpdateMapInfos();
	UpdateFieldInfo( 0, 0 );
	pViewRenderMap->Update();
}

void svViewMap::LoadMap( const char *filename ){
	svMap *map = NULL;
	decDiscFileReader *file = NULL;
	svMapLoader mapLoader;
	try{
		// open file for reading
		file = new decDiscFileReader( filename );
		if( ! file ) THROW( dueFileNotFound );
		// load map using a map loader
		map = mapLoader.LoadMap( file );
		// close file
		delete file;
		file = NULL;
		// replace
		if( pMap ) delete pMap;
		pMap = map;
	}catch( duException ){
		if( file ) delete file;
		if( map ) delete map;
		throw;
	}
	// select first animation
	pViewRenderMap->SetMap( pMap );
	UpdateRanges();
	pViewRenderMap->SetField( 0, 0 );
	pViewRenderMap->SetPositionX( 0 );
	pViewRenderMap->SetPositionY( 0 );
	pScrollX->setPosition( 0 );
	pScrollY->setPosition( 0 );
	UpdateMapInfos();
	UpdateFieldInfo( 0, 0 );
	pViewRenderMap->Update();
}

void svViewMap::UpdateRanges(){
	if( ! pMap ) THROW( dueInvalidParam );
	int i;
//	printf( "[DEBUG] %i %i %i %i\n", pMap->GetMapWidth(),
//		pMap->GetMapHeight(), pViewMap->getWidth(), pViewMap->getHeight() );
	pScrollX->setRange( pMap->GetMapWidth() );
	pScrollX->setLine( 1 );
	pScrollX->setPage( pViewRenderMap->getWidth() );
//	pScrollX->setPosition( pPosX );
	pScrollY->setRange( pMap->GetMapHeight() );
	pScrollY->setLine( 1 );
	pScrollY->setPage( pViewRenderMap->getHeight() );
//	pScrollY->setPosition( pPosY );
}

void svViewMap::UpdateFieldInfo( int fieldX, int fieldY ){
	if( ! pMap ) return;
	char numBuf[ 20 ];
	int fileIndex;
	svSprite *tile;
	svSprite *object;
	
	svMapField *field = pMap->GetFieldAt( fieldX, fieldY );
	sprintf( ( char* )&numBuf, "%i,%i", fieldX, fieldY );
	pEditField->setText( numBuf );
	sprintf( ( char* )&numBuf, "0x%.4x", field->GetFlags() );
	pEditFlags->setText( numBuf );
	sprintf( ( char* )&numBuf, "%i;%i", field->GetTileFileIndex(), field->GetTileIndex() );
	pEditTile->setText( numBuf );
	sprintf( ( char* )&numBuf, "%i", field->GetObjectIndex() );
	pEditObject->setText( numBuf );
	
	fileIndex = field->GetTileFileIndex();
	if( fileIndex >= 0 && fileIndex < pMap->GetTileCount() ){
		tile = pMap->GetTileAt( fileIndex );
		pEditTileFile->setText( tile->GetFilename() );
	}else{
		pEditTileFile->setText( "" );
	}
	
	fileIndex = field->GetObjectIndex();
	if( fileIndex >= 0 && fileIndex < pMap->GetObjectCount() ){
		object = pMap->GetObjectAt( fileIndex );
		pEditObjectFile->setText( object->GetFilename() );
	}else{
		pEditObjectFile->setText( "" );
	}
}

void svViewMap::UpdateMapInfos(){
	if( ! pMap ) return;
	char numBuf[ 40 ];
	sprintf( ( char* )&numBuf, "%ix%i", pMap->GetFieldXCount(), pMap->GetFieldYCount() );
	pEditFieldCount->setText( numBuf );
	sprintf( ( char* )&numBuf, "%ix%i", pMap->GetFieldWidth(), pMap->GetFieldHeight() );
	pEditFieldSize->setText( numBuf );
	sprintf( ( char* )&numBuf, "%i", pMap->GetTileCount() );
	pEditTileCount->setText( numBuf );
	sprintf( ( char* )&numBuf, "%i", 0 /*pMap->GetObjectCount()*/ );
	pEditObjectCount->setText( numBuf );
}



// Private Functions
//////////////////////

svSprite *svViewMap::pNewTile(){
	svSprite *tile = NULL;
	svSpriteImage *tileImage = NULL;
	svColor *pixelLine;
	int x, y, i, value;
	// create new tile with default tile images
	try{
		// create tile
		tile = new svSprite;
		if( ! tile ) THROW( dueOutOfMemory );
		// create a series of default images
		for( i=0; i<16; i++ ){
			value = i << 4;
			tileImage = new svSpriteImage( 64, 32 );
			if( ! tileImage ) THROW( dueOutOfMemory );
			for( y=0; y<32; y++ ){
				pixelLine = tileImage->GetLineAt( y );
				for( x=0; x<64; x++ ){
					pixelLine[ x ].red = ( unsigned char )value;
					pixelLine[ x ].green = ( unsigned char )( 255 - value );
					pixelLine[ x ].blue = 0;
					pixelLine[ x ].alpha = 255;
				}
			}
			tile->AddImage( tileImage );
			tileImage = NULL;
		}
	}catch( duException ){
		if( tileImage ) delete tileImage;
		if( tile ) delete tile;
		throw;
	}
	// return created tile
	return tile;
}

svMap *svViewMap::pNewMap(){
	svMap *map = NULL;
	svMapField *field;
	svSprite *tile = NULL;
	int x, y, rotator;
	// create new map
	try{
		// create map
		map = new svMap( 15, 30, 64, 32 );
		if( ! map ) THROW( dueOutOfMemory );
		// add a tile
		tile = pNewTile();
		map->AddTile( tile );
		tile = NULL;
		// fill fields
		rotator = 0;
		for( y=0; y<30; y++ ){
			for( x=0; x<15; x++ ){
				field = map->GetFieldAt( x, y );
				field->SetTileIndex( 0, rotator );
				rotator = ( rotator + 1 ) % 16;
			}
		}
	}catch( duException ){
		if( tile ) delete tile;
		if( map ) delete map;
		throw;
	}
	// return created map
	return map;
}
