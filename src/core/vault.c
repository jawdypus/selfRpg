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
#include <unistd.h>

static ActiveVault g_activeVault = {"", "", 0};

typedef struct {
  char name[_SC_LOGIN_NAME_MAX];
  char path[PATH_MAX];
} VaultInfo;

typedef struct {
  VaultInfo vaults[10];
  int vaultCount;
} AppConfig;

static int readConfig(AppConfig* config) {
  char* USERNAME;
  USERNAME = getlogin();
  if (USERNAME == NULL) {
    return 0;
  }

  char configPath[PATH_MAX];
  sprintf(configPath, "/home/%s/.config/selfRpg/config", USERNAME);

  FILE* fptr;

  fptr = fopen(configPath, "r");
  if (!fptr) {
    fprintf(stderr, "Error: Could not open config file at %s\n", configPath);
    return 0;
  }

  char line[PATH_MAX + _SC_LOGIN_NAME_MAX];
  config->vaultCount = 0;

  while (fgets(line, sizeof(line), fptr) && config->vaultCount < 10) {
    line[strcspn(line, "\r\n")] = 0;

    if (line[0] == '\0' || line[0] == '#') {
      continue;
    }

    char* separator = strchr(line, '=');
    if (separator) {
      size_t nameLen = separator - line;
      if (nameLen > 0 && nameLen < _SC_LOGIN_NAME_MAX) {
        strncpy(config->vaults[config->vaultCount].name, line, nameLen);
        config->vaults[config->vaultCount].name[nameLen] = '\0';

        strcpy(config->vaults[config->vaultCount].path, separator + 1);

        config->vaultCount++;
      }
    }
  }

  fclose(fptr);

  if (config->vaultCount == 0) {
    fprintf(stderr, "Warning: No vault configurations found in %s\n",
            configPath);
    return 0;
  }

  return 1;
}

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
