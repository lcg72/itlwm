//
//  AirportSTAIOCTL.cpp
//  AirportItlwm
//
//  Created by qcwap on 2020/9/4.
//  Copyright © 2020 钟先耀. All rights reserved.
//

#include "AirportItlwm.hpp"

SInt32 AirportItlwm::apple80211Request(unsigned int request_type,
                                       int request_number,
                                       IO80211Interface *interface,
                                       void *data)
{
    // This funciton is not only called by IPC, but will called by IO80211Family internal functions, so we should call it in gate.
    return getCommandGate()->runAction(&apple80211RequestGated, &request_type, &request_number, interface, data);
}

IOReturn AirportItlwm::
apple80211RequestGated(OSObject *target, void *arg0, void *arg1, void *arg2, void *arg3)
{
    IOReturn ret = kIOReturnError;
    uint request_type = *(uint*)arg0;
    int request_number = *(int*)arg1;
    IO80211Interface *interface = (IO80211Interface*)arg2;
    void *data = arg3;
    AirportItlwm *that = (AirportItlwm *)target;
    bool isGet = (request_type == SIOCGA80211);
    
    XYLog("%s: IOCTL %s(%d) %s", __FUNCTION__,
          isGet ? "get" : "set",
          request_number,
          IOCTL_NAMES[request_number]);
    
    switch (request_number) {
        case APPLE80211_IOC_SSID:  // 1
            IOCTL(request_type, SSID, apple80211_ssid_data);
            break;
        case APPLE80211_IOC_AUTH_TYPE:  // 2
            IOCTL_GET(request_type, AUTH_TYPE, apple80211_authtype_data);
            break;
        case APPLE80211_IOC_CHANNEL:  // 4
            IOCTL_GET(request_type, CHANNEL, apple80211_channel_data);
            break;
        case APPLE80211_IOC_PROTMODE:
            IOCTL(request_type, PROTMODE, apple80211_protmode_data);
            break;
        case APPLE80211_IOC_TXPOWER:  // 7
            IOCTL_GET(request_type, TXPOWER, apple80211_txpower_data);
            break;
        case APPLE80211_IOC_RATE:  // 8
            IOCTL_GET(request_type, RATE, apple80211_rate_data);
            break;
        case APPLE80211_IOC_BSSID:  // 9
            IOCTL_GET(request_type, BSSID, apple80211_bssid_data);
            break;
        case APPLE80211_IOC_SCAN_REQ:  // 10
            IOCTL_SET(request_type, SCAN_REQ, apple80211_scan_data);
            break;
        case APPLE80211_IOC_SCAN_REQ_MULTIPLE:
            IOCTL_SET(request_type, SCAN_REQ_MULTIPLE, apple80211_scan_multiple_data);
            break;
        case APPLE80211_IOC_SCAN_RESULT:  // 11
            IOCTL_GET(request_type, SCAN_RESULT, apple80211_scan_result*);
            break;
        case APPLE80211_IOC_CARD_CAPABILITIES:  // 12
            IOCTL_GET(request_type, CARD_CAPABILITIES, apple80211_capability_data);
            break;
        case APPLE80211_IOC_STATE:  // 13
            IOCTL_GET(request_type, STATE, apple80211_state_data);
            break;
        case APPLE80211_IOC_PHY_MODE:  // 14
            IOCTL_GET(request_type, PHY_MODE, apple80211_phymode_data);
            break;
        case APPLE80211_IOC_OP_MODE:  // 15
            IOCTL_GET(request_type, OP_MODE, apple80211_opmode_data);
            break;
        case APPLE80211_IOC_RSSI:  // 16
            IOCTL_GET(request_type, RSSI, apple80211_rssi_data);
            break;
        case APPLE80211_IOC_NOISE:  // 17
            IOCTL_GET(request_type, NOISE, apple80211_noise_data);
            break;
        case APPLE80211_IOC_INT_MIT:  // 18
            IOCTL_GET(request_type, INT_MIT, apple80211_intmit_data);
            break;
        case APPLE80211_IOC_POWER:  // 19
            IOCTL(request_type, POWER, apple80211_power_data);
            break;
        case APPLE80211_IOC_ASSOCIATE:  // 20
            IOCTL_SET(request_type, ASSOCIATE, apple80211_assoc_data);
            break;
        case APPLE80211_IOC_ASSOCIATE_RESULT:
            IOCTL_GET(request_type, ASSOCIATE_RESULT, apple80211_assoc_result_data);
            break;
        case APPLE80211_IOC_RATE_SET:
            IOCTL_GET(request_type, RATE_SET, apple80211_rate_set_data);
            break;
        case APPLE80211_IOC_MCS_INDEX_SET:
            IOCTL_GET(request_type, MCS_INDEX_SET, apple80211_mcs_index_set_data);
            break;
        case APPLE80211_IOC_SUPPORTED_CHANNELS:  // 27
            IOCTL_GET(request_type, SUPPORTED_CHANNELS, apple80211_sup_channel_data);
            break;
        case APPLE80211_IOC_LOCALE:  // 28
            IOCTL_GET(request_type, LOCALE, apple80211_locale_data);
            break;
        case APPLE80211_IOC_DEAUTH:
            IOCTL(request_type, DEAUTH, apple80211_deauth_data);
            break;
        case APPLE80211_IOC_TX_ANTENNA:  // 37
            IOCTL_GET(request_type, TX_ANTENNA, apple80211_antenna_data);
            break;
        case APPLE80211_IOC_ANTENNA_DIVERSITY:  // 39
            IOCTL_GET(request_type, ANTENNA_DIVERSITY, apple80211_antenna_data);
            break;
        case APPLE80211_IOC_DRIVER_VERSION:  // 43
            IOCTL_GET(request_type, DRIVER_VERSION, apple80211_version_data);
            break;
        case APPLE80211_IOC_HARDWARE_VERSION:  // 44
            IOCTL_GET(request_type, HARDWARE_VERSION, apple80211_version_data);
            break;
        case APPLE80211_IOC_ASSOCIATION_STATUS:  // 50
            IOCTL_GET(request_type, ASSOCIATION_STATUS, apple80211_assoc_status_data);
            break;
        case APPLE80211_IOC_COUNTRY_CODE:  // 51
            IOCTL_GET(request_type, COUNTRY_CODE, apple80211_country_code_data);
            break;
        case APPLE80211_IOC_RADIO_INFO:
            IOCTL_GET(request_type, RADIO_INFO, apple80211_radio_info_data);
            break;
        case APPLE80211_IOC_MCS:  // 57
            IOCTL_GET(request_type, MCS, apple80211_mcs_data);
            break;
        case APPLE80211_IOC_VIRTUAL_IF_CREATE: // 94
            IOCTL_SET(request_type, VIRTUAL_IF_CREATE, apple80211_virt_if_create_data);
            break;
        case APPLE80211_IOC_ROAM_THRESH:
            IOCTL_GET(request_type, ROAM_THRESH, apple80211_roam_threshold_data);
            break;
        case APPLE80211_IOC_POWERSAVE:
            IOCTL_GET(request_type, POWERSAVE, apple80211_powersave_data);
            break;
        case APPLE80211_IOC_CIPHER_KEY:
            IOCTL_SET(request_type, CIPHER_KEY, apple80211_key);
            break;
        case APPLE80211_IOC_SCANCACHE_CLEAR:
            IOCTL_SET(request_type, SCANCACHE_CLEAR, apple80211req);
            break;
        default:
            XYLog("%s Unhandled IOCTL %s (%d)\n", __FUNCTION__, IOCTL_NAMES[request_number],
                  request_number);
            break;
    }
    
    return ret;
}

IOReturn AirportItlwm::
getSSID(OSObject *object,
                        struct apple80211_ssid_data *sd)
{
    struct ieee80211com* ic = fHalService->get80211Controller();
    if (ic->ic_state == IEEE80211_S_RUN) {
        memset(sd, 0, sizeof(*sd));
        sd->version = APPLE80211_VERSION;
        memcpy(sd->ssid_bytes, ic->ic_des_essid, strlen((const char*)ic->ic_des_essid));
        sd->ssid_len = (uint32_t)strlen((const char*)ic->ic_des_essid);
        return kIOReturnSuccess;
    }
    return kIOReturnError;
}

IOReturn AirportItlwm::
setSSID(OSObject *object, struct apple80211_ssid_data *sd)
{
    return kIOReturnSuccess;
}

IOReturn AirportItlwm::
getAUTH_TYPE(OSObject *object, struct apple80211_authtype_data *ad)
{
    if (fHalService->get80211Controller()->ic_state > IEEE80211_S_SCAN) {
        ad->version = APPLE80211_VERSION;
        ad->authtype_lower = APPLE80211_AUTHTYPE_OPEN;
        ad->authtype_upper = 8;
        return kIOReturnSuccess;
    }
    return kIOReturnError;
}

IOReturn AirportItlwm::
setCIPHER_KEY(OSObject *object, struct apple80211_key *ck)
{
    XYLog("%s", __FUNCTION__);
    return kIOReturnSuccess;
}

static int ieeeChanFlag2apple(int flags)
{
    int ret = 0;
    if (flags & IEEE80211_CHAN_2GHZ)    ret |= APPLE80211_C_FLAG_2GHZ;
    if (flags & IEEE80211_CHAN_5GHZ)    ret |= APPLE80211_C_FLAG_5GHZ;
    if (!(flags & IEEE80211_CHAN_PASSIVE))    ret |= APPLE80211_C_FLAG_ACTIVE;
    if (flags & IEEE80211_CHAN_OFDM)    ret |= APPLE80211_C_FLAG_20MHZ; // XXX ??
    if (flags & IEEE80211_CHAN_CCK)        ret |= APPLE80211_C_FLAG_10MHZ; // XXX ??
    if (flags & IEEE80211_CHAN_VHT)     ret |= APPLE80211_C_FLAG_5GHZ;
    return ret;
}

IOReturn AirportItlwm::
getCHANNEL(OSObject *object,
                           struct apple80211_channel_data *cd)
{
    struct ieee80211com* ic = fHalService->get80211Controller();
    if (ic->ic_state == IEEE80211_S_RUN) {
        memset(cd, 0, sizeof(apple80211_channel_data));
        cd->version = APPLE80211_VERSION;
        cd->channel.version = APPLE80211_VERSION;
        cd->channel.channel = ieee80211_chan2ieee(ic, ic->ic_bss->ni_chan);
        cd->channel.flags = ieeeChanFlag2apple(ic->ic_bss->ni_chan->ic_flags);
        return kIOReturnSuccess;
    }
    return kIOReturnError;
}

IOReturn AirportItlwm::
getPROTMODE(OSObject *object, struct apple80211_protmode_data *pd)
{
    struct ieee80211com* ic = fHalService->get80211Controller();
    if (ic->ic_state == IEEE80211_S_RUN) {
        memset(pd, 0, sizeof(*pd));
        pd->version = APPLE80211_VERSION;
        pd->threshold = 0;
        pd->protmode = 0;
        return kIOReturnSuccess;
    }
    return kIOReturnError;
}

IOReturn AirportItlwm::
setPROTMODE(
                            OSObject *object, struct apple80211_protmode_data *pd)
{
    return kIOReturnError;
}

IOReturn AirportItlwm::
getTXPOWER(OSObject *object,
                           struct apple80211_txpower_data *txd)
{
    ieee80211com *ic = fHalService->get80211Controller();
    if (ic->ic_state == IEEE80211_S_RUN) {
        memset(txd, 0, sizeof(*txd));
        txd->version = APPLE80211_VERSION;
        txd->txpower = 100;
        txd->txpower_unit = APPLE80211_UNIT_PERCENT;
        return kIOReturnSuccess;
    }
    return kIOReturnError;
}

IOReturn AirportItlwm::
getRATE(OSObject *object, struct apple80211_rate_data *rd)
{
    ieee80211com *ic = fHalService->get80211Controller();
    if (ic->ic_state == IEEE80211_S_RUN) {
        memset(rd, 0, sizeof(*rd));
        rd->version = APPLE80211_VERSION;
        rd->num_radios = 1;
        rd->rate[0] = ic->ic_bss->ni_rates.rs_rates[ic->ic_bss->ni_txrate];
        return kIOReturnSuccess;
    }
    return kIOReturnError;
}

IOReturn AirportItlwm::
getBSSID(OSObject *object,
                         struct apple80211_bssid_data *bd)
{
    ieee80211com *ic = fHalService->get80211Controller();
    if (ic->ic_state == IEEE80211_S_RUN) {
        memset(bd, 0, sizeof(*bd));
        bd->version = APPLE80211_VERSION;
        memcpy(bd->bssid.octet, ic->ic_bss->ni_bssid, APPLE80211_ADDR_LEN);
        return kIOReturnSuccess;
    }
    return kIOReturnError;
}

IOReturn AirportItlwm::
getCARD_CAPABILITIES(OSObject *object,
                                     struct apple80211_capability_data *cd)
{
    cd->version = APPLE80211_VERSION;
    cd->capabilities[0] = 0xeb;
    cd->capabilities[1] = 0x7e;
    cd->capabilities[2] |= 0xc0;
    cd->capabilities[2] = 3;
    cd->capabilities[2] |= 0x13;
    cd->capabilities[2] |= 0x20;
    cd->capabilities[2] |= 0x28;
    cd->capabilities[2] |= 4;
    cd->capabilities[5] |= 8;
    cd->capabilities[3] |= 2;
    cd->capabilities[4] |= 1;
    cd->capabilities[6] |= 8;

    cd->capabilities[3] |= 0x23;
    cd->capabilities[2] |= 0x80;
    cd->capabilities[5] |= 4;
    cd->capabilities[2] |= 0xC0;
    cd->capabilities[6] |= 0x84;
    cd->capabilities[3] |= 8;
    cd->capabilities[6] |= 1;
    cd->capabilities[5] |= 0x80;
    return kIOReturnSuccess;
}

IOReturn AirportItlwm::
getSTATE(OSObject *object,
                         struct apple80211_state_data *sd)
{
    ieee80211com *ic = fHalService->get80211Controller();
    sd->version = APPLE80211_VERSION;
    sd->state = ic->ic_state;
    return kIOReturnSuccess;
}

IOReturn AirportItlwm::
getMCS_INDEX_SET(OSObject *object, struct apple80211_mcs_index_set_data *ad)
{
    ieee80211com *ic = fHalService->get80211Controller();
    if (ic->ic_state == IEEE80211_S_RUN) {
        memset(ad, 0, sizeof(*ad));
        ad->version = APPLE80211_VERSION;
        for (int i=0; i<10; i++) {
            ad->mcs_set_map[i] = ic->ic_bss->ni_rxmcs[i];
        }
        return kIOReturnSuccess;
    }
    return kIOReturnError;
}

IOReturn AirportItlwm::
getRATE_SET(OSObject *object, struct apple80211_rate_set_data *ad)
{
    ieee80211com *ic = fHalService->get80211Controller();
    if (ic->ic_state == IEEE80211_S_RUN) {
        memset(ad, 0, sizeof(*ad));
        ad->version = APPLE80211_VERSION;
        ad->num_rates = ic->ic_bss->ni_rates.rs_nrates;
        for (int i=0; i<15; i++) {
            struct apple80211_rate apple_rate = ad->rates[i];
            apple_rate.version = APPLE80211_VERSION;
            apple_rate.rate = ic->ic_bss->ni_rates.rs_rates[i];
            apple_rate.flags = 0;
        }
        return kIOReturnSuccess;
    }
    return kIOReturnError;
}

IOReturn AirportItlwm::
getPHY_MODE(OSObject *object,
                            struct apple80211_phymode_data *pd)
{
    pd->version = APPLE80211_VERSION;
    pd->phy_mode = APPLE80211_MODE_11A
    | APPLE80211_MODE_11B
    | APPLE80211_MODE_11G
    | APPLE80211_MODE_11N;
    if (fHalService->getDriverInfo()->is5GBandSupport()) {
        pd->phy_mode |= APPLE80211_MODE_11AC;
    }
    
    switch (fHalService->get80211Controller()->ic_curmode) {
        case IEEE80211_MODE_AUTO:
            pd->active_phy_mode = APPLE80211_MODE_AUTO;
            break;
        case IEEE80211_MODE_11A:
            pd->active_phy_mode = APPLE80211_MODE_11A;
            break;
        case IEEE80211_MODE_11B:
            pd->active_phy_mode = APPLE80211_MODE_11B;
            break;
        case IEEE80211_MODE_11G:
            pd->active_phy_mode = APPLE80211_MODE_11G;
            break;
        case IEEE80211_MODE_11N:
            pd->active_phy_mode = APPLE80211_MODE_11N;
            break;
        case IEEE80211_MODE_11AC:
            pd->active_phy_mode = APPLE80211_MODE_11AC;
            break;
            
        default:
            pd->active_phy_mode = APPLE80211_MODE_AUTO;
            break;
    }
    
    return kIOReturnSuccess;
}

IOReturn AirportItlwm::
getOP_MODE(OSObject *object,
                           struct apple80211_opmode_data *od)
{
    od->version = APPLE80211_VERSION;
    od->op_mode = APPLE80211_M_STA;
    return kIOReturnSuccess;
}

IOReturn AirportItlwm::
getRSSI(OSObject *object,
                        struct apple80211_rssi_data *rd)
{
    ieee80211com *ic = fHalService->get80211Controller();
    if (ic->ic_state == IEEE80211_S_RUN) {
        memset(rd, 0, sizeof(*rd));
        rd->num_radios = 1;
        rd->rssi_unit = APPLE80211_UNIT_DBM;
        rd->rssi[0] = rd->aggregate_rssi
        = rd->rssi_ext[0]
        = rd->aggregate_rssi_ext
        = ic->ic_bss->ni_rssi;
        return kIOReturnSuccess;
    }
    return kIOReturnError;
}

IOReturn AirportItlwm::
getNOISE(OSObject *object,
                         struct apple80211_noise_data *nd)
{
    ieee80211com *ic = fHalService->get80211Controller();
    if (ic->ic_state == IEEE80211_S_RUN) {
        memset(nd, 0, sizeof(*nd));
        nd->version = APPLE80211_VERSION;
        nd->num_radios = 1;
        nd->noise[0]
        = nd->aggregate_noise = -101;
        nd->noise_unit = APPLE80211_UNIT_DBM;
        return kIOReturnSuccess;
    }
    return kIOReturnError;
}

IOReturn AirportItlwm::
getINT_MIT(OSObject *object, struct apple80211_intmit_data *imd)
{
    imd->version = APPLE80211_VERSION;
    imd->int_mit = APPLE80211_INT_MIT_AUTO;
    return kIOReturnSuccess;
}

IOReturn AirportItlwm::
getPOWER(OSObject *object,
                         struct apple80211_power_data *pd)
{
    pd->version = APPLE80211_VERSION;
    pd->num_radios = 1;
    pd->power_state[0] = power_state;
    return kIOReturnSuccess;
}

IOReturn AirportItlwm::
getPOWERSAVE(OSObject *object, struct apple80211_powersave_data *pd)
{
    pd->version = APPLE80211_VERSION;
    pd->powersave_level = APPLE80211_POWERSAVE_MODE_DISABLED;
    return kIOReturnSuccess;
}

IOReturn AirportItlwm::
setPOWER(OSObject *object,
                         struct apple80211_power_data *pd)
{
    if (pd->num_radios > 0) {
        power_state = (pd->power_state[0]);
    }
    
//    interface->postMessage(APPLE80211_M_POWER_CHANGED);
    
    return kIOReturnSuccess;
}

IOReturn AirportItlwm::
setASSOCIATE(OSObject *object,
                             struct apple80211_assoc_data *ad)
{
    XYLog("%s [%s] [%s]\n", __FUNCTION__, ad->ad_ssid, ad->ad_key.key);    //    interface->postMessage(APPLE80211_M_ASSOC_DONE, 0, 0);
    getNetworkInterface()->postMessage(APPLE80211_M_SSID_CHANGED);
    getNetworkInterface()->setLinkState(IO80211LinkState::kIO80211NetworkLinkUp, 0);
    return kIOReturnSuccess;
}

IOReturn AirportItlwm::
getASSOCIATE_RESULT(OSObject *object, struct apple80211_assoc_result_data *ad)
{
    XYLog("%s\n", __FUNCTION__);
    ieee80211com *ic = fHalService->get80211Controller();
    if (ic->ic_state == IEEE80211_S_RUN) {
        memset(ad, 0, sizeof(struct apple80211_assoc_result_data));
        ad->version = APPLE80211_VERSION;
        ad->result = APPLE80211_RESULT_SUCCESS;
        return kIOReturnSuccess;
    }
    return kIOReturnError;
}

IOReturn AirportItlwm::
getSUPPORTED_CHANNELS(OSObject *object, struct apple80211_sup_channel_data *ad)
{
    ad->version = APPLE80211_VERSION;
    ad->num_channels = 0;
    ieee80211com *ic = fHalService->get80211Controller();
    for (int i = 0; i < IEEE80211_CHAN_MAX; i++) {
        if (ic->ic_channels[i].ic_freq != 0) {
            ad->supported_channels[ad->num_channels++].channel    = ieee80211_chan2ieee(ic, &ic->ic_channels[i]);
            ad->supported_channels[ad->num_channels].flags    = ieeeChanFlag2apple(ic->ic_channels[i].ic_flags);
        }
    }
    return kIOReturnSuccess;
}

IOReturn AirportItlwm::
getLOCALE(OSObject *object,
                          struct apple80211_locale_data *ld)
{
    ld->version = APPLE80211_VERSION;
    ld->locale  = APPLE80211_LOCALE_FCC;
    
    return kIOReturnSuccess;
}

IOReturn AirportItlwm::
getDEAUTH(OSObject *object,
                          struct apple80211_deauth_data *da) {
    da->version = APPLE80211_VERSION;
    da->deauth_reason = APPLE80211_REASON_UNSPECIFIED;
    return kIOReturnSuccess;
}

IOReturn AirportItlwm::
getASSOCIATION_STATUS(
                                      OSObject *object, struct apple80211_assoc_status_data *hv) {
    XYLog("%s\n", __FUNCTION__);
    ieee80211com *ic = fHalService->get80211Controller();
    memset(hv, 0, sizeof(*hv));
    hv->version = APPLE80211_VERSION;
    if (ic->ic_state == IEEE80211_S_RUN) {
        hv->status = APPLE80211_STATUS_SUCCESS;
        return kIOReturnSuccess;
    } else if (ic->ic_state == IEEE80211_S_AUTH || ic->ic_state == IEEE80211_S_ASSOC) {
        hv->status = APPLE80211_STATUS_UNAVAILABLE;
        return kIOReturnBusy;
    } else {
        //todo use reason code
        hv->status = APPLE80211_STATUS_UNSPECIFIED_FAILURE;
        return kIOReturnError;
    }
}

IOReturn AirportItlwm::
setSCANCACHE_CLEAR(OSObject *object, struct apple80211req *req)
{
    return kIOReturnSuccess;
}

IOReturn AirportItlwm::
setDEAUTH(OSObject *object,
                          struct apple80211_deauth_data *da) {
    XYLog("%s\n", __FUNCTION__);
    return kIOReturnSuccess;
}

IOReturn AirportItlwm::
getTX_ANTENNA(OSObject *object,
                              apple80211_antenna_data *ad)
{
    ieee80211com *ic = fHalService->get80211Controller();
    if (ic->ic_state != IEEE80211_S_RUN ||  ic->ic_bss == NULL)
        return kIOReturnError;
    ad->version = APPLE80211_VERSION;
    ad->num_radios = 1;
    ad->antenna_index[0] = 1;
    return kIOReturnSuccess;
}

IOReturn AirportItlwm::
getANTENNA_DIVERSITY(OSObject *object,
                                     apple80211_antenna_data *ad)
{
    ieee80211com *ic = fHalService->get80211Controller();
    if (ic->ic_state != IEEE80211_S_RUN ||  ic->ic_bss == NULL)
        return kIOReturnError;
    ad->version = APPLE80211_VERSION;
    ad->num_radios = 1;
    ad->antenna_index[0] = 1;
    return kIOReturnSuccess;
}

IOReturn AirportItlwm::
getDRIVER_VERSION(OSObject *object,
                                  struct apple80211_version_data *hv)
{
    const char* local_version = "itlwm 1.0.0d";
    hv->version = APPLE80211_VERSION;
    snprintf(hv->string, sizeof(hv->string), "%s %s", local_version, fHalService->getDriverInfo()->getFirmwareVersion());
    hv->string_len = strlen(hv->string);
    return kIOReturnSuccess;
}

IOReturn AirportItlwm::
getHARDWARE_VERSION(OSObject *object,
                                    struct apple80211_version_data *hv)
{
    hv->version = APPLE80211_VERSION;
    strncpy(hv->string, fHalService->getDriverInfo()->getFirmwareVersion(), sizeof(hv->string));
    hv->string_len = strlen(fHalService->getDriverInfo()->getFirmwareVersion());
    return kIOReturnSuccess;
}

IOReturn AirportItlwm::
getCOUNTRY_CODE(OSObject *object,
                                struct apple80211_country_code_data *cd)
{
    cd->version = APPLE80211_VERSION;
    strncpy((char*)cd->cc, "ZZ", sizeof(cd->cc));
    return kIOReturnSuccess;
}

IOReturn AirportItlwm::
getMCS(OSObject *object, struct apple80211_mcs_data* md)
{
    ieee80211com *ic = fHalService->get80211Controller();
    if (ic->ic_state != IEEE80211_S_RUN ||  ic->ic_bss == NULL)
        return kIOReturnError;
    md->version = APPLE80211_VERSION;
    md->index = ic->ic_bss->ni_txmcs;
    return kIOReturnSuccess;
}

IOReturn AirportItlwm::
getROAM_THRESH(OSObject *object, struct apple80211_roam_threshold_data* md)
{
    ieee80211com *ic = fHalService->get80211Controller();
    if (ic->ic_state != IEEE80211_S_RUN ||  ic->ic_bss == NULL)
        return kIOReturnError;
    md->threshold = 100;
    md->count = 0;
    return kIOReturnSuccess;
}

IOReturn AirportItlwm::
getRADIO_INFO(OSObject *object, struct apple80211_radio_info_data* md)
{
    ieee80211com *ic = fHalService->get80211Controller();
    if (ic->ic_state != IEEE80211_S_RUN ||  ic->ic_bss == NULL)
        return kIOReturnError;
    md->version = 1;
    md->count = 1;
    return kIOReturnSuccess;
}

IOReturn AirportItlwm::
setSCAN_REQ(OSObject *object,
                            struct apple80211_scan_data *sd)
{
    if (fScanResultWrapping) {
        return kIOReturnBusy;
    }
    if (scanSource) {
        scanSource->setTimeoutMS(3000);
        scanSource->enable();
    }
    return kIOReturnSuccess;
}

IOReturn AirportItlwm::
setSCAN_REQ_MULTIPLE(OSObject *object, struct apple80211_scan_multiple_data *sd)
{
    if (fScanResultWrapping) {
        return kIOReturnBusy;
    }
    if (scanSource) {
        scanSource->setTimeoutMS(3000);
        scanSource->enable();
    }
    return kIOReturnSuccess;
}

IOReturn AirportItlwm::
getSCAN_RESULT(OSObject *object, struct apple80211_scan_result **sr)
{
    ieee80211com *ic = fHalService->get80211Controller();
    
    if (fNextNodeToSend == NULL) { // start at beginning if we're not in the middle
        if (fScanResultWrapping) {
            fScanResultWrapping = false;
            XYLog("%s no more results\n", __FUNCTION__);
            return 5; // XXX no more results
        } else {
            fNextNodeToSend = RB_MIN(ieee80211_tree, &ic->ic_tree);
            if (fNextNodeToSend == NULL) {
                XYLog("%s fNextNodeToSend = NULL\n", __FUNCTION__);
                return 5;
            }
        }
    }
    XYLog("%s ni_bssid=%s ni_essid=%s channel=%d flags=%d asr_cap=%d asr_nrates=%d asr_ssid_len=%d asr_ie_len=%d asr_rssi=%d\n", __FUNCTION__, ether_sprintf(fNextNodeToSend->ni_bssid), fNextNodeToSend->ni_essid, ieee80211_chan2ieee(ic, fNextNodeToSend->ni_chan), ieeeChanFlag2apple(fNextNodeToSend->ni_chan->ic_flags), fNextNodeToSend->ni_capinfo, fNextNodeToSend->ni_rates.rs_nrates, fNextNodeToSend->ni_esslen, fNextNodeToSend->ni_rsnie_tlv == NULL ? 0 : fNextNodeToSend->ni_rsnie_tlv_len, fNextNodeToSend->ni_rssi);
    apple80211_scan_result* result = (apple80211_scan_result* )fNextNodeToSend->verb;
//    apple80211_scan_result* result = (apple80211_scan_result*)kzalloc(sizeof(struct apple80211_scan_result));
    bzero(result, sizeof(*result));
    result->version = APPLE80211_VERSION;
    if (fNextNodeToSend->ni_rsnie_tlv) {
        result->asr_ie_len = fNextNodeToSend->ni_rsnie_tlv_len;
        result->asr_ie_data = fNextNodeToSend->ni_rsnie_tlv;
    } else {
        result->asr_ie_len = 0;
        result->asr_ie_data = NULL;
    }
    result->asr_beacon_int = 100;
    for (int i = 0; i < result->asr_nrates; i++ )
        result->asr_rates[i] = fNextNodeToSend->ni_rates.rs_rates[i];
    result->asr_nrates = fNextNodeToSend->ni_rates.rs_nrates;
    result->asr_cap = fNextNodeToSend->ni_capinfo;
    result->asr_channel.version = APPLE80211_VERSION;
    result->asr_channel.channel = ieee80211_chan2ieee(ic, fNextNodeToSend->ni_chan);
    result->asr_channel.flags = ieeeChanFlag2apple(fNextNodeToSend->ni_chan->ic_flags);
    result->asr_noise = -101;
    result->asr_rssi = fNextNodeToSend->ni_rssi;
    memcpy(result->asr_bssid, fNextNodeToSend->ni_bssid, IEEE80211_ADDR_LEN);
    result->asr_ssid_len = fNextNodeToSend->ni_esslen;
    if (result->asr_ssid_len != 0) {
        memcpy(&result->asr_ssid, fNextNodeToSend->ni_essid, result->asr_ssid_len + 1);
    }

    *sr = result;
//
//    // done sending this one, now move to next for subsequent request
    fNextNodeToSend = RB_NEXT(ieee80211_tree, &ic->ic_tree, fNextNodeToSend);
    if (fNextNodeToSend == NULL) // if there is no next one then wrap next time
        fScanResultWrapping = true; // XXX next time signal that we got no more
    return kIOReturnSuccess;
}

IOReturn AirportItlwm::
setVIRTUAL_IF_CREATE(OSObject *object, struct apple80211_virt_if_create_data* data)
{
    struct ether_addr addr;
    IOLog("%s role=%d, bsd_name=%s, mac=%s, unk1=%d\n", __FUNCTION__, data->role, data->bsd_name,
          ether_sprintf(data->mac), data->unk1);
    if (data->role == 1) {
        IO80211P2PInterface *inf = new IO80211P2PInterface;
        if (inf == NULL) {
            return kIOReturnError;
        }
        memcpy(addr.octet, data->mac, 6);
        inf->init(this, &addr, data->role, "p2p");
        inf->setEnabledBySystem(true);
        IOLog("啊啊啊啊 虚拟接口调用成功\n");
    } else if (data->role == 4) {
        IO80211P2PInterface *inf = new IO80211P2PInterface;
        if (inf == NULL) {
            return kIOReturnError;
        }
        memcpy(addr.octet, data->mac, 6);
        inf->init(this, &addr, data->role, "awdl");
        inf->setEnabledBySystem(true);
        IOLog("啊啊啊啊 虚拟接口调用成功\n");
    }
    return kIOReturnSuccess;
}
