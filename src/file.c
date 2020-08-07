#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "file.h"

void initFile( void ) {
    L84File.firstEleven = L84File_firstEleven;
    L84File.getChecksum =L84File_getChecksum;
    L84File.getDataLength = L84File_getDataLength;
    L84File.getTokenCount = L84File_getTokenCount;
    L84File.getVarLength = L84File_getVarLength;
    L84File.writeChecksum = L84File_writeChecksum;
    L84File.writeComment = L84File_writeComment;
    L84File.writeSubheader = L84File_writeSubheader;
    L84File.writeWord = L84File_writeWord;
}


void L84File_writeWord( FILE *f, uint16_t word ) {
    unsigned char arr[2] = { 0 };
    arr[0] = word & 0xff;
    arr[1] = ( word >> 8 ) & 0xff;
    fwrite( arr, 1, 2, f );
}

void L84File_firstEleven( FILE *f ) {
    unsigned char arr[11] = { 0 };
    char *t = "**TI83F*";
    memcpy( arr, t, 8 );
    arr[8] = 0x1a;
    arr[9] = 0x0a;
    fwrite( arr, 1, 11, f );
}

void L84File_writeComment( FILE *f, char *com ) {
    // Assumes size of exactly 42 bytes + 1 null terminus, array should have been 43 bytes.
    fwrite( com, 1, 42, f );
}

uint32_t L84File_getDataLength( FILE *f ) {
    rewind( f );
    uint32_t a = L84File.getVarLength( f );
    return a + 17;
}

uint32_t L84File_getTokenCount( FILE *f ) {
    rewind( f );
    int c;
    uint32_t tc = 0;
    while ( ( c = fgetc( f ) ) != EOF )
        tc++;
    return tc;
}

uint32_t L84File_getVarLength( FILE *f ) {
    rewind( f );
    uint32_t a = L84File.getTokenCount( f );
    return a + 2;
}

void L84File_writeSubheader( FILE *f, FILE *f2, char *vname ) {
    uint16_t dl = L84File.getDataLength( f2 );
    L84File.writeWord( f, dl );
    L84File.writeWord( f, 0xd );
    uint16_t vl = L84File.getVarLength( f2 );
    L84File.writeWord( f, vl );
    fputc( 6, f );
    fwrite( vname, 1, 8, f );
    fputc( 0, f );
    fputc( 0, f );
    L84File.writeWord( f, vl );
    uint16_t tkc = L84File.getTokenCount( f2 );
    L84File.writeWord( f, tkc );
    rewind( f2 );
    int c;
    while ( ( c = fgetc( f2 ) ) != EOF )
        fputc( c, f );
}

uint16_t L84File_getChecksum( FILE *f ) {
    fseek( f, 55L, SEEK_SET );
    int c;
    uint64_t sum = 0;
    while ( ( c = fgetc( f ) ) != EOF )
        sum += c;
    fseek( f, 0L, SEEK_END );
    return ( sum & 0xffff );
}

void L84File_writeChecksum( FILE *f, uint16_t sum ) {
    L84File.writeWord( f, sum );
}