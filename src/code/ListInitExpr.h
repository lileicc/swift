//
//  ListInitExpr.h
//  swift-project
//
//  Created by Lei Li on 1/16/14.
//
//

#pragma once

#include <vector>
#include <string>
#include "Expr.h"


namespace swift {
  namespace code {
    
    class ListInitExpr: public Expr {
    public:
      
            // For Printer
      void print(printer::Printer* prt);
    private:
      
    };
    
  } /* namespace code */
} /* namespace swift */