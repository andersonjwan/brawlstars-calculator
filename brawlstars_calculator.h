#ifndef BRAWLSTARS_CALC_H
#define BRAWLSTARS_CALC_H

#define PWR_PTS_LVL_1 0
#define PWR_PTS_LVL_2 20
#define PWR_PTS_LVL_3 30
#define PWR_PTS_LVL_4 50
#define PWR_PTS_LVL_5 80
#define PWR_PTS_LVL_6 130
#define PWR_PTS_LVL_7 210
#define PWR_PTS_LVL_8 340
#define PWR_PTS_LVL_9 550
#define PWR_PTS_LVL_10 0

#include <stdbool.h>

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
struct node * createList(struct node *, struct brawler_t);
struct node * appendNode(struct node *, struct brawler_t);
struct node * findBrawler(struct node *, const char []);
struct brawler_t * createBrawler(struct brawler_t);
struct brawler_t collectBrawlerInfo(void);
bool reallocateMem(struct node * iter);
void readLine(char []);
void printBrawlers(struct node *);
void printMenu(void);
bool writeBrawlers(struct node *);
struct node * readBrawlers(struct node *);
#endif
