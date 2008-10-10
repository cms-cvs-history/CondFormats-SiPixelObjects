// SiPixelQuality.cc
//
// class implementation to hold a list of disabled pixel modules
//
// M. Eads
// Apr 2008

#include "CondFormats/SiPixelObjects/interface/SiPixelQuality.h"

#include <algorithm>

// add a list of modules to the vector of disabled modules
void SiPixelQuality::addDisabledModule(std::vector<SiPixelQuality::disabledModuleType> & idVector) {
  theDisabledModules.insert(theDisabledModules.end(),
			    idVector.begin(),
			    idVector.end());

} 

// void SiPixelQuality::addDisabledModule(std::vector<SiPixelQuality::disabledModuleType> idVector)
// remove disabled module from the list
// returns false if id not in disable list, true otherwise


// bool SiPixelQuality::removeDisabledModule(const SiPixelQuality::disabledModuleType &module) {
//   std::vector<SiPixelQuality::disabledModuleType>::iterator iter = find(
// 										theDisabledModules.begin(),
// 										theDisabledModules.end(),
// 										module
// 										);
//   if (iter == theDisabledModules.end())
//     return false;
  
//   theDisabledModules.erase(iter);
//   return true;

// } 

bool SiPixelQuality::removeDisabledModule(const uint32_t & detid){

  return true;
}
// bool SiPixelQuality::removeDisabledModule(disabledModuleType module)
// method to return true if the specified module is in the list
// of disabled modules

//bool SiPixelQuality::isModuleDisabled(SiPixelQuality::disabledModuleType module) {
//  std::vector<SiPixelQuality::disabledModuleType>::const_iterator iter = find(theDisabledModules.begin(),
//						     theDisabledModules.end(),
//						     module);
//  return iter != theDisabledModules.end();




bool SiPixelQuality::IsModuleUsable(const uint32_t& detid) const {
  std::vector<disabledModuleType>::const_iterator iter = std::lower_bound(theDisabledModules.begin(),theDisabledModules.end(),detid,SiPixelQuality::BadComponentStrictWeakOrdering());
  if (iter!=theDisabledModules.end() && iter->DetID==detid)
      return false;
  return true;
}


 bool SiPixelQuality::IsModuleBad(const uint32_t & detid) const {
  std::vector<disabledModuleType>::const_iterator iter = std::lower_bound(theDisabledModules.begin(),theDisabledModules.end(),detid,SiPixelQuality::BadComponentStrictWeakOrdering());
  if (iter!=theDisabledModules.end() && iter->DetID==detid)
    //    return iter->BadModule;
     return true;
  return false;
}



bool SiPixelQuality::IsRocBad(const uint32_t& detid, const short& rocNb) const {
    return true; 
  }


short SiPixelQuality::getBadRocs(const uint32_t& detid) const{
  return 1; 
}


