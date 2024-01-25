#include QMK_KEYBOARD_H

extern HSV layer_color_indicators[];

enum via_config_value {
    id_layer_indicator_color    = 1,
    id_autocorrect              = 2
};

void via_config_set_value(uint8_t *data);
void via_config_get_value(uint8_t *data);
void via_config_save(void);

void via_custom_value_command_kb(uint8_t *data, uint8_t length) {
    // data = [ command_id, channel_id, value_id, value_data ]
    uint8_t *command_id        = &(data[0]);
    uint8_t *channel_id        = &(data[1]);
    uint8_t *value_id_and_data = &(data[2]);

    if ( *channel_id == id_custom_channel ) {
        switch ( *command_id )
        {
            case id_custom_set_value:
            {
                via_config_set_value(value_id_and_data);
                break;
            }
            case id_custom_get_value:
            {
                via_config_get_value(value_id_and_data);
                break;
            }
            case id_custom_save:
            {
                via_config_save();
                break;
            }
            default:
            {
                // Unhandled message.
                *command_id = id_unhandled;
                break;
            }
        }
        return;
    }

    // Return the unhandled state
    *command_id = id_unhandled;

    // DO NOT call raw_hid_send(data,length) here, let caller do this
}

void via_config_set_value( uint8_t *data )
{
    // data = [ value_id, value_data ]
    uint8_t *value_id   = &(data[0]);
    uint8_t *value_data = &(data[1]);

    switch ( *value_id )
    {
        case id_autocorrect:
        {
            if (*value_data) {
                autocorrect_enable();
            } else {
                autocorrect_disable();
            }
            break;
        }
        case id_layer_indicator_color:
        {
            uint8_t layer = value_data[0]; // == 0,1,2
            if ( layer >= 0 && layer < 6 )
            {
                layer_color_indicators[layer].h = value_data[1];
                layer_color_indicators[layer].s = value_data[2];
                layer_color_indicators[layer].v = rgb_matrix_get_val();
            }
            break;
        }
    }
}

void via_config_get_value( uint8_t *data )
{
    // data = [ value_id, value_data ]
    uint8_t *value_id   = &(data[0]);
    uint8_t *value_data = &(data[1]);

    switch ( *value_id )
    {
        case id_autocorrect: {
            *value_data = autocorrect_is_enabled();
        }
        case id_layer_indicator_color:
        {
            uint8_t layer = value_data[0]; // == 0,1,2
            if ( layer >= 0 && layer < 6 )
            {
                // *value_data = 123;
                value_data[1] = layer_color_indicators[layer].h;
                value_data[2] = layer_color_indicators[layer].s;
            }

            break;
        }
    }
}

void via_config_save(void)
{
    // eeprom_update_block( &g_buttglow_config,
    //     ((void*)BUTTGLOW_CONFIG_EEPROM_ADDR),
    //     sizeof(buttglow_config) );
}
