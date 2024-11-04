#ifndef MEM_T_H_
#define MEM_T_H_

unsigned long  read_long_value  (int pointer);
unsigned int   read_int_value   (int pointer);
unsigned short read_short_value (int pointer);
unsigned char  read_byte_value  (int pointer);

long  read_signed_long_value  (int pointer);
int   read_signed_int_value   (int pointer);
short read_signed_short_value (int pointer);
char  read_signed_byte_value  (int pointer);

void write_long_value  (int pointer, unsigned long value);
void write_int_value   (int pointer, unsigned int value);
void write_short_value (int pointer, unsigned short value);
void write_byte_value  (int pointer, unsigned char value);

void write_signed_long_value  (int pointer, long value);
void write_signed_int_value   (int pointer, int value);
void write_signed_short_value (int pointer, short value);
void write_signed_byte_value  (int pointer, char value);

#endif // MEM_T_H_
