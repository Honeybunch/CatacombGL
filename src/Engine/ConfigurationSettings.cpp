// Copyright (C) 2018 Arno Ansems
// 
// This program is free software: you can redistribute it and/or modify 
// it under the terms of the GNU General Public License as published by 
// the Free Software Foundation, either version 3 of the License, or 
// (at your option) any later version. 
// 
// This program is distributed in the hope that it will be useful, 
// but WITHOUT ANY WARRANTY; without even the implied warranty of 
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
// GNU General Public License for more details. 
// 
// You should have received a copy of the GNU General Public License 
// along with this program.  If not, see http://www.gnu.org/licenses/ 

#include "ConfigurationSettings.h"
#include <fstream>
#include <iostream>
#include <string>
#include "..\..\ThirdParty\SDL\include\SDL_keyboard.h"

ConfigurationSettings::ConfigurationSettings() :
    m_aspectRatio(0),
    m_fov(25),
    m_textureFilter(IRenderer::Linear),
    m_depthShading(true),
    m_showFps(false),
    m_vsync(true),
    m_soundMode(1),
    m_mouseSensitivity(10),
    m_mouseLook(true)
{

}

void ConfigurationSettings::LoadFromFile(const std::string& configurationFile)
{
    std::ifstream file;
    file.open(configurationFile);
    if (file.is_open())
    {
        std::map<std::string, std::string> keyValuePairs;
        std::string line;
        while (std::getline(file, line) && file.eofbit)
        {
            size_t pos = line.find('=');
            if (pos != std::string::npos)
            {
                std:: string key = line.substr(0, pos);
                std::string value = line.substr(pos + 1);
                keyValuePairs.insert(std::make_pair(key, value));
            }
        }

        auto depthShadingPair = keyValuePairs.find("depthshading");
        if (depthShadingPair != keyValuePairs.end())
        {
            m_depthShading = (depthShadingPair->second.compare("true") == 0);
        }
        
        auto showfpsPair = keyValuePairs.find("showfps");
        if (showfpsPair != keyValuePairs.end())
        {
            m_showFps = (showfpsPair->second.compare("true") == 0);
        }

        auto vsyncPair = keyValuePairs.find("vsync");
        if (vsyncPair != keyValuePairs.end())
        {
            m_vsync = (vsyncPair->second.compare("true") == 0);
        }

        auto aspectRatioPair = keyValuePairs.find("aspectratio");
        if (aspectRatioPair != keyValuePairs.end())
        {
            m_aspectRatio = (aspectRatioPair->second.compare("Classic") == 0) ? 0 : 1;
        }

        auto textureFilterPair = keyValuePairs.find("texturefilter");
        if (textureFilterPair != keyValuePairs.end())
        {
            m_textureFilter = (textureFilterPair->second.compare("Linear") == 0) ? IRenderer::Linear : IRenderer::Nearest;
        }

        auto fovPair = keyValuePairs.find("fov");
        if (fovPair != keyValuePairs.end())
        {
            int32_t fov = std::stoi(fovPair->second);
            m_fov = (fov < 25) ? 25 : (fov > 45) ? 45 : fov;
        }

        auto soundModePair = keyValuePairs.find("soundmode");
        if (soundModePair != keyValuePairs.end())
        {
            m_soundMode = (soundModePair->second.compare("Off") == 0) ? 0 : 1;
        }

        auto mouseLookPair = keyValuePairs.find("mlook");
        if (mouseLookPair != keyValuePairs.end())
        {
            m_mouseLook = (mouseLookPair->second.compare("Enabled") == 0);
        }

        auto mouseSensitivityPair = keyValuePairs.find("mouseSensitivity");
        if (mouseSensitivityPair != keyValuePairs.end())
        {
            int32_t sensitivity = std::stoi(mouseSensitivityPair->second);
            m_mouseSensitivity = (sensitivity < 5) ? 5 : (sensitivity > 15) ? 15: sensitivity;
        }

        const std::vector<SDL_Keycode>& allowedKeys = ControlsMap::GetAllowedKeys();
        for (const auto key: allowedKeys)
        {
            const std::string keyName = SDL_GetKeyName(key);
            const auto keyPair = keyValuePairs.find(keyName);
            if (keyPair != keyValuePairs.end())
            {
                const ControlAction action = ControlsMap::StringToAction(keyPair->second);
                m_controlsMap.AssignActionToKey(action, key);
            }
        }
        for (uint8_t i = 1; i < 4; i++)
        {
            const std::string buttonName = ControlsMap::GetMouseButtonName(i);
            const auto buttonPair = keyValuePairs.find(buttonName);
            if (buttonPair != keyValuePairs.end())
            {
                const ControlAction action = ControlsMap::StringToAction(buttonPair->second);
                m_controlsMap.AssignActionToMouseButton(action, i);
            }
        }

        file.close();
    }
}

void ConfigurationSettings::StoreToFile(const std::string& configurationFile) const
{
    std::ofstream file;
    file.open(configurationFile);
    if (file.is_open())
    {
        file << "# This file was generated by CatacombGL\n";
        file << "# Video settings\n";
        const std::string aspectRatioValue = (m_aspectRatio == 0) ? "Classic" : "FitToScreen";
        file << "aspectratio=" << aspectRatioValue << "\n";
        const std::string depthShadingValue = m_depthShading ? "true" : "false";
        file << "depthshading=" << depthShadingValue << "\n";
        const std::string showfpsValue = m_showFps ? "true" : "false";
        file << "showfps=" << showfpsValue << "\n";
        const std::string vsyncValue = m_vsync ? "true" : "false";
        file << "vsync=" << vsyncValue << "\n";
        const std::string textureFilterValue = (m_textureFilter == IRenderer::TextureFilterSetting::Nearest) ? "Nearest" : "Linear";
        file << "texturefilter=" << textureFilterValue << "\n";
        std::string fovValue = std::to_string(m_fov);
        file << "fov=" << fovValue << "\n";
        file << "# Sound settings\n";
        const std::string modeValue = (m_soundMode == 0) ? "Off" : "Adlib";
        file << "soundmode=" << modeValue << "\n";
        file << "# Controls settings\n";
        const std::string mlookValue = (m_mouseLook) ? "Enabled" : "Disabled";
        file << "mlook=" << mlookValue << "\n"; 
        std::string mouseSensitivityValue = std::to_string(m_mouseSensitivity);
        file << "mouseSensitivity=" << mouseSensitivityValue << "\n";
        file << "# Key bindings\n";
        for (uint8_t i = (uint8_t)MoveForward; i < (uint8_t)MaxControlAction; i++)
	    {
            const std::vector<SDL_Keycode> keysForAction = m_controlsMap.GetKeysFromAction(ControlAction(i));
            const std::string& actionLabel = m_controlsMap.GetActionLabels().at((ControlAction)i);
            for (uint8_t j = 0; j < keysForAction.size(); j++)
            {
                const std::string keyLabel = SDL_GetKeyName(keysForAction.at(j));
                file << keyLabel << "=" << actionLabel << "\n";
            }
            const std::vector<uint8_t>buttonsForAction = m_controlsMap.GetMouseButtonsFromAction(ControlAction(i));
            for (uint8_t j = 0; j < buttonsForAction.size(); j++)
            {
                const std::string buttonLabel = ControlsMap::GetMouseButtonName(buttonsForAction.at(j));
                file << buttonLabel << "=" << actionLabel << "\n";
            }
        }
            
        file.close();
    }
}

uint8_t ConfigurationSettings::GetAspectRatio() const
{
    return m_aspectRatio;
}

void ConfigurationSettings::SetAspectRatio(const uint8_t ratio)
{
    m_aspectRatio = ratio;
}

uint8_t ConfigurationSettings::GetFov() const
{
    return m_fov;
}

void ConfigurationSettings::SetFov(const uint8_t fov)
{
    m_fov = fov;
}

IRenderer::TextureFilterSetting ConfigurationSettings::GetTextureFilter() const
{
    return m_textureFilter;
}

void ConfigurationSettings::SetTextureFilter(const IRenderer::TextureFilterSetting filter)
{
    m_textureFilter = filter;
}

bool ConfigurationSettings::GetDepthShading() const
{
    return m_depthShading;
}

void ConfigurationSettings::SetDepthShading(const bool enabled)
{
    m_depthShading = enabled;
}

bool ConfigurationSettings::GetShowFps() const
{
    return m_showFps;
}

void ConfigurationSettings::SetShowFps(const bool enabled)
{
    m_showFps = enabled;
}

bool ConfigurationSettings::GetVSync() const
{
    return m_vsync;
}

void ConfigurationSettings::SetVSync(const bool enabled)
{
    m_vsync = enabled;
}

ControlsMap& ConfigurationSettings::GetControlsMap()
{
    return m_controlsMap;
}

const ControlsMap& ConfigurationSettings::GetConstControlsMap() const
{
    return m_controlsMap;
}

uint8_t ConfigurationSettings::GetSoundMode() const
{
    return m_soundMode;
}

void ConfigurationSettings::SetSoundMode(const uint8_t mode)
{
    m_soundMode = mode;
}

uint8_t ConfigurationSettings::GetMouseSensitivity() const
{
    return m_mouseSensitivity;
}

void ConfigurationSettings::SetMouseSensitivity(const uint8_t sensitivity)
{
    m_mouseSensitivity = sensitivity;
}

bool ConfigurationSettings::GetMouseLook() const
{
    return m_mouseLook;
}

void ConfigurationSettings::SetMouseLook(const bool enabled)
{
    m_mouseLook = enabled;
}
