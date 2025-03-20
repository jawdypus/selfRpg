/*
 * =====================================================================================
 *
 *       Filename:  vault.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  03/20/2025 05:04:18 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (),
 *   Organization:
 *
 * =====================================================================================
 */
#include "core/vault.h"

#include <errno.h>
#include <linux/limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

void generate_vault_files(char* VAULT_PATH) {
  char PATH_BUFFER[PATH_MAX];

  const char* dirs[] = {"pages", "journals", "todos"};

  for (int i = 0; i < 3; i++) {
    sprintf(PATH_BUFFER, "%s/%s", VAULT_PATH, dirs[i]);

    struct stat st = {0};
    if (stat(PATH_BUFFER, &st) == -1) {
      if (mkdir(PATH_BUFFER, 0700) == -1) {
        perror("Error creating directory");
        return;
      }
    }
  }

  char FILENAME[PATH_MAX];

  sprintf(FILENAME, "%s/character.txt", VAULT_PATH);

  FILE* fptr;

  fptr = fopen(FILENAME, "w");

  fclose(fptr);
}
