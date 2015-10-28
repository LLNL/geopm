/*
 * Copyright (c) 2015, Intel Corporation
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in
 *       the documentation and/or other materials provided with the
 *       distribution.
 *
 *     * Neither the name of Intel Corporation nor the names of its
 *       contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY LOG OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef PROFILE_HPP_INCLUDE
#define PROFILE_HPP_INCLUDE

#include <stdint.h>
#include <string>

#include "SharedMemory.hpp"
#include "LockingHashTable.hpp"

namespace geopm
{
    class Profile
    {
        public:
            Profile(const std::string name, int sample_reduce, size_t table_size, const std::string shm_key);
            Profile(const std::string name, int sample_reduce, size_t table_size);
            virtual ~Profile();
            uint64_t region(const std::string region_name, long policy_hint);
            void enter(uint64_t region_id);
            void exit(uint64_t region_id);
            void progress(uint64_t region_id, double fraction);
            void outer_sync(void);
            void sample(uint64_t region_id);
            void enable(const std::string feature_name);
            void disable(const std::string feature_name);
            void print(FILE *fid, int depth) const;
        protected:
            std::string m_name;
            int m_sample_reduce;
            uint64_t m_curr_region_id;
            struct timespec m_enter_time;
            int m_num_enter;
            int m_num_progress;
            double m_progress;
            void *m_table_buffer;
            SharedMemoryUser *m_shmem;
            LockingHashTable<struct geopm_sample_message_s> *m_table;
    };
}

#endif
