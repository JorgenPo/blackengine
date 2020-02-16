//
// Created by popov on 16.02.2020.
//

#ifndef BLACKENGINE_EDITOR_SRC_WIDGETS_PERFORMANCEINFOWIDGET_H
#define BLACKENGINE_EDITOR_SRC_WIDGETS_PERFORMANCEINFOWIDGET_H

#include <QLabel>

namespace black {
class PerformanceCounter;
}

namespace blackeditor {

class PerformanceInfoWidget : public QLabel {
Q_OBJECT;

  std::shared_ptr<black::PerformanceCounter> m_timer;

public:
  explicit PerformanceInfoWidget(std::shared_ptr<black::PerformanceCounter> timer);

  void updateInfo();
};

}

#endif //BLACKENGINE_EDITOR_SRC_WIDGETS_PERFORMANCEINFOWIDGET_H
