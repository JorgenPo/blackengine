#include "ContextInfoWidget.h"
#include "ui_context_info.h"

#include <memory>

constexpr const char *to_string(QSurfaceFormat::OpenGLContextProfile profile) {
  switch (profile) {
  case QSurfaceFormat::OpenGLContextProfile::CompatibilityProfile:
    return "Compatibility";
  case QSurfaceFormat::OpenGLContextProfile::CoreProfile:
    return "Core";
  case QSurfaceFormat::NoProfile:
    return "No profile";
  }

  return "Unknown";
}

ContextInfoWidget::ContextInfoWidget(QWidget *parent, std::shared_ptr<blackeditor::RenderWindow> renderWindow)
: QWidget(parent)
, ui(std::make_shared<Ui::ContextInfo>()) {
  ui->setupUi(this);

  ui->lContextVersion->setText(renderWindow->getOpenGLVersionString().c_str());
  ui->lGlslVersion->setText(renderWindow->getGLSLVersionString().c_str());
  ui->lContextProfile->setText(renderWindow->getProfileString().c_str());
}
