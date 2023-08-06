#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#include <glu.h>
#include <math.h>

#include <QApplication>
#include <QColorDialog>
#include <QDebug>
#include <QDockWidget>
#include <QFileDialog>
#include <QMainWindow>
#include <QMessageBox>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QPushButton>
#include <QTimer>
#include <QWidget>
#include <QtOpenGL>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>

#include "lib/3rdParty/giflib/gif_lib.h"
#include "lib/gifimage/qgifimage.h"

extern "C" {
#include "../s21_3DViewer.h"
}

class MyOpenGLWidget : public QOpenGLWidget, public QOpenGLFunctions {
  Q_OBJECT

 public:
  MyOpenGLWidget(QWidget *parent = nullptr);
  ~MyOpenGLWidget();

  GLfloat *v = nullptr;
  GLuint *f = nullptr;
  int size_v = 0, size_f = 0;
  bool isClicking, radio;
  int stipple, square;
  float size_line, size_point;
  float num_last_scale = 1;
  float num_last_x_move, num_last_y_move, num_last_z_move;
  float num_last_x_rot, num_last_y_rot, num_last_z_rot;

  int xRot, yRot, zRot;
  float one_frame;

  void parcer(QString fileName);

  void projection(bool checked);
  void line_type(int check_line);
  void projectionParallel();
  void projectionCenter();

  void centerFigure();

  void line_width(double size);
  void point_type(int check_point);
  void point_size(double size);
  void style();

  void colorLine(QColor color);  // выбор цвета
  void colorPoint(QColor color);
  void colorBackground(QColor color);

 private slots:
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;
  void paintFigure();

  void mousePressEvent(QMouseEvent *) override;
  void mouseMoveEvent(QMouseEvent *) override;

 private:
  const char *name_file;
  QTimer timerUi;
  float max_x, min_x, max_y, min_y, max_z, min_z;
  GLfloat rL, gL, bL;
  GLfloat rP, gP, bP;
  GLfloat rB, gB, bB;
  QPoint mPos, mDelta;
  int glwidth, glheight, err;
};

#endif  // MYGLWIDGET_H
