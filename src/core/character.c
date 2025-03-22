/*
 * =====================================================================================
 *
 *       Filename:  character.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  02/27/2025 04:19:22 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (),
 *   Organization:
 *
 * =====================================================================================
 */
#include "core/character.h"

#include <linux/limits.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "core/ui/cli/message_renderer.h"

const char *characters[] = {
    "assets/characters/warrior", "assets/characters/wizard",
    "assets/characters/bard", "assets/characters/scout"};

const int num_characters = sizeof(characters) / sizeof(characters[0]);

void initPlayer(char *VAULT_PATH, char *HERO_NAME) {
  Character player;

  int playerClassInd = choose_class();
  initCharacter(&player, playerClassInd, HERO_NAME);
  write_character_data(&player, VAULT_PATH);
}

int choose_class(void) {
  int index = 0;
  char input;

  while (1) {
    display_ascii(characters[index]);
    printf("\n[Select: s | Next: n | Prev: p | Exit: q]\n");

    input = getchar();
    while (getchar() != '\n');  // Clear input buffer

    if (input == 'n') {
      index = (index + 1) % num_characters;
    } else if (input == 's') {
      break;
    } else if (input == 'p') {
      index = (index - 1 + num_characters) % num_characters;
    } else if (input == 'q') {
      break;
    }
  }

  return index;
}

void initCharacter(Character *character, CharacterClasses chClass,
                   const char *name) {
  character->chClass = chClass;
  strncpy(character->name, name, _SC_LOGIN_NAME_MAX);
  character->level = 1;
  character->experience = 0;

  switch (chClass) {
    case WARRIOR:
      character->hp = 15;
      character->strenght = 10;
      character->perception = 4;
      character->endurance = 7;
      character->charisma = 2;
      character->intelligence = 2;
      character->agility = 5;
      break;
    case WIZARD:
      character->hp = 10;
      character->strenght = 2;
      character->perception = 6;
      character->endurance = 4;
      character->charisma = 5;
      character->intelligence = 10;
      character->agility = 3;
      break;
    case BARD:
      character->hp = 10;
      character->strenght = 2;
      character->perception = 4;
      character->endurance = 3;
      character->charisma = 10;
      character->intelligence = 5;
      character->agility = 6;
      break;
    case SCOUT:
      character->hp = 10;
      character->strenght = 2;
      character->perception = 9;
      character->endurance = 5;
      character->charisma = 3;
      character->intelligence = 6;
      character->agility = 5;
      break;
  }
}

void write_character_data(Character *character, char *VAULT_PATH) {
  char FILENAME[PATH_MAX];

  sprintf(FILENAME, "%s/character.txt", VAULT_PATH);

  FILE *fptr;
  fptr = fopen(FILENAME, "w");

  fprintf(fptr, "Name:%s\n", character->name);
  fprintf(fptr, "HP:%d\n", character->hp);
  fprintf(fptr, "Level:%d\n", character->level);
  fprintf(fptr, "XP:%d\n", character->experience);
  fprintf(fptr, "ST:%d\n", character->strenght);
  fprintf(fptr, "PE:%d\n", character->perception);
  fprintf(fptr, "EN:%d\n", character->endurance);
  fprintf(fptr, "CH:%d\n", character->charisma);
  fprintf(fptr, "IT:%d\n", character->intelligence);
  fprintf(fptr, "AG:%d\n", character->agility);

  fclose(fptr);
}
