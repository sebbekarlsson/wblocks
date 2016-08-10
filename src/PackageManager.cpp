#include "PackageManager.h"


PackageManager::PackageManager () {
    std::cout << "PackageManager" << std::endl;
}

void PackageManager::downloadPackage() {
    CURL *curl;
    FILE *fp;
    CURLcode res;
    std::string url = "http://stackoverflow.com";
    char outfilename[FILENAME_MAX] = "page.html";
    curl = curl_easy_init();                                                                                                                                                                                                                                                           
    if (curl)
    {   
        fp = fopen(outfilename,"wb");
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, NULL);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        fclose(fp);

        std::cout << res << std::endl;
    } else { std::cout << "A curl error" << std::endl; }
}
