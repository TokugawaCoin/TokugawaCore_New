// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2018 The PIVX developers
// Copyright (c) 2019 The Tokugawa developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "libzerocoin/Params.h"
#include "chainparams.h"
#include "random.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

using namespace std;
using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

/**
 * Main network
 */

//! Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress>& vSeedsOut, const SeedSpec6* data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7 * 24 * 60 * 60;
    for (unsigned int i = 0; i < count; i++) {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

//   What makes a good checkpoint block?
// + Is surrounded by blocks with reasonable timestamps
//   (no blocks before with a timestamp after, none after with
//    timestamp before)
// + Contains no strange transactions
static Checkpoints::MapCheckpoints mapCheckpoints =
    boost::assign::map_list_of
    (0, uint256("0x000001c46884d82e562759882dc44dc6b0721d62152416b9f57d6db1ef195fa5"))
	(1, uint256("0x00000f058a733423b9a1279c336ad342b2439db345fde2429b5f7e7ef4ebd89b"))
	(87, uint256("0x0000007f398aa2dde459c3aa64cabe7c5cf7ed1d62fa903858bf12ebc9b7b019"))
	(724, uint256("0x6a47ce44b144183ec3da0a2f7eae332830e8c7632b1143988c1da8423e3143ca"))
	(1966, uint256("0x4febb4a2de89072969b9b2317025bf87e5f2233a7332c3d6f3e30a929e81d9ea"))
	(2408, uint256("0xeb0f587eba1bad7cc60019c553307b2dc21c9f2a8904a45577976a57193fefdd"))
	(2923, uint256("0x74e2cde3c2dd2d0085bd7205c44c471649ed9bf49d0fcb9cec531223caf1924c"))
	(3356, uint256("0x92d19bb5dad7030deb8e43af7ac23a0220608df76e1656c3b59690a346d299de"))
	(4698, uint256("0xc82b0ed9a2e9ee5ef44526f972df0e3dddefc0692c5da2d1797027cfa17559da"))
    (5931, uint256("0xbb7b66bc62403d289267e2fb8ed3d6abc75fc99befab3be59710e7ebe0e57a69"))
    (6030, uint256("0x3d47b3d438a24dc22262869749ad0c72b85b8a15ce25fc8e34067a26dc241670"))
	(23497, uint256("0x0df489b3de5870d808ddbd911ca0ad2a3e48f0ff8d997ce431bc3c070118e363"))
	(48206, uint256("0xa99c45a8bb1aa291fc9689bbcb1c921e82b412afd605a2c3aaf28feebc720072"))
	(71237, uint256("0xedafca6f30e12fa8e7aab1bd18b78e7839f71205780ba64563d797f3f999f27a"))
	(89907, uint256("0x3ea8a340bacd71213ddfad6e0c9cd43ed118116c2620e5c3c7fdb377fa2b3ce7"))
	;
static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
	1552369491, // * UNIX timestamp of last checkpoint block
    11822,    // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the SetBestChain debug.log lines)
    2365        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of(0, uint256("0x001"));
static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1740710,
    0,
    250};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of(0, uint256("0x001"));
static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1546927200,
    0,
    100};

libzerocoin::ZerocoinParams* CChainParams::Zerocoin_Params(bool useModulusV1) const
{
    assert(this);
    static CBigNum bnHexModulus = 0;
    if (!bnHexModulus)
        bnHexModulus.SetHex(zerocoinModulus);
    static libzerocoin::ZerocoinParams ZCParamsHex = libzerocoin::ZerocoinParams(bnHexModulus);
    static CBigNum bnDecModulus = 0;
    if (!bnDecModulus)
        bnDecModulus.SetDec(zerocoinModulus);
    static libzerocoin::ZerocoinParams ZCParamsDec = libzerocoin::ZerocoinParams(bnDecModulus);

    if (useModulusV1)
        return &ZCParamsHex;

    return &ZCParamsDec;
}

class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0xa9;
        pchMessageStart[1] = 0xc1;
        pchMessageStart[2] = 0xb4;
        pchMessageStart[3] = 0x7e;
        vAlertPubKey = ParseHex("0000098d3ba6ba6e7423fa5cbd6a89e0a9a5348f88d332b44a5cb1a8b7ed2c1eaa335fc8dc4f012cb8241cc0bdafd6ca70c5f5448916e4e6f511bcd746ed57dc50");
        nDefaultPort = 7119;
        bnProofOfWorkLimit = ~uint256(0) >> 20; // Tokugawa starting difficulty is 1 / 2^12
        //nSubsidyHalvingInterval = 210000;
        nMaxReorganizationDepth = 100;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // Tokugawa: 1 day
        nTargetSpacing = 1 * 60;  // Tokugawa: 1 minute
        nMaturity = 45;
        nMasternodeCountDrift = 20;
        nMaxMoneyOut = 30000000 * COIN;

        /** Height or Time Based Activations **/
        nLastPOWBlock = 200;
        nModifierUpdateBlock = 999999999;
        nZerocoinStartHeight = 201;
        nZerocoinStartTime = 1546927200; // Tuesday, January 8, 2019 6:00:00 AM GMT	
        nBlockEnforceSerialRange = 253; //Enforce serial range starting this block
        nBlockRecalculateAccumulators = ~1; //Trigger a recalculation of accumulators
        nBlockFirstFraudulent = ~1; //First block that bad serials emerged
        nBlockLastGoodCheckpoint = ~1; //Last valid accumulator checkpoint
        nBlockEnforceInvalidUTXO = 999999999; //Start enforcing the invalid UTXO's
        nInvalidAmountFiltered = 0 * COIN; //Amount of invalid coins filtered through exchanges, that should be considered valid
        nBlockZerocoinV2 = 201; //!> The block that zerocoin v2 becomes active - roughly Tuesday, May 8, 2018 4:00:00 AM GMT
        nEnforceNewSporkKey = 1546948800; //!> Sporks signed after (GMT): Tuesday, January 8, 2019 12:00:00 PM GMT must use the new spork key
        nRejectOldSporkKey = 1527811200; //!> Fully reject old spork key after (GMT): Friday, June 1, 2018 12:00:00 AM

        /**
         * Build the genesis block. Note that the output of the genesis coinbase cannot
         * be spent as it did not originally exist in the database.
         *
         * CBlock(hash=00000ffd590b14, ver=1, hashPrevBlock=00000000000000, hashMerkleRoot=e0028e, nTime=1390095618, nBits=1e0ffff0, nNonce=28917698, vtx=1)
         *   CTransaction(hash=e0028e, ver=1, vin.size=1, vout.size=1, nLockTime=0)
         *     CTxIn(COutPoint(000000, -1), coinbase 04ffff001d01044c5957697265642030392f4a616e2f3230313420546865204772616e64204578706572696d656e7420476f6573204c6976653a204f76657273746f636b2e636f6d204973204e6f7720416363657074696e6720426974636f696e73)
         *     CTxOut(nValue=50.00000000, scriptPubKey=0xA9037BAC7050C479B121CF)
         *   vMerkleTree: e0028e
         */
        const char* pszTimestamp = "Search For Cockpit Voice Recorder Of Crashed Lion Air Jet To Resume.";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
		txNew.vout[0].SetEmpty();
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("04b10e83b2703ccf321f7dbd62dd5845ac7c10bd055814ce121ba32607d573b8810c02c0582aed05b4deb9a4b77b26d92428c61256cd42774babea0a073b2ed0c9") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime = 1546927200;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 775837;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x000001c46884d82e562759882dc44dc6b0721d62152416b9f57d6db1ef195fa5"));
        assert(genesis.hashMerkleRoot == uint256("0x925110bbad597d2b5fbf39d4cc38519c6a429cd23338e05e0373912e4dba3cf1"));

        vSeeds.push_back(CDNSSeedData("0", "178.128.208.192"));
        vSeeds.push_back(CDNSSeedData("1", "2604:a880:800:a1::287:e001"));
        vSeeds.push_back(CDNSSeedData("2", "167.99.8.23")); 
        vSeeds.push_back(CDNSSeedData("3", "2604:a880:400:d1::9f4:a001"));
        vSeeds.push_back(CDNSSeedData("4", "162.243.144.16"));
		vSeeds.push_back(CDNSSeedData("5", "2604:a880:1:20::3b:7001"));
		vSeeds.push_back(CDNSSeedData("6", "188.166.1.164"));
		vSeeds.push_back(CDNSSeedData("7", "2a03:b0c0:2:d0::15:e001"));
		vSeeds.push_back(CDNSSeedData("8", "178.128.93.175"));
		vSeeds.push_back(CDNSSeedData("9", "2400:6180:0:d1::1ff:4001"));
		vSeeds.push_back(CDNSSeedData("10", "178.62.13.109"));
		vSeeds.push_back(CDNSSeedData("11", "2a03:b0c0:1:d0::6bb:6001"));
		vSeeds.push_back(CDNSSeedData("12", "142.93.110.246"));
		vSeeds.push_back(CDNSSeedData("13", "2a03:b0c0:3:e0::70:e001"));
		vSeeds.push_back(CDNSSeedData("14", "159.89.123.185"));
		vSeeds.push_back(CDNSSeedData("15", "2604:a880:cad:d0::c5d:3001"));
		vSeeds.push_back(CDNSSeedData("16", "139.59.90.46"));
		vSeeds.push_back(CDNSSeedData("17", "2400:6180:100:d0::893:a001"));


        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 66);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 85);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 153);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();
        // 	BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x77).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive = false;

        nPoolMaxTransactions = 3;
        strSporkKey = "04693405167a272986bf55699568b911416c3b91152a7e46bebb81ab7cbff9682c4a8c0e769b8c24624ec0d91fe6b28098664607700e0e12ba3486fdde823d1601";
        strSporkKeyOld = "04693405167a272986bf55699568b911416c3b91152a7e46bebb81ab7cbff9682c4a8c0e769b8c24624ec0d91fe6b28098664607700e0e12ba3486fdde823d1601";
        strObfuscationPoolDummyAddress = "TN1q2gC9s6nNrnzEsg4aT6bHMLsK9nUhEw";
        nStartMasternodePayments = 1546957800; // Tuesday, January 8, 2019 2:30:00 PM GMT

        /** Zerocoin */
        zerocoinModulus = "25195908475657893494027183240048398571429282126204032027777137836043662020707595556264018525880784"
            "4069182906412495150821892985591491761845028084891200728449926873928072877767359714183472702618963750149718246911"
            "6507761337985909570009733045974880842840179742910064245869181719511874612151517265463228221686998754918242243363"
            "7259085141865462043576798423387184774447920739934236584823824281198163815010674810451660377306056201619676256133"
            "8441436038339044149526344321901146575444541784240209246165157233507787077498171257724679629263863563732899121548"
            "31438167899885040445364023527381951378636564391212010397122822120720357";
        nMaxZerocoinSpendsPerTransaction = 7; // Assume about 20kb each
        nMinZerocoinMintFee = 1 * CENT; //high fee required for zerocoin mints
        nMintRequiredConfirmations = 20; //the maximum amount of confirmations until accumulated in 19
        nRequiredAccumulation = 1;
        nDefaultSecurityLevel = 100; //full security level for accumulators
        nZerocoinHeaderVersion = 4; //Block headers must be this version once zerocoin is active
        nZerocoinRequiredStakeDepth = 200; //The required confirmations for a ztok to be stakable

        nBudget_Fee_Confirmations = 6; // Number of confirmations for the finalization fee
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return data;
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams
{
public:
    CTestNetParams()
    {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
        pchMessageStart[0] = 0x45;
        pchMessageStart[1] = 0x76;
        pchMessageStart[2] = 0x65;
        pchMessageStart[3] = 0xba;
        vAlertPubKey = ParseHex("000010e83b2703ccf322f7dbd62dd5855ac7c10bd055814ce121ba32607d573b8810c02c0582aed05b4deb9c4b77b26d92428c61256cd42774babea0a073b2ed0c9");
        nDefaultPort = 51474;
        nEnforceBlockUpgradeMajority = 51;
        nRejectBlockOutdatedMajority = 75;
        nToCheckBlockUpgradeMajority = 100;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // Tokugawa: 1 day
        nTargetSpacing = 1 * 60;  // Tokugawa: 1 minute
        nLastPOWBlock = 200;
        nMaturity = 15;
        nMasternodeCountDrift = 4;
        nModifierUpdateBlock = 51197; //approx Mon, 17 Apr 2017 04:00:00 GMT
        nMaxMoneyOut = 43199500 * COIN;
        nZerocoinStartHeight = 201576;
        nZerocoinStartTime = 1501776000;
        nBlockEnforceSerialRange = 1; //Enforce serial range starting this block
        nBlockRecalculateAccumulators = 9908000; //Trigger a recalculation of accumulators
        nBlockFirstFraudulent = 9891737; //First block that bad serials emerged
        nBlockLastGoodCheckpoint = 9891730; //Last valid accumulator checkpoint
        nBlockEnforceInvalidUTXO = 9902850; //Start enforcing the invalid UTXO's
        nInvalidAmountFiltered = 0; //Amount of invalid coins filtered through exchanges, that should be considered valid
        nBlockZerocoinV2 = 444020; //!> The block that zerocoin v2 becomes active
        nEnforceNewSporkKey = 1521604800; //!> Sporks signed after Wednesday, March 21, 2018 4:00:00 AM GMT must use the new spork key
        nRejectOldSporkKey = 1522454400; //!> Reject old spork key after Saturday, March 31, 2018 12:00:00 AM GMT

        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1546927200;
        genesis.nNonce = 2402015;

        hashGenesisBlock = genesis.GetHash();
        //assert(hashGenesisBlock == uint256("0x0000041e482b9b9691d98eefb48473405c0b8ec31b76df3797c74a78680ef818"));

        vFixedSeeds.clear();
        vSeeds.clear();
        vSeeds.push_back(CDNSSeedData("fuzzbawls.pw", "tokugawa-testnet.seed.fuzzbawls.pw"));
        vSeeds.push_back(CDNSSeedData("fuzzbawls.pw", "tokugawa-testnet.seed2.fuzzbawls.pw"));
        vSeeds.push_back(CDNSSeedData("s3v3nh4cks.ddns.net", "s3v3nh4cks.ddns.net"));
        vSeeds.push_back(CDNSSeedData("88.198.192.110", "88.198.192.110"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 139); // Testnet tokugawa addresses start with 'x' or 'y'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 19);  // Testnet tokugawa script addresses start with '8' or '9'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);     // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        // Testnet tokugawa BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
        // Testnet tokugawa BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
        // Testnet tokugawa BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x01).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions = 2;
        strSporkKey = "04A8B319388C0F8588D238B9941DC26B26D3F9465266B368A051C5C100F79306A557780101FE2192FE170D7E6DEFDCBEE4C8D533396389C0DAFFDBC842B002243C";
        strSporkKeyOld = "04348C2F50F90267E64FACC65BFDC9D0EB147D090872FB97ABAE92E9A36E6CA60983E28E741F8E7277B11A7479B626AC115BA31463AC48178A5075C5A9319D4A38";
        strObfuscationPoolDummyAddress = "y57cqfGRkekRyDRNeJiLtYVEbvhXrNbmox";
        nStartMasternodePayments = 1420837558; //Fri, 09 Jan 2015 21:05:58 GMT
        nBudget_Fee_Confirmations = 3; // Number of confirmations for the finalization fee. We have to make this very short
                                       // here because we only have a 8 block finalization window on testnet
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams
{
public:
    CRegTestParams()
    {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
        strNetworkID = "regtest";
        pchMessageStart[0] = 0xa1;
        pchMessageStart[1] = 0xcf;
        pchMessageStart[2] = 0x7e;
        pchMessageStart[3] = 0xac;
        //nSubsidyHalvingInterval = 150;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 1;
        nTargetTimespan = 24 * 60 * 60; // Tokugawa: 1 day
        nTargetSpacing = 1 * 60;        // Tokugawa: 1 minutes
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        genesis.nTime = 1546927200;
        genesis.nBits = 0x207fffff;
        genesis.nNonce = 12345;

        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 51476;
        //assert(hashGenesisBlock == uint256("0x4f023a2120d9127b21bbad01724fdb79b519f593f2a85b60d3d79160ec5f29df"));

        vFixedSeeds.clear(); //! Testnet mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Testnet mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataRegtest;
    }
};
static CRegTestParams regTestParams;

/**
 * Unit test
 */
class CUnitTestParams : public CMainParams, public CModifiableParams
{
public:
    CUnitTestParams()
    {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nDefaultPort = 51478;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Unit test mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fAllowMinDifficultyBlocks = false;
        fMineBlocksOnDemand = true;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }

    //! Published setters to allow changing values in unit test cases
    //virtual void setSubsidyHalvingInterval(int anSubsidyHalvingInterval) { nSubsidyHalvingInterval = anSubsidyHalvingInterval; }
    virtual void setEnforceBlockUpgradeMajority(int anEnforceBlockUpgradeMajority) { nEnforceBlockUpgradeMajority = anEnforceBlockUpgradeMajority; }
    virtual void setRejectBlockOutdatedMajority(int anRejectBlockOutdatedMajority) { nRejectBlockOutdatedMajority = anRejectBlockOutdatedMajority; }
    virtual void setToCheckBlockUpgradeMajority(int anToCheckBlockUpgradeMajority) { nToCheckBlockUpgradeMajority = anToCheckBlockUpgradeMajority; }
    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks) { fDefaultConsistencyChecks = afDefaultConsistencyChecks; }
    virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) { fAllowMinDifficultyBlocks = afAllowMinDifficultyBlocks; }
    virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) { fSkipProofOfWorkCheck = afSkipProofOfWorkCheck; }
};
static CUnitTestParams unitTestParams;


static CChainParams* pCurrentParams = 0;

CModifiableParams* ModifiableParams()
{
    assert(pCurrentParams);
    assert(pCurrentParams == &unitTestParams);
    return (CModifiableParams*)&unitTestParams;
}

const CChainParams& Params()
{
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(CBaseChainParams::Network network)
{
    switch (network) {
    case CBaseChainParams::MAIN:
        return mainParams;
    case CBaseChainParams::TESTNET:
        return testNetParams;
    case CBaseChainParams::REGTEST:
        return regTestParams;
    case CBaseChainParams::UNITTEST:
        return unitTestParams;
    default:
        assert(false && "Unimplemented network");
        return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}
