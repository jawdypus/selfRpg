/*
 * =====================================================================================
 *
 *       Filename:  helper.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  02/28/2025 08:56:06 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (),
 *   Organization:
 *
 * =====================================================================================
 */
#include <linux/limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char* get_executable_path() {
  char* path = malloc(PATH_MAX);
  if (path == NULL) {
    return NULL;  // Memory allocation failed
  }

  ssize_t count = readlink("/proc/self/exe", path, PATH_MAX);
  if (count == -1) {
    free(path);
    return NULL;
  }

  path[count] = '\0';  // Null terminate the path
  return path;
}

// To get just the directory:
char* get_executable_dir() {
  char* path = get_executable_path();
  if (path == NULL) {
    return NULL;
  }

  // Find the last '/'
  char* last_slash = strrchr(path, '/');
  if (last_slash != NULL) {
    *last_slash = '\0';  // Truncate at the last slash
  }

  return path;
}
