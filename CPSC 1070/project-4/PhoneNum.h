/* File Name: PhoneNum.h
 * Name: Kenny Sun
 * Date: 12/3/2023
 * Purpose: Header file for PhoneNum.c
 * Citations:
 * Anon. ASCII table. Retrieved December 3, 2023a from https://www.asciitable.com/
 * Anon. FILE. Retrieved December 3, 2023b from https://cplusplus.com/reference/cstdio/FILE/
 * Anon. Fprintf. Retrieved December 3, 2023c from https://cplusplus.com/reference/cstdio/fprintf/
 * Anon. Fscanf. Retrieved December 3, 2023d from https://cplusplus.com/reference/cstdio/fscanf/
 * Academic Honesty Statement:
 * As members of the Clemson University community, we have inherited
 * Thomas Green Clemson’s vision of this institution as a “high seminary of
 * learning.” Fundamental to this vision is a mutual commitment to
 * truthfulness, honor, and responsibility, without which we cannot earn the
 * trust and respect of others. Furthermore, we recognize that academic
 * dishonesty detracts from the value of a Clemson degree. Therefore, we shall
 * not tolerate lying, cheating, or stealing in any form
 * Electronically Signed - Kenny Sun
 */
#ifndef PHONENUM_H //Header guards
#define PHONENUM_H

#include <stdio.h> //Needed for file reading

//Function prototypes
void conversionT9(FILE*, FILE*, char);
char *toWord(char*);
char *toDigits(char*);
char *getNextChars(FILE*);
void textonymFind(char*);

#endif
