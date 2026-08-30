// Copyright (c) 2026-present The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kernel/chainparams.h>
#include <kernel/messagestartchars.h>
#include <util/chaintype.h>

#include <test/util/setup_common.h>

#include <boost/test/unit_test.hpp>

#include <algorithm>
#include <optional>
#include <vector>

//! Bitcoin mainnet's message start, which this fork must not reuse.
static constexpr MessageStartChars BITCOIN_MAIN_MESSAGE_START{0xf9, 0xbe, 0xb4, 0xd9};

BOOST_FIXTURE_TEST_SUITE(chainparams_tests, BasicTestingSetup)

BOOST_AUTO_TEST_CASE(main_message_start_is_not_bitcoin_mainnet)
{
    const auto main_params{CChainParams::Main()};

    // This chain has its own genesis block, so answering to Bitcoin mainnet's message start would
    // let Bitcoin mainnet peers complete a V1 handshake, and would share the BIP324 v2 key
    // derivation salt with them.
    BOOST_CHECK(!std::ranges::equal(main_params->MessageStart(), BITCOIN_MAIN_MESSAGE_START));
    BOOST_CHECK(GetNetworkForMagic(BITCOIN_MAIN_MESSAGE_START) == std::nullopt);
    BOOST_CHECK(GetNetworkForMagic(main_params->MessageStart()) == ChainType::MAIN);

    // The message start is derived from the genesis block hash, so respinning genesis also respins
    // the network identity.
    BOOST_CHECK(std::equal(main_params->MessageStart().begin(), main_params->MessageStart().end(),
                           main_params->GetConsensus().hashGenesisBlock.begin()));
}

BOOST_AUTO_TEST_CASE(message_start_is_unique_per_chain)
{
    std::vector<MessageStartChars> magics{
        CChainParams::Main()->MessageStart(),
        CChainParams::TestNet()->MessageStart(),
        CChainParams::TestNet4()->MessageStart(),
        CChainParams::RegTest({})->MessageStart(),
        CChainParams::SigNet({})->MessageStart(),
    };

    std::ranges::sort(magics);
    BOOST_CHECK(std::ranges::adjacent_find(magics) == magics.end());
}

BOOST_AUTO_TEST_SUITE_END()
