#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "brawlstars_calc.h"
#include "brawler_functions.h"

int main(int argc, char * argv[]) {
  struct node * node_h;
  node_h = (struct node *) malloc(sizeof(struct node));

  printMenu();
  appendBrawler(node_h);
  appendBrawler(node_h);
  appendBrawler(node_h);

  printBrawlers(node_h);
  return 0;
}

struct node * appendBrawler(struct node * node_h) {
  /**
   * appendBrawler creates a new brawler with the
   * specified attributes.
   *
   * @param iter: Pointer to beginning of list.
   * @return brawler_node: Pointer to new brawler.
   */

  struct node * iter = node_h;

  // traverse to end of the list
  while(iter != NULL) {
    iter = iter->next;
  }

  // allocate memory for new node
  struct node * new_node;
  new_node = (struct node *) malloc(sizeof(struct node));

  // create new brawler and append to list
  if(new_node != NULL) {
    // successful allocation of memory for new node
    if(createBrawler(new_node)) {
      // append to list
      iter = new_node;
      new_node->prev = NULL;
      new_node->next = NULL;

      return new_node;
    }
  }
  else {
    return iter; // return pointer to end-of-list
  }
}

bool createBrawler(struct node * new_node) {
  /**
   * createBrawler creates a new brawler from the
   * supplied attributes from the user.
   * @param new_node: Pointer to new node to store brawler.
   * @return created: Success/failure of brawler creation.
   */

  bool created;

  // allocate memory for new brawler
  struct brawler * new_brawler;
  new_brawler = (struct brawler *) malloc(sizeof(struct brawler));

  // create brawler's attributes
  if(new_brawler != NULL) {
    // successful allocation of memory for new brawler
    created = true;

    // Brawler's Name
    printf("Brawler's Name: ");
    scanf("%s", new_brawler->name);

    // Power Level
    printf("%s's Power Level: ", new_brawler->name);
    scanf(" %d", &(new_brawler->level));

    // Star Power(s)
    if(new_brawler->level == 10) {
      printf("%s's Star Power Count: ", new_brawler->name);
      scanf("%d", &(new_brawler->star_count));
    }
    else {
      // not high enough level for star power(s)
      new_brawler->star_count = 0;
    }

    // Power Point(s)
    printf("%s's Power Points to next level: ", new_brawler->name);
    scanf("%d", &(new_brawler->power_points));

    // link brawler to node
    new_node->brawler_ptr = new_brawler;
  }
  else {
    created = false;
  }

  return created;
}

void printBrawlers(struct node * node_h) {
  /**
   * printBrawlers displays all brawlers.
   */

  struct node * iter = node_h;

  while(iter != NULL) {
    printf("%s, %d, %d, %d\n", iter->brawler_ptr->name,
           iter->brawler_ptr->level, iter->brawler_ptr->star_count,
           iter->brawler_ptr->power_points);

    // point to next node
    iter = iter->next;
  }
}
