/*
 * Copyright (c) 2022 Esco Medical ApS
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef ZEPHYR_INCLUDE_DRIVERS_LED_STRIP_WS2812_PIO_H_
#define ZEPHYR_INCLUDE_DRIVERS_LED_STRIP_WS2812_PIO_H_

#include <zephyr/drivers/led_strip.h>

/**
 * @brief Set the global brightness control levels for the tlc5971 strip.
 *
 * change will take effect on next update of the led strip
 *
 * @param dev LED strip device
 * @param pixel global brightness values for RGB channels

 * @return 0 on success, negative on error
 */

typedef uint32_t (*led_api_color_converter)(struct led_rgb*);

#define CONVERT_TO_BGR(bgra)   (*((uint32_t*)bgra) >> 8)

static inline uint32_t led_strip_convert_to_bgr0(struct led_rgb* bgra) { 
     return CONVERT_TO_BGR(bgra) << 8; 
}
static inline uint32_t led_strip_convert_to_rbg0(struct led_rgb* bgra) { 
    return (CONVERT_TO_BGR(bgra) | ((CONVERT_TO_BGR(bgra) & 0x00FF) << 24)) & 0xFFFFFF00; 
}
static inline uint32_t led_strip_convert_to_grb0(struct led_rgb* bgra) { 
    return ((CONVERT_TO_BGR(bgra) >> 8) | (CONVERT_TO_BGR(bgra) << 16)) & 0xFFFFFF00; 
}

static inline uint32_t led_strip_swap_baxx(uint32_t abxx) {
	uint32_t tmpa = (abxx >> 8) & 0x00FF0000;
	uint32_t tmpb = (abxx & 0x00FF0000) << 8;
	return (abxx & 0x0000FFFF) | tmpb | tmpa;
}

static inline uint32_t led_strip_convert_to_gbr0(struct led_rgb* bgra) { return led_strip_swap_baxx(led_strip_convert_to_bgr0(bgra)); }
static inline uint32_t led_strip_convert_to_brg0(struct led_rgb* bgra) { return led_strip_swap_baxx(led_strip_convert_to_rbg0(bgra)); }
static inline uint32_t led_strip_convert_to_rgb0(struct led_rgb* bgra) { return led_strip_swap_baxx(led_strip_convert_to_grb0(bgra)); }

#endif /* ZEPHYR_INCLUDE_DRIVERS_LED_STRIP_WS2812_PIO_H_ */