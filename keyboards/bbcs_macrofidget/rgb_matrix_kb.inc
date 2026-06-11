RGB_MATRIX_EFFECT(RED_ORANGE_WAVE_WHITE_SPLASH)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

static bool RED_ORANGE_WAVE_WHITE_SPLASH(effect_params_t *params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    uint8_t time  = scale16by8(g_rgb_timer, qadd8(rgb_matrix_config.speed / 4, 1));
    uint8_t count = g_last_hit_tracker.count;

    for (uint8_t i = led_min; i < led_max; i++) {
        RGB_MATRIX_TEST_LED_FLAGS();

        hsv_t hsv = rgb_matrix_config.hsv;
        hsv.h     = hsv.h + scale8(abs8(g_led_config.point[i].x - time), 24);

        uint8_t white_amount = 0;
        for (uint8_t j = 0; j < count; j++) {
            int16_t  dx     = g_led_config.point[i].x - g_last_hit_tracker.x[j];
            int16_t  dy     = g_led_config.point[i].y - g_last_hit_tracker.y[j];
            uint8_t  dist   = sqrt16(dx * dx + dy * dy);
            uint16_t tick   = scale16by8(g_last_hit_tracker.tick[j], qadd8(rgb_matrix_config.speed, 1)) * 2;
            uint16_t effect = tick - dist;
            if (effect > 255) effect = 255;
            uint8_t peak        = 255 - effect;
            uint8_t attenuation = qsub8(255, dist * 3);
            white_amount        = qadd8(white_amount, scale8(peak, attenuation));
        }

        hsv.s = qsub8(hsv.s, white_amount);
        hsv.v = qadd8(hsv.v, white_amount);

        rgb_t rgb = rgb_matrix_hsv_to_rgb(hsv);
        rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
    }
    return rgb_matrix_check_finished_leds(led_max);
}

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
