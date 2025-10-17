/* Koi Video Game Library
 * Copyright (c) 2025 Paolo Giordano
 * Licensed under the MIT License. See the LICENSE file for details.
 *
 * errorprivate.h - This header is part of the error handling module and exposes its private API.
 * 
 * Private API:
 * - koi_put_debug_info: prints debug info to stderr (useful while debugging Koi library);
 * - koi_set_error_message: store an error message to the current thread's error buffer. 
*/

#ifndef KOI_ERROR_PRIVATE_H
#define KOI_ERROR_PRIVATE_H

// Disable C++ name mangling
#ifdef __cplusplus
extern "C"
{
#endif

/* Used to print on stderr Koi internal errors and Win32 Error Codes. 
 * Max format string length is 4096 characters.
*/
void koi_put_debug_info(const char *debug_info_format_string, ...);

/* Used by Koi functions to store error messages that are useful for the Koi final user. 
*/
void koi_set_error_message(const char *error_message_format_string, ...);
 
// Disable C++ name mangling
#ifdef __cplusplus
}
#endif
 
#endif /* KOI_ERROR_PRIVATE_H */