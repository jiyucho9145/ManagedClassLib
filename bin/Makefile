greeting:  ../src/ap/greeting.c libmc.so libbf.so libut.so
	gcc -I../include -std=c99 -o greeting ../src/ap/greeting.c ./libmc.so ./libbf.so ./libut.so

libmc.so: ../src/mc/mc_check.c ../src/mc/mc_manager.c ../src/mc/mc_memory.c
	gcc -I../include -std=c99 -shared -fPIC -o libmc.so ../src/mc/mc_check.c ../src/mc/mc_manager.c ../src/mc/mc_memory.c

libbf.so: ../src/bf/bf_char_buffer.c
	gcc -I../include -std=c99 -shared -fPIC -o libbf.so ../src/bf/bf_char_buffer.c ./libmc.so

libut.so: ../src/ut/ut_str.c
	gcc -I../include -std=c99 -shared -fPIC -o libut.so ../src/ut/ut_str.c ./libmc.so ./libbf.so
