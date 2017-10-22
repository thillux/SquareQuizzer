#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#define SQUARE_X 8
#define SQUARE_Y 8

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = nullptr);
  void squareReset(bool type);
  bool squares[SQUARE_X][SQUARE_Y];
  void squareTurnOff(int number);
  void redraw();
  ~MainWindow() override;
  int countUsedSquares();
  int countUsedMiddleSquares();

private slots:

  void on_pushButton_clicked();
  void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;

  void on_nextButton_clicked();

  void on_previousButton_clicked();

  void on_RevealButton_clicked();

private:
  Ui::MainWindow *ui;

  QStringList filenames;
  QStringList::const_iterator constIterator;
  QPixmap cur_image;
};

#endif // MAINWINDOW_H
