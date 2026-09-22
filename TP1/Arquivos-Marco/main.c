#include "controleDaMissao/controleDaMissao.h"

int main() {
  srand(time(NULL)); 

  CentroDePesquisa cp;
  char inputFileName[MAX_TAM_STRING];

  cm_input(inputFileName);

  cm_init(&cp);
  
  cm_registro(&cp, inputFileName);
  
  cm_captura(&cp);
  
  cm_retorno(&cp);
  
  cm_relatorio(&cp);

  cm_libera(&cp);
   
  return SUCESSO;
}
