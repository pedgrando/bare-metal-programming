#include "../headers/memfuncs.h"

/*
 * 	Now, all mem functions are defined as part of the boot section
 * 	as we don't need to copy them to ram, as with the rest of the
 * 	text section
 */

// Sets n mem bytes to constant c
__attribute__((section(".boot")))void *memset( void *s, int c, size_t n){
	unsigned char *dst = s;

	for(size_t i = 0; i < n; i++){
		*(dst++) = (unsigned char) c; 
	}

	return s;
}

// Move n bytes from src to dest with possibility of overlap
__attribute__((section(".boot")))void *memmove( void *dest, const void *src, size_t n){
	// create temp for granting possibility of mem overlap
	unsigned char *d = (unsigned char *)dest, temp[n];
       	const unsigned char *s = (const unsigned char *)src;

	for(size_t i = 0; i < n; i++)
		temp[i] = s[i];
	for(size_t i = 0; i < n; i++)
		d[i] = temp[i];

	return dest;
}

// Compares n first bytes of s1 with ones of s2
__attribute__((section(".boot")))int memcmp(const void *s1, const void *s2, size_t n){
	const unsigned char *str1 = (const unsigned char *) s1, *str2 = (const unsigned char *) s2;

	for(size_t i = 0; i < n; i++, str1++, str2++){
		if(*str1 < *str2)
			return -1;
		else if(*str1 > *str2){
			return 1;
		}
	}
	return 0;
}

// Copies n bytes from src to dest without overlap
__attribute__((section(".boot")))void *memcpy(void *dest, const void *src, size_t n){
	unsigned char *d = (unsigned char *)dest;
	const unsigned char *s = (const unsigned char *) src;

	for(size_t i = 0; i < n; i++)
		d[i] = s[i];

	return dest;
}
