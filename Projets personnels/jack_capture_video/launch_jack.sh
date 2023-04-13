pkill jackd
/usr/bin/jackd -dalsa -dhw:0,0 -r192000 -p4096 -n2 -z n -M -H -C hw:CARD=PCH,DEV=0
