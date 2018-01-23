//
//    File: JQueueSet.h
// Created: Wed Oct 11 22:51:32 EDT 2017
// Creator: davidl (on Darwin harriet 15.6.0 i386)
//
// ------ Last repository commit info -----
// [ Date ]
// [ Author ]
// [ Source ]
// [ Revision ]
//
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
// Jefferson Science Associates LLC Copyright Notice:  
// Copyright 251 2014 Jefferson Science Associates LLC All Rights Reserved. Redistribution
// and use in source and binary forms, with or without modification, are permitted as a
// licensed user provided that the following conditions are met:  
// 1. Redistributions of source code must retain the above copyright notice, this
//    list of conditions and the following disclaimer. 
// 2. Redistributions in binary form must reproduce the above copyright notice, this
//    list of conditions and the following disclaimer in the documentation and/or other
//    materials provided with the distribution.  
// 3. The name of the author may not be used to endorse or promote products derived
//    from this software without specific prior written permission.  
// This material resulted from work developed under a United States Government Contract.
// The Government retains a paid-up, nonexclusive, irrevocable worldwide license in such
// copyrighted data to reproduce, distribute copies to the public, prepare derivative works,
// perform publicly and display publicly and to permit others to do so.   
// THIS SOFTWARE IS PROVIDED BY JEFFERSON SCIENCE ASSOCIATES LLC "AS IS" AND ANY EXPRESS
// OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL
// JEFFERSON SCIENCE ASSOCIATES, LLC OR THE U.S. GOVERNMENT BE LIABLE TO LICENSEE OR ANY
// THIRD PARTES FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
// OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
// LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
// OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
//
// Description:
//
//
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
#ifndef _JQueueSet_h_
#define _JQueueSet_h_

#include <map>
#include <vector>
#include <string>

#include "JQueueInterface.h"

class JQueueSet
{
	//If you want individual queues to skip-until-buffered (e.g. output) or skip-if-buffered (e.g. input): Is responsibility of individual JQueue

	public:

		//In order of execution priority. For example:
		//Could be I/O bound:
			//If not enough events buffered (in queue) from current input, buffer another event
			//If too many events in output buffers (queues), execute output tasks
		//Otherwise:
			//Process tasks in user-provided queues first (finish analyzing an open event)
			//Process events (Execute all processors on new event)
			//Process remaining tasks in output queue

		//How is this implemented?:
			//First loop through queues calling CheckBuffer()
		//Difference between Input & Events
		//If not disentangling: None really
		//Want to distinguish between reading in events from file, and processing events
		//If event queue size < N, get more events from file
		//OR:
		//If disentangle queue size < N, get more events from file. If event queue size < M, disentangle
		enum class JQueueType { Output = 0, SubTasks, Events };

		JQueueInterface* GetQueue(JQueueType aQueueType, const std::string& aName = "") const;

		void SetQueues(JQueueType aQueueType, const std::vector<JQueueInterface*>& aQueues);
		void AddQueue(JQueueType aQueueType, JQueueInterface* aQueue);
		void RemoveQueues(JQueueType aQueueType);
		void RemoveQueues(void);

		std::pair<JQueueType, JTaskBase*> GetTask(void) const;
		JTaskBase* GetTask(JQueueType aQueueType, const std::string& aQueueName) const;

	private:
		std::map<JQueueType, std::vector<JQueueInterface*>> mQueues;
};

#endif // _JQueueSet_h_