#include "Test.h"
#include <stdio.h>

namespace Bobert {
  void Print() {
    printf("Welcome to Bobert Engine :)\n"); // \n to znak nowej linii
    fflush(stdout); // To wymusza natychmiastowe wypisanie tekstu na ekran
  }
}