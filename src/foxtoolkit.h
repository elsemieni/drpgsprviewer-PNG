/* 
 * Drag[en]gine Normal/Displacement Map Generator
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

// include only once
#ifndef _FOXTOOLKIT_H_
#define _FOXTOOLKIT_H_

// includes
#if defined( HAS_FOX_CONFIG )
#	include <fx.h>
#	include <fx3d.h>

#elif defined( HAVE_FOX_1_2_FX_H )
#	include <fox-1.2/fx.h>
#	include <fox-1.2/fx3d.h>
#elif defined(HAVE_FOX_1_3_FX_H)
#	include <fox-1.3/fx.h>
#	include <fox-1.3/fx3d.h>

#else
#	error "No FOX toolkit specified!"
#endif

// definitions

// end of include only once
#endif
