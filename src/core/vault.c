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
  sprintf(configPath, "/home/%s/.config/selfRPG/config", USERNAME);

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

static int findVaultByName(const AppConfig* config, const char* vaultName) {
  for (int i = 0; i < config->vaultCount; i++) {
    if (strcmp(config->vaults[i].name, vaultName) == 0) {
      return i;
    }
  }

  return -1;  // Not found
}

static int determineActiveVault(AppConfig* config, int argc, char* argv[]) {
  int activeVaultIndex = 0;

  // Check for vault specified in command line args
  for (int i = 1; i < argc; i++) {
    // Check for -v or --vault flag
    if ((strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--vault") == 0) &&
        i + 1 < argc) {
      int foundIndex = findVaultByName(config, argv[i + 1]);
      if (foundIndex >= 0) {
        activeVaultIndex = foundIndex;
        break;
      } else {
        fprintf(stderr,
                "Warning: Specified vault '%s' not found in config, using "
                "default\n",
                argv[i + 1]);
      }
      i++;  // Skip the next argument as it's the vault name
    }
  }

  return activeVaultIndex;
}

static int validateVaultPath(const char* vaultPath) {
  // Check if directory exists
  if (access(vaultPath, F_OK) == -1) {
    fprintf(stderr, "Error: Vault directory %s does not exist\n", vaultPath);
    return 0;
  }

  // Check if character.txt exists in the vault
  char characterPath[PATH_MAX];
  snprintf(characterPath, PATH_MAX, "%s/character.txt", vaultPath);

  if (access(characterPath, F_OK) == -1) {
    fprintf(stderr, "Error: Character file %s does not exist\n", characterPath);
    return 0;
  }

  return 1;
}

int initVault(int argc, char* argv[]) {
  if (g_activeVault.isInitialized) {
    return 1;
  }

  AppConfig config;

  if (!readConfig(&config)) {
    return 0;
  }

  int activeIndex = determineActiveVault(&config, argc, argv);

  strncpy(g_activeVault.name, config.vaults[activeIndex].name,
          _SC_LOGIN_NAME_MAX - 1);
  g_activeVault.name[_SC_LOGIN_NAME_MAX - 1] = '\0';

  strncpy(g_activeVault.path, config.vaults[activeIndex].path, PATH_MAX - 1);
  g_activeVault.path[PATH_MAX - 1] = '\0';

  // Validate the vault path
  if (!validateVaultPath(g_activeVault.path)) {
    return 0;
  }

  g_activeVault.isInitialized = 1;
  return 1;
}

const char* getActiveVaultName(void) {
  if (!g_activeVault.isInitialized) {
    fprintf(stderr, "Error: Vault manager not initialized\n");
    return "";
  }

  return g_activeVault.name;
}

// Get the active vault path
const char* getActiveVaultPath(void) {
  if (!g_activeVault.isInitialized) {
    fprintf(stderr, "Error: Vault manager not initialized\n");
    return "";
  }
  return g_activeVault.path;
}

// Check if the vault manager is initialized
int isVaultInitialized(void) { return g_activeVault.isInitialized; }

// Free resources used by vault manager - call this at program end
void cleanupVault(void) { memset(&g_activeVault, 0, sizeof(ActiveVault)); }

