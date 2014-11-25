#ifndef MAPWIDGET_H
#define MAPWIDGET_H

#include <QLabel>
#include <QMouseEvent>
#include <QVector>

class MapWidget: public QLabel {
  Q_OBJECT

public:
  explicit MapWidget(QWidget* parent = nullptr);

  void openMap(const QString& fileName);
  void updateMapTileType(int tileType);

  void moveTile(bool up, bool down, bool left, bool right);

protected:
  virtual void mousePressEvent(QMouseEvent* event);

private:
  unsigned int m_scale;
  unsigned int m_currentX;
  unsigned int m_currentY;
  unsigned int m_columnCount;
  unsigned int m_lineCount;
  QString m_fileName;
  QVector<int> m_mapVector;

private:
  void drawTiles(void);

signals:
  void tileSelected(int tileType);

public slots:
  void saveMap(void);

};

#endif // MAPWIDGET_H
