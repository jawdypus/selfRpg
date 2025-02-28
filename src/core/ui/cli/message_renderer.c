/*
 * =====================================================================================
 *
 *       Filename:  message_renderer.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  02/28/2025 09:15:02 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (),
 *   Organization:
 *
 * =====================================================================================
 */
#include "core/ui/cli/message_renderer.h"

#include <linux/limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils/helper.h"

void display_ascii(const char* filename) {
  char* exe_dir = get_executable_dir();

  char* last_slash = strrchr(exe_dir, '/');
  if (last_slash != NULL) {
    *last_slash = '\0';  // Truncate at the last slash to remove "/bin"
  }

  size_t path_len = strlen(exe_dir) + 1 + strlen(filename) + 1;
  char* full_path = (char*)malloc(path_len);

  if (full_path == NULL) {
    free(exe_dir);
  }

  sprintf(full_path, "%s/%s", exe_dir, filename);

  FILE* file = fopen(full_path, "r");
  if (!file) {
    perror("Error opening file");
    return;
  }

  char line[256];
  system("clear");  // Clear screen (use "cls" for Windows)
  while (fgets(line, sizeof(line), file)) {
    printf("%s", line);
  }
  fclose(file);
}
