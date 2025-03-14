/*
 * =====================================================================================
 *
 *       Filename:  character.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  02/27/2025 04:11:23 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (),
 *   Organization:
 *
 * =====================================================================================
 */
#ifndef CHARACTER_H
#define CHARACTER_H

#include <unistd.h>

typedef struct Character {
  char Name[_SC_LOGIN_NAME_MAX];
} Character;

void choose_class(void);

#endif
