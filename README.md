# CS_3503-Assignment2
## Author 
Ian Guzman

## Description
The project implements a set of number conversion functions in C, which focuses on base and signed number conversions.

-oct_to_bin - Converts octal string -> binary string.
-oct_to_hex – Convert octal string → hexadecimal string.
-hex_to_bin - Convert hexadecimal string → binary string.

-uint32_to_bin - Function I added that converts a 32-bit unsigned integer into a
32-character binary string with leading zeros. It is used for the final three functions.

-to_sign_magnitude – Represent a signed 32-bit integer in sign-magnitude form.
-to_ones_complement – Represent a signed 32-bit integer in one’s complement form
-to_twos_complement – Represent a signed 32-bit integer in two’s complement form.

The main.c file reads the test cases from the a2_test.txt file and prints out the tests with the output, expected output, and the final summary of how many tests you passed.

## Build Instructions
Open the terminal and make sure it is in the project folder. Then compile the program by running :
‘‘ bash
gcc -o convert convert.c main.c
./ convert
‘‘‘
Could also run "./convert > output.txt" to redirect the output into a text file of its own.

## What's New
- Added direct base mapping functions (oct/hex/bin).
- Implemented signed 32-bit number representations.
- Improved input validation and test parser.

## Test Results
Test 1: oct_to_bin(725) -> Expected: "111010101", Got: "111010101" [PASS]
Test 12: oct_to_hex(100) -> Expected: "40", Got: "40" [PASS]
Test 22: hex_to_bin(Ff) -> Expected: "11111111", Got: "11111111" [PASS]
Test 33: to_sign_magnitude(-1) -> Expected: "10000000000000000000000000000001", Got: "10000000000000000000000000000001" [PASS]
Test 40: to_ones_complement(-1) -> Expected: "11111111111111111111111111111110", Got: "11111111111111111111111111111110" [PASS]
Test 48: to_twos_complement(-255) -> Expected: "11111111111111111111111100000001", Got: "11111111111111111111111100000001" [PASS]
Summary: 51/51 tests passed
