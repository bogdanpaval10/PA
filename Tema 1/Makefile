# Darius-Florentin Neatu <neatudarius@gmail.com>

# Exemplu de Makefile pentru tema

# tag-uri obligatorii (nume + comportament identic)
# build    => compileaza toata tema
#             (ATENTIE! E important - NU compilati in tag-urile de run. Sesizati?)
# run-p$ID => ruleaza problema cu ID-ul specificat (1, 2, 3, 4)
# clean    => sterge toate fisierele generate

# restul este la alegerea studentului
# TODO

# nume necesar (build)
TARGETS= statistics walsh
build: $(TARGETS)

walsh: walsh.c
	gcc walsh.c -o walsh

statistics: statistics.cpp
	g++ statistics.cpp -o statistics

run-p1:
	./walsh

run-p2:
	./statistics

run-p3: 	 # nume necesar

run-p4:      # nume necesar

clean:
	rm -f *.o $(TARGETS)
