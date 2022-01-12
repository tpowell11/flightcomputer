/*
Device error header
(c) Tom Powell, under the GPL
*/


namespace err{
    const char* base[100] = 
    {
        "base:noChip",
        "base:lowVoltage",
        "base:overVoltage",
        "base:unknown"
    };
    const char* imu[100] = 
    {
        "imu:overflow"
    };
}