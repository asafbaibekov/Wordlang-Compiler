#ifndef SYMBOL_OPERATIONS_H
#define SYMBOL_OPERATIONS_H

#include <stdio.h>
#include <stdlib.h>
#include "Symbol.h"
#include "../bin/y.tab.h"

Symbol *perform_unary_operation(int OPERATION, Symbol *symbol);

Symbol *perform_binary_operation(Symbol *symbol1, int OPERATION, Symbol *symbol2);

void perform_input_operation(Symbol **symbol);

#endif // SYMBOL_OPERATIONS_H