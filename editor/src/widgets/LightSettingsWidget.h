//
// Created by popov on 10.02.2020.
//

#ifndef BLACKENGINE_EDITOR_SRC_WIDGETS_LIGHTSETTINGSWIDGET_H
#define BLACKENGINE_EDITOR_SRC_WIDGETS_LIGHTSETTINGSWIDGET_H

#include <QWidget>
#include <QGroupBox>
#include <QSlider>
#include <QPushButton>
#include <QCheckBox>

#include <BlackEngine/components/LightComponent.h>

namespace black {
class Logger;
}

namespace blackeditor {

class RenderWindow;

/**
 * Light settings dock widget
 */
class LightSettingsWidget : public QWidget {
Q_OBJECT;
  std::shared_ptr<black::Logger> m_logger;
  std::shared_ptr<RenderWindow> m_renderWindow;
  QSlider *m_ambientIntensitySlider{};
  QSlider *m_directedIntensitySlider{};
  QPushButton *m_ambientColorButton{};
  QPushButton *m_directedColorButton{};
  QCheckBox *m_directedEnabledCB{};
  QCheckBox *m_ambientEnabledCB{};

public:
  explicit LightSettingsWidget(std::shared_ptr<RenderWindow> renderWindow, QWidget *parent = nullptr);
  void setLightIntensity(black::LightType lightType, int value);

private:
  QGroupBox *createAmbientLightGroupBox();
  QGroupBox *createDirectLightGroupBox();

  void setUpSignals();
  void lightColorChanged(black::LightType lightType);

};

}

#endif //BLACKENGINE_EDITOR_SRC_WIDGETS_LIGHTSETTINGSWIDGET_H
