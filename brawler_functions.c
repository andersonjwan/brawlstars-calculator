#include <stdio.h>
#include "brawlstars_calculator.h"
#include "brawler_functions.h"

int powerPointsToLevel(struct brawler_t * brawler) {
  /**
   * powerPointsToLevel calculates the total amount
   * of Power Points to upgrade to the next level
   * @param brawler: Pointer to brawler_t structure.
   * @return: Power Points to next level upgrade.
   */

  if(brawler == ((struct brawler_t *) 0)) {
    // list is empty
    return -1;
  }

  int brawler_lvl = brawler->power_level;
  int brawler_pwr_pts = brawler->power_points;
  int rem_pwr_pts;

  switch(brawler_lvl) {
  case 1: {
    rem_pwr_pts = calcPowerPointsRemain(brawler_pwr_pts, 20);
  }
    break;
  case 2: {
    rem_pwr_pts = calcPowerPointsRemain(brawler_pwr_pts, 30);
  }
    break;
  case 3: {
    rem_pwr_pts = calcPowerPointsRemain(brawler_pwr_pts, 50);
  }
    break;
  case 4: {
    rem_pwr_pts = calcPowerPointsRemain(brawler_pwr_pts, 80);
  }
    break;
  case 5: {
    rem_pwr_pts = calcPowerPointsRemain(brawler_pwr_pts, 130);
  }
    break;
  case 6: {
    rem_pwr_pts = calcPowerPointsRemain(brawler_pwr_pts, 210);
  }
    break;
  case 7: {
    rem_pwr_pts = calcPowerPointsRemain(brawler_pwr_pts, 340);
  }
    break;
  case 8: {
    rem_pwr_pts = calcPowerPointsRemain(brawler_pwr_pts, 550);
  }
    break;
  case 9: {
    rem_pwr_pts = calcPowerPointsRemain(brawler_pwr_pts, 0);
  }
    break;
  case 10: {
    rem_pwr_pts = -2; // star power(s) gained level
  }
    break;
  default: {
    return -3;
  }
    break;
  }
}

int calcPowerPointsRemain(int curr_pwr_pts, int req_pwr_pts) {
  /**
   * calcPowerPointsRemain calculates the remaining Power Points
   * for a Brawler to upgrade to the next level based on the
   * given current Power Points and the Power Points goal.
   *
   * @param curr_pwr_pts: Brawler's current obtained Power Points.
   * @param req_pwr_pts: Power Points get to next level.
   * @return: Difference between the two values - zero if current is
   * larger than required.
   */

  if(curr_pwr_pts >= req_pwr_pts) {
    return 0;
  }
  else {
    return (req_pwr_pts - curr_pwr_pts);
  }
}
