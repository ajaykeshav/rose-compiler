// DQ (3/24/2005): This fixes a problem in GNU g++.  test2005_34.C demonstrates code which will compile with EDG and GNU g++
// but when normalized via ROSE will generate legal C++ which compiles with EDG, but not with GNU g++.  The problem code
// is generated by SWIG.  Example code: std::string arg = (std::string) (std::string) (std::string)std::string("");
/*! \brief Handles code which GNU g++ will not compile (current bug in GNU g++)
 */
#ifndef __fixupBackendComp
#define __fixupBackendComp
void fixupforGnuBackendCompiler( SgNode* node );

/*! \brief Recognize and eliminate redundent calls to the same casting operator (or constructor initializer)

    \internal This is a fix for code generated by SWIG, it does not likely to occur in hand written code.
 */
class FixupforGnuBackendCompiler : public SgSimpleProcessing
   {
     public:
      //! Required traversal function
          void visit (SgNode* node);
   };

#endif 

