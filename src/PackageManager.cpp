#include "PackageManager.h"


PackageManager::PackageManager () {
    std::cout << "PackageManager" << std::endl;
}

void PackageManager::downloadPackage(std::string packageName) {
   
    /* Just until there actualy is a package mirror/server */ 
    for (int i = 0; i < 10+1; i++) {
        std::cout << "[Downloading Package]: http://websitecompilerpackages.com/"\
            << packageName << ".tar.gz " <<\
            std::to_string(((float)i/10)*100) << "%" << std::endl;
    }
    for (int i = 0; i < 10+1; i++) {
        std::cout << "[Extracting Package]: "\
            << packageName << ".tar.gz " <<\
            std::to_string(((float)i/10)*100) << "%" << std::endl;
    }


    /*CURL *curl;
    FILE *fp;
    CURLcode res;
    std::string url = "http://ianertson.com/";
    curl = curl_easy_init();                                                                                                                                                                                                                                                           
    if (curl)
    {   
        fp = fopen("page.html","wb");
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, NULL);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        fclose(fp);

        std::cout << res << std::endl;
    }*/
}
