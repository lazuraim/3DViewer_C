#define GL_SILENCE_DEPRECATION
#include "myopenglwidget.h"

MyOpenGLWidget::MyOpenGLWidget(QWidget* parent) : QOpenGLWidget(parent) {
  v = nullptr, f = nullptr;
  num_last_x_move = 0.0, num_last_y_move = 0.0, num_last_z_move = 0.0;
  num_last_x_rot = 0.0, num_last_y_rot = 0.0, num_last_z_rot = 0.0;
  num_last_scale = 1.0;
  max_x = 1.0, min_x = -1.0, max_y = 1.0, min_y = -1.0, max_z = 1.0,
  min_z = -1.0;
  radio = 1;
  stipple = 0, square = 0;
  size_line = 1.0, size_point = 0.0;
  rL = 1, gL = 1, bL = 1;
  rP = 1, gP = 1, bP = 1;
  rB = 0, gB = 0, bB = 0;
  xRot = 0;
  yRot = 0;
  zRot = 0;
  err = 0;
  //  connect( &timerUi, SIGNAL(timeout()), this, SLOT(timeUpdate()));
  //  timerUi.start(one_frame);
}

void MyOpenGLWidget::colorLine(QColor color) {
  rL = color.redF();
  gL = color.greenF();
  bL = color.blueF();
  update();
}

void MyOpenGLWidget::colorPoint(QColor color) {
  rP = color.redF();
  gP = color.greenF();
  bP = color.blueF();
  update();
}


void MyOpenGLWidget::colorBackground(QColor color) {
  rB = color.redF();
  gB = color.greenF();
  bB = color.blueF();
  update();
}

void MyOpenGLWidget::style()  // стили
{
  if (stipple == 1) {
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 10);
  } else if (!stipple)
    glDisable(GL_LINE_STIPPLE);

  if (square == 1)
    glEnable(GL_POINT_SMOOTH);
  else if (!square)
    glDisable(GL_POINT_SMOOTH);

  glLineWidth(size_line);
  glPointSize(size_point);
}

MyOpenGLWidget::~MyOpenGLWidget() {
  if (v) free(v);
  if (f) free(f);
}

void MyOpenGLWidget::initializeGL() {
  initializeOpenGLFunctions();
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
}

void MyOpenGLWidget::paintGL() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(rB, gB, bB, 0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  if (radio)
    projectionCenter();
  else
    projectionParallel();
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glRotatef(xRot, 1.0, 0.0, 0.0);
  glRotatef(yRot, 0.0, 1.0, 0.0);
  glRotatef(zRot, 0.0, 0.0, 1.0);
  paintFigure();
}

void MyOpenGLWidget::resizeGL(int w, int h) {
  glwidth = w;
  glheight = h;
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
}

void MyOpenGLWidget::paintFigure() {
  if (v && f) {
    style();
    glVertexPointer(3, GL_FLOAT, 0, v);
    glEnableClientState(GL_VERTEX_ARRAY);
    glColor3f(rL, gL, bL);
    if (stipple != 2) glDrawElements(GL_LINES, size_f, GL_UNSIGNED_INT, f);
    glColor3f(rP, gP, bP);
    if (square != 2) glDrawArrays(GL_POINTS, 0, size_v / 3);
    glDisableClientState(GL_VERTEX_ARRAY);
  }
}

void MyOpenGLWidget::parcer(QString fileName) {
  QByteArray arr = fileName.toUtf8();
  arr.append('\0');

  err = open_file(arr.data(), &v, &f, &size_v, &size_f);
  s21_centralize(v, size_v);

  if ((!v || !f) && fileName != "")
    QMessageBox::critical(this, tr("Ошибка"),
                          tr("Не удалось открыть файл").arg(fileName));
}

// Управление с помощью мышки
void MyOpenGLWidget::mousePressEvent(QMouseEvent* mo) { mPos = mo->pos(); }

void MyOpenGLWidget::mouseMoveEvent(QMouseEvent* mo) {
  float kx = 0.01;  // коэффициент для замедления вращения модели
  float ky = 0.01;  // коэффициент для замедления вращения модели
  xRot += kx * 180 / (M_PI) * (mo->pos().y() - mPos.y());
  yRot += ky * 180 / (M_PI) * (mo->pos().x() - mPos.x());
  mPos = mo->pos();
  update();
}

/* Центрирование фигуры*/
void MyOpenGLWidget::centerFigure() {
  if (v && f) {
    s21_centralize(v, size_v);
    //    reduction();
  }
  update();
}

/*--- Проекция ---*/

// Центральная
void MyOpenGLWidget::projectionCenter() {
  if (v && f) {
    float fov = 30.0 * M_PI / 180;
    float heapHeight = max_y / (2 * tan(fov / 2));
    glFrustum(min_x, max_x, min_y, max_y, heapHeight, max_z * 100);
    glTranslatef(0, 0, -heapHeight * 3);
  }
  update();
}

// Параллельная
void MyOpenGLWidget::projectionParallel() {
  if (v && f) {
    glOrtho(min_x * 1.5f, max_x * 1.5f, min_y * 1.5f, max_y * 1.5f,
            min_z * 3.5f, max_z * 3.5f);
    glTranslatef(0, 0, -0.5);
  }
  update();
}

/* Значения кнопок */
void MyOpenGLWidget::projection(bool checked) { radio = checked; }
void MyOpenGLWidget::line_type(int check_line) { stipple = check_line; }
void MyOpenGLWidget::line_width(double size) { size_line = size; }
void MyOpenGLWidget::point_size(double size) { size_point = size; }
void MyOpenGLWidget::point_type(int check_point) { square = check_point; }
