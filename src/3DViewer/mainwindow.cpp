
#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_Open_file_clicked() {
  QString fileDialog = QFileDialog::getOpenFileName(
      this, QDir::homePath(), tr("Object Files (*.obj);;All Files (*)"),
      tr("Object Files (*.obj)"));
  ui->openGLWidget->parcer(fileDialog);
  if (fileDialog != "") ui->filename->setText(fileDialog);
  QString fileName = QString::fromStdString(findName(fileDialog));
  ui->Name->setText(fileName);
  ui->num_of_vertices->setText(QString::number(ui->openGLWidget->size_v / 3));
  ui->num_of_facets->setText(QString::number(ui->openGLWidget->size_f / 2));
}

std::string MainWindow::findName(
    QString filePath)  // вычленение имени файла из пути
{
  std::string utf8_text = filePath.toUtf8().constData();
  std::string file = utf8_text.substr(utf8_text.rfind('/') + 1);
  return file;
}

void MainWindow::on_SpinBox_Scale_valueChanged(double arg1) {
  ui->SpinBox_Scale->setMinimum(0.1);
  s21_scale(ui->openGLWidget->v, ui->openGLWidget->size_v,
            arg1 / ui->openGLWidget->num_last_scale);
  ui->openGLWidget->num_last_scale = arg1;
  ui->openGLWidget->update();
}

void MainWindow::on_SpinBox_moveX_valueChanged(double x) {
  s21_translate(ui->openGLWidget->v, ui->openGLWidget->size_v,
                x - ui->openGLWidget->num_last_x_move, 0);
  ui->openGLWidget->num_last_x_move = x;
  ui->openGLWidget->update();
}

void MainWindow::on_SpinBox_moveY_valueChanged(double y) {
  s21_translate(ui->openGLWidget->v, ui->openGLWidget->size_v,
                y - ui->openGLWidget->num_last_y_move, 1);
  ui->openGLWidget->num_last_y_move = y;
  ui->openGLWidget->update();
}

void MainWindow::on_SpinBox_moveZ_valueChanged(double z) {
  s21_translate(ui->openGLWidget->v, ui->openGLWidget->size_v,
                z - ui->openGLWidget->num_last_z_move, 2);
  ui->openGLWidget->num_last_z_move = z;
  ui->openGLWidget->update();
}

void MainWindow::on_exit_program_clicked()  // выход из программы
{
  QApplication::quit();
}

void MainWindow::on_color_lines_clicked()  // выбор цвета
{
  QColor color = QColorDialog::getColor(Qt::white, this, "Select Color");
  if (color.isValid()) ui->openGLWidget->colorLine(color);
}

void MainWindow::on_color_background_clicked() {
  QColor color = QColorDialog::getColor(Qt::white, this, "Select Color");
  if (color.isValid()) ui->openGLWidget->colorBackground(color);
}

void MainWindow::on_color_point_clicked() {
  QColor color = QColorDialog::getColor(Qt::white, this, "Select Color");
  if (color.isValid()) ui->openGLWidget->colorPoint(color);
}

// Вращение объекта

void MainWindow::on_SpinBox_X_rot_valueChanged(int arg1) {
  if (arg1 >= 360) {
    ui->SpinBox_X_rot->setValue(0);  // в spinBox установить значение 0
  } else if (arg1 <= -1) {
    ui->SpinBox_X_rot->setValue(359);
  } else {
    s21_rotate(ui->openGLWidget->v, ui->openGLWidget->size_v,
               arg1 - ui->openGLWidget->num_last_x_rot, 'x');
    ui->openGLWidget->num_last_x_rot = arg1;
  }
  QObject::connect(ui->SpinBox_X_rot, SIGNAL(valueChanged(int)), ui->dial_X_rot,
                   SLOT(setValue(int)));
  ui->openGLWidget->update();
}

void MainWindow::on_dial_X_rot_valueChanged(int value) {
  ui->openGLWidget->xRot = value;
  QObject::connect(ui->dial_X_rot, SIGNAL(valueChanged(int)), ui->SpinBox_X_rot,
                   SLOT(setValue(int)));
}

void MainWindow::on_SpinBox_Y_rot_valueChanged(int arg1) {
  if (arg1 >= 360) {
    ui->SpinBox_Y_rot->setValue(0);
  } else if (arg1 <= -1) {
    ui->SpinBox_Y_rot->setValue(359);
  } else {
    s21_rotate(ui->openGLWidget->v, ui->openGLWidget->size_v,
               arg1 - ui->openGLWidget->num_last_y_rot, 'y');
    ui->openGLWidget->num_last_y_rot = arg1;
  }
  QObject::connect(ui->SpinBox_Y_rot, SIGNAL(valueChanged(int)), ui->dial_Y_rot,
                   SLOT(setValue(int)));
  ui->openGLWidget->update();
}

void MainWindow::on_dial_Y_rot_valueChanged(int value) {
  ui->openGLWidget->yRot = value;
  QObject::connect(ui->dial_Y_rot, SIGNAL(valueChanged(int)), ui->SpinBox_Y_rot,
                   SLOT(setValue(int)));
}

void MainWindow::on_SpinBox_Z_rot_valueChanged(int arg1) {
  if (arg1 >= 360) {
    ui->SpinBox_Z_rot->setValue(0);
  } else if (arg1 <= -1) {
    ui->SpinBox_Z_rot->setValue(359);
  } else {
    s21_rotate(ui->openGLWidget->v, ui->openGLWidget->size_v,
               arg1 - ui->openGLWidget->num_last_z_rot, 'z');
    ui->openGLWidget->num_last_z_rot = arg1;
  }
  QObject::connect(ui->SpinBox_Z_rot, SIGNAL(valueChanged(int)), ui->dial_Z_rot,
                   SLOT(setValue(int)));
  ui->openGLWidget->update();
}

void MainWindow::on_dial_Z_rot_valueChanged(int value) {
  ui->openGLWidget->zRot = value;
  QObject::connect(ui->dial_Z_rot, SIGNAL(valueChanged(int)), ui->SpinBox_Z_rot,
                   SLOT(setValue(int)));
}

// Вид проекции

void MainWindow::on_radioButton_toggled(bool checked) {
  if (checked) {
    ui->radioButton_2->setChecked(0);
    ui->openGLWidget->projection(1);
    ui->openGLWidget->update();
  }
}

void MainWindow::on_radioButton_2_toggled(bool checked) {
  if (checked) {
    ui->radioButton->setChecked(0);
    ui->openGLWidget->projection(0);
  }
}

void MainWindow::on_line_clicked() {
  if (ui->line->isChecked()) {
    ui->dash_line->setChecked(0);
    ui->disable_line->setChecked(0);
    ui->openGLWidget->line_type(0);
  }
}

void MainWindow::on_dash_line_clicked() {
  if (ui->dash_line->isChecked()) {
    ui->line->setChecked(0);
    ui->disable_line->setChecked(0);
    ui->openGLWidget->line_type(1);
  }
}

void MainWindow::on_disable_line_clicked() {
  if (ui->disable_line->isChecked()) {
    ui->line->setChecked(0);
    ui->dash_line->setChecked(0);
    ui->openGLWidget->line_type(2);
  }
}

void MainWindow::on_doubleSpinBox_8_valueChanged(double arg1) {
  ui->openGLWidget->line_width(arg1);
}

void MainWindow::on_doubleSpinBox_9_valueChanged(double arg1) {
  ui->openGLWidget->point_size(arg1);
}

void MainWindow::on_square_clicked() {
  if (ui->square->isChecked()) {
    ui->circle->setChecked(0);
    ui->vertex_disable->setChecked(0);
    ui->openGLWidget->point_type(0);
  }
}

void MainWindow::on_circle_clicked() {
  if (ui->circle->isChecked()) {
    ui->square->setChecked(0);
    ui->vertex_disable->setChecked(0);
    ui->openGLWidget->point_type(1);
  }
}

void MainWindow::on_vertex_disable_clicked() {
  if (ui->vertex_disable->isChecked()) {
    ui->square->setChecked(0);
    ui->circle->setChecked(0);
    ui->openGLWidget->point_type(2);
  }
}

// Сброс параментров (Работает некоректно!)
void MainWindow::on_pB_resetParam_clicked() {
  ui->SpinBox_Scale->setValue(1);
  ui->SpinBox_X_rot->setValue(1);
  ui->SpinBox_Y_rot->setValue(1);
  ui->SpinBox_Z_rot->setValue(1);
  ui->SpinBox_X_rot->setValue(0);
  ui->SpinBox_Y_rot->setValue(0);
  ui->SpinBox_Z_rot->setValue(0);

  ui->SpinBox_moveX->setValue(0);
  ui->SpinBox_moveY->setValue(0);
  ui->SpinBox_moveZ->setValue(0);

  ui->doubleSpinBox_8->setValue(0);

  ui->openGLWidget->centerFigure();
  ui->openGLWidget->projection(1);

  ui->openGLWidget->line_type(0);
  ui->openGLWidget->point_type(0);
  // ui->openGLWidget->line_width(0);

  ui->openGLWidget->point_size(0);

  ui->openGLWidget->update();
}

void MainWindow::on_pushButton_clicked()  // Скрин
{
  qDebug() << "push screenShot";
  // Определение размеров окна виджета openGLWidget
  const QRect rect(0, 0, ui->openGLWidget->width(), ui->openGLWidget->height());
  QPixmap pixmap = ui->openGLWidget->grab(rect);
  // Создание имени файла с которым будет загружаться меню сохранения файла
  // screenShot'а
  const QString format = "png";
  QString initialPath =
      QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);
  if (initialPath.isEmpty()) {
    initialPath = QDir::currentPath();
  }
  initialPath += tr("/untitled.") + format;

  // Вызов диалогового окна "сохранить как"
  QFileDialog fileDialog(this, tr("Save As"), initialPath);
  fileDialog.setAcceptMode(QFileDialog::AcceptSave);
  fileDialog.setFileMode(QFileDialog::AnyFile);
  fileDialog.setDirectory(initialPath);

  QStringList mimeTypes;
  const QList<QByteArray> baMimeTypes = QImageWriter::supportedMimeTypes();
  for (const QByteArray &bf : baMimeTypes) {
    mimeTypes.append(QLatin1String(bf));
  }
  fileDialog.setMimeTypeFilters(mimeTypes);
  fileDialog.selectMimeTypeFilter("image/" + format);
  fileDialog.setDefaultSuffix(format);
  if (fileDialog.exec() != QDialog::Accepted) return;
  const QString fileName = fileDialog.selectedFiles().first();
  if (!pixmap.save(fileName)) {
    QMessageBox::warning(this, tr("Ошибка при сохранении"),
                         tr("Снимок экрана не сохранён saved to \"%1\".")
                             .arg(QDir::toNativeSeparators(fileName)));
  }
}

void MainWindow::on_pB_GIF_clicked() {
  qDebug() << "push GIF";
  QString filter = "*.gif";
  file_name = "/0";
  file_name = QFileDialog::getSaveFileName(this, "Сохранить GIF",
                                           QDir::homePath(), filter);

  ptr_save_file = new QFile(file_name);
  if (!ptr_save_file->open(QIODevice::WriteOnly)) {
    QMessageBox::critical(this, "Warning", "Не удалось записать файл");
  } else {
    start_timer_gif();
  }
}

void MainWindow::start_timer_gif() {
  gif = new QGifImage(QSize(640, 480));
  timerGIF = new QTimer(this);
  connect(timerGIF, &QTimer::timeout, this, &MainWindow::record_gif);
  timerGIF->start(100);
  frame = 0;
}

void MainWindow::record_gif() {
  qDebug() << ui->openGLWidget->width();
  qDebug() << ui->openGLWidget->height();
  const QRect rect(0, 0, 1024, 768);
  QPixmap pixmap = ui->openGLWidget->grab(rect);

  qDebug() << "pixmap = " << pixmap;

  QImage myImage = pixmap.toImage();
  frame++;
  gif->addFrame(myImage, 100);  // цифра это задержка
  if (frame == 50) {
    timerGIF->stop();
    gif->save(ptr_save_file);
    ptr_save_file->close();
    delete ptr_save_file;
    ptr_save_file = nullptr;
    delete gif;
    gif = nullptr;
    QMessageBox::about(this, "Статус", "GIF сохранена");
  }
}
