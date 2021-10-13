
#include "../json/json.hpp"
#include <iostream>
#include <fstream>

using nlohmann::json;

class Contador {
  private:
    int contagem;

  public:
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Contador, contagem);
    Contador() { contagem=0; }
    void contar() { contagem++; }
    int get_contagem() { return contagem; }
};

int main() {
  Contador c;

  json j;
  std::ifstream ifile;
  ifile.open("teste.json");
  ifile >> j;
  ifile.close();

  c = j["contador"];
  c.contar();
  j["contador"] = c;

  std::ofstream ofile;
  ofile.open("teste.json");
  ofile << j;
  ofile.close();

  std::cout << "Este programa executou: " << c.get_contagem() << " vezes " << std::endl;

  return 0;
}
