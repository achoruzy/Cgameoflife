OUT=".\bin\Cbuoy.exe"

cmake:
	cmake -S . -B ./build -G "Unix Makefiles"

compile: 
	make -C ./build

run:
	$(OUT)
