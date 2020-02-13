//
// Created by popov on 01.12.2019.
//

#ifndef BLACKENGINE_EDITOR_SRC_WIDGETS_CONTEXTINFOWIDGET_H
#define BLACKENGINE_EDITOR_SRC_WIDGETS_CONTEXTINFOWIDGET_H

#include <QtWidgets/QWidget>
#include <QtGui/QSurfaceFormat>

#include <renderwindow.h>

#include <memory>

QT_BEGIN_NAMESPACE
namespace Ui { class ContextInfo; }
QT_END_NAMESPACE

namespace blackeditor {
class ContextInfoWidget : public QWidget {
Q_OBJECT;

  std::shared_ptr<Ui::ContextInfo> ui;

public:
  ContextInfoWidget(QWidget *parent, std::shared_ptr<blackeditor::RenderWindow> renderWindow);
};

}

#endif //BLACKENGINE_EDITOR_SRC_WIDGETS_CONTEXTINFOWIDGET_H
