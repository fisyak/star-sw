#ifndef __StarLogicalFilter__
#define __StarLogicalFilter__

#include "StarFilterMaker.h"
#include <string>

/**!

   \class StarLogicalFilter

   Purpose:

   Allows the user to use multiple filters in combination with each other.
   
   Say that you have four filters A, B, C and D that you want to combine as
   follows:
   
   result = (A + B) * (C + D)

   If filter condition A or B fires, and filter condition C or D fires,
   then the event is accepted.

   // Setup and configure the four concrete filter makers
   auto* A = new SomeFilter("A");
   auto* B = new SomeOtherFilter("B");
   auto* C = new YetAnotherFilter("C");
   auto* D = new YouGuessedIt("D");

   StarLogicalFilter* result = new StarLogicalFilter("result");
   result->SetOperator("AND");

   StarLogicalFilter* AorB = new StarLogicalFilter("AorB");
   AorB->SetOperator("OR");
   AorB->AddFilter(A);
   AorB->AddFilter(B);

   StarLogicalFilter* CorD = new StarLogicalFilter("CorD");
   CorD->SetOperator("OR");
   CorD->AddFilter(C);
   CorD->AddFilter(D);

 */

class StarLogicalFilter : public StarFilterMaker {

 public:
  StarLogicalFilter( const char* name="" );
  virtual ~StarLogicalFilter(){ /* nada */ };
  
  virtual int Filter( StarGenEvent* event=0 );
  void AddFilter( StarFilterMaker* f ){ 
    mFilters.push_back(f); 
    AddMaker(f); 
    f->SetActive(false);
  }

  // Sets the mode of operation to logical AND or logical OR.  This
  // is a convienence method which uses the StMaker::SetAttr method
  // to define the operation, and safeguards against invalid values.
  void SetOperator( const char* op="AND" );

 private:
  std::vector< StarFilterMaker* > mFilters;

  ClassDef(StarLogicalFilter,0);

};

#endif
