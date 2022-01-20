#ifndef dgus_displayH
#define dgus_displayH

#include "Arduino.h"
#include "utils/swap_endian.h"
#include "display/TColor16Bit.h"


#pragma pack(push, 1)

/**
 * @brief position and size of the control
 * 
 * @return typedef struct 
 */
typedef struct dgus_control_size 
{
  uint16_t_BigEndian x_top;
  uint16_t_BigEndian y_top;
  uint16_t_BigEndian x_bottom;
  uint16_t_BigEndian y_bottom;
} dgus_control_size;            /**< xy position and size of control */
#pragma pack(pop)

/**
 * @brief The position of the control in x,y from the top left of the display
 * 
 * @return typedef struct 
 */

#pragma pack(push, 1)
typedef struct dgus_control_position 
{
  uint16_t_BigEndian x;
  uint16_t_BigEndian y;
} dgus_control_position;        /**< xy position of control */
#pragma pack(pop)



#pragma pack(push, 1)
typedef struct var_icon
{
    uint16_t_BigEndian VP;
    uint16_t_BigEndian x;
    uint16_t_BigEndian y;
    uint16_t_BigEndian v_min;
    uint16_t_BigEndian v_max;
    uint16_t_BigEndian icon_min;
    uint16_t_BigEndian icon_max;
    uint8_t icon_lib;
    uint8_t mode;
    uint8_t layer_mode;
    uint8_t icon_gamma;
    uint8_t pic_gamma;
    uint8_t filter_set;
} var_icon; /**< Icon Data */
#pragma pack(pop)


#pragma pack(push, 1)
typedef struct animation_icon
{
    uint16_t_BigEndian VP;
    uint16_t_BigEndian x;
    uint16_t_BigEndian y;
    uint16_t_BigEndian reset_icon;
    uint16_t_BigEndian v_stop;
    uint16_t_BigEndian v_start;
    uint16_t_BigEndian icon_stop;
    uint16_t_BigEndian icon_start;
    uint16_t_BigEndian icon_end;
    uint8_t icon_lib;
    uint8_t mode;
    uint8_t layer_mode;
    uint8_t icon_gamma;
    uint8_t pic_gamma;
    uint8_t time;
    uint8_t display_mode;
    uint8_t filter_set;
} animation_icon; /**< Animation Icon Data */
#pragma pack(pop)


#pragma pack(push, 1)
typedef struct slider_display
{
    uint16_t_BigEndian VP;
    uint16_t_BigEndian v_begin;
    uint16_t_BigEndian v_end;
    uint16_t_BigEndian x_begin;
    uint16_t_BigEndian x_end;
    uint16_t_BigEndian icon_id;
    uint16_t_BigEndian y;
    uint8_t x_adj;
    uint8_t mode;
    uint8_t icon_lib;
    uint8_t icon_mode;
    uint8_t vp_data_mode;
    uint8_t layer_mode;
    uint8_t icon_gamma;
    uint8_t pic_gamma;
    uint8_t filter_set;
} slider_display; /**< Slider Data */
#pragma pack(pop)


#pragma pack(push, 1)
typedef struct artistic_var
{
    uint16_t_BigEndian VP;
    uint16_t_BigEndian x;
    uint16_t_BigEndian y;
    uint16_t_BigEndian icon_0;
    uint8_t icon_lib;
    uint8_t icon_mode;
    uint8_t integer_digits;
    uint8_t decimal_digits;
    uint8_t vp_mode;
    uint8_t alignment;
    uint8_t layer_mode;
    uint8_t icon_gamma;
    uint8_t pic_gamma;
    uint8_t filter_set;
} artistic_var; /**< Artistic Data */
#pragma pack(pop)


#pragma pack(push, 1)
typedef struct image_animation
{
    uint16_t_BigEndian zero;
    uint16_t_BigEndian pic_begin;
    uint16_t_BigEndian pic_end;
    uint8_t frame_time;
    uint8_t icl_Lib_id;
    uint8_t pic_end_exp;
    uint8_t reserved[16];
} image_animation; /**< Image Animation Data */
#pragma pack(pop)


#pragma pack(push, 1)
typedef struct icon_rotation
{
    uint16_t_BigEndian VP;
    uint16_t_BigEndian icon_id;
    uint16_t_BigEndian icon_xc;
    uint16_t_BigEndian icon_yc;
    uint16_t_BigEndian xc;
    uint16_t_BigEndian yc;
    uint16_t_BigEndian v_begin;
    uint16_t_BigEndian v_end;
    uint16_t_BigEndian al_begin;
    uint16_t_BigEndian al_end;
    uint8_t vp_mode;
    uint8_t lib_id;
    uint8_t mode;
} icon_rotation; /**< Icon Rotation Data */
#pragma pack(pop)


#pragma pack(push, 1)
typedef struct bit_var_icon
{
    uint16_t_BigEndian VP;
    uint16_t_BigEndian vp_aux;
    uint8_t display_mode;
    uint8_t move_mode;
    uint8_t icon_mode;
    uint8_t icon_lib;
    uint16_t_BigEndian icon_0_s;
    uint16_t_BigEndian icon_0_e;
    uint16_t_BigEndian icon_1_s;
    uint16_t_BigEndian icon_1_e;
    uint16_t_BigEndian x;
    uint16_t_BigEndian y;
    uint16_t_BigEndian dismove;
    uint16_t_BigEndian reserved;
} bit_var_icon; /**< Bit Var Icon Data */
#pragma pack(pop)


#pragma pack(push, 1)
typedef struct data_var
{
    uint16_t_BigEndian VP;
    uint16_t_BigEndian x;
    uint16_t_BigEndian y;
    uint16_t_BigEndian Color;
    uint8_t lib_id;
    uint8_t font_width;
    uint8_t alignment;
    uint8_t integer_digits;
    uint8_t decimal_digits;
    uint8_t vp_mode;
    uint8_t len_unit;
    uint8_t string_unit[];
} data_var; /**< Data Var Data */
#pragma pack(pop)


#pragma pack(push, 1)
typedef struct rtc_display_digital
{
    uint16_t_BigEndian zero;
    uint16_t_BigEndian x;
    uint16_t_BigEndian y;
    uint16_t_BigEndian Color;
    uint8_t lib_id;
    uint8_t font_width;
    uint8_t string_code[]; // max 15
} rtc_display_digital;     /**< RTC Data */
#pragma pack(pop)


#pragma pack(push, 1)
typedef struct rtc_display_analogue
{
    uint16_t_BigEndian one; // literally 0x0001
    uint16_t_BigEndian x;
    uint16_t_BigEndian y;
    uint16_t_BigEndian icon_hour;
    uint32_t_BigEndian icon_hour_central;
    uint16_t_BigEndian icon_minute;
    uint32_t_BigEndian icon_minute_central;
    uint16_t_BigEndian icon_second;
    uint32_t_BigEndian icon_second_central;
    uint8_t lib_id;
    uint8_t reserved;
} rtc_display_analogue; /**< RTC Display Data */
#pragma pack(pop)


#pragma pack(push, 1)
typedef struct hex_data
{
    uint16_t_BigEndian VP;
    uint16_t_BigEndian x;
    uint16_t_BigEndian y;
    uint8_t mode;
    uint8_t lib_id;
    uint8_t font_x;
    uint8_t string_code[]; // max 15
} hex_data;                /**< Hex Data */
#pragma pack(pop)


#pragma pack(push, 1)
typedef struct roll_text
{
    uint16_t_BigEndian VP;
    uint8_t rolling_mode;
    uint8_t rolling_distance_px;
    uint8_t adjust_mode;
    uint8_t reserved_00;
    uint16_t_BigEndian Color;
    uint16_t_BigEndian x_start;
    uint16_t_BigEndian y_start;
    uint16_t_BigEndian x_end;
    uint16_t_BigEndian y_end;
    uint8_t font_0_id;
    uint8_t font_1_id;
    uint8_t font_x_dots;
    uint8_t font_y_dots;
    uint8_t encode_mode;
    uint8_t text_distance_px;
    uint32_t_BigEndian reserved;
} roll_text; /**< Rolling Text Data */
#pragma pack(pop)


#pragma pack(push, 1)
typedef struct data_window
{
    uint16_t_BigEndian VP;
    uint8_t v_min;
    uint8_t v_max;
    uint8_t integer_digits;
    uint8_t decimal_digits;
    uint8_t data_num;
    uint8_t mode;
    uint16_t_BigEndian x;
    uint16_t_BigEndian y;
    uint16_t_BigEndian adjust_step;
    uint8_t font_x_dots;
    uint8_t font_y_dots;
    uint16_t_BigEndian Color;
    uint8_t font_x_dots1;
    uint8_t font_y_dots1;
    uint16_t_BigEndian colour1;
    uint16_t_BigEndian reserved;
} data_window; /**< Window Data */
#pragma pack(pop)


#pragma pack(push, 1)
typedef struct basic_graphic
{
    uint16_t_BigEndian VP;
    uint8_t area[8];
    uint8_t dashed_line_enable;
    uint8_t dash_set[4];
    uint8_t pixel_scale[13];
} basic_graphic; /**< Graphic Data */
#pragma pack(pop)


#pragma pack(push, 1)
typedef struct zone_rolling
{
    uint16_t_BigEndian x_start;
    uint16_t_BigEndian y_start;
    uint16_t_BigEndian x_end;
    uint16_t_BigEndian y_end;
    uint16_t_BigEndian distance_move;
    uint16_t_BigEndian mode_move;
} zone_rolling; /**< Zone Data */
#pragma pack(pop)


#pragma pack(push, 1)
typedef struct qr_code
{
    uint16_t_BigEndian VP;
    uint16_t_BigEndian x;
    uint16_t_BigEndian y;
    uint16_t_BigEndian unit_pixels;
    uint8_t fix_mode;
    uint8_t reserved_0;
} qr_code; /**< QR Data */
#pragma pack(pop)


#pragma pack(push, 1)
typedef struct area_brightness
{
    uint16_t_BigEndian VP;
    uint16_t_BigEndian x_start;
    uint16_t_BigEndian y_start;
    uint16_t_BigEndian x_end;
    uint16_t_BigEndian y_end;
} area_brightness; /**< Area Brightness Data */
#pragma pack(pop)



#endif
