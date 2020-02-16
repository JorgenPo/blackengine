//
// Created by popov on 15.02.2020.
//

#ifndef BLACKENGINE_EDITOR_SRC_WIDGETS_VECTOR3DEDITWIDGET_H
#define BLACKENGINE_EDITOR_SRC_WIDGETS_VECTOR3DEDITWIDGET_H

#include <QWidget>
#include <QVector3D>

namespace blackeditor {

class Vector3DEditWidget : public QWidget {
  Q_OBJECT;

  QVector3D m_vector;

public:
  explicit Vector3DEditWidget(QVector3D vector, QWidget *parent = nullptr);

  [[nodiscard]] const QVector3D &getVector() const;
  void setVector(const QVector3D &Vector);

private:
  void setUpLayout();
};

}

#endif //BLACKENGINE_EDITOR_SRC_WIDGETS_VECTOR3DEDITWIDGET_H
