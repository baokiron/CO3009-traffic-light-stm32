/*
 * dht20.h - DHT20 temperature and humidity sensor driver (Owner: C)
 */

#ifndef INC_DHT20_H_
#define INC_DHT20_H_

#include <stdint.h>

void    dht20_init(void);
uint8_t dht20_read(void);   /* returns 1 on success, updates dht20_temperature / dht20_humidity */
void    dht20_task(void);   /* scheduled task, period ~2 s */

#endif /* INC_DHT20_H_ */
