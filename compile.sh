gcc -o main src/main.c src/eval.h -lleif -lglfw -lm -lGL -lclipboard $(pkg-config --cflags --libs xcb)
