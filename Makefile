OUT=".\bin\Cbuoy.exe"

cmake:
	cmake -S . -B ./build -G "Unix Makefiles"

compile: 
	make -C ./build

run:
	$(OUT)

test_cmake:
	cd test && cmake -S . -B ./build
	cd test && make -C ./build
	cd test/buid && ctest
