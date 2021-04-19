
#ifndef BME280_H_
#define BME280_H_

int bme280Init(int iAddr);
int bme280ReadValues(int *T, int *P, int *H);
void getTemperature (float *temp, float *hum);

#endif // __BME280__