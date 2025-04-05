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
#include "core/page.h"
#include "core/todo.h"
#include "core/vault.h"
#include "utils/helper.h"

typedef struct {
  int vault_flag;
  int journal_flag;
  int page_flag;
  int todo_flag;
  char *page_value;
  char *todo_value;
} Arguments;

char *remove_quotes(char *str) {
  int len = strlen(str);
  if (len >= 2 && ((str[0] == '"' && str[len - 1] == '"') ||
                   (str[0] == '\'' && str[len - 1] == '\''))) {
    str[len - 1] = '\0';
    return str + 1;
  }

  return str;
}

Arguments parse_arguments(int argc, char *argv[]) {
  Arguments args = {0};  // Initialize all to zero/NULL

  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "--journal") == 0 || strcmp(argv[i], "-j") == 0) {
      args.journal_flag = 1;
    } else if (strcmp(argv[i], "--page") == 0 || strcmp(argv[i], "-p") == 0) {
      if (i + 1 < argc) {
        args.page_flag = 1;
        args.page_value = remove_quotes(argv[i + 1]);
        i++;
      } else {
        fprintf(
            stderr,
            "Error: Enter name of the page in quetes after the page flag\n");
      }
    } else if (strcmp(argv[i], "--todo") == 0 || strcmp(argv[i], "-t") == 0) {
      if (i + 1 < argc) {
        args.todo_flag = 1;
        args.todo_value = remove_quotes(argv[i + 1]);
        i++;
      } else {
        fprintf(stderr, "Error: Enter todo data\n");
      }
    }
  }

  return args;
}

int main(int argc, char *argv[]) {
  if (argc == 1) {
    first_run();
  }

  Arguments args = parse_arguments(argc, argv);

  if (!initVault(argc, argv)) {
    printf("Error: Failed to initialize vault manager\n");
    return 1;
  }

  if (args.journal_flag) {
    create_today_journal(getActiveVaultPath());
  }
  if (args.page_flag) {
    create_page(getActiveVaultPath(), args.page_value);
  }
  if (args.todo_flag) {
    add_todo(getActiveVaultPath(), args.todo_value);
  }

  cleanupVault();

  return 0;
}
