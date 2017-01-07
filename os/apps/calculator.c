#include "calculator.h"
#include "../modules/io.h"
#include <stdint.h>

void calculator_start(){
	char operator;
	int32_t firstNumber,secondNumber;

	io_scanf("Enter an operator (+, -, *,): %c\n",&operator);

	io_scanf("Enter two operands: %d %d\n",&firstNumber, &secondNumber);

	switch(operator)
	{
		case '+':
			io_printf("%d + %d = %d\n",firstNumber, secondNumber, firstNumber + secondNumber);
			break;

		case '-':
			io_printf("%d - %d = %d\n",firstNumber, secondNumber, firstNumber - secondNumber);
			break;

		case '*':
			io_printf("%d * %d = %d\n",firstNumber, secondNumber, firstNumber * secondNumber);
			break;

		case '/':
			io_printf("%d / %d = %d\n",firstNumber, secondNumber, firstNumber / firstNumber);
			break;

		// operator doesn't match any case constant (+, -, *, /)
		default:
			io_printf("Error! operator is not correct\n");
	}
}
