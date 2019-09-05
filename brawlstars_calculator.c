#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "brawlstars_calculator.h"
#include "brawler_functions.h"

int main(void) {
  struct node * node_head = ((struct node *) 0), * curr = ((struct node *) 0);
  char choice;
  bool run = true;

  printMenu();

  while(run) {
    // prompt user
    printf(">> ");
    scanf(" %c", &choice);

    switch(choice) {
    case 'A': {
      if(node_head == ((struct node *) 0)) {
        // create list head
        node_head = createList(node_head);
        curr = node_head;
      }
      else {
        curr = appendNode(node_head);
      }
    }
      break;
    case 'U': {
      const char brawler_name[16];
      struct node * target_brawler;

      printf("Brawler's Name: ");
      scanf("%s", brawler_name);

      target_brawler = findBrawler(node_head, brawler_name);

      // test for whether brawler exists
      if(target_brawler != NULL) {
        // brawler exists
        printf("%s found...\n");
        printf("Power Points Required: %d.\n",
               powerPointsToLevel(target_brawler->brawler));
      }
      else {
        // brawler does not exist
        printf("%s does not exists.\n", brawler_name);
      }
    }
      break;
    case 'D': {
      // display brawler(s)
      printBrawlers(node_head);
    }
      break;
    case '?': {
      printMenu();
    }
      break;
    case 'Q': {
      run = false;
    }
      break;
    }
  }
  return 0;
}

struct node * createList(struct node * iter) {
  /**
   * createList creates the first node of the list
   * and returns the pointer to be the head of the
   * list.
   *
   * @param iter: First node, should be NULL.
   * @return: Pointer to head of list.
   */

  // test if the node is the first node created
  if(iter == ((struct node *) 0)) {
    // allocate memory for new node
    struct node * node_head;
    node_head = (struct node *) malloc(sizeof(struct node));

    // test for allocation success/failure
    if(node_head != NULL) {
      // default values of node attribute(s)
      node_head->brawler = createBrawler(collectBrawlerInfo());
      node_head->next = ((struct node *) 0);

      // returns pointer to new node if created successfully
      return node_head;
    }
  }

  return ((struct node *) 0); // fails to create head
}

struct node * appendNode(struct node * iter) {
  /**
   * appendNode inserts a new node at the end of the
   * list.
   *
   * @param iter: node head of list.
   * @return: Pointer to node created.
   */

  // allocate memory for new node
  struct node * new_node;
  new_node = (struct node *) malloc(sizeof(struct node));

  if(new_node != NULL) {
    // default values of node attribute(s)
    new_node->brawler = createBrawler(collectBrawlerInfo());
    new_node->next = ((struct node *) 0);

    // traverse to end of list
    while(iter->next != NULL) {
      iter = iter->next;
    }

    // append to end of list
    iter->next = new_node;
  }

  return new_node;
}

struct node * findBrawler(struct node * iter, const char target_name[]) {
  /**
   * findBrawler searches through the list linearly
   * and returns a pointer to the brawler with a matching
   * string.
   * @param iter: Pointer to head of list.
   * @param target_name: Brawler name to search.
   * @return: Pointer to node with matching name.
   */

  struct node * target = ((struct node *) 0); // set to NULL

  // iterate until brawler found
  while(iter != NULL) {
    if(strcmp(iter->brawler->name, target_name) == 0) {
      target = iter;
      break;
    }
  }

  return target;
}

struct brawler_t * createBrawler(struct brawler_t brawler) {
  /**
   * createBrawler creates a new brawler from the supplied
   * information and returns a pointer to the new brawler.
   *
   * @param brawler: Brawler attributes to be added.
   * @return: Pointer to new brawler.
   */

  // allocate memory for new brawler
  struct brawler_t * new_brawler;
  new_brawler = (struct brawler_t *) malloc(sizeof(struct brawler_t));

  // test for allocation success/failure
  if(new_brawler != NULL) {
    // add attributes supplied
    strcpy(new_brawler->name, brawler.name);
    new_brawler->power_level = brawler.power_level;
    new_brawler->star_powers = brawler.star_powers;
    new_brawler->power_points = brawler.power_points;
  }

  return new_brawler;
}

struct brawler_t collectBrawlerInfo(void) {
  struct brawler_t brawler_info;

  // prompt user for brawler name
  printf("Brawler's Name: ");
  scanf("%s", brawler_info.name);
  //readLine(brawler_info.name);

  // prompt user for brawler power level
  printf("%s's Power Level: ", brawler_info.name);
  scanf("%d", &(brawler_info.power_level));

  // prompt user for star power(s) if applicable
  if(brawler_info.power_level == 10) {
    printf("%s's Star Power count: ", brawler_info.name);
    scanf("%d", &(brawler_info.star_powers));
  }
  else {
    // not level 10 brawler
    brawler_info.star_powers = 0;
  }

  // prompt brawler for power points to next level
  // this value can be higher than needed for the next level
  printf("%s's Power Points: ", brawler_info.name);
  scanf("%d", &(brawler_info.power_points));

  return brawler_info;
}

void readLine(char buffer[]) {
  /**
   * readLine reads a line of characters
   * and stores it into an array.
   *
   * @param buffer: Character array.
   */

  int i = 0;
  char character;

  do {
    character = getchar();
    buffer[i] = character;
    ++i;
  }
  while(character != '\n');

  // append null character to create string
  buffer[i - 1] = '\0';
}

void printBrawlers(struct node * iter) {
  /**
   * printBrawlers displays all brawlers in the
   * list.
   *
   * @param node_head: Pointer to beginning of list.
   */

  if(iter == ((struct node *) 0)) {
    printf("No brawlers added.\n");
  }
  else {
    while(iter != ((struct node *) 0)) {
      printf("Brawler: %s\n", iter->brawler->name);
      printf("Power Level: %d\n", iter->brawler->power_level);
      printf("Star Power(s): %d\n", iter->brawler->star_powers);
      printf("Power Point(s): %d\n", iter->brawler->power_points);
      printf("-----\n");

      iter = iter->next;
    }
  }
}

void printMenu(void) {
  /**
   * printMenu displays the context menu.
   */

  printf("########################################\n");
  printf("A: Add a new brawler.\n");
  printf("D: Display brawlers.\n");
  printf("U: Power Points required to next level.\n");
  printf("Q: Quit program.\n");
  printf("?: Print context menu.\n");
  printf("########################################\n");
}
