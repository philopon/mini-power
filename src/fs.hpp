#pragma once

extern const char *LOG_FILE_PATH;

void IntializeLittleFs();
bool PushLog(const char *line);
