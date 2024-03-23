#include "argparse/argparse.hpp"
#include <fstream>
#include <stdexcept>

#include "TransEngine/TransLang/Compiler/ChameleonsParserMain-inl.h"

struct FAILED_TO_TRANSFOMRED: public std::exception {
  ~FAILED_TO_TRANSFOMRED() {}
  const char* what() {
    return "Failed to transformed";
  }
};

int main(int argc, char* argv[]) {
  argparse::ArgumentParser program("Chameleon", "0.0.1");

  // Commandline register
  program.add_argument("-i", "--input")
    .required()
    .help("Path of target source file to be transformed");

  program.add_argument("-o", "--output")
    .required()
    .help("Path to output transformed file");

  program.add_argument("-r", "--rule")
    .required()
    .help("Path of rule configurations");

  try {
    program.parse_args(argc, argv);
  } catch (const std::exception& err) {
    std::cerr << err.what() << std::endl;
    std::cerr << program;
    std::exit(1);
  }

  std::ifstream input_rule(program.get("--rule"));
  std::ifstream input(program.get("--input"));
  std::ofstream output(program.get("--output"));

  using Main = Chameleon::TransEngine::Compiler::ChameleonsMain;
  Main main(&input_rule, &input);

  std::optional<std::string> transed = main();
  if (!transed.has_value()) {
    throw FAILED_TO_TRANSFOMRED();
  } else {
    output << transed.value();
  }

  output.close();
  input_rule.close();
  input.close();

  return 0;
}
