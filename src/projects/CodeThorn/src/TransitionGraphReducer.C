
#include "sage3basic.h"
#include "TransitionGraphReducer.h"
#include "TransitionGraph.h"
#include "EState.h"
#include "CodeThornException.h"

#include <unordered_set>
#include <cstdlib>

using namespace CodeThorn;
using namespace std;

TransitionGraphReducer::TransitionGraphReducer(EStateSet* eStateSet, TransitionGraph* stg) :
  _states(eStateSet),
  _stg(stg){
}

void TransitionGraphReducer::reduceStgToStatesSatisfying(function<bool(const EState*)> predicate) {
  if (_stg->size() == 0) {
    return;
  }
  // no in-place reduction because paths in between states that satisfy the predicate might be shared
  TransitionGraph* reducedStg = new TransitionGraph();
  reducedStg->setStartLabel(_stg->getStartLabel());
  reducedStg->setIsPrecise(_stg->isPrecise());
  reducedStg->setIsComplete(_stg->isComplete());
  // init
  list<const EState*> worklist;
  unordered_set<const EState*> visited;
  worklist.push_back(_stg->getStartEState());
  visited.insert(_stg->getStartEState());
  // traverse the entire _stg
  cout<<"STATUS: traversing AST and creating reduced graph ... "<<endl;
  int wl=1;
  int err=system("tput civis"); // turn off cursor
  ROSE_ASSERT(err!=-1);
  while (!worklist.empty()) {
    const EState* current = *worklist.begin();
    ROSE_ASSERT(current);
    worklist.pop_front();
    wl--;
    ROSE_ASSERT(predicate(current) || current == _stg->getStartEState());
    // similar to CTAnalysis's "subSolver"
    list<const EState*> successors = successorsOfStateSatisfying(current, predicate);
    for (list<const EState*>::iterator i=successors.begin(); i!= successors.end(); ++i) {
      if (visited.find(*i) == visited.end()) {
        worklist.push_back(*i);
        visited.insert(*i);
        wl++;
      }
      Edge* newEdge = new Edge(current->label(),EDGE_PATH,(*i)->label());
      reducedStg->add(Transition(current, *newEdge, *i));
    }
    // update in place (extra spaces required)
    cout<<"\rReduction processing: WL:"<<wl<<" Visited: "<<visited.size()<<"    ";
  }
  cout<<endl;
  err=system("tput cnorm"); // turn on cursor
  ROSE_ASSERT(err!=-1);

  // replace old stg (local variable of analyzer, stack frame) with reduced one
  *_stg = *reducedStg;
  // "garbage collection": Remove all states from _states that were bypassed during the reduction
  // (cannot simply replace the set because of potential states in the analyzer's worklist)
  cout<<"STATUS: removing states  ... "<<endl;
  EStateSet::iterator i=_states->begin();
  while (i!=_states->end()) {
    if (visited.find(*i) == visited.end()) {
      i = _states->erase(i);
    } else {
      ++i;
    }
  }
}

list<const EState*> TransitionGraphReducer::successorsOfStateSatisfying(const EState* state, function<bool(const EState*)> predicate) {
  list<const EState*> result;
  // init
  list<const EState*> worklist;
  unordered_set<const EState*> visited;
  worklist.push_back(state);
  visited.insert(state);
  while (!worklist.empty()) {
    const EState* current = *worklist.begin();
    worklist.pop_front();
    ROSE_ASSERT(!predicate(current) || current == state);
    set<const EState*> successors = _stg->succ(current);
    for (set<const EState*>::iterator i=successors.begin(); i!= successors.end(); ++i) {
      if (visited.find(*i) == visited.end()) {
        if (predicate(*i) || *i == _stg->getStartEState()) {
          result.push_back(*i); // stop exploration when predicate is satisfied	
        } else {
          worklist.push_back(*i);
        }
        visited.insert(*i);
      }
    }
  }
  return result;
}

