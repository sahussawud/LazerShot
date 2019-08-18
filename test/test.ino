#include <string.h>
int val[3];
void setup() {
  Serial.begin(9600);
  pinMode(D0, OUTPUT);
}

void split(char txt[10]){
  int i=0;
  char arr[3][5];
  char *token = strtok(txt, ",");
  while(token != NULL){
    strcpy(arr[i], token);
    val[i] = atoi(arr[i]);
    token = strtok(NULL, ",");
    //Serial.println(val[i]);
    i += 1;
  }
  i = 0;
}

void loop() {
  // put your main code here, to run repeatedly:
  char txt[] = "02,3,1500";
  split(txt);
  for(int i = 0; i<3; i++){
    
    Serial.println(val[i]);
    delay(1000);
  }
}
