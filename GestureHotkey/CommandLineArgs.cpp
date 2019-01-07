#include "CommandLineArgs.h"
#include <cstring>
#include <exception>
#include <regex>

static bool ParseRect(const std::string &str, Rect<int> *out)
{
    std::regex re("(\\d+),(\\d+),(\\d+),(\\d+)");
    std::smatch match;
    if (!std::regex_match(str, match, re))
        return false;
    int x1, y1, x2, y2;
    try {
        x1 = std::stoi(match[1].str());
        y1 = std::stoi(match[2].str());
        x2 = std::stoi(match[3].str());
        y2 = std::stoi(match[4].str());
    } catch (const std::invalid_argument &) {
        return false;
    } catch (const std::out_of_range &) {
        return false;
    }
    if (x1 > x2)
        return false;
    if (y1 > y2)
        return false;
    out->x1 = x1;
    out->y1 = y1;
    out->x2 = x2;
    out->y2 = y2;
    return true;
}

static bool ParsePercent(const std::string &str, int *out)
{
    int value;
    try {
        value = std::stoi(str);
    } catch (const std::invalid_argument &) {
        return false;
    } catch (const std::out_of_range &) {
        return false;
    }
    if (value < 0 || value > 100)
        return false;
    *out = value;
    return true;
}

CommandLineArgs::CommandLineArgs(int argc, char *argv[])
{
    for (int i = 1; i < argc; ++i) {
        if (std::strcmp(argv[i], "-t") == 0 && i < argc - 1) {
            if (!ParseRect(argv[++i], &touchpadRect))
                return;
        } else if (std::strcmp(argv[i], "-s") == 0 && i < argc - 1) {
            if (!ParseRect(argv[++i], &screenRect))
                return;
        } else if (std::strcmp(argv[i], "-w") == 0 && i < argc - 1) {
            if (!ParsePercent(argv[++i], &smoothingWeight))
                return;
        } else if (std::strcmp(argv[i], "-m") == 0) {
            manageTouchpad = true;
        } else if (std::strcmp(argv[i], "-c") == 0) {
            sendClick = true;
        } else {
            return;
        }
    }
    ok = true;
}
