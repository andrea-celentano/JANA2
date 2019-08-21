//
// Created by Nathan W Brei on 2019-04-24.
//

#ifndef JANA2_JPROCESSINGTOPOLOGY_H
#define JANA2_JPROCESSINGTOPOLOGY_H

#include <JANA/JArrow.h>
#include <JANA/JMailbox.h>
#include <JANA/JFactorySet.h>
#include <JANA/JEventSourceManager.h>
#include <JANA/JActivable.h>
#include <JANA/JEventProcessor.h>
#include "JPerfMetrics.h"
#include "JEventPool.h"
#include "JProcessorMapping.h"
#include "JComponentSummary.h"

class JApplication;

struct JProcessingTopology : public JActivable {

    enum Status { Inactive, Running, Draining, Finished };

    explicit JProcessingTopology(JApplication* app);
    virtual ~JProcessingTopology();

    JEventSourceManager event_source_manager;
    std::shared_ptr<JEventPool> event_pool;
    std::vector<JFactoryGenerator*> factory_generators;
    std::vector<JEventProcessor*> event_processors;
    JPerfMetrics metrics;
    JComponentSummary component_summary;
    Status status = Inactive; // TODO: Merge this concept with JActivable

    std::vector<JArrow*> arrows;
    std::vector<JArrow*> sources;           // Sources needed for activation
    std::vector<JArrow*> sinks;             // Sinks needed for finished message count
    JProcessorMapping mapping;

    JLogger _logger;

    bool is_active() override;
    void set_active(bool is_active) override;
};


#endif //JANA2_JPROCESSINGTOPOLOGY_H