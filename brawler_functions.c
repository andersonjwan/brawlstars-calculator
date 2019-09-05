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
    rem_pwr_pts = calcPowerPointsRemain(brawler_pwr_pts, PWR_PTS_LVL_2);
  }
    break;
  case 2: {
    rem_pwr_pts = calcPowerPointsRemain(brawler_pwr_pts, PWR_PTS_LVL_3);
  }
    break;
  case 3: {
    rem_pwr_pts = calcPowerPointsRemain(brawler_pwr_pts, PWR_PTS_LVL_4);
  }
    break;
  case 4: {
    rem_pwr_pts = calcPowerPointsRemain(brawler_pwr_pts, PWR_PTS_LVL_5);
  }
    break;
  case 5: {
    rem_pwr_pts = calcPowerPointsRemain(brawler_pwr_pts, PWR_PTS_LVL_6);
  }
    break;
  case 6: {
    rem_pwr_pts = calcPowerPointsRemain(brawler_pwr_pts, PWR_PTS_LVL_7);
  }
    break;
  case 7: {
    rem_pwr_pts = calcPowerPointsRemain(brawler_pwr_pts, PWR_PTS_LVL_8);
  }
    break;
  case 8: {
    rem_pwr_pts = calcPowerPointsRemain(brawler_pwr_pts, PWR_PTS_LVL_9);
  }
    break;
  case 9: {
    rem_pwr_pts = calcPowerPointsRemain(brawler_pwr_pts, PWR_PTS_LVL_10);
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

int powerPointsToMax(struct brawler_t * brawler) {
  /**
   * powerPointsToMax calculates the amount of Power Points
   * required to reach the max level of a brawler through
   * Power Points - level 9.
   *
   * @param brawler: Brawler structure in observation.
   * @return: Power Points to level 9.
   */

  return (calcPowerPointsCurr(brawler->power_points, brawler->power_level) -
          calcPowerPointsCurr(PWR_PTS_LVL_10, 10));
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

int calcPowerPointsCurr(int brawler_pwr_pts, int brawler_lvl) {
  /**
   * calcPowerPointsCurr calculates the total
   * accumulated Power Points of a brawler based on its
   * level and unspent Power Points.
   *
   * @param brawler_pwr_pts: Brawler's unspent Point Points.
   * @param brawler_lvl: Brawler's level.
   * @return: Total power points accumulated.
   */

  int power_points_sum = 0;

  switch(brawler_lvl) {
  case 1:
    power_points_sum += PWR_PTS_LVL_1;
  case 2:
    power_points_sum += PWR_PTS_LVL_2;
  case 3:
    power_points_sum += PWR_PTS_LVL_3;
  case 4:
    power_points_sum += PWR_PTS_LVL_4;
  case 5:
    power_points_sum += PWR_PTS_LVL_5;
  case 6:
    power_points_sum += PWR_PTS_LVL_6;
  case 7:
    power_points_sum += PWR_PTS_LVL_7;
  case 8:
    power_points_sum += PWR_PTS_LVL_8;
  case 9:
    power_points_sum += PWR_PTS_LVL_9;
  case 10:
    power_points_sum += PWR_PTS_LVL_10;
  default:
    power_points_sum += brawler_pwr_pts;
  }

  return power_points_sum;
}

int calcPotentialLevel(int brawler_pwr_pts, int brawler_lvl) {
  /**
   * calcPotentialLevel calculates the potential level
   * that the Brawler could be assuming all Power Points were
   * spent to upgrade.
   * @param brawler_pwr_pts: Brawler's unspent Power Points.
   * @param brawler_lvl: Brawler's Power level.
   * @return: Brawler's potential level.
   */

  int curr_pwr_pts = calcPowerPointsCurr(brawler_pwr_pts, brawler_lvl);
  int potential_level;

  // highest level to smallest level
  if(curr_pwr_pts >= calcPowerPointsCurr(PWR_PTS_LVL_10, 10)) {
    potential_level = 10;
  }
  else if(curr_pwr_pts >= calcPowerPointsCurr(PWR_PTS_LVL_9, 9)) {
    potential_level = 9;
  }
  else if(curr_pwr_pts >= calcPowerPointsCurr(PWR_PTS_LVL_9, 8)) {
    potential_level = 8;
  }
  else if(curr_pwr_pts >= calcPowerPointsCurr(PWR_PTS_LVL_7, 7)) {
    potential_level = 7;
  }
  else if(curr_pwr_pts >= calcPowerPointsCurr(PWR_PTS_LVL_6, 6)) {
    potential_level = 6;
  }
  else if(curr_pwr_pts >= calcPowerPointsCurr(PWR_PTS_LVL_5, 5)) {
    potential_level = 5;
  }
  else if(curr_pwr_pts >= calcPowerPointsCurr(PWR_PTS_LVL_4, 4)) {
    potential_level = 4;
  }
  else if(curr_pwr_pts >= calcPowerPointsCurr(PWR_PTS_LVL_3, 3)) {
    potential_level = 3;
  }
  else if(curr_pwr_pts >= calcPowerPointsCurr(PWR_PTS_LVL_2, 2)) {
    potential_level = 2;
  }
  else {
    potential_level = 1;
  }

  return potential_level;
}
