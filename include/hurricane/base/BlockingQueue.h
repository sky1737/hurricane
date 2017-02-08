/**
 * licensed to the apache software foundation (asf) under one
 * or more contributor license agreements.  see the notice file
 * distributed with this work for additional information
 * regarding copyright ownership.  the asf licenses this file
 * to you under the apache license, version 2.0 (the
 * "license"); you may not use this file except in compliance
 * with the license.  you may obtain a copy of the license at
 *
 * http://www.apache.org/licenses/license-2.0
 *
 * unless required by applicable law or agreed to in writing, software
 * distributed under the license is distributed on an "as is" basis,
 * without warranties or conditions of any kind, either express or implied.
 * see the license for the specific language governing permissions and
 * limitations under the license.
 */

#pragma once

#include <condition_variable>
#include <string>
#include <queue>
#include <chrono>

namespace hurricane {
namespace base {
template <class T>
class BlockingQueue {
public:
    BlockingQueue() ;
    virtual ~BlockingQueue();

    void Push(const T& element);
    bool Pop(T& element, int32_t milliseconds = 0);
    bool Peek(T& element) const;
    bool Empty() const;

    int32_t GetSize() const {
        std::unique_lock<std::mutex> locker(_mutex);

        return _queue.size();
    }

private:
    mutable std::mutex _mutex;
    std::condition_variable _emptyCv;
    std::queue<T> _queue;
};
}
}

#include "hurricane/base/BlockingQueue.tcc"
