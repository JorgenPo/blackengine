//
// Created by popov on 15.02.2020.
//

#ifndef BLACKENGINE_EDITOR_SRC_WIDGETS_OBJECTINFOWIDGET_H
#define BLACKENGINE_EDITOR_SRC_WIDGETS_OBJECTINFOWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QGroupBox>
#include <QVBoxLayout>

namespace black {
class GameObject;
class Component;
}

namespace blackeditor {

class ObjectInfoWidget : public QWidget {
Q_OBJECT;

  std::shared_ptr<black::GameObject> m_object;

  QLabel *m_objectName{};
  QVBoxLayout *m_mainLayout{};
  QGroupBox *m_componentsGB{};
public:
  explicit ObjectInfoWidget(QWidget *parent = nullptr);

public slots:
  void setObject(std::shared_ptr<black::GameObject> object);

private:
  void setUpLayout();
  void renderObjectInfo();
  QGroupBox *renderComponentInfo(std::string_view name, std::shared_ptr<black::Component> component);
};

}
#endif //BLACKENGINE_EDITOR_SRC_WIDGETS_OBJECTINFOWIDGET_H
