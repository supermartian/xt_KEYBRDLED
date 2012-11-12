## About

xt_KEYBRDLED is a netfilter TARGET module which allows you to blink your leds on the keyboard according to your match.

## How to make & install

1. netfilter module

    ```
    make
    insmod xt_KEYBRDLED.ko
    ```
2. userspace addon

    ```
    cd lib
    make libipt_KEYBRDLED.so
    sudo cp libipt_KEYBRDLED.so /usr/lib

## Do it!

    ```
    sudo iptables -A INPUT -t KEYBRDLED
    ```

## TODO

1. An elegant Makefile

2. Fix some crash issues
