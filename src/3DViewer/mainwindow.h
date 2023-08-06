#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "myopenglwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget* parent = nullptr);
  ~MainWindow();

 private slots:

  void on_Open_file_clicked();
  void on_exit_program_clicked();

  void on_SpinBox_Scale_valueChanged(double scale);  // размер объекта

  void on_SpinBox_moveX_valueChanged(double arg1);
  void on_SpinBox_moveY_valueChanged(double arg1);
  void on_SpinBox_moveZ_valueChanged(double arg1);

  std::string findName(QString filePath);  // вычленение имени

  /* Вращение объекта */
  void on_SpinBox_X_rot_valueChanged(int arg1);
  void on_dial_X_rot_valueChanged(int value);
  void on_SpinBox_Y_rot_valueChanged(int arg1);
  void on_dial_Y_rot_valueChanged(int value);
  void on_SpinBox_Z_rot_valueChanged(int arg1);
  void on_dial_Z_rot_valueChanged(int value);

  void on_color_lines_clicked();
  void on_color_background_clicked();
  void on_color_point_clicked();

  void on_radioButton_2_toggled(bool checked);
  void on_radioButton_toggled(bool checked);

  void on_line_clicked();
  void on_dash_line_clicked();
  void on_disable_line_clicked();

  void on_doubleSpinBox_8_valueChanged(double arg1);
  void on_doubleSpinBox_9_valueChanged(double arg1);

  void on_square_clicked();
  void on_circle_clicked();
  void on_vertex_disable_clicked();

  void on_pB_resetParam_clicked();

  void on_pushButton_clicked();

  void start_timer_gif();
  void record_gif();

  void on_pB_GIF_clicked();

 private:
  Ui::MainWindow* ui;

  QString file_name;
  QTimer* timerGIF;  // идентификатор таймера
  int frame;
  QGifImage* gif;
  QFile* ptr_save_file;
};

#endif  // MAINWINDOW_H
