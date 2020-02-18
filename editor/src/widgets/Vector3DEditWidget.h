//
// Created by popov on 15.02.2020.
//

#ifndef BLACKENGINE_EDITOR_SRC_WIDGETS_VECTOR3DEDITWIDGET_H
#define BLACKENGINE_EDITOR_SRC_WIDGETS_VECTOR3DEDITWIDGET_H

#include <QWidget>
#include <QVector3D>
#include <QDoubleSpinBox>

namespace blackeditor {

class Vector3DEditWidget : public QWidget {
  Q_OBJECT;

  QVector3D m_vector;
  float m_step;
  bool m_enableNegative;

  QDoubleSpinBox *m_xSpin;
  QDoubleSpinBox *m_ySpin;
  QDoubleSpinBox *m_zSpin;
public:
  explicit Vector3DEditWidget(QVector3D vector, float step, bool enableNegative = true, QWidget *parent = nullptr);

  [[nodiscard]] const QVector3D &getVector() const;
  void setVector(const QVector3D &Vector);

signals:
  void vectorChanged(const QVector3D &vector);

private:
  void setUpLayout();
  void setUpSignals();

private slots:
  void onXChanged(double x);
  void onYChanged(double y);
  void onZChanged(double z);
};

}

#endif //BLACKENGINE_EDITOR_SRC_WIDGETS_VECTOR3DEDITWIDGET_H
