/*
 * =====================================================================================
 *
 *       Filename:  journal.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  03/23/2025 11:29:19 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (),
 *   Organization:
 *
 * =====================================================================================
 */
#include "core/journal.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void create_today_journal(const char *VAULT_PATH) {
  time_t t = time(NULL);
  struct tm tm = *localtime(&t);

  char FILENAME[256];

  sprintf(FILENAME, "%s/journals/%02d-%02d-%04d.md", VAULT_PATH, tm.tm_mday,
          tm.tm_mon + 1, tm.tm_year + 1900);

  char CMD[512];
  sprintf(CMD, "vim %s", FILENAME);

  system(CMD);
}
