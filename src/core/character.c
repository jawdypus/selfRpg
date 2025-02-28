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

#include <stdio.h>

#include "core/ui/cli/message_renderer.h"

const char *characters[] = {"assets/characters/warrior",
                            "assets/characters/wizzard",
                            "assets/characters/bard"};

const int num_characters = sizeof(characters) / sizeof(characters[0]);

void choose_class(void) {
  int index = 0;
  char input;

  while (1) {
    display_ascii(characters[index]);
    printf("\n[Next: n | Prev: p | Exit: q]\n");

    input = getchar();
    while (getchar() != '\n');  // Clear input buffer

    if (input == 'n') {
      index = (index + 1) % num_characters;
    } else if (input == 'p') {
      index = (index - 1 + num_characters) % num_characters;
    } else if (input == 'q') {
      break;
    }
  }
}
