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
#ifndef _DECBASEFILEREADER_H_
#define _DECBASEFILEREADER_H_

// includes

// predefinitions
class decDataChunk;


/**
 * @author Plüss Roland
 * @version 1.0
 * @date 2006
 * @brief File Reader Interface.
 */
class decBaseFileReader{
public:
	/** @name Constructors and Destructors */
	/*@{*/
	virtual ~decBaseFileReader();
	/*@}*/
	
	/** @name Management */
	/*@{*/
	/** Retrieves the name of the file. */
	virtual const char *GetFilename() = 0;
	/** Retrieves the length of the file. */
	virtual int GetLength() = 0;
	/** Retrieves the current reading position in the file. */
	virtual int GetPosition() = 0;
	/** Sets the file position for the next read action. */
	virtual void SetPosition( int position ) = 0;
	/** Moves the file position by the given offset. */
	virtual void MovePosition( int offset ) = 0;
	/** Sets the file position to the given position measured from the end of the file. */
	virtual void SetPositionEnd( int position ) = 0;
	/** Reads 'size' bytes into 'buffer' and advances the file pointer. */
	virtual void Read( void *buffer, int size ) = 0;
	/*@}*/
	
	/** @name Helper Functions */
	/*@{*/
	/** Determines if the file pointer is at the end of the file. */
	bool IsEOF();
	/** Reads one byte ( 1 byte ) and advances the file pointer. */
	char ReadChar();
	/** Reads one unsigned byte ( 1 byte ) and advances the file pointer. */
	unsigned char ReadByte();
	/** Reads one short ( 2 bytes ) and advances the file pointer. */
	short ReadShort();
	/** Reads one unsigned short ( 2 bytes ) and advances the file pointer. */
	unsigned short ReadUShort();
	/** Reads one int ( 4 bytes ) and advances the file pointer. */
	int ReadInt();
	/** Reads one unsigned int ( 4 bytes ) and advances the file pointer. */
	unsigned int ReadUInt();
	/** Reads one float ( 4 bytes ) and advances the file pointer. */
	float ReadFloat();
	/**
	 * Reads a string prefixed by a 1-byte length field and advances the file pointer.
	 * The returned string pointer has to be freed by the caller itself.
	 */
	char *ReadString8();
	/**
	 * Reads a string prefixed by a 2-byte2 length field and advances the file pointer.
	 * The returned string pointer has to be freed by the caller itself.
	 */
	char *ReadString16();
	/** Skips a string prefixed by a 1-byte length field and advances the file pointer. */
	void SkipString8();
	/** Skips a string prefixed by a 2-byte2 length field and advances the file pointer. */
	void SkipString16();
	/*@}*/
};

// end of include only once
#endif
