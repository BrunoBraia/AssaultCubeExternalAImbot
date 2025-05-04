#include <Windows.h>
#include <TlHelp32.h>
#include <iostream>
#include <string>
#include <cstddef>
#include <cmath>
#include "mem.h"
#include "offsets.hpp"

#define M_PI 3.14159265358979323846

int main()
{
    const DWORD pid = memory::GetProcID(L"ac_client.exe");
    if (pid == 0)
    {
        MessageBox(NULL, L"Failed to get proc ID", L"Tutorial", MB_OK);
        return 1;
    }

    const std::uintptr_t module_base = memory::GetModuleBaseAddress(pid, L"ac_client.exe");
    if (module_base == 0)
    {
        MessageBox(NULL, L"Failed to get module base", L"Tutorial", MB_OK);
        return 1;
    }

    MessageBox(NULL, L"Attachment successful", L"Tutorial", MB_OK);

    bool running = true;

    while (running)
    {
        const auto localplayer = memory::Read<std::uintptr_t>(module_base + offsets::localPlayer);
        if (!localplayer)
        {
            std::cout << "Local Player not found";
        }

        const auto entitylist = memory::Read<std::uintptr_t>(module_base + offsets::entityList);
        if (!entitylist)
        {
            std::cout << "Entity List not found";
        }

        float menorDistancia = FLT_MAX;
        uintptr_t alvoProximo = 0;
        float melhorYaw = 0.0f;
        float melhorPitch = 0.0f;

        const auto count = memory::Read<std::uintptr_t>(module_base + offsets::playerCount);

        for (int i = 1; i < count; i++)
        {    
            const auto target = memory::Read<std::uintptr_t>(entitylist + i * 0x4);
            const auto hp = memory::Read<int>(target + offsets::healthValue);
            const auto localTeam = memory::Read<int>(localplayer + offsets::flagTeam); 
            const auto targetTeam = memory::Read<int>(target + offsets::flagTeam); 

            if (!target)
                continue;

            if (hp <= 0)
                continue;

            if (localTeam == targetTeam)
                continue;

            if (!(GetAsyncKeyState (VK_RBUTTON) & 0x8000))
                continue;

            {
                const auto playerX = memory::Read<float>(localplayer + offsets::positionX);
                const auto playerY = memory::Read<float>(localplayer + offsets::positionY);
                const auto playerZ = memory::Read<float>(localplayer + offsets::positionZ);

                const auto targetX = memory::Read<float>(target + offsets::positionX);
                const auto targetY = memory::Read<float>(target + offsets::positionY);
                const auto targetZ = memory::Read<float>(target + offsets::positionZ);

                const auto absX = targetX - playerX;
                const auto absY = targetY - playerY;
                const auto absZ = targetZ - playerZ;

                float dist = sqrt(absX * absX + absY * absY + absZ * absZ);

                // find close target
                if (dist < menorDistancia)
                {
                    menorDistancia = dist;
                    alvoProximo = target;

                    melhorYaw = atan2(absY, absX) * (180 / M_PI) + 90;
                    melhorPitch = atan2(absZ, sqrt(absX * absX + absY * absY)) * (180 / M_PI);
                }

                const auto angleYaw = atan2(absY, absX) * (180 / M_PI) + 90;
                const auto anglePitch = atan2(absZ, sqrt(absX * absX + absY * absY)) * (180 / M_PI);     
            }   
            Sleep(10);
        }

        if (alvoProximo) 
        {
            memory::Write<float>(localplayer + offsets::playerCameraX, melhorYaw);
            memory::Write<float>(localplayer + offsets::playerCameraY, melhorPitch);
        }
    }

    return 0;
}






