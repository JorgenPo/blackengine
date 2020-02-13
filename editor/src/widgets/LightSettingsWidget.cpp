//
// Created by popov on 10.02.2020.
//

#include "LightSettingsWidget.h"
#include "../renderwindow.h"

#include <QVBoxLayout>
#include <QFormLayout>
#include <QTranslator>
#include <QColorDialog>

#include <BlackEngine/log/Logger.h>


using namespace blackeditor;

LightSettingsWidget::LightSettingsWidget(std::shared_ptr<RenderWindow> renderWindow, QWidget *parent)
  : QWidget(parent)
  , m_renderWindow(std::move(renderWindow))
  , m_logger(black::Logger::Get("LightSettingsWidget"))
{
  auto mainLayout = new QVBoxLayout;

  mainLayout->addWidget(createAmbientLightGroupBox());
  mainLayout->addWidget(createDirectLightGroupBox());
  mainLayout->addStretch(50);
  setLayout(mainLayout);

  setUpSignals();
}

struct LightSettings {
  QGroupBox *groupBox;
  QSlider *slider;
  QPushButton *button;
  QCheckBox *checkBox;
};

LightSettings createLightGroupBox(std::string_view name) {
  LightSettings result{};
  auto box = new QGroupBox(QObject::tr(name.data()));
  auto form = new QFormLayout;

  result.slider = new QSlider(Qt::Horizontal, box);
  result.button = new QPushButton(box);
  result.checkBox = new QCheckBox(QObject::tr("Enable"));
  result.checkBox->setChecked(true);

  form->addRow(QObject::tr("Intensity"), result.slider);
  form->addRow(QObject::tr("Color"), result.button);
  form->addRow(result.checkBox);

  box->setLayout(form);

  result.groupBox = box;
  return result;
}

QGroupBox *LightSettingsWidget::createAmbientLightGroupBox() {
  auto ambientSettings = createLightGroupBox("Ambient light");
  m_ambientColorButton = ambientSettings.button;
  m_ambientIntensitySlider = ambientSettings.slider;
  m_ambientEnabledCB = ambientSettings.checkBox;
  return ambientSettings.groupBox;
}

QGroupBox *LightSettingsWidget::createDirectLightGroupBox() {
  auto directedSettings = createLightGroupBox("Directed light");
  m_directedColorButton = directedSettings.button;
  m_directedIntensitySlider = directedSettings.slider;
  m_directedEnabledCB = directedSettings.checkBox;
  return directedSettings.groupBox;
}

void LightSettingsWidget::setUpSignals() {
  connect(m_directedIntensitySlider, &QSlider::valueChanged, this, [=](int value) {
    m_renderWindow->getScene()->onLightIntensityChanged(static_cast<float>(value) / 100);
  });

  connect(m_ambientIntensitySlider,  &QSlider::valueChanged, this, [=](int value) {
    m_renderWindow->getScene()->onAmbientIntensityChanged(static_cast<float>(value) / 100);
  });

  connect(m_directedEnabledCB, &QCheckBox::clicked, this, [=]() {
    m_renderWindow->getScene()->setLightEnabled(m_directedEnabledCB->checkState());
  });

  connect(m_ambientColorButton, &QPushButton::clicked, this, [this]() {
    lightColorChanged(LightType::AMBIENT);
  });

  connect(m_directedColorButton, &QPushButton::clicked, this, [this]() {
    lightColorChanged(LightType::DIRECTED);
  });
}


void LightSettingsWidget::lightColorChanged(black::LightType lightType) {
  QPushButton *button;

  switch (lightType) {
  case LightType::DIRECTED:
    button = m_directedColorButton;
    break;
  case LightType::AMBIENT:
    button = m_ambientColorButton;
    break;
  default:
    m_logger->warning("MainWindow::lightColorChanged failed to change light color lightType={}", lightType);
    return;
  }

  const auto &palette = button->palette();
  const auto &oldColor = palette.color(QPalette::Button);
  auto newColor = QColorDialog::getColor(
      palette.color(QPalette::Button),
      this,
      "Choose new light color");

  if (newColor == oldColor) {
    return;
  }

  QPalette newPalette(palette);
  newPalette.setColor(QPalette::Button, newColor);
  button->setPalette(newPalette);

  m_renderWindow->getScene()->onLightColorChanged(newColor, lightType);
}

void LightSettingsWidget::setLightIntensity(black::LightType lightType, int value) {
  switch (lightType) {
  case LightType::DIRECTED: m_directedIntensitySlider->setValue(value);
  case LightType::SPOT:break;
  case LightType::POINT:break;
  case LightType::AMBIENT: m_ambientIntensitySlider->setValue(value);
  }
}
