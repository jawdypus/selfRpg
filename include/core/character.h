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

typedef enum { WARRIOR = 0, WIZARD = 1, BARD = 2, SCOUT = 3 } CharacterClasses;

typedef struct {
  CharacterClasses chClass;
  char name[_SC_LOGIN_NAME_MAX];
  int hp;
  int strenght;
  int perception;
  int endurance;
  int charisma;
  int intelligence;
  int agility;
  int experience;
  int level;
} Character;

void initPlayer(char *VAULT_PATH);
void set_hero_name(Character *character);
void choose_class(Character *character);
void init_character(Character *character);
void write_character_data(Character *character, char *VAULT_PATH);

#endif
