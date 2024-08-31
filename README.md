## Arduino example code for the WADX0080 board
This shows how to communicate with the LCD controller found on ABB's board WADX0080.

## WADX0080 pinout
Board contains an onboard `Vee` generator (for the LCD contrast) based around the `ICL7660`, and a `74HC164` logic gate. The LCD controller is a `S6A0069` made by Samsung.

The `74HC164` is a shift register, which converts serial data to parallel. In fact, the LCD controller's data input is connected directly to this gate's parallel output, thus, reducing the required signals to control it. It's not possible to read data back from the LCD controller; only write is possible.

There's a flexible ribbon cable that goes to the main unit, whose pinout is as follows:

| Flex connector pin | Connection |
|--------------------|------------|
| 1                  | Vcc (around 10v, a zener regulates 5v on the board) |
| 3                  | GND        |
| 5                  | LCD controller pin `E` |
| 6                  | LCD controller pin `RS` |
| 12                 | 74HC164 serial data input |
| 13                 | 74HC164 serial data clock |

## Arduino test
In order to test this board, you need to connect it as follows:

| Arduino Nano pin | Flex connector pin | Meaning |
|------------------|--------------------|---------|
| D2               | 6                  | LCD `RS`|
| D3               | 5                  | LCD `E` |
| D11              | 12                 | 74HC164 serial data input |
| D13              | 13                 | 74HC164 serial data clock |

The code uses `SPI` to write data into the `74HC164`, and two additional lines to control the LCD controller.
