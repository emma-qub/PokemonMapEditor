#include "MapWidget.h"

#include <QPainter>
#include <iostream>
#include <QDockWidget>
#include <QTextStream>

MapWidget::MapWidget(QWidget* parent) :
  QLabel(parent),
  m_scale(2),
  m_currentX(0),
  m_currentY(0),
  m_columnCount(0),
  m_lineCount(0),
  m_fileName(),
  m_mapVector() {
}

void MapWidget::openMap(const QString& fileName) {
  m_fileName = fileName;

  QPixmap newPixmap(fileName);

  m_columnCount = newPixmap.width()/16;
  m_lineCount = newPixmap.height()/16;
  m_mapVector = QVector<int>(m_columnCount*m_lineCount, 14);

  drawTiles();
}

void MapWidget::saveMap(void) {
  QStringList nameAndExtension = m_fileName.split(".");
  nameAndExtension.removeLast();
  QString mapFileName = nameAndExtension.join(".")+".txt";

  QFile file(mapFileName);
  if(!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
    std::cerr << "Cannot open file in MapWidget::saveMap" << std::endl;
    return;
  }

  QTextStream inFile(&file);

  int k = 1;
  for (int tileType : m_mapVector) {
    if (tileType < 10)
      inFile << " ";
    inFile << tileType << ",";
    if (k%m_columnCount == 0)
      inFile << "\n";
    ++k;
  }

  file.close();

  std::cerr << "Map Saved" << std::endl;
}

void MapWidget::updateMapTileType(int tileType) {
  m_mapVector.replace(m_currentY*m_columnCount+m_currentX, tileType);

  drawTiles();
}

void MapWidget::moveTile(bool up, bool down, bool left, bool right) {
  if (up && m_currentY > 0)
    m_currentY--;
  else if (down && m_currentY < m_lineCount-1)
    m_currentY++;
  else if (left && m_currentX > 0)
    m_currentX--;
  else if (right && m_currentX < m_columnCount-1)
    m_currentX++;

  drawTiles();

  emit tileSelected(m_mapVector.at(m_currentY*m_columnCount+m_currentX));
}

void MapWidget::mousePressEvent(QMouseEvent* event) {
  m_currentX = event->x()/(16*m_scale);
  m_currentY = event->y()/(16*m_scale);

  drawTiles();

  emit tileSelected(m_mapVector.at(m_currentY*m_columnCount+m_currentX));
}

void MapWidget::drawTiles(void) {
  QImage image(m_fileName);
  image = image.scaled(image.width()*m_scale, image.height()*m_scale);

  QPixmap newPixmap = QPixmap::fromImage(image);
  QPainter *paint = new QPainter(&newPixmap);
  paint->setPen(Qt::black);

  for (unsigned int i = 1; i < newPixmap.width()/(16*m_scale); ++i)
    paint->drawLine(i*m_scale*16, 0, i*m_scale*16, newPixmap.height());
  for (unsigned int i = 1; i < newPixmap.width()/(16*m_scale); ++i)
    paint->drawLine(0, i*m_scale*16, newPixmap.width(), i*m_scale*16);

  paint->setPen(QPen(QBrush(Qt::black), 3));
  paint->drawRect(m_currentX*(16*m_scale), m_currentY*(16*m_scale), 16*m_scale, 16*m_scale);

  for (int k = 0; k < m_mapVector.size(); ++k) {
    if (m_mapVector.at(k) != 14) {
      int currentX = static_cast<int>(k%m_columnCount);
      int currentY = static_cast<int>(k/m_columnCount);
      paint->fillRect(currentX*(16*m_scale), currentY*(16*m_scale), 16*m_scale, 16*m_scale, QColor(255, 255, 255, 127));
    }
  }

  setPixmap(newPixmap);
}
