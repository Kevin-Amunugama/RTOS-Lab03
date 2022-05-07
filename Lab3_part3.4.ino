#include <stdlib.h>
#if CONFIG_FREERTOS_UNICORE
  static const BaseType_t app_cpu = 0;
#else
  static const BaseType_t app_cpu = 1;
#endif

static const int buf_len = 20;
static const int led_pin = LED_BUILTIN;
static int LEDdelay = 500;  // this is the initial delay later will be replaced

void toggleLED(void *parameter) {
  while (1) {
    digitalWrite(led_pin, HIGH);
    vTaskDelay(LEDdelay / portTICK_PERIOD_MS);
    digitalWrite(led_pin, LOW);
    vTaskDelay(LEDdelay / portTICK_PERIOD_MS);
  }
}

void SerialRead(void *parameters) {

  char c;
  char buf[buf_len];
  int idx = 0;

  memset(buf, 0, buf_len);

  while (1) {

    if (Serial.available() > 0) {
      c = Serial.read();

      if (c == '\n') {
        LEDdelay = atoi(buf);
        Serial.print("Updated LED delay to: ");
        Serial.println(LEDdelay);
        memset(buf, 0, buf_len);
        idx = 0;
      } else {
          buf[idx] = c;
          idx++;
        
      }
    }
  }
}


void setup() {
  pinMode(led_pin, OUTPUT);

  Serial.begin(115200);
  vTaskDelay(1000 / portTICK_PERIOD_MS);
  Serial.println("Enter the delay in mS : ");


  xTaskCreatePinnedToCore(  
            toggleLED,      
            "Toggle LED",  
            1024,          
            NULL,         
            1,             
            NULL,           
            app_cpu);       
            

  xTaskCreatePinnedToCore( 
            SerialRead,     
            "Read Serial",  
            1024,           
            NULL,           
            1,             
            NULL,         
            app_cpu);      


  vTaskDelete(NULL);
}

void loop() {

}
