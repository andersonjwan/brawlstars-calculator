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
        node_head = createList(node_head, collectBrawlerInfo());
        curr = node_head;
      }
      else {
        curr = appendNode(node_head, collectBrawlerInfo());
      }
    }
      break;
    case 'U': {
      char brawler_name[16];
      struct node * target_node;

      printf("Brawler's Name: ");
      readLine(brawler_name);

      target_node = findBrawler(node_head, brawler_name);

      // test for whether brawler exists
      if(target_node != ((struct node *) 0)) {
        // brawler exists
        printf("%s found...\n", brawler_name);
        printf("Power Points Required: %d.\n",
               powerPointsToLevel(target_node->brawler));
      }
      else {
        // brawler does not exist
        printf("%s does not exists.\n", brawler_name);
      }
    }
      break;
    case 'M': {
      const char brawler_name[16];
      struct node * target_node;

      printf("Brawler's Name: ");
      scanf("%s", brawler_name);

      target_node = findBrawler(node_head, brawler_name);

      // test for whether brawler exists
      if(target_node != ((struct node *) 0)) {
        // brawler exists
        printf("%s found...\n", brawler_name);
        printf("Power Points Required to Max: %d.\n",
               powerPointsToMax(target_node->brawler));
      }
    }
      break;
    case 'D': {
      // display brawler(s)
      printBrawlers(node_head);
    }
      break;
    case 'S': {
      // save brawler(s) and attribute(s) to file
      if(writeBrawlers(node_head)) {
        printf("Brawlers saved successfully.\n");
      }
      else {
        printf("Error. Unable to save brawlers.\n");
      }
    }
      break;
    case 'L': {
      // load brawler(s) and attribute(s) to list
      if((node_head = readBrawlers(node_head))) {
        printf("Brawlers successfully loaded.\n");
      }
      else {
        printf("Brawlers unable to be loaded.\n");
      }
    }
    case '?': {
      printMenu();
    }
      break;
    case 'Q': {
      run = false;
    }
      break;
    default: {
      printf("Unknown option.\n");
    }
      break;
    }
  }

  // free memory
  if(reallocateMem(node_head)) {
    printf("Memory successefully cleared.\n");
  }
  else {
    printf("Memory not clearned. Error.\n");
  }

  return 0;
}

struct node * createList(struct node * iter, struct brawler_t new_brawler) {
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
      node_head->brawler = createBrawler(new_brawler);
      node_head->next = ((struct node *) 0);

      // returns pointer to new node if created successfully
      return node_head;
    }
  }

  return ((struct node *) 0); // fails to create head
}

struct node * appendNode(struct node * iter, struct brawler_t new_brawler) {
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
    new_node->brawler = createBrawler(new_brawler);
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

    // point to next node
    iter = iter->next;
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
  readLine(brawler_info.name);

  // prompt user for brawler power level
  printf("%s's Power Level: ", brawler_info.name);
  scanf("%d", &(brawler_info.power_level));

  // prompt user for star power(s) if applicable
  if(brawler_info.power_level == 10) {
    printf("%s's Star Power count: ", brawler_info.name);
    scanf("%d", &(brawler_info.star_powers));

    // set power points to zero
    brawler_info.power_points = 0;
  }
  else {
    // not level 10 brawler
    brawler_info.star_powers = 0;

    // prompt brawler for power points to next level
    // this value can be higher than needed for the next level
    printf("%s's Power Points: ", brawler_info.name);
    scanf("%d", &(brawler_info.power_points));
  }

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

  // clear the buffer
  while((getchar()) != '\n');

  // create name
  do {
    character = getchar();
    buffer[i] = character;
    ++i;
  }
  while(character != '\n');

  // append null character to create string
  buffer[i - 1] = '\0';
}

bool reallocateMem(struct node * iter) {
  /** reallocateMem re-allocates the memory
   * of the pointers and structures created.
   *
   * @param iter: Pointer to head of list.
   */

  struct node * temp_iter;

  while(iter != NULL) {
    // set temp_iter
    temp_iter = iter;

    // free brawler_t structure
    free(temp_iter->brawler);

    // point to next node
    iter = iter->next;

    // free previous node structure
    free(temp_iter);
  }

  if(iter != NULL) {
    return false;
  }

  return true;
}

void printBrawlers(struct node * iter) {
  /**
   * printBrawlers displays all brawlers in the
   * list.
   *
   * @param node_head: Pointer to beginning of list.
   */

  // line break segment
  printf("--------------------\n");

  if(iter == ((struct node *) 0)) {
    printf("No brawlers added.\n");
  }
  else {
    while(iter != ((struct node *) 0)) {
      printf("Brawler: %s\n", iter->brawler->name);
      printf("Power Level: %d\n", iter->brawler->power_level);
      printf("Star Power(s): %d\n", iter->brawler->star_powers);
      printf("Power Point(s): %d\n", iter->brawler->power_points);
      printf("--------------------\n");

      iter = iter->next;
    }
  }
}

bool writeBrawlers(struct node * iter) {
  /**
   * writeBrawlers writes the brawlers and their
   * associated attributes to a file labeled
   * 'brawlers-info.txt'.
   *
   * @param iter: Pointer to head of list.
   * @return: Writing success/failure.
   */

  // create file
  FILE * output_file;

  // open file
  if((output_file = fopen("brawlers-info.txt", "w")) == NULL) {
    fprintf(stderr, "Unable to open 'brawlers-info.txt'\n");
    return false;
  }

  // write data to file
  while(iter != NULL) {
    // write brawler name
    fprintf(output_file, "%s ", iter->brawler->name);
    // write delimiter
    fprintf(output_file, ":");

    // write brawler power level
    fprintf(output_file, "%d", iter->brawler->power_level);
    fprintf(output_file, ":");

    // write brawler star power count
    fprintf(output_file, "%d", iter->brawler->star_powers);
    fprintf(output_file, ":");

    // write brawler power points
    fprintf(output_file, "%d", iter->brawler->power_points);
    fprintf(output_file, "\n");

    // point to next node
    iter = iter->next;
  }

  // close file
  fclose(output_file);

  return true;
}

struct node * readBrawlers(struct node * iter) {
  /**
   * readBrawlers reads the brawlers and their
   * associated attributes from a file to a list
   *
   * @param iter: Pointer to head of list.
   * @return: Pointer to head of list.
   */

  // create file
  FILE * input_file;

  // open file
  if((input_file = fopen("brawlers-info.txt", "r")) == NULL) {
    fprintf(stderr, "Unable to open 'brawlers-info.txt'. Check that the file exists.\n");
    return false;
  }

  struct brawler_t temp_brawler;

  // read data into list
  while(!feof(input_file)) {
    fscanf(input_file, "%s :%d:%d:%d", temp_brawler.name, &(temp_brawler.power_level),
           &(temp_brawler.star_powers), &(temp_brawler.power_points));

    // create new brawler
    if(iter == ((struct node *) 0)) {
      iter = createList(iter, temp_brawler);
    }
    else {
      appendNode(iter, temp_brawler);
    }
  }

  // close file
  fclose(input_file);

  return iter;
}

void printMenu(void) {
  /**
   * printMenu displays the context menu.
   */

  printf("########################################\n");
  printf("A: Add a new brawler.\n");
  printf("D: Display brawlers.\n");
  printf("U: Power Points required to next level.\n");
  printf("M: Power Points required to max level.\n");
  printf("S: Save added brawlers to a file.\n");
  printf("L: Load brawlers from file.\n");
  printf("Q: Quit program.\n");
  printf("?: Print context menu.\n");
  printf("########################################\n");
}
