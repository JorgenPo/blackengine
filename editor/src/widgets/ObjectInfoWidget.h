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
class TransformComponent;
}

namespace blackeditor {
class Vector3DEditWidget;

class ObjectInfoWidget : public QWidget {
Q_OBJECT;

  std::shared_ptr<black::GameObject> m_object;

  QLabel *m_objectName{};
  QVBoxLayout *m_mainLayout{};
  QGroupBox *m_componentsGB{};
  Vector3DEditWidget *m_position;
  Vector3DEditWidget *m_rotation;
  Vector3DEditWidget *m_scale;

public:
  explicit ObjectInfoWidget(QWidget *parent = nullptr);

public slots:
  void setObject(std::shared_ptr<black::GameObject> object);
  void updateObjectInfo();
  void onPositionChanged(const QVector3D &position);
  void onRotationChanged(const QVector3D &rotation);
  void onScaleChanged(const QVector3D &scale);

private:
  void setUpLayout();
  void renderObjectInfo();
  QGroupBox *renderComponentInfo(std::string_view name, std::shared_ptr<black::Component> component);
  QLayout *renderComponent(const std::shared_ptr<black::TransformComponent>& component);
};

}
#endif //BLACKENGINE_EDITOR_SRC_WIDGETS_OBJECTINFOWIDGET_H
