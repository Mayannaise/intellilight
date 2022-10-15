/**
 * @file Generic functions to manipulate colours
 */
 
/* local includes */
#include "colours.h"


struct hsv_colour colours_rgb_to_hsv(struct rgb_colour rgb)
{
    struct hsv_colour hsv;
    
    /* calculate HSV "value" component */
    const unsigned char rgb_min = rgb.r < rgb.g ? (rgb.r < rgb.b ? rgb.r : rgb.b) : (rgb.g < rgb.b ? rgb.g : rgb.b);
    const unsigned char rgb_max = rgb.r > rgb.g ? (rgb.r > rgb.b ? rgb.r : rgb.b) : (rgb.g > rgb.b ? rgb.g : rgb.b);
    const unsigned char rgb_delta = rgb_max - rgb_min;
    hsv.v = rgb_max;

    /* calculate HSV "saturation" component */
    if (hsv.v == 0) {
        hsv.s = 0;
    } else {
        hsv.s = 255 * ((float)rgb_delta / (float)rgb_max);
    }

    /* calculate HSV "hue" component */
    const unsigned char sixty_degrees = 255.0 / (360.0 / 60.0);
    if (rgb_delta == 0) {
        hsv.h = 0;
    } else if (rgb_max == rgb.r) {
        hsv.h = 0 + sixty_degrees * ((rgb.g - rgb.b) / (float)rgb_delta);
    } else if (rgb_max == rgb.g) {
        hsv.h = 85 + sixty_degrees * ((rgb.b - rgb.r) / (float)rgb_delta);
    } else if (rgb_max == rgb.b) {
        hsv.h = 171 + sixty_degrees * ((rgb.r - rgb.g) / (float)rgb_delta);
    }

    return hsv;
}
