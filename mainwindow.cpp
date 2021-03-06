#include "mainwindow.h"
#include "qgraphicsclickablerectitem.h"
#include "ui_mainwindow.h"
#include <QPointer>
#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  // Sets up the squares (every square is on by default)
  squareReset(true);
}

MainWindow::~MainWindow() { delete ui; }

// When we click the Load button, we load the current image to the cur_image
// variable, reset squares  and redraw the whole playground.
void MainWindow::on_pushButton_clicked() {
  filenames = QFileDialog::getOpenFileNames(
      this, tr("Select Images"), "", tr("Image Files (*.png *.jpg *.bmp)"));
  constIterator = filenames.constBegin();
  cur_image = QPixmap(*constIterator);
  ui->label->setText(*constIterator);
  squareReset(true);
  redraw();
}

int MainWindow::countUsedSquares() {
  int count = 0;
  for (int i = 0; i < SQUARE_X; ++i) {
    for (int j = 0; j < SQUARE_Y; ++j) {
      if (!squares[i][j])
        ++count;
    }
  }
  return count;
}

int MainWindow::countUsedMiddleSquares() {
  int count = 0;
  for (int i = 1; i < SQUARE_X - 1; ++i) {
    for (int j = 1; j < SQUARE_Y - 1; ++j) {
      if (!squares[i][j])
        ++count;
    }
  }
  return count;
}

// This function redraws the whole playground.
void MainWindow::redraw() {
  if (ui->graphicsView->scene()) {
    ui->graphicsView->scene()->clear();
    ui->graphicsView->scene()->deleteLater();
  }
  QPointer<QGraphicsScene> scene = new QGraphicsScene;

  if (!cur_image.isNull())
    scene->addPixmap(
        cur_image.scaled(ui->graphicsView->width(), ui->graphicsView->height(),
                         Qt::KeepAspectRatio, Qt::SmoothTransformation));
  ui->graphicsView->setRenderHints(QPainter::Antialiasing |
                                   QPainter::SmoothPixmapTransform |
                                   QPainter::TextAntialiasing);
  ui->graphicsView->setScene(scene);
  ui->graphicsView->fitInView(ui->graphicsView->scene()->sceneRect(),
                              Qt::KeepAspectRatio);

  qreal square_width = ui->graphicsView->scene()->width() / SQUARE_X;
  qreal square_height = ui->graphicsView->scene()->height() / SQUARE_Y;

  for (int i = 0; i < SQUARE_X; i++) {
    for (int j = 0; j < SQUARE_Y; j++) {
      if (squares[i][j]) {
        int number = (i + 1) + j * SQUARE_X; // Calculate current square number

        // Add a square to our scene
        QPen myPen(Qt::red);
        myPen.setWidth(2);
        ui->graphicsView->scene()->addRect(i * square_width, j * square_height,
                                           square_width, square_height, myPen,
                                           QBrush(Qt::black));
        QGraphicsItem *cur_rekt =
            new QGraphicsClickableRectItem(i * square_width, j * square_height,
                                           square_width, square_height, number);

        ui->graphicsView->scene()->addItem(cur_rekt);

        // Add a label to our square
        QPointer<QGraphicsTextItem> io = new QGraphicsTextItem;
        io->setPos((i * square_width + square_width / 2) - 20,
                   (j * square_height + square_height / 2) - 20);
        io->setPlainText(QString::number(number));
        io->setScale(2.0);
        io->setDefaultTextColor(Qt::white);
        ui->graphicsView->scene()->addItem(io);
      }
    }
  }
  int points = (SQUARE_X * SQUARE_Y / 2 - (countUsedSquares() / 2) * 2) -
               countUsedMiddleSquares();
  points = points > 0 ? points : 1;
  ui->pointLabel->setText("Punkte:" + QString::number(points));
  ui->graphicsView->show();
}

// On window resize we need to redraw our whole playfield, so the image will be
// visible.
void MainWindow::resizeEvent(QResizeEvent *) { redraw(); }

// This function resets the squares, so they are true or false
void MainWindow::squareReset(bool type) {
  for (int i = 0; i < SQUARE_X; i++) {
    for (int j = 0; j < SQUARE_Y; j++) {
      squares[i][j] = type;
    }
  }
}

void MainWindow::squareTurnOff(int number) {
  int number_x = (number - 1) % SQUARE_X; // x coordinate taken from number.
  int number_y = (number - 1) / SQUARE_X; // y coordinate taken from number.

  squares[number_x][number_y] = false;
  redraw();
}

void MainWindow::on_nextButton_clicked() {
  if (filenames.empty())
    return;

  constIterator = constIterator != (filenames.constEnd() - 1)
                      ? ++constIterator
                      : filenames.constBegin();
  cur_image = QPixmap(*constIterator);
  ui->label->setText(*constIterator);
  squareReset(true);
  redraw();
}

void MainWindow::on_previousButton_clicked() {
  if (filenames.empty())
    return;

  constIterator = constIterator != (filenames.constBegin())
                      ? --constIterator
                      : filenames.constEnd() - 1;
  cur_image = QPixmap(*constIterator);
  ui->label->setText(*constIterator);
  squareReset(true);
  redraw();
}

void MainWindow::on_RevealButton_clicked() {
  squareReset(false);
  redraw();
}
