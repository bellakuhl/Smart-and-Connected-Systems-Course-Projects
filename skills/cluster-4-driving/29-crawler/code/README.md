# Crawler

To run this codebase, connect the crawlers ECS data pin to GPIO 12 and
the steering data pin to GPIO 15 through the H-Bridge.

Then turn on the crawler and flash this code:

```
idf.py flash
```

The crawler will first be callibrated then cycle through the steering and
speed control directions.

