/*
 * =====================================================================================
 *
 *       Filename:  config.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  02/27/2025 04:47:20 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (),
 *   Organization:
 *
 * =====================================================================================
 */
#ifndef CONFIG_H
#define CONFIG_H

#define MAX_LINE_SIZE 256
#define MAX_KEY_SIZE 64
#define MAX_VALUE_SIZE 192

typedef struct {
  char key[MAX_KEY_SIZE];
  char value[MAX_VALUE_SIZE];
} ConfigItem;

int is_first_run(void);

void first_run(void);

#endif
