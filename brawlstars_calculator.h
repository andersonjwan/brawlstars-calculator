#ifndef BRAWLSTARS_CALC_H
#define BRAWLSTARS_CALC_H

/* structure definition(s) */
struct brawler_t {
  // attribute(s)
  char name[16];
  int power_level;
  int star_powers;
  int power_points;
};

struct node {
  // data
  struct brawler_t * brawler;

  // link(s)
  struct node * next;
};

/* forward declaration(s) */
struct node * createList(struct node *);
struct node * appendNode(struct node *);
struct brawler_t * createBrawler(struct brawler_t);
struct brawler_t collectBrawlerInfo(void);
void readLine(char []);
void printBrawlers(struct node *);
void printMenu(void);
#endif
