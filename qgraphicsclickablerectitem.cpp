#include "qgraphicsclickablerectitem.h"
#include "mainwindow.h"
#include <QApplication>
#include <QDebug>

void QGraphicsClickableRectItem::mousePressEvent(QGraphicsSceneMouseEvent *) {
  QWidgetList widgets = qApp->topLevelWidgets();
  for (QWidgetList::iterator i = widgets.begin(); i != widgets.end(); ++i)
    if ((*i)->objectName() == "MainWindow")
      (static_cast<MainWindow *>(*i))->squareTurnOff(number);
}
