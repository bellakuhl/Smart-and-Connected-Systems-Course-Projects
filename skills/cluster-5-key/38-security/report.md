#  Security in Connected Systems

Author: Isabella Kuhl, 2019-11-20

## Summary & Response

In this skill, I identify weaknesses in Quest 3 (wearable fitness tracker). The first security issue to address is weaknesses in the node.js system used for transmitting the sensor data to the server. One weakness is the lack of privacy for the personal data of the user. Just by navigating to the server on the Pi, anyone is about to see the personal data of the user. Another issue is that if the Pi is stolen, the file containing the sensor data can be accessed.

A "bad guy" can access the system by logging onto the Pi and track and recording the information needed. The user's location can also be accessed by recording the WiFi that the Pi is connected to and tracking its IP address. Finally, the server location can also be tracked and stolen/accessed by tracking the IP address of the Pi.

We can overcome these challenges by implementing the security techniques used in this current quest. By assigning a unique ID and code to each wearable, we can ensure that only registered users are able to access the information. Also adding a username and password to the webserver would prevent others from opening a webpage and viewing the real time user information.

Implementing IoT provisioning is a technique to implement the security measure just mentioned. By requiring a unique user ID and password for the server and sensor, we can both track who is accessing the wearable data as well as prevent non registered persons from using and abusing said data.


-----

## Reminders
- Repo is private
