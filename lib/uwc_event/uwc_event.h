/*
 * This file is part of the wawan-ikhwan project.
 * Copyright (c) 2022 Muhammad Ikhwan Perwira <ikhwanperwira@gmail.com>
 *
 * udp-wifi-camera event.
 *
 */

#ifndef __UWC_EVENT_H__
#define __UWC_EVENT_H__

#include "esp_err.h"
#include "uwc_cam.h"
#include "uwc_eolremover.h"
#include "uwc_led.h"
#include "uwc_nvs.h"
#include "uwc_tag.h"
#include "uwc_uart.h"
#include "uwc_udp.h"
#include "uwc_wifi.h"

// Type for uwcEvent_t
typedef void uwcEvent_t;

// Error variable that will be usage by any event.
esp_err_t uwcEventErr;

/**
 * @brief initializing built-in LED.
 */
uwcEvent_t uwc_event_led_init(void);

/**
 * @brief Set on LED.
 */
uwcEvent_t uwc_event_led_set_on(void);

/**
 * @brief Set off LED.
 */
uwcEvent_t uwc_event_led_set_off(void);

/**
 * @brief Init camera.
 */
uwcEvent_t uwc_event_cam_init(void);

/**
 * @brief Deinit camera.
 */
uwcEvent_t uwc_event_cam_deinit(void);

/**
 * @brief Init NVS.
 */
uwcEvent_t uwc_event_nvs_init(void);

/**
 * @brief Open NVS with using namespace "uwc".
 */
uwcEvent_t uwc_event_nvs_open(void);

/**
 * @brief Read SSID from NVS.
 */
uwcEvent_t uwc_event_nvs_read_ssid(void);

/**
 * @brief Write SSID from NVS.
 */
uwcEvent_t uwc_event_nvs_write_ssid(void);

/**
 * @brief Erase SSID from NVS.
 */
uwcEvent_t uwc_event_nvs_erase_ssid(void);

/**
 * @brief Read PASW from NVS.
 */
uwcEvent_t uwc_event_nvs_read_pasw(void);

/**
 * @brief Write PASW from NVS.
 */
uwcEvent_t uwc_event_nvs_write_pasw(void);

/**
 * @brief Erase PASW from NVS.
 */
uwcEvent_t uwc_event_nvs_erase_pasw(void);

/**
 * @brief Commit changes WiFI auth into NVS.
 */
uwcEvent_t uwc_event_nvs_commit_auth(void);

/**
 * @brief Close NVS with namespace "uwc".
 */
uwcEvent_t uwc_event_nvs_close(void);

/**
 * @brief Init WiFI.
 */
uwcEvent_t uwc_event_wifi_init(void);

/**
 * @brief Setup new SSID and new PASW.
 */
uwcEvent_t uwc_event_wifi_setup(void);

/**
 * @brief Show WiFi connected info.
 */
uwcEvent_t uwc_event_wifi_info(void);

/**
 * @brief Deinit WiFI.
 */
uwcEvent_t uwc_event_wifi_deinit(void);

/**
 * @brief Init UDP.
 */
uwcEvent_t uwc_event_udp_init(void);

#endif
