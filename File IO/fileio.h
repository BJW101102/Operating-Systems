//////////////////////////////////////////////////////////////////////
// Intentionally flawed system call library that implements         //
// (unfortunately, not) "safe" file I/O, which "disallows" writing  //
// "\x7F""ELF" at the beginning of a file.                          //
// Tweaks by A. Ali-Gombe  8/2022                                                               //
// Written by Golden G. Richard III (@nolaforensix), 6/2022.        //
//                                                                  //
// Props to Brian Hay for the idea, based on a similar exercise he  //
// used in a training exercise.                                     //
//////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// filesystem error code
typedef enum  {
  NONE, 
  OPEN_FAILED,
  CLOSE_FAILED,
  READ_FAILED,
  WRITE_FAILED,
  ILLEGAL_ELF
} FSError;

// file handle type
typedef FILE* File;







// seek anchors
typedef enum {
  BEGINNING_OF_FILE,
  CURRENT_POSITION, 
  END_OF_FILE
} SeekAnchor;

// function prototypes for system calls

// open file with pathname 'name'. Files are always opened for
// read/write access.  Always sets 'fserror' global.
File open_file(char *name);

// close file with handle 'file'.  Always sets 'fserror' global.
void close_file(File file);

// read 'num_bytes' into 'data' from 'file' at 'offset' bytes from a
// particular 'start'-ing position.  Returns the number of bytes
// read. Always sets 'fserror' global.
unsigned long read_file_from(File file, void *data, unsigned long num_bytes,
			     SeekAnchor start, long offset);

// write 'num_bytes' from 'data' into 'file' at 'offset' bytes from a 
// particular 'start'-ing position. Returns the number of bytes
// written.  Always sets 'fserror' global.
unsigned long write_file_at(File file, void *data, unsigned long num_bytes, 
			    SeekAnchor start, long offset);

// describe current filesystem error code 
void fs_print_error(void);

// GLOBALS //

// filesystem error code set (set by each function)
extern FSError fserror;