#include <LittleFS.h>
#include "./fs.hpp"

const char *LOG_FILE_PATH = "/mini-power.log";
File LOG_FILE;

void IntializeLittleFs()
{
    if (!LittleFS.begin(true))
    {
        Serial.println("LittleFS Mount Failed");
    }

    /*
    if (!LittleFS.format())
    {
        Serial.println("LittleFS Format Failed");
    }
*/
    LOG_FILE = LittleFS.open(LOG_FILE_PATH, FILE_WRITE);

    PushLog("initialized");
}

bool PushLog(const char *line)
{
    if (!LOG_FILE)
    {
        Serial.println("failed to open file");
        return false;
    }

    if (LOG_FILE.println((String() + millis() + ":\t" + line).c_str()))
    {
        LOG_FILE.flush();
        Serial.println("log appended");
        return true;
    }
    else
    {
        Serial.println("log append failed");
        return false;
    }
}
