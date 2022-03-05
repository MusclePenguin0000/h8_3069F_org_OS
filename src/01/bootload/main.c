#include "defines.h"
#include "serial.h"
#include "lib.h"

int main(void)
{
    /* シリアル・デバイスを初期化 */
    serial_init(SERIAL_DEFAULT_DEVICE);
    /* 「Hello World!」を出力 */
    puts("Hello World!\n");

    while(1);

    return 0;
}
