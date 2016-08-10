FLAGZ=-lcurl


output:\
    	ResourceManager.o\
    	Website.o\
	PackageManager.o\
	main.o
	    g++\
		$(FLAGZ)\
		ResourceManager.o\
		Website.o\
		PackageManager.o\
		main.o\
		-o websitecompiler

main.o: src/main.cpp
	g++ -c src/main.cpp

Website.o: src/Website.cpp src/Website.h
	g++ -c src/Website.cpp

PackageManager.o: src/PackageManager.cpp src/PackageManager.h
	g++ $(FLAGZ) -c src/PackageManager.cpp

ResourceManager.o: src/ResourceManager/ResourceManager.cpp src/ResourceManager/ResourceManager.h
	g++ -c src/ResourceManager/ResourceManager.cpp

clean:
	rm *.o
