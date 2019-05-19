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
#ifndef _DECDISCFILEREADER_H_
#define _DECDISCFILEREADER_H_

// includes
#include <stdio.h>
#include "decBaseFileReader.h"

// predefinitions



/**
 * @author Plüss Roland
 * @version 1.0
 * @date 2006
 * @brief Disc File Reader.
 * Reads data from files stored on disc.
 */
class decDiscFileReader : public decBaseFileReader{
private:
	char *p_Filename;
	FILE *p_File;
	int p_Length;
public:
	/** @name Constructors and Destructors */
	/*@{*/
	/**
	 * Creates a new file reader object for the file. The file is opened
	 * immediatly for reading only. The filename specified has to be
	 * an absolute path.
	 */
	decDiscFileReader( const char *filename );
	/** Closes the file and cleans up. */
	virtual ~decDiscFileReader();
	/*@}*/
	
	/** @name Management */
	/*@{*/
	const char *GetFilename();
	int GetLength();
	int GetPosition();
	void SetPosition(int Position);
	void MovePosition(int Offset);
	void SetPositionEnd(int Position);
	void Read(void *Buffer, int Size);
	/*@}*/
};

// end of include only once
#endif
