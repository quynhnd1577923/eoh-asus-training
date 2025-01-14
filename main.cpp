/*************************************************************
  Download latest ERa library here:
    https://github.com/eoh-jsc/era-lib/releases/latest
    https://www.arduino.cc/reference/en/libraries/era
    https://registry.platformio.org/libraries/eoh-ltd/ERa/installation

    ERa website:                https://e-ra.io
    ERa blog:                   https://iotasia.org
    ERa forum:                  https://forum.eoh.io
    Follow us:                  https://www.fb.com/EoHPlatform
 *************************************************************/

// Enable debug console
// #define ERA_DEBUG
// #define ERA_SERIAL stdout

// Enable Modbus
#include <ERaSimpleMBLinux.hpp>

// Enable Modbus and Zigbee
// #include <ERaLinux.hpp>
#include <ERaOptionsArgs.hpp>
#include <ERaConsole.h>

static const char* auth;
static const char* boardID;
static const char* host;
static uint16_t port;
static const char* user;
static const char* pass;

static int devBaud = 115200;
static const char* devName = "/dev/serial/by-id/usb-1a86_USB2.0-Ser_-if00-port0";

ERaSerialLinux serial;
ERaConsole console(serial);

/* This function will run every time ERa is connected */
ERA_CONNECTED() {
    printf("ERa connected!\r\n");
}

/* This function will run every time ERa is disconnected */
ERA_DISCONNECTED() {
    printf("ERa disconnected!\r\n");
}

/* This function print uptime every second */
void timerEvent() {
    console.requestHumidity(100);
    console.requestTemperature(100);
    console.requestDistance(100);
    printf("Uptime: %d\r\n", ERaMillis() / 1000L);
}

void setup() {
    serial.begin(devName, devBaud);

    ERa.setAppLoop(false);
    ERa.setBoardID(boardID);
    ERa.begin(auth, host, port, user, pass);
    ERa.addInterval(1000L, timerEvent);
}

void loop() {
    ERa.run();
    console.run();
  int sds=this->stream.read();
  ERa.virtualWrite(V0, sds);
}

int main(int argc, char* argv[]) {
    processArgs(argc, argv, auth, boardID,
                host, port, user, pass);

    setup();
    while (1) {
        loop();
    }

    return 0;
}
