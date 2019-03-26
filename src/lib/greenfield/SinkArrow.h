//
// Created by nbrei on 3/25/19.
//

#ifndef GREENFIELD_SINKARROW_H
#define GREENFIELD_SINKARROW_H

#include <greenfield/Arrow.h>
#include <greenfield/Components.h>

namespace greenfield {

template<typename T>
class SinkArrow : public Arrow {

private:
    Sink<T> & _sink;
    Queue<T> * _input_queue;
    std::vector<T> _chunk_buffer;
    bool _is_initialized = false;

public:
    SinkArrow(std::string name, size_t index, Sink<T>& sink, Queue<T>* input_queue)
        : Arrow(name, index, false)
        , _sink(sink)
        , _input_queue(input_queue) {

        _input_queues.push_back(input_queue);
    };

    StreamStatus execute() {
        if (is_finished()) {
            return StreamStatus::Finished;
        }
        if (!_is_initialized) {
            _sink.initialize();
            _chunk_buffer.reserve(get_chunksize());
            _is_initialized = true;
        }
        StreamStatus result = _input_queue->pop(_chunk_buffer, get_chunksize());
        for (T item : _chunk_buffer) {
            _sink.outprocess(item);
        }
        _chunk_buffer.clear();
        if (result == StreamStatus::Finished) {
            set_finished(true);
            _sink.finalize();
        }
        return result;
    }
};

} // namespace greenfield

#endif //GREENFIELD_SINKARROW_H