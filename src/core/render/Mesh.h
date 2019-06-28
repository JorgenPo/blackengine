//
// Created by popof on 09.10.2018.
//

#ifndef BLACKENGINE_MESH_H
#define BLACKENGINE_MESH_H

#include <CommonHeaders.h>
#include <Types.h>

#include <vector>

namespace black {
/**
 * Raw data such as vertices, indices and uv coordinates
 */
class BLACK_EXPORTED Mesh {
protected:
  std::vector<float> vertices;
  std::vector<float> textureCoords;

  DrawMode drawMode;
  int polygonSize;

public:
  Mesh(std::vector<float> vertices, std::vector<float> textureCoords);

  // Getters setters
  [[nodiscard]] const std::vector<float> &getVertices() const;

  [[nodiscard]] const std::vector<float> &getTextureCoords() const;

  [[nodiscard]] int getPolygonSize() const;
  void setPolygonSize(int polygonSize);

  /**
   * Can be overwritten to return render system specific draw mode value
   */
  [[nodiscard]] virtual int getDrawMode() const;
  void setDrawMode(DrawMode drawMode);

  size_t getVerticesCount();

  /**
   * Bind a mesh and use it for next draw function
   */
  virtual void bind() = 0;
};
}

#endif //BLACKENGINE_MESH_H
