#include "string.h"

int strlen(char *str){
	int length = -1;
	while(str[++length] != '\0');

	return length;
}

char* itoa(int num, char* str, int base){
    int i = 0;
    char isNegative = 0;
 
    /* Handle 0 explicitely, otherwise empty string is printed for 0 */
    if (num == 0){
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }
 
    // In standard itoa(), negative numbers are handled only with 
    // base 10. Otherwise numbers are considered unsigned.
    if (num < 0 && base == 10){
        isNegative = 1;
        num = -num;
    }
 
    // Process individual digits
    while (num != 0){
        int rem = num % base;
        str[i++] = (rem > 9)? (rem-10) + 'a' : rem + '0';
        num = num/base;
    }
 
    // If number is negative, append '-'
    if (isNegative)
        str[i++] = '-';
 
    str[i] = '\0'; // Append string terminator
 
    // Reverse the string
    reverse(str);
}

void reverse(char* str){
    int start = 0;
    int end = strlen(str)-1;
    while (start < end){
		char a = *(str+start);
		*(str+start) = *(str+end);
		*(str+end) = a;
			start++;
			end--;
    }
}
