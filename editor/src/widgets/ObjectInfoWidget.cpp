//
// Created by popov on 15.02.2020.
//
#include "ObjectInfoWidget.h"
#include "Vector3DEditWidget.h"
#include "common/Util.h"

#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QGroupBox>
#include <QVector3D>

#include <BlackEngine/GameObject.h>
#include <BlackEngine/components/Component.h>
#include <BlackEngine/components/TransformComponent.h>
#include <BlackEngine/components/BoundingComponent.h>
#include <BlackEngine/components/LightComponent.h>
#include <BlackEngine/components/ModelComponent.h>
#include <BlackEngine/components/TerrainComponent.h>
#include <BlackEngine/log/Logger.h>

using namespace blackeditor;
using namespace black;

ObjectInfoWidget::ObjectInfoWidget(QWidget *parent)
  : QWidget(parent)
{
  setUpLayout();
}

void ObjectInfoWidget::setObject(std::shared_ptr<black::GameObject> object) {
  m_object = std::move(object);
  renderObjectInfo();
}

void ObjectInfoWidget::setUpLayout() {
  m_mainLayout = new QVBoxLayout();

  // Name group box
  auto nameGB = new QGroupBox(tr("Name"));
  auto nameLayout = new QVBoxLayout();

  nameGB->setLayout(nameLayout);
  m_objectName = new QLabel(tr("Unknown"));
  nameLayout->addWidget(m_objectName);

  // Components group box
  m_componentsGB = new QGroupBox(tr("Components"));
  auto componentsLayout = new QVBoxLayout();

  m_componentsGB->setLayout(componentsLayout);
  m_mainLayout->addWidget(nameGB);
  m_mainLayout->addWidget(m_componentsGB);
  m_mainLayout->addStretch(20);

  setMinimumWidth(150);
  setLayout(m_mainLayout);
}

void ObjectInfoWidget::renderObjectInfo() {
  // Clear prior object info
  delete m_componentsGB->layout();
  m_componentsGB->setLayout(new QVBoxLayout());

  auto componentsLayout = new QVBoxLayout();
  m_objectName->setText(tr("Unknown"));

  if (m_object == nullptr) {
    return;
  }

  m_objectName->setText(m_object->getName().data());
  for (auto && [name, component] : m_object->getComponents()) {
    componentsLayout->addWidget(renderComponentInfo(name, component));
  }

  qDeleteAll(m_componentsGB->children());
  m_componentsGB->setLayout(componentsLayout);
}

QLayout *ObjectInfoWidget::renderComponent(const std::shared_ptr<black::TransformComponent>& component) {
  auto layout = new QVBoxLayout();
  m_position = new Vector3DEditWidget(toQtVector(component->getPosition()));
  connect(m_position, &Vector3DEditWidget::vectorChanged, this, &ObjectInfoWidget::onPositionChanged);
  layout->addWidget(m_position);

  auto componentLayout = new QVBoxLayout();
  componentLayout->addWidget(new QLabel(QObject::tr("Position")));
  componentLayout->addLayout(layout);
  return componentLayout;
}

QGroupBox *ObjectInfoWidget::renderComponentInfo(std::string_view name, std::shared_ptr<black::Component> component) {
  auto componentGB = new QGroupBox(tr(name.data()));
  QLayout *componentLayout = nullptr;

  if (name == TransformComponent::GetName()) {
    componentLayout = renderComponent(std::dynamic_pointer_cast<TransformComponent>(component));
  } else if (name == BoundingComponent::GetName()) {
    //componentLayout = renderComponent<BoundingComponent>(std::move(component));
  } else if (name == LightComponent::GetName()) {
    //componentLayout = renderComponent<LightComponent>(std::move(component));
  } else if (name == ModelComponent::GetName()) {
    //componentLayout = renderComponent<ModelComponent>(std::move(component));
  } else if (name == TerrainComponent::GetName()) {
    //componentLayout = renderComponent<TerrainComponent>(std::move(component));
  } else {
    Logger::Get("ObjectInfoWidget")->info(
        "renderComponentInfo failed: component with name '{}' not found", name);
  }

  componentGB->setLayout(componentLayout);
  return componentGB;
}

void ObjectInfoWidget::updateObjectInfo() {
  if (m_object == nullptr) {
    return;
  }

  auto transform = m_object->get<TransformComponent>();
}

void ObjectInfoWidget::onPositionChanged(const QVector3D &position) {
  if (m_object) {
    m_object->transform->setPosition(fromQtVector(position));
  }
}
