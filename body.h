class body {
  private:
    float x_velocity;
    float y_velocity;


  public:
    float x_position;
    float y_position;
    float mass;

  void update_position(float dt);
  void update_velocity(float dvx, float dvy);
  body(float x_init, float y_init, float m);
};
