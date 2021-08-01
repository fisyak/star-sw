//
// File generated by /afs/rhic.bnl.gov/star/ROOT/5.34.09/.sl53_gcc432/rootdeb/bin/rootcint at Wed Aug 28 18:35:50 2013

// Do NOT change. Changes will be lost next time file is generated
//

#define R__DICTIONARY_FILENAME Dict
#include "RConfig.h" //rootcint 4834
#if !defined(R__ACCESS_IN_SYMBOL)
//Break the privacy of classes -- Disabled for the moment
#define private public
#define protected public
#endif

// Since CINT ignores the std namespace, we need to do so in this file.
namespace std {} using namespace std;
#include "Dict.h"

#include "TClass.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"

// START OF SHADOWS

namespace ROOT {
   namespace Shadow {
   } // of namespace Shadow
} // of namespace ROOT
// END OF SHADOWS

namespace ROOT {
   void HelloSignal_ShowMembers(void *obj, TMemberInspector &R__insp);
   static void HelloSignal_Dictionary();
   static void *new_HelloSignal(void *p = 0);
   static void *newArray_HelloSignal(Long_t size, void *p);
   static void delete_HelloSignal(void *p);
   static void deleteArray_HelloSignal(void *p);
   static void destruct_HelloSignal(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::HelloSignal*)
   {
      ::HelloSignal *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::HelloSignal),0);
      static ::ROOT::TGenericClassInfo 
         instance("HelloSignal", "./HelloSignal.h", 19,
                  typeid(::HelloSignal), DefineBehavior(ptr, ptr),
                  0, &HelloSignal_Dictionary, isa_proxy, 0,
                  sizeof(::HelloSignal) );
      instance.SetNew(&new_HelloSignal);
      instance.SetNewArray(&newArray_HelloSignal);
      instance.SetDelete(&delete_HelloSignal);
      instance.SetDeleteArray(&deleteArray_HelloSignal);
      instance.SetDestructor(&destruct_HelloSignal);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::HelloSignal*)
   {
      return GenerateInitInstanceLocal((::HelloSignal*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::HelloSignal*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static void HelloSignal_Dictionary() {
      ::ROOT::GenerateInitInstanceLocal((const ::HelloSignal*)0x0)->GetClass();
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_HelloSignal(void *p) {
      return  p ? ::new((::ROOT::TOperatorNewHelper*)p) ::HelloSignal : new ::HelloSignal;
   }
   static void *newArray_HelloSignal(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::TOperatorNewHelper*)p) ::HelloSignal[nElements] : new ::HelloSignal[nElements];
   }
   // Wrapper around operator delete
   static void delete_HelloSignal(void *p) {
      delete ((::HelloSignal*)p);
   }
   static void deleteArray_HelloSignal(void *p) {
      delete [] ((::HelloSignal*)p);
   }
   static void destruct_HelloSignal(void *p) {
      typedef ::HelloSignal current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::HelloSignal

/********************************************************
* Dict.cxx
* CAUTION: DON'T CHANGE THIS FILE. THIS FILE IS AUTOMATICALLY GENERATED
*          FROM HEADER FILES LISTED IN G__setup_cpp_environmentXXX().
*          CHANGE THOSE HEADER FILES AND REGENERATE THIS FILE.
********************************************************/

#ifdef G__MEMTEST
#undef malloc
#undef free
#endif

#if defined(__GNUC__) && __GNUC__ >= 4 && ((__GNUC_MINOR__ == 2 && __GNUC_PATCHLEVEL__ >= 1) || (__GNUC_MINOR__ >= 3))
#pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif

extern "C" void G__cpp_reset_tagtableDict();

extern "C" void G__set_cpp_environmentDict() {
  G__cpp_reset_tagtableDict();
}
#include <new>
extern "C" int G__cpp_dllrevDict() { return(30051515); }

/*********************************************************
* Member function Interface Method
*********************************************************/

/* HelloSignal */
static int G__Dict_189_0_3(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
   HelloSignal* p = NULL;
   char* gvp = (char*) G__getgvp();
   switch (libp->paran) {
   case 1:
     //m: 1
     if ((gvp == (char*)G__PVOID) || (gvp == 0)) {
       p = new HelloSignal((QWidget*) G__int(libp->para[0]));
     } else {
       p = new((void*) gvp) HelloSignal((QWidget*) G__int(libp->para[0]));
     }
     break;
   case 0:
     int n = G__getaryconstruct();
     if (n) {
       if ((gvp == (char*)G__PVOID) || (gvp == 0)) {
         p = new HelloSignal[n];
       } else {
         p = new((void*) gvp) HelloSignal[n];
       }
     } else {
       if ((gvp == (char*)G__PVOID) || (gvp == 0)) {
         p = new HelloSignal;
       } else {
         p = new((void*) gvp) HelloSignal;
       }
     }
     break;
   }
   result7->obj.i = (long) p;
   result7->ref = (long) p;
   G__set_tagnum(result7,G__get_linked_tagnum(&G__DictLN_HelloSignal));
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__Dict_189_0_4(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      {
         const TString& obj = ((const HelloSignal*) G__getstructoffset())->Text();
         result7->ref = (long) (&obj);
         result7->obj.i = (long) (&obj);
      }
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__Dict_189_0_5(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      ((HelloSignal*) G__getstructoffset())->Show();
      G__setnull(result7);
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__Dict_189_0_6(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      ((HelloSignal*) G__getstructoffset())->Hide();
      G__setnull(result7);
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__Dict_189_0_7(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      ((HelloSignal*) G__getstructoffset())->NewRootCommand();
      G__setnull(result7);
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__Dict_189_0_8(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      ((HelloSignal*) G__getstructoffset())->SetPrompt((int) G__int(libp->para[0]));
      G__setnull(result7);
   return(1 || funcname || hash || result7 || libp) ;
}

// automatic destructor
typedef HelloSignal G__THelloSignal;
static int G__Dict_189_0_9(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
   char* gvp = (char*) G__getgvp();
   long soff = G__getstructoffset();
   int n = G__getaryconstruct();
   //
   //has_a_delete: 0
   //has_own_delete1arg: 0
   //has_own_delete2arg: 0
   //
   if (!soff) {
     return(1);
   }
   if (n) {
     if (gvp == (char*)G__PVOID) {
       delete[] (HelloSignal*) soff;
     } else {
       G__setgvp((long) G__PVOID);
       for (int i = n - 1; i >= 0; --i) {
         ((HelloSignal*) (soff+(sizeof(HelloSignal)*i)))->~G__THelloSignal();
       }
       G__setgvp((long)gvp);
     }
   } else {
     if (gvp == (char*)G__PVOID) {
       delete (HelloSignal*) soff;
     } else {
       G__setgvp((long) G__PVOID);
       ((HelloSignal*) (soff))->~G__THelloSignal();
       G__setgvp((long)gvp);
     }
   }
   G__setnull(result7);
   return(1 || funcname || hash || result7 || libp) ;
}


/* Setting up global function */

/*********************************************************
* Member function Stub
*********************************************************/

/* HelloSignal */

/*********************************************************
* Global function Stub
*********************************************************/

/*********************************************************
* Get size of pointer to member function
*********************************************************/
class G__Sizep2memfuncDict {
 public:
  G__Sizep2memfuncDict(): p(&G__Sizep2memfuncDict::sizep2memfunc) {}
    size_t sizep2memfunc() { return(sizeof(p)); }
  private:
    size_t (G__Sizep2memfuncDict::*p)();
};

size_t G__get_sizep2memfuncDict()
{
  G__Sizep2memfuncDict a;
  G__setsizep2memfunc((int)a.sizep2memfunc());
  return((size_t)a.sizep2memfunc());
}


/*********************************************************
* virtual base class offset calculation interface
*********************************************************/

   /* Setting up class inheritance */

/*********************************************************
* Inheritance information setup/
*********************************************************/
extern "C" void G__cpp_setup_inheritanceDict() {

   /* Setting up class inheritance */
   if(0==G__getnumbaseclass(G__get_linked_tagnum(&G__DictLN_HelloSignal))) {
     HelloSignal *G__Lderived;
     G__Lderived=(HelloSignal*)0x1000;
     {
       QObject *G__Lpbase=(QObject*)G__Lderived;
       G__inheritance_setup(G__get_linked_tagnum(&G__DictLN_HelloSignal),G__get_linked_tagnum(&G__DictLN_QObject),(long)G__Lpbase-(long)G__Lderived,1,1);
     }
   }
}

/*********************************************************
* typedef information setup/
*********************************************************/
extern "C" void G__cpp_setup_typetableDict() {

   /* Setting up typedef entry */
   G__search_typename2("vector<ROOT::TSchemaHelper>",117,G__get_linked_tagnum(&G__DictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("reverse_iterator<const_iterator>",117,G__get_linked_tagnum(&G__DictLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR),0,G__get_linked_tagnum(&G__DictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR));
   G__setnewtype(-1,NULL,0);
   G__search_typename2("reverse_iterator<iterator>",117,G__get_linked_tagnum(&G__DictLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR),0,G__get_linked_tagnum(&G__DictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR));
   G__setnewtype(-1,NULL,0);
   G__search_typename2("vector<TVirtualArray*>",117,G__get_linked_tagnum(&G__DictLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("reverse_iterator<const_iterator>",117,G__get_linked_tagnum(&G__DictLN_reverse_iteratorlEvectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgRcLcLiteratorgR),0,G__get_linked_tagnum(&G__DictLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR));
   G__setnewtype(-1,NULL,0);
   G__search_typename2("reverse_iterator<iterator>",117,G__get_linked_tagnum(&G__DictLN_reverse_iteratorlEvectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgRcLcLiteratorgR),0,G__get_linked_tagnum(&G__DictLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR));
   G__setnewtype(-1,NULL,0);
}

/*********************************************************
* Data Member information setup/
*********************************************************/

   /* Setting up class,struct,union tag member variable */

   /* HelloSignal */
static void G__setup_memvarHelloSignal(void) {
   G__tag_memvar_setup(G__get_linked_tagnum(&G__DictLN_HelloSignal));
   { HelloSignal *p; p=(HelloSignal*)0x1000; if (p) { }
   G__memvar_setup((void*)0,85,0,0,G__get_linked_tagnum(&G__DictLN_QWidget),-1,-1,4,"fGuiWidget=",0,(char*)NULL);
   G__memvar_setup((void*)0,85,0,0,G__get_linked_tagnum(&G__DictLN_QLineEdit),-1,-1,4,"fLineEdit=",0,(char*)NULL);
   G__memvar_setup((void*)0,85,0,0,G__get_linked_tagnum(&G__DictLN_QLabel),-1,-1,4,"fLabel=",0,(char*)NULL);
   G__memvar_setup((void*)0,117,0,0,G__get_linked_tagnum(&G__DictLN_TString),-1,-1,4,"fLastString=",0,(char*)NULL);
   G__memvar_setup((void*)0,108,0,0,-1,-1,-1,4,"G__virtualinfo=",0,(char*)NULL);
   }
   G__tag_memvar_reset();
}

extern "C" void G__cpp_setup_memvarDict() {
}
/***********************************************************
************************************************************
************************************************************
************************************************************
************************************************************
************************************************************
************************************************************
***********************************************************/

/*********************************************************
* Member function information setup for each class
*********************************************************/
static void G__setup_memfuncHelloSignal(void) {
   /* HelloSignal */
   G__tag_memfunc_setup(G__get_linked_tagnum(&G__DictLN_HelloSignal));
   G__memfunc_setup("HelloSignal",1106,(G__InterfaceMethod) NULL, 105, G__get_linked_tagnum(&G__DictLN_HelloSignal), -1, 0, 1, 1, 4, 0, "u 'HelloSignal' - 11 - -", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("operator=",937,(G__InterfaceMethod) NULL, 121, -1, -1, 0, 1, 1, 4, 0, "u 'HelloSignal' - 11 - -", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("HelloSignal",1106,G__Dict_189_0_3, 105, G__get_linked_tagnum(&G__DictLN_HelloSignal), -1, 0, 1, 1, 1, 0, "U 'QWidget' - 0 '0' parent", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("Text",421,G__Dict_189_0_4, 117, G__get_linked_tagnum(&G__DictLN_TString), -1, 1, 0, 1, 1, 9, "", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("Show",417,G__Dict_189_0_5, 121, -1, -1, 0, 0, 1, 1, 0, "", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("Hide",378,G__Dict_189_0_6, 121, -1, -1, 0, 0, 1, 1, 0, "", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("NewRootCommand",1421,G__Dict_189_0_7, 121, -1, -1, 0, 0, 1, 1, 0, "", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("SetPrompt",942,G__Dict_189_0_8, 121, -1, -1, 0, 1, 1, 1, 0, "i - - 0 - indx", (char*)NULL, (void*) NULL, 0);
   // automatic destructor
   G__memfunc_setup("~HelloSignal", 1232, G__Dict_189_0_9, (int) ('y'), -1, -1, 0, 0, 1, 1, 0, "", (char*) NULL, (void*) NULL, 1);
   G__tag_memfunc_reset();
}


/*********************************************************
* Member function information setup
*********************************************************/
extern "C" void G__cpp_setup_memfuncDict() {
}

/*********************************************************
* Global variable information setup for each class
*********************************************************/
static void G__cpp_setup_global0() {

   /* Setting up global variables */
   G__resetplocal();

}

static void G__cpp_setup_global1() {
   G__memvar_setup((void*)(&gHelloSignal),85,0,0,G__get_linked_tagnum(&G__DictLN_HelloSignal),-1,-1,1,"gHelloSignal=",0,(char*)NULL);

   G__resetglobalenv();
}
extern "C" void G__cpp_setup_globalDict() {
  G__cpp_setup_global0();
  G__cpp_setup_global1();
}

/*********************************************************
* Global function information setup for each class
*********************************************************/
static void G__cpp_setup_func0() {
   G__lastifuncposition();

}

static void G__cpp_setup_func1() {
}

static void G__cpp_setup_func2() {
}

static void G__cpp_setup_func3() {
}

static void G__cpp_setup_func4() {
}

static void G__cpp_setup_func5() {
}

static void G__cpp_setup_func6() {
}

static void G__cpp_setup_func7() {
}

static void G__cpp_setup_func8() {
}

static void G__cpp_setup_func9() {
}

static void G__cpp_setup_func10() {
}

static void G__cpp_setup_func11() {
}

static void G__cpp_setup_func12() {
}

static void G__cpp_setup_func13() {

   G__resetifuncposition();
}

extern "C" void G__cpp_setup_funcDict() {
  G__cpp_setup_func0();
  G__cpp_setup_func1();
  G__cpp_setup_func2();
  G__cpp_setup_func3();
  G__cpp_setup_func4();
  G__cpp_setup_func5();
  G__cpp_setup_func6();
  G__cpp_setup_func7();
  G__cpp_setup_func8();
  G__cpp_setup_func9();
  G__cpp_setup_func10();
  G__cpp_setup_func11();
  G__cpp_setup_func12();
  G__cpp_setup_func13();
}

/*********************************************************
* Class,struct,union,enum tag information setup
*********************************************************/
/* Setup class/struct taginfo */
G__linked_taginfo G__DictLN_TString = { "TString" , 99 , -1 };
G__linked_taginfo G__DictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR = { "vector<ROOT::TSchemaHelper,allocator<ROOT::TSchemaHelper> >" , 99 , -1 };
G__linked_taginfo G__DictLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR = { "reverse_iterator<vector<ROOT::TSchemaHelper,allocator<ROOT::TSchemaHelper> >::iterator>" , 99 , -1 };
G__linked_taginfo G__DictLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR = { "vector<TVirtualArray*,allocator<TVirtualArray*> >" , 99 , -1 };
G__linked_taginfo G__DictLN_reverse_iteratorlEvectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgRcLcLiteratorgR = { "reverse_iterator<vector<TVirtualArray*,allocator<TVirtualArray*> >::iterator>" , 99 , -1 };
G__linked_taginfo G__DictLN_QObject = { "QObject" , 99 , -1 };
G__linked_taginfo G__DictLN_QWidget = { "QWidget" , 99 , -1 };
G__linked_taginfo G__DictLN_QLineEdit = { "QLineEdit" , 99 , -1 };
G__linked_taginfo G__DictLN_QLabel = { "QLabel" , 99 , -1 };
G__linked_taginfo G__DictLN_HelloSignal = { "HelloSignal" , 99 , -1 };

/* Reset class/struct taginfo */
extern "C" void G__cpp_reset_tagtableDict() {
  G__DictLN_TString.tagnum = -1 ;
  G__DictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR.tagnum = -1 ;
  G__DictLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR.tagnum = -1 ;
  G__DictLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR.tagnum = -1 ;
  G__DictLN_reverse_iteratorlEvectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgRcLcLiteratorgR.tagnum = -1 ;
  G__DictLN_QObject.tagnum = -1 ;
  G__DictLN_QWidget.tagnum = -1 ;
  G__DictLN_QLineEdit.tagnum = -1 ;
  G__DictLN_QLabel.tagnum = -1 ;
  G__DictLN_HelloSignal.tagnum = -1 ;
}


extern "C" void G__cpp_setup_tagtableDict() {

   /* Setting up class,struct,union tag entry */
   G__get_linked_tagnum_fwd(&G__DictLN_TString);
   G__get_linked_tagnum_fwd(&G__DictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR);
   G__get_linked_tagnum_fwd(&G__DictLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR);
   G__get_linked_tagnum_fwd(&G__DictLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR);
   G__get_linked_tagnum_fwd(&G__DictLN_reverse_iteratorlEvectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgRcLcLiteratorgR);
   G__get_linked_tagnum_fwd(&G__DictLN_QObject);
   G__get_linked_tagnum_fwd(&G__DictLN_QWidget);
   G__get_linked_tagnum_fwd(&G__DictLN_QLineEdit);
   G__get_linked_tagnum_fwd(&G__DictLN_QLabel);
   G__tagtable_setup(G__get_linked_tagnum_fwd(&G__DictLN_HelloSignal),sizeof(HelloSignal),-1,3840,(char*)NULL,G__setup_memvarHelloSignal,G__setup_memfuncHelloSignal);
}
extern "C" void G__cpp_setupDict(void) {
  G__check_setup_version(30051515,"G__cpp_setupDict()");
  G__set_cpp_environmentDict();
  G__cpp_setup_tagtableDict();

  G__cpp_setup_inheritanceDict();

  G__cpp_setup_typetableDict();

  G__cpp_setup_memvarDict();

  G__cpp_setup_memfuncDict();
  G__cpp_setup_globalDict();
  G__cpp_setup_funcDict();

   if(0==G__getsizep2memfunc()) G__get_sizep2memfuncDict();
  return;
}
class G__cpp_setup_initDict {
  public:
    G__cpp_setup_initDict() { G__add_setup_func("Dict",(G__incsetup)(&G__cpp_setupDict)); G__call_setup_funcs(); }
   ~G__cpp_setup_initDict() { G__remove_setup_func("Dict"); }
};
G__cpp_setup_initDict G__cpp_setup_initializerDict;
