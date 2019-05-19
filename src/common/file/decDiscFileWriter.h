/* 
 * Drag[en]gine Library -- Game Engine
 *
 * Copyright (C) 2004, Plüss Roland ( roland@rptd.dnsalias.net )
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
#ifndef _DECDISCFILEWRITER_H_
#define _DECDISCFILEWRITER_H_

// includes
#include <stdio.h>
#include "decBaseFileWriter.h"

// predefinitions



/**
 * @author Plüss Roland
 * @version 1.0
 * @date 2006
 * @brief Disc File Writer.
 * Writes data to files on disc.
 */
class decDiscFileWriter : public decBaseFileWriter{
private:
	char *p_Filename;
	FILE *p_File;
public:
	/** @name Constructors and Destructors */
	/*@{*/
	/**
	 * Creates a new file reader object for the file. The file is opened
	 * immediatly for readin/writing. The filename specified has to be
	 * an absolute path.
	 * @param filename Filename of file
	 * @param append True to append to or false to overwrite file
	 */
	decDiscFileWriter( const char *filename, bool append );
	/** Closes the file and cleans up. */
	~decDiscFileWriter();
	/*@}*/
	
	/** @name Management */
	/*@{*/
	const char *GetFilename();
	void Write( void *buffer, int size );
	/*@}*/
};

// end of include only once
#endif
