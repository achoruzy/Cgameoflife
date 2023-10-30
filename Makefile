OUT=".\bin\Cbuoy.exe"
TEST=".\test\bin\Cbuoy_test.exe"

cmake:
	cmake -S . -B ./build -G "Unix Makefiles"

cmake_debug:
	cmake -S . -B ./build -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug ./build

compile: 
	make -C ./build

run:
	$(OUT)

test_compile:
	cd test && cmake -S . -B ./build -G "Unix Makefiles"
	cd test && make -C ./build

test_run:
	$(TEST)

gdb:
	gdb ./bin/Cbuoy.exe