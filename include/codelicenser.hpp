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

#pragma once

#include <filesystem>
#include <string>

namespace jluzonm {
namespace codelicenser {

class CodeLicenser
{
public:
    CodeLicenser();
    ~CodeLicenser();

    bool license(const std::string &path, const std::string &licPath, const std::string& comment) noexcept;

private:
    // hidden:
    CodeLicenser(const CodeLicenser &other);
    CodeLicenser &operator=(const CodeLicenser &other);
    //

    std::string m_currentLicenseTxt;
    std::string m_currentComment;

    bool loadLicense(const std::filesystem::path &licPath);

    bool licenseDir(const std::filesystem::path &dirPath);

    bool licenseFile(const std::filesystem::path &filePath);
};

} // namespace codelicenser
} // namespace jluzonm
