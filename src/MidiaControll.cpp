#include "MidiaControll.hpp"
#include <iostream>
#include <cstdlib>

#ifdef _WIN32
#include <windows.h>
#pragma comment(lib, "winmm.lib")
#endif

void MidiaControll::playAudio(const std::string &baseFilePath)
{
    std::string filePath;

#ifdef _WIN32
    filePath = baseFilePath + ".wav";
    PlaySound(filePath.c_str(), NULL, SND_FILENAME | SND_ASYNC);
#elif __APPLE__
    filePath = baseFilePath + ".mp3";
    std::string command = "afplay " + filePath + " &";
    if (system(command.c_str()) != 0)
    {
        std::cerr << "Erro ao tentar reproduzir áudio no macOS." << std::endl;
    }
#elif __linux__
    filePath = baseFilePath + ".ogg";
    std::string command = "ogg123 " + filePath + " &";
    if (system(command.c_str()) != 0)
    {
        std::cerr << "Erro ao tentar reproduzir áudio no Linux." << std::endl;
    }
#else
    std::cerr << "Sistema não suportado para reprodução de áudio." << std::endl;
#endif
}
