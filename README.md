# Binary Toolkit

## Overview
Welcome to the Binary Toolkit project! This toolkit provides functionalities for converting between binary and decimal numbers and performing various bitwise operations. The project aims to help users understand and manipulate binary numbers using bitwise operators.

## Features
- Convert binary numbers to signed or unsigned decimal format.
- Convert decimal numbers to two's complement binary representation.
- Perform bitwise AND, OR, left shift, and right shift operations.

## Getting Started
Clone the repository on your local machine. The primary code for this project will be implemented in the `toolkit.c` file.

```bash
git clone https://github.com/raghavrajsah/Binary-Toolkit-Perform-Bitwise-.git

```

## Usage

### Binary to Decimal Conversion
To convert a binary number to a decimal format, use the following command:
```bash
./toolkit 0b<binary_number> <s/u>
```
- `<binary_number>`: The binary number to be converted (e.g., `0b10010011`).
- `<s/u>`: Specify `s` for signed or `u` for unsigned decimal conversion.

Example:
```bash
./toolkit 0b10010011 s
```
Output:
```
-2^7 + 2^4 + 2^1 + 2^0
-128 + 16 + 2 + 1
-109
```

### Decimal to Binary Conversion
To convert a decimal number to a two's complement binary format, use the following command:
```bash
./toolkit <decimal_number> <bit_count>
```
- `<decimal_number>`: The decimal number to be converted (e.g., `-13`).
- `<bit_count>`: The number of bits for the binary representation (maximum 32).

Example:
```bash
./toolkit -13 8
```
Output:
```
0 + -2^7 = -128
-128 + 2^6 = -64
-64 + 2^5 = -32
-32 + 2^4 = -16
2^3 does not fit
2^2 does not fit
-16 + 2^1 = -14
-14 + 2^0 = -13
0b11110011
```

### Bitwise Operations
To perform bitwise operations, use the following command:
```bash
./toolkit 0b<binary_number1> <operation> 0b<binary_number2>
```
- `<binary_number1>`: The first binary number (e.g., `0b10011011`).
- `<operation>`: The bitwise operation (`&` for AND, `|` for OR, `<<` for left shift, `>>` for right shift).
- `<binary_number2>`: The second binary number or shift count (e.g., `0b01011100` or `5` for shift operations).

Example for bitwise AND:
```bash
./toolkit 0b10011011 & 0b01011100
```
Output:
```
  0b10011011
& 0b01011100 
------------
  0b00011000 = 24
```

Example for left shift:
```bash
./toolkit 0b10011011 << 5
```
Output:
```
0b10011011 << 5 = 0b01100000 = 96
```

## Program Design
- **Use of logical shift operators:** The toolkit uses logical shift operators for binary operations and conversions.
- **Modular design:** The code is organized into multiple functions, avoiding duplication and enhancing readability.
- **Constants:** Constants are defined to avoid hardcoding values in the code.
- **Comments:** Functions are well-documented with comments for clarity.



Thank you for using the Binary Toolkit! If you have any questions or feedback, please don't hesitate to reach out.
