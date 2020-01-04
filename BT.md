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

## Bugs
Restart advertising upon receiving the event ``ESP_GATTS_DISCONNECT_EVT``.

Problems coexisting with RMT

No solve:
Component config > Bluetooth > Bluetooth controller > Coexistence Bluetooth Side Options

Looks good so far:
Component config > Bluetooth > Bluetooth controller > The cpu core which bluetooth controller run = 1
was 0
but bluedroid on core 0







