#ifndef LINK84FILE
#define LINK84FILE

#include <stdint.h>

/* This defines file operations for the linker.
 * Need: First 11 bytes for signature, write comment, little endian data writing for 16 bit integer,
 * length finder, subheader constructor, checksum finder.
 * For the subheader constructor: need: token counter.
 */

typedef struct {
    // Writes a 16-bit number, little-endian, to the file.
    void ( *writeWord )( FILE *, uint16_t );

    // Writes the first eleven bytes of an 8xp file.
    void ( *firstEleven )( FILE * );

    // Writes the comment given to the file.
    void ( *writeComment )( FILE *, char * );

    // The next 3 functions should take the binary file, not the 8xp file.

    // Gets the length of the program + the 17 bytes in the subheader.
    uint32_t ( *getDataLength )( FILE * );

    // Gets token count (character count) of the specified file. Use this to find the length of a program without the length byte.
    uint32_t ( *getTokenCount )( FILE * );

    // Gets the length of the program + 2.
    uint32_t ( *getVarLength )( FILE * );

    // Writes the subheader (anything after the variable type) to the first file.
    void ( *writeSubheader )( FILE *, FILE *, char * );

    // Gets the checksum of the variable data. Supply the 8xp file.
    uint16_t ( *getChecksum )( FILE * );

    // Writies the checksum. Aliases to writeWord.
    void ( *writeChecksum )( FILE *, uint16_t );

} L84FileFnStruct;

extern L84FileFnStruct L84File;

void initFile( void );


void L84File_writeWord( FILE *, uint16_t );
void L84File_firstEleven( FILE * );
void L84File_writeComment( FILE *, char * );
uint32_t L84File_getDataLength( FILE * );
uint32_t L84File_getTokenCount( FILE * );
uint32_t L84File_getVarLength( FILE * );
void L84File_writeSubheader( FILE *, FILE *, char * );
uint16_t L84File_getChecksum( FILE * );
void L84File_writeChecksum( FILE *, uint16_t );

#endif