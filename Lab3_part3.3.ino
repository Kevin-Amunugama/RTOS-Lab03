// Blinking LED with different rates
#if CONFIG_FREERTOS_UNICORE
static const BaseType_t app_cpu = 0;
#else
static const BaseType_t app_cpu = 1;
#endif

const int ledPin1 = 5;
const int ledPin2 = 6;
static const int rate_1 = 500;  // LED blink rate is defined here in mS
static const int rate_2 = 300;  // LED blink rate is defined here in mS


// A method (task) to blink led with a rate we define. 
void toggleLED_1(void *parameter) {
  while(1) {
    digitalWrite(ledPin1, HIGH);
    vTaskDelay(rate_1 / portTICK_PERIOD_MS);
    digitalWrite(ledPin1, LOW);
    vTaskDelay(rate_1 / portTICK_PERIOD_MS);
  }
}

// A method (task) to blink the led with another rate we define. 
void toggleLED_2(void *parameter) {
  while(1) {
    digitalWrite(ledPin2, HIGH);
    vTaskDelay(rate_2 / portTICK_PERIOD_MS);
    digitalWrite(ledPin2, LOW);
    vTaskDelay(rate_2 / portTICK_PERIOD_MS);
  }
}

void setup() {


  pinMode(led_pin, OUTPUT);// setting the inbuilt LED as output.

  // ToggleLED_1 is set to run forever using xTaskCreatePinnedToCore
  xTaskCreatePinnedToCore(  
              toggleLED_1,  
              "Toggle 1",   
              1024,         
              NULL,         
              1,            
              NULL,        
              app_cpu);    

  // ToggleLED_2 is set to run forever using xTaskCreatePinnedToCore
  xTaskCreatePinnedToCore(  
              toggleLED_2,  
              "Toggle 2",   
              1024,         
              NULL,         
              1,            
              NULL,         
              app_cpu);    

 }

void loop() {
}
