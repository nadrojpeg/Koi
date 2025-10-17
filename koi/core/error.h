/* Koi Video Game Library
 * Copyright (c) 2025 Paolo Giordano
 * Licensed under the MIT License. See the LICENSE file for details.
 *
 * error.h - This header is part of the error handling module and exposes its public API.
 * 
 * The error handling module is quite simple, but effective: every Koi function can store an error message into a 
 * buffer that Koi users can later read in case of function failure. Since Koi is designed with multi-threading 
 * in mind, Koi functions can be called from any thread, making it necessary to guarantee error buffer consistency 
 * across multiple threads. Given this premise, this module uses Thread-Local Storage variables from the C standard 
 * library, guaranteeing that each thread has its own unique buffer.
 * 
 * Public API:
 * - koi_error_box: displays a message box with given caption and error message;
 * - koi_get_last_error: retrieves the last stored error message from the current thread's buffer. 
*/

#ifndef KOI_ERROR_H
#define KOI_ERROR_H
 
// Disable C++ name mangling
#ifdef __cplusplus
extern "C"
{
#endif

/* Used by some Koi function as a return type. */
typedef enum koi_error_t {
  KOI_ERROR_MUTEX_OK,
  KOI_ERROR_MUTEX_ABANDONED,
  KOI_ERROR_MUTEX_FAILED
} koi_error_t;

/* This function works like printf: you can pass an error message as a format string, followed by a variable-length 
 * parameter list. Max supported error message format string length is 4096 bytes. Longer strings will be truncated. 
*/
void koi_error_box(const char *caption, const char *error_message_format_string, ...);

/* Returns the pointer to the current thread's unique error buffer.
 * After any thread starts its execution, the error message should be checked only after function failure, 
 * which is always indicated by the function's return value.
*/
const char *koi_get_last_error(void);

// Disable C++ name mangling
#ifdef __cplusplus
}
#endif

#endif /* KOI_ERROR_H */