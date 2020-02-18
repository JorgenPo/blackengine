//
// Created by popov on 16.02.2020.
//

#include "PerformanceInfoWidget.h"

#include <BlackEngine/performance/PerformanceCounter.h>

using namespace blackeditor;

PerformanceInfoWidget::PerformanceInfoWidget(std::shared_ptr<black::PerformanceCounter> timer)
  : m_timer(std::move(timer))
{
  updateInfo();
}

void PerformanceInfoWidget::updateInfo() {
  static QString infoTemplate = tr("FPS: %1, MPF: %2");

  if (m_timer) {
    setText(infoTemplate.arg(m_timer->getFPS()).arg(m_timer->getTimeSinceLastUpdate()));
  }
}