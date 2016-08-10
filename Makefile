output:\
    	ResourceManager.o\
    	Website.o\
	main.o
	    g++\
		ResourceManager.o\
		Website.o\
		main.o\
		-o websitecompiler

main.o: src/main.cpp
	g++ -c src/main.cpp

Website.o: src/Website.cpp src/Website.h
	g++ -c src/Website.cpp

ResourceManager.o: src/ResourceManager/ResourceManager.cpp src/ResourceManager/ResourceManager.h
	g++ -c src/ResourceManager/ResourceManager.cpp

clean:
	rm *.o
