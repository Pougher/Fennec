#ifndef FENNEC_LOG_H
#define FENNEC_LOG_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

/*
 * If your terminal does not support true colour, before including fennec.h
 * write #define FENNEC_TERMINAL_NOCOLOUR
 *
 * All log functions insert a \n at the end of the message provided
 */

/*
 * @description
 * Logs an error to stderr
 * If FENNEC_TERMINAL_NOCOLOUR is not defined, then the output text will be
 * coloured RED
 *
 * @argument: The error that is to be output
 */
void fennec_log_error(char*);

/*
 * @description
 * Logs info to stdout
 * If FENNEC_TERMINAL_NOCOLOUR is not defined, then the output text will be
 * coloured WHITE
 *
 * @argument: The info that is to be output
 */
void fennec_log_info(char*);

/*
 * @description
 * Logs a warning to stdout
 * If FENNEC_TERMINAL_NOCOLOUR is not defined, then the output text will be
 * coloured ORANGE
 *
 * @argument: The info that is to be output
 */
void fennec_log_warning(char*);

#endif
