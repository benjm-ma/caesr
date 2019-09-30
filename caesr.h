#define DEFAULT_SHIFT 5
#define ASCII_CAPTL_UPPER_BOUND 90
#define ASCII_CAPTL_LOWER_BOUND 65
#define ASCII_LOWR_UPPER_BOUND 122 
#define ASCII_LOWR_LOWER_BOUND 97
#define CIPHER_ENCODE 0
#define CIPHER_DECODE 1

/**
 * Convert character to int by first
 * converting char to string then 
 * string to int.
 */
#define char_to_int(c, dest)\
do{\
  char tmp[2];\
  tmp[0]= c;\
  dest= atoi(tmp);\
}while(0)

typedef enum { false, true } bool;

bool is_ascii_lower(char); 
bool is_ascii_upper(char);
bool is_ascii_letter(char);
FILE* open_stream (const char*, const char*);
void proc_cipher(short, FILE*, FILE*, int);
int wrap_ascii_val(int, int, int);
void print_usage(void);
