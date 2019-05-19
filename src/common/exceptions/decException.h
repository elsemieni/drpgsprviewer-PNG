/* 
 * Drag[en]gine Library -- Game Engine
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
#ifndef _DUEXCEPTION_H_
#define _DUEXCEPTION_H_

// class duException
class duException{
private:
	const char *p_Name; // name of exception
	const char *p_Desc; // description of exception
	const char *p_Info; // additional info about the exception
	const char *p_File; // name of source file where the exception occured
	int p_Line; // number of the line where the exception occured
public:
	// constructors
	duException(const char *Name, const char *Description, const char *Info, const char *File, int Line);
	// management
	inline const char *GetName() const{ return p_Name; }
	inline const char *GetDescription() const{ return p_Desc; }
	inline const char *GetInfo() const{ return p_Info; }
	inline const char *GetFile() const{ return p_File; }
	inline int GetLine() const{ return p_Line; }
	bool IsNamed(const char *Name) const;
	void PrintError();
};

// common exceptions
class dueGeneric : public duException{
public: inline dueGeneric(const char *Info, const char *File, int Line) :
	duException("Generic","An Exception has occured",Info,File,Line){}
};
class dueInvalidParam : public duException{
public: inline dueInvalidParam(const char *Info, const char *File, int Line) :
	duException("InvalidParam","Invalid Parameter specified",Info,File,Line){}
};
class dueOutOfMemory : public duException{
public: inline dueOutOfMemory(const char *Info, const char *File, int Line) :
	duException("OutOfMemory","There is not enough Memory left",Info,File,Line){}
};
class dueOutOfBoundary : public duException{
public: inline dueOutOfBoundary(const char *Info, const char *File, int Line) :
	duException("OutOfBoundary","Index is outside allowed boundaries",Info,File,Line){}
};
class dueStackEmpty : public duException{
public: inline dueStackEmpty(const char *Info, const char *File, int Line) :
	duException("StackEmpty","Stack is empty",Info,File,Line){}
};
class dueStackOverflow : public duException{
public: inline dueStackOverflow(const char *Info, const char *File, int Line) :
	duException("StackOverflow","Stack Overflow",Info,File,Line){}
};
class dueDivisionByZero : public duException{
public: inline dueDivisionByZero(const char *Info, const char *File, int Line) :
	duException("DivisionByZero","Division By Zero",Info,File,Line){}
};
class dueNullPointer : public duException{
public: inline dueNullPointer(const char *Info, const char *File, int Line) :
	duException("NullPointer","Null Pointer",Info,File,Line){}
};
class dueInvalidAction : public duException{
public: inline dueInvalidAction(const char *Info, const char *File, int Line) :
	duException("InvalidAction","Invalid Action (internal error)",Info,File,Line){}
};

// file exceptions
class dueFileNotFound : public duException{
public: inline dueFileNotFound(const char *Info, const char *File, int Line) :
	duException("FileNotFound","File does not exist",Info,File,Line){}
};
class dueFileExists : public duException{
public: inline dueFileExists(const char *Info, const char *File, int Line) :
	duException("FileExists","File does exist already",Info,File,Line){}
};
class dueOpenFile : public duException{
public: inline dueOpenFile(const char *Info, const char *File, int Line) :
	duException("OpenFileFailed","Open File failed",Info,File,Line){}
};
class dueReadFile : public duException{
public: inline dueReadFile(const char *Info, const char *File, int Line) :
	duException("ReadFileFailed","Can not read from file",Info,File,Line){}
};
class dueWriteFile : public duException{
public: inline dueWriteFile(const char *Info, const char *File, int Line) :
	duException("WriteFileFailed","Can not write to file",Info,File,Line){}
};
class dueInvalidFileFormat : public duException{
public: inline dueInvalidFileFormat(const char *Info, const char *File, int Line) :
	duException("InvalidFileFormat","Invalid File Format",Info,File,Line){}
};

// testing exceptions
class dueTestFailed : public duException{
public: inline dueTestFailed(const char *Info, const char *File, int Line) :
	duException("TestCaseFailed","Test Case failed",Info,File,Line){}
};
class dueAssertion : public duException{
public: inline dueAssertion(const char *Info, const char *File, int Line) :
	duException("AssertionException","Assertion exception has occured",Info,File,Line){}
};

// macros
#define THROW(cls)				throw cls("", __FILE__, __LINE__)
#define THROW_INFO(cls,info)	throw cls(info, __FILE__, __LINE__)

// end of include only once
#endif

