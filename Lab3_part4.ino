#if CONFIG_FREERTOS_UNICORE
  static const BaseType_t app_cpu = 0;
#else
  static const BaseType_t app_cpu = 1;
#endif

// Some string to print
const char msg[] = "Hello World.";

// Task handles
static TaskHandle_t task_1 = NULL;
static TaskHandle_t task_2 = NULL;

//*****************************************************************************
// Tasks

// Task: print to Serial Terminal with lower priority
void startTask1(void *parameter) {

  // Count number of characters in string
  int msg_len = strlen(msg);

  // Print string to Terminal
  while (1) {
    Serial.println();
    for (int i = 0; i < msg_len; i++) {
      Serial.print(msg[i]);
    }
    Serial.println();
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

// Task: print to Serial Terminal with higher priority
void startTask2(void *parameter) {
  while (1) {
    Serial.print('*');
    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}

void setup() {

  Serial.begin(9600);
 // Task to run forever
  xTaskCreatePinnedToCore(startTask1, // Function to be called
                          "Task 1",  // Name of task
                          1024,// Stack size
                          NULL, // Parameter to pass
                          1, // Task priority
                          &task_1, // Task handle
                          app_cpu); // Run on one core

  // Task to run once with higher priority
  xTaskCreatePinnedToCore(startTask2, // Function to be called
                          "Task 2", // Name of task
                          1024, // Stack size
                          NULL, // Parameter to pass
                          2, // Task priority
                          &task_2, // Task handle
                          app_cpu); // Run on one core
}

void loop() {
  if (task_1 != NULL) {
    vTaskDelete(task_1);
    task_1 = NULL;
  }
}
