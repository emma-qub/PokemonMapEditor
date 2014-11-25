#include "MainWindow.h"

#include <iostream>

MainWindow::MainWindow(QWidget* p_parent):
  QMainWindow(p_parent) {

  m_openMap = new QAction("Open Map", this);
  m_openMap->setShortcut(QKeySequence::Open);
  connect(m_openMap, SIGNAL(triggered(void)), this, SLOT(openMap(void)));
  addAction(m_openMap);

  m_mapWidget = new MapWidget;

  m_saveMap = new QAction("Save Map", this);
  m_saveMap->setShortcut(QKeySequence::Save);
  connect(m_saveMap, SIGNAL(triggered(void)), m_mapWidget, SLOT(saveMap(void)));
  addAction(m_saveMap);

  setCentralWidget(m_mapWidget);
  m_mapWidget->setAlignment(Qt::AlignCenter);
  connect(m_mapWidget, SIGNAL(tileSelected(int)), this, SLOT(updateRadioButton(int)));

  setWindowTitle("Pokemon Map Editor");

  QWidget* wid = new QWidget;
  m_walkable = new QRadioButton("m_walkable");
  m_enterable = new QRadioButton("m_enterable");
  m_cuttable = new QRadioButton("m_cuttable");
  m_readable = new QRadioButton("m_readable");
  m_swimable = new QRadioButton("m_swimable");
  m_downjumpable = new QRadioButton("m_downjumpable");
  m_rightjumpable = new QRadioButton("m_rightjumpable");
  m_leftjumpable = new QRadioButton("m_leftjumpable");
  m_upEnterable = new QRadioButton("m_upEnterable");
  m_downEnterable = new QRadioButton("m_downEnterable");
  m_rightEnterable = new QRadioButton("m_rightEnterable");
  m_leftEnterable = new QRadioButton("m_leftEnterable");
  m_catchable = new QRadioButton("m_catchable");
  m_forbidden = new QRadioButton("m_forbidden");
  m_none = new QRadioButton("None");
  m_none->setVisible(false);

  connect(m_walkable, SIGNAL(clicked()), this, SLOT(updateMapTile()));
  connect(m_enterable , SIGNAL(clicked()), this, SLOT(updateMapTile()));
  connect(m_cuttable , SIGNAL(clicked()), this, SLOT(updateMapTile()));
  connect(m_readable , SIGNAL(clicked()), this, SLOT(updateMapTile()));
  connect(m_swimable , SIGNAL(clicked()), this, SLOT(updateMapTile()));
  connect(m_downjumpable , SIGNAL(clicked()), this, SLOT(updateMapTile()));
  connect(m_rightjumpable , SIGNAL(clicked()), this, SLOT(updateMapTile()));
  connect(m_leftjumpable , SIGNAL(clicked()), this, SLOT(updateMapTile()));
  connect(m_upEnterable , SIGNAL(clicked()), this, SLOT(updateMapTile()));
  connect(m_downEnterable , SIGNAL(clicked()), this, SLOT(updateMapTile()));
  connect(m_rightEnterable , SIGNAL(clicked()), this, SLOT(updateMapTile()));
  connect(m_leftEnterable , SIGNAL(clicked()), this, SLOT(updateMapTile()));
  connect(m_catchable , SIGNAL(clicked()), this, SLOT(updateMapTile()));
  connect(m_forbidden , SIGNAL(clicked()), this, SLOT(updateMapTile()));

  QVBoxLayout* widLayout = new QVBoxLayout;
  widLayout->addWidget(m_walkable);
  widLayout->addWidget(m_enterable);
  widLayout->addWidget(m_cuttable);
  widLayout->addWidget(m_readable);
  widLayout->addWidget(m_swimable);
  widLayout->addWidget(m_downjumpable);
  widLayout->addWidget(m_rightjumpable);
  widLayout->addWidget(m_leftjumpable);
  widLayout->addWidget(m_upEnterable);
  widLayout->addWidget(m_downEnterable);
  widLayout->addWidget(m_rightEnterable);
  widLayout->addWidget(m_leftEnterable);
  widLayout->addWidget(m_catchable);
  widLayout->addWidget(m_forbidden);
  widLayout->addWidget(m_none);
  wid->setLayout(widLayout);

  m_dockWidget = new QDockWidget("Map TileTtype");
  m_dockWidget->setAllowedAreas(Qt::RightDockWidgetArea);
  m_dockWidget->setWidget(wid);
  addDockWidget(Qt::RightDockWidgetArea, m_dockWidget);
}

void MainWindow::openMap(void) {
  QString fileName = QFileDialog::getOpenFileName(this, "Open Map", "../Pokemon/resources/maps", "PNG File (*.png)");
  if (fileName == "") {
    return;
  }

  m_mapWidget->openMap(fileName);
}

void MainWindow::updateMapTile(void) {
  if (m_walkable->isChecked())
    m_mapWidget->updateMapTileType(0);
  else if (m_enterable->isChecked())
    m_mapWidget->updateMapTileType(1);
  else if (m_cuttable->isChecked())
    m_mapWidget->updateMapTileType(2);
  else if (m_readable->isChecked())
    m_mapWidget->updateMapTileType(3);
  else if (m_swimable->isChecked())
    m_mapWidget->updateMapTileType(4);
  else if (m_downjumpable->isChecked())
    m_mapWidget->updateMapTileType(5);
  else if (m_rightjumpable->isChecked())
    m_mapWidget->updateMapTileType(6);
  else if (m_leftjumpable->isChecked())
    m_mapWidget->updateMapTileType(7);
  else if (m_upEnterable->isChecked())
    m_mapWidget->updateMapTileType(8);
  else if (m_downEnterable->isChecked())
    m_mapWidget->updateMapTileType(9);
  else if (m_rightEnterable->isChecked())
    m_mapWidget->updateMapTileType(10);
  else if (m_leftEnterable->isChecked())
    m_mapWidget->updateMapTileType(11);
  else if (m_catchable->isChecked())
    m_mapWidget->updateMapTileType(12);
  else if (m_forbidden->isChecked())
    m_mapWidget->updateMapTileType(13);
}

void MainWindow::updateRadioButton(int tileType) {
  std::cerr << tileType << std::endl;

  disconnect(m_walkable, SIGNAL(clicked()), this, SLOT(updateMapTile()));
  disconnect(m_enterable , SIGNAL(clicked()), this, SLOT(updateMapTile()));
  disconnect(m_cuttable , SIGNAL(clicked()), this, SLOT(updateMapTile()));
  disconnect(m_readable , SIGNAL(clicked()), this, SLOT(updateMapTile()));
  disconnect(m_swimable , SIGNAL(clicked()), this, SLOT(updateMapTile()));
  disconnect(m_downjumpable , SIGNAL(clicked()), this, SLOT(updateMapTile()));
  disconnect(m_rightjumpable , SIGNAL(clicked()), this, SLOT(updateMapTile()));
  disconnect(m_leftjumpable , SIGNAL(clicked()), this, SLOT(updateMapTile()));
  disconnect(m_upEnterable , SIGNAL(clicked()), this, SLOT(updateMapTile()));
  disconnect(m_downEnterable , SIGNAL(clicked()), this, SLOT(updateMapTile()));
  disconnect(m_rightEnterable , SIGNAL(clicked()), this, SLOT(updateMapTile()));
  disconnect(m_leftEnterable , SIGNAL(clicked()), this, SLOT(updateMapTile()));
  disconnect(m_catchable , SIGNAL(clicked()), this, SLOT(updateMapTile()));
  disconnect(m_forbidden , SIGNAL(clicked()), this, SLOT(updateMapTile()));

  m_walkable->setChecked(tileType == 0);
  m_enterable->setChecked(tileType == 1);
  m_cuttable->setChecked(tileType == 2);
  m_readable->setChecked(tileType == 3);
  m_swimable->setChecked(tileType == 4);
  m_downjumpable->setChecked(tileType == 5);
  m_rightjumpable->setChecked(tileType == 6);
  m_leftjumpable->setChecked(tileType == 7);
  m_upEnterable->setChecked(tileType == 8);
  m_downEnterable->setChecked(tileType == 9);
  m_rightEnterable->setChecked(tileType == 10);
  m_leftEnterable->setChecked(tileType == 11);
  m_catchable->setChecked(tileType == 12);
  m_forbidden->setChecked(tileType == 13);
  m_none->setChecked(tileType == 14);

  connect(m_walkable, SIGNAL(clicked()), this, SLOT(updateMapTile()));
  connect(m_enterable , SIGNAL(clicked()), this, SLOT(updateMapTile()));
  connect(m_cuttable , SIGNAL(clicked()), this, SLOT(updateMapTile()));
  connect(m_readable , SIGNAL(clicked()), this, SLOT(updateMapTile()));
  connect(m_swimable , SIGNAL(clicked()), this, SLOT(updateMapTile()));
  connect(m_downjumpable , SIGNAL(clicked()), this, SLOT(updateMapTile()));
  connect(m_rightjumpable , SIGNAL(clicked()), this, SLOT(updateMapTile()));
  connect(m_leftjumpable , SIGNAL(clicked()), this, SLOT(updateMapTile()));
  connect(m_upEnterable , SIGNAL(clicked()), this, SLOT(updateMapTile()));
  connect(m_downEnterable , SIGNAL(clicked()), this, SLOT(updateMapTile()));
  connect(m_rightEnterable , SIGNAL(clicked()), this, SLOT(updateMapTile()));
  connect(m_leftEnterable , SIGNAL(clicked()), this, SLOT(updateMapTile()));
  connect(m_catchable , SIGNAL(clicked()), this, SLOT(updateMapTile()));
  connect(m_forbidden , SIGNAL(clicked()), this, SLOT(updateMapTile()));
}

void MainWindow::keyReleaseEvent(QKeyEvent* event) {
  switch (event->key()) {
  case Qt::Key_Up:
    m_mapWidget->moveTile(true, false, false, false);
    break;
  case Qt::Key_Down:
    m_mapWidget->moveTile(false, true, false, false);
    break;
  case Qt::Key_Left:
    m_mapWidget->moveTile(false, false, true, false);
    break;
  case Qt::Key_Right:
    m_mapWidget->moveTile(false, false, false, true);
    break;
  }
}
