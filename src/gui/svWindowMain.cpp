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
#include "svWindowMain.h"
#include "svDialogInfo.h"
#include "svViewSprite.h"
#include "svViewMap.h"
#include "../sprite/svSprite.h"
#include "../sprite/svSpriteImage.h"
#include "../sprite/svSpriteLoader.h"
#include "../animation/svAnimationSet.h"
#include "../animation/svAnimation.h"
#include "../animation/svAnimationLoader.h"
#include "../tile/svTileLoader.h"
#include "../common/deCmdLineArgs.h"
#include "../common/file/decDiscFileReader.h"
#include "../common/file/decDiscFileWriter.h"
#include "../common/file/decPath.h"
#include "../common/exceptions.h"



// events
///////////
FXDEFMAP( svWindowMain ) svWindowMainMap[]={
	FXMAPFUNC( SEL_COMMAND, svWindowMain::ID_FILEOPEN, svWindowMain::onFileOpen ),
	FXMAPFUNC( SEL_COMMAND, svWindowMain::ID_FILEQUIT, svWindowMain::onFileQuit ),
	FXMAPFUNC( SEL_COMMAND, svWindowMain::ID_INFOABOUT, svWindowMain::onInfoAbout ),
};



// definitions
////////////////
#define SV_SETTINGS			".drpgsprviewer"



// class svWindowMain
///////////////////////

FXIMPLEMENT( svWindowMain, FXMainWindow, svWindowMainMap, ARRAYNUMBER( svWindowMainMap ) )

svWindowMain::svWindowMain(){ }

void svWindowMain::create(){
	// create the windows
	FXMainWindow::create();
	// make the main window appear
	show( PLACEMENT_SCREEN );
	// tooltips
	/*
	FXToolTip *tooltip = new FXToolTip(getApp());
	tooltip->create();
	tooltip->show();
	*/
}



// constructor, destructor
////////////////////////////

svWindowMain::svWindowMain( FXApp* app, deCmdLineArgs *args ) :
FXMainWindow( app, "Digimon RPG Viewer (Auto PNG Export)", NULL, NULL, DECOR_ALL, 0, 0, 500, 500 ){
	if( ! args ) THROW( dueInvalidParam );
	// prepare
	pViewSprite = NULL;
	pViewMap = NULL;
	pMenuFile = NULL;
	pMenuInfos = NULL;
	pTabViews = NULL;
	pCmdArgs = args;
	pLastFileType = eftSprite;
	pFilename = NULL;
		
	// create menu
	FXMenuBar *menubar = new FXMenuBar( this, LAYOUT_SIDE_TOP | LAYOUT_FILL_X );
	
	pMenuFile = new FXMenuPane( this );
	new FXMenuTitle( menubar, "&File", NULL, pMenuFile );
		new FXMenuCommand( pMenuFile, "&Open...\tCtl-O\tOpen Sprite", NULL,
			this, svWindowMain::ID_FILEOPEN );
		new FXMenuCommand( pMenuFile, "&Quit\t\tQuit the application.", NULL,
			app, FXApp::ID_QUIT );
	
	pMenuInfos = new FXMenuPane( this );
	new FXMenuTitle( menubar, "&Infos", NULL, pMenuInfos );
		new FXMenuCommand( pMenuInfos, "About this App...\t\tShort Infos about this app", NULL,
			this, svWindowMain::ID_INFOABOUT );
	
	// add tab
	pTabViews = new FXTabBook( this, NULL, 0, LAYOUT_FILL_X | LAYOUT_FILL_Y
		| TABBOOK_NORMAL );
	
	pTabItemSprite = new FXTabItem( pTabViews, "Sprite", 0, TAB_TOP_NORMAL,
		0, 0, 0, 0, 10, 10 );
	pViewSprite = new svViewSprite( this, pTabViews );
	if( ! pViewSprite ) THROW( dueOutOfMemory );
	
	pTabItemSprite = new FXTabItem( pTabViews, "Map", 0, TAB_TOP_NORMAL,
		0, 0, 0, 0, 10, 10 );
	pViewMap = new svViewMap( this, pTabViews );
	if( ! pViewMap ) THROW( dueOutOfMemory );
	
	// update menu and toolbar
	UpdateWindowTitle();
}

svWindowMain::~svWindowMain(){
	// NEVER delete stuff derived from fox widgets!
	// save settings. this comes soon. for the time beeing do it by hand
	// cleanup
	if( pFilename ) delete [] pFilename;
}

void svWindowMain::Update(){
}



// management
///////////////

void svWindowMain::CleanUp(){
}

bool svWindowMain::QuitRequest(){
	// check if user wants to quit. returns true if a quit
	// is wished by the user
	
	// clean up
	CleanUp();
	return true;
}

void svWindowMain::UpdateWindowTitle(){
	char *buffer = new char[ 256 ];
	decPath path;
	if( pFilename ) path.SetFromNative( pFilename );
	try{
		if( ! buffer ) THROW( dueOutOfMemory );
		if( pFilename ){
			sprintf( buffer, "Digimon RPG Viewer (Auto PNG Export) - %s", path.GetLastComponent() );
		}else{
			strcpy( buffer, "Digimon RPG Viewer (Auto PNG Export)" );
		}
		setTitle( buffer );
		delete [] buffer;
	}catch( duException ){
		if( buffer ) delete [] buffer;
		throw;
	}
}



// callbacks
//////////////

long svWindowMain::onFileOpen( FXObject *sender, FXSelector selector, void *data ){
	FXFileDialog dialog( this, "Open File" );
	FXString filename, message;
	int fileLen;
	dialog.setPatternList( "DRPG Sprite (*.spr)\nDRPG Animation (*.ani)\nDRPG Tile (*.til)\nDRPG Map (*.map)\nAll Files(*)" );
	dialog.setCurrentPattern( pLastFileType );
	if( GetFilename() ){
		dialog.setFilename( GetFilename() );
	}else{
		dialog.setFilename( "sprite.spr" );
	}
	if( dialog.execute( PLACEMENT_OWNER ) == TRUE ){
		filename = dialog.getFilename();
		try{
			fileLen = strlen( filename.text() );
			if( dialog.getCurrentPattern() == 0 ){
				pViewSprite->LoadSprite( filename.text() );
				SetFilename( filename.text(), eftSprite );
			}else if( dialog.getCurrentPattern() == 1 ){
				pViewSprite->LoadAnimation( filename.text() );
				SetFilename( filename.text(), eftAnimation );
			}else if( dialog.getCurrentPattern() == 2 ){
				pViewSprite->LoadTile( filename.text() );
				SetFilename( filename.text(), eftTile );
			}else if( dialog.getCurrentPattern() == 3 ){
				pViewMap->LoadMap( filename.text() );
				SetFilename( filename.text(), eftMap );
			}else{
				fileLen = strlen( filename.text() );
				if( fileLen > 4 ){
					if( strcmp( filename.text() + fileLen - 4, ".spr" ) == 0 ){
						pViewSprite->LoadSprite( filename.text() );
						SetFilename( filename.text(), eftSprite );
					}else if( strcmp( filename.text() + fileLen - 4, ".ani" ) == 0 ){
						pViewSprite->LoadAnimation( filename.text() );
						SetFilename( filename.text(), eftAnimation );
					}else if( strcmp( filename.text() + fileLen - 4, ".til" ) == 0 ){
						pViewSprite->LoadTile( filename.text() );
						SetFilename( filename.text(), eftTile );
					}else if( strcmp( filename.text() + fileLen - 4, ".map" ) == 0 ){
						pViewMap->LoadMap( filename.text() );
						SetFilename( filename.text(), eftMap );
					}else{
						pViewSprite->LoadSprite( filename.text() );
						SetFilename( filename.text(), eftSprite );
					}
				}else{
					pViewSprite->LoadSprite( filename.text() );
					SetFilename( filename.text(), eftSprite );
				}
			}
			UpdateWindowTitle();
		}catch( duException e ){
			message.format( "%s (%s)", e.GetDescription(), e.GetInfo() );
			FXMessageBox::error( this, FX::MBOX_OK, "Open File Error", message.text() );
			return 0;
		}
		Update();
		return 1;
	}else{
		return 0;
	}
}

long svWindowMain::onFileQuit( FXObject *sender, FXSelector selector, void *data ){
	if( QuitRequest() ){
		//gtk_widget_destroy( GTK_WIDGET(wnd->GetWidget()) );
	}
	return 1;
}

long svWindowMain::onInfoAbout( FXObject *sender, FXSelector selector, void *data ){
	svDialogInfo dialog( this );
	dialog.execute( PLACEMENT_OWNER );
	return 1;
}



// File
/////////

void svWindowMain::SetFilename( const char *filename, int fileType ){
	if( ! filename ) THROW( dueInvalidParam );
	if( fileType < eftSprite || fileType > EFT_COUNT ) THROW( dueInvalidParam );
	char *newString = new char[ strlen( filename ) + 1 ];
	if( ! newString ) THROW( dueOutOfMemory );
	strcpy( newString, filename );
	if( pFilename ) delete [] pFilename;
	pFilename = newString;
	pLastFileType = fileType;
	if( fileType == eftSprite ){
		pTabItemSprite->setText( "Sprite" );
		pTabViews->setCurrent( 0 );
	}else if( fileType == eftAnimation ){
		pTabItemSprite->setText( "Animation" );
		pTabViews->setCurrent( 0 );
	}else if( fileType == eftTile ){
		pTabItemSprite->setText( "Tile" );
		pTabViews->setCurrent( 0 );
	}else if( fileType == eftMap ){
		pTabViews->setCurrent( 1 );
	}
}



// Private Functions
//////////////////////
