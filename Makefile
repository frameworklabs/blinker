run: build_app
	build/blinker

test: build_test
	build/blinker_lever_test
	
clean:
	rm -rf build
	
build_app: src/app/shell/main.c src/env/blinker_env.c gen_app
	cc -I src -I dep -I build src/app/shell/main.c src/env/blinker_env.c build/blech/app/control/blinker.c -lcurses -o build/blinker
	
build_test: src/test/shell/main_test.c src/env/blinker_env.c gen_test
	cc -I src -I dep -I build src/test/shell/main_test.c src/env/blinker_env.c build/blech/test/control/blinker_lever_test.c -lcurses -o build/blinker_lever_test
	
gen_app: src/app/control/blinker.blc build_dir
	blechc -od build -sp src src/app/control/blinker.blc

gen_test: src/test/control/blinker_lever_test.blc build_dir
	blechc -od build -sp src src/test/control/blinker_lever_test.blc

build_dir:
	[ -d build ] || mkdir build
