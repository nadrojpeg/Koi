/* Koi Video Game Library
 * Copyright (c) 2025 Paolo Giordano
 * Licensed under the MIT License. See the LICENSE file for details.
 *
 * error.c - This source file is part of the error handling module and provides its implementation.
*/
 
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <stdio.h>
/* Since C23 _Thread_local is deprecated and thread_local is a keyword. */
#if __STDC_VERSION__ < 202311L // C23 Version
    #include <threads.h>
    #define thread_local _Thread_local
#endif
#include "error.h"
#include "errorprivate.h"

#define KOI_ERROR_BUFFER_SIZE 4096

thread_local char koi_global_error_buffer[KOI_ERROR_BUFFER_SIZE] = {0};

void koi_put_debug_info(const char *debug_info_format_string, ...) {
	#ifdef KOI_DEBUG_MODE
	char error_buffer[KOI_ERROR_BUFFER_SIZE];
	
	va_list var_args;
	va_start (var_args, debug_info_format_string);
	/* _vsnprintf_s uses a count to prevent buffer overflow (still vulnerable to format string attack) */
	_vsnprintf_s(error_buffer, KOI_ERROR_BUFFER_SIZE, KOI_ERROR_BUFFER_SIZE - 1, debug_info_format_string, var_args);
	va_end (var_args);
	 
	fprintf(stderr, "%s", error_buffer);
	#else 
		(void *) debug_info_format_string; // Used to turn off "cl /W4" warnings
	#endif
}
 
void koi_error_box(const char *caption, const char *error_message_format_string, ...) {
	int function_line = __LINE__ - 1;
	char error_buffer[KOI_ERROR_BUFFER_SIZE];

	va_list var_args;
	va_start (var_args, error_message_format_string);
	/* _vsnprintf_s uses a count to prevent buffer overflow (still vulnerable to format string attack) */
	_vsnprintf_s(error_buffer, KOI_ERROR_BUFFER_SIZE, KOI_ERROR_BUFFER_SIZE - 1, error_message_format_string, var_args);
	va_end (var_args);
   
    int message_box_return_value =  MessageBoxA(NULL, error_buffer, caption, MB_OK | MB_ICONERROR);
	if (message_box_return_value == 0) {
		koi_put_debug_info("In function %s (file: %s, line: %d): 'MessageBoxA' failed with error code %d\n", 
			__func__,
			__FILE__, 
			function_line,
			GetLastError());
	}
}
 
const char *koi_get_last_error(void) {
	return koi_global_error_buffer;
}
 
void koi_set_error_message(const char *error_message_format_string, ...) {
	char error_buffer[KOI_ERROR_BUFFER_SIZE];
	 
	va_list var_args;
	va_start (var_args, error_message_format_string);
	/* _vsnprintf_s uses a count to prevent buffer overflow (still vulnerable to format string attack) */
	int written_characters = _vsnprintf_s(error_buffer, KOI_ERROR_BUFFER_SIZE, KOI_ERROR_BUFFER_SIZE - 1, error_message_format_string, var_args);
	va_end (var_args);
	 
	// written_characters doesn't count the null terminator character
	memcpy(koi_global_error_buffer, error_buffer, written_characters + 1);
}