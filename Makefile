OUT=".\bin\Cbuoy.exe"

cmake:
	cmake -S . -B ./build -G "Unix Makefiles"

make: 
	make -C ./build

run:
	$(OUT)
