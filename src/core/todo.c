/*
 * =====================================================================================
 *
 *       Filename:  todo.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  04/03/2025 04:40:04 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (),
 *   Organization:
 *
 * =====================================================================================
 */
#include "core/todo.h"

#include <linux/limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

void init_todos(const char *VAULT_PATH) {
  char PATH_BUFFER[PATH_MAX];

  FILE *fptr;

  const char *files[] = {"todo.md", "completed.md"};

  for (int i = 0; i < 2; i++) {
    sprintf(PATH_BUFFER, "%s/todos/%s", VAULT_PATH, files[i]);

    struct stat st = {0};
    if (stat(PATH_BUFFER, &st) == -1) {
      fptr = fopen(PATH_BUFFER, "w");
      fclose(fptr);
    }
  }
}

void add_todo(const char *VAULT_PATH, const char *TASK) {
  init_todos(VAULT_PATH);

  char FILENAME[PATH_MAX];
  FILE *fptr;

  sprintf(FILENAME, "%s/todos/todo.md", VAULT_PATH);

  fptr = fopen(FILENAME, "a");
  fprintf(fptr, "[ ] %s\n", TASK);
  fclose(fptr);
}
