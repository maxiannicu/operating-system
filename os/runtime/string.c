#include "string.h"

int32_t strlen(char *str){
	int32_t length = -1;
	while(str[++length] != '\0');

	return length;
}

char* itoa(int32_t num, char* str, int32_t base){
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

int32_t atoi(char *str)
{
	int32_t res = 0; // Initialize result
	int8_t negative = 0;

    // Iterate through all characters of input string and update result
    for (int32_t i = 0; str[i] != '\0'; ++i){
    	if(i == 0 && str[i] == '-')
    		negative = -1;
    	else
    		res = res*10 + str[i] - '0';
    }

    if (negative){
    	res *= -1;
    }

    // return result.
    return res;
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
