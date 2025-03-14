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

int is_first_run(void) { return 1; }

void first_run(void) {
  if (!is_first_run()) {
    return;
  }

  char DEFAULT_PATH[PATH_MAX], DEFAULT_VAULT_NAME[_SC_LOGIN_NAME_MAX],
      *DEFAULT_USERNAME;
  char VAULTH_PATH[PATH_MAX], USERNAME[_SC_LOGIN_NAME_MAX];

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
  fgets(VAULTH_PATH, sizeof(VAULTH_PATH), stdin);

  // Save vault and name to the config
  char configDirectory[PATH_MAX];
  sprintf(configDirectory, "/home/%s", DEFAULT_USERNAME);

  printf("Home dir is: %s\n", configDirectory);

  struct stat st = {0};
  if (stat(configDirectory, &st) == -1) {
    // Directory doesn't exist, so print an error message
    perror("Parent directory does not exist");
    return;
  }

  strcat(configDirectory, "/.config/");
  if (stat(configDirectory, &st) == -1) {
    // Directory doesn't exist, so create it
    if (mkdir(configDirectory, 0700) == -1) {
      perror("Error creating .config directory");
      return;
    }
    printf("Created %s directory\n", configDirectory);
  }

  strcat(configDirectory, "selfRPG/");
  if (stat(configDirectory, &st) == -1) {
    // Directory doesn't exist, so create it
    if (mkdir(configDirectory, 0700) == -1) {
      perror("Error creating .config directory");
      return;
    }
    printf("Created %s directory\n", configDirectory);
  }
}
