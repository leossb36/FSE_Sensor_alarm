
#ifndef BME280_H_
#define BME280_H_

int bme280Init(int iAddr);
int bme280ReadValues(int *T, int *P, int *H);

#endif // __BME280__