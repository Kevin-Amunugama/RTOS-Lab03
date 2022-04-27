//Blinking an LED with a 500mS delay

//floowing code is to use just one core from the CPU for the process of blinking the LED
#if CONFIG_FREERTOS_UNICORE
static const BaseType_t app_cpu = 0;
#else
static const BaseType_t app_cpu = 1;
#endif


static const int rate_1 = 500;  // LED blink rate is defined here in mS
static const int led_pin = LED_BUILTIN;  //in built led pin

// A method (task) to blink just one led with a rate we define. 
void toggleLED_1(void *parameter) {
  while(1) {
    digitalWrite(led_pin, HIGH);
    vTaskDelay(rate_1 / portTICK_PERIOD_MS);  // non blocking and works in vanilla free RTOS can be used over delay function
    digitalWrite(led_pin, LOW);
    vTaskDelay(rate_1 / portTICK_PERIOD_MS);
  }
}


void setup() {

  // Configure pin
  pinMode(led_pin, OUTPUT);  // setting the LED to output

  // Task to run forever
  xTaskCreatePinnedToCore(  
              toggleLED_1,  
              "Toggle 1",  
              1024,        
              NULL,         
              1,            
              NULL,         
              app_cpu);     

}

void loop() {

}
