all:
	cmake --build build -j12
	build/src/app/OpenBirch2

clean:
	rm -rf build
	mkdir build
	cmake -S . -B build