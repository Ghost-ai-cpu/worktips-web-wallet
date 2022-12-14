//
// Created by mwo on 7/01/17.
//

#include "ssqlses.h"


namespace wtipeg
{


ostream& operator<< (std::ostream& os, const Table& data)
{
    os << data.table_name() << ": " << data.to_json().dump() << '\n';
    return os;
};

json
WtipAccount::to_json() const
{
    json j {{"id"                     , id.data},
            {"address"                , address},
            {"viewkey"                , viewkey},
            {"scanned_block_height"   , scanned_block_height},
            {"scanned_block_timestamp", static_cast<uint64_t>(scanned_block_timestamp)},
            {"start_height"           , start_height}
    };

    return j;
}

json
WtipTransaction::to_json() const
{
    json j {{"id"                  , id.data},
            {"hash"                , hash},
            {"prefix_hash"         , prefix_hash},
            {"tx_pub_key"          , tx_pub_key},
            {"account_id"          , account_id},
            {"total_received"      , total_received},
            {"total_sent"          , total_sent},
            {"height"              , height},
            {"payment_id"          , payment_id},
            {"unlock_time"         , unlock_time},
            {"coinbase"            , bool {coinbase}},
            {"is_rct"              , bool {is_rct}},
            {"rct_type"            , rct_type},
            {"spendable"           , bool {spendable}},
            {"mixin"               , mixin},
            {"timestamp"           , static_cast<uint64_t>(timestamp)}
    };

    return j;
}

DateTime
WtipTransaction::timestamp_to_DateTime(time_t timestamp)
{

    // to avoid potentially inserting a time before 1970-01-01 -- 00:00
    // (DateTime constructor uses localtime and so if the time passed
    // is 0 and the time zone is west of UTC then it errors)
    if (timestamp < 24 * 60 * 60)
    {
        timestamp = 24 * 60 * 60;
    }
    return DateTime(timestamp);
}

ostream& operator<< (std::ostream& os, const WtipTransaction& acc)
{
    os << "WtipTransactions: " << acc.to_json().dump() << '\n';
    return os;
};


json
WtipOutput::to_json() const
{
    json j {{"id"                  , id.data},
            {"account_id"          , account_id},
            {"tx_id"               , tx_id},
            {"out_pub_key"         , out_pub_key},
            {"tx_pub_key"          , tx_pub_key},
            {"amount"              , amount},
            {"global_index"        , global_index},
            {"out_index"           , out_index},
            {"mixin"               , mixin},
            {"timestamp"           , static_cast<uint64_t>(timestamp)}
    };

    return j;
}


ostream& operator<< (std::ostream& os, const WtipOutput& out) {
    os << "WtipOutputs: " << out.to_json().dump() << '\n';
    return os;
};


json
WtipInput::to_json() const
{
    json j {{"id"                  , id.data},
            {"account_id"          , account_id},
            {"tx_id"               , tx_id},
            {"output_id"           , output_id},
            {"key_image"           , key_image},
            {"amount"              , amount},
            {"timestamp"           , static_cast<uint64_t>(timestamp)}
    };

    return j;
}



ostream& operator<< (std::ostream& os, const WtipInput& out)
{
    os << "WtipInput: " << out.to_json().dump() << '\n';
    return os;
};

json
WtipPayment::to_json() const
{
    json j {{"id"               , id.data},
            {"account_id"       , account_id},
            {"payment_id"       , payment_id},
            {"tx_hash"          , tx_hash},
            {"request_fulfilled", bool {request_fulfilled}},
            {"import_fee"       , import_fee},
            {"payment_address"  , payment_address},
    };

    return j;
}


ostream& operator<< (std::ostream& os, const WtipPayment& out) {
    os << "WtipPayment: " << out.to_json().dump() << '\n';
    return os;
};



}
