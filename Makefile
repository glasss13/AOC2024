.PHONY: init clean build

build: init
	cd build && cmake --build .

init:
	@mkdir -p build
	cd build && cmake ..

clean:
	@rm -rf build

