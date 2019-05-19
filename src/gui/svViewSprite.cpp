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
#include "svViewSprite.h"
#include "svWindowMain.h"
#include "../sprite/svSprite.h"
#include "../sprite/svSpriteImage.h"
#include "../sprite/svSpriteLoader.h"
#include "../animation/svAnimationSet.h"
#include "../animation/svAnimation.h"
#include "../animation/svAnimationLoader.h"
#include "../tile/svTileLoader.h"
#include "../common/file/decDiscFileReader.h"
#include "../common/file/decDiscFileWriter.h"
#include "../common/file/decPath.h"
#include "../common/exceptions.h"

#include <FXPNGImage.h> 

// events
///////////
FXDEFMAP( svViewSprite ) svViewSpriteMap[]={
	FXMAPFUNC( SEL_CHANGED, svViewSprite::ID_SCROLLINDEX, svViewSprite::onScrollIndexChanged ),
	FXMAPFUNC( SEL_COMMAND, svViewSprite::ID_CBANIM, svViewSprite::onCBAnimChanged ),
};



// class svViewSprite
///////////////////////

FXIMPLEMENT( svViewSprite, FXVerticalFrame, svViewSpriteMap, ARRAYNUMBER( svViewSpriteMap ) )

svViewSprite::svViewSprite(){ }



// constructor, destructor
////////////////////////////

svViewSprite::svViewSprite( svWindowMain *wndMain, FXComposite *parent ) : 
FXVerticalFrame( parent, LAYOUT_FILL_X | LAYOUT_FILL_Y | LAYOUT_TOP
| LAYOUT_LEFT | FRAME_RAISED,
0, 0, 0, 0, 10, 10, 10, 10 ){
	if( ! wndMain ) THROW( dueInvalidParam );
	// prepare
	pWndMain = wndMain;
	pViewImage = NULL;
	pScrollIndex = NULL;
	pEditIndex = NULL;
	pEditWidth = NULL;
	pEditHeight = NULL;
	pEditAnim = NULL;
	pComboAnim = NULL;
	pEditStartFrame = NULL;
	pEditEndFrame = NULL;
	pSprite = NULL;
	pAnimSet = NULL;
	pImage = NULL;
	pImageIndex = 0;
	
	// create image view panel
	FXHorizontalFrame *viewPanel = new FXHorizontalFrame( this,
		LAYOUT_SIDE_TOP | LAYOUT_FILL_X | LAYOUT_FILL_Y, 0, 0, 0, 0, 0, 0, 0, 0 );
	
	pViewImage = new FXImageView( viewPanel, NULL, NULL, 0, LAYOUT_FILL_X | LAYOUT_FILL_Y );
	pViewImage->setBackColor( FXRGB( 0, 0, 0 ) );
	
	// create index panel
	FXHorizontalFrame *indexPanel = new FXHorizontalFrame( this,
		LAYOUT_SIDE_TOP | LAYOUT_FILL_X, 0, 0, 0, 0, 0, 0, 2, 0 );
		
	new FXLabel( indexPanel, "Width:" );
	pEditWidth = new FXTextField( indexPanel, 5, NULL, 0,
		TEXTFIELD_INTEGER | FRAME_SUNKEN | TEXTFIELD_READONLY );
	pEditWidth->setText( "0" );
		
	new FXLabel( indexPanel, "Height:" );
	pEditHeight = new FXTextField( indexPanel, 5, NULL, 0,
		TEXTFIELD_INTEGER | FRAME_SUNKEN | TEXTFIELD_READONLY );
	pEditHeight->setText( "0" );
		
	new FXLabel( indexPanel, "Frame:" );
	pEditIndex = new FXTextField( indexPanel, 5, NULL, 0,
		TEXTFIELD_INTEGER | FRAME_SUNKEN | TEXTFIELD_READONLY );
	pEditIndex->setText( "0" );
	pScrollIndex = new FXScrollBar( indexPanel, this, ID_SCROLLINDEX,
		LAYOUT_FILL_X | SCROLLBAR_HORIZONTAL );
	
	// create animation panel
	FXHorizontalFrame *animPanel = new FXHorizontalFrame( this,
		LAYOUT_SIDE_TOP | LAYOUT_FILL_X, 0, 0, 0, 0, 0, 0, 2, 0 );
	
	new FXLabel( animPanel, "Animation:" );
	pComboAnim = new FXComboBox( animPanel, 20, this, ID_CBANIM,
		COMBOBOX_STATIC | FRAME_SUNKEN );
	pComboAnim->setNumVisible( 5 );
		
	new FXLabel( animPanel, "Start:" );
	pEditStartFrame = new FXTextField( animPanel, 5, NULL, 0,
		TEXTFIELD_INTEGER | FRAME_SUNKEN | TEXTFIELD_READONLY );
	pEditStartFrame->setText( "0" );
		
	new FXLabel( animPanel, "End:" );
	pEditEndFrame = new FXTextField( animPanel, 5, NULL, 0,
		TEXTFIELD_INTEGER | FRAME_SUNKEN | TEXTFIELD_READONLY );
	pEditEndFrame->setText( "0" );
	
	// create an new sprite and animation
	NewAnimation();
}

svViewSprite::~svViewSprite(){
	if( pAnimSet ) delete pAnimSet;
	if( pImage ) delete pImage;
	if( pSprite ) delete pSprite;
}

void svViewSprite::Update(){
}



// management
///////////////

void svViewSprite::CleanUp(){
}



// callbacks
//////////////

long svViewSprite::onScrollIndexChanged( FXObject *sender, FXSelector selector, void *data ){
	SetImageIndex( pScrollIndex->getPosition() );
	return 1;
}

long svViewSprite::onCBAnimChanged( FXObject *sender, FXSelector selector, void *data ){
	SetAnimationIndex( pComboAnim->getCurrentItem() );
	return 1;
}



// viewing
////////////



// Sprite
///////////

void svViewSprite::NewAnimation(){
	svAnimationSet *animSet = NULL;
	svSprite *sprite = NULL;
	// create new animation set and sprite
	try{
		animSet = pNewAnimationSet();
		sprite = pNewSprite();
	}catch( duException ){
		if( sprite ) delete sprite;
		if( animSet ) delete animSet;
		throw;
	}
	// replace
	if( pAnimSet ) delete pAnimSet;
	pAnimSet = animSet;
	if( pSprite ) delete pSprite;
	pSprite = sprite;
	// select first animation
	UpdateRanges();
	SetAnimationIndex( 0 );
}

void svViewSprite::LoadSprite( const char *filename ){
	svAnimationSet *animSet = NULL;
	svSprite *sprite = NULL;
	decDiscFileReader *file = NULL;
	svSpriteLoader spriteLoader;
	// load sprite from given file
	try{
		// open file for reading
		file = new decDiscFileReader( filename );
		if( ! file ) THROW( dueFileNotFound );
		// load sprite using a sprite loader
		sprite = spriteLoader.LoadSprite( file );
		// close file
		delete file;
		file = NULL;
		// make sure the sprite is valid
		if( sprite->GetImageCount() < 1 ) THROW( dueInvalidParam );
		// create a default animation
		animSet = pNewAnimationSet();
		// replace
		if( pAnimSet ) delete pAnimSet;
		pAnimSet = animSet;
		if( pSprite ) delete pSprite;
		pSprite = sprite;
	}catch( duException ){
		if( file ) delete file;
		if( animSet ) delete animSet;
		if( sprite ) delete sprite;
		throw;
	}
	// select first animation
	UpdateRanges();
	SetAnimationIndex( 0 );
}

void svViewSprite::LoadAnimation( const char *filename ){
	svAnimationSet *animSet = NULL;
	svSprite *sprite = NULL;
	decDiscFileReader *file = NULL;
	svAnimationLoader animLoader;
	svSpriteLoader spriteLoader;
	decPath path;
	// load animation and the assigned sprite from given file
	try{
		// open file for reading
		file = new decDiscFileReader( filename );
		if( ! file ) THROW( dueFileNotFound );
		// load animation set using an animation loader
		animSet = animLoader.LoadAnimation( file );
		// close file
		delete file;
		file = NULL;
		// make sure the animation is valid
		if( animSet->GetAnimationCount() < 1 ) THROW( dueInvalidParam );
		
		// init path to sprite file
		path.SetFromNative( filename );
		path.RemoveLastComponent();
		path.AddNativePath( animSet->GetSpriteFile() );
		// open file for reading
		file = new decDiscFileReader( path.GetPathNative() );
		if( ! file ) THROW( dueFileNotFound );
		// load sprite using a sprite loader
		sprite = spriteLoader.LoadSprite( file );
		// close file
		delete file;
		file = NULL;
		// make sure the sprite is valid
		if( sprite->GetImageCount() < 1 ) THROW( dueInvalidParam );
		
		// replace
		if( pAnimSet ) delete pAnimSet;
		pAnimSet = animSet;
		if( pSprite ) delete pSprite;
		pSprite = sprite;
	}catch( duException ){
		if( file ) delete file;
		if( animSet ) delete animSet;
		if( sprite ) delete sprite;
		throw;
	}
	// select first animation
	UpdateRanges();
	SetAnimationIndex( 0 );
}

void svViewSprite::LoadTile( const char *filename ){
	svAnimationSet *animSet = NULL;
	svSprite *sprite = NULL;
	decDiscFileReader *file = NULL;
	svTileLoader tileLoader;
	// load tile from given file
	try{
		// open file for reading
		file = new decDiscFileReader( filename );
		if( ! file ) THROW( dueFileNotFound );
		// load tile using a tile loader
		sprite = tileLoader.LoadTile( file );
		// close file
		delete file;
		file = NULL;
		// make sure the tile is valid
		if( sprite->GetImageCount() < 1 ) THROW( dueInvalidParam );
		// create a default animation
		animSet = pNewAnimationSet();
		// replace
		if( pAnimSet ) delete pAnimSet;
		pAnimSet = animSet;
		if( pSprite ) delete pSprite;
		pSprite = sprite;
	}catch( duException ){
		if( file ) delete file;
		if( animSet ) delete animSet;
		if( sprite ) delete sprite;
		throw;
	}
	// select first animation
	UpdateRanges();
	SetAnimationIndex( 0 );
}

void svViewSprite::SetImageIndex( int index ){
	if( ! pSprite ) THROW( dueInvalidParam );
	svSpriteImage *spriteImage = pSprite->GetImageAt( index );
	int height = spriteImage->GetHeight();
	int width = spriteImage->GetWidth();
	FXPNGImage *image = NULL;
	svColor *pixelLine;
	char numBuf[ 10 ];
	int x, y;
	// unset and delete the old image
	pViewImage->setImage( NULL );
	if( pImage ){
		delete pImage;
		pImage = NULL;
	}
	// create a new image from the given sprite image
	try{
		// create image with the same size as the sprite image
		image = new FXPNGImage( getApp(), NULL, IMAGE_KEEP | IMAGE_OWNED
			| IMAGE_SHMI | IMAGE_SHMP, width, height );
		if( ! image ) THROW( dueOutOfMemory );
		// copy the pixels over from the sprite image to this image
		for( y=0; y<height; y++ ){
			pixelLine = spriteImage->GetLineAt( y );
			for( x=0; x<width; x++ ){
				image->setPixel( x, y, FXRGBA( pixelLine[ x ].red,
					pixelLine[ x ].green, pixelLine[ x ].blue,
					pixelLine[ x ].alpha ) );
			}
		}
		// update the image. if this is ommited an unlogical crash
		// avalanche is tripped off :/
		image->create();
	}catch( duException ){
		if( image ) delete image;
		throw;
	}
	// set the new image
	pImageIndex = index;
	pImage = image;
	pViewImage->setImage( pImage );
	
	//save image to PNG
	char out_index[255];
	sprintf(out_index, "export_%i.png", index);
	FXString filename = out_index;
	FXFileStream *saveStream = new FXFileStream();
	saveStream->open(filename, FX::FXStreamSave);
	image->savePixels(*saveStream);
	saveStream->close();
	
	// update panel
	sprintf( ( char* )&numBuf, "%i", spriteImage->GetWidth() );
	pEditWidth->setText( numBuf );
	sprintf( ( char* )&numBuf, "%i", spriteImage->GetHeight() );
	pEditHeight->setText( numBuf );
	sprintf( ( char* )&numBuf, "%i", index );
	pEditIndex->setText( numBuf );
	pScrollIndex->setPosition( index );
}

void svViewSprite::SetAnimationIndex( int index ){
	if( ! pAnimSet ) THROW( dueInvalidParam );
	svAnimation *anim = pAnimSet->GetAnimationAt( index );
	char numBuf[ 10 ];
	// set the animation
	pAnimIndex = index;
	// update panel
	pComboAnim->setCurrentItem( index );
	sprintf( ( char* )&numBuf, "%i", anim->GetStartFrame() );
	pEditStartFrame->setText( numBuf );
	sprintf( ( char* )&numBuf, "%i", anim->GetEndFrame() );
	pEditEndFrame->setText( numBuf );
	// set start frame as current image
	if( anim->GetStartFrame() >= pSprite->GetImageCount() ){
		SetImageIndex( pSprite->GetImageCount() - 1 );
	}else{
		SetImageIndex( anim->GetStartFrame() );
	}
}

void svViewSprite::UpdateRanges(){
	if( ! pSprite || ! pAnimSet ) THROW( dueInvalidParam );
	int i;
	pScrollIndex->setRange( pSprite->GetImageCount() );
	pScrollIndex->setLine( 1 );
	pScrollIndex->setPage( 1 );
	pComboAnim->clearItems();
	for( i=0; i<pAnimSet->GetAnimationCount(); i++ ){
		pComboAnim->appendItem( pAnimSet->GetAnimationAt( i )->GetName(), NULL );
	}
}



// Private Functions
//////////////////////

svSprite *svViewSprite::pNewSprite(){
	svSprite *sprite = NULL;
	svSpriteImage *spriteImage = NULL;
	svColor *pixelLine;
	int x, y;
	// create new sprite with a default image
	try{
		// create sprite
		sprite = new svSprite;
		if( ! sprite ) THROW( dueOutOfMemory );
		// create a default image
		spriteImage = new svSpriteImage( 256, 256 );
		if( ! spriteImage ) THROW( dueOutOfMemory );
		for( y=0; y<256; y++ ){
			pixelLine = spriteImage->GetLineAt( y );
			for( x=0; x<256; x++ ){
				pixelLine[ x ].red = ( unsigned char )x;
				pixelLine[ x ].green = ( unsigned char )y;
				pixelLine[ x ].blue = 0;
				pixelLine[ x ].alpha = 255;
			}
		}
		sprite->AddImage( spriteImage );
	}catch( duException ){
		if( spriteImage ) delete spriteImage;
		if( sprite ) delete sprite;
		throw;
	}
	// return created sprite
	return sprite;
}

svAnimationSet *svViewSprite::pNewAnimationSet(){
	svAnimationSet *animSet = NULL;
	svAnimation *anim = NULL;
	// create new animation set with a animation
	try{
		// create animation set
		animSet = new svAnimationSet;
		if( ! animSet ) THROW( dueOutOfMemory );
		// create a default animation
		anim = new svAnimation( 0, 0 );
		if( ! anim ) THROW( dueOutOfMemory );
		animSet->AddAnimation( anim );
	}catch( duException ){
		if( anim ) delete anim;
		if( animSet ) delete animSet;
		throw;
	}
	// return created animation set
	return animSet;
}
