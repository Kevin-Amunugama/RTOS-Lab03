//defining the cores for dual core operation
static const BaseType_t pro_cpu = 0;
static const BaseType_t app_cpu = 1;



// this is the Task A which is supposed to run on core 0
void TaskA(void *parameters) {
  char str[50];
  while (1) {
    sprintf(str, "Task A Running on Core : %i\r\n", xPortGetCoreID());
    Serial.print(str);

  }
}

//this is the task B which is supposed to run of core 1
void TaskB(void *parameters) {


  char str[50];
  while (1) {
    sprintf(str, "Task B Running on Core : %i\r\n", xPortGetCoreID());
    Serial.print(str);

  }
}

void setup() {

  Serial.begin(9600);

  xTaskCreatePinnedToCore(TaskA,
                          "Task A",
                          3000,
                          NULL,
                          1,
                          NULL,
                          app_cpu);


  xTaskCreatePinnedToCore(TaskB,
                          "Task B",
                          3000,
                          NULL,
                          2,
                          NULL,
                          pro_cpu);


  // Delete "setup and loop" task
  vTaskDelete(NULL);
}

void loop() {

}
