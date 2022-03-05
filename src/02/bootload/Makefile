PREFIX	= /usr/local
ARCH	= h8300-elf
BINDIR	= $(PREFIX)/bin
ADDNAME	= $(ARCH)-

AR 		= $(BINDIR)/$(ADDNAME)ar
AS		= $(BINDIR)/$(ADDNAME)as
CC		= $(BINDIR)/$(ADDNAME)gcc
LD		= $(BINDIR)/$(ADDNAME)ld
NM		= $(BINDIR)/$(ADDNAME)nm
OBJCOPY = $(BINDIR)/$(ADDNAME)objcopy
OBJDUMP = $(BINDIR)/$(ADDNAME)objdump
RANLIB	= $(BINDIR)/$(ADDNAME)ranlib
STRIP	= $(BINDIR)/$(ADDNAME)strip

# フラッシュROM書き込みツール
H8WRITE = ../../tools/h8write/h8write.exe

# FreeBSD-4.x:/dev/cuaaX, FreeBSD-6.x:/dev/cuadX, FreeBSD(USB):/dev/cuaUx
# Linux:/dev/ttySx, Linux(USB):/dev/ttyUSBx, Windows:comX
# シリアル接続先
H8WRITE_SERDEV = com0

# ソースコード群
OBJS  = vector.o startup.o main.o
OBJS += lib.o serial.o

# 生成する実行形式のファイル名
TARGET = kzload

# コンパイルオプション
CFLAGS = -Wall -mh -nostdinc -nostdlib -fno-builtin
#CFLAGS += -mint32 # intを32ビットにすると掛算／割算ができなくなる
CFLAGS += -I.
#CFLAGS += -g
CFLAGS += -Os
CFLAGS += -DKZLOAD

# リンク・オプション
LFLAGS = -static -T ld.scr -L.

.SUFFIXES: .c .o
.SUFFIXES: .s .o

all :		$(TARGET)

# 実行形式の生成ルール
$(TARGET) :	$(OBJS)
		$(CC) $(OBJS) -o $(TARGET) $(CFLAGS) $(LFLAGS)
		cp $(TARGET) $(TARGET).elf
		$(STRIP) $(TARGET)

# .cファイルのコンパイルルール
.c.o :		$<
		$(CC) -c $(CFLAGS) $<

# アセンブラ・ファイルのアセンブル・ルール
.s.o :		$<
		$(CC) -c $(CFLAGS) $<

# モトローラSレコード・フォーマットへの変換ルール
$(TARGET).mot :	$(TARGET)
		$(OBJCOPY) -O srec $(TARGET) $(TARGET).mot

image :		$(TARGET).mot

# フラッシュROMへの転送
write :		$(TARGET).mot
		$(H8WRITE) -3069 -f20 $(TARGET).mot $(H8WRITE_SERDEV)

# フォルダの削除
clean :
		rm -f $(OBJS) $(TARGET) $(TARGET).elf $(TARGET).mot

