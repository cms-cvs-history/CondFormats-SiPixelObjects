#ifndef CondFormats_SiPixelObjects_SiPixelGainCalibrationForHLT_h
#define CondFormats_SiPixelObjects_SiPixelGainCalibrationForHLT_h
// -*- C++ -*-
//
// Package:    SiPixelObjects
// Class:      SiPixelGainCalibrationForHLT
// 
/**\class SiPixelGainCalibrationForHLT SiPixelGainCalibrationForHLT.h CondFormats/SiPixelObjects/src/SiPixelGainCalibrationForHLT.cc

 Description: Gain calibration object for the Silicon Pixel detector for use at HLT.  Stores only average gain and average pedestal per column.

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Vincenzo Chiochia
//         Created:  Tue 8 12:31:25 CEST 2007
//         Modified: Evan Friis
//         Modified: Freya Blekman
// $Id: SiPixelGainCalibrationForHLT.h,v 1.2 2008/04/15 14:39:03 friis Exp $
//
//
#include<vector>
#include<map>
#include<iostream>
#include<boost/cstdint.hpp>

class SiPixelGainCalibrationForHLT {

 public:

  struct DecodingStructure{  
    unsigned int gain  :8;
    unsigned int ped   :8;
  };
  
  struct DetRegistry{
    uint32_t detid;
    uint32_t ibegin;
    uint32_t iend;
  };
  
  class StrictWeakOrdering{
  public:
    bool operator() (const DetRegistry& p,const uint32_t& i) const {return p.detid < i;}
  };
  
  typedef std::vector<char>::const_iterator                ContainerIterator;  
  typedef std::pair<ContainerIterator, ContainerIterator>  Range;      
  typedef std::vector<DetRegistry>                         Registry;
  typedef Registry::const_iterator                         RegistryIterator;
  
  // Constructors
  SiPixelGainCalibrationForHLT();
  SiPixelGainCalibrationForHLT(float minPed, float maxPed, float minGain, float maxGain);
  virtual ~SiPixelGainCalibrationForHLT(){};

  bool  put(const uint32_t& detID,Range input);
  const Range getRange(const uint32_t& detID) const;
  void  getDetIds(std::vector<uint32_t>& DetIds_) const;
  const int getNCols(const uint32_t& detID) const;
  const std::pair<const Range, const int> getRangeAndNCols(const uint32_t& detID) const;

  // Set and get public methods
  void  setData(float pedLowRows, float gainLowRows, float pedHighRows, float gainHighRows, std::vector<char>& vped);
  void setDead(bool lowRows, bool highRows, std::vector<char>& vped);

  float getPed   (const int& col, const int& row, const Range& range, const int& nCols,  bool & isdead) const;
  float getGain  (const int& col, const int& row, const Range& range, const int& nCols,  bool & isdead) const;
  bool isDead(const int& col, const int& row, const Range& range, const int& nCols) const;

  private:

  float   encodeGain(const float& gain);
  float   encodePed (const float& ped);
  float   decodeGain(unsigned int gain) const;
  float   decodePed (unsigned int ped) const;

  std::vector<char> v_pedestals; //@@@ blob streaming doesn't work with uint16_t and with classes
  std::vector<DetRegistry> indexes;
  float  minPed_, maxPed_, minGain_, maxGain_;

  float nBins_;
  unsigned int deadVal_;
};
    
#endif