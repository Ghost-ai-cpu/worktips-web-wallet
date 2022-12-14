//
// Created by mwo on 13/02/17.
//

#pragma once

#include "CurrentBlockchainStatus.h"
#include "tools.h"

#include <map>
#include <utility>

namespace wtipeg
{


class OutputInputIdentificationException: public std::runtime_error
{
    using std::runtime_error::runtime_error;
};


/*
 * This class takes user address, viewkey
 * and searches for outputs in a given tx
 * and possible spendings/inputs.
 *
 * It is the key class for identification of incoming worktips
 * and candidate outcoming wtip for a user in a blockchain and in
 * mempool.
 *
 * searching for our incoming and outgoing wtip has two components.
 *
 * FIRST. to search for the incoming wtip, we use address, viewkey and
 * outputs public key. Its straight forward, as this is what viewkey was
 * designed to do.
 *
 * SECOND. Searching for spendings (i.e., key images) is more difficult,
 * because we dont have spendkey. But what we can do is, we can look for
 * candidate key images. And this can be achieved by checking if any mixin
 * in associated with the given key image, is our output. If it is our output,
 * then we assume its our key image (i.e. we spend this output). Off course
 * this is only
 * assumption as our outputs can be used in key images of others for their
 * mixin purposes. Thus, we sent to the frontend the list of key images
 * that we think are yours, and the frontend, because it has spendkey,
 * can filter out false positives.
 */
class OutputInputIdentification
{

public:

    // define a structure to keep information about found
    // outputs that we can need in later parts.
    struct output_info
    {
        public_key pub_key;
        public_key tx_pub_key;
        uint64_t   amount;
        uint64_t   idx_in_tx;
        string     rtc_outpk;
        string     rtc_mask;
        string     rtc_amount;
        uint64_t   unlock_time;
    };

    // define a structure to keep information about found
    // inputs that we can need in later parts.
    struct input_info
    {
        string key_img;
        uint64_t amount;
        public_key out_pub_key;
    };

    crypto::hash tx_hash;
    crypto::hash tx_prefix_hash;
    vector<public_key> tx_pub_keys;
    int matched_pub_key_index;

    string tx_hash_str;
    string tx_prefix_hash_str;
    string tx_pub_key_str;

    bool tx_is_coinbase;

    bool is_rct;
    uint8_t rct_type;

    uint64_t total_received {0};

    uint64_t mixin_no {0};

    // for each output, in a tx, check if it belongs
    // to the given account of specific address and viewkey

    // public transaction key is combined with our viewkey
    // to create, so called, derived key.

    // stores key derivation and associated tx pub key
    std::vector<std::pair<key_derivation, public_key> > derivations; 

    vector<output_info> identified_outputs;
    vector<input_info>  identified_inputs;

    std::shared_ptr<CurrentBlockchainStatus> current_bc_status;

    // default constructor. Useful for unit tests
    OutputInputIdentification() = default;

    OutputInputIdentification(const address_parse_info* _a,
                              const secret_key* _v,
                              const transaction* _tx,
                              crypto::hash const& _tx_hash,
                              bool is_coinbase,
                              std::shared_ptr<CurrentBlockchainStatus>
                                _current_bc_status);

    /**
     * FIRST step. search for the incoming wtip using address, viewkey and
     * outputs public keys.
     */
    virtual void
    identify_outputs();


    /**
     * SECOND step. search for possible our inputs.
     * We do this by comparing mixin public keys with
     * our known output keys. If a metch is found, we assume
     * that associated input is ours
     *
     * The known_outputs_keys parameter is optional. But when we have
     * it, the identification is faster as we just check mixins public keys
     * if they are in known_outputs_keys.
     *
     * searching without known_outputs_keys is not implemented yet here
     * but it was done for the onion explorer. so later basically just
     * copy and past here.
     *
     * known_outputs_keys is pair of <output public key, output amount>
     *
     */
    virtual void
    identify_inputs(unordered_map<public_key, uint64_t> const&
                    known_outputs_keys);

    virtual string const&
    get_tx_hash_str();

    virtual string const&
    get_tx_prefix_hash_str();

    virtual string const&
    get_tx_pub_key_str();

    virtual uint64_t
    get_mixin_no();

    virtual ~OutputInputIdentification() = default;

private:

    // address and viewkey for this search thread.
    const address_parse_info* address_info;
    const secret_key* viewkey;

    // transaction that is beeing search
    const transaction* tx;
};

}
