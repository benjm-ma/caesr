obj=caesr
cc=gcc

$(obj):
	$(cc) $@.c -o build/$@

.PHONY: clean build

clean:
	rm -r build
