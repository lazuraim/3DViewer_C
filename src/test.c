#include <check.h>
#include <stdbool.h>
#include <stdlib.h>

#include "s21_3DViewer.h"

#define ERR_NONE 0
#define EPS 1e-5f
#define _USE_MATH_DEFINES
#include <math.h>

START_TEST(s21_open_file_1) {
  float *v = NULL;
  unsigned int *f = NULL;
  int size_v = 0;
  int size_f = 0;

  int result = open_file("./obj_files/dog.obj", &v, &f, &size_v, &size_f);
  ck_assert_int_eq(result, 0);
}

START_TEST(s21_open_file_2) {
  float *v = NULL;
  unsigned int *f = NULL;
  int size_v = 0;
  int size_f = 0;

  int result = open_file("./obj_files/no_exist.obj", &v, &f, &size_v, &size_f);
  ck_assert_int_eq(result, 1);
}

START_TEST(s21_open_file_3) {
  float *v = NULL;
  unsigned int *f = NULL;
  int size_v = 0;
  int size_f = 0;

  int result = open_file("./obj_files/cottage.obj", &v, &f, &size_v, &size_f);
  ck_assert_int_eq(result, 0);
}

START_TEST(s21_read_file_1) {
  float *v = NULL;
  unsigned int *f = NULL;
  int size_v = 0;
  int size_f = 0;

  FILE *file = fopen("./obj_files/cottage.obj", "r");
  int result = read_file(file, &v, &f, &size_v, &size_f);
  fclose(file);
  ck_assert_int_eq(result, 0);
}

START_TEST(s21_counting_num_of_v_test_1) {
  FILE *file = fopen("./obj_files/dog.obj", "r");
  float *v = NULL;
  unsigned int *f = NULL;
  int size_v = 0;
  int size_f = 0;

  read_file(file, &v, &f, &size_v, &size_f);

  ck_assert_int_eq(size_v, 12664 * 3);
  fclose(file);
}

START_TEST(s21_counting_num_of_v_test_2) {
  FILE *file = fopen("./obj_files/ball.obj", "r");
  float *v = NULL;
  unsigned int *f = NULL;
  int size_v = 0;
  int size_f = 0;

  read_file(file, &v, &f, &size_v, &size_f);

  ck_assert_int_eq(size_v, 9667 * 3);
  fclose(file);
}

START_TEST(s21_counting_num_of_v_test_3) {
  FILE *file = fopen("./obj_files/car.obj", "r");
  float *v = NULL;
  unsigned int *f = NULL;
  int size_v = 0;
  int size_f = 0;

  read_file(file, &v, &f, &size_v, &size_f);

  ck_assert_int_eq(size_v, 1485 * 3);
  fclose(file);
}

START_TEST(s21_v_test_1) {
  FILE *file = fopen("./obj_files/dog.obj", "r");
  float *v = NULL;
  unsigned int *f = NULL;
  int size_v = 0;
  int size_f = 0;

  read_file(file, &v, &f, &size_v, &size_f);
  ck_assert_float_eq(v[0], -31.1280);
  ck_assert_float_eq(v[1], 1.2403);
  ck_assert_float_eq(v[2], 1.6385);
  ck_assert_float_eq(v[3], 17.0992);
  ck_assert_float_eq(v[4], 2.9942);
  ck_assert_float_eq(v[5], 129.5545);
  fclose(file);
}

START_TEST(s21_v_test_3) {
  FILE *file = fopen("./obj_files/gun.obj", "r");
  float *v = NULL;
  unsigned int *f = NULL;
  int size_v = 0;
  int size_f = 0;

  read_file(file, &v, &f, &size_v, &size_f);
  ck_assert_float_eq(v[0], -1.692615);
  ck_assert_float_eq(v[1], -0.021714);
  ck_assert_float_eq(v[2], -1.219301);
  ck_assert_float_eq(v[3], 7.334266);
  ck_assert_float_eq(v[4], -0.021714);
  ck_assert_float_eq(v[5], -1.219302);
  ck_assert_float_eq(v[3 * 13163], -0.236967);
  ck_assert_float_eq(v[3 * 13163 + 1], 0.112143);
  ck_assert_float_eq(v[3 * 13163 + 2], 0.014873);

  fclose(file);
}

START_TEST(s21_v_test_4) {
  FILE *file = fopen("./obj_files/cube.obj", "r");
  float *v = NULL;
  unsigned int *f = NULL;
  int size_v = 0;
  int size_f = 0;

  read_file(file, &v, &f, &size_v, &size_f);
  ck_assert_float_eq(v[0], 1);
  ck_assert_float_eq(v[1], -1);
  ck_assert_float_eq(v[2], -1);
  ck_assert_float_eq(v[3], 1);
  ck_assert_float_eq(v[4], -1);
  ck_assert_float_eq(v[5], 1);
  ck_assert_float_eq(v[6], -1);
  ck_assert_float_eq(v[7], -1);
  ck_assert_float_eq(v[8], 1);
  ck_assert_float_eq(v[9], -1);
  ck_assert_float_eq(v[10], -1);
  ck_assert_float_eq(v[11], -1);
  ck_assert_float_eq(v[12], 1);
  ck_assert_float_eq(v[13], 1);
  ck_assert_float_eq(v[14], -0.999999);
  ck_assert_float_eq(v[15], 0.999999);
  ck_assert_float_eq(v[16], 1);
  ck_assert_float_eq(v[18], -1);
  ck_assert_float_eq(v[19], 1);
  ck_assert_float_eq(v[20], 1);
  ck_assert_float_eq(v[21], -1);
  ck_assert_float_eq(v[22], 1);
  ck_assert_float_eq(v[23], -1);

  fclose(file);
}

START_TEST(s21_f_test_2) {
  FILE *file = fopen("./obj_files/lamp.obj", "r");
  float *v = NULL;
  unsigned int *f = NULL;
  int size_v = 0;
  int size_f = 0;

  read_file(file, &v, &f, &size_v, &size_f);
  ck_assert_float_eq(f[0], 1668);
  ck_assert_float_eq(f[1], 1691);
  ck_assert_float_eq(f[2], 1691);
  ck_assert_float_eq(f[3], 1690);
  ck_assert_float_eq(f[4], 1690);
  ck_assert_float_eq(f[5], 1668);
  ck_assert_float_eq(f[6], 1687);
  ck_assert_float_eq(f[7], 1691);
  ck_assert_float_eq(f[8], 1691);
  ck_assert_float_eq(f[9], 1686);
  ck_assert_float_eq(f[10], 1686);
  ck_assert_float_eq(f[11], 1687);
  fclose(file);
}

START_TEST(s21_f_test_3) {
  FILE *file = fopen("./obj_files/car.obj", "r");
  float *v = NULL;
  unsigned int *f = NULL;
  int size_v = 0;
  int size_f = 0;

  read_file(file, &v, &f, &size_v, &size_f);
  ck_assert_float_eq(f[0], 4);
  ck_assert_float_eq(f[1], 2);
  ck_assert_float_eq(f[2], 2);
  ck_assert_float_eq(f[3], 0);
  ck_assert_float_eq(f[4], 0);
  ck_assert_float_eq(f[5], 4);
  ck_assert_float_eq(f[6], 4);
  ck_assert_float_eq(f[7], 5);
  ck_assert_float_eq(f[8], 5);
  ck_assert_float_eq(f[9], 3);
  ck_assert_float_eq(f[10], 3);
  ck_assert_float_eq(f[11], 2);
  ck_assert_float_eq(f[12], 2);
  ck_assert_float_eq(f[13], 4);
  fclose(file);
}

START_TEST(s21_f_test_4) {
  FILE *file = fopen("./obj_files/car.obj", "r");
  float *v = NULL;
  unsigned int *f = NULL;
  int size_v = 0;
  int size_f = 0;

  read_file(file, &v, &f, &size_v, &size_f);
  ck_assert_float_eq(f[size_f - 14], 1472);
  ck_assert_float_eq(f[size_f - 13], 1354);
  ck_assert_float_eq(f[size_f - 12], 1354);
  ck_assert_float_eq(f[size_f - 11], 1352);
  ck_assert_float_eq(f[size_f - 10], 1352);
  ck_assert_float_eq(f[size_f - 9], 1471);
  ck_assert_float_eq(f[size_f - 8], 1472);
  ck_assert_float_eq(f[size_f - 7], 1388);
  ck_assert_float_eq(f[size_f - 6], 1388);
  ck_assert_float_eq(f[size_f - 5], 1353);
  ck_assert_float_eq(f[size_f - 4], 1353);
  ck_assert_float_eq(f[size_f - 3], 1354);
  ck_assert_float_eq(f[size_f - 2], 1354);
  ck_assert_float_eq(f[size_f - 1], 1472);
  fclose(file);
}

START_TEST(s21_scale_1) {
  float *v = NULL;
  float *v_buf = NULL;
  unsigned int *f = NULL;
  unsigned int *f_buf = NULL;
  int size_v = 0;
  int size_v_buf = 0;
  int size_f = 0;
  int size_f_buf = 0;

  open_file("./obj_files/car.obj", &v, &f, &size_v, &size_f);
  open_file("./obj_files/car.obj", &v_buf, &f_buf, &size_v_buf, &size_f_buf);
  double scale = 0.1;
  double last_scale = 0;
  s21_scale(v, size_v, scale - last_scale);
  ck_assert_float_eq_tol(v[0], v_buf[0] * (scale - last_scale), 1e-6);
  ck_assert_float_eq_tol(v[1], v_buf[1] * (scale - last_scale), 1e-6);
  ck_assert_float_eq_tol(v[2], v_buf[2] * (scale - last_scale), 1e-6);
  ck_assert_float_eq_tol(v[3], v_buf[3] * (scale - last_scale), 1e-6);
  ck_assert_float_eq_tol(v[4], v_buf[4] * (scale - last_scale), 1e-6);
  ck_assert_float_eq_tol(v[5], v_buf[5] * (scale - last_scale), 1e-6);
  ck_assert_float_eq_tol(v[6], v_buf[6] * (scale - last_scale), 1e-6);
  ck_assert_float_eq_tol(v[7], v_buf[7] * (scale - last_scale), 1e-6);
}

START_TEST(s21_scale_2) {
  float *v = NULL;
  float *v_buf = NULL;
  unsigned int *f = NULL;
  unsigned int *f_buf = NULL;
  int size_v = 0;
  int size_v_buf = 0;
  int size_f = 0;
  int size_f_buf = 0;

  open_file("./obj_files/lamp.obj", &v, &f, &size_v, &size_f);
  open_file("./obj_files/lamp.obj", &v_buf, &f_buf, &size_v_buf, &size_f_buf);
  double scale = 10;
  double last_scale = 1;
  s21_scale(v, size_v, scale - last_scale);
  ck_assert_float_eq_tol(v[0], v_buf[0] * (scale - last_scale), 1e-6);
  ck_assert_float_eq_tol(v[1], v_buf[1] * (scale - last_scale), 1e-6);
  ck_assert_float_eq_tol(v[2], v_buf[2] * (scale - last_scale), 1e-6);
  ck_assert_float_eq_tol(v[3], v_buf[3] * (scale - last_scale), 1e-6);
  ck_assert_float_eq_tol(v[4], v_buf[4] * (scale - last_scale), 1e-6);
  ck_assert_float_eq_tol(v[5], v_buf[5] * (scale - last_scale), 1e-6);
  ck_assert_float_eq_tol(v[6], v_buf[6] * (scale - last_scale), 1e-6);
  ck_assert_float_eq_tol(v[7], v_buf[7] * (scale - last_scale), 1e-6);
}

START_TEST(s21_scale_3) {
  float *v = NULL;
  float *v_buf = NULL;
  unsigned int *f = NULL;
  unsigned int *f_buf = NULL;
  int size_v = 0;
  int size_v_buf = 0;
  int size_f = 0;
  int size_f_buf = 0;

  open_file("./obj_files/lamp.obj", &v, &f, &size_v, &size_f);
  open_file("./obj_files/lamp.obj", &v_buf, &f_buf, &size_v_buf, &size_f_buf);
  double scale = 0.1;
  double last_scale = 0.1;
  s21_scale(v, size_v, scale - last_scale);
  ck_assert_float_eq_tol(v[0], v_buf[0], 1e-6);
  ck_assert_float_eq_tol(v[1], v_buf[1], 1e-6);
  ck_assert_float_eq_tol(v[2], v_buf[2], 1e-6);
  ck_assert_float_eq_tol(v[3], v_buf[3], 1e-6);
  ck_assert_float_eq_tol(v[4], v_buf[4], 1e-6);
  ck_assert_float_eq_tol(v[5], v_buf[5], 1e-6);
  ck_assert_float_eq_tol(v[6], v_buf[6], 1e-6);
  ck_assert_float_eq_tol(v[7], v_buf[7], 1e-6);
}

START_TEST(s21_translate_1) {
  float *v = NULL;
  float *v_buf = NULL;
  unsigned int *f = NULL;
  unsigned int *f_buf = NULL;
  int size_v = 0;
  int size_v_buf = 0;
  int size_f = 0;
  int size_f_buf = 0;

  open_file("./obj_files/lamp.obj", &v, &f, &size_v, &size_f);
  open_file("./obj_files/lamp.obj", &v_buf, &f_buf, &size_v_buf, &size_f_buf);
  double value = 0.5;
  double last_value = 0;
  s21_translate(v, size_v, value - last_value, 0);
  ck_assert_float_eq_tol(v[0], v_buf[0] + value - last_value, 1e-6);
  ck_assert_float_eq_tol(v[1], v_buf[1], 1e-6);
  ck_assert_float_eq_tol(v[2], v_buf[2], 1e-6);
  ck_assert_float_eq_tol(v[3], v_buf[3] + value - last_value, 1e-6);
  ck_assert_float_eq_tol(v[4], v_buf[4], 1e-6);
  ck_assert_float_eq_tol(v[5], v_buf[5], 1e-6);
  ck_assert_float_eq_tol(v[6], v_buf[6] + value - last_value, 1e-6);
  ck_assert_float_eq_tol(v[7], v_buf[7], 1e-6);
}

START_TEST(s21_translate_2) {
  float *v = NULL;
  float *v_buf = NULL;
  unsigned int *f = NULL;
  unsigned int *f_buf = NULL;
  int size_v = 0;
  int size_v_buf = 0;
  int size_f = 0;
  int size_f_buf = 0;

  open_file("./obj_files/lamp.obj", &v, &f, &size_v, &size_f);
  open_file("./obj_files/lamp.obj", &v_buf, &f_buf, &size_v_buf, &size_f_buf);
  double value = 0.5;
  double last_value = 0;
  s21_translate(v, size_v, value - last_value, 1);
  ck_assert_float_eq_tol(v[0], v_buf[0], 1e-6);
  ck_assert_float_eq_tol(v[1], v_buf[1] + value - last_value, 1e-6);
  ck_assert_float_eq_tol(v[2], v_buf[2], 1e-6);
  ck_assert_float_eq_tol(v[3], v_buf[3], 1e-6);
  ck_assert_float_eq_tol(v[4], v_buf[4] + value - last_value, 1e-6);
  ck_assert_float_eq_tol(v[5], v_buf[5], 1e-6);
  ck_assert_float_eq_tol(v[6], v_buf[6], 1e-6);
  ck_assert_float_eq_tol(v[7], v_buf[7] + value - last_value, 1e-6);
}

START_TEST(s21_translate_3) {
  float *v = NULL;
  float *v_buf = NULL;
  unsigned int *f = NULL;
  unsigned int *f_buf = NULL;
  int size_v = 0;
  int size_v_buf = 0;
  int size_f = 0;
  int size_f_buf = 0;

  open_file("./obj_files/lamp.obj", &v, &f, &size_v, &size_f);
  open_file("./obj_files/lamp.obj", &v_buf, &f_buf, &size_v_buf, &size_f_buf);
  double value = 0.7;
  double last_value = 0;
  s21_translate(v, size_v, value - last_value, 2);
  ck_assert_float_eq_tol(v[0], v_buf[0], 1e-6);
  ck_assert_float_eq_tol(v[1], v_buf[1], 1e-6);
  ck_assert_float_eq_tol(v[2], v_buf[2] + value - last_value, 1e-6);
  ck_assert_float_eq_tol(v[3], v_buf[3], 1e-6);
  ck_assert_float_eq_tol(v[4], v_buf[4], 1e-6);
  ck_assert_float_eq_tol(v[5], v_buf[5] + value - last_value, 1e-6);
  ck_assert_float_eq_tol(v[6], v_buf[6], 1e-6);
  ck_assert_float_eq_tol(v[7], v_buf[7], 1e-6);
}

START_TEST(s21_max_min_value_test_1) {
  int size_v = 12;
  float v[size_v];
  int coordinate = 0;  // x
  int comparison = 0;  // min

  v[0] = 0.000000;  // x
  v[1] = 8.407028;
  v[2] = 0.000000;
  v[3] = 0.000000;  // x
  v[4] = 8.380042;
  v[5] = -0.204985;
  v[6] = 0.053054;  // x
  v[7] = 8.380042;
  v[8] = -0.198000;
  v[9] = 0.102492;  // x
  v[10] = 8.380042;
  v[11] = -0.177522;

  ck_assert_float_eq_tol(
      v[0], s21_max_min_value(v, size_v, coordinate, comparison), 1e-6);
}

START_TEST(s21_max_min_value_test_2) {
  int size_v = 12;
  float v[size_v];
  int coordinate = 0;  // x
  int comparison = 1;  // max

  v[0] = 0.000000;  // x
  v[1] = 8.407028;
  v[2] = 0.000000;
  v[3] = 0.000000;  // x
  v[4] = 8.380042;
  v[5] = -0.204985;
  v[6] = 0.053054;  // x
  v[7] = 8.380042;
  v[8] = -0.198000;
  v[9] = 0.102492;  // x
  v[10] = 8.380042;
  v[11] = -0.177522;

  ck_assert_float_eq_tol(
      v[9], s21_max_min_value(v, size_v, coordinate, comparison), 1e-6);
}

START_TEST(s21_max_min_value_test_3) {
  int size_v = 12;
  float v[size_v];
  int coordinate = 1;  // y
  int comparison = 0;  // min

  v[0] = 0.000000;
  v[1] = 8.407028;  // y
  v[2] = 0.000000;
  v[3] = 0.000000;
  v[4] = 8.380042;  // y
  v[5] = -0.204985;
  v[6] = 0.053054;
  v[7] = 8.380042;  // y
  v[8] = -0.198000;
  v[9] = 0.102492;
  v[10] = 8.380042;  // y
  v[11] = -0.177522;

  ck_assert_float_eq_tol(
      v[4], s21_max_min_value(v, size_v, coordinate, comparison), 1e-6);
}

START_TEST(s21_max_min_value_test_4) {
  int size_v = 12;
  float v[size_v];
  int coordinate = 1;  // y
  int comparison = 1;  // max

  v[0] = 0.000000;
  v[1] = 8.407028;  // y
  v[2] = 0.000000;
  v[3] = 0.000000;
  v[4] = 8.380042;  // y
  v[5] = -0.204985;
  v[6] = 0.053054;
  v[7] = 8.380042;  // y
  v[8] = -0.198000;
  v[9] = 0.102492;
  v[10] = 8.380042;  // y
  v[11] = -0.177522;

  ck_assert_float_eq_tol(
      v[1], s21_max_min_value(v, size_v, coordinate, comparison), 1e-6);
}

START_TEST(s21_max_min_value_test_5) {
  int size_v = 12;
  float v[size_v];
  int coordinate = 2;  // z
  int comparison = 0;  // min

  v[0] = 0.000000;
  v[1] = 8.407028;
  v[2] = 0.000000;  // z
  v[3] = 0.000000;
  v[4] = 8.380042;
  v[5] = -0.204985;  // z
  v[6] = 0.053054;
  v[7] = 8.380042;
  v[8] = -0.198000;  // z
  v[9] = 0.102492;
  v[10] = 8.380042;
  v[11] = -0.177522;  // z

  ck_assert_float_eq_tol(
      v[5], s21_max_min_value(v, size_v, coordinate, comparison), 1e-6);
}

START_TEST(s21_max_of_x_y_z_test_1) {
  double min_x = 0.000000;
  double min_y = 8.380042;
  double min_z = -0.204985;
  double max_x = 0.102492;
  double max_y = 8.407028;
  double max_z = 0.000000;

  ck_assert_float_eq_tol(
      0.204985, s21_max_of_x_y_z(min_x, min_y, min_z, max_x, max_y, max_z),
      1e-6);
}

START_TEST(s21_max_of_x_y_z_test_2) {
  double min_x = 1000;
  double min_y = 100;
  double min_z = 10;
  double max_x = 10;
  double max_y = 100;
  double max_z = 1000;

  ck_assert_float_eq_tol(
      990, s21_max_of_x_y_z(min_x, min_y, min_z, max_x, max_y, max_z), 1e-6);
}

START_TEST(s21_max_of_x_y_z_test_3) {
  double min_x = 1000;
  double min_y = 100;
  double min_z = 10;
  double max_x = 100000;
  double max_y = 100;
  double max_z = 1000;

  ck_assert_float_eq_tol(
      99000, s21_max_of_x_y_z(min_x, min_y, min_z, max_x, max_y, max_z), 1e-6);
}

START_TEST(s21_calculate_center_test_1) {
  double min_value = 100;
  double max_value = 900;

  ck_assert_float_eq_tol(500, s21_calculate_center(min_value, max_value), 1e-6);
}

START_TEST(s21_calculate_center_test_2) {
  double min_value = 0;
  double max_value = 100;

  ck_assert_float_eq_tol(50, s21_calculate_center(min_value, max_value), 1e-6);
}

START_TEST(s21_centralize_test_1) {
  int size_v = 12;
  float v[size_v];

  v[0] = 0.000000;
  v[1] = 8.407028;
  v[2] = 0.000000;  // z
  v[3] = 0.000000;
  v[4] = 8.380042;
  v[5] = -0.204985;  // z
  v[6] = 0.053054;
  v[7] = 8.380042;
  v[8] = -0.198000;  // z
  v[9] = 0.102492;
  v[10] = 8.380042;
  v[11] = -0.177522;  // z

  double min_x = s21_max_min_value(v, size_v, 0, MIN);
  double min_y = s21_max_min_value(v, size_v, 1, MIN);
  double min_z = s21_max_min_value(v, size_v, 2, MIN);

  double max_x = s21_max_min_value(v, size_v, 0, MAX);
  double max_y = s21_max_min_value(v, size_v, 1, MAX);
  double max_z = s21_max_min_value(v, size_v, 2, MAX);

  double scale = s21_max_of_x_y_z(min_x, min_y, min_z, max_x, max_y, max_z);

  double v_0 = (v[0] - s21_calculate_center(min_x, max_x)) / scale;
  double v_1 = (v[1] - s21_calculate_center(min_y, max_y)) / scale;
  double v_2 = (v[2] - s21_calculate_center(min_z, max_z)) / scale;  // z
  double v_3 = (v[3] - s21_calculate_center(min_x, max_x)) / scale;
  double v_4 = (v[4] - s21_calculate_center(min_y, max_y)) / scale;
  double v_5 = (v[5] - s21_calculate_center(min_z, max_z)) / scale;  // z
  double v_6 = (v[6] - s21_calculate_center(min_x, max_x)) / scale;
  double v_7 = (v[7] - s21_calculate_center(min_y, max_y)) / scale;
  double v_8 = (v[8] - s21_calculate_center(min_z, max_z)) / scale;  // z
  double v_9 = (v[9] - s21_calculate_center(min_x, max_x)) / scale;
  double v_10 = (v[10] - s21_calculate_center(min_y, max_y)) / scale;
  double v_11 = (v[11] - s21_calculate_center(min_z, max_z)) / scale;

  s21_centralize(v, size_v);

  ck_assert_float_eq_tol(v[0], v_0, 1e-6);
  ck_assert_float_eq_tol(v[1], v_1, 1e-6);
  ck_assert_float_eq_tol(v[2], v_2, 1e-6);
  ck_assert_float_eq_tol(v[3], v_3, 1e-6);
  ck_assert_float_eq_tol(v[4], v_4, 1e-6);
  ck_assert_float_eq_tol(v[5], v_5, 1e-6);
  ck_assert_float_eq_tol(v[6], v_6, 1e-6);
  ck_assert_float_eq_tol(v[7], v_7, 1e-6);
  ck_assert_float_eq_tol(v[8], v_8, 1e-6);
  ck_assert_float_eq_tol(v[9], v_9, 1e-6);
  ck_assert_float_eq_tol(v[10], v_10, 1e-6);
  ck_assert_float_eq_tol(v[11], v_11, 1e-6);
}

// test mamiemal

START_TEST(load_test_1) {
  int size_v = 0;
  int size_f = 0;

  float *v = NULL;
  unsigned int *f = NULL;

  int err = open_file("./obj_files/cube.obj", &v, &f, &size_v, &size_f);

  ck_assert_int_eq(err, ERR_NONE);

  ck_assert_ptr_ne(v, NULL);
  ck_assert_ptr_ne(f, NULL);
  ck_assert_int_eq(size_v, 24);
  ck_assert_int_eq(size_f, 72);
  float test_v[] = {1.0, -1.0,     -1.0, 1.0,  -1.0, 1.0,  -1.0,      -1.0,
                    1.0, -1.0,     -1.0, -1.0, 1.0,  1.0,  -0.999999, 0.999999,
                    1.0, 1.000001, -1.0, 1.0,  1.0,  -1.0, 1.0,       -1.0};
  unsigned int test_f[] = {
      1, 2, 2, 3, 3, 1, 7, 6, 6, 5, 5, 7, 4, 5, 5, 1, 1, 4, 5, 6, 6, 2, 2, 5,
      2, 6, 6, 7, 7, 2, 0, 3, 3, 7, 7, 0, 0, 1, 1, 3, 3, 0, 4, 7, 7, 5, 5, 4,
      0, 4, 4, 1, 1, 0, 1, 5, 5, 2, 2, 1, 3, 2, 2, 7, 7, 3, 4, 0, 0, 7, 7, 4};
  for (int i = 0; i < 24; i++) ck_assert_float_eq_tol(v[i], test_v[i], EPS);

  for (int j = 0; j < 72; j++) ck_assert_float_eq_tol(f[j], test_f[j], EPS);

  if (v != NULL) free(v);
  if (f != NULL) free(f);
}
END_TEST

START_TEST(load_test_2) {
  int size_v = 0, size_f = 0;
  float *v = NULL;
  unsigned int *f = NULL;
  int err = open_file("./obj_files/Ball_OBJ.obj", &v, &f, &size_v, &size_f);

  ck_assert_int_eq(err, ERR_NONE);
  ck_assert_int_eq(size_v, 46986);
  ck_assert_int_eq(size_f, 182520);

  if (v != NULL) free(v);
  if (f != NULL) free(f);
}
END_TEST

int main() {
  int nf;
  Suite *s1 = suite_create("Core");
  TCase *tc1_1 = tcase_create("Core");
  SRunner *sr = srunner_create(s1);

  suite_add_tcase(s1, tc1_1);
  tcase_add_test(tc1_1, s21_open_file_1);
  tcase_add_test(tc1_1, s21_open_file_2);
  tcase_add_test(tc1_1, s21_open_file_3);
  tcase_add_test(tc1_1, s21_read_file_1);
  tcase_add_test(tc1_1, s21_counting_num_of_v_test_1);
  tcase_add_test(tc1_1, s21_counting_num_of_v_test_2);
  tcase_add_test(tc1_1, s21_counting_num_of_v_test_3);
  tcase_add_test(tc1_1, s21_v_test_1);
  tcase_add_test(tc1_1, s21_v_test_3);
  tcase_add_test(tc1_1, s21_v_test_4);
  tcase_add_test(tc1_1, s21_f_test_2);
  tcase_add_test(tc1_1, s21_f_test_3);
  tcase_add_test(tc1_1, s21_f_test_4);
  tcase_add_test(tc1_1, s21_scale_1);
  tcase_add_test(tc1_1, s21_scale_2);
  tcase_add_test(tc1_1, s21_scale_3);
  tcase_add_test(tc1_1, s21_translate_1);
  tcase_add_test(tc1_1, s21_translate_2);
  tcase_add_test(tc1_1, s21_translate_3);

  tcase_add_test(tc1_1, s21_max_min_value_test_1);
  tcase_add_test(tc1_1, s21_max_min_value_test_2);
  tcase_add_test(tc1_1, s21_max_min_value_test_3);
  tcase_add_test(tc1_1, s21_max_min_value_test_4);
  tcase_add_test(tc1_1, s21_max_min_value_test_5);
  tcase_add_test(tc1_1, s21_max_of_x_y_z_test_1);
  tcase_add_test(tc1_1, s21_max_of_x_y_z_test_2);
  tcase_add_test(tc1_1, s21_max_of_x_y_z_test_3);
  tcase_add_test(tc1_1, s21_calculate_center_test_1);
  tcase_add_test(tc1_1, s21_calculate_center_test_2);
  tcase_add_test(tc1_1, s21_centralize_test_1);

  // test_mamiemal

  tcase_add_test(tc1_1, load_test_1);
  tcase_add_test(tc1_1, load_test_2);

  srunner_run_all(sr, CK_ENV);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);

  return nf == 0 ? 0 : 1;
}
