all: git-update
	cmake --build build -j12
	build/src/app/OpenBirch2

clean:
	rm -rf build
	mkdir build
	cmake -S . -B build

documentation: git-update
	doxygen Doxyfile
	
git-update:
	git submodule sync
	git submodule update --init --recursive

bear: git-update clean 
	bear -- make
