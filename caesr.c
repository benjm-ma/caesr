/**
 *: Program     : caesr
 *: Author      : Benjamin Ahola
 *: Date        : 17/09/2019
 *: Description : A program which encrypts and decrypts ASCII text 
 *:             : using the caesar cipher.
 *: Version     : v0.1
 *: Usage       : caesr [-[d|e][n]|h] [string|file]
 *:             : Options: 
 *:             :   -d[n]    : Decrypt a message using the offset of n. 
 *:             :   -e[n]    : Encrypt a message using the offset of n.
 *:             :   -f [PATH]: Read from a file at PATH
 *:             :   -o [PATH]: Write from a file at PATH
 *:             :   -h       : Display usage message
 *    -d[n[-k]] String  : Decrypt a string shifting by n
 *            caesr -d1 "AVGDR"
 *            caesr -d1-4 "AVGDR"
 *            caesr -d1 "AVGDR" output.txt
 *            caesr -d1 -o output.txt 
 *
 *    -e[n] String  : Encrypt a string shifting by n
 *            caesr -e2 "Hello"
 *    -h : print usage 
 *
 *    *When encrypting, if n is not provided, 5 is used as default.
 *      When decrypting, if n is not provided, 5 is used as default.
 *      You can try a range of shifts when decrypting as such: caesr -d1-4 "AVGDR"
 *
 * - Program can either read from a file, from the command line or be apart of a 
 *   pipeline.
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include "caesr.h"

int main( int argc, char* argv[] )
{
  FILE *fp_out= stdout;
  FILE *fp_in= stdin;
  unsigned short offset;

  if (argc == 3){ // Reading from file or String
    // TODO: Determine if user specified pathname or string
    // Assume pathname is string for now
    fp_in= open_stream (argv[2], "r");
    char_to_int(argv[1][2], offset);
  }else if (argc == 2){ //Reading from stdin
    char_to_int(argv[1][2], offset);
  }else{
    print_usage();
  }
  
  switch (argv[1][1]){
    case 'd':
      proc_cipher( offset, fp_in, fp_out, CIPHER_DECODE );
      break;
    case 'e':
      proc_cipher( offset, fp_in, fp_out, CIPHER_ENCODE );
      break;
    default:
      printf ("Usage: ...\n");
  }

  fclose(fp_in);
  fclose(fp_out);
  return 0;
}

bool is_ascii_lower(char c) 
{
  if (c > 96 && c < 123)
    return true;
  return false;
}
bool is_ascii_upper(char c)
{
  if (c > 63 && c < 91)
    return true;
  return false;
}
bool is_ascii_letter(char c)
{
  if ((is_ascii_lower(c) || is_ascii_upper(c)))
    return true;
  return false;
}

int wrap_ascii_val( int x, int lower_bound, int upper_bound )
{
  //printf( "%c: value is %d\n", x, x);
  if( x < lower_bound )
    return upper_bound - (lower_bound - x) % (upper_bound - lower_bound) + 1;
  else if( x > upper_bound )
    return lower_bound + (x - lower_bound) % (upper_bound - lower_bound) - 1;
  else
    return x;
}

FILE* open_stream (const char* path, const char* mode)
{
  FILE* fp= fopen (path, mode);
  if (!fp){
    printf ("Error: %s\n\tUnable to open file: %s\n", strerror(errno), path);
    return stdin;
  }
  return fp;
}

void proc_cipher( short offset, FILE *fp_in, FILE *fp_out, int out_fmt )
{
  char c= fgetc(fp_in);
  int c_offset= 0;

  while( c != EOF ){

    if( is_ascii_letter(c) ){
      
      // Are we decoding  or encoding cipher text?
      if( out_fmt == CIPHER_ENCODE )
        c_offset= c + offset;
      else
        c_offset= c - offset;

      if( is_ascii_upper(c) ){
        c= wrap_ascii_val( c_offset, ASCII_CAPTL_LOWER_BOUND, ASCII_CAPTL_UPPER_BOUND );
      }else{
        c= wrap_ascii_val( c_offset, ASCII_LOWR_LOWER_BOUND, ASCII_LOWR_UPPER_BOUND );
      }
    }

    fputc( c, fp_out );
    c= fgetc( fp_in );
  }
  return;
}

void print_usage()
{
  printf(
      "Usage:\n"
      "\tcaesr [-[d|e][n]|h] string|-f PATH [-o [PATH]]\n"
      "Options:\n"
      "\t-d[n]\t\t: Decrypt a message using the offset n\n"
      "\t-e[n]\t\t: Encrypt a message using the offset n\n"
      "\t-f [PATH]\t: Read from a file at PATH\n"
      "\t-o [PATH]\t: Write to a file at PATH\n"
      "\t-h \t\t: Display this message\n\n"
  );
}
