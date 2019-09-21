// code-licenser auto-generated license header

// Copyright (C) 2019 Jose Luzón Martín
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
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include "codelicenser.hpp"

#include <iostream>
#include <regex>
#include <fstream>

using namespace jluzonm::codelicenser;

CodeLicenser::CodeLicenser()
{
}

CodeLicenser::~CodeLicenser()
{
}

bool CodeLicenser::license(const std::string &pathStr, const std::string &licPathStr, const std::string &comment, const std::string &fileExtension) noexcept
{
    m_currentComment = comment;
    m_currentFileExtension = fileExtension;

    std::filesystem::path thePath(pathStr);
    std::filesystem::path licPath(licPathStr);

    std::cout << "Code Licenser started at : " << thePath << std::endl;
    std::cout << "File extensions : " << m_currentFileExtension << std::endl;

    if ( !std::filesystem::exists(thePath) )
    {
        std::cout << "Path not found : " << thePath << std::endl;
        return false;
    }

    std::cout << "License file : " << licPath << std::endl;

    if ( !std::filesystem::exists(licPath) )
    {
        std::cout << "License file not found : " << licPath << std::endl;
        return false;
    }
    else if ( !loadLicense(licPath) )
    {
        return false;
    }

    bool licenserDone = false;

    if ( std::filesystem::is_directory(thePath) )
    {
        licenserDone = licenseDir(thePath);
    }
    else if ( std::filesystem::is_regular_file(thePath) )
    {
        licenserDone = licenseFile(thePath);
    }
    else
    {
        std::cout << "Path is not a directory nor a regular file: " << thePath << std::endl;
    }
    
    std::cout << "Code Licenser finished!" << std::endl;

    return licenserDone;
}

bool CodeLicenser::loadLicense(const std::filesystem::path& licPath)
{
    bool loaded = false;

    std::ifstream ifstream;
    ifstream.open( licPath, std::ios_base::in | std::ios_base::binary );

    if ( ifstream.is_open() )
    {
        std::stringstream str;
        std::string line;
        while (std::getline(ifstream, line))
        {
            str << line << std::endl;
        }
        ifstream.close();

        m_currentLicenseTxt = str.str();

        loaded = true;
    }
    else
    {
        std::cout << "Error opening license file!" << std::endl;
    }
    

    return loaded;
}

bool CodeLicenser::licenseDir(const std::filesystem::path& dirPath)
{
    for (const auto & entry : std::filesystem::recursive_directory_iterator(dirPath))
    {
        if (entry.is_regular_file())
        {
            licenseFile(entry.path());
        }
    }

    return true;
}

bool CodeLicenser::licenseFile(const std::filesystem::path& filePath)
{
    bool fileLicensed = false;

    // TODO: make file extensions parameterizable
    std::regex fileFiler(".+\\.(" + m_currentFileExtension + ")");

    std::cout << "Licensing file : " << filePath << "... ";

    if ( std::regex_match(filePath.filename().string(), fileFiler) )
    {
        std::ifstream ifstream;
        ifstream.open( filePath, std::ios_base::in | std::ios_base::binary );

        if ( ifstream.is_open() )
        {
            std::stringstream str;
            std::string line;

            // First line contains the 'key' to check already licensed file.
            if ( std::getline(ifstream, line) && line.find("code-licenser auto-generated license header") == std::string::npos )
            {
                str << line << std::endl;
                
                // continue reading...
                while (std::getline(ifstream, line))
                {
                    str << line << std::endl;
                }
                ifstream.close();

                std::ofstream ofstream;
                ofstream.open( filePath, std::ios_base::out | std::ios_base::binary | std::ios_base::trunc );

                if ( ofstream.is_open() )
                {
                    // The first line is used to check files already licensed with code-licenser.
                    ofstream    << m_currentComment << " code-licenser auto-generated license header" << std::endl
                                << std::endl
                                << m_currentLicenseTxt
                                << std::endl
                                << str.str();

                    fileLicensed = true;

                    std::cout << "done!" << std::endl;    
                }
                else
                {
                    std::cout << "error opening!" << std::endl;    
                } 
            }
            else
            {
                std::cout << "already licensed!" << std::endl;
                ifstream.close();
            }            
        }
        else
        {
            std::cout << "error opening!" << std::endl;    
        }        
    }
    else
    {
        std::cout << "skipped!" << std::endl;
    }

    return fileLicensed;
}
