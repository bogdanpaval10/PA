# Darius-Florentin Neatu <neatudarius@gmail.com>

# Exemplu de Makefile pentru tema

# tag-uri obligatorii (nume + comportament identic)
# build    => compileaza toata tema
#             (ATENTIE! E important - NU compilati in tag-urile de run. Sesizati?)
# run-p$ID => ruleaza problema cu ID-ul specificat (1, 2, 3, 4)
# clean    => sterge toate fisierele generate

# restul este la alegerea studentului
CC=g++
CFLAGS=-std=c++17 -Wall -g

# nume necesar (build)
build: curatare curse fortificatii beamdrone 

curatare: curatare.o
	$(CC) $(CFLAGS) $^ -o $@

curatare.o: curatare.cpp
	$(CC) $(CFLAGS) -c $<

beamdrone: beamdrone.o
	$(CC) $(CFLAGS) $^ -o $@

beamdrone.o: beamdrone.cpp
	$(CC) $(CFLAGS) -c $<

fortificatii: fortificatii.o
	$(CC) $(CFLAGS) $^ -o $@

fortificatii.o: fortificatii.cpp
	$(CC) $(CFLAGS) -c $<

curse: curse.o
	$(CC) $(CFLAGS) $^ -o $@

curse.o: curse.cpp
	$(CC) $(CFLAGS) -c $<


run-p1:      # nume necesar
	./curatare

run-p2:      # nume necesar
	./fortificatii

run-p3:      # nume necesar
	./beamdrone

run-p4:      # nume necesar
	./curse

clean:		 # nume necesar
	rm -f *.o
	rm -f ./beamdrone
	rm -f ./fortificatii
	rm -f ./curse
