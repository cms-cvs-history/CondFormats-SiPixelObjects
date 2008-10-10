// SiPixelQuality.h
//
// class definition to hold a list of disabled pixel modules
//
// M. Eads
// Apr 2008

#ifndef SiPixelQuality_H
#define SiPixelQuality_H

#include <vector>
#include <utility>

#include "DataFormats/DetId/interface/DetId.h"

class SiPixelQuality {

 public:
  typedef struct disabledModuleType { 
    uint32_t DetID;  
    int      errorType;
    unsigned short BadRocs;
  };


  class BadComponentStrictWeakOrdering{
  public:
    bool operator() (const disabledModuleType& p,const uint32_t i) const {return p.DetID < i;}
  };



  SiPixelQuality() : theDisabledModules(0) {;}

  // constructor from a list of disabled modules
  SiPixelQuality(std::vector<disabledModuleType> & disabledModules) : theDisabledModules(disabledModules) {;}

  virtual ~SiPixelQuality() {;}

  // set the list of disabled modules (current list is lost)
  void setDisabledModuleList(std::vector<disabledModuleType> & disabledModules) 
  { theDisabledModules = disabledModules; }

  // add a single module to the vector of disabled modules
  void addDisabledModule(disabledModuleType module)
  { theDisabledModules.push_back(module); }

  // add a vector of modules to the vector of disabled modules
  void addDisabledModule(std::vector<disabledModuleType> & idVector);

  // remove disabled module from the list
  // returns false if id not in disable list, true otherwise
  //  bool removeDisabledModule(const disabledModuleType & module);
  bool removeDisabledModule(const uint32_t & detid);


//--------------- Interface for the user -----------------//
//------- designed to match SiStripQuality methods ----------//



  bool IsModuleBad(const uint32_t & detid) const;  //returns True if module disabled
  bool IsModuleUsable(const uint32_t& detid) const;  //returns True if module NOT disabled
  bool IsRocBad(const uint32_t& detid, const short& rocNb) const;  //returns True if ROC is disabled
  short getBadRocs(const uint32_t& detid) const;  //returns bad Rocs for given DetId
  const std::vector<disabledModuleType> getBadComponentList() const  //returns list of disabled modules/ROCs
    { return theDisabledModules; }


 private:
  std::vector<disabledModuleType> theDisabledModules;

}; // class SiPixelQuality










#endif
