#define speed_left       6
#define speed_right      5 
#define dir_left         7
#define dir_right        4
#define left_SENSOR_PIN  8
#define right_SENSOR_PIN 9

#define speed            100
#define slow_speed       35
 
#define back_slow_speed  30
#define back_FAST_speed  50
#define brake_K          4
 
#define state_FORWARD    0
#define state_right      1
#define state_left       2
 
#define speed_STEP       2
 
#define FAST_TIME_THRESHOLD     500
 
int state = state_FORWARD;
int currentspeed = speed;
int fastTime = 0;
 
void runForward() 
{
    state = state_FORWARD;
 
    fastTime += 1;
    if (fastTime < FAST_TIME_THRESHOLD) {
        currentspeed = slow_speed;
    } else {
        currentspeed = min(currentspeed + speed_STEP, speed);
    }
 
    analogWrite(speed_left, currentspeed);
    analogWrite(speed_right, currentspeed);
 
    digitalWrite(dir_left, HIGH);
    digitalWrite(dir_right, HIGH);
}
 
void steerright() 
{
    state = state_right;
    fastTime = 0;
 
    analogWrite(speed_right, 0);
    analogWrite(speed_left, speed);
 
    digitalWrite(dir_left, HIGH);
    digitalWrite(dir_right, HIGH);
}
 
void steerleft() 
{
    state = state_left;
    fastTime = 0;
 
    analogWrite(speed_left, 0);
    analogWrite(speed_right, speed);
 
    digitalWrite(dir_left, HIGH);
    digitalWrite(dir_right, HIGH);
}
 
 
void stepback(int duration, int state) {
    if (!duration)
        return;
    int leftspeed = (state == state_right) ? back_slow_speed : back_FAST_speed;
    int rightspeed = (state == state_left) ? back_slow_speed : back_FAST_speed;
 
    analogWrite(speed_left, leftspeed);
    analogWrite(speed_right, rightspeed);
 
    // реверс колёс
    digitalWrite(dir_right, LOW);
    digitalWrite(dir_left, LOW);
 
    delay(duration);
}
 
 
void setup() 
{
    for(int i = 4; i <= 7; i++)
        pinMode(i, OUTPUT);
    runForward();
} 
 
void loop() 
{ 
    boolean left = !digitalRead(left_SENSOR_PIN);
    boolean right = !digitalRead(right_SENSOR_PIN);
 
    int targetstate;
 
    if (left == right) {
        targetstate = state_FORWARD;
    } else if (left) {
        targetstate = state_left;
    } else {
        targetstate = state_right;
    }
 
    if (state == state_FORWARD && targetstate != state_FORWARD) {
        int brakeTime = (currentspeed > slow_speed) ?
            currentspeed : 0;
        stepback(brakeTime, targetstate);
    }
 
    switch (targetstate) {
        case state_FORWARD:
            runForward();
            break;
 
        case state_right:
            steerright();
            break;
 
        case state_left:
            steerleft();
            break;
    }
 
}
