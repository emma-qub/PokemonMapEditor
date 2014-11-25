#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include "MapWidget.h"

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget* p_parent = nullptr);

public slots:
  void openMap(void);
  void updateMapTile(void);
  void updateRadioButton(int tileType);

protected:
  void keyReleaseEvent(QKeyEvent* event);

private:
  MapWidget* m_mapWidget;
  QAction* m_openMap;
  QAction* m_saveMap;
  QDockWidget* m_dockWidget;
  QRadioButton* m_walkable;
  QRadioButton* m_enterable;
  QRadioButton* m_cuttable;
  QRadioButton* m_readable;
  QRadioButton* m_swimable;
  QRadioButton* m_downjumpable;
  QRadioButton* m_rightjumpable;
  QRadioButton* m_leftjumpable;
  QRadioButton* m_upEnterable;
  QRadioButton* m_downEnterable;
  QRadioButton* m_rightEnterable;
  QRadioButton* m_leftEnterable;
  QRadioButton* m_catchable;
  QRadioButton* m_forbidden;
  QRadioButton* m_none;
};

#endif // MAINWINDOW_H
