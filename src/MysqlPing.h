//
// Created by mwo on 12/07/18.
//

#ifndef WORKTIPS_MYSQLPING_H
#define WORKTIPS_MYSQLPING_H

#include "MySqlConnector.h"

#include <memory>
#include <thread>
#include <atomic>

namespace wtipeg
{

class MysqlPing
{
public:

    enum class StopReason {NotYetStopped, PingFailed, PointerExpired};

    MysqlPing(std::shared_ptr<MySqlConnector> _conn, uint64_t _ping_time = 300);

    void operator()();
    void stop() {keep_looping = false;}

    uint64_t get_counter() const {return counter;}
    StopReason get_stop_reason() const {return why_stoped;};

    MysqlPing(MysqlPing&&) = default;
    MysqlPing& operator=(MysqlPing&&) = default;

private:
    std::weak_ptr<MySqlConnector> conn;
    uint64_t ping_time; // in seconds
    atomic<bool> keep_looping {true};
    atomic<uint64_t> counter {0};
    atomic<StopReason> why_stoped {StopReason::NotYetStopped};
};
}

#endif //WORKTIPS_MYSQLPING_H
