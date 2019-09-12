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
        printf("Power Points Required: %d.\n",
               powerPointsToLevel(target_node->brawler));
        printf("Coins Required: %d.\n",
               coinsToLevel(target_node->brawler));
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
        printf("Power Points Required to Max: %d.\n",
               powerPointsToMax(target_node->brawler));
        printf("Coins Required to Max: %d.\n",
               coinsToMax(target_node->brawler));
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

  // default attribute(s)
  strcpy(brawler_info.name, "blank");
  brawler_info.power_level = 1;
  brawler_info.star_powers = 0;
  brawler_info.power_points = 0;

  /* user supplied attribute(s) */

  // prompt user for brawler name
  printf("Brawler's Name: ");
  readLine(brawler_info.name);

  // prompt user for brawler power level
  do {
    printf("%s's Power Level: ", brawler_info.name);
    scanf("%d", &(brawler_info.power_level));

    // test for correct range of power level
    if(brawler_info.power_level < 1 || brawler_info.power_level > 10) {
      printf("Incorrect Power Level (Range: 1-10)\n");
    }
  }
  while(brawler_info.power_level < 1 || brawler_info.power_level > 10);

  // prompt user for star power(s) if applicable
  if(brawler_info.power_level == 10) {
    do {
      printf("%s's Star Power count: ", brawler_info.name);
      scanf("%d", &(brawler_info.star_powers));

      // test for correct range of star power(s)
      if(brawler_info.star_powers < 0 || brawler_info.star_powers > 2) {
        printf("Incorrect Star Powers (Range: 0-2)\n");
      }
    }
    while(brawler_info.star_powers < 0 || brawler_info.star_powers > 2);
  }
  else {
    // brawler not level 10, test for power points applicability

    int poss_pwr_pts = powerPointsToMax(&brawler_info);

    // prompt brawler for power points to next level
    // this value can be higher than needed for the next level
    if(brawler_info.power_level < 9) {
      do {
        printf("%s's Power Points: ", brawler_info.name);
        scanf("%d", &(brawler_info.power_points));

        // test for correct range of power point(s)
        if(brawler_info.power_points < 0 ||
           brawler_info.power_points > poss_pwr_pts) {
          printf("Incorrect Power Points (Range: 0-%d)\n", poss_pwr_pts);
        }
      }
      while(brawler_info.power_points < 0 ||
            brawler_info.power_points > poss_pwr_pts);
    }
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

  char file_name[80];

  // prompt for file to open
  printf("Save As: ");
  scanf("%s", file_name);

  // create file
  FILE * output_file;

  // open file
  if((output_file = fopen(file_name, "w")) == NULL) {
    fprintf(stderr, "Unable to open '%s'\n", file_name);
    return false;
  }

  // write data to file
  while(iter != NULL) {
    // write brawler name

    fprintf(output_file, "%s", iter->brawler->name);
    fprintf(output_file, ":"); // delimeter

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

  char file_name[80];

  // prompt for file to open
  printf("Open: ");
  scanf("%s", file_name);
  // create file
  FILE * input_file;

  // open file
  if((input_file = fopen(file_name, "r")) == NULL) {
    fprintf(stderr, "Unable to open '%s'.\n", file_name);
    return false;
  }

  // read data into buffer
  char character, * buffer;
  int i;

  do {
    // new buffer to be allocated
    buffer = (char *) malloc(80 * sizeof(char));
    i = 0;

    do {
      // read character
      character = getc(input_file);

      if(character == '\n') {
        // append null character to buffer
        *(buffer + i) = '\0';
      }
      else {
        // append character to buffer
        *(buffer + i) = character;
      }

      // test for read line
      if(*(buffer + i) == '\0') {
        // create brawler with information in buffer
        char temp_name[16], temp_level[16];
        char temp_star[16], temp_points[16];

        // parse brawler attribute(s)
        parseBrawler(buffer, temp_name,
                     temp_level, temp_star, temp_points);

        // create new brawler
        struct brawler_t temp_brawler;

        // set attribute(s)
        strcpy(temp_brawler.name, temp_name);

        // convert strings to integers
        temp_brawler.power_level = atoi(temp_level);
        temp_brawler.star_powers = atoi(temp_star);
        temp_brawler.power_points = atoi(temp_points);

        // append brawler to list
        if(iter == ((struct node *) 0)) {
          iter = createList(iter, temp_brawler);
        }
        else {
          appendNode(iter, temp_brawler);
        }
      }

      // move to next character position
      ++i;
    }
    while(character != '\n' && character != EOF);

    // free buffer
    free(buffer);
  }
  while(character != EOF);

  // close file
  fclose(input_file);

  return iter;
}

void parseBrawler(char * buffer, char * temp_name, char * temp_level,
                  char * temp_star, char * temp_points) {
  /**
   * parseBrawler parses a brawler buffer into its
   * appropriate information using the ':' as the delimeter.
   *
   * @param buffer: Buffer with brawler attribute(s).
   * @param temp_name: Brawler name.
   * @param temp_level: Brawler level.
   * @param temp_star: Brawler Star Power count.
   * @param temp_points: Brawler Power Points.
   */

  char character;
  int i = 0, ii = 0, iii = 0, iv = 0, v = 0;
  int delimeter_count = 0;

  do {
    character = *(buffer + i);

    if(character == ':') {
      ++delimeter_count;
    }

    switch(delimeter_count) {
    case 0: {
      // reading brawler name
      if(character != ':') {
        *(temp_name + ii) = character;
        ++ii;
      }
    }
      break;
    case 1: {
      // reading brawler level
      if(character != ':') {
        *(temp_level + iii) = character;
        ++iii;
      }
    }
      break;
    case 2: {
      // reading brawler star power
      if(character != ':') {
        *(temp_star + iv) = character;
        ++iv;
      }
    }
      break;
    case 3: {
      // reading brawler power points
      if(character != ':') {
        *(temp_points + v) = character;
        ++v;
      }
    }
      break;
    }

    // increment to next character in buffer
    ++i;
  }
  while(character != '\0');

  // append null character(s)
  *(temp_name + ii) = '\0';
  *(temp_level + iii) = '\0';
  *(temp_star + iv) = '\0';
  *(temp_points + v) = '\0';
}

void printMenu(void) {
  /**
   * printMenu displays the context menu.
   */

  printf("########################################\n");
  printf("A: Add a new brawler.\n");
  printf("D: Display brawlers.\n");
  printf("U: Power Points & Coins required to next level.\n");
  printf("M: Power Points & Coins required to max level.\n");
  printf("S: Save added brawlers to a file.\n");
  printf("L: Load brawlers from file.\n");
  printf("Q: Quit program.\n");
  printf("?: Print context menu.\n");
  printf("########################################\n");
}
