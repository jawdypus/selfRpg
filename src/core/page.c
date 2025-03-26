/*
 * =====================================================================================
 *
 *       Filename:  page.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  03/26/2025 09:17:13 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (),
 *   Organization:
 *
 * =====================================================================================
 */
#include "core/page.h"

#include <linux/limits.h>
#include <stdio.h>
#include <stdlib.h>

void create_page(const char *VAULT_PATH, const char *PAGE_NAME) {
  char FILENAME[PATH_MAX];

  sprintf(FILENAME, "%s/pages/%s", VAULT_PATH, PAGE_NAME);

  char CMD[512];
  sprintf(CMD, "vim \"%s\"", FILENAME);

  system(CMD);
}
