#include "lib.hpp"

// int circleDims() {}
// Point<double> circlePos() {}
int roundUpToMultipleOfEight(int v) { return (v + (8 - 1)) & -8; }
// midpoint circle alg
std::vector<SDL_Point> PixelizeCircle(SDL_Point center, int radius) {
  std::vector<SDL_Point> points;

  // 35 / 49 is a slightly biased approximation of 1/sqrt(2)
  const int arrSize = roundUpToMultipleOfEight(radius * 8 * 35 / 49);
  points.reserve(arrSize);
  const int32_t diameter = (radius * 2);
  int32_t x = (radius - 1);
  int32_t y = 0;
  int32_t tx = 1;
  int32_t ty = 1;
  int32_t error = (tx - diameter);

  while (x >= y) {
    // Each of the following renders an octant of the circle
    points.push_back({center.x + x, center.y - y});
    points.push_back({center.x + x, center.y + y});
    points.push_back({center.x - x, center.y - y});
    points.push_back({center.x - x, center.y + y});
    points.push_back({center.x + y, center.y - x});
    points.push_back({center.x + y, center.y + x});
    points.push_back({center.x - y, center.y - x});
    points.push_back({center.x - y, center.y + x});
    if (error <= 0) {
      ++y;
      error += ty;
      ty += 2;
    }
    if (error > 0) {
      --x;
      tx += 2;
      error += (tx - diameter);
    }
  }
  return points;  // RVO FTW
}

std::vector<SDL_Vertex> triangleFanCirc(int x, int y, int radius,
                                        int segments) {
  segments += 2;
  std::vector<SDL_Vertex> circle(segments + 2);
  circle[0].position.x = x;
  circle[0].position.y = y;
  // 225, 150, 107, 255

  for (int i = 1; i < segments; i++) {
    double dPi = 2 * M_PI;
    circle[i].position.x = x + (radius * cos(dPi / segments));
    circle[i].position.y = y + (radius * sin(dPi / segments));
    circle[i].color.r = 255;
    circle[i].color.g = 150;
    circle[i].color.b = 107;
    circle[i].color.a = 255;
  }
  return circle;
}

void GenerateCircle(std::vector<SDL_Vertex> &outCircleVertices,
                    size_t vertexCount, int radius,
                    std::vector<int> &outIndices) {
  // Size our vector so it can hold all the requested vertices plus our center
  // one
  outCircleVertices.resize(vertexCount + 1);

  // Calculate the angle we'll need to rotate by for each iteration (* (PI /
  // 180) to convert it into radians)
  double segRotationAngle = (360.0 / vertexCount) * (M_PI / 180);

  // Here I set a center in the middle of the window as an example. The center
  // point of the circle can be anywhere
  int centerX = DIM_X / 2;
  int centerY = DIM_Y / 2;

  // We need an initial vertex in the center as a point for all of the triangles
  // we'll generate
  outCircleVertices[0].position.x = centerX;
  outCircleVertices[0].position.y = centerY;

  // Set the colour of the center point
  outCircleVertices[0].color.r = 255;
  outCircleVertices[0].color.g = 255;
  outCircleVertices[0].color.b = 255;
  outCircleVertices[0].color.a = 255;

  // Set the starting point for the initial generated vertex. We'll be rotating
  // this point around the origin in the loop
  double startX = 0.0 - radius;
  double startY = 0.0;

  for (int i = 1; i < vertexCount + 1; i++) {
    // Calculate the angle to rotate the starting point around the origin
    double finalSegRotationAngle = (i * segRotationAngle);

    // Rotate the start point around the origin (0, 0) by the
    // finalSegRotationAngle (see
    // https://en.wikipedia.org/wiki/Rotation_(mathematics) section on two
    // dimensional rotation)
    outCircleVertices[i].position.x = cos(finalSegRotationAngle) * startX -
                                      sin(finalSegRotationAngle) * startY;
    outCircleVertices[i].position.y = cos(finalSegRotationAngle) * startY +
                                      sin(finalSegRotationAngle) * startX;

    // Set the point relative to our defined center (in this case the center of
    // the screen)
    outCircleVertices[i].position.x += centerX;
    outCircleVertices[i].position.y += centerY;

    // Set the colour for the vertex
    outCircleVertices[i].color.r = 255;
    outCircleVertices[i].color.g = 255;
    outCircleVertices[i].color.b = 255;
    outCircleVertices[i].color.a = 255;

    // Add centre point index
    outIndices.push_back(0);

    // Add generated point index
    outIndices.push_back(i);

    // Add next point index (with logic to wrap around when we reach the start)
    int index = (i + 1) % vertexCount;
    if (index == 0) {
      index = vertexCount;
    }
    outIndices.push_back(index);
  }
}
