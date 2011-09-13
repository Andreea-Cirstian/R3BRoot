// -------------------------------------------------------------------------
// -----                      R3BTargetPoint source file                  -----
// -------------------------------------------------------------------------

#include "R3BTargetDigi.h"

#include <iostream>

using std::cout;
using std::endl;
using std::flush;


// -----   Default constructor   -------------------------------------------
R3BTargetDigi::R3BTargetDigi() {
   
     Ss03_smul=0;
     Ss03_kmul=0;
     Ss06_smul=0;
     Ss06_kmul=0;
     
     X0=0.;
     Y0=0.;
     T0=0.;
     
     Estar=0;
     
   
}

R3BTargetDigi::R3BTargetDigi(Double_t ss03_smul,Double_t ss03_kmul,Double_t ss06_smul,Double_t ss06_kmul,
Double_t x0,Double_t y0,Double_t t0,Double_t estar) {


     Ss03_smul=ss03_smul;
     Ss03_kmul=ss03_kmul;
     Ss06_smul=ss06_smul;
     Ss06_kmul=ss06_kmul;
     
     X0=x0;
     Y0=y0;
     T0=t0;
     
     Estar=estar;
     


   
}

// -----   Destructor   ----------------------------------------------------
R3BTargetDigi::~R3BTargetDigi() { }

// -----   Public method Print   -------------------------------------------
void R3BTargetDigi::Print(const Option_t* opt) const {

}
// -------------------------------------------------------------------------

ClassImp(R3BTargetDigi)