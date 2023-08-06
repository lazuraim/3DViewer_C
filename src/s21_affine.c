#include "s21_3DViewer.h"

double s21_max_min_value(float *v, int size_v, int coordinate, int comparison) {
  double max = v[coordinate];
  double min = v[coordinate];
  for (int i = coordinate; i < size_v; i += 3) {
    if (v[i] > max) {
      max = v[i];
    }
    if (v[i] < min) {
      min = v[i];
    }
  }
  return comparison ? max : min;
}

void s21_centralize(float *v, int size_v) {
  double min_x = s21_max_min_value(v, size_v, 0, MIN);
  double min_y = s21_max_min_value(v, size_v, 1, MIN);
  double min_z = s21_max_min_value(v, size_v, 2, MIN);

  double max_x = s21_max_min_value(v, size_v, 0, MAX);
  double max_y = s21_max_min_value(v, size_v, 1, MAX);
  double max_z = s21_max_min_value(v, size_v, 2, MAX);

  double scale = s21_max_of_x_y_z(min_x, min_y, min_z, max_x, max_y, max_z);

  for (int i = 0; i < size_v; i += 3) {
    v[i] -= s21_calculate_center(min_x, max_x);
    v[i + 1] -= s21_calculate_center(min_y, max_y);
    v[i + 2] -= s21_calculate_center(min_z, max_z);

    v[i] /= scale;
    v[i + 1] /= scale;
    v[i + 2] /= scale;
  }
}

double s21_calculate_center(double min_value, double max_value) {
  return min_value + (max_value - min_value) / 2.0;
}

double s21_max_of_x_y_z(double min_x, double min_y, double min_z, double max_x,
                        double max_y, double max_z) {
  double x = max_x - min_x;
  double y = max_y - min_y;
  double z = max_z - min_z;

  double max_value = x;
  if (y >= x && y >= z) {
    max_value = y;
  } else if (z >= x && z >= y) {
    max_value = z;
  }
  return max_value;
}

void s21_scale(float *v, int size_v, double scale) {
  if (scale != 0.0) {
    for (int i = 0; i < size_v; i++) {
      v[i] *= scale;
    }
  }
}

void s21_translate(float *v, int size_v, double value, int coordinate) {
  for (int i = coordinate; i < size_v; i += 3) {
    v[i] += value;
  }
}

void s21_rotate(float *v, int size_v, int angle, char coordinate) {
  double rad = angle * M_PI / 180;
  double sin_t = sin(rad);
  double cos_t = cos(rad);
  float buf_x = 0, buf_y = 0, buf_z = 0;
  for (int i = 0; i < size_v; i += 3) {
    buf_x = v[i];
    buf_y = v[i + 1];
    buf_z = v[i + 2];
    if (coordinate == 'x') {
      v[i + 1] = buf_y * cos_t + buf_z * (-sin_t);
      v[i + 2] = buf_y * sin_t + buf_z * cos_t;
    } else if (coordinate == 'y') {
      v[i] = buf_x * cos_t + buf_z * sin_t;
      v[i + 2] = buf_x * (-sin_t) + buf_z * cos_t;
    } else if (coordinate == 'z') {
      v[i] = buf_x * cos_t + buf_y * (-sin_t);
      v[i + 1] = buf_x * sin_t + buf_y * cos_t;
    }
  }
}
