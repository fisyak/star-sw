#ifndef __StarLight_h__
#define __StarLight_h__

#include "StarGenerator/BASE/StarGenerator.h"

///////////////////////////////////////////////////////////////////////////
//
//    Copyright 2010
//
//    This file is part of starlight.
//
//    starlight is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    starlight is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with starlight. If not, see <http://www.gnu.org/licenses/>.
//
///////////////////////////////////////////////////////////////////////////
//
// File and Version Information:
// $Rev::                             $: revision of last commit
// $Author: jwebb $: author of last commit
// $Date: 2012/11/27 22:27:33 $: date of last commit
//
// Description:
//
//
//
///////////////////////////////////////////////////////////////////////////


#ifndef STARLIGHT_H
#define STARLIGHT_H

#define Starlight_VERSION_MAJOR 1
#define Starlight_VERSION_MINOR 0


#include <string>

#include "upcevent.h"
#include "eventchannel.h"


class inputParameters;
class beam;
class beamBeamSystem;


class starlight {

public:
      
	starlight();
	~starlight();
      
	bool init();

	upcEvent produceEvent();
      
	std::string   configFileName() const { return _configFileName;              }
	unsigned long nmbAttempts   () const { return _eventChannel->nmbAttempts(); }
	unsigned long nmbAccepted   () const { return _eventChannel->nmbAccepted(); } 
   
	void setInputParameters(inputParameters* inputParams) { _inputParameters = inputParams; }

private:
      
	bool luminosityTableIsValid() const;

	bool createEventChannel();
      
	inputParameters*   _inputParameters;
	beam*              _beam0;
	beam*              _beam1;
	beamBeamSystem*    _beamSystem;
	eventChannel*      _eventChannel;
	unsigned int       _nmbEventsPerFile;
	unsigned long long _nmbEventsToGenerate;
	std::string        _configFileName;
	std::string        _eventDataFileName;
	std::string        _lumLookUpTableFileName;
	bool               _isInitialised;

};


#endif  // STARLIGHT_H

#include "inputParameters.h"

class StarGenAAEvent;

//class inputParameters;

/**
   \class StarLight
   \brief Interface to the StarLight (c++ version) event generator
   
 */

class StarLight : public StarGenerator
{

 public:
  StarLight( const Char_t *name="STARlight" );
  ~StarLight(){ /* nada */ };

  Int_t Init();
  Int_t Generate();

  //void Set( const Char_t *s ){ mSTARlight -> readString(s); }

  //void const char *GetCVS() const
  //{static const char cvs[]="Tag $Name:  $ $Id: StarLight.h,v 1.4 2014/08/06 11:43:58 jeromel Exp $ built " __DATE__ " " __TIME__ ; return cvs;}

 private:
 protected:
  map<TString,Double_t> ParametersDouble;
  map<TString,Int_t>    ParametersInt;

  inputParameters *_parameters;

  //STARlight::STARlight *mSTARlight;
  starlight *mSTARlight;

  void FillAA( StarGenEvent *event );
  void FillPP( StarGenEvent *event );

public:
  void SetEtaCut( Double_t low, Double_t high );
  void SetPtCut( Double_t low, Double_t high );
  void SetRapidityValues( Double_t high, Int_t bins );
  void SetWValues( Double_t low, Double_t high, Int_t bin );
  void SetProductionMode( Int_t mode );
  void SetProductionPID( Int_t pid );
  void SetBreakupMode( Int_t mode );
  void SetInterference( Double_t percent );
  void SetIncoherence( Double_t percent );
  void SetBFORD( Double_t value );
  void SetInterferencePtValues( Double_t high, Int_t bins );
  void ProcessParameters();

  ClassDef(StarLight,1);

};

#endif
