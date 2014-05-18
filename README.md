fakecheerlights
===============

an MQTT based Cheerlights (http://www.cheerlights.com/) implementation

Unlike the original Cheerlights implementation which has a limited (12) available colours, and uses an HTTP
pull method on the clients, the fakecheerlights system uses raw RGB hex values and a publish/subscribe model
with an MQTT broker.

The components are:
1) a twitter stream follower that watches for tweets containing both 'cheerlights' and 'fakecheerlights'
   This follower then publishes the raw tweet, any matched colour name and the corresponding hex value to
   three mqtt topics (fakecheerlights/raw fakecheerlights/colour and fakecheerlights/rgb)
   
2) an arduino ethernet (developed on a nanode) sketch that subscribes to the rgb stream above and sets the colour
   of a WS2812 LED
