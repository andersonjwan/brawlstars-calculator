#ifndef PP_CALC_H
#define PP_CALC_H

/* structure definition(s) */
struct brawler {
  char name[16];
  int level;
  int star_count;
  int power_points;
};

struct node {
  // data element(s)
  struct brawler * brawler_ptr;

  // linking element(s)
  struct node * prev;
  struct node * next;
};

/* forward declaration(s) */
struct node * appendBrawler(struct node *);
bool createBrawler(struct node *);
void printBrawlers(struct node *);
#endif
