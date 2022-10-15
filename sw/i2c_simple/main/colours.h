/**
 * @file Generic functions to manipulate colours
 */

#ifndef INTELLILIGHT_COLOURS_H
#define INTELLILIGHT_COLOURS_H

/**
 * @brief RGB definition
 */
struct rgb_colour
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
};

/**
 * @brief HSV definition
 */
struct hsv_colour
{
    unsigned char h;
    unsigned char s;
    unsigned char v;
};

/**
 * @brief Convert RGB to HSV
 * @param rgb RGB value to convert
 * @return HSV representation of the input RGB value
 */
extern struct hsv_colour colours_rgb_to_hsv(struct rgb_colour rgb);

#endif
