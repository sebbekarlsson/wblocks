#ifndef PACKAGEMANAGER_H
#define PACKAGEMANAGER_H
#include <cpr.h>
#include <curl/curl.h>
#include <string>
#include <iostream>


class PackageManager {
    public:
        PackageManager();
        void downloadPackage();
};

#endif
