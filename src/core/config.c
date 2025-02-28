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
#include <linux/limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
}
