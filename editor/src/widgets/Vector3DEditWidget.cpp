//
// Created by popov on 15.02.2020.
//

#include "Vector3DEditWidget.h"

#include <QHBoxLayout>
#include <QDoubleSpinBox>

namespace blackeditor {

Vector3DEditWidget::Vector3DEditWidget(QVector3D vector, QWidget *parent)
  : QWidget(parent), m_vector(vector)
{
  setUpLayout();
}

const QVector3D &Vector3DEditWidget::getVector() const {
  return m_vector;
}

void Vector3DEditWidget::setVector(const QVector3D &Vector) {
  m_vector = Vector;
  setUpLayout();
}

QDoubleSpinBox *createSpinboxFor(float value) {
  auto spinBox = new QDoubleSpinBox();
  spinBox->setRange(-1000.0f, 1000.0f);
  spinBox->setValue(value);

  return spinBox;
}

void Vector3DEditWidget::setUpLayout() {
  auto layout = new QHBoxLayout();
  layout->addWidget(createSpinboxFor(m_vector.x()));
  layout->addWidget(createSpinboxFor(m_vector.y()));
  layout->addWidget(createSpinboxFor(m_vector.z()));
  setLayout(layout);
}

}