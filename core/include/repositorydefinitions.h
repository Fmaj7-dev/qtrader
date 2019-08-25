#ifndef REPOSITORY_DEFINITIONS_H
#define REPOSITORY_DEFINITIONS_H

#include <string>

class RepositoryDefinitions
{
public:
    enum class Stock
    {
        LIVE_BCH,
        LIVE_BTC,
        LIVE_EOS,
        LIVE_ETH,
        LIVE_LTC,
        LIVE_TRX,
        LIVE_XRP,

        /* LIVE_GOLD,
        LIVE_EUR_USD, */
    };

    static std::string toString( Stock type )
    {
        switch ( type )
        {
        case Stock::LIVE_BCH:
            return "live_bch";
        break;
        case Stock::LIVE_BTC:
            return "live_btc";
        break;
        case Stock::LIVE_EOS:
            return "live_eos";
        break;
        case Stock::LIVE_ETH:
            return "live_eth";
        break;
        case Stock::LIVE_LTC:
            return "live_ltc"; 
        break;
        case Stock::LIVE_TRX:
            return "live_trx";
        break;
        case Stock::LIVE_XRP:
            return "live_xrp";
        break;
        }
    }

};

#endif