/*
 * This file is part of the wawan-ikhwan project.
 * Copyright (c) 2022 Muhammad Ikhwan Perwira <ikhwanperwira@gmail.com>
 *
 * uwc_udp.
 *
 */

#ifndef __UWC_UDP_H__
#define __UWC_UDP_H__

#include <lwip/netdb.h>
#include <string.h>
#include <sys/param.h>

#include "esp_err.h"
#include "esp_event.h"
#include "esp_log.h"
#include "esp_netif.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "lwip/err.h"
#include "lwip/sockets.h"
#include "lwip/sys.h"
#include "stdbool.h"
#include "string.h"
#include "uwc_eolremover.h"
#include "uwc_tag.h"
#include "uwc_wifi.h"

#define UDP_BUF_SIZE 512

extern char SERV_IPV4[16];
extern u16_t SERV_PORT;
extern bool interruptHandshake;  // signal interrupt when handshaking.
extern bool isUdpInit;
extern u8_t timeoutCounter;  // timeout counted when length == 0;

// /**
//  * @brief Set target UDP server IP.
//  * @param ip: IP of UDP server.
//  * @return
//  *  nothing.
//  */
// void uwc_udp_set_ip(char* ip);

// /**
//  * @brief Set target UDP server port.
//  * @param port: Port of UDP server.
//  * @return
//  *  nothing.
//  */
// void uwc_udp_set_port(u16_t port);

/**
 * @brief Set target UDP server port.
 * @param sec: second.
 * @param usec: nanosecond.
 * @return
 *  nothing.
 */
void uwc_udp_set_timeout(u8_t sec, u8_t usec);

/**
 * @brief Initializing uwc_udp. Make sure setup SERV_IPV4 and SERV_PORT first.
 * @return
 *     ESP_OK:       Success.
 *     !ESP_OK:      Fail.
 */
esp_err_t uwc_udp_init();

/**
 * @brief Send data.
 * @param data: Data to send.
 * @return
 *     ESP_OK:       Success.
 *     !ESP_OK:      Fail.
 */
esp_err_t uwc_udp_send(char* data);

/**
 * @brief  Receive data. Use uwc_udp_on() for handling data received,
 * or access read buffer with uwc_udp_get_data().
 * @return
 *  Total bytes received.
 */
int uwc_udp_recv(void);

/**
 * @brief Get data received that stored in read buffer after uwc_udp_recv()
 * is called.
 * @return
 *  Pointer to the data.
 */
char* uwc_udp_get_data(void);

/**
 * @brief Get data received that stored in read buffer after uwc_udp_recv()
 is
 * called.
 * @param check: Check if data received is match with this parameter.
 * @return bool.
 */
bool uwc_udp_is_data_match(char* check);

/**
 * @brief Handling data with callback after uwc_udp_recv() is called.
 * @param data: Data to compare.
 * @param on_match: Callback do something if data received is match, set to
 * NULL if not needed.
 * @param on_unmatch: Callback do something if data received is unmatch, set
 * to NULL if not needed.
 * @return
 *  nothing.
 */
void uwc_udp_on(char* data, void on_match(), void on_unmatch());

/**
 * @brief Clear RX buffer and TX buffer.
 * @return
 *  nothing.
 */
void uwc_udp_flush(void);

// debug
void uwc_udp_debug(void);

/**
 * @brief Handling incoming data interactively with blocking.
 * @param msg: Message to show.
 * @param val_out: Store input to val_out.
 * @param show_echo: send back input.
 * @param remove_eol: remove any CR and any LF at End of Line.
 * @return
 *  nothing.
 */
void uwc_udp_input(char* msg, char* val_out, bool show_echo, bool remove_eol);

#endif
