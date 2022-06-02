#include <iostream>
#include <iomanip>
#include <cmath>
#include "body.cpp"

using namespace std;

float get_force(body body_1, body body_2);
float get_square_distance(body body_1, body body_2);
float get_sin_angle(body body_1, body body_2);
float get_cos_angle(body body_1, body body_2);

int main() {
  body A( 100, 100, 100);
  body B(-100, -50, 100);
  const float dt = 0.0001;
  float Fab;
  int time_steps = 0;

  while (true) {
    Fab = get_force(A, B);

    A.update_velocity(get_cos_angle(A, B) * Fab * dt / A.mass, get_sin_angle(A, B) * Fab * dt / A.mass);
    B.update_velocity(get_cos_angle(B, A) * Fab * dt / B.mass, get_sin_angle(B, A) * Fab * dt / B.mass);

    A.update_position(dt);
    B.update_position(dt);

    time_steps += 1;
    if (time_steps % 1000 == 0)
      cout << "Body A x position: " << A.x_position << " Time steps: " << time_steps << endl;
  }

  return 0;
}

float get_sin_angle(body body_1, body body_2) {
  return (body_1.y_position - body_2.y_position) / sqrt(get_square_distance(body_1, body_2));
}

float get_cos_angle(body body_1, body body_2) {
  return (body_1.x_position - body_2.x_position) / sqrt(get_square_distance(body_1, body_2));
}

float get_square_distance(body body_1, body body_2) {
  return pow(body_1.x_position - body_2.x_position, 2) + pow(body_1.y_position - body_2.y_position, 2);
}

float get_force(body body_1, body body_2) {
  float s_distance = get_square_distance(body_1, body_2);
  if (s_distance < 5) {
    return 0;
  }
  return -body_1.mass * body_2.mass / get_square_distance(body_1, body_2);
}