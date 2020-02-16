//
// Created by popov on 15.02.2020.
//

#include "Vector3DEditWidget.h"

#include <QHBoxLayout>
#include <QDoubleSpinBox>

#include <BlackEngine/log/Logger.h>

namespace blackeditor {

Vector3DEditWidget::Vector3DEditWidget(QVector3D vector, QWidget *parent)
  : QWidget(parent), m_vector(vector)
{
  setUpLayout();
  setUpSignals();
}

const QVector3D &Vector3DEditWidget::getVector() const {
  return m_vector;
}

void Vector3DEditWidget::setVector(const QVector3D &Vector) {
  m_vector = Vector;

  m_xSpin->setValue(Vector.x());
  m_ySpin->setValue(Vector.y());
  m_zSpin->setValue(Vector.z());
}

QDoubleSpinBox *createSpinboxFor(float value) {
  auto spinBox = new QDoubleSpinBox();
  spinBox->setRange(-1000.0f, 1000.0f);
  spinBox->setValue(value);
  spinBox->setSingleStep(std::abs(value) + 1.0f / 4.0f);

  return spinBox;
}

void Vector3DEditWidget::setUpLayout() {
  auto layout = new QHBoxLayout();
  m_xSpin = createSpinboxFor(m_vector.x());
  m_ySpin = createSpinboxFor(m_vector.y());
  m_zSpin = createSpinboxFor(m_vector.z());

  layout->addWidget(m_xSpin);
  layout->addWidget(m_ySpin);
  layout->addWidget(m_zSpin);
  setLayout(layout);
}

void Vector3DEditWidget::setUpSignals() {
  connect(m_xSpin, SIGNAL(valueChanged(double)), this, SLOT(onXChanged(double)));
  connect(m_ySpin, SIGNAL(valueChanged(double)), this, SLOT(onYChanged(double)));
  connect(m_zSpin, SIGNAL(valueChanged(double)), this, SLOT(onZChanged(double)));
}

void Vector3DEditWidget::onXChanged(double x) {
  m_vector.setX(static_cast<float>(x));
  emit vectorChanged(m_vector);
}

void Vector3DEditWidget::onYChanged(double y) {
  m_vector.setY(static_cast<float>(y));
  emit vectorChanged(m_vector);
}

void Vector3DEditWidget::onZChanged(double z) {
  m_vector.setZ(static_cast<float>(z));
  emit vectorChanged(m_vector);
}

}