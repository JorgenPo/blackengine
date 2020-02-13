//
// Created by popov on 10.02.2020.
//

#ifndef BLACKENGINE_EDITOR_SRC_WIDGETS_LIGHTSETTINGSWIDGET_H
#define BLACKENGINE_EDITOR_SRC_WIDGETS_LIGHTSETTINGSWIDGET_H

#include <QWidget>
#include <QGroupBox>
#include <QSlider>
#include <QPushButton>

namespace blackeditor {

class RenderWindow;

/**
 * Light settings dock widget
 */
class LightSettingsWidget : public QWidget {
Q_OBJECT;

  std::shared_ptr<RenderWindow> m_renderWindow;
  QSlider *m_ambientIntensitySlider{};
  QSlider *m_directedIntensitySlider{};
  QPushButton *m_ambientColorButton{};
  QPushButton *m_directedColorButton{};

public:
  LightSettingsWidget(std::shared_ptr<RenderWindow> renderWindow, QWidget *parent = nullptr);

private:
  QGroupBox *createAmbientLightGroupBox();
  QGroupBox *createDirectLightGroupBox();
};

}

#endif //BLACKENGINE_EDITOR_SRC_WIDGETS_LIGHTSETTINGSWIDGET_H
