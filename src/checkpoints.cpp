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
         ( 310000,   uint256("0x00000000000007513c081026a00423f113680bfa49e1d9ddbb5f333176001510") )
         ( 328469,   uint256("0x0af9fdc4c9ea957c1e2daa34336a987cf3058eddcaa76f059cea89ddee52dfd7") )
         ( 341437,   uint256("0x00000000000007701e00a133a072da368c1fc0d3e139e4f65aaa9229e287cbbf") )
         ( 366069,   uint256("0xeec9b2f7557e2716eab8d08e174880be7c8ce44f87c12297bd6e49ed9f9eb8ad") )
         ( 379029,   uint256("0x00000000000027b12e09c7d58b0f682b5866fc980ddbc1e53c8dc050d72d36da") )
         ( 381111,   uint256("0x3b0c06f22f3a7d6983b97bf91930f4f64b8c77c11475eea97789921fc0127848") )
         ( 410776,   uint256("0x000000000000379ade662d04511e3abe027b1c60debb4b8580b4a3ab70324740") )
         ( 425984,   uint256("0x000000000000438d2c4e1a363038cc86635c899926e1175f91bd916b9c3cd225") )
         ( 473560,   uint256("0xd5c4fac1e88e051c2359355082f4f1df153e445e5ad215c2842575e2c3509a60") )
         ( 509101,   uint256("0x85bb7c220c22d29ee93975a8556801db434579f0a05699794307bc270a238439") )
         ( 561832,   uint256("0xdd95b968975f9584ecf4dc89ee58e8087390e3941290b87b628734fd0cf406ea") )
         ( 608469,   uint256("0x0000000000001516c92e96768a66659a145c1341b610da8c85cb0f5011b7baaa") )
         ( 620403,   uint256("0x0000000000003a41b785161f13d9c061746af336b7aeb9b0e6ce8f38927752cd") )
         ( 640035,   uint256("0x000000000000035b096e0b71c1eb34c79a7f0c8409c49d1919ccfd4908a487c1") )
         ( 672401,   uint256("0x0000000000000bab154558d521558d5fe039ec321de4eb8d61e95adf227ae7cd") )
         ( 703740,   uint256("0x0000000000001b50a0d87abe28ec57e53d52f3ea86e75369c2a60f501b3289e0") )
         ( 811883,   uint256("0x00000000000002b4968cf6607f6be066d5062f19ad5e5c72981438d0d3c7d4c1") )
         ( 890249,   uint256("0x0000000000000c26af8b0aa6bc93097357bd18c7eeae9303d360b917daade4ee") )
         ( 900050,   uint256("0xdba7d0d479d1c3ef8fe4b9b74d012a559584b0138fda5cf7f91bb3138c61fde3") )
         ( 1007490,   uint256("0x7177d26b41bbc5cc242c5a1946777df56f44806bf2b1c27a3212728506374b4d") )
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
