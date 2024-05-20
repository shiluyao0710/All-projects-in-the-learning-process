CC := aarch64-linux-gnu-gcc
SRC := $(shell find src -name '*.c')
OBJ := $(subst src/, obj/, $(SRC:.c=.o))
INC := ./include/ \
		./3rd/usr/include/ \
		./../../wiringOP-master/_INSTALL/usr/local/include/ \
		./3rd/usr/include/python3.10/ \
		./3rd/usr/include/aarch64-linux-gnu/ \
		./3rd/usr/include/aarch64-linux-gnu/python3.10/ 

TARGET = obj/garbage_recognize

CFLAGS := $(foreach item, $(INC), -I$(item))
LIBS_PATH := ./3rd/lib/aarch64-linux-gnu/ \
			./../../wiringOP-master/_INSTALL/usr/local/lib/ \
			./3rd/usr/lib/aarch64-linux-gnu/ \
			./3rd/usr/lib/python3.10/ 

LDFLAGS := $(foreach item, $(LIBS_PATH), -L$(item))

LIBS := -lwiringPi -lpython3.10 -pthread -lexpat -lz -lcrypt

obj/%.o: src/%.c
	mkdir -p obj
	$(CC) -o $@ -c $< $(CFLAGS) $(LDFLAGS) $(LIBS)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS) $(LIBS)

all: $(TARGET)

debug:
	echo $(SRC)
	echo $(OBJ)
	echo $(INC)
	echo $(LIBS_PATH)
	echo $(TARGET)
	echo $(CFLAGS)
	echo $(LDFLAGS)
	echo $(LIBS)

clean:
	rm $(OBJ) obj  -rf

.PHONY: all clean debug