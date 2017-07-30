## Inspiration
Physics is the underpinning of all sports, but forces, trajectories, inertia, or momentum are usually the last thought of someone whose head is in the game! These seemingly dry or boring topics are anything but!

We want to share our love of STEM by showing just how much it touches every aspect of our lives.

## What it does
We built a platform for sports-based demonstrations and learning activities to promote interest in STEM fields. The platform consists of a hardware device that is made of off-the-shelf parts (Arduino 101 and Groove Kit components) and an open-source app. We have built a proof-of-concept of a single learning activity, but the platform can be expanded to cover many other topics.

Using the accelerometer data, we calculate the horizontal and vertical velocities of a football as a person throws it. Then we provide that initial velocity information in the app along with a walkthrough tutorial guiding the user to calculate the predicted range using Newtonian physics. Don't worry, we keep it light and fun! Then we encourage the user to experimentally measure out the range to compare it with their calculated value.

## How we built it
We used the onboard accelerometer of the Arduino 101. Taking the integral of that realtime accelerometer data, we were able to get velocity information. Then we used the onboard BLE radio to beam up the velocity info to the companion app (written in PhoneGap).

## Wiring
* 9V battery to input of Arduino 101
* Groove Kit shield with push button connected to D4
* Onboard accelerometer and BLE

## Getting started
* Program the Arduino 101 with the supplied .ino
* Follow instructions in App folder for iOS and Android compiling
