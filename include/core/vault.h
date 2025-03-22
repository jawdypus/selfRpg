/*
 * =====================================================================================
 *
 *       Filename:  vault.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  03/20/2025 05:01:30 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (),
 *   Organization:
 *
 * =====================================================================================
 */
#ifndef VAULT_H
#define VAULT_H

#include <linux/limits.h>
#include <unistd.h>

typedef struct {
  char name[_SC_LOGIN_NAME_MAX];
  char path[PATH_MAX];
  int isInitialized;
} ActiveVault;

int initVault(int argc, char* argv[]);
const char* getActiveVaultName(void);
const char* getActiveVaultPath(void);
int isVaultManagerInitialized(void);
void cleanupVault(void);

void generate_vault_files(char* VAULT_PATH);

#endif
