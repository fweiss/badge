# BT LE on ESP32

## Bluetooth setup

This is pretty standard stuff from the examples.

First, start with the controller.

1. initialize a ``esp_bt_controller_config_t`` object
2. initialize and configure the bt controller ``esp_bt_controller_init``
3. enable the bt controller and set the BT mode ``esp_bt_controller_enable``

Next the bluedroid stack.

1. initialize bluedroid ``esp_bluedroid_init``
2. enable bluedroid ``esp_bluedroid_enable``

Next register the callbacks

1. register the gatts callback ``esp_ble_gatts_register_callback``
2. register the gap callback ``esp_ble_gap_register_callback``

Finally register the BT app service(s)

1. register a service ``esp_ble_gatts_app_register``

Each of these calls returns a status code ``esp_err_t`` which should be checked after each call.

The BT address can be obtained, after bluedroid has been enabled, with ``esp_bt_dev_get_addres``.
The device name (shown in advertisement) can be set with ``esp_bt_dev_set_device_name``.

## Callbacks

After a service (app) is registered, a callback event cascade is started.
Each callback event may call other APIs which usually result in additional events.

### Service event patterns

- registering a service starts with ``esp_ble_gatts_app_register``
- services are identified by 16-bit service id
- the event ``ESP_GATTS_REG_EVT`` is dispatched
- the service is created with ``esp_ble_gatts_create_service``
- the event ``ESP_GATTS_CREATE_EVT`` is dispatched
- the service handle is made available for creating characteristics, etc.
- the service is started with ``esp_ble_gatts_start_service``
- the event ``ESP_GATTS_START_EVT`` is dispatched (what to do?)

Advertising is started in ``ESP_GATTS_REG_EVT``, but it seems that it should happen after the service
is started.



|| Main thread                || Callback thread              || Callback event        || Callback action              ||
| ----------------------------|-------------------------------|------------------------|-------------------------------|
| ``esp_ble_gatts_app_register`` | NA                            | ``ESP_GATTS_REG_EVT``   | ``esp_ble_gatts_create_service`` \\
                                                                                         ``esp_ble_gap_config_adv_data``  |
|                             | ``esp_ble_gatts_create_service`` | ``ESP_GATTS_CREATE_EVT`` | ``esp_ble_gatts_start_service`` |
|                             | ``esp_ble_gatts_start_service``  | ``ESP_GATTS_START_EVT``  |                               |

### Characteristc event patterns
For createing and managing characterics, use the following patterns.
Creating a characteristic requires a service handle.

- create a characteristic with ``esp_ble_gatts_add_char``.
- receive the event ``ESP_GATTS_ADD_CHAR_EVT`` (not sure what needs to be done)

### Characteristc data event patterns
The data events can be initiated from the service or from the client.

- client initiates a characteristic write
- receive the event ``ESP_GATTS_WRITE_EVT``

### Advertisement event patterns

- configure the advertising data with ``esp_ble_gap_config_adv_data``
- receive the event ``ESP_GAP_BLE_ADV_DATA_SET_COMPLETE_EVT``
- start advertising with ``esp_ble_gap_start_advertising``

## GATTS callback decoder
the gatts_event_handler in BLECore
swiatch on esp_gatts_cb_event_t
each event originates from a call
``typedef enum esp_gatts_cb_event_t`` in ``esp_gatts_api.h``

- event enum
- event param union ``esp_ble_gatts_cb_param_t``

api calls in 

| Event enum | Event param | Initiating call | Notes
|--- |--- |--- |---
| ESP_GATTS_REG_EVT | gatts_reg_evt_param |
| ESP_GATTS_READ_EVT | gatts_read_evt_param |
| ESP_GATTS_WRITE_EVT | gatts_write_evt_param | ::esp_ble_gatts_set_attr_value |
| ESP_GATTS_EXEC_WRITE_EVT | gatts_exec_write_evt_param |
| ESP_GATTS_MTU_EVT | gatts_mtu_evt_param |
| ESP_GATTS_CONF_EVT | gatts_conf_evt_param | esp_ble_gatts_send_indicate?
| ESP_GATTS_UNREG_EVT | na | esp_ble_gatts_app_unregister?
| ESP_GATTS_CREATE_EVT | gatts_create_evt_param | esp_ble_gatts_create_service?
| ESP_GATTS_ADD_INCL_SRVC_EVT | gatts_add_incl_srvc_evt_param | esp_ble_gatts_add_included_service?
| ESP_GATTS_ADD_CHAR_EVT | gatts_add_char_evt_param | esp_ble_gatts_add_char | 
| ESP_GATTS_ADD_CHAR_DESCR_EVT | gatts_add_char_descr_evt_param | esp_ble_gatts_add_char_descr | Descriptor is added to the previously added characteristic
| ESP_GATTS_DELETE_EVT | gatts_delete_evt_param | esp_ble_gatts_delete_service?
| ESP_GATTS_START_EVT | gatts_start_evt_param | esp_ble_gatts_start_service?
| ESP_GATTS_STOP_EVT | gatts_stop_evt_param | esp_ble_gatts_stop_service
| ESP_GATTS_CONNECT_EVT | gatts_connect_evt_param |
| ESP_GATTS_DISCONNECT_EVT | gatts_disconnect_evt_param |
| ESP_GATTS_OPEN_EVT | gatts_open_evt_param | esp_ble_gatts_open?
| ESP_GATTS_CANCEL_OPEN_EVT | gatts_cancel_open_evt_param |
| ESP_GATTS_CLOSE_EVT | gatts_close_evt_param | esp_ble_gatts_close?
| ESP_GATTS_LISTEN_EVT | na |
| ESP_GATTS_CONGEST_EVT | gatts_congest_evt_param |
| ESP_GATTS_RESPONSE_EVT | gatts_rsp_evt_param | esp_ble_gatts_send_response?
| ESP_GATTS_CREAT_ATTR_TAB_EVT | gatts_add_attr_tab_evt_param |
| ESP_GATTS_SET_ATTR_VAL_EVT | gatts_set_attr_val_evt_param | esp_ble_gatts_set_attr_value?
| ESP_GATTS_SEND_SERVICE_CHANGE_EVT | gatts_send_service_change_evt_param | esp_ble_gatts_send_service_change_indication?

others:
- esp_ble_gatts_send_indicate
- esp_ble_gatts_get_attr_value


## Bugs
Restart advertising upon receiving the event ``ESP_GATTS_DISCONNECT_EVT``.

Problems coexisting with RMT

No solve:
Component config > Bluetooth > Bluetooth controller > Coexistence Bluetooth Side Options

Looks good so far:
Component config > Bluetooth > Bluetooth controller > The cpu core which bluetooth controller run = 1
was 0
but bluedroid on core 0







