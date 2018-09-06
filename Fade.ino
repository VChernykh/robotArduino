#define speed_left       6
#define speed_right      5 
#define dir_left         7
#define dir_right        4
#define left_SENSOR_PIN  8
#define right_SENSOR_PIN 9

#define speed            100
#define SLOW_speed       35
 
#define BACK_SLOW_speed  30
#define BACK_FAST_speed  50
#define BRAKE_K          4
 
#define STATE_FORWARD    0
#define STATE_right      1
#define STATE_left       2
 
#define speed_STEP       2
 
#define FAST_TIME_THRESHOLD     500
 
int state = STATE_FORWARD;
int currentspeed = speed;
int fastTime = 0;
 
void runForward() 
{
    state = STATE_FORWARD;
 
    fastTime += 1;
    if (fastTime < FAST_TIME_THRESHOLD) {
        currentspeed = SLOW_speed;
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
    state = STATE_right;
    fastTime = 0;
 
    analogWrite(speed_right, 0);
    analogWrite(speed_left, speed);
 
    digitalWrite(dir_left, HIGH);
    digitalWrite(dir_right, HIGH);
}
 
void steerleft() 
{
    state = STATE_left;
    fastTime = 0;
 
    analogWrite(speed_left, 0);
    analogWrite(speed_right, speed);
 
    digitalWrite(dir_left, HIGH);
    digitalWrite(dir_right, HIGH);
}
 
 
void stepBack(int duration, int state) {
    if (!duration)
        return;
    int leftspeed = (state == STATE_right) ? BACK_SLOW_speed : BACK_FAST_speed;
    int rightspeed = (state == STATE_left) ? BACK_SLOW_speed : BACK_FAST_speed;
 
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
 
    int targetState;
 
    if (left == right) {
        targetState = STATE_FORWARD;
    } else if (left) {
        targetState = STATE_left;
    } else {
        targetState = STATE_right;
    }
 
    if (state == STATE_FORWARD && targetState != STATE_FORWARD) {
        int brakeTime = (currentspeed > SLOW_speed) ?
            currentspeed : 0;
        stepBack(brakeTime, targetState);
    }
 
    switch (targetState) {
        case STATE_FORWARD:
            runForward();
            break;
 
        case STATE_right:
            steerright();
            break;
 
        case STATE_left:
            steerleft();
            break;
    }
 
}
