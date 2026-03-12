/* ---------------------------------------------------------
   PROJECT: YAHYA OPTIMIZER (ULTIMATE EDITION)
   DEVELOPER: YAHYA (EGYPT)
   YEAR: 2026
   COPYRIGHT: All Rights Reserved.
   --------------------------------------------------------- */

#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include <cstdlib>
#include <chrono> // [1]
#include <thread> // [2]

using namespace std;

int getCPUtemp() {
    #ifdef __linux__
        ifstream tempFile("/sys/class/thermal/thermal_zone0/temp"); // [3]
        int temp = 0;
        if (tempFile.is_open()) {
            tempFile >> temp;
            tempFile.close();
            return temp / 1000;
        }
    #endif
    return 0;
}

int main() {
    cout << "==========================================" << endl;
    cout << "      YAHYA OPTIMIZER - ULTIMATE          " << endl;
    cout << "     HARDWARE & SOFTWARE SYNCED           " << endl;
    cout << "==========================================" << endl;

    while (true) {
        auto start_task = chrono::steady_clock::now(); // [4]

        #ifdef _WIN32
            system("powercfg /setactive 8c5e7fda-e8bf-4a96-9a85-a6e23a8c635c"); // [5]
            system("del /s /f /q %temp%\\*.* > nul 2>&1"); // [6]
        #elif __linux__
            int currentTemp = getCPUtemp(); // [7]
            if (currentTemp >= 65) {
                system("echo 255 | sudo tee /sys/class/hwmon/hwmon*/pwm1 > /dev/null 2>&1"); // [8]
            } 
            else if (currentTemp >= 45) {
                system("echo 150 | sudo tee /sys/class/hwmon/hwmon*/pwm1 > /dev/null 2>&1"); // [9]
            } 
            else {
                system("echo 80 | sudo tee /sys/class/hwmon/hwmon*/pwm1 > /dev/null 2>&1"); // [10]
            }
            system("echo performance | sudo tee /sys/devices/system/cpu/cpu*/cpufreq/scaling_governor > /dev/null 2>&1"); // [11]
            system("sudo sync; echo 3 | sudo tee /proc/sys/vm/drop_caches > /dev/null"); // [12]
        #elif __APPLE__
            system("sudo purge"); // [13]
        #endif

        auto end_task = chrono::steady_clock::now(); // [14]
        auto duration = chrono::duration_cast<chrono::milliseconds>(end_task - start_task).count(); // [15]

        if (duration < 50) {
            this_thread::sleep_for(chrono::seconds(5)); // [16]
        } else {
            this_thread::sleep_for(chrono::seconds(2)); // [17]
        }
    }

    return 0;
}
