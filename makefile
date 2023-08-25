all: git-update
	cmake --build build -j12
	build/src/app/OpenBirch2

gdb: build
	gdb -ex run build/src/app/OpenBirch2 -q

build:
	cmake --build build -j12

clean:
	rm -rf build
	mkdir build
	cmake -G Ninja -S . -B build

documentation: git-update
	doxygen Doxyfile
	
git-update:
	git submodule sync
	git submodule update --init --recursive

bear: git-update clean 
	bear -- make
