# COMM
Notes and learning about badge communication over BLE.

# MTU size
Android 20

This limits how much can be sent in one message. So how to send a 64*3 bute frame?

Need to use some kind of streaming or serial protocol. The AT has SPP, but GATT, for good reason or not, does not.

[Discussion of serial over BLE, but not very conclusive](https://punchthrough.com/serial-over-ble/)

## SPP
- 1101 service class
- 0002 RFCOMM protocol

## Issues

``undefined reference to `esp_spp_init'``
In menuconfig:
Component config > Bluetooth > Bluedroid Options
classic bluetooth > SPP

``Error: app partition is too small for binary badge.bin size 0x105f40``
Partition Table > Partition Table
try Single factory app (large), no OTA

changed device name to ESP_SPP_ACCEPTOR, instad of BADGE

## Notes and references

https://www.youtube.com/watch?v=FvIywveUVZw

NORDIC UART SERVICE

LSB-MSB
9ECA  DC24 0EE5 A9E0 93F3 A3B5 0100 406E

esp_spp_api:
0x00, 0x00, 0x11, 0x01, 0x00, 0x00, 0x10, 0x00,
                                    0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB

According to Nordic:
https://infocenter.nordicsemi.com/index.jsp?topic=%2Fcom.nordic.infocenter.sdk5.v14.0.0%2Fble_sdk_app_nus_eval.html

The 128-bit vendor-specific UUID of the Nordic UART Service is 6E400001-B5A3-F393-E0A9-E50E24DCCA9E (16-bit offset: 0x0001).

RX Characteristic (UUID: 6E400002-B5A3-F393-E0A9-E50E24DCCA9E)
The peer can send data to the device by writing to the RX Characteristic of the service. ATT Write Request or ATT Write Command can be used. The received data is sent on the UART interface.

TX Characteristic (UUID: 6E400003-B5A3-F393-E0A9-E50E24DCCA9E)
If the peer has enabled notifications for the TX Characteristic, the application can send data to the peer as notifications. The application will transmit all data received over UART as notifications.

Confusion about
- Nordic UART service
- Classic BT SPP - Serial Protocol Profile
- ESP32 SPP - Secure Simple Pairing (referenced in the example code)

maybe look in
``./components/bt/host/bluedroid/hci/hci_hal_h4.c:static void event_uart_has_bytes(fixed_queue_t *queue);``
``./components/bt/host/nimble/nimble/nimble/transport/uart/include/transport/uart/ble_hci_uart.h:void ble_hci_uart_init(void);
``
``./examples/bluetooth/bluedroid/ble/ble_spp_client/README.md:  The server will receive this data in the ESP_GATTS_WRITE_EVT event and send data to the Uart terminal by `uart_wrire_bytes` function. For example:
``

### others
https://openlabpro.com/guide/ble-uart-on-esp32-controller/

https://github.com/ThingEngineer/ESP32_BLE_client_uart

## Schema
Example: nRF52 DK (peer) - nRF UART app (app)

For badge, the ESP32 is the peer and the phone has the app.
> For testing, the app is nRF UART, etc.

On the app, thus we need:

- UART Service

    - rx characteristic (peer send to device as write)
    
  - tx characteristic (app send to peer via notify)


  > On nRF UART write data as command, not request.


