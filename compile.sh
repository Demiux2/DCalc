gcc -o main src/main.c -lleif -lglfw -lm -lGL -lclipboard $(pkg-config --cflags --libs xcb)
