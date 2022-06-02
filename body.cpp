#include "body.h"

body::body(float x_init, float y_init, float m) {
  x_position = x_init;
  y_position = y_init;
  mass = m;
}

void body::update_position(float dt) {
  x_position += x_velocity * dt;
  y_position += y_velocity * dt;
}

void body::update_velocity(float dvx, float dvy) {
  x_velocity += dvx;
  y_velocity += dvy;
}
