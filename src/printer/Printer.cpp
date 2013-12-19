#include "Printer.h"

namespace swift { namespace printer {

Printer::Printer(std::string str) : indent(0), newline(true) {
  file = fopen(str.c_str(), "w");
  if (file == NULL) {
    fprintf(stderr, "Warning: the output file is not modifiable! set defualt to stdout.\n");
    file = stdout;
  }
}

Printer::~Printer() {
  if (file != stdout) fclose(file);
}

void Printer::printIndent() {
  if (newline)
    fprintf(file, "%*s", indent, "");
}

void Printer::printLine() {
  if (newline)
    fprintf(file, "\n");
}

}
}
