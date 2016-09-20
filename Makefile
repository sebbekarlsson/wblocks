FLAGZ="-std=c++11"


output:\
    	ResourceManager.o\
    	Website.o\
	main.o
	    g++\
		$(FLAGZ)\
		ResourceManager.o\
		Website.o\
		main.o\
		-o websitecompiler

main.o: src/main.cpp
	g++ -std=c++11 -c src/main.cpp

Website.o: src/Website.cpp src/Website.h
	g++ -std=c++11 -c src/Website.cpp

ResourceManager.o: src/ResourceManager/ResourceManager.cpp src/ResourceManager/ResourceManager.h
	g++ -std=c++11 -c src/ResourceManager/ResourceManager.cpp

clean:
	rm *.o
