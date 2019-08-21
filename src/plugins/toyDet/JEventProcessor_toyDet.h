//
//    File: toyDet/JEventProcessor_toyDet.h
// Created: Wed Apr 24 16:04:14 EDT 2019
// Creator: pooser (on Linux rudy.jlab.org 3.10.0-957.10.1.el7.x86_64 x86_64)
//
// ------ Last repository commit info -----
// [ Date ]
// [ Author ]
// [ Source ]
// [ Revision ]

#ifndef _JEventProcessor_toyDet_h_
#define _JEventProcessor_toyDet_h_

#include <mutex>

#include <JANA/JEventProcessor.h>
#include <JANA/JEvent.h>

#include <TFile.h>
#include <TTree.h>

using namespace std;

//////////////////////////////////////////////////////////////////////////////////////////////////
/// Brief class description.
///
/// Detailed class description.
//////////////////////////////////////////////////////////////////////////////////////////////////
class JEventProcessor_toyDet : public JEventProcessor{

 public:

  JEventProcessor_toyDet();
  virtual ~JEventProcessor_toyDet();

  virtual void Init(void);
  virtual void Process(const std::shared_ptr<const JEvent>& aEvent);
  virtual void Finish(void);

 protected:


 private:

  // mutex objects
  mutex fillMutex;

  // root objects
  TFile *outFile;
  TTree *eventTree, *sampleTree;

  // user defined data types
  // TODO: put these somewhere that make sense ('global' parameter?)
  static const uint numChans   = 80;
  static const uint numSamples = 1024;

  uint chan, event, nentries;
  uint tdcSample, adcSample;

};

#endif // _JEventProcessor_toyDet_h_

