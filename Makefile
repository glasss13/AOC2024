.PHONY: init clean build input

# bring in the SESSION cookie for getting the input
include .env

build: init
	cd build && cmake --build .

init:
	@mkdir -p build
	cd build && cmake ..

clean:
	@rm -rf build

input:
	mkdir -p inputs
	curl -X GET "https://adventofcode.com/2024/day/$(DAY)/input" -b "session=$(SESSION)" > inputs/day$(DAY).txt
