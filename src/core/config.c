/*
 * =====================================================================================
 *
 *       Filename:  config.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  02/27/2025 04:49:04 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (),
 *   Organization:
 *
 * =====================================================================================
 */
#include <errno.h>
#include <linux/limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "core/character.h"
#include "core/vault.h"

int is_first_run(void) {
  char *USERNAME;
  USERNAME = getlogin();
  if (USERNAME == NULL) {
    perror("getlogin failed");
  }

  char configDirectory[PATH_MAX];
  sprintf(configDirectory, "/home/%s/.config/selfRPG/config", USERNAME);

  FILE *file;
  file = fopen(configDirectory, "r");
  if (file) {
    return 0;  // FALSE
    fclose(file);
  } else {
    return 1;  // TRUE
  }
}

int init_config(char HERO_NAME[_SC_LOGIN_NAME_MAX],
                char VAULTH_PATH[PATH_MAX]) {
  char *USERNAME;
  USERNAME = getlogin();
  if (USERNAME == NULL) {
    perror("getlogin failed");
  }

  char configDirectory[PATH_MAX];
  sprintf(configDirectory, "/home/%s", USERNAME);

  struct stat st = {0};
  if (stat(configDirectory, &st) == -1) {
    // Directory doesn't exist, so print an error message
    perror("Parent directory does not exist");
    return 1;
  }

  strcat(configDirectory, "/.config/");
  if (stat(configDirectory, &st) == -1) {
    // Directory doesn't exist, so create it
    if (mkdir(configDirectory, 0700) == -1) {
      perror("Error creating .config directory");
      return 1;
    }
  }

  strcat(configDirectory, "selfRPG/");
  if (stat(configDirectory, &st) == -1) {
    // Directory doesn't exist, so create it
    if (mkdir(configDirectory, 0700) == -1) {
      perror("Error creating .config directory");
      return 1;
    }
  }

  char FILENAME[PATH_MAX];
  char ITEM[256];

  sprintf(FILENAME, "%sconfig", configDirectory);
  sprintf(ITEM, "%s=%s", HERO_NAME, VAULTH_PATH);

  FILE *fptr;

  fptr = fopen(FILENAME, "w");
  fprintf(fptr, ITEM);

  // Close the file
  fclose(fptr);

  return 0;
}

void first_run(void) {
  if (is_first_run() == 0) {
    return;
  }

  char DEFAULT_PATH[PATH_MAX], DEFAULT_VAULT_NAME[_SC_LOGIN_NAME_MAX],
      *DEFAULT_USERNAME;
  char VAULT_PATH[PATH_MAX], USERNAME[_SC_LOGIN_NAME_MAX];

  memset(DEFAULT_VAULT_NAME, 0, _SC_LOGIN_NAME_MAX);

  // Setting the default username
  DEFAULT_USERNAME = getlogin();
  if (DEFAULT_USERNAME == NULL) {
    perror("getlogin failed");
  }

  printf("Enter your hero name [%s]: ", DEFAULT_USERNAME);
  fgets(USERNAME, sizeof(USERNAME), stdin);

  size_t len = strlen(USERNAME);
  if (len > 0 && USERNAME[len - 1] == '\n') {
    USERNAME[len - 1] = '\0';
    len--;
  }

  if (len == 0) {
    strcpy(USERNAME, DEFAULT_USERNAME);
  }

  // Setting the default path

  strcat(DEFAULT_VAULT_NAME, "/");
  strcat(DEFAULT_VAULT_NAME, USERNAME);
  strcat(DEFAULT_VAULT_NAME, "Journey");

  getcwd(DEFAULT_PATH, sizeof(DEFAULT_PATH));
  strcat(DEFAULT_PATH, DEFAULT_VAULT_NAME);

  printf("Enter vault path [%s]: ", DEFAULT_PATH);
  fgets(VAULT_PATH, sizeof(VAULT_PATH), stdin);
  len = strlen(VAULT_PATH);
  if (len > 0 && VAULT_PATH[len - 1] == '\n') {
    VAULT_PATH[len - 1] = '\0';
    len--;
  }

  if (len == 0) {
    strcpy(VAULT_PATH, DEFAULT_PATH);
  }

  struct stat st = {0};
  if (stat(VAULT_PATH, &st) == -1) {
    // Directory doesn't exist, so create it
    if (mkdir(VAULT_PATH, 0700) == -1) {
      perror("Error creating vault directory");
      return;
    }
  }

  // Save vault and name to the config
  if (init_config(USERNAME, VAULT_PATH)) {
    return;
  }

  generate_vault_files(VAULT_PATH);
  initPlayer(VAULT_PATH, USERNAME);
}
