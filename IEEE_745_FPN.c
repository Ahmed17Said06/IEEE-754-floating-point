// Name: Ahmed Said AbdelSattar
//NU ID: 211000541
// C program to convert a float value to IEEE 754 floating point representation and vice versa
// CIT 661 MalwareAnalysis

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

void print_Binary_rep (int n, int i)
{
	// Prints the binary representation of a number n into i bits.

	int t;
	for (t = i - 1; t >= 0; t--) {

		if ((n >> t) & 1)
			printf("1");
		else
			printf("0");
	}
}


typedef union {

	float input;
	struct
	{
    // Noncompliant Code Example (Bit-Field Alignment)
		// Members of the union data structure use the same memory (32 bits) https://en.wikipedia.org/wiki/Union_type.

		unsigned int Mantissa : 23; // LSB
		unsigned int Exponent : 8;
		unsigned int Sign : 1; // MSB

	} input32bits;
} IEEE_float;

// Function to print float value into IEEE 754 floating point representation.
void printIEEE_754(IEEE_float var)
{


	printf("%d", var.input32bits.Sign);
	print_Binary_rep(var.input32bits.Exponent, 8);
	print_Binary_rep(var.input32bits.Mantissa, 23);
	printf("\n\n\n");

  printf("\nSign bit value: %d", var.input32bits.Sign);
  printf("\nExponent bit value:");
  print_Binary_rep(var.input32bits.Exponent, 8);
  printf("\nMantissa bit value:");
  print_Binary_rep(var.input32bits.Mantissa, 23);
printf("\n\n\n");

}


// Function to compute float value out of IEEE 754 floating point representation.
void printFLoat(char *arr){

  float final = 0;
  int bin[31], i;

  // convert the 32-bit string to array of integers.
  for (i = 0; i<32 ; i++)
    {
        bin[i] = arr[i] - '0';
    }

    // Calculate Mantissa.
    int temp_m = 1;
    float Mantissa = 0;

    for (i = 9; i<32 ; i++)
      {
          Mantissa = Mantissa + (bin[i] * pow(2,(-1 * temp_m)));
          temp_m = temp_m + 1;
      }

      Mantissa = Mantissa + 1;

      printf("\nMantissa: %f", Mantissa);

      // Calculate Exponent.
      int temp_E = 0;
      int Exponent = 0;

      for (i = 8; i>0 ; i--)
        {
            Exponent = Exponent + (bin[i] * pow(2,(1 * temp_E)));
            temp_E = temp_E + 1;
        }

        printf("\nExponent: %d", Exponent);

        // Calculate the sign.

        if (!bin[0])
        {
          printf("\nSign: +1");
          final = Mantissa * pow(2,(Exponent - 127));
          printf("\nThe computed floating value = mantissa x 2^(Exponent - 127) = %f", final);
        }
        else
        {
          printf("\nSign: -1");
          final = Mantissa * pow(2,(Exponent - 127));
          final = (-1 * final);
          printf("\nThe computed floating value = mantissa x 2^(Exponent - 127) = %f", final);
        }
}



int main()
{
  while(1){

	IEEE_float value;

  printf("Please make sure to enter valid inputs otherwise you will get irrational results.");

  printf("\n\nEnter a float value : ");

  scanf("%f", &value.input);

	printf("IEEE 754 representation of %f is : ", value.input);
	printIEEE_754(value);


  char *arr[31];
  printf("Enter 32-bit (IEEE 754): ");
  scanf("%s", arr);
  printFLoat(arr);
  printf("\n\n\n");

        }
  return 0;
}
