
// * CLRSTR header file, created by Hppsrc.
// * Header build 25011316

// * Simple Color String Formatting C Header

// * Source code on: https://github.com/hppsrc/libs
// * Under LGPLv3 license feel free to modify, distribute and use this code for any purpose.

#pragma once

#ifndef CLRSTRG_H
#define CLRSTRG_H

#define NONE    ""
#define RESET   "\e[0"

#define BLACK   "30"
#define RED     "31"
#define GREEN   "32"
#define YELLOW  "33"
#define BLUE    "34"
#define MAGENTA "35"
#define CYAN    "36"
#define WHITE   "37"

// #define BOLD_x   "[1;3xm"
// #define BG_x     "[4xm"

#define MAX_STR_LENGTH 256

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {
    RST,  // RESET: Reset any color to default at the start
 // CRT,  // CURRENT: Set color for the current context
    IGN,  // IGNORE: Overwrite any prev. color
    END   // END: Reset any color to defeult at the end
} STATE;

/**
 * @brief Formats a string with color using ANSI escape codes,
 * 
 * @param clrstr_s The string to be formatted
 * @param clrstr_c The color code for text (RED, GREEN, BLUE, NONE, etc.)
 * @param clrstr_bg The background color code (RED, GREEN, BLUE, NONE, etc.)
 * @param clrstr_st The state of color formatting (RST: Reset before, IGN: Ignore prev, END: Reset after)
 * 
 * @return Formatted string with ANSI color codes.
 * 
 * @example
 *   printf_clrstr("Hello", RED, NONE, RST);
 *   printf_clrstr("World", BLUE, RED, END);
 */
char* printf_clrstr(char clrstr_s[], const char* clrstr_c, const char* clrstr_bg , STATE clrstr_st) {

    char final[MAX_STR_LENGTH] = "";        // final string to return
    char clstr_format[MAX_STR_LENGTH] = ""; // backg string to build

    if ( clrstr_st == RST ) { clrstr_bg = clrstr_c = RESET; }

    sprintf(clstr_format,"\e[%sm\e[%dm", clrstr_c, atoi(clrstr_bg) + 10 ); // Concat format 
    sprintf(final,"%s%s", clstr_format, clrstr_s ); // Finalconcat

    if ( clrstr_st == END ) { sprintf(final, "%s%sm", final, RESET ); } // Reset if END set

    return strdup(final); // Return final String

}

#endif // CLRSTRG_H