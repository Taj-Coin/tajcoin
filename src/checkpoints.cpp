// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <boost/assign/list_of.hpp> // for 'map_list_of()'
#include <boost/foreach.hpp>

#include "checkpoints.h"

#include "txdb.h"
#include "main.h"
#include "uint256.h"


static const int nCheckpointSpan = 500;

namespace Checkpoints
{
    typedef std::map<int, uint256> MapCheckpoints;

    //
    // What makes a good checkpoint block?
    // + Is surrounded by blocks with reasonable timestamps
    //   (no blocks before with a timestamp after, none after with
    //    timestamp before)
    // + Contains no strange transactions
    //
    static MapCheckpoints mapCheckpoints =
        boost::assign::map_list_of
         ( 0,   uint256("0x00000b414afcc2b242531999ae4cc5e7279eaa1508aa72cb289cc175ebb1db2b") )
         ( 33333,   uint256("0x756b15d7f5253a36329eb4bae79445ad7fab8acde2b3149fd8db731732477d69") )
         ( 66666,   uint256("0x0000000000033356d0b99e4844de6f36d361db02ed1cc5b01884e07ab7b9569a") )
         ( 99999,   uint256("0x00000000001edc265fffa6e5bc8be9baed105eb5ddd00b79e396bb19f38b666d") )
         ( 133333,   uint256("0xfeb23bcaa052267858808381492ff4e39d7219678ac307aa2bddb84213e64f42") )
         ( 166666,   uint256("0x00000000000042841340d9df5806d095506c1bcd224e6309eb4b774f43a74d44") )
         ( 199999,   uint256("0x00000000000067318b08f3582dda20abf254863ebe8be6db0edfd13beee68867 ") )
         ( 233333,   uint256("0x000000000001eb8f242e54a049501a1dc3cb7fe6bdfb0831237dc302d5c90368") )
         ( 280000,   uint256("0x000000000000078b75c3f63acaa95affa5e2fed7668a8aae4ccbc7fe4112cd3c") )
    ;


    // TestNet has no checkpoints
    static MapCheckpoints mapCheckpointsTestnet;

    bool CheckHardened(int nHeight, const uint256& hash)
    {
        MapCheckpoints& checkpoints = (TestNet() ? mapCheckpointsTestnet : mapCheckpoints);

        MapCheckpoints::const_iterator i = checkpoints.find(nHeight);
        if (i == checkpoints.end()) return true;
        return hash == i->second;
    }

    int GetTotalBlocksEstimate()
    {
        MapCheckpoints& checkpoints = (TestNet() ? mapCheckpointsTestnet : mapCheckpoints);

        if (checkpoints.empty())
            return 0;
        return checkpoints.rbegin()->first;
    }

    CBlockIndex* GetLastCheckpoint(const std::map<uint256, CBlockIndex*>& mapBlockIndex)
    {
        MapCheckpoints& checkpoints = (TestNet() ? mapCheckpointsTestnet : mapCheckpoints);

        BOOST_REVERSE_FOREACH(const MapCheckpoints::value_type& i, checkpoints)
        {
            const uint256& hash = i.second;
            std::map<uint256, CBlockIndex*>::const_iterator t = mapBlockIndex.find(hash);
            if (t != mapBlockIndex.end())
                return t->second;
        }
        return NULL;
    }

    // Automatically select a suitable sync-checkpoint
    const CBlockIndex* AutoSelectSyncCheckpoint()
    {
        const CBlockIndex *pindex = pindexBest;
        // Search backward for a block within max span and maturity window
        while (pindex->pprev && pindex->nHeight + nCheckpointSpan > pindexBest->nHeight)
            pindex = pindex->pprev;
        return pindex;
    }

    // Check against synchronized checkpoint
    bool CheckSync(int nHeight)
    {
        const CBlockIndex* pindexSync = AutoSelectSyncCheckpoint();

        if (nHeight <= pindexSync->nHeight)
            return false;
        return true;
    }
}
