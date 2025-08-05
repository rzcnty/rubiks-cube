##
# Project Title
#
# @file
# @version 0.1

# Derleyici
CC = gcc

# Derleyici Ayarları
CFLAGS = -g -Wall

# Matematik kütüphanesini linklemek için
LIBS = -lm

# Kaynak dosyalar (.c)
# Standart_Search.c'yi BURAYA EKLE!
SRCS = GRAPH_SEARCH.c SpecificToProblem.c HashTable.c Standart_Search.c

# Kaynak dosyalardan türetilecek object dosyaları (.o)
OBJS = $(SRCS:.c=.o)

# Oluşturulacak programın adı
TARGET = rubik_solver

all: $(TARGET)

# Programı oluşturma kuralı
# LIBS değişkenini buraya ekle!
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

# end
