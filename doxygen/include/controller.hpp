#pragma once

#include "model.hpp"
#include "view.hpp"

class Controller {
  private:
    Model model;
    View view;
    int variavel_interna;

  public:
    Controller(Model &model, View &view);
    ~Controller();
    void step();
};
