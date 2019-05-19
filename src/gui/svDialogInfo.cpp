/* 
 * Drag[en]gine Map Editor
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
#include "svDialogInfo.h"
#include "../common/exceptions.h"



// events
///////////



// class svDialogInfo
///////////////////////
FXIMPLEMENT( svDialogInfo, FXDialogBox, NULL, 0 )

// constructor, destructor
svDialogInfo::svDialogInfo(){ }

svDialogInfo::svDialogInfo( FXWindow *owner ) :
FXDialogBox( owner, "About DRPG Sprite Viewer (Auto PNG Export)" ){
	char text[] = "Digimon RPG Sprite Viewer\n"
		"Written By Plüss Roland\n"
		"Release " VERSION "\n"
		"Contact: roland@rptd.dnsalias.net\n\n"
		"Auto PNG Export patch 2019 by EN.I\n"
		"https://github.com/elsemieni/drpgsprviewer-PNG";
		
	// build gui
	FXVerticalFrame *content = new FXVerticalFrame( this,
		LAYOUT_FILL_X | LAYOUT_FILL_Y | LAYOUT_TOP | LAYOUT_LEFT,
		0, 0, 0, 0, 0, 0, 0, 0 );
	
	new FXLabel( content, text, 0, JUSTIFY_CENTER_X | LAYOUT_FILL_X );
	
	FXHorizontalFrame *frameButtons = new FXHorizontalFrame( content,
		LAYOUT_SIDE_TOP | LAYOUT_FILL_X | LAYOUT_FILL_Y,
		0, 0, 0, 0, 10, 10, 10, 10 );
	new FXButton( frameButtons, "Okay... Got it", NULL, this, ID_CANCEL,
		BUTTON_NORMAL | LAYOUT_FILL_X );
}
svDialogInfo::~svDialogInfo(){ }
