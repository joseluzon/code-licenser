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

#include <iostream>
#include "codelicenser.hpp"

int main(int argc, char* argv[])
{    
    std::cout << "code-licenser Copyright (C) 2019 Jose Luzón Martin" << std::endl
              << "This program comes with ABSOLUTELY NO WARRANTY." << std::endl
              << "This is free software, and you are welcome to redistribute it" << std::endl
              << "under the terms of the GNU Lesser General Public License" << std::endl
              << "as published by the Free Software Foundation," << std:: endl
              << "either version 3, or (at your option) any later version." << std::endl << std::endl;

    if (argc < 4)
    {
        std::cout << "Usage : code-licenser <path-to-license> <path-to-license-file> <source-code-comment-string>" <<  std::endl;
    }
    else
    {
        std::string path(argv[1]);
        std::string licPath(argv[2]);
        std::string commentStr(argv[3]);

        jluzonm::codelicenser::CodeLicenser cl;    
        cl.license(path, licPath, commentStr);
    }
    
    return EXIT_SUCCESS;
}
