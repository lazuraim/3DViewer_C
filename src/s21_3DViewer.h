#ifndef PARSER_H
#define PARSER_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1
#define MIN 0

int writing_data(FILE *file, float **v, unsigned int **f, int size_v);
int read_file(FILE *file, float **v, unsigned int **f, int *size_v,
              int *size_f);
int open_file(const char *name_file, float **v, unsigned int **f, int *size_v,
              int *size_f);

void s21_scale(float *v, int size_v, double scale);
void s21_translate(float *v, int size_v, double value, int coordinate);
void s21_rotate(float *v, int size_v, int angle, char coordinate);

double s21_calculate_center(double min_value, double max_value);
double s21_max_min_value(float *v, int size_v, int coordinate, int comparison);
double s21_max_of_x_y_z(double min_x, double min_y, double min_z, double max_x,
                        double max_y, double max_z);
void s21_centralize(float *v, int size_v);
int check_indices(unsigned int *f, int size_v, int size_f);

#endif  // PARSER_H
