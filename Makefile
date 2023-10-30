OUT=".\bin\Cbuoy.exe"

cmake:
	cmake -S . -B ./build -G "Unix Makefiles"

cmake_debug:
	cmake -S . -B ./build -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug ./build

compile: 
	make -C ./build

run:
	$(OUT)

test_cmake:
	cd test && cmake -S . -B ./build
	cd test && make -C ./build
	cd test/buid && ctest

gdb:
	gdb ./bin/Cbuoy.exe