obj=caesr
cc=gcc

$(obj): build
	$(cc) $@.c -o build/$@

.PHONY: clean build

clean:
	rm -r build

build:
	mkdir build
