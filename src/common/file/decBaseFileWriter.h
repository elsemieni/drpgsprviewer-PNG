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
#ifndef _DECBASEFILEWRITER_H_
#define _DECBASEFILEWRITER_H_

// includes

// predefinitions



/**
 * @author Plüss Roland
 * @version 1.0
 * @date 2006
 * @brief File Writer Interface.
 */
class decBaseFileWriter{
public:
	/** @name Constructors and Destructors */
	/*@{*/
	virtual ~decBaseFileWriter();
	/*@}*/
	
	/** @name Management */
	/*@{*/
	virtual const char *GetFilename() = 0;
	/*@}*/
	
	/** @name Management */
	/*@{*/
	/** Writes 'size' bytes of 'buffer' to file and advances write pointer. */
	virtual void Write( void *buffer, int size ) = 0;
	/*@}*/
	
	/** @name Helper Functions */
	/*@{*/
	/** Writes one byte ( 1 byte ) to file and advances write pointer. */
	void WriteChar(char Value);
	/** Writes one unsigned byte ( 1 byte ) to file and advances write pointer. */
	void WriteByte(unsigned char Value);
	/** Writes one short ( 2 bytes ) to file and advances write pointer. */
	void WriteShort(short Value);
	/** Writes one unsigned short ( 2 bytes ) to file and advances write pointer. */
	void WriteUShort(unsigned short Value);
	/** Writes one int ( 4 bytes ) to file and advances write pointer. */
	void WriteInt(int Value);
	/** Writes one unsigned int ( 4 bytes ) to file and advances write pointer. */
	void WriteUInt(unsigned int Value);
	/** Writes one float ( 4 bytes ) to file and advances write pointer. */
	void WriteFloat(float Value);
	/** Writes string-length bytes of string to file without length field and advances write pointer. */
	void WriteString(const char *String);
	/** Writes string-length bytes of string to file with a 1-byte length field in front and advances write pointer. */
	void WriteString8(const char *String);
	/** Writes string-length bytes of string to file with a 2-byte length field in front and advances write pointer. */
	void WriteString16(const char *String);
	/*@}*/
};

// end of include only once
#endif
