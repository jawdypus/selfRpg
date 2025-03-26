/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  02/26/2025 03:20:20 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (),
 *   Organization:
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <string.h>

#include "core/character.h"
#include "core/config.h"
#include "core/journal.h"
#include "core/vault.h"
#include "utils/helper.h"

void read_args(int argc, char *argv[]) {
  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-j") == 0 || strcmp(argv[i], "--journal")) {
      create_today_journal(getActiveVaultPath());
    }
  }
}

int main(int argc, char *argv[]) {
  if (argc == 1) {
    first_run();
  }

  if (!initVault(argc, argv)) {
    printf("Error: Failed to initialize vault manager\n");
    return 1;
  }

  read_args(argc, argv);

  cleanupVault();

  return 0;
}
