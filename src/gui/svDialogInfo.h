/* 
 * Digimon RPG Sprite Viewer
 *
 * Copyright (C) 2004, Pl�ss Roland ( rptd@gmx.net )
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

// include only once
#ifndef _SVDIALOGINFO_H_
#define _SVDIALOGINFO_H_

// includes
#include "../drpgsprviewer.h"
#include "../foxtoolkit.h"

// predefinitions



/**
 * @author Pl�ss Roland
 * @version 1.0
 * @date 2006
 * @brief Info Dialog.
 * Shows some small informations about this application.
 */
class svDialogInfo : public FXDialogBox{
	FXDECLARE( svDialogInfo )
protected:
	svDialogInfo();
public:
	enum eFoxIDs{
		ID_CANVAS=FXDialogBox::ID_LAST,
		ID_LAST
	};
public:
	// constructor, destructor
	svDialogInfo( FXWindow *owner );
	~svDialogInfo();
};

// end of include only once
#endif
