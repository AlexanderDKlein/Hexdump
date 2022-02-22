#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* Author: Alexander Klein
 * Date: 9/3/21
 * Assignment 1: Hexdump (Simple Utility)
 */ 
int main(int argc, char *argv[]) {
	//Creates strings for user input.
	char *str2;
	char *str3;
	//Creates the parameter and reads the first word.
	int param = 0;
	if (argc == 3) {
		//Reads the third part of the input if the user entered parameters
		str2 = strtok(argv[1], " ");
		str3 = strtok(argv[2], " ");
		param = 1;
	} else {
		//Makes it easier for file manipulation if user entered no parameters
		str3 = strtok(argv[1], " ");
	}
	
	//Opens and reads the file
	FILE *fr;
	fr = fopen(str3, "r");
	if (!fr) {
		printf("%s does not exist!\n", str3);
	} else {
		fclose(fr);
		//Outputs the file in octal format.
		if (param == 1 && strchr(str2, 'b') != NULL) {
			//Reopens file.
			fr = fopen(str3, "r");
			//Declares variables.
			int offset = 0x0;
			int count = 16;
			int oct;
			//Gets the next character
			while ((oct = fgetc(fr)) != EOF) {
				//Checks if its time to move to the next offset line
				if (count == 16) {
					printf("\n%07x ", offset);
					offset += 0x10;
					count = 0;
				}
				//Outputs the octal number
				printf("%03o ", oct);
				count++;
			}
			//Closes the file.
			fclose(fr);
		}
		//Outputs the file in hexadecimal format followed by ASCII.
		if (param == 1 && strchr(str2, 'C') != NULL) {
			//Reopens file
			fr = fopen(str3, "r");
			//Declares variables
			int offset = 0x0;
			char ascii[18] = "|";
			int count = 0;
			int hex;
			char c;
			char bar = '|';
			//Outputs the first offset number
			printf("\n%08x ", offset);
			offset += 0x10;
			//Gets the next character
			while ((hex = fgetc(fr)) != EOF) {
				c = hex;
				//Adds the space between the first 8 characters and the next 8
				if (count == 8) {
					printf(" ");
				}
				//Outputs the ascii translation and moves to the next offset line
				if (count == 16) {
					strncat(ascii, &bar, 1);
					printf(" %s\n%08x ", ascii, offset);
					offset += 0x10;
					count = 0;
					*ascii = '\0';
					strncat(ascii, &bar, 1);
				}
				//Outputs the hex values
				printf("%02x ", hex);
				count++;
				//Adds the ascii translated character (if it can be translated) to the string
				if (isprint(c) != 0) {
					strncat(ascii, &c, 1);
				} else {
					char dot = '.';
					strncat(ascii, &dot, 1);
				}
			}
			//Outputs the last ascii translated string in proper indentation format
			while (count < 16) {
				printf("   ");
				if (count == 8) {
					printf(" ");
				}
				count++;
			}
			strncat(ascii, &bar, 1);
			printf(" %s", ascii);
			//Closes the file
			fclose(fr);
		}
		//Outputs the file in standard hexadecimal format.
		if (param == 0) {	
			//Reopens file
			fr = fopen(str3, "r");
			//Declares variables
			int offset = 0x0;
			int count = 8;
			int hex;
			int hex2;
			//Gets the next two hex humbers
			while ((hex2 = fgetc(fr)) != EOF) {
				hex = fgetc(fr);
				//Moves to the next offset line
				if (count == 8) {
					printf("\n%07x ", offset);
						offset += 0x10;
					count = 0;
				}
				//Outputs the hex numbers
				printf("%02x%02x ", hex, hex2);
				count++;
			}
			//Closes the file.
			fclose(fr);
		}
	}
	printf("\n");
	return 0;
}
