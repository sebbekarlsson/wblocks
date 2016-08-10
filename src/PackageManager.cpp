#include "PackageManager.h"


PackageManager::PackageManager () {
    std::cout << "PackageManager" << std::endl;
}

void PackageManager::downloadPackage() {
    auto r = cpr::Get(cpr::Url{"http://www.httpbin.org/get"});
}
