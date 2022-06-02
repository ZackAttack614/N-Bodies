#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <cstdlib>
#include "body.cpp"

using namespace std;

float get_force(body body_1, body body_2);
float get_square_distance(body body_1, body body_2);
float get_sin_angle(body body_1, body body_2);
float get_cos_angle(body body_1, body body_2);

int main() {
  vector<body> bodies;

  int time_steps = 0;
  int num_bodies = 10;
  const float dt = 0.0001;
  float F;

  for (int i = 0; i < num_bodies; i++)
    bodies.push_back(body(rand() % 200 - 100, rand() % 200 - 100, 100));

  while (true) {
    time_steps += 1;

    for (int i = 0; i < bodies.size(); i++) {
      for (int j = i+1; j < bodies.size(); j++) {
        F = get_force(bodies[i], bodies[j]);
        bodies[i].update_velocity(get_cos_angle(bodies[i], bodies[j]) * F * dt / bodies[i].mass, get_sin_angle(bodies[i], bodies[j]) * F * dt / bodies[i].mass);
        bodies[j].update_velocity(get_cos_angle(bodies[j], bodies[i]) * F * dt / bodies[j].mass, get_sin_angle(bodies[j], bodies[i]) * F * dt / bodies[j].mass);
      }
    }

    for (int i = 0; i < bodies.size(); i++) {
      bodies[0].update_position(dt);

      if (time_steps % 1000 == 0)
        cout << "Body A x position: " << bodies[0].x_position << " Time steps: " << time_steps << endl;
    }
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