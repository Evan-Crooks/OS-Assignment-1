CC=gcc
CFLAGS=-pthread -lrt
TARGETS=producer consumer

all: $(TARGETS)

producer: producer.c
	gcc producer.c -pthread -lrt -o producer

consumer: consumer.c
	gcc consumer.c -pthread -lrt -o consumer 

clean: 
	gcc cleanup.c -pthread -lrt -o cleanup
	./cleanup
	rm -f $(TARGETS) cleanup

run: all
	./producer & ./consumer &

stop kill:
	killall producer consumer || true