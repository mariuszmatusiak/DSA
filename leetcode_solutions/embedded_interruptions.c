// czujnik temperatury + mcu
// przerwania wstepnie skonfigurowane
// mozliwe kilka watkow do odczytu temperatury
// float read_temperature_data()//

#define TEMP_ADDRESS 0x20000000
#define MAX_THREADS 128

typedef subFunPtr ... ;
volatile float current_temperature;
volatile size_t idx = 0;
subFunPtr subscribers [MAX_THREADS];
volatile uint8_t publish = false;


void sensor_interrupt() {
  if (!publish) {
  current_temperature = read_temperature_data();
  publish = true;
  }
}
 

void publish_temp() {
  while(1){
  while(!publish) {};
  lock();
  for (size_t i = 0u; i < idx; ++i) {
    subscribers[i](current_temperature);
  }
  unlock();
  publish = false;
  };
}

void sensor_subscribe(subFunPtr fun) {
  sei();
  lock();
  subscribers[idx++] = fun;
  unlock();
  cli();
}

int main (void) {
  
  thread t (publish_temp);
  t.start();
  while(1) {
    
    
  }
  
}