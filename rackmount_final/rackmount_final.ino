int output_line = 2;
int keypad_latch = 3;
int colons = 4;
int clock_line = 5;
int reset_line = 6;
int data_bus_1 = 8;
int data_bus_2 = 7;
int data_bus_3 = 10;
int data_bus_4 = 9;

//boolean all[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
boolean buttons[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; //{0,1,2,3,4,5,6,7,8,9,a,b,c,d,e} a=set, b=clr, c=gen, d=rd'r, e=usr.b
boolean dip[] = {0,0,0,0,0,0,0,0}; //{0,1,2,3,4,5,6,7} 
/*
dip0, 0=ntsc, 1=pal
dip1, 0=col'r, 1=non c
dip2, 0=fram, 1=blnk
dip3, 0=vcg, 1=size
dip4, 0=off, 1=d.f.
dip5, 0=norm, 1=fld 2
dip6, 0=norm, 1=opt 1
dip7, 0=norm, 1=opt 2
*/

int d = 20;
int i = 0;
int displays[] = {0,1,2,3,4,5,6,7,'l','l'}; // corrected order, use as "seven_seg(displays[order[i]]);"
int order[] = {6,5,4,3,2,1,0,9,8,7}; // {7seg6,7seg5,7seg4,7seg3,7seg2,7seg1,7seg0,LEDs2-3,LEDs0-1,7seg7}
/*
for displays[8, 9]

set 0 for both LEDs on
set 2 for LED 0, or 2
set 1 for LED 1, or 3
set invalid (like 'a') for both LEDs off
  
0=gen
1=rd'r
2=lck
3=d.f.
  
*/


void setup() { 
 //Initialize serial and wait for port to open:
  Serial.begin(115200); 
  pinMode(output_line, OUTPUT);
  pinMode(keypad_latch, OUTPUT);
  pinMode(colons, OUTPUT);
  pinMode(clock_line, OUTPUT);
  pinMode(reset_line, OUTPUT);
  pinMode(data_bus_1, OUTPUT);
  pinMode(data_bus_2, OUTPUT);
  pinMode(data_bus_3, OUTPUT);
  pinMode(data_bus_4, OUTPUT);
  
  digitalWrite(output_line, LOW);
  digitalWrite(keypad_latch, LOW);
  digitalWrite(colons, LOW);
  digitalWrite(clock_line, HIGH);
  digitalWrite(reset_line, LOW);
  digitalWrite(data_bus_1, LOW);
  digitalWrite(data_bus_2, LOW);
  digitalWrite(data_bus_3, LOW);
  digitalWrite(data_bus_4, LOW);
  
  reset_4017();
  Serial.print("Display IO Test"); 
}


void loop() { 
   if(i>9)
   {
     i=0;
     reset_4017();
   }
    delayMicroseconds(d);
    buton(order[i]);
    seven_seg(displays[order[i]]);
    increment_4017();
    i++;
  //delay(100);
}


void print_button() {
  Serial.print("buttons: ");
  for (i=0;i<15;i++)
  {
    Serial.print(buttons[i]); 
  }
  return;
}


void print_dip() {
  Serial.print("dips: ");
  for (i=0;i<8;i++)
  {
    Serial.print(dip[i]); 
  }
  return;
}


void print_all() {
  Serial.print("all: ");
  for (i=0;i<17;i++)
  {
    Serial.print(all[i]); 
  }
  return;
}


void buton(int input) {
  
  pinMode(data_bus_1, INPUT);
  pinMode(data_bus_2, INPUT);
  pinMode(data_bus_3, INPUT);
  pinMode(data_bus_4, INPUT);
  
  digitalWrite(output_line, HIGH);
  
  digitalWrite(keypad_latch, HIGH);
  digitalWrite(keypad_latch, LOW);

  
  switch (input) {
    case 0: //correct
      if(digitalRead(data_bus_1)) {
         dip[4] = 0;
      }
      else{
         dip[4] = 1;
      }
      if(digitalRead(data_bus_2)) {
         dip[5] = 0;
      }
      else{
         dip[5] = 1;
      }
      if(digitalRead(data_bus_3)) {
         dip[6] = 0;
      }
      else{
         dip[6] = 1;
      }
      if(digitalRead(data_bus_4)) {
         dip[7] = 0;
      }
      else{
         dip[7] = 1;
      }
      break;
    case 1://correct plus speculation
      if(digitalRead(data_bus_1)) {
         dip[0] = 0;
      }
      else{
         dip[0] = 1;
      }
      if(digitalRead(data_bus_2)) {
         dip[1] = 0;
      }
      else{
         dip[1] = 1;
      }
      if(digitalRead(data_bus_3)) {
         dip[2] = 0;
      }
      else{
         dip[2] = 1;
      }
      if(digitalRead(data_bus_4)) {
         dip[3] = 0;
      }
      else{
         dip[3] = 1;
      }
      break;
    case 2://correct plus re-mapping
      if(digitalRead(data_bus_1)) {
         buttons[14] = 0;
      }
      else{
         buttons[14] = 1;
      }
      if(digitalRead(data_bus_2)) {
         buttons[13] = 0;
      }
      else{
         buttons[13] = 1;
      }
      if(digitalRead(data_bus_3)) {
         buttons[12] = 0;
      }
      else{
         buttons[12] = 1;
      }
     /* if(digitalRead(data_bus_4)) {
         all[0] = 1;
      }
      else{
         all[0] = 0;
      }*/
      break;
    case 3://correct
      if(digitalRead(data_bus_1)) {
         buttons[8] = 0;
      }
      else{
         buttons[8] = 1;
      }
      if(digitalRead(data_bus_2)) {
         buttons[9] = 0;
      }
      else{
         buttons[9] = 1;
      }
      if(digitalRead(data_bus_3)) {
         buttons[10] = 0;
      }
      else{
         buttons[10] = 1;
      }
      if(digitalRead(data_bus_4)) {
         buttons[11] = 0;
      }
      else{
         buttons[11] = 1;
      }
      break;
    case 4://correct plus re-mapping
      if(digitalRead(data_bus_1)) {
         buttons[4] = 0;
      }
      else{
         buttons[4] = 1;
      }
      if(digitalRead(data_bus_2)) {
         buttons[5] = 0;
      }
      else{
         buttons[5] = 1;
      }
      if(digitalRead(data_bus_3)) {
         buttons[6] = 0;
      }
      else{
         buttons[6] = 1;
      }
      if(digitalRead(data_bus_4)) {
         buttons[7] = 0;
      }
      else{
         buttons[7] = 1;
      }
      break;
    case 5://correct
      if(digitalRead(data_bus_1)) {
         buttons[0] = 0;
      }
      else{
         buttons[0] = 1;
      }
      if(digitalRead(data_bus_2)) {
         buttons[1] = 0;
      }
      else{
         buttons[1] = 1;
      }
      if(digitalRead(data_bus_3)) {
         buttons[2] = 0;
      }
      else{
         buttons[2] = 1;
      }
      if(digitalRead(data_bus_4)) {
         buttons[3] = 0;
      }
      else{
         buttons[3] = 1;
      }
      break;
    case 6://re-mapped
     /* if(digitalRead(data_bus_1)) {
         all[2] = 1;
      }
      else{
         all[2] = 0;
      }
      if(digitalRead(data_bus_2)) {
         all[3] = 1;
      }
      else{
         all[3] = 0;
      }
      if(digitalRead(data_bus_3)) {
         all[4] = 1;
      }
      else{
         all[4] = 0;
      }
      if(digitalRead(data_bus_4)) {
         all[5] = 1;
      }
      else{
         all[5] = 0;
      }*/
      break;
    case 7://re-mapped
      /*if(digitalRead(data_bus_1)) {
         all[6] = 1;
      }
      else{
         all[6] = 0;
      }
      if(digitalRead(data_bus_2)) {
         all[7] = 1;
      }
      else{
         all[7] = 0;
      }
      if(digitalRead(data_bus_3)) {
         all[8] = 1;
      }
      else{
         all[8] = 0;
      }
      if(digitalRead(data_bus_4)) {
         all[9] = 1;
      }
      else{
         all[9] = 0;
      }*/
      break;
    case 8://re-mapped
     /* if(digitalRead(data_bus_1)) {
         all[10] = 1;
      }
      else{
         all[10] = 0;
      }
      if(digitalRead(data_bus_2)) {
         all[11] = 1;
      }
      else{
         all[11] = 0;
      }
      if(digitalRead(data_bus_3)) {
         all[12] = 1;
      }
      else{
         all[12] = 0;
      }
      if(digitalRead(data_bus_4)) {
         all[13] = 1;
      }
      else{
         all[13] = 0;
      }*/
      break;
    case 9:
     /* if(digitalRead(data_bus_1)) {
         all[14] = 1;
      }
      else{
         all[14] = 0;
      }
      if(digitalRead(data_bus_2)) {
         all[15] = 1;
      }
      else{
         all[15] = 0;
      }
      if(digitalRead(data_bus_3)) {
         all[16] = 1;
      }
      else{
         all[16] = 0;
      }
      if(digitalRead(data_bus_4)) {
         all[1] = 1;
      }
      else{
         all[1] = 0;
      }*/
      break;
    default: 
      break;
  }
  
  
  pinMode(data_bus_1, OUTPUT);
  pinMode(data_bus_2, OUTPUT);
  pinMode(data_bus_3, OUTPUT);
  pinMode(data_bus_4, OUTPUT);
  
  digitalWrite(data_bus_1, LOW);
  digitalWrite(data_bus_2, LOW);
  digitalWrite(data_bus_3, LOW);
  digitalWrite(data_bus_4, LOW);
  
  digitalWrite(output_line, LOW);
  
  return;
}


void seven_seg(int input) {
  //set 0 for both LEDs on
  //set 2 for LED 0, or 2
  //set 1 for LED 1, or 3
  //set invalid (like 'a') for both LEDs off
  switch (input) {
    case 1:
        digitalWrite(data_bus_1, HIGH);
        digitalWrite(data_bus_2, LOW);
        digitalWrite(data_bus_3, LOW);
        digitalWrite(data_bus_4, LOW);
      break;
    case 2:
        digitalWrite(data_bus_1, LOW);
        digitalWrite(data_bus_2, HIGH);
        digitalWrite(data_bus_3, LOW);
        digitalWrite(data_bus_4, LOW);
      break;
    case 3:
        digitalWrite(data_bus_1, HIGH);
        digitalWrite(data_bus_2, HIGH);
        digitalWrite(data_bus_3, LOW);
        digitalWrite(data_bus_4, LOW);
      break;
    case 4:
        digitalWrite(data_bus_1, LOW);
        digitalWrite(data_bus_2, LOW);
        digitalWrite(data_bus_3, HIGH);
        digitalWrite(data_bus_4, LOW);
      break;
    case 5:
        digitalWrite(data_bus_1, HIGH);
        digitalWrite(data_bus_2, LOW);
        digitalWrite(data_bus_3, HIGH);
        digitalWrite(data_bus_4, LOW);
      break;
    case 6:
        digitalWrite(data_bus_1, LOW);
        digitalWrite(data_bus_2, HIGH);
        digitalWrite(data_bus_3, HIGH);
        digitalWrite(data_bus_4, LOW);
      break;
    case 7:
        digitalWrite(data_bus_1, HIGH);
        digitalWrite(data_bus_2, HIGH);
        digitalWrite(data_bus_3, HIGH);
        digitalWrite(data_bus_4, LOW);
      break;
    case 8:
        digitalWrite(data_bus_1, LOW);
        digitalWrite(data_bus_2, LOW);
        digitalWrite(data_bus_3, LOW);
        digitalWrite(data_bus_4, HIGH);
      break;
    case 9:
        digitalWrite(data_bus_1, HIGH);
        digitalWrite(data_bus_2, LOW);
        digitalWrite(data_bus_3, LOW);
        digitalWrite(data_bus_4, HIGH);
      break;
    case 0:
        digitalWrite(data_bus_1, LOW);
        digitalWrite(data_bus_2, LOW);
        digitalWrite(data_bus_3, LOW);
        digitalWrite(data_bus_4, LOW);
      break;
    default: 
        digitalWrite(data_bus_1, HIGH);
        digitalWrite(data_bus_2, HIGH);
        digitalWrite(data_bus_3, HIGH);
        digitalWrite(data_bus_4, HIGH);
  }
  return; 
}


void increment_4017() {
  digitalWrite(clock_line, LOW);
  //delayMicroseconds(1);
  digitalWrite(clock_line, HIGH);
}


void reset_4017() {
  digitalWrite(reset_line, HIGH);
  //delayMicroseconds(1);
  digitalWrite(reset_line, LOW);
}
