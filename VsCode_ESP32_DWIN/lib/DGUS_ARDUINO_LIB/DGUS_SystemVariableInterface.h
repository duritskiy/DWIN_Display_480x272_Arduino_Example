#ifndef DGUS_SystemVariableInterfaceH
#define DGUS_SystemVariableInterfaceH

#include "DGUS_T5LProtocol.h"
#include "display/idgus_reg.h"
#include "idgus_util.h"


class DGUS_SystemVariableInterface
{

  public:

		DwinT5LProtocol &dgus;   

private:
	
public:



/**
 * @brief Get the currently displayed page ID number
 *
 * @param page a pointer the page id variable
 * @return #bool
 */
  bool get_page(uint16_t &page);

  /**
   * @brief Change DGUS page
   *
   * @param page page id
   * @return #bool
   */
  bool set_page(uint16_t page);

  bool Setup_CRC_Mode(void);

  /**
   * @brief Change an icon to index val
   *
   * @param icon_addr VP of the icon
   * @param val index to set to
   * @return #bool
   */
  // bool set_icon(uint16_t icon_addr, uint8_t val) {}

  /**
   * @brief Get the current brightness for the display
   *
   * @param brightness value from 0 - 100%
   * @return #bool
   */
  bool get_LedConfig(dgus_cmd_led_config &LedConfig);

  /**
   * @brief Get the current brightness for the display
   *
   * @param brightness value from 0 - 100%
   * @return #bool
   */
  bool set_LedConfig(dgus_cmd_led_config &LedConfig);

  /**
   * @brief Get the current volume
   *
   * @param volume pointer. 0-255 volume
   * @return #bool
   */
  bool get_volume(uint8_t *volume);

  /**
   * @brief Set the current volume level
   *
   * @param volume 0-255
   * @return #bool
   */
  bool set_volume(uint8_t volume);

  /**
   * @brief Reset the DGUS display
   *
   * @param full_reset 0 or 1. 1 will perform a full reset including T5 chip, NAND and all peripherals
   * @return #bool
   */
  bool system_reset(uint8_t full_reset);

  /**
   * @brief Read the system configuration variable
   *
   * @param config
   * @return #bool
   */
  bool get_system_config(dgus_cmd_system_config &config);
  bool set_system_config(dgus_cmd_system_config &config);

  /**
   * @brief PLay a stored wav by id
   *
   * @param sound_id id of the wav from the designer
   * @param section_id section of the wav to play
   * @param volume
   * @param play_mode 0x0 stop, 0x1 pause, 0x2 play || or  section_id to loop back to (firmware version dependant)
   * @return #bool
   */
  // bool dgus_play_sound(uint8_t sound_id, uint8_t section_id, uint8_t volume, uint8_t play_mode);

  DGUS_SystemVariableInterface(DwinT5LProtocol &_dgus) : dgus(_dgus){};
  ~DGUS_SystemVariableInterface(){};
};






#endif