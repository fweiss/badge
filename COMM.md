# COMM
Notes and learning about badge communication over BLE.

# MTU size
Android 20

This limits how much can be sent in one message. So how to send a 64*3 bute frame?

Need to use some kind of streaming or serial protocol. The AT has SPP, but GATT, for good reason or not, does not.

[Discussion of serial over BLE, but not very conclusive](https://punchthrough.com/serial-over-ble/)

