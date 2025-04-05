/*
 * =====================================================================================
 *
 *       Filename:  todo.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  04/03/2025 04:37:14 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (),
 *   Organization:
 *
 * =====================================================================================
 */
#ifndef TODO_H
#define TODO_H

typedef struct {
  int priority_flag;
  int due_flag;
  int atrigbute_flag;
} TodoFlags;

void init_todos(const char *VAULT_PATH);
void add_todo(const char *VAULT_PATH, const char *TASK);
void complete_todo(const char *VAULT_PATH, int TASK_ID);
void view_todos(const char *VAULT_PATH);

#endif
