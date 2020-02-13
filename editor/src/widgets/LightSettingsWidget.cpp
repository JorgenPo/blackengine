//
// Created by popov on 10.02.2020.
//

#include "LightSettingsWidget.h"

#include <QVBoxLayout>
#include <QFormLayout>
#include <QTranslator>

using namespace blackeditor;

LightSettingsWidget::LightSettingsWidget(std::shared_ptr<RenderWindow> renderWindow, QWidget *parent)
  : QWidget(parent), m_renderWindow(std::move(renderWindow))
{
  auto mainLayout = new QVBoxLayout;

  mainLayout->addWidget(createAmbientLightGroupBox());
  mainLayout->addWidget(createDirectLightGroupBox());
  mainLayout->addStretch(50);
  setLayout(mainLayout);
}

QGroupBox *createLightGroupBox(std::string_view name, QSlider *slider, QPushButton *button) {
  auto box = new QGroupBox(QObject::tr(name.data()));
  auto form = new QFormLayout;

  slider = new QSlider(Qt::Horizontal, box);
  button = new QPushButton(box);

  form->addRow(QObject::tr("Intensity"), slider);
  form->addRow(QObject::tr("Color"), button);
  box->setLayout(form);

  return box;
}

QGroupBox *LightSettingsWidget::createAmbientLightGroupBox() {
  return createLightGroupBox("Ambient light", m_ambientIntensitySlider, m_ambientColorButton);
}

QGroupBox *LightSettingsWidget::createDirectLightGroupBox() {
  return createLightGroupBox("Directed light", m_directedIntensitySlider, m_directedColorButton);
}
