#include "driver/temp_sensor.h"; //SENSOR SUHU CORE
int TIME_TO_SLEEP = 10; //klo kepanasan tidur berapa detik
int uS_TO_S_FACTOR = 1000000; //sleepnya dalam microsecond jadi harus x 1juta

void initCoreSensor(){//SENSOR CORE TEMP
    temp_sensor_config_t temp_sensor = TSENS_CONFIG_DEFAULT();
    temp_sensor.dac_offset = TSENS_DAC_L1;  // TSENS_DAC_L2 is default; L4(-40°C ~ 20°C), L2(-10°C ~ 80°C), L1(20°C ~ 100°C), L0(50°C ~ 125°C)
    temp_sensor_set_config(temp_sensor);
    temp_sensor_start();
}

void setup() {
  Serial.begin(115200);//memulai serial
  initCoreSensor();//setup temp core

}

void loop() {
  Serial.print("Suhu core: ");
  float coretemp = 0;
  temp_sensor_read_celsius(&coretemp);
  Serial.println(coretemp);
  if (coretemp>70){//sesuaikan limit sesuka kalian
    Serial.println("CORE TERLALU PANAS, MATIKAN SELAMA 10 detik");
    esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
    esp_deep_sleep_start();
  }
  delay(10000);
}
