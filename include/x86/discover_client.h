#ifndef DISCOVER_CLIENT_H
#define DISCOVER_CLIENT_H

#include "discover_def.h"
#ifdef __cplusplus
extern "C" {
#endif

int discover_client_init();

void discover_client_deinit();

void discover_reg_ipscan_cb(discover_ipscan_cb_t cb, int usr_param);

void discover_reg_ipscan_cb2(discover_ipscan_cb_t cb);

void discover_ipscan();

void discover_ipscan2();

void discover_print_ipscan(const struct ipscan_t* ipscan);

void discover_setip_bymac(const char* mac, const char* ip, const char* netmask, const char* gateway);

#ifdef __cplusplus
    }
#endif

#endif //

