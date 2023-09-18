#include <check.h>
#include <stdio.h>

#include "./back/polish/polish.h"
#include "./back/polish/stack.h"
#include "./back/polish/tokenize.h"

#define SUCCESS 0
#define FAIL 1

START_TEST(test_1) {
  char expr[200] =
      "(2 ** cos(asin(sqrt(sin(log(asin(ln(2))))))) * 6 * 1**4 / 9)\0";
  double res = 0;
  int flag = calculate_res(expr, &res);
  ck_assert_int_eq(flag, FAIL);
}
END_TEST

START_TEST(test_2) {
  char expr[200] = "(2 - 1 + atan(10) ** 8**7 - 6)\0";
  double res = 0;
  int flag = calculate_res(expr, &res);
  ck_assert_int_eq(flag, FAIL);
}
END_TEST

START_TEST(test_3) {
  char expr[200] = "(3 ** 10 - acos(sqrt(asin(6))) + 2**7 ** asin(8))\0";
  double res = 0;
  int flag = calculate_res(expr, &res);
  ck_assert_int_eq(flag, FAIL);
}
END_TEST

START_TEST(test_4) {
  char expr[200] = "(sin(5)/2-6/6*7)\0";
  double res = 0;
  int flag = calculate_res(expr, &res);
  ck_assert_int_eq(flag, SUCCESS);
  ck_assert_int_eq(!(fabs(res - (-7.479462137331569)) < 1e-7), SUCCESS);
}
END_TEST

START_TEST(test_5) {
  char expr[200] = "(9 ** 2 - cos(sin(4)) / cos(acos(2))**5 ** sqrt(3))\0";
  double res = 0;
  int flag = calculate_res(expr, &res);
  ck_assert_int_eq(flag, FAIL);
}
END_TEST

START_TEST(test_6) {
  char expr[200] =
      "(atan(ln(1)) / asin(2) - 2 * tan(atan(4))**3 + ln(acos(cos(cos(5)))))\0";
  double res = 0;
  int flag = calculate_res(expr, &res);
  ck_assert_int_eq(flag, FAIL);
}
END_TEST

START_TEST(test_7) {
  char expr[200] = "(6 + sqrt(tan(6)) * 1 * 7**8 * ln(ln(6)))\0";
  double res = 0;
  int flag = calculate_res(expr, &res);
  ck_assert_int_eq(flag, FAIL);
}
END_TEST

START_TEST(test_8) {
  char expr[200] = "(1 - acos(9) / 1 - sin(4)**5 ** 3)\0";
  double res = 0;
  int flag = calculate_res(expr, &res);
  ck_assert_int_eq(flag, FAIL);
}
END_TEST

START_TEST(test_9) {
  char expr[200] = "(10 / 1 ** ln(6) - asin(tan(4))**3 * sqrt(acos(ln(7))))\0";
  double res = 0;
  int flag = calculate_res(expr, &res);
  ck_assert_int_eq(flag, FAIL);
}
END_TEST

START_TEST(test_10) {
  char expr[200] = "(9 / 8 ^(log(5)) - 4^7 / 10)\0";
  double res = 0;
  int flag = calculate_res(expr, &res);
  ck_assert_int_eq(flag, SUCCESS);
  ck_assert_int_eq(!(fabs(res - (-1636.296174584662)) < 1e-7), SUCCESS);
}
END_TEST

START_TEST(test_11) {
  char expr[200] = "(9 - 1 ** 7 * 3**1 / sin(asin(3)))\0";
  double res = 0;
  int flag = calculate_res(expr, &res);
  ck_assert_int_eq(flag, FAIL);
}
END_TEST

START_TEST(test_12) {
  char expr[200] = "(cos(6) ** 8 * atan(10) ** 3**10 / 3)\0";
  double res = 0;
  int flag = calculate_res(expr, &res);
  ck_assert_int_eq(flag, FAIL);
}
END_TEST

START_TEST(test_13) {
  char expr[200] =
      "(cos(atan(atan(cos(cos(1))))) * 8 * 10 + 2**10 - ln(asin(sqrt(4))))\0";
  double res = 0;
  int flag = calculate_res(expr, &res);
  ck_assert_int_eq(flag, FAIL);
}
END_TEST

START_TEST(test_14) {
  char expr[200] =
      "(sin(sqrt(8)) / ln(2) * acos(3) - tan(cos(2))**10 * sin(4))\0";
  double res = 0;
  int flag = calculate_res(expr, &res);
  ck_assert_int_eq(flag, FAIL);
}
END_TEST

START_TEST(test_15) {
  char expr[200] =
      "(acos(ln(3)) ** acos(asin(1)) ** 6 / sqrt(3)**7 - tan(sqrt(atan(4))))\0";
  double res = 0;
  int flag = calculate_res(expr, &res);
  ck_assert_int_eq(flag, FAIL);
}
END_TEST

START_TEST(test_16) {
  char expr[200] = "(4 - 2 + atan(7) - 3^10 + 3)\0";
  double res = 0;
  int flag = calculate_res(expr, &res);
  ck_assert_int_eq(flag, SUCCESS);
  ck_assert_int_eq(!(fabs(res - (-59042.57110072781)) < 1e-7), SUCCESS);
}
END_TEST

START_TEST(test_17) {
  char expr[200] =
      "(asin(2) * 4 - sqrt(1) * asin(cos(sqrt(2)))**7 - atan(4))\0";
  double res = 0;
  int flag = calculate_res(expr, &res);
  ck_assert_int_eq(flag, FAIL);
}
END_TEST

START_TEST(test_18) {
  char expr[200] =
      "(asin(sin(log(1))) + sqrt(4) / asin(acos(1)) - ln(3)**6 + 2)\0";
  double res = 0;
  int flag = calculate_res(expr, &res);
  ck_assert_int_eq(flag, FAIL);
}
END_TEST

START_TEST(test_19) {
  char expr[200] = "(acos(10) + log(log(4)) / log(5) + asin(9)**4 - 5)\0";
  double res = 0;
  int flag = calculate_res(expr, &res);
  ck_assert_int_eq(flag, FAIL);
}
END_TEST

START_TEST(test_20) {
  char expr[200] = "(sin(asin(sqrt(4))) / 5 / 5 + sqrt(ln(sin(5)))**7 * 3)\0";
  double res = 0;
  int flag = calculate_res(expr, &res);
  ck_assert_int_eq(flag, FAIL);
}
END_TEST

START_TEST(test_21) {
  char expr[200] =
      "(sin(asin(sqrt(4))) / 5 / 5 + sqrt(ln(sin(5)))**7 * 3 + "
      "10*18*sin(10))\0";
  double res = 0;
  int flag = calculate_res(expr, &res);
  ck_assert_int_eq(flag, FAIL);
}
END_TEST

START_TEST(test_22) {
  char expr[200] =
      "(asin(3) + atan(ln(6)) ** acos(6) - ln(log(sin(9)))**7 / "
      "asin(log(cos(atan(1)))))\0";
  double res = 0;
  int flag = calculate_res(expr, &res);
  ck_assert_int_eq(flag, FAIL);
}
END_TEST

START_TEST(test_23) {
  char expr[200] = "(2 - tan(2) / sqrt(cos(2)) ** 7**10 / 4)\0";
  double res = 0;
  int flag = calculate_res(expr, &res);
  ck_assert_int_eq(flag, FAIL);
}
END_TEST

START_TEST(test_24) {
  char expr[200] =
      "(sin(atan(4)) + cos(9) * ln(5) ** sqrt(acos(acos(2)))**6 * 5)\0";
  double res = 0;
  int flag = calculate_res(expr, &res);
  ck_assert_int_eq(flag, FAIL);
}
END_TEST

START_TEST(test_25) {
  char expr[200] =
      "(sin(atan(4)) + cos(9) * ln(5) ** sqrt(acos(acos(2)))**6 + 5 mod 10)\0";
  double res = 0;
  int flag = calculate_res(expr, &res);
  ck_assert_int_eq(flag, FAIL);
}
END_TEST

START_TEST(test_26) {
  char expr[200] = "( 10*6^2 + sin(1) + 10 mod 2)\0";
  double res = 0;
  int flag = calculate_res(expr, &res);
  ck_assert_int_eq(flag, SUCCESS);
  ck_assert_int_eq(!(fabs(res - (360.84147)) < 1e-2), SUCCESS);
}
END_TEST

START_TEST(test_27) {
  char expr[200] =
      "(ln(sin(sin(acos(asin(sqrt(1)))))) - atan(asin(ln(6))) ** 5 * "
      "atan(5)**4 / 2)\0";
  double res = 0;
  int flag = calculate_res(expr, &res);
  ck_assert_int_eq(flag, FAIL);
}
END_TEST

START_TEST(test_28) {
  char expr[200] = "(7 ^ 1 / 1 - ln(2)^7 - log(1))\0";
  double res = 0;
  int flag = calculate_res(expr, &res);
  ck_assert_int_eq(flag, SUCCESS);
  ck_assert_int_eq(!(fabs(res - (6.923126221627538)) < 1e-7), SUCCESS);
}
END_TEST

START_TEST(test_29) {
  char expr[200] = "(2 + 3 / tan(10) ** tan(atan(acos(8)))**8 + 2)\0";
  double res = 0;
  int flag = calculate_res(expr, &res);
  ck_assert_int_eq(flag, FAIL);
}
END_TEST

START_TEST(test_30) {
  char expr[200] = "(8 - asin(8) - 1 ** sqrt(5)**5 + atan(acos(acos(3))))\0";
  double res = 0;
  int flag = calculate_res(expr, &res);
  ck_assert_int_eq(flag, FAIL);
}
END_TEST

START_TEST(test_31) {
  char expr[200] = "\0";
  double res = 0;
  int flag = calculate_res(expr, &res);
  ck_assert_int_eq(flag, FAIL);
}
END_TEST

START_TEST(test_32) {
  char expr[200] = "(ln(tanr(6)) * 5 - 5 - 4**3 ** 4)\0";
  double res = 0;
  int flag = calculate_res(expr, &res);
  ck_assert_int_eq(flag, FAIL);
}
END_TEST

START_TEST(test_33) {
  char expr[200] = "(x)\0";
  double res = 0;
  int flag = calculate_res(expr, &res);
  ck_assert_int_eq(flag, SUCCESS);
  ck_assert_int_eq(!(fabs(res - (10)) < 1e-7), SUCCESS);
}
END_TEST

START_TEST(test_34) {
  char expr[200] = "(asin(cos(7)) / 3 * 9 / log(ln(ln(8)))^9 * log(1))\0";
  double res = 0;
  int flag = calculate_res(expr, &res);
  ck_assert_int_eq(flag, SUCCESS);
  ck_assert_int_eq(!(fabs(res - (-0.0)) < 1e-7), SUCCESS);
}
END_TEST

START_TEST(test_35) {
  char expr[200] = "(sqrt(9) ^ (2) + 11 mod 10)\0";
  double res = 0;
  int flag = calculate_res(expr, &res);
  ck_assert_int_eq(flag, SUCCESS);
  ck_assert_int_eq(!(fabs(res - (10)) < 1e-7), SUCCESS);
}
END_TEST

START_TEST(test_36) {
  char expr[200] = "(sin(5) * 9 ^ (sqrt(2)) - cos(log(1))^(7) * acos(1))\0";
  double res = 0;
  int flag = calculate_res(expr, &res);
  ck_assert_int_eq(flag, SUCCESS);
  ck_assert_int_eq(!(fabs(res - (-22.443072370948173)) < 1e-7), SUCCESS);
}
END_TEST

START_TEST(test_37) {
  char expr[200] = "(+5+1)\0";
  double res = 0;
  int flag = calculate_res(expr, &res);
  ck_assert_int_eq(flag, SUCCESS);
  ck_assert_int_eq(!(fabs(res - (6)) < 1e-7), SUCCESS);
}
END_TEST

START_TEST(test_38) {
  char expr[200] = "(log(3) / 6 + 5)\0";
  double res = 0;
  int flag = calculate_res(expr, &res);
  ck_assert_int_eq(flag, SUCCESS);
  ck_assert_int_eq(!(fabs(res - (5.079520209119944)) < 1e-7), SUCCESS);
}
END_TEST

START_TEST(test_39) {
  char expr[200] = "(9 - 4.5 - cos(9)^(8) - tan(1))\0\0";
  double res = 0;
  int flag = calculate_res(expr, &res);
  ck_assert_int_eq(flag, SUCCESS);
  ck_assert_int_eq(!(fabs(res - (2.4676467823691444)) < 1e-7), SUCCESS);
}
END_TEST

START_TEST(test_40) {
  char expr[200] = "(-5-1)\0";
  double res = 0;
  int flag = calculate_res(expr, &res);
  ck_assert_int_eq(flag, SUCCESS);
  ck_assert_int_eq(!(fabs(res - (-6)) < 1e-7), SUCCESS);
}
END_TEST

START_TEST(test_41) {
  char expr[200] = "(sin(9) ** 5 * 5 - asin(5)**10 * 6)\0";
  double res = 0;
  int flag = calculate_res(expr, &res);
  ck_assert_int_eq(flag, FAIL);
}
END_TEST

START_TEST(test_42) {
  char expr[200] =
      "(3 + acos(cos(7)) - cos(7) / log(acos(cos(cos(asin(10)))))**8 + 2)\0";
  double res = 0;
  int flag = calculate_res(expr, &res);
  ck_assert_int_eq(flag, FAIL);
}
END_TEST

START_TEST(test_43) {
  char expr[200] =
      "(atan(sqrt(ln(sqrt(asin(3))))) / acos(cos(tan(6))) * 7 + "
      "acos(sqrt(4))**5 ** 2)\0";
  double res = 0;
  int flag = calculate_res(expr, &res);
  ck_assert_int_eq(flag, FAIL);
}
END_TEST

START_TEST(test_44) {
  char expr[200] =
      "(ln(ln(sqrt(atan(ln(10))))) * 2 + asin(7) * 3**4 / sin(8))\0";
  double res = 0;
  int flag = calculate_res(expr, &res);
  ck_assert_int_eq(flag, FAIL);
}
END_TEST

START_TEST(test_45) {
  char expr[200] =
      "(log(5) ** asin(8) + atan(log(log(ln(5)))) / log(cos(asin(4)))**8 ** "
      "4)\0";
  double res = 0;
  int flag = calculate_res(expr, &res);
  ck_assert_int_eq(flag, FAIL);
}
END_TEST

START_TEST(test_46) {
  char expr[200] = "(acos(acos(ln(4))) * asin(9) + 2 - 8**7 * 9)\0";
  double res = 0;
  int flag = calculate_res(expr, &res);
  ck_assert_int_eq(flag, FAIL);
}
END_TEST

START_TEST(test_47) {
  char expr[200] = "11 mod 10 + 2\0";
  double res = 0;
  int flag = calculate_res(expr, &res);
  ck_assert_int_eq(flag, SUCCESS);
  ck_assert_int_eq(!(fabs(res - (3)) < 1e-7), SUCCESS);
}
END_TEST

START_TEST(test_48) {
  char expr[200] = "(2 * 4 + 9 mod 3)\0";
  double res = 0;
  int flag = calculate_res(expr, &res);
  ck_assert_int_eq(flag, SUCCESS);
  ck_assert_int_eq(!(fabs(res - (8)) < 1e-7), SUCCESS);
}
END_TEST

START_TEST(test_49) {
  char expr[200] = "(cos(5) ** 1 * sqrt(cos(4)) * 4**7 / tan(3))\0";
  double res = 0;
  int flag = calculate_res(expr, &res);
  ck_assert_int_eq(flag, FAIL);
}
END_TEST

START_TEST(test_50) {
  char expr[200] = "(1 - asin(4) / sqrt(9) + 7**4 + 10)\0";
  double res = 0;
  int flag = calculate_res(expr, &res);
  ck_assert_int_eq(flag, FAIL);
}
END_TEST

Suite *test_calc(void) {
  Suite *s = suite_create("\033[45m-=S21_CALC=-\033[0m");
  TCase *tc1_1 = tcase_create("calc");

  suite_add_tcase(s, tc1_1);
  tcase_add_test(tc1_1, test_1);
  tcase_add_test(tc1_1, test_2);
  tcase_add_test(tc1_1, test_3);
  tcase_add_test(tc1_1, test_4);
  tcase_add_test(tc1_1, test_5);
  tcase_add_test(tc1_1, test_6);
  tcase_add_test(tc1_1, test_7);
  tcase_add_test(tc1_1, test_8);
  tcase_add_test(tc1_1, test_9);
  tcase_add_test(tc1_1, test_10);
  tcase_add_test(tc1_1, test_11);
  tcase_add_test(tc1_1, test_12);
  tcase_add_test(tc1_1, test_13);
  tcase_add_test(tc1_1, test_14);
  tcase_add_test(tc1_1, test_15);
  tcase_add_test(tc1_1, test_16);
  tcase_add_test(tc1_1, test_17);
  tcase_add_test(tc1_1, test_18);
  tcase_add_test(tc1_1, test_19);
  tcase_add_test(tc1_1, test_20);
  tcase_add_test(tc1_1, test_21);
  tcase_add_test(tc1_1, test_22);
  tcase_add_test(tc1_1, test_23);
  tcase_add_test(tc1_1, test_24);
  tcase_add_test(tc1_1, test_25);
  tcase_add_test(tc1_1, test_26);
  tcase_add_test(tc1_1, test_27);
  tcase_add_test(tc1_1, test_28);
  tcase_add_test(tc1_1, test_29);
  tcase_add_test(tc1_1, test_30);
  tcase_add_test(tc1_1, test_31);
  tcase_add_test(tc1_1, test_32);
  tcase_add_test(tc1_1, test_33);
  tcase_add_test(tc1_1, test_34);
  tcase_add_test(tc1_1, test_35);
  tcase_add_test(tc1_1, test_36);
  tcase_add_test(tc1_1, test_37);
  tcase_add_test(tc1_1, test_38);
  tcase_add_test(tc1_1, test_39);
  tcase_add_test(tc1_1, test_40);
  tcase_add_test(tc1_1, test_41);
  tcase_add_test(tc1_1, test_42);
  tcase_add_test(tc1_1, test_43);
  tcase_add_test(tc1_1, test_44);
  tcase_add_test(tc1_1, test_45);
  tcase_add_test(tc1_1, test_46);
  tcase_add_test(tc1_1, test_47);
  tcase_add_test(tc1_1, test_48);
  tcase_add_test(tc1_1, test_49);
  tcase_add_test(tc1_1, test_50);

  suite_add_tcase(s, tc1_1);
  return s;
}

int main(void) {
  int failed = 0;
  Suite *s21_calc_test[] = {test_calc(), NULL};

  for (int i = 0; s21_calc_test[i] != NULL; i++) {
    SRunner *sr = srunner_create(s21_calc_test[i]);

    srunner_set_fork_status(sr, CK_NOFORK);
    srunner_run_all(sr, CK_NORMAL);

    failed += srunner_ntests_failed(sr);
    srunner_free(sr);
  }
  printf("========= FAILED: %d =========\n", failed);

  return failed == 0 ? 0 : 1;
}
